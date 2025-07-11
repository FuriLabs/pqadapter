/*
 * Copyright (C) 2024 Bardia Moshiri
 * SPDX-License-Identifier: GPL-3.0+
 * Author: Bardia Moshiri <fakeshell@bardia.tech>
 */

#include "pq.h"
#include <stdio.h>
#include <stdlib.h>
#include <gio/gio.h>

int
set_color_region_hidl(GBinderClient* client,
                      const int split_en,
                      const int start_x,
                      const int end_x,
                      const int start_y,
                      const int end_y)
{
    gint status = 0, retval = 0;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;
    GBinderReader reader;
    GBinderRemoteReply* reply;

    // setColorRegion
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, split_en);
    gbinder_writer_append_int32(&writer, start_x);
    gbinder_writer_append_int32(&writer, end_x);
    gbinder_writer_append_int32(&writer, start_y);
    gbinder_writer_append_int32(&writer, end_y);
    reply = gbinder_client_transact_sync_reply(client, SET_COLOR_REGION, req, &status);

    gbinder_remote_reply_init_reader(reply, &reader);
    gbinder_reader_read_int32(&reader, &status);
    if (status == 0) {
        gbinder_reader_read_int32(&reader, &retval);
        if (retval != 0) {
            g_debug("setColorRegion failed, PQ returned the value %d", retval);
        }
    } else {
        retval = status;
        g_debug("Failed to call setColorRegion, transaction failed with status %d", status);
    }

    gbinder_local_request_unref(req);
    gbinder_remote_reply_unref(reply);

    return retval;
}

int
set_pq_mode_hidl(GBinderClient* client,
                 const int mode,
                 const int step,
                 GSettings *settings)
{
    gint status = 0, retval = 0;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;
    GBinderReader reader;
    GBinderRemoteReply* reply;

    // setPQMode
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, mode);
    gbinder_writer_append_int32(&writer, step);
    reply = gbinder_client_transact_sync_reply(client, SET_PQ_MODE, req, &status);

    gbinder_remote_reply_init_reader(reply, &reader);
    gbinder_reader_read_int32(&reader, &status);
    if (status == 0) {
        gbinder_reader_read_int32(&reader, &retval);
        if (retval != 0) {
            g_debug("setPQMode failed, PQ returned the value %d", retval);
        }
    } else {
        retval = status;
        g_debug("Failed to call setPQMode, transaction failed with status %d", status);
    }

    gbinder_local_request_unref(req);
    gbinder_remote_reply_unref(reply);

    if (settings) {
        g_settings_set_int(settings, "pq-mode", mode);
        g_settings_sync();
    }

    return retval;
}

int
set_tdshp_flag(GBinderClient* client,
               const int tdshp_flag)
{
    gint status = 0, retval = 0;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;
    GBinderReader reader;
    GBinderRemoteReply* reply;

    // setTDSHPFlag
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, tdshp_flag);
    reply = gbinder_client_transact_sync_reply(client, SET_TDSHP_FLAG, req, &status);

    gbinder_remote_reply_init_reader(reply, &reader);
    gbinder_reader_read_int32(&reader, &status);
    if (status == 0) {
        gbinder_reader_read_int32(&reader, &retval);
        if (retval != 0) {
            g_debug("setTDSHPFlag failed, PQ returned the value %d", retval);
        }
    } else {
        retval = status;
        g_debug("Failed to call setTDSHPFlag, transaction failed with status %d", status);
    }

    gbinder_local_request_unref(req);
    gbinder_remote_reply_unref(reply);

    return retval;
}

int
get_tdshp_flag(GBinderClient* client)
{
    gint status = 0, retval = 0, tdshp_flag;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;
    GBinderReader reader;
    GBinderRemoteReply* reply;

    // getTDSHPFlag
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, tdshp_flag);
    reply = gbinder_client_transact_sync_reply(client, GET_TDSHP_FLAG, req, &status);

    gbinder_remote_reply_init_reader(reply, &reader);
    gbinder_reader_read_int32(&reader, &status);
    if (status == 0) {
        gbinder_reader_read_int32(&reader, &retval);
        if (retval != 0) {
            g_debug("getTDSHPFlag failed, PQ returned the value %d", retval);
            retval = -1;
        } else {
            gbinder_reader_read_int32(&reader, &tdshp_flag);
            retval = tdshp_flag;
        }
    } else {
        retval = status;
        g_debug("Failed to call getTDSHPFlag, transaction failed with status %d", status);
    }

    gbinder_local_request_unref(req);
    gbinder_remote_reply_unref(reply);

    return retval;
}

int
set_pq_index_hidl(GBinderClient* client,
                  const int level,
                  const int scenario,
                  const int tuning_mode,
                  const int index,
                  const int step)
{
    gint status = 0, retval = 0;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;
    GBinderReader reader;
    GBinderRemoteReply* reply;

    // setPQIndex
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, level);
    gbinder_writer_append_int32(&writer, scenario);
    gbinder_writer_append_int32(&writer, tuning_mode);
    gbinder_writer_append_int32(&writer, index);
    gbinder_writer_append_int32(&writer, step);
    reply = gbinder_client_transact_sync_reply(client, SET_PQ_INDEX, req, &status);

    gbinder_remote_reply_init_reader(reply, &reader);
    gbinder_reader_read_int32(&reader, &status);
    if (status == 0) {
        gbinder_reader_read_int32(&reader, &retval);
        if (retval != 0) {
            g_debug("setPQIndex failed, PQ returned the value %d", retval);
        }
    } else {
        retval = status;
        g_debug("Failed to call setPQIndex, transaction failed with status %d", status);
    }

    gbinder_local_request_unref(req);
    gbinder_remote_reply_unref(reply);

    return retval;
}

int
set_disp_scenario(GBinderClient* client,
                  const int scenario,
                  const int step)
{
    gint status = 0, retval = 0;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;
    GBinderReader reader;
    GBinderRemoteReply* reply;

    // setDISPScenario
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, scenario);
    gbinder_writer_append_int32(&writer, step);
    reply = gbinder_client_transact_sync_reply(client, SET_DISP_SCENARIO, req, &status);

    gbinder_remote_reply_init_reader(reply, &reader);
    gbinder_reader_read_int32(&reader, &status);
    if (status == 0) {
        gbinder_reader_read_int32(&reader, &retval);
        if (retval != 0) {
            g_debug("setDISPScenario failed, PQ returned the value %d", retval);
        }
    } else {
        retval = status;
        g_debug("Failed to call setDISPScenario, transaction failed with status %d", status);
    }

    gbinder_local_request_unref(req);
    gbinder_remote_reply_unref(reply);

    return retval;
}

