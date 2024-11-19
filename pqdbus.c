/*
 * Copyright (C) 2024 Bardia Moshiri
 * SPDX-License-Identifier: GPL-3.0+
 * Author: Bardia Moshiri <fakeshell@bardia.tech>
 */

#include <gio/gio.h>
#include "pq.h"
#include <stdio.h>
#include <stdlib.h>

static const gchar introspection_xml[] =
    "<node>"
    "  <interface name='io.FuriOS.PQ'>"
    "    <method name='SetPQMode'>"
    "      <arg type='i' name='mode' direction='in'/>"
    "    </method>"
    "    <method name='EnableBlueLight'>"
    "      <arg type='i' name='mode' direction='in'/>"
    "    </method>"
    "    <method name='SetBlueLightStrength'>"
    "      <arg type='i' name='mode' direction='in'/>"
    "    </method>"
    "    <method name='EnableChameleon'>"
    "      <arg type='i' name='mode' direction='in'/>"
    "    </method>"
    "    <method name='SetChameleonStrength'>"
    "      <arg type='i' name='mode' direction='in'/>"
    "    </method>"
    "    <method name='SetGammaIndex'>"
    "      <arg type='i' name='mode' direction='in'/>"
    "    </method>"
    "    <method name='SetFeatureDisplayColor'>"
    "      <arg type='i' name='mode' direction='in'/>"
    "    </method>"
    "    <method name='SetFeatureContentColor'>"
    "      <arg type='i' name='mode' direction='in'/>"
    "    </method>"
    "    <method name='SetFeatureContentColorVideo'>"
    "      <arg type='i' name='mode' direction='in'/>"
    "    </method>"
    "    <method name='SetFeatureSharpness'>"
    "      <arg type='i' name='mode' direction='in'/>"
    "    </method>"
    "    <method name='SetFeatureDynamicContrast'>"
    "      <arg type='i' name='mode' direction='in'/>"
    "    </method>"
    "    <method name='SetFeatureDynamicSharpness'>"
    "      <arg type='i' name='mode' direction='in'/>"
    "    </method>"
    "    <method name='SetFeatureDisplayCCorr'>"
    "      <arg type='i' name='mode' direction='in'/>"
    "    </method>"
    "    <method name='SetFeatureDisplayGamma'>"
    "      <arg type='i' name='mode' direction='in'/>"
    "    </method>"
    "    <method name='SetFeatureDisplayOverDrive'>"
    "      <arg type='i' name='mode' direction='in'/>"
    "    </method>"
    "    <method name='SetFeatureISOAdaptiveSharpness'>"
    "      <arg type='i' name='mode' direction='in'/>"
    "    </method>"
    "    <method name='SetFeatureUltraResolution'>"
    "      <arg type='i' name='mode' direction='in'/>"
    "    </method>"
    "    <method name='SetFeatureVideoHDR'>"
    "      <arg type='i' name='mode' direction='in'/>"
    "    </method>"
    "  </interface>"
    "</node>";

typedef struct {
    PQContext *pq_ctx;
    GSettings *settings;
} ServiceContext;

static void
cleanup_service_context(ServiceContext *ctx)
{
    if (!ctx)
        return;
    if (ctx->pq_ctx)
        cleanup_pq_hidl(ctx->pq_ctx);
    if (ctx->settings)
        g_object_unref(ctx->settings);
    free(ctx);
}

static ServiceContext*
init_service_context(void)
{
    ServiceContext *ctx = malloc(sizeof(ServiceContext));
    if (!ctx)
        return NULL;

    ctx->pq_ctx = NULL;
    ctx->settings = NULL;

    ctx->pq_ctx = init_pq_hidl();
    if (!ctx->pq_ctx) {
        cleanup_service_context(ctx);
        return NULL;
    }

    GSettingsSchemaSource *schema_source = g_settings_schema_source_get_default();
    GSettingsSchema *schema = g_settings_schema_source_lookup(schema_source, "io.furios.pq", TRUE);
    ctx->settings = schema ? g_settings_new("io.furios.pq") : NULL;

    if (!ctx->settings) {
        cleanup_service_context(ctx);
        return NULL;
    }

    return ctx;
}

