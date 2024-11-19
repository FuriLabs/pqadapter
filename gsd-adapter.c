/*
 * Copyright (C) 2024 Bardia Moshiri
 * SPDX-License-Identifier: GPL-3.0+
 * Author: Bardia Moshiri <fakeshell@bardia.tech>
 */

#include "pq.h"
#include "alsa.h"
#include <gio/gio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <hybris/properties/properties.h>

typedef struct {
    GSettings *settings_color;
    GSettings *settings_privacy;
    GSettings *settings_location;
    GSettings *settings_pq;
    GMainLoop *main_loop;
    PQContext *pq_ctx;

    guint32 original_min_temperature;
    guint32 original_max_temperature;
    guint32 scale_min;
    guint32 scale_max;

    const char *pq_keys[PQ_FUNCTION_MAX - 1];
} AppSettings;

static AppSettings *
init_app_settings()
{
    AppSettings* settings = malloc(sizeof(AppSettings));
    if (!settings)
        return NULL;

    settings->pq_ctx = init_pq_hidl();
    if (!settings->pq_ctx) {
        free(settings);
        return NULL;
    }

    settings->settings_color = g_settings_new("org.gnome.settings-daemon.plugins.color");
    settings->settings_privacy = g_settings_new("org.gnome.desktop.privacy");
    settings->settings_location = g_settings_new("org.gnome.system.location");
    settings->settings_pq = g_settings_new("io.furios.pq");
    settings->main_loop = NULL;

    settings->original_min_temperature = 1700;
    settings->original_max_temperature = 4700;
    settings->scale_min = 0;
    settings->scale_max = 1000;

    static const char *keys[] = {
        "pq-mode",
        "blue-light",
        "blue-light-strength",
        "chameleon",
        "chameleon-strength",
        "gamma-index",
        "display-color",
        "content-color",
        "content-color-video",
        "sharpness",
        "dynamic-contrast",
        "dynamic-sharpness",
        "display-ccorr",
        "display-gamma",
        "display-over-drive",
        "iso-adaptive-sharpness",
        "ultra-resolution",
        "video-hdr",
        "global-pq-switch",
        "global-pq-strength"
    };

    for (int i = 0; i < PQ_FUNCTION_MAX - 1; i++) {
        settings->pq_keys[i] = keys[i];
    }

    return settings;
}

static void
on_night_light_enabled(GSettings *settings,
                       gchar *key,
                       gpointer data)
{
    AppSettings *app_settings = (AppSettings*)data;
    gboolean night_light_enabled = g_settings_get_boolean(settings, key);
    g_print("Current Night Light setting: %s\n", night_light_enabled ? "enabled" : "disabled");

    if (night_light_enabled)
        enable_blue_light_hidl(app_settings->pq_ctx->client, 1, app_settings->settings_pq);
    else
        enable_blue_light_hidl(app_settings->pq_ctx->client, 0, app_settings->settings_pq);
}

static void
on_night_light_temperature_changed(GSettings *settings,
                                   gchar *key,
                                   gpointer data)
{
    AppSettings *app_settings = (AppSettings*)data;
    gboolean night_light_enabled = g_settings_get_boolean(settings, "night-light-enabled");

    if (night_light_enabled) {
        guint32 temperature = g_settings_get_uint(settings, key);

        guint32 reversed_temperature = app_settings->original_max_temperature -
                                     (temperature - app_settings->original_min_temperature);

        double scaled_temperature = (double)(reversed_temperature - app_settings->original_min_temperature) *
                                  (app_settings->scale_max - app_settings->scale_min) /
                                  (app_settings->original_max_temperature - app_settings->original_min_temperature) +
                                  app_settings->scale_min;
        scaled_temperature = scaled_temperature * 0.3;

        g_print("Night Light temperature mapped: %.0f \n", scaled_temperature);
        set_blue_light_strength_hidl(app_settings->pq_ctx->client,
                                     (int)scaled_temperature,
                                     app_settings->settings_pq);
    }
}