int
set_feature_display_color_hidl(GBinderClient* client,
                               const int mode,
                               GSettings *settings)
{
    gint status = 0, retval = 0;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;
    GBinderReader reader;
    GBinderRemoteReply* reply;

    // setFeatureSwitch
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, DISPLAY_COLOR);
    gbinder_writer_append_int32(&writer, mode);
    reply = gbinder_client_transact_sync_reply(client, SET_FEATURE_SWITCH, req, &status);

    gbinder_remote_reply_init_reader(reply, &reader);
    gbinder_reader_read_int32(&reader, &status);
    if (status == 0) {
        gbinder_reader_read_int32(&reader, &retval);
        if (retval != 0) {
            g_debug("setFeatureSwitch display color failed, PQ returned the value %d", retval);
        }
    } else {
        retval = status;
        g_debug("Failed to call setFeatureSwitch display color, transaction failed with status %d", status);
    }

    gbinder_local_request_unref(req);
    gbinder_remote_reply_unref(reply);

    if (settings) {
        g_settings_set_int(settings, "display-color", mode);
        g_settings_sync();
    }

    return retval;
}

int
set_feature_content_color_hidl(GBinderClient* client,
                               const int mode,
                               GSettings *settings)
{
    gint status = 0, retval = 0;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;
    GBinderReader reader;
    GBinderRemoteReply* reply;

    // setFeatureSwitch
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, CONTENT_COLOR);
    gbinder_writer_append_int32(&writer, mode);
    reply = gbinder_client_transact_sync_reply(client, SET_FEATURE_SWITCH, req, &status);

    gbinder_remote_reply_init_reader(reply, &reader);
    gbinder_reader_read_int32(&reader, &status);
    if (status == 0) {
        gbinder_reader_read_int32(&reader, &retval);
        if (retval != 0) {
            g_debug("setFeatureSwitch content color failed, PQ returned the value %d", retval);
        }
    } else {
        retval = status;
        g_debug("Failed to call setFeatureSwitch content color, transaction failed with status %d", status);
    }

    gbinder_local_request_unref(req);
    gbinder_remote_reply_unref(reply);

    if (settings) {
        g_settings_set_int(settings, "content-color", mode);
        g_settings_sync();
    }

    return retval;
}

int
set_feature_content_color_video_hidl(GBinderClient* client,
                                     const int mode,
                                     GSettings *settings)
{
    gint status = 0, retval = 0;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;
    GBinderReader reader;
    GBinderRemoteReply* reply;

    // setFeatureSwitch
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, CONTENT_COLOR_VIDEO);
    gbinder_writer_append_int32(&writer, mode);
    reply = gbinder_client_transact_sync_reply(client, SET_FEATURE_SWITCH, req, &status);

    gbinder_remote_reply_init_reader(reply, &reader);
    gbinder_reader_read_int32(&reader, &status);
    if (status == 0) {
        gbinder_reader_read_int32(&reader, &retval);
        if (retval != 0) {
            g_debug("setFeatureSwitch content color video failed, PQ returned the value %d", retval);
        }
    } else {
        retval = status;
        g_debug("Failed to call setFeatureSwitch content color video, transaction failed with status %d", status);
    }

    gbinder_local_request_unref(req);
    gbinder_remote_reply_unref(reply);

    if (settings) {
        g_settings_set_int(settings, "content-color-video", mode);
        g_settings_sync();
    }

    return retval;
}

int
set_feature_sharpness_hidl(GBinderClient* client,
                           const int mode,
                           GSettings *settings)
{
    gint status = 0, retval = 0;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;
    GBinderReader reader;
    GBinderRemoteReply* reply;

    // setFeatureSwitch
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, SHARPNESS);
    gbinder_writer_append_int32(&writer, mode);
    reply = gbinder_client_transact_sync_reply(client, SET_FEATURE_SWITCH, req, &status);

    gbinder_remote_reply_init_reader(reply, &reader);
    gbinder_reader_read_int32(&reader, &status);
    if (status == 0) {
        gbinder_reader_read_int32(&reader, &retval);
        if (retval != 0) {
            g_debug("setFeatureSwitch sharpness failed, PQ returned the value %d", retval);
        }
    } else {
        retval = status;
        g_debug("Failed to call setFeatureSwitch sharpness, transaction failed with status %d", status);
    }

    gbinder_local_request_unref(req);
    gbinder_remote_reply_unref(reply);

    if (settings) {
        g_settings_set_int(settings, "sharpness", mode);
        g_settings_sync();
    }

    return retval;
}

int
set_feature_dynamic_contrast_hidl(GBinderClient* client,
                                  const int mode,
                                  GSettings *settings)
{
    gint status = 0, retval = 0;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;
    GBinderReader reader;
    GBinderRemoteReply* reply;

    // setFeatureSwitch
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, DYNAMIC_CONTRAST);
    gbinder_writer_append_int32(&writer, mode);
    reply = gbinder_client_transact_sync_reply(client, SET_FEATURE_SWITCH, req, &status);

    gbinder_remote_reply_init_reader(reply, &reader);
    gbinder_reader_read_int32(&reader, &status);
    if (status == 0) {
        gbinder_reader_read_int32(&reader, &retval);
        if (retval != 0) {
            g_debug("setFeatureSwitch dynamic contrast failed, PQ returned the value %d", retval);
        }
    } else {
        retval = status;
        g_debug("Failed to call setFeatureSwitch dynamic contrast, transaction failed with status %d", status);
    }

    gbinder_local_request_unref(req);
    gbinder_remote_reply_unref(reply);

    if (settings) {
        g_settings_set_int(settings, "dynamic-contrast", mode);
        g_settings_sync();
    }

    return retval;
}

