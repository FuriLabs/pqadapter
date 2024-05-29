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

static void on_night_light_enabled(GSettings *settings, gchar *key, gpointer data) {
    gboolean night_light_enabled = g_settings_get_boolean(settings, key);
    printf("Current Night Light setting: %s\n", night_light_enabled ? "enabled" : "disabled");

    // 2 is enableBlueLight in this context
    if (night_light_enabled) {
        init_pq_hidl(ENABLE_BLUE_LIGHT, 1);
    } else {
        init_pq_hidl(ENABLE_BLUE_LIGHT, 0);
    }
}

static void on_night_light_temperature_changed(GSettings *settings, gchar *key, gpointer data) {
    gboolean night_light_enabled = g_settings_get_boolean(settings, "night-light-enabled");

    if (night_light_enabled) {
        const guint32 original_min_temperature = 1700;
        const guint32 original_max_temperature = 4700;
        const guint32 scale_min = 0;
        const guint32 scale_max = 1000;

        guint32 temperature = g_settings_get_uint(settings, key);

        // Reverse the temperature
        guint32 reversed_temperature = original_max_temperature - (temperature - original_min_temperature);

        // Map the reversed temperature to a 0-1000 scale
        double scaled_temperature = (double)(reversed_temperature - original_min_temperature) * (scale_max - scale_min) / (original_max_temperature - original_min_temperature) + scale_min;
        scaled_temperature = scaled_temperature * 0.3;

        printf("Night Light temperature mapped: %.0f \n", scaled_temperature);

        // 3 is setBlueLightStrength in this context
        init_pq_hidl(SET_BLUE_LIGHT_STRENGTH, (int)scaled_temperature);
    }
}

static void clear_directory(const char *path) {
    DIR *dir = opendir(path);
    if (dir) {
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }
            char full_path[512];
            snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
            remove(full_path);
        }
        closedir(dir);
        rmdir(path);
        printf("GStreamer cache cleared.\n");
    }
}

static void on_privacy_setting_changed(GSettings *settings, gchar *key, gpointer data) {
    gboolean setting_value = g_settings_get_boolean(settings, key);
    printf("Privacy setting '%s' changed to: %s\n", key, setting_value ? "true" : "false");

    if (g_strcmp0(key, "disable-microphone") == 0) {
        // Toggle microphone mute state based on setting
        set_capture_state("default", "Capture", setting_value ? 0 : 1);
    } else if (g_strcmp0(key, "disable-camera") == 0) {
        char service_state[PROP_VALUE_MAX];
        if (setting_value) {
            if (property_get("init.svc.camerahalserver", service_state, "stopped") && strcmp(service_state, "running") == 0) {
                // Stop the camera HAL server
                property_set("ctl.stop", "camerahalserver");
                printf("Camera HAL server stopped.\n");
            }
        } else {
            if (property_get("init.svc.camerahalserver", service_state, "running") && strcmp(service_state, "stopped") == 0) {
                property_set("ctl.start", "camerahalserver");
                printf("Camera HAL server started.\n");

                char cache_dir[512];
                snprintf(cache_dir, sizeof(cache_dir), "%s/.cache/gstreamer-1.0", getenv("HOME"));
                clear_directory(cache_dir);
            }
        }
    }
}

static void on_location_setting_changed(GSettings *settings, gchar *key, gpointer data) {
    gboolean setting_value = g_settings_get_boolean(settings, key);
    printf("Location setting '%s' changed to: %s\n", key, setting_value ? "true" : "false");

    char service_state[PROP_VALUE_MAX];
    if (setting_value) {
        if (property_get("init.svc.vendor.gnss-default", service_state, "running") && strcmp(service_state, "stopped") == 0) {
            // Start the GNSS service
            property_set("ctl.start", "vendor.gnss-default");
            printf("GNSS service started.\n");
            system("systemctl restart geoclue");
        }
    } else {
        if (property_get("init.svc.vendor.gnss-default", service_state, "stopped") && strcmp(service_state, "running") == 0) {
            // Stop the GNSS service
            property_set("ctl.stop", "vendor.gnss-default");
            printf("GNSS service stopped.\n");
            system("systemctl stop geoclue");
        }
    }
}

void pq_startup() {
    GSettings *settings = g_settings_new("io.furios.pq");

    if (!settings) {
        fprintf(stderr, "Failed to initialize GSettings\n");
        return;
    }

    const char *keys[PQ_FUNCTION_MAX - 1] = {
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
        int mode = g_settings_get_int(settings, keys[i]);
        enum PQFunctions function = (enum PQFunctions)(i + 1);
        printf("Setting %s to %d\n", keys[i], mode);
        init_pq_hidl(function, mode);
    }

    g_object_unref(settings);
}

int main(int argc, char **argv) {
    pq_startup();

    GSettings *settings_color = g_settings_new("org.gnome.settings-daemon.plugins.color");
    GSettings *settings_privacy = g_settings_new("org.gnome.desktop.privacy");
    GSettings *settings_location = g_settings_new("org.gnome.system.location");

    if (settings_color) {
        // check status and apply chnages once on startup
        on_night_light_enabled(settings_color, "night-light-enabled", NULL);
        on_night_light_temperature_changed(settings_color, "night-light-temperature", NULL);

        g_signal_connect(settings_color, "changed::night-light-enabled", G_CALLBACK(on_night_light_enabled), NULL);
        g_signal_connect(settings_color, "changed::night-light-temperature", G_CALLBACK(on_night_light_temperature_changed), NULL);
    }

    if (settings_privacy) {
        g_signal_connect(settings_privacy, "changed::disable-camera", G_CALLBACK(on_privacy_setting_changed), NULL);
        g_signal_connect(settings_privacy, "changed::disable-microphone", G_CALLBACK(on_privacy_setting_changed), NULL);
        g_signal_connect(settings_privacy, "changed::disable-sound-output", G_CALLBACK(on_privacy_setting_changed), NULL);
    }

    if (settings_location) {
        g_signal_connect(settings_location, "changed::enabled", G_CALLBACK(on_location_setting_changed), NULL);
    }

    GMainLoop *loop = g_main_loop_new(NULL, FALSE);
    if (loop) {
        g_main_loop_run(loop);
        g_main_loop_unref(loop);
    }

    if (settings_color) g_object_unref(settings_color);
    if (settings_privacy) g_object_unref(settings_privacy);

    return 0;
}