static void
clear_directory(const char *path)
{
    DIR *dir = opendir(path);
    if (dir) {
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            char full_path[512];
            snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
            remove(full_path);
        }
        closedir(dir);
        rmdir(path);
        g_print("GStreamer cache cleared.\n");
    }
}

static void
on_privacy_setting_changed(GSettings *settings,
                           gchar *key,
                           gpointer data)
{
    AppSettings *app_settings = (AppSettings*)data;
    gboolean setting_value = g_settings_get_boolean(settings, key);
    g_print("Privacy setting '%s' changed to: %s\n", key, setting_value ? "true" : "false");

    if (g_strcmp0(key, "disable-microphone") == 0) {
        set_capture_state("default", "Capture", setting_value ? 0 : 1);
    } else if (g_strcmp0(key, "disable-camera") == 0) {
        char service_state[PROP_VALUE_MAX];
        if (setting_value) {
            if (property_get("init.svc.camerahalserver", service_state, "stopped") &&
                strcmp(service_state, "running") == 0) {
                property_set("ctl.stop", "camerahalserver");
                g_print("Camera HAL server stopped.\n");
            }
        } else {
            if (property_get("init.svc.camerahalserver", service_state, "running") &&
                strcmp(service_state, "stopped") == 0) {
                property_set("ctl.start", "camerahalserver");
                g_print("Camera HAL server started.\n");

                char cache_dir[512];
                snprintf(cache_dir, sizeof(cache_dir), "%s/.cache/gstreamer-1.0", getenv("HOME"));
                clear_directory(cache_dir);
            }
        }
    }
}

static void
on_location_setting_changed(GSettings *settings,
                            gchar *key,
                            gpointer data)
{
    AppSettings *app_settings = (AppSettings*)data;
    gboolean setting_value = g_settings_get_boolean(settings, key);
    g_print("Location setting '%s' changed to: %s\n", key, setting_value ? "true" : "false");

    char service_state[PROP_VALUE_MAX];
    if (setting_value) {
        if (property_get("init.svc.vendor.gnss-default", service_state, "running") &&
            strcmp(service_state, "stopped") == 0) {
            property_set("ctl.start", "vendor.gnss-default");
            g_print("GNSS service started.\n");
            system("systemctl restart geoclue");
        }
    } else {
        if (property_get("init.svc.vendor.gnss-default", service_state, "stopped") &&
            strcmp(service_state, "running") == 0) {
            property_set("ctl.stop", "vendor.gnss-default");
            g_print("GNSS service stopped.\n");
            system("systemctl stop geoclue");
        }
    }
}