int
set_feature_dynamic_sharpness_hidl(GBinderClient* client,
                                   const int mode,
                                   GSettings *settings)
{
    gint status = 0, retval = 0;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;
    GBinderReader reader;
    GBinderRemoteReply* reply;

    // setFeatureSwitch
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, DYNAMIC_SHARPNESS);
    gbinder_writer_append_int32(&writer, mode);
    reply = gbinder_client_transact_sync_reply(client, SET_FEATURE_SWITCH, req, &status);

    gbinder_remote_reply_init_reader(reply, &reader);
    gbinder_reader_read_int32(&reader, &status);
    if (status == 0) {
        gbinder_reader_read_int32(&reader, &retval);
        if (retval != 0) {
            g_debug("setFeatureSwitch dynamic sharpness failed, PQ returned the value %d", retval);
        }
    } else {
        retval = status;
        g_debug("Failed to call setFeatureSwitch dynamic sharpness, transaction failed with status %d", status);
    }

    gbinder_local_request_unref(req);
    gbinder_remote_reply_unref(reply);

    if (settings) {
        g_settings_set_int(settings, "dynamic-sharpness", mode);
        g_settings_sync();
    }

    return retval;
}

int
set_feature_display_ccorr_hidl(GBinderClient* client,
                               const int mode,
                               GSettings *settings)
{
    gint status = 0, retval = 0;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;
    GBinderReader reader;
    GBinderRemoteReply* reply;

    // setFeatureSwitch
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, DISPLAY_CCORR);
    gbinder_writer_append_int32(&writer, mode);
    reply = gbinder_client_transact_sync_reply(client, SET_FEATURE_SWITCH, req, &status);

    gbinder_remote_reply_init_reader(reply, &reader);
    gbinder_reader_read_int32(&reader, &status);
    if (status == 0) {
        gbinder_reader_read_int32(&reader, &retval);
        if (retval != 0) {
            g_debug("setFeatureSwitch display ccorr failed, PQ returned the value %d", retval);
        }
    } else {
        retval = status;
        g_debug("Failed to call setFeatureSwitch display ccorr , transaction failed with status %d", status);
    }

    gbinder_local_request_unref(req);
    gbinder_remote_reply_unref(reply);

    if (settings) {
        g_settings_set_int(settings, "display-ccorr", mode);
        g_settings_sync();
    }

    return retval;
}

int
set_feature_display_gamma_hidl(GBinderClient* client,
                               const int mode,
                               GSettings *settings)
{
    gint status = 0, retval = 0;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;
    GBinderReader reader;
    GBinderRemoteReply* reply;

    // setFeatureSwitch
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, DISPLAY_GAMMA);
    gbinder_writer_append_int32(&writer, mode);
    reply = gbinder_client_transact_sync_reply(client, SET_FEATURE_SWITCH, req, &status);

    gbinder_remote_reply_init_reader(reply, &reader);
    gbinder_reader_read_int32(&reader, &status);
    if (status == 0) {
        gbinder_reader_read_int32(&reader, &retval);
        if (retval != 0) {
            g_debug("setFeatureSwitch display gamma failed, PQ returned the value %d", retval);
        }
    } else {
        retval = status;
        g_debug("Failed to call setFeatureSwitch display gamma, transaction failed with status %d", status);
    }

    gbinder_local_request_unref(req);
    gbinder_remote_reply_unref(reply);

    if (settings) {
        g_settings_set_int(settings, "display-gamma", mode);
        g_settings_sync();
    }

    return retval;
}

int
set_feature_display_over_drive_hidl(GBinderClient* client,
                                    const int mode,
                                    GSettings *settings)
{
    gint status = 0, retval = 0;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;
    GBinderReader reader;
    GBinderRemoteReply* reply;

    // setFeatureSwitch
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, DISPLAY_OVER_DRIVE);
    gbinder_writer_append_int32(&writer, mode);
    reply = gbinder_client_transact_sync_reply(client, SET_FEATURE_SWITCH, req, &status);

    gbinder_remote_reply_init_reader(reply, &reader);
    gbinder_reader_read_int32(&reader, &status);
    if (status == 0) {
        gbinder_reader_read_int32(&reader, &retval);
        if (retval != 0) {
            g_debug("setFeatureSwitch display over drive failed, PQ returned the value %d", retval);
        }
    } else {
        retval = status;
        g_debug("Failed to call setFeatureSwitch display over drive, transaction failed with status %d", status);
    }

    gbinder_local_request_unref(req);
    gbinder_remote_reply_unref(reply);

    if (settings) {
        g_settings_set_int(settings, "display-over-drive", mode);
        g_settings_sync();
    }

    return retval;
}

int
set_feature_iso_adaptive_sharpness_hidl(GBinderClient* client,
                                        const int mode,
                                        GSettings *settings)
{
    gint status = 0, retval = 0;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;
    GBinderReader reader;
    GBinderRemoteReply* reply;

    // setFeatureSwitch
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, ISO_ADAPTIVE_SHARPNESS);
    gbinder_writer_append_int32(&writer, mode);
    reply = gbinder_client_transact_sync_reply(client, SET_FEATURE_SWITCH, req, &status);

    gbinder_remote_reply_init_reader(reply, &reader);
    gbinder_reader_read_int32(&reader, &status);
    if (status == 0) {
        gbinder_reader_read_int32(&reader, &retval);
        if (retval != 0) {
            g_debug("setFeatureSwitch iso adaptive sharpness failed, PQ returned the value %d", retval);
        }
    } else {
        retval = status;
        g_debug("Failed to call setFeatureSwitch iso adaptive sharpness, transaction failed with status %d", status);
    }

    gbinder_local_request_unref(req);
    gbinder_remote_reply_unref(reply);

    if (settings) {
        g_settings_set_int(settings, "iso-adaptive-sharpness", mode);
        g_settings_sync();
    }

    return retval;
}

int
set_feature_ultra_resolution_hidl(GBinderClient* client,
                                  const int mode,
                                  GSettings *settings)
{
    gint status = 0, retval = 0;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;
    GBinderReader reader;
    GBinderRemoteReply* reply;

    // setFeatureSwitch
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, ULTRA_RESOLUTION);
    gbinder_writer_append_int32(&writer, mode);
    reply = gbinder_client_transact_sync_reply(client, SET_FEATURE_SWITCH, req, &status);

    gbinder_remote_reply_init_reader(reply, &reader);
    gbinder_reader_read_int32(&reader, &status);
    if (status == 0) {
        gbinder_reader_read_int32(&reader, &retval);
        if (retval != 0) {
            g_debug("setFeatureSwitch ultra resolution failed, PQ returned the value %d", retval);
        }
    } else {
        retval = status;
        g_debug("Failed to call setFeatureSwitch ultra resolution, transaction failed with status %d", status);
    }

    gbinder_local_request_unref(req);
    gbinder_remote_reply_unref(reply);

    if (settings) {
        g_settings_set_int(settings, "ultra-resolution", mode);
        g_settings_sync();
    }

    return retval;
}

