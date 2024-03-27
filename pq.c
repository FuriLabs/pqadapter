/*
 * Copyright (C) 2024 Bardia Moshiri
 * SPDX-License-Identifier: GPL-3.0+
 * Author: Bardia Moshiri <fakeshell@bardia.tech>
 */

#include "pq.h"
#include <stdio.h>
#include <stdlib.h>

enum PQFeatureID : int32_t {
    DISPLAY_COLOR = 0,
    CONTENT_COLOR,
    CONTENT_COLOR_VIDEO,
    SHARPNESS,
    DYNAMIC_CONTRAST,
    DYNAMIC_SHARPNESS,
    DISPLAY_CCORR,
    DISPLAY_GAMMA,
    DISPLAY_OVER_DRIVE,
    ISO_ADAPTIVE_SHARPNESS,
    ULTRA_RESOLUTION,
    VIDEO_HDR,
    PQ_FEATURE_MAX
};

void set_pq_mode_hidl(GBinderClient* client, const int mode) {
    int status;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;

    // setPQMode
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, mode);
    gbinder_writer_append_int32(&writer, 5);
    gbinder_client_transact_sync_reply(client, 3, req, &status);
    gbinder_local_request_unref(req);
}

void enable_blue_light_hidl(GBinderClient* client, const int mode) {
    int status;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;

    // enableBlueLight
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_bool(&writer, mode);
    gbinder_writer_append_int32(&writer, 5);
    gbinder_client_transact_sync_reply(client, 14, req, &status);
    gbinder_local_request_unref(req);
}

void set_blue_light_strength_hidl(GBinderClient* client, const int mode) {
    int status;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;

    // setBlueLightStrength
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, mode);
    gbinder_writer_append_int32(&writer, 5);
    gbinder_client_transact_sync_reply(client, 16, req, &status);
    gbinder_local_request_unref(req);
}

void enable_chameleon_hidl(GBinderClient* client, const int mode) {
    int status;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;

    // enableChameleon
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_bool(&writer, mode);
    gbinder_writer_append_int32(&writer, 5);
    gbinder_client_transact_sync_reply(client, 18, req, &status);
    gbinder_local_request_unref(req);
}

void set_chameleon_strength_hidl(GBinderClient* client, const int mode) {
    int status;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;

    // setChameleonStrength
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, mode);
    gbinder_writer_append_int32(&writer, 5);
    gbinder_client_transact_sync_reply(client, 20, req, &status);
    gbinder_local_request_unref(req);
}

void set_gamma_index_hidl(GBinderClient* client, const int mode) {
    int status;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;

    // setGammaIndex
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_bool(&writer, mode);
    gbinder_writer_append_int32(&writer, 5);
    gbinder_client_transact_sync_reply(client, 27, req, &status);
    gbinder_local_request_unref(req);
}

void set_feature_display_color_hidl(GBinderClient* client, const int mode) {
    int status;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;

    // setFeatureSwitch
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, DISPLAY_COLOR);
    gbinder_writer_append_int32(&writer, mode);
    gbinder_client_transact_sync_reply(client, 12, req, &status);
    gbinder_local_request_unref(req);
}

void set_feature_content_color_hidl(GBinderClient* client, const int mode) {
    int status;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;

    // setFeatureSwitch
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, CONTENT_COLOR);
    gbinder_writer_append_int32(&writer, mode);
    gbinder_client_transact_sync_reply(client, 12, req, &status);
    gbinder_local_request_unref(req);
}

void set_feature_content_color_video_hidl(GBinderClient* client, const int mode) {
    int status;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;

    // setFeatureSwitch
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, CONTENT_COLOR_VIDEO);
    gbinder_writer_append_int32(&writer, mode);
    gbinder_client_transact_sync_reply(client, 12, req, &status);
    gbinder_local_request_unref(req);
}

void set_feature_sharpness_hidl(GBinderClient* client, const int mode) {
    int status;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;

    // setFeatureSwitch
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, SHARPNESS);
    gbinder_writer_append_int32(&writer, mode);
    gbinder_client_transact_sync_reply(client, 12, req, &status);
    gbinder_local_request_unref(req);
}

void set_feature_dynamic_contrast_hidl(GBinderClient* client, const int mode) {
    int status;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;

    // setFeatureSwitch
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, DYNAMIC_CONTRAST);
    gbinder_writer_append_int32(&writer, mode);
    gbinder_client_transact_sync_reply(client, 12, req, &status);
    gbinder_local_request_unref(req);
}

void set_feature_dynamic_sharpness_hidl(GBinderClient* client, const int mode) {
    int status;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;

    // setFeatureSwitch
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, DYNAMIC_SHARPNESS);
    gbinder_writer_append_int32(&writer, mode);
    gbinder_client_transact_sync_reply(client, 12, req, &status);
    gbinder_local_request_unref(req);
}

