/*
 * Copyright (C) 2024 Bardia Moshiri
 * SPDX-License-Identifier: GPL-3.0+
 * Author: Bardia Moshiri <fakeshell@bardia.tech>
 */

#ifndef PQ_H
#define PQ_H

#include <gio/gio.h>
#include <gbinder.h>

enum PQFunctions2_0 {
    /* vendor.mediatek.hardware.pq@2.0::IPictureQuality/default */
    SET_COLOR_REGION = 1,
    GET_COLOR_REGION,
    SET_PQ_MODE,
    SET_TDSHP_FLAG,
    GET_TDSHP_FLAG,
    GET_MAPPED_COLOR_INDEX,
    GET_MAPPED_TDSHP_INDEX,
    GET_COLOR_INDEX,
    GET_TDSHP_INDEX,
    SET_PQ_INDEX,
    SET_DISP_SCENARIO,
    SET_FEATURE_SWITCH,
    GET_FEATURE_SWITCH,
    ENABLE_BLUE_LIGHT,
    GET_BLUE_LIGHT_ENABLED,
    SET_BLUE_LIGHT_STRENGTH,
    GET_BLUE_LIGHT_STRENGTH,
    ENABLE_CHAMELEON,
    GET_CHAMELEON_ENABLED,
    SET_CHAMELEON_STRENGTH,
    GET_CHAMELEON_STRENGTH,
    SET_TUNING_FIELD,
    GET_TUNING_FIELD,
    GET_ASHMEM,
    SET_AMBIENT_LIGHT_CT,
    SET_AMBIENT_LIGHT_RGBW,
    SET_GAMMA_INDEX,
    GET_GAMMA_INDEX,
    SET_EXTERNAL_PANEL_NITS,
    GET_EXTERNAL_PANEL_NITS,
    SET_COLOR_TRANSFORM,
    EXEC_IOCTL,
    SET_RGB_GAIN,
    SET_GLOBAL_PQ_SWITCH,
    GET_GLOBAL_PQ_SWITCH,
    SET_GLOBAL_PQ_STRENGTH,
    GET_GLOBAL_PQ_STRENGTH,
    GET_GLOBAL_PQ_STRENGTH_RANGE,
    GET_GLOBAL_PQ_INDEX,
    SET_GLOBAL_PQ_STABLE_STATUS,
    GET_GLOBAL_PQ_STABLE_STATUS,
    PQ_FUNCTION_MAX
};