int
set_feature_video_hdr_hidl(GBinderClient* client,
                           const int mode,
                           GSettings *settings)
{
    gint status = 0, retval = 0;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;
    GBinderReader reader;
    GBinderRemoteReply* reply;

    // setFeatureSwitch
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, VIDEO_HDR);
    gbinder_writer_append_int32(&writer, mode);
    reply = gbinder_client_transact_sync_reply(client, SET_FEATURE_SWITCH, req, &status);

    gbinder_remote_reply_init_reader(reply, &reader);
    gbinder_reader_read_int32(&reader, &status);
    if (status == 0) {
        gbinder_reader_read_int32(&reader, &retval);
        if (retval != 0) {
            g_debug("setFeatureSwitch video hdr failed, PQ returned the value %d", retval);
        }
    } else {
        retval = status;
        g_debug("Failed to call setFeatureSwitch video hdr, transaction failed with status %d", status);
    }

    gbinder_local_request_unref(req);
    gbinder_remote_reply_unref(reply);

    if (settings) {
        g_settings_set_int(settings, "video-hdr", mode);
        g_settings_sync();
    }

    return retval;
}

int
get_feature_switch(GBinderClient* client,
                   const int feature)
{
    gint status = 0, retval = 0, value;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;
    GBinderReader reader;
    GBinderRemoteReply* reply;

    // getFeatureSwitch
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, feature);
    reply = gbinder_client_transact_sync_reply(client, GET_FEATURE_SWITCH, req, &status);

    gbinder_remote_reply_init_reader(reply, &reader);
    gbinder_reader_read_int32(&reader, &status);
    if (status == 0) {
        gbinder_reader_read_int32(&reader, &retval);
        if (retval != 0) {
            g_debug("getFeatureSwitch failed, PQ returned the value %d", retval);
            retval = -1;
        } else {
            gbinder_reader_read_int32(&reader, &value);
            retval = value;
        }
    } else {
        retval = status;
        g_debug("Failed to call getFeatureSwitch, transaction failed with status %d", status);
    }

    gbinder_local_request_unref(req);
    gbinder_remote_reply_unref(reply);

    return retval;
}

int
enable_blue_light_hidl(GBinderClient* client,
                       const int enable,
                       const int step,
                       GSettings *settings)
{
    gint status = 0, retval = 0;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;
    GBinderReader reader;
    GBinderRemoteReply* reply;

    // enableBlueLight
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_bool(&writer, enable);
    gbinder_writer_append_int32(&writer, step);
    reply = gbinder_client_transact_sync_reply(client, ENABLE_BLUE_LIGHT, req, &status);

    gbinder_remote_reply_init_reader(reply, &reader);
    gbinder_reader_read_int32(&reader, &status);
    if (status == 0) {
        gbinder_reader_read_int32(&reader, &retval);
        if (retval != 0) {
            g_debug("enableBlueLight failed, PQ returned the value %d", retval);
        }
    } else {
        retval = status;
        g_debug("Failed to call enableBlueLight, transaction failed with status %d", status);
    }

    gbinder_local_request_unref(req);

    if (settings) {
        g_settings_set_int(settings, "blue-light", enable);
        g_settings_sync();
    }

    return retval;
}

int
get_blue_light_enabled_hidl(GBinderClient* client)
{
    gint status = 0, retval = 0;
    gboolean is_enabled = FALSE;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;
    GBinderReader reader;
    GBinderRemoteReply* reply;

    // getBlueLightEnabled
    gbinder_local_request_init_writer(req, &writer);
    reply = gbinder_client_transact_sync_reply(client, GET_BLUE_LIGHT_ENABLED, req, &status);

    gbinder_remote_reply_init_reader(reply, &reader);
    gbinder_reader_read_int32(&reader, &status);
    if (status == 0) {
        gbinder_reader_read_int32(&reader, &retval);
        if (retval != 0) {
            g_debug("getBlueLightEnabled failed, PQ returned the value %d", retval);
            retval = -1;
        } else {
            gbinder_reader_read_bool(&reader, &is_enabled);
            retval = 1 ? is_enabled : 0;
        }
    } else {
        retval = status;
        g_debug("Failed to call getBlueLightEnabled, transaction failed with status %d", status);
    }

    gbinder_local_request_unref(req);
    gbinder_remote_reply_unref(reply);

    return retval;
}

int
set_blue_light_strength_hidl(GBinderClient* client,
                             const int strength,
                             const int step,
                             GSettings *settings)
{
    gint status = 0, retval = 0;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;
    GBinderReader reader;
    GBinderRemoteReply* reply;

    // setBlueLightStrength
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, strength);
    gbinder_writer_append_int32(&writer, step);
    reply = gbinder_client_transact_sync_reply(client, SET_BLUE_LIGHT_STRENGTH, req, &status);

    gbinder_remote_reply_init_reader(reply, &reader);
    gbinder_reader_read_int32(&reader, &status);
    if (status == 0) {
        gbinder_reader_read_int32(&reader, &retval);
        if (retval != 0) {
            g_debug("setBlueLightStrength failed, PQ returned the value %d", retval);
        }
    } else {
        retval = status;
        g_debug("Failed to call setBlueLightStrength, transaction failed with status %d", status);
    }

    gbinder_local_request_unref(req);
    gbinder_remote_reply_unref(reply);

    if (settings) {
        g_settings_set_int(settings, "blue-light-strength", strength);
        g_settings_sync();
    }

    return retval;
}