static void
handle_method_call(GDBusConnection* connection,
                   const gchar* sender,
                   const gchar* object_path,
                   const gchar* interface_name,
                   const gchar* method_name,
                   GVariant* parameters,
                   GDBusMethodInvocation* invocation,
                   gpointer user_data)
{
    ServiceContext *ctx = (ServiceContext*)user_data;
    int mode;
    g_variant_get(parameters, "(i)", &mode);

    if (g_strcmp0(method_name, "SetPQMode") == 0)
        set_pq_mode_hidl(ctx->pq_ctx->client, mode, ctx->settings);
    else if (g_strcmp0(method_name, "EnableBlueLight") == 0)
        enable_blue_light_hidl(ctx->pq_ctx->client, mode, ctx->settings);
    else if (g_strcmp0(method_name, "SetBlueLightStrength") == 0)
        set_blue_light_strength_hidl(ctx->pq_ctx->client, mode, ctx->settings);
    else if (g_strcmp0(method_name, "EnableChameleon") == 0)
        enable_chameleon_hidl(ctx->pq_ctx->client, mode, ctx->settings);
    else if (g_strcmp0(method_name, "SetChameleonStrength") == 0)
        set_chameleon_strength_hidl(ctx->pq_ctx->client, mode, ctx->settings);
    else if (g_strcmp0(method_name, "SetGammaIndex") == 0)
        set_gamma_index_hidl(ctx->pq_ctx->client, mode, ctx->settings);
    else if (g_strcmp0(method_name, "SetFeatureDisplayColor") == 0)
        set_feature_display_color_hidl(ctx->pq_ctx->client, mode, ctx->settings);
    else if (g_strcmp0(method_name, "SetFeatureContentColor") == 0)
        set_feature_content_color_hidl(ctx->pq_ctx->client, mode, ctx->settings);
    else if (g_strcmp0(method_name, "SetFeatureContentColorVideo") == 0)
        set_feature_content_color_video_hidl(ctx->pq_ctx->client, mode, ctx->settings);
    else if (g_strcmp0(method_name, "SetFeatureSharpness") == 0)
        set_feature_sharpness_hidl(ctx->pq_ctx->client, mode, ctx->settings);
    else if (g_strcmp0(method_name, "SetFeatureDynamicContrast") == 0)
        set_feature_dynamic_contrast_hidl(ctx->pq_ctx->client, mode, ctx->settings);
    else if (g_strcmp0(method_name, "SetFeatureDynamicSharpness") == 0)
        set_feature_dynamic_sharpness_hidl(ctx->pq_ctx->client, mode, ctx->settings);
    else if (g_strcmp0(method_name, "SetFeatureDisplayCCorr") == 0)
        set_feature_display_ccorr_hidl(ctx->pq_ctx->client, mode, ctx->settings);
    else if (g_strcmp0(method_name, "SetFeatureDisplayGamma") == 0)
        set_feature_display_gamma_hidl(ctx->pq_ctx->client, mode, ctx->settings);
    else if (g_strcmp0(method_name, "SetFeatureDisplayOverDrive") == 0)
        set_feature_display_over_drive_hidl(ctx->pq_ctx->client, mode, ctx->settings);
    else if (g_strcmp0(method_name, "SetFeatureISOAdaptiveSharpness") == 0)
        set_feature_iso_adaptive_sharpness_hidl(ctx->pq_ctx->client, mode, ctx->settings);
    else if (g_strcmp0(method_name, "SetFeatureUltraResolution") == 0)
        set_feature_ultra_resolution_hidl(ctx->pq_ctx->client, mode, ctx->settings);
    else if (g_strcmp0(method_name, "SetFeatureVideoHDR") == 0)
        set_feature_video_hdr_hidl(ctx->pq_ctx->client, mode, ctx->settings);

    g_dbus_method_invocation_return_value(invocation, NULL);
}

static const
GDBusInterfaceVTable interface_vtable = {
    handle_method_call,
    NULL,
    NULL
};

static void
on_bus_acquired(GDBusConnection* connection,
                const gchar* name,
                gpointer user_data)
{
    GDBusNodeInfo* introspection_data = ((gpointer*)user_data)[0];
    ServiceContext* service_ctx = ((gpointer*)user_data)[1];
    GError* error = NULL;

    g_dbus_connection_register_object(
        connection,
        "/io/FuriOS/PQ",
        introspection_data->interfaces[0],
        &interface_vtable,
        service_ctx,
        NULL,
        &error);

    if (error) {
        g_printerr("Error registering object: %s\n", error->message);
        g_error_free(error);
    }
}

static void
on_name_acquired(GDBusConnection* connection,
                 const gchar* name,
                 gpointer user_data)
{
    g_print("Name acquired: %s\n", name);
}

static void
on_name_lost(GDBusConnection* connection,
             const gchar* name,
             gpointer user_data)
{
    g_printerr("Name lost: %s\n", name);
    GMainLoop *loop = ((gpointer*)user_data)[2];
    if (loop)
        g_main_loop_quit(loop);
}

int
main(int argc, char* argv[])
{
    GMainLoop* loop;
    guint owner_id;
    GError* error = NULL;

    ServiceContext* service_ctx = init_service_context();
    if (!service_ctx) {
        g_printerr("Failed to initialize service context\n");
        return 1;
    }

    GDBusNodeInfo* introspection_data = g_dbus_node_info_new_for_xml(introspection_xml, &error);
    if (error) {
        g_printerr("Error parsing introspection XML: %s\n", error->message);
        g_error_free(error);
        cleanup_service_context(service_ctx);
        return 1;
    }

    gpointer user_data[] = {
        introspection_data,
        service_ctx,
        NULL
    };

    loop = g_main_loop_new(NULL, FALSE);
    user_data[2] = loop;

    owner_id = g_bus_own_name(
        G_BUS_TYPE_SESSION,
        "io.FuriOS.PQ",
        G_BUS_NAME_OWNER_FLAGS_NONE,
        on_bus_acquired,
        on_name_acquired,
        on_name_lost,
        user_data,
        NULL);

    g_main_loop_run(loop);

    g_bus_unown_name(owner_id);
    g_dbus_node_info_unref(introspection_data);
    g_main_loop_unref(loop);
    cleanup_service_context(service_ctx);

    return 0;
}