enum PQFeatureID {
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

typedef struct {
    GBinderServiceManager* sm;
    GBinderRemoteObject* remote;
    GBinderClient* client;
} PQContext;

/**
 * Initialize PQ HIDL interface
 *
 * @return PQContext pointer on success, NULL on failure
 */
PQContext *init_pq_hidl(void);

/**
 * Cleanup PQ HIDL interface and free resources
 *
 * @param ctx PQContext to be cleaned up
 */
void cleanup_pq_hidl(PQContext* ctx);

/**
 * Set PQ mode via HIDL interface
 *
 * @param client GBinder client instance
 * @param mode PQ mode to set
 * @param settings GSettings instance for persisting the setting
 */
void set_pq_mode_hidl(GBinderClient* client,
                      const int mode,
                      GSettings *settings);

/**
 * Enable or disable blue light filter
 *
 * @param client GBinder client instance
 * @param mode 1 to enable, 0 to disable
 * @param settings GSettings instance for persisting the setting
 */
void enable_blue_light_hidl(GBinderClient* client,
                            const int mode,
                            GSettings *settings);

/**
 * Set blue light filter strength
 *
 * @param client GBinder client instance
 * @param mode Strength value (0-1000)
 * @param settings GSettings instance for persisting the setting
 */
void set_blue_light_strength_hidl(GBinderClient* client,
                                  const int mode,
                                  GSettings *settings);

/**
 * Enable or disable chameleon mode
 *
 * @param client GBinder client instance
 * @param mode 1 to enable, 0 to disable
 * @param settings GSettings instance for persisting the setting
 */
void enable_chameleon_hidl(GBinderClient* client,
                           const int mode,
                           GSettings *settings);

/**
 * Set chameleon mode strength
 *
 * @param client GBinder client instance
 * @param mode Strength value
 * @param settings GSettings instance for persisting the setting
 */
void set_chameleon_strength_hidl(GBinderClient* client,
                                 const int mode,
                                 GSettings *settings);

/**
 * Set gamma index value
 *
 * @param client GBinder client instance
 * @param mode Gamma index value
 * @param settings GSettings instance for persisting the setting
 */
void set_gamma_index_hidl(GBinderClient* client,
                          const int mode,
                          GSettings *settings);

/**
 * Configure display color feature
 *
 * @param client GBinder client instance
 * @param mode Feature mode value
 * @param settings GSettings instance for persisting the setting
 */
void set_feature_display_color_hidl(GBinderClient* client,
                                    const int mode,
                                    GSettings *settings);

/**
 * Configure content color feature
 *
 * @param client GBinder client instance
 * @param mode Feature mode value
 * @param settings GSettings instance for persisting the setting
 */
void set_feature_content_color_hidl(GBinderClient* client,
                                    const int mode,
                                    GSettings *settings);

/**
 * Configure video content color feature
 *
 * @param client GBinder client instance
 * @param mode Feature mode value
 * @param settings GSettings instance for persisting the setting
 */
void set_feature_content_color_video_hidl(GBinderClient* client,
                                          const int mode,
                                          GSettings *settings);

/**
 * Set display sharpness level
 *
 * @param client GBinder client instance
 * @param mode Sharpness value
 * @param settings GSettings instance for persisting the setting
 */
void set_feature_sharpness_hidl(GBinderClient* client,
                                const int mode,
                                GSettings *settings);

/**
 * Configure dynamic contrast feature
 *
 * @param client GBinder client instance
 * @param mode Feature mode value
 * @param settings GSettings instance for persisting the setting
 */
void set_feature_dynamic_contrast_hidl(GBinderClient* client,
                                       const int mode,
                                       GSettings *settings);

/**
 * Configure dynamic sharpness feature
 *
 * @param client GBinder client instance
 * @param mode Feature mode value
 * @param settings GSettings instance for persisting the setting
 */
void set_feature_dynamic_sharpness_hidl(GBinderClient* client,
                                        const int mode,
                                        GSettings *settings);

/**
 * Configure display CCORR feature
 *
 * @param client GBinder client instance
 * @param mode Feature mode value
 * @param settings GSettings instance for persisting the setting
 */
void set_feature_display_ccorr_hidl(GBinderClient* client,
                                    const int mode,
                                    GSettings *settings);

/**
 * Configure display gamma feature
 *
 * @param client GBinder client instance
 * @param mode Feature mode value
 * @param settings GSettings instance for persisting the setting
 */
void set_feature_display_gamma_hidl(GBinderClient* client,
                                    const int mode,
                                    GSettings *settings);

/**
 * Configure display overdrive feature
 *
 * @param client GBinder client instance
 * @param mode Feature mode value
 * @param settings GSettings instance for persisting the setting
 */
void set_feature_display_over_drive_hidl(GBinderClient* client,
                                         const int mode,
                                         GSettings *settings);

/**
 * Configure ISO adaptive sharpness feature
 *
 * @param client GBinder client instance
 * @param mode Feature mode value
 * @param settings GSettings instance for persisting the setting
 */
void set_feature_iso_adaptive_sharpness_hidl(GBinderClient* client,
                                             const int mode,
                                             GSettings *settings);

/**
 * Configure ultra resolution feature
 *
 * @param client GBinder client instance
 * @param mode Feature mode value
 * @param settings GSettings instance for persisting the setting
 */
void set_feature_ultra_resolution_hidl(GBinderClient* client,
                                       const int mode,
                                       GSettings *settings);

/**
 * Configure video HDR feature
 *
 * @param client GBinder client instance
 * @param mode Feature mode value
 * @param settings GSettings instance for persisting the setting
 */
void set_feature_video_hdr_hidl(GBinderClient* client,
                                const int mode,
                                GSettings *settings);

/**
 * Configure global PQ switch
 *
 * @param client GBinder client instance
 * @param mode Switch value (0/1)
 * @param settings GSettings instance for persisting the setting
 */
void set_global_pq_switch_hidl(GBinderClient* client,
                               const int mode,
                               GSettings *settings);

/**
 * Set global PQ strength
 *
 * @param client GBinder client instance
 * @param mode Strength value
 * @param settings GSettings instance for persisting the setting
 */
void set_global_pq_strength_hidl(GBinderClient* client,
                                 const int mode,
                                 GSettings *settings);

/**
 * Run a PQ HIDL command
 *
 * @param func Function ID from PQFunctions enum
 * @param mode Mode value for the selected function
 * @return 0 on success, 1 on failure
 */
int run_pq_hidl(const int func,
                const int mode);

#endif // PQ_H