int
get_blue_light_strength_hidl(GBinderClient* client)
{
    gint status = 0, retval = 0, strength = 0;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;
    GBinderReader reader;
    GBinderRemoteReply* reply;

    // getBlueLightStrength
    gbinder_local_request_init_writer(req, &writer);
    reply = gbinder_client_transact_sync_reply(client, GET_BLUE_LIGHT_STRENGTH, req, &status);

    gbinder_remote_reply_init_reader(reply, &reader);
    gbinder_reader_read_int32(&reader, &status);
    if (status == 0) {
        gbinder_reader_read_int32(&reader, &retval);
        if (retval != 0) {
            g_debug("getBlueLightStrength failed, PQ returned the value %d", retval);
            retval = -1;
        } else {
            gbinder_reader_read_uint32(&reader, &strength);
            retval = strength;
        }
    } else {
        retval = status;
        g_debug("Failed to call getBlueLightStrength, transaction failed with status %d", status);
    }

    gbinder_local_request_unref(req);
    gbinder_remote_reply_unref(reply);

    return retval;
}

int
enable_chameleon_hidl(GBinderClient* client,
                      const int enable,
                      const int step,
                      GSettings *settings)
{
    gint status = 0, retval = 0;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;
    GBinderReader reader;
    GBinderRemoteReply* reply;

    // enableChameleon
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_bool(&writer, enable);
    gbinder_writer_append_int32(&writer, step);
    reply = gbinder_client_transact_sync_reply(client, ENABLE_CHAMELEON, req, &status);

    gbinder_remote_reply_init_reader(reply, &reader);
    gbinder_reader_read_int32(&reader, &status);
    if (status == 0) {
        gbinder_reader_read_int32(&reader, &retval);
        if (retval != 0) {
            g_debug("enableChameleon failed, PQ returned the value %d", retval);
        }
    } else {
        retval = status;
        g_debug("Failed to call enableChameleon, transaction failed with status %d", status);
    }

    gbinder_local_request_unref(req);
    gbinder_remote_reply_unref(reply);

    if (settings) {
        g_settings_set_int(settings, "chameleon", enable);
        g_settings_sync();
    }

    return retval;
}

int
get_chameleon_enabled_hidl(GBinderClient* client)
{
    gint status = 0, retval = 0;
    gboolean is_enabled = FALSE;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;
    GBinderReader reader;
    GBinderRemoteReply* reply;

    // getChameleonEnabled
    gbinder_local_request_init_writer(req, &writer);
    reply = gbinder_client_transact_sync_reply(client, GET_CHAMELEON_ENABLED, req, &status);

    gbinder_remote_reply_init_reader(reply, &reader);
    gbinder_reader_read_int32(&reader, &status);
    if (status == 0) {
        gbinder_reader_read_int32(&reader, &retval);
        if (retval != 0) {
            g_debug("getChameleonEnabled failed, PQ returned the value %d", retval);
            retval = -1;
        } else {
            gbinder_reader_read_bool(&reader, &is_enabled);
            retval = 1 ? is_enabled : 0;
        }
    } else {
        retval = status;
        g_debug("Failed to call getChameleonEnabled, transaction failed with status %d", status);
    }

    gbinder_local_request_unref(req);
    gbinder_remote_reply_unref(reply);

    return retval;
}

int
set_chameleon_strength_hidl(GBinderClient* client,
                            const int strength,
                            const int step,
                            GSettings *settings)
{
    gint status = 0, retval = 0;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;
    GBinderReader reader;
    GBinderRemoteReply* reply;

    // setChameleonStrength
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, strength);
    gbinder_writer_append_int32(&writer, step);
    reply = gbinder_client_transact_sync_reply(client, SET_CHAMELEON_STRENGTH, req, &status);

    gbinder_remote_reply_init_reader(reply, &reader);
    gbinder_reader_read_int32(&reader, &status);
    if (status == 0) {
        gbinder_reader_read_int32(&reader, &retval);
        if (retval != 0) {
            g_debug("setChameleonStrength failed, PQ returned the value %d", retval);
        }
    } else {
        retval = status;
        g_debug("Failed to call setChameleonStrength, transaction failed with status %d", status);
    }

    gbinder_local_request_unref(req);
    gbinder_remote_reply_unref(reply);

    if (settings) {
        g_settings_set_int(settings, "chameleon-strength", strength);
        g_settings_sync();
    }

    return retval;
}

int
get_chameleon_strength_hidl(GBinderClient* client)
{
    gint status = 0, retval = 0, strength = 0;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;
    GBinderReader reader;
    GBinderRemoteReply* reply;

    // getChameleonStrength
    gbinder_local_request_init_writer(req, &writer);
    reply = gbinder_client_transact_sync_reply(client, GET_CHAMELEON_STRENGTH, req, &status);

    gbinder_remote_reply_init_reader(reply, &reader);
    gbinder_reader_read_int32(&reader, &status);
    if (status == 0) {
        gbinder_reader_read_int32(&reader, &retval);
        if (retval != 0) {
            g_debug("getBlueLightStrength failed, PQ returned the value %d", retval);
            retval = -1;
        } else {
            gbinder_reader_read_int32(&reader, &strength);
            retval = strength;
        }
    } else {
        retval = status;
        g_debug("Failed to call getBlueLightStrength, transaction failed with status %d", status);
    }

    gbinder_local_request_unref(req);
    gbinder_remote_reply_unref(reply);

    return retval;
}

int
set_tuning_field_hidl(GBinderClient* client,
                      const int pq_module,
                      const int field,
                      const int value)
{
    gint status = 0, retval = 0;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;
    GBinderReader reader;
    GBinderRemoteReply* reply;

    // setTuningField
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, pq_module);
    gbinder_writer_append_int32(&writer, field);
    gbinder_writer_append_int32(&writer, value);
    reply = gbinder_client_transact_sync_reply(client, SET_TUNING_FIELD, req, &status);

    gbinder_remote_reply_init_reader(reply, &reader);
    gbinder_reader_read_int32(&reader, &status);
    if (status == 0) {
        gbinder_reader_read_int32(&reader, &retval);
        if (retval != 0) {
            g_debug("setTuningField failed, PQ returned the value %d", retval);
            retval = -1;
        }
    } else {
        retval = status;
        g_debug("Failed to call setTuningField, transaction failed with status %d", status);
    }

    gbinder_local_request_unref(req);
    gbinder_remote_reply_unref(reply);

    return retval;
}

