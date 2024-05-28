/*
 * Copyright (C) 2024 Bardia Moshiri
 * SPDX-License-Identifier: GPL-3.0+
 * Author: Bardia Moshiri <fakeshell@bardia.tech>
 */

#include <gio/gio.h>
#include "pq.h"
#include <stdio.h>
#include <stdlib.h>

static void handle_method_call(
    GDBusConnection* connection,
    const gchar* sender,
    const gchar* object_path,
    const gchar* interface_name,
    const gchar* method_name,
    GVariant* parameters,
    GDBusMethodInvocation* invocation,
    gpointer user_data) {

    int mode;
    g_variant_get(parameters, "(i)", &mode);

    int func = 0;

    if (g_strcmp0(method_name, "SetPQMode") == 0) {
        func = SET_PQ_MODE;
    } else if (g_strcmp0(method_name, "EnableBlueLight") == 0) {
        func = ENABLE_BLUE_LIGHT;
    } else if (g_strcmp0(method_name, "SetBlueLightStrength") == 0) {
        func = SET_BLUE_LIGHT_STRENGTH;
    } else if (g_strcmp0(method_name, "EnableChameleon") == 0) {
        func = ENABLE_CHAMELEON;
    } else if (g_strcmp0(method_name, "SetChameleonStrength") == 0) {
        func = SET_CHAMELEON_STRENGTH;
    } else if (g_strcmp0(method_name, "SetGammaIndex") == 0) {
        func = SET_GAMMA_INDEX;
    } else if (g_strcmp0(method_name, "SetFeatureDisplayColor") == 0) {
        func = SET_FEATURE_DISPLAY_COLOR;
    } else if (g_strcmp0(method_name, "SetFeatureContentColor") == 0) {
        func = SET_FEATURE_CONTENT_COLOR;
    } else if (g_strcmp0(method_name, "SetFeatureContentColorVideo") == 0) {
        func = SET_FEATURE_CONTENT_COLOR_VIDEO;
    } else if (g_strcmp0(method_name, "SetFeatureSharpness") == 0) {
        func = SET_FEATURE_SHARPNESS;
    } else if (g_strcmp0(method_name, "SetFeatureDynamicContrast") == 0) {
        func = SET_FEATURE_DYNAMIC_CONTRAST;
    } else if (g_strcmp0(method_name, "SetFeatureDynamicSharpness") == 0) {
        func = SET_FEATURE_DYNAMIC_SHARPNESS;
    } else if (g_strcmp0(method_name, "SetFeatureDisplayCCorr") == 0) {
        func = SET_FEATURE_DISPLAY_CCORR;
    } else if (g_strcmp0(method_name, "SetFeatureDisplayGamma") == 0) {
        func = SET_FEATURE_DISPLAY_GAMMA;
    } else if (g_strcmp0(method_name, "SetFeatureDisplayOverDrive") == 0) {
        func = SET_FEATURE_DISPLAY_OVER_DRIVE;
    } else if (g_strcmp0(method_name, "SetFeatureISOAdaptiveSharpness") == 0) {
        func = SET_FEATURE_ISO_ADAPTIVE_SHARPNESS;
    } else if (g_strcmp0(method_name, "SetFeatureUltraResolution") == 0) {
        func = SET_FEATURE_ULTRA_RESOLUTION;
    } else if (g_strcmp0(method_name, "SetFeatureVideoHDR") == 0) {
        func = SET_FEATURE_VIDEO_HDR;
    }

    if (func != 0) {
        init_pq_hidl(func, mode);
    }

    g_dbus_method_invocation_return_value(invocation, NULL);
}

static const GDBusInterfaceVTable interface_vtable = {
    handle_method_call,
    NULL,
    NULL
};

static void on_bus_acquired(
    GDBusConnection* connection,
    const gchar* name,
    gpointer user_data) {

    GDBusNodeInfo* introspection_data = (GDBusNodeInfo*)user_data;

    GError* error = NULL;

    g_dbus_connection_register_object(
        connection,
        "/io/FuriOS/PQ",
        introspection_data->interfaces[0],
        &interface_vtable,
        NULL,
        NULL,
        &error);

    if (error) {
        g_printerr("Error registering object: %s\n", error->message);
        g_error_free(error);
    }
}

static void on_name_acquired(
    GDBusConnection* connection,
    const gchar* name,
    gpointer user_data) {
    g_print("Name acquired: %s\n", name);
}

static void on_name_lost(
    GDBusConnection* connection,
    const gchar* name,
    gpointer user_data) {
    g_printerr("Name lost: %s\n", name);
}

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

int main(int argc, char* argv[]) {
    GMainLoop* loop;
    guint owner_id;
    guint registration_id;
    GError* error = NULL;

    GDBusNodeInfo* introspection_data = g_dbus_node_info_new_for_xml(introspection_xml, &error);
    if (error) {
        g_printerr("Error parsing introspection XML: %s\n", error->message);
        g_error_free(error);
        return 1;
    }

    owner_id = g_bus_own_name(
        G_BUS_TYPE_SESSION,
        "io.FuriOS.PQ",
        G_BUS_NAME_OWNER_FLAGS_NONE,
        on_bus_acquired,
        on_name_acquired,
        on_name_lost,
        introspection_data,
        NULL);

    loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(loop);

    g_bus_unown_name(owner_id);
    g_dbus_node_info_unref(introspection_data);
    g_main_loop_unref(loop);

    return 0;
}