static void
pq_gsettings_init(AppSettings *app_settings)
{
    if (!app_settings->settings_pq) {
        fprintf(stderr, "Failed to initialize GSettings\n");
        return;
    }

    for (int i = 0; i < PQ_FUNCTION_MAX - 1; i++) {
        int mode = g_settings_get_int(app_settings->settings_pq, app_settings->pq_keys[i]);
        g_print("Setting %s to %d\n", app_settings->pq_keys[i], mode);

        switch (i + 1) {
            case 1:
                set_pq_mode_hidl(app_settings->pq_ctx->client, mode, app_settings->settings_pq);
                break;
            case 2:
                enable_blue_light_hidl(app_settings->pq_ctx->client, mode, app_settings->settings_pq);
                break;
            case 3:
                set_blue_light_strength_hidl(app_settings->pq_ctx->client, mode, app_settings->settings_pq);
                break;
            case 4:
                enable_chameleon_hidl(app_settings->pq_ctx->client, mode, app_settings->settings_pq);
                break;
            case 5:
                set_chameleon_strength_hidl(app_settings->pq_ctx->client, mode, app_settings->settings_pq);
                break;
            case 6:
                set_gamma_index_hidl(app_settings->pq_ctx->client, mode, app_settings->settings_pq);
                break;
            case 7:
                set_feature_display_color_hidl(app_settings->pq_ctx->client, mode, app_settings->settings_pq);
                break;
            case 8:
                set_feature_content_color_hidl(app_settings->pq_ctx->client, mode, app_settings->settings_pq);
                break;
            case 9:
                set_feature_content_color_video_hidl(app_settings->pq_ctx->client, mode, app_settings->settings_pq);
                break;
            case 10:
                set_feature_sharpness_hidl(app_settings->pq_ctx->client, mode, app_settings->settings_pq);
                break;
            case 11:
                set_feature_dynamic_contrast_hidl(app_settings->pq_ctx->client, mode, app_settings->settings_pq);
                break;
            case 12:
                set_feature_dynamic_sharpness_hidl(app_settings->pq_ctx->client, mode, app_settings->settings_pq);
                break;
            case 13:
                set_feature_display_ccorr_hidl(app_settings->pq_ctx->client, mode, app_settings->settings_pq);
                break;
            case 14:
                set_feature_display_gamma_hidl(app_settings->pq_ctx->client, mode, app_settings->settings_pq);
                break;
            case 15:
                set_feature_display_over_drive_hidl(app_settings->pq_ctx->client, mode, app_settings->settings_pq);
                break;
            case 16:
                set_feature_iso_adaptive_sharpness_hidl(app_settings->pq_ctx->client, mode, app_settings->settings_pq);
                break;
            case 17:
                set_feature_ultra_resolution_hidl(app_settings->pq_ctx->client, mode, app_settings->settings_pq);
                break;
            case 18:
                set_feature_video_hdr_hidl(app_settings->pq_ctx->client, mode, app_settings->settings_pq);
                break;
            case 19:
                set_global_pq_switch_hidl(app_settings->pq_ctx->client, mode, app_settings->settings_pq);
                break;
            case 20:
                set_global_pq_strength_hidl(app_settings->pq_ctx->client, mode, app_settings->settings_pq);
                break;
        }
    }
}

static void
cleanup_app_settings(AppSettings *settings)
{
    if (settings->settings_color)
        g_object_unref(settings->settings_color);
    if (settings->settings_privacy)
        g_object_unref(settings->settings_privacy);
    if (settings->settings_location)
        g_object_unref(settings->settings_location);
    if (settings->settings_pq)
        g_object_unref(settings->settings_pq);
    if (settings->main_loop)
        g_main_loop_unref(settings->main_loop);
    free(settings);
}

int
main(int argc, char **argv)
{
    AppSettings *app_settings = init_app_settings();

    pq_gsettings_init(app_settings);

    if (app_settings->settings_color) {
        on_night_light_enabled(app_settings->settings_color, "night-light-enabled", app_settings);
        on_night_light_temperature_changed(app_settings->settings_color, "night-light-temperature", app_settings);

        g_signal_connect(app_settings->settings_color, "changed::night-light-enabled",
                         G_CALLBACK(on_night_light_enabled), app_settings);
        g_signal_connect(app_settings->settings_color, "changed::night-light-temperature",
                         G_CALLBACK(on_night_light_temperature_changed), app_settings);
    }

    if (app_settings->settings_privacy) {
        g_signal_connect(app_settings->settings_privacy, "changed::disable-camera",
                         G_CALLBACK(on_privacy_setting_changed), app_settings);
        g_signal_connect(app_settings->settings_privacy, "changed::disable-microphone",
                         G_CALLBACK(on_privacy_setting_changed), app_settings);
        g_signal_connect(app_settings->settings_privacy, "changed::disable-sound-output",
                         G_CALLBACK(on_privacy_setting_changed), app_settings);
    }

    if (app_settings->settings_location) {
        g_signal_connect(app_settings->settings_location, "changed::enabled",
                         G_CALLBACK(on_location_setting_changed), app_settings);
    }

    app_settings->main_loop = g_main_loop_new(NULL, FALSE);
    if (app_settings->main_loop)
        g_main_loop_run(app_settings->main_loop);

    cleanup_app_settings(app_settings);
    return 0;
}