int
get_tuning_field_hidl(GBinderClient* client,
                      const int pq_module,
                      const int field)
{
    gint status = 0, retval = 0, value = 0;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;
    GBinderReader reader;
    GBinderRemoteReply* reply;

    // getTuningField
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, pq_module);
    gbinder_writer_append_int32(&writer, field);
    reply = gbinder_client_transact_sync_reply(client, GET_TUNING_FIELD, req, &status);

    gbinder_remote_reply_init_reader(reply, &reader);
    gbinder_reader_read_int32(&reader, &status);
    if (status == 0) {
        gbinder_reader_read_int32(&reader, &retval);
        if (retval != 0) {
            g_debug("getTuningField failed, PQ returned the value %d", retval);
            retval = -1;
        } else {
            gbinder_reader_read_int32(&reader, &value);
            retval = value;
        }
    } else {
        retval = status;
        g_debug("Failed to call getTuningField, transaction failed with status %d", status);
    }

    gbinder_local_request_unref(req);
    gbinder_remote_reply_unref(reply);

    return retval;
}

int
set_ambient_light_ct_hidl(GBinderClient* client,
                          gdouble input_x,
                          gdouble input_y,
                          gdouble input_Y)
{
    gint status = 0, retval = 0;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;
    GBinderReader reader;
    GBinderRemoteReply* reply;

    // setAmbientLightCT
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_double(&writer, input_x);
    gbinder_writer_append_double(&writer, input_y);
    gbinder_writer_append_double(&writer, input_Y);
    reply = gbinder_client_transact_sync_reply(client, SET_AMBIENT_LIGHT_CT, req, &status);

    gbinder_remote_reply_init_reader(reply, &reader);
    gbinder_reader_read_int32(&reader, &status);
    if (status == 0) {
        gbinder_reader_read_int32(&reader, &retval);
        if (retval != 0) {
            g_debug("setAmbientLightCT failed, PQ returned the value %d", retval);
            retval = -1;
        }
    } else {
        retval = status;
        g_debug("Failed to call setAmbientLightCT, transaction failed with status %d", status);
    }

    gbinder_local_request_unref(req);
    gbinder_remote_reply_unref(reply);

    return retval;
}

int
set_ambient_light_rgbw_hidl(GBinderClient* client,
                            const int input_R,
                            const int input_G,
                            const int input_B,
                            const int input_W)
{
    gint status = 0, retval = 0;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;
    GBinderReader reader;
    GBinderRemoteReply* reply;

    // setAmbientLightRGBW
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, input_R);
    gbinder_writer_append_int32(&writer, input_G);
    gbinder_writer_append_int32(&writer, input_B);
    gbinder_writer_append_int32(&writer, input_W);
    reply = gbinder_client_transact_sync_reply(client, SET_AMBIENT_LIGHT_RGBW, req, &status);

    gbinder_remote_reply_init_reader(reply, &reader);
    gbinder_reader_read_int32(&reader, &status);
    if (status == 0) {
        gbinder_reader_read_int32(&reader, &retval);
        if (retval != 0) {
            g_debug("setAmbientLightRGBW failed, PQ returned the value %d", retval);
            retval = -1;
        }
    } else {
        retval = status;
        g_debug("Failed to call setAmbientLightRGBW, transaction failed with status %d", status);
    }

    gbinder_local_request_unref(req);
    gbinder_remote_reply_unref(reply);

    return retval;
}

int
set_gamma_index_hidl(GBinderClient* client,
                     const int index,
                     const int step,
                     GSettings *settings)
{
    gint status = 0, retval = 0;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;
    GBinderReader reader;
    GBinderRemoteReply* reply;

    // setGammaIndex
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_bool(&writer, index);
    gbinder_writer_append_int32(&writer, step);
    reply = gbinder_client_transact_sync_reply(client, SET_GAMMA_INDEX, req, &status);

    gbinder_remote_reply_init_reader(reply, &reader);
    gbinder_reader_read_int32(&reader, &status);
    if (status == 0) {
        gbinder_reader_read_int32(&reader, &retval);
        if (retval != 0) {
            g_debug("setGammaIndex failed, PQ returned the value %d", retval);
        }
    } else {
        retval = status;
        g_debug("Failed to call setGammaIndex, transaction failed with status %d", status);
    }

    gbinder_local_request_unref(req);
    gbinder_remote_reply_unref(reply);

    if (settings) {
        g_settings_set_int(settings, "gamma-index", index);
        g_settings_sync();
    }

    return retval;
}

int
get_gamma_index_hidl(GBinderClient* client)
{
    gint status = 0, retval = 0, index = 0;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;
    GBinderReader reader;
    GBinderRemoteReply* reply;

    // getGammaIndex
    gbinder_local_request_init_writer(req, &writer);
    reply = gbinder_client_transact_sync_reply(client, GET_GAMMA_INDEX, req, &status);

    gbinder_remote_reply_init_reader(reply, &reader);
    gbinder_reader_read_int32(&reader, &status);
    if (status == 0) {
        gbinder_reader_read_int32(&reader, &retval);
        if (retval != 0) {
            g_debug("getGammaIndex failed, PQ returned the value %d", retval);
            retval = -1;
        } else {
            gbinder_reader_read_int32(&reader, &index);
            retval = index;
        }
    } else {
        retval = status;
        g_debug("Failed to call getGammaIndex, transaction failed with status %d", status);
    }

    gbinder_local_request_unref(req);
    gbinder_remote_reply_unref(reply);

    return retval;
}

int
set_external_panel_nits_hidl(GBinderClient* client,
                             const int nits)
{
    gint status = 0, retval = 0;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;
    GBinderReader reader;
    GBinderRemoteReply* reply;

    // setExternalPanelNits
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, nits);
    reply = gbinder_client_transact_sync_reply(client, SET_EXTERNAL_PANEL_NITS, req, &status);

    gbinder_remote_reply_init_reader(reply, &reader);
    gbinder_reader_read_int32(&reader, &status);
    if (status == 0) {
        gbinder_reader_read_int32(&reader, &retval);
        if (retval != 0) {
            g_debug("setExternalPanelNits failed, PQ returned the value %d", retval);
        }
    } else {
        retval = status;
        g_debug("Failed to call setExternalPanelNits, transaction failed with status %d", status);
    }

    gbinder_local_request_unref(req);
    gbinder_remote_reply_unref(reply);

    return retval;
}