void set_feature_display_ccorr_hidl(GBinderClient* client, const int mode) {
    int status;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;

    // setFeatureSwitch
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, DISPLAY_CCORR);
    gbinder_writer_append_int32(&writer, mode);
    gbinder_client_transact_sync_reply(client, 12, req, &status);
    gbinder_local_request_unref(req);
}

void set_feature_display_gamma_hidl(GBinderClient* client, const int mode) {
    int status;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;

    // setFeatureSwitch
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, DISPLAY_GAMMA);
    gbinder_writer_append_int32(&writer, mode);
    gbinder_client_transact_sync_reply(client, 12, req, &status);
    gbinder_local_request_unref(req);
}

void set_feature_display_over_drive_hidl(GBinderClient* client, const int mode) {
    int status;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;

    // setFeatureSwitch
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, DISPLAY_OVER_DRIVE);
    gbinder_writer_append_int32(&writer, mode);
    gbinder_client_transact_sync_reply(client, 12, req, &status);
    gbinder_local_request_unref(req);
}

void set_feature_iso_adaptive_sharpness_hidl(GBinderClient* client, const int mode) {
    int status;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;

    // setFeatureSwitch
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, ISO_ADAPTIVE_SHARPNESS);
    gbinder_writer_append_int32(&writer, mode);
    gbinder_client_transact_sync_reply(client, 12, req, &status);
    gbinder_local_request_unref(req);
}

void set_feature_ultra_resolution_hidl(GBinderClient* client, const int mode) {
    int status;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;

    // setFeatureSwitch
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, ULTRA_RESOLUTION);
    gbinder_writer_append_int32(&writer, mode);
    gbinder_client_transact_sync_reply(client, 12, req, &status);
    gbinder_local_request_unref(req);
}

void set_feature_video_hdr_hidl(GBinderClient* client, const int mode) {
    int status;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;

    // setFeatureSwitch
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, VIDEO_HDR);
    gbinder_writer_append_int32(&writer, mode);
    gbinder_client_transact_sync_reply(client, 12, req, &status);
    gbinder_local_request_unref(req);
}

int init_pq_hidl(const int func, const int mode) {
    GBinderServiceManager* sm = gbinder_servicemanager_new("/dev/hwbinder");
    if (!sm) return 1;

    GBinderRemoteObject* remote = gbinder_servicemanager_get_service_sync(sm, "vendor.mediatek.hardware.pq@2.0::IPictureQuality/default", NULL);
    if (!remote) {
        gbinder_servicemanager_unref(sm);
        return 1;
    }

    GBinderClient* client = gbinder_client_new(remote, "vendor.mediatek.hardware.pq@2.0::IPictureQuality");
    if (!client) {
        gbinder_remote_object_unref(remote);
        gbinder_servicemanager_unref(sm);
        return 1;
    }

    if (func == 1) {
        set_pq_mode_hidl(client, mode);
    } else if (func == 2) {
        enable_blue_light_hidl(client, mode);
    } else if (func == 3) {
        set_blue_light_strength_hidl(client, mode);
    } else if (func == 4) {
        enable_chameleon_hidl(client, mode);
    } else if (func == 5) {
        set_chameleon_strength_hidl(client, mode);
    } else if (func == 6) {
        set_gamma_index_hidl(client, mode);
    } else if (func == 7) {
        set_feature_display_color_hidl(client, mode);
    } else if (func == 8) {
        set_feature_content_color_hidl(client, mode);
    } else if (func == 9) {
        set_feature_content_color_video_hidl(client, mode);
    } else if (func == 10) {
        set_feature_sharpness_hidl(client, mode);
    } else if (func == 11) {
        set_feature_dynamic_contrast_hidl(client, mode);
    } else if (func == 12) {
        set_feature_dynamic_sharpness_hidl(client, mode);
    } else if (func == 13) {
        set_feature_display_ccorr_hidl(client, mode);
    } else if (func == 14) {
        set_feature_display_gamma_hidl(client, mode);
    } else if (func == 15) {
        set_feature_display_over_drive_hidl(client, mode);
    } else if (func == 16) {
        set_feature_iso_adaptive_sharpness_hidl(client, mode);
    } else if (func == 17) {
        set_feature_ultra_resolution_hidl(client, mode);
    } else if (func == 18) {
        set_feature_video_hdr_hidl(client, mode);
    } else {
        return 1;
    }

    gbinder_client_unref(client);

    if (!remote) {
        gbinder_remote_object_unref(remote);
    }

    return 0;
}