int
get_external_panel_nits_hidl(GBinderClient* client)
{
    gint status = 0, retval = 0, nits = 0;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;
    GBinderReader reader;
    GBinderRemoteReply* reply;

    // getExternalPanelNits
    gbinder_local_request_init_writer(req, &writer);
    reply = gbinder_client_transact_sync_reply(client, GET_EXTERNAL_PANEL_NITS, req, &status);

    gbinder_remote_reply_init_reader(reply, &reader);
    gbinder_reader_read_int32(&reader, &status);
    if (status == 0) {
        gbinder_reader_read_int32(&reader, &retval);
        if (retval != 0) {
            g_debug("getExternalPanelNits failed, PQ returned the value %d", retval);
            retval = -1;
        } else {
            gbinder_reader_read_int32(&reader, &nits);
            retval = nits;
        }
    } else {
        retval = status;
        g_debug("Failed to call getExternalPanelNits, transaction failed with status %d", status);
    }

    gbinder_local_request_unref(req);
    gbinder_remote_reply_unref(reply);

    return retval;
}

int
set_rgb_gain_hidl(GBinderClient* client,
                  const int r_gain,
                  const int g_gain,
                  const int b_gain,
                  const int step)
{
    gint status = 0, retval = 0;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;
    GBinderReader reader;
    GBinderRemoteReply* reply;

    // setRGBGain
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, r_gain);
    gbinder_writer_append_int32(&writer, g_gain);
    gbinder_writer_append_int32(&writer, b_gain);
    gbinder_writer_append_int32(&writer, step);
    reply = gbinder_client_transact_sync_reply(client, SET_RGB_GAIN, req, &status);

    gbinder_remote_reply_init_reader(reply, &reader);
    gbinder_reader_read_int32(&reader, &status);
    if (status == 0) {
        gbinder_reader_read_int32(&reader, &retval);
        if (retval != 0) {
            g_debug("setRGBGain failed, PQ returned the value %d", retval);
            retval = -1;
        }
    } else {
        retval = status;
        g_debug("Failed to call setRGBGain, transaction failed with status %d", status);
    }

    gbinder_local_request_unref(req);
    gbinder_remote_reply_unref(reply);

    return retval;
}

int
set_global_pq_switch_hidl(GBinderClient* client,
                          const int mode,
                          GSettings *settings)
{
    gint status = 0, retval = 0;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;
    GBinderReader reader;
    GBinderRemoteReply* reply;

    // setGlobalPQSwitch
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, mode);
    reply = gbinder_client_transact_sync_reply(client, SET_GLOBAL_PQ_SWITCH, req, &status);

    gbinder_remote_reply_init_reader(reply, &reader);
    gbinder_reader_read_int32(&reader, &status);
    if (status == 0) {
        gbinder_reader_read_int32(&reader, &retval);
        if (retval != 0) {
            g_debug("setGlobalPQSwitch failed, PQ returned the value %d", retval);
        }
    } else {
        retval = status;
        g_debug("Failed to call setGlobalPQSwitch, transaction failed with status %d", status);
    }

    gbinder_local_request_unref(req);
    gbinder_remote_reply_unref(reply);

    if (settings) {
        g_settings_set_int(settings, "global-pq-switch", mode);
        g_settings_sync();
    }

    return retval;
}

int
get_global_pq_switch_hidl(GBinderClient* client)
{
    gint status = 0, retval = 0, switch_value = 0;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;
    GBinderReader reader;
    GBinderRemoteReply* reply;

    // getGlobalPQSwitch
    gbinder_local_request_init_writer(req, &writer);
    reply = gbinder_client_transact_sync_reply(client, GET_GLOBAL_PQ_SWITCH, req, &status);

    gbinder_remote_reply_init_reader(reply, &reader);
    gbinder_reader_read_int32(&reader, &status);
    if (status == 0) {
        gbinder_reader_read_int32(&reader, &retval);
        if (retval != 0) {
            g_debug("getGlobalPQSwitch failed, PQ returned the value %d", retval);
            retval = -1;
        } else {
            gbinder_reader_read_int32(&reader, &switch_value);
            retval = switch_value;
        }
    } else {
        retval = status;
        g_debug("Failed to call getGlobalPQSwitch, transaction failed with status %d", status);
    }

    gbinder_local_request_unref(req);
    gbinder_remote_reply_unref(reply);

    return retval;
}

int
set_global_pq_strength_hidl(GBinderClient* client,
                            const int strength,
                            GSettings *settings)
{
    gint status = 0, retval = 0;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;
    GBinderReader reader;
    GBinderRemoteReply* reply;

    // setGlobalPQStrength
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, strength);
    reply = gbinder_client_transact_sync_reply(client, SET_GLOBAL_PQ_STRENGTH, req, &status);

    gbinder_remote_reply_init_reader(reply, &reader);
    gbinder_reader_read_int32(&reader, &status);
    if (status == 0) {
        gbinder_reader_read_int32(&reader, &retval);
        if (retval != 0) {
            g_debug("setGlobalPQStrength failed, PQ returned the value %d", retval);
        }
    } else {
        retval = status;
        g_debug("Failed to call setGlobalPQStrength, transaction failed with status %d", status);
    }

    gbinder_local_request_unref(req);
    gbinder_remote_reply_unref(reply);

    if (settings) {
        g_settings_set_int(settings, "global-pq-strength", strength);
        g_settings_sync();
    }

    return retval;
}

int
get_global_pq_strength_hidl(GBinderClient* client)
{
    gint status = 0, retval = 0, strength = 0;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;
    GBinderReader reader;
    GBinderRemoteReply* reply;

    // getGlobalPQStrength
    gbinder_local_request_init_writer(req, &writer);
    reply = gbinder_client_transact_sync_reply(client, GET_GLOBAL_PQ_STRENGTH, req, &status);

    gbinder_remote_reply_init_reader(reply, &reader);
    gbinder_reader_read_int32(&reader, &status);
    if (status == 0) {
        gbinder_reader_read_int32(&reader, &retval);
        if (retval != 0) {
            g_debug("getGlobalPQStrength failed, PQ returned the value %d", retval);
            retval = -1;
        } else {
            gbinder_reader_read_int32(&reader, &strength);
            retval = strength;
        }
    } else {
        retval = status;
        g_debug("Failed to call getGlobalPQStrength, transaction failed with status %d", status);
    }

    gbinder_local_request_unref(req);
    gbinder_remote_reply_unref(reply);

    return retval;
}

int
set_global_pq_stable_status_hidl(GBinderClient* client,
                                 const int stable)
{
    gint status = 0, retval = 0;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;
    GBinderReader reader;
    GBinderRemoteReply* reply;

    // setGlobalPQStableStatus
    gbinder_local_request_init_writer(req, &writer);
    gbinder_writer_append_int32(&writer, stable);
    reply = gbinder_client_transact_sync_reply(client, SET_GLOBAL_PQ_STABLE_STATUS, req, &status);

    gbinder_remote_reply_init_reader(reply, &reader);
    gbinder_reader_read_int32(&reader, &status);
    if (status == 0) {
        gbinder_reader_read_int32(&reader, &retval);
        if (retval != 0) {
            g_debug("setGlobalPQStableStatus failed, PQ returned the value %d", retval);
        }
    } else {
        retval = status;
        g_debug("Failed to call setGlobalPQStableStatus, transaction failed with status %d", status);
    }

    gbinder_local_request_unref(req);
    gbinder_remote_reply_unref(reply);

    return retval;
}

int
get_global_pq_stable_status_hidl(GBinderClient* client)
{
    gint status = 0, retval = 0, stable = 0;
    GBinderLocalRequest* req = gbinder_client_new_request(client);
    GBinderWriter writer;
    GBinderReader reader;
    GBinderRemoteReply* reply;

    // getGlobalPQStableStatus
    gbinder_local_request_init_writer(req, &writer);
    reply = gbinder_client_transact_sync_reply(client, GET_GLOBAL_PQ_STABLE_STATUS, req, &status);

    gbinder_remote_reply_init_reader(reply, &reader);
    gbinder_reader_read_int32(&reader, &status);
    if (status == 0) {
        gbinder_reader_read_int32(&reader, &retval);
        if (retval != 0) {
            g_debug("getGlobalPQStableStatus failed, PQ returned the value %d", retval);
            retval = -1;
        } else {
            gbinder_reader_read_int32(&reader, &stable);
            retval = stable;
        }
    } else {
        retval = status;
        g_debug("Failed to call getGlobalPQStableStatus, transaction failed with status %d", status);
    }

    gbinder_local_request_unref(req);
    gbinder_remote_reply_unref(reply);

    return retval;
}

PQContext *
init_pq_hidl(void)
{
    PQContext* ctx = malloc(sizeof(PQContext));
    if (!ctx) return NULL;

    ctx->sm = NULL;
    ctx->remote = NULL;
    ctx->client = NULL;

    ctx->sm = gbinder_servicemanager_new("/dev/hwbinder");
    if (!ctx->sm) {
        free(ctx);
        return NULL;
    }

    ctx->remote = gbinder_servicemanager_get_service_sync(ctx->sm,
        "vendor.mediatek.hardware.pq@2.0::IPictureQuality/default", NULL);
    if (!ctx->remote) {
        gbinder_servicemanager_unref(ctx->sm);
        free(ctx);
        return NULL;
    }

    ctx->client = gbinder_client_new(ctx->remote,
        "vendor.mediatek.hardware.pq@2.0::IPictureQuality");
    if (!ctx->client) {
        gbinder_remote_object_unref(ctx->remote);
        gbinder_servicemanager_unref(ctx->sm);
        free(ctx);
        return NULL;
    }

    return ctx;
}

void
cleanup_pq_hidl(PQContext* ctx)
{
    if (!ctx)
        return;
    if (ctx->client)
        gbinder_client_unref(ctx->client);
    if (ctx->remote)
        gbinder_remote_object_unref(ctx->remote);
    if (ctx->sm)
        gbinder_servicemanager_unref(ctx->sm);
    free(ctx);
}

int
run_pq_hidl(const int func,
            const int mode)
{
    int retval = 0;

    GBinderServiceManager* sm = gbinder_servicemanager_new("/dev/hwbinder");
    if (!sm)
        return 1;

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

    GSettingsSchemaSource *schema_source = g_settings_schema_source_get_default();
    GSettingsSchema *schema = g_settings_schema_source_lookup(schema_source, "io.furios.pq", TRUE);
    GSettings *settings = schema ? g_settings_new("io.furios.pq") : NULL;

    if (func == 1)
        set_pq_mode_hidl(client, mode, 5, settings);
    else if (func == 2)
        enable_blue_light_hidl(client, mode, 5, settings);
    else if (func == 3)
        set_blue_light_strength_hidl(client, mode, 5, settings);
    else if (func == 4)
        enable_chameleon_hidl(client, mode, 5, settings);
    else if (func == 5)
        set_chameleon_strength_hidl(client, mode, 5, settings);
    else if (func == 6)
        set_gamma_index_hidl(client, mode, 5, settings);
    else if (func == 7)
        set_feature_display_color_hidl(client, mode, settings);
    else if (func == 8)
        set_feature_content_color_hidl(client, mode, settings);
    else if (func == 9)
        set_feature_content_color_video_hidl(client, mode, settings);
    else if (func == 10)
        set_feature_sharpness_hidl(client, mode, settings);
    else if (func == 11)
        set_feature_dynamic_contrast_hidl(client, mode, settings);
    else if (func == 12)
        set_feature_dynamic_sharpness_hidl(client, mode, settings);
    else if (func == 13)
        set_feature_display_ccorr_hidl(client, mode, settings);
    else if (func == 14)
        set_feature_display_gamma_hidl(client, mode, settings);
    else if (func == 15)
        set_feature_display_over_drive_hidl(client, mode, settings);
    else if (func == 16)
        set_feature_iso_adaptive_sharpness_hidl(client, mode, settings);
    else if (func == 17)
        set_feature_ultra_resolution_hidl(client, mode, settings);
    else if (func == 18)
        set_feature_video_hdr_hidl(client, mode, settings);
    else if (func == 19)
        set_global_pq_switch_hidl(client, mode, settings);
    else if (func == 20)
        set_global_pq_strength_hidl(client, mode, settings);
    else
        retval = 1;

cleanup:
    gbinder_client_unref(client);
    if (settings)
        g_object_unref(settings);
    if (!remote)
        gbinder_remote_object_unref(remote);
    return retval;
}
