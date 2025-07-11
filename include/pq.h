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
 * Set display color demo window parameters
 *
 * @param client GBinder client instance
 * @param split_en decides color effect is in/out of demo window
 * @param start_x start position on x-axis (Range: 0x0 ~ 0xFFFE)
 * @param end_x end position on x-axis (Range: 0x1 ~ 0xFFFF)
 * @param start_y start position on y-axis (Range: 0x0 ~ 0xFFFE)
 * @param end_y end position on y-axis (Range: 0x1 ~ 0xFFFF)
 * @return 0 if setColorRegion successfully executed, error code otherwise
 */
int set_color_region_hidl(GBinderClient* client,
                          const int split_en,
                          const int start_x,
                          const int end_x,
                          const int start_y,
                          const int end_y);

/**
 * Set PQ mode via HIDL interface
 *
 * @param client GBinder client instance
 * @param mode Picture Mode (0: Standard, 1: Vivid, 2: User defined)
 * @param step Transition speed for effect change
 * @param settings GSettings instance for persisting the setting
 * @return 0 if setPQMode successfully executed, error code otherwise
 */
int set_pq_mode_hidl(GBinderClient* client,
                     const int mode,
                     const int step,
                     GSettings *settings);

/**
 * Set TDSHP tuning flag to notify MDP not to write TDSHP HW
 *
 * @param client GBinder client instance
 * @param tdshp_flag Flag set by tuning tool
 * @return 0 if setTDSHPFlag successfully executed, error code otherwise
 */
int set_tdshp_flag(GBinderClient* client,
                   const int tdshp_flag);

/**
 * Get TDSHP tuning flag that indicates current tuning status
 *
 * @param client GBinder client instance
 * @return Current TDSHP flag value, error code on failure
 */
int get_tdshp_flag(GBinderClient* client);

/**
 * Set level of specific PQ parameter
 *
 * @param client GBinder client instance
 * @param level Strength of specific PQ parameter
 * @param scenario Usage scenario (picture/video/camera)
 * @param tuning_mode Hint whether user is Gallery app or not
 * @param index PQ parameter item (e.g. brightness)
 * @param step Transition speed for PQ effect change
 * @return 0 if setPQIndex successfully executed, error code otherwise
 */
int set_pq_index_hidl(GBinderClient* client,
                      const int level,
                      const int scenario,
                      const int tuning_mode,
                      const int index,
                      const int step);

/**
 * Set scenario for changing DISP PQ parameters
 *
 * @param client GBinder client instance
 * @param scenario Usage scenario (picture/video/camera)
 * @param step Transition speed for PQ effect change
 * @return 0 if setDISPScenario successfully executed, error code otherwise
 */
int set_disp_scenario(GBinderClient* client,
                      const int scenario,
                      const int step);

/**
 * Configure display color feature
 *
 * @param client GBinder client instance
 * @param mode Feature mode value (0: off, 1: on)
 * @param settings GSettings instance for persisting the setting
 * @return 0 if setFeatureSwitch successfully executed, error code otherwise
 */
int set_feature_display_color_hidl(GBinderClient* client,
                                   const int mode,
                                   GSettings *settings);

/**
 * Configure content color feature
 *
 * @param client GBinder client instance
 * @param mode Feature mode value (0: off, 1: on)
 * @param settings GSettings instance for persisting the setting
 * @return 0 if setFeatureSwitch successfully executed, error code otherwise
 */
int set_feature_content_color_hidl(GBinderClient* client,
                                   const int mode,
                                   GSettings *settings);

/**
 * Configure video content color feature
 *
 * @param client GBinder client instance
 * @param mode Feature mode value (0: off, 1: on)
 * @param settings GSettings instance for persisting the setting
 * @return 0 if setFeatureSwitch successfully executed, error code otherwise
 */
int set_feature_content_color_video_hidl(GBinderClient* client,
                                         const int mode,
                                         GSettings *settings);

/**
 * Set display sharpness level
 *
 * @param client GBinder client instance
 * @param mode Feature mode value (0: off, 1: on)
 * @param settings GSettings instance for persisting the setting
 * @return 0 if setFeatureSwitch successfully executed, error code otherwise
 */
int set_feature_sharpness_hidl(GBinderClient* client,
                               const int mode,
                               GSettings *settings);

/**
 * Configure dynamic contrast feature
 *
 * @param client GBinder client instance
 * @param mode Feature mode value (0: off, 1: on)
 * @param settings GSettings instance for persisting the setting
 * @return 0 if setFeatureSwitch successfully executed, error code otherwise
 */
int set_feature_dynamic_contrast_hidl(GBinderClient* client,
                                      const int mode,
                                      GSettings *settings);

/**
 * Configure dynamic sharpness feature
 *
 * @param client GBinder client instance
 * @param mode Feature mode value (0: off, 1: on)
 * @param settings GSettings instance for persisting the setting
 * @return 0 if setFeatureSwitch successfully executed, error code otherwise
 */
int set_feature_dynamic_sharpness_hidl(GBinderClient* client,
                                       const int mode,
                                       GSettings *settings);

/**
 * Configure display CCORR feature
 *
 * @param client GBinder client instance
 * @param mode Feature mode value (0: off, 1: on)
 * @param settings GSettings instance for persisting the setting
 * @return 0 if setFeatureSwitch successfully executed, error code otherwise
 */
int set_feature_display_ccorr_hidl(GBinderClient* client,
                                   const int mode,
                                   GSettings *settings);

/**
 * Configure display gamma feature
 *
 * @param client GBinder client instance
 * @param mode Feature mode value (0: off, 1: on)
 * @param settings GSettings instance for persisting the setting
 * @return 0 if setFeatureSwitch successfully executed, error code otherwise
 */
int set_feature_display_gamma_hidl(GBinderClient* client,
                                   const int mode,
                                   GSettings *settings);

/**
 * Configure display overdrive feature
 *
 * @param client GBinder client instance
 * @param mode Feature mode value (0: off, 1: on)
 * @param settings GSettings instance for persisting the setting
 * @return 0 if setFeatureSwitch successfully executed, error code otherwise
 */
int set_feature_display_over_drive_hidl(GBinderClient* client,
                                        const int mode,
                                        GSettings *settings);

/**
 * Configure ISO adaptive sharpness feature
 *
 * @param client GBinder client instance
 * @param mode Feature mode value (0: off, 1: on)
 * @param settings GSettings instance for persisting the setting
 * @return 0 if setFeatureSwitch successfully executed, error code otherwise
 */
int set_feature_iso_adaptive_sharpness_hidl(GBinderClient* client,
                                            const int mode,
                                            GSettings *settings);

/**
 * Configure ultra resolution feature
 *
 * @param client GBinder client instance
 * @param mode Feature mode value (0: off, 1: on)
 * @param settings GSettings instance for persisting the setting
 * @return 0 if setFeatureSwitch successfully executed, error code otherwise
 */
int set_feature_ultra_resolution_hidl(GBinderClient* client,
                                      const int mode,
                                      GSettings *settings);

/**
 * Configure video HDR feature
 *
 * @param client GBinder client instance
 * @param mode Feature mode value (0: off, 1: on)
 * @param settings GSettings instance for persisting the setting
 * @return 0 if setFeatureSwitch successfully executed, error code otherwise
 */
int set_feature_video_hdr_hidl(GBinderClient* client,
                               const int mode,
                               GSettings *settings);

/**
 * Get status of specific PQ feature
 *
 * @param client GBinder client instance
 * @param feature PQ Feature ID to query
 * @return Feature status (0: off, 1: on), error code on failure
 */
int get_feature_switch(GBinderClient* client,
                       const int feature);

/**
 * Enable or disable blue light filter
 *
 * @param client GBinder client instance
 * @param enable 1 to enable, 0 to disable
 * @param step Transition speed for effect change
 * @param settings GSettings instance for persisting the setting
 * @return 0 if enableBlueLight successfully executed, error code otherwise
 */
int enable_blue_light_hidl(GBinderClient* client,
                           const int enable,
                           const int step,
                           GSettings *settings);

/**
 * Get blue light filter enabled status
 *
 * @param client GBinder client instance
 * @return 1 if enabled, 0 if disabled, error code on failure
 */
int get_blue_light_enabled_hidl(GBinderClient* client);

/**
 * Set blue light filter strength
 *
 * @param client GBinder client instance
 * @param strength Strength value (0-1000)
 * @param step Transition speed for effect change
 * @param settings GSettings instance for persisting the setting
 * @return 0 if setBlueLightStrength successfully executed, error code otherwise
 */
int set_blue_light_strength_hidl(GBinderClient* client,
                                 const int strength,
                                 const int step,
                                 GSettings *settings);

/**
 * Get current blue light filter strength
 *
 * @param client GBinder client instance
 * @return Current strength value, error code on failure
 */
int get_blue_light_strength_hidl(GBinderClient* client);

/**
 * Enable or disable chameleon mode
 *
 * @param client GBinder client instance
 * @param enable 1 to enable, 0 to disable
 * @param step Transition speed for effect change
 * @param settings GSettings instance for persisting the setting
 * @return 0 if enableChameleon successfully executed, error code otherwise
 */
int enable_chameleon_hidl(GBinderClient* client,
                          const int enable,
                          const int step,
                          GSettings *settings);

/**
 * Get chameleon mode enabled status
 *
 * @param client GBinder client instance
 * @return 1 if enabled, 0 if disabled, error code on failure
 */
int get_chameleon_enabled_hidl(GBinderClient* client);

/**
 * Set chameleon mode strength
 *
 * @param client GBinder client instance
 * @param strength Strength value
 * @param step Transition speed for effect change
 * @param settings GSettings instance for persisting the setting
 * @return 0 if setChameleonStrength successfully executed, error code otherwise
 */
int set_chameleon_strength_hidl(GBinderClient* client,
                                const int strength,
                                const int step,
                                GSettings *settings);

/**
 * Get current chameleon mode strength
 *
 * @param client GBinder client instance
 * @return Current strength value, error code on failure
 */
int get_chameleon_strength_hidl(GBinderClient* client);

/**
 * Set value to specific address for PQ Tuning
 *
 * @param client GBinder client instance
 * @param pq_module Base address of module
 * @param field Offset address (based on pq_module)
 * @param value Value to set at specific address
 * @return 0 if setTuningField successfully executed, error code otherwise
 */
int set_tuning_field_hidl(GBinderClient* client,
                          const int pq_module,
                          const int field,
                          const int value);

/**
 * Get value of specific address for PQ Tuning
 *
 * @param client GBinder client instance
 * @param pq_module Base address of module
 * @param field Offset address (based on pq_module)
 * @return Value at specified address, error code on failure
 */
int get_tuning_field_hidl(GBinderClient* client,
                          const int pq_module,
                          const int field);

/**
 * Set color temperature for ambient light
 *
 * @param client GBinder client instance
 * @param input_x Debounced x value of color temperature
 * @param input_y Debounced y value of color temperature
 * @param input_Y Debounced Y value of color temperature
 * @return 0 if setAmbientLightCT successfully executed, error code otherwise
 */
int set_ambient_light_ct_hidl(GBinderClient* client,
                              gdouble input_x,
                              gdouble input_y,
                              gdouble input_Y);

/**
 * Set ambient RGBW light values
 *
 * @param client GBinder client instance
 * @param input_R Undebounced R value of ambient light
 * @param input_G Undebounced G value of ambient light
 * @param input_B Undebounced B value of ambient light
 * @param input_W Undebounced W value of ambient light
 * @return 0 if setAmbientLightRGBW successfully executed, error code otherwise
 */
int set_ambient_light_rgbw_hidl(GBinderClient* client,
                                const int input_R,
                                const int input_G,
                                const int input_B,
                                const int input_W);

/**
 * Set gamma index value
 *
 * @param client GBinder client instance
 * @param index Gamma index value
 * @param step Transition speed for effect change
 * @param settings GSettings instance for persisting the setting
 * @return 0 if setGammaIndex successfully executed, error code otherwise
 */
int set_gamma_index_hidl(GBinderClient* client,
                         const int index,
                         const int step,
                         GSettings *settings);

/**
 * Get current gamma index value
 *
 * @param client GBinder client instance
 * @return Current gamma index, error code on failure
 */
int get_gamma_index_hidl(GBinderClient* client);

/**
 * Set External Panel Nits for Video HDR
 *
 * @param client GBinder client instance
 * @param nits Panel nits value for external display
 * @return 0 if setExternalPanelNits successfully executed, error code otherwise
 */
int set_external_panel_nits_hidl(GBinderClient* client,
                                 const int nits);

/**
 * Get External Panel Nits value
 *
 * @param client GBinder client instance
 * @return Current panel nits value, error code on failure
 */
int get_external_panel_nits_hidl(GBinderClient* client);

/**
 * Set RGB channel gain values
 *
 * @param client GBinder client instance
 * @param r_gain Red channel gain ratio
 * @param g_gain Green channel gain ratio
 * @param b_gain Blue channel gain ratio
 * @param step Transition speed for effect change
 * @return 0 if setRGBGain successfully executed, error code otherwise
 */
int set_rgb_gain_hidl(GBinderClient* client,
                      const int r_gain,
                      const int g_gain,
                      const int b_gain,
                      const int step);

/**
 * Configure global PQ switch that controls DC and Sharpness
 *
 * @param client GBinder client instance
 * @param mode Switch value (0: off, 1: on)
 * @param settings GSettings instance for persisting the setting
 * @return 0 if setGlobalPQSwitch successfully executed, error code otherwise
 */
int set_global_pq_switch_hidl(GBinderClient* client,
                              const int mode,
                              GSettings *settings);

/**
 * Get global PQ switch status
 *
 * @param client GBinder client instance
 * @return Current switch value, error code on failure
 */
int get_global_pq_switch_hidl(GBinderClient* client);

/**
 * Set global PQ strength for DC and Sharpness
 *
 * @param client GBinder client instance
 * @param strength Strength value
 * @param settings GSettings instance for persisting the setting
 * @return 0 if setGlobalPQStrength successfully executed, error code otherwise
 */
int set_global_pq_strength_hidl(GBinderClient* client,
                                const int strength,
                                GSettings *settings);

/**
 * Get current global PQ strength value
 *
 * @param client GBinder client instance
 * @return Current strength value, error code on failure
 */
int get_global_pq_strength_hidl(GBinderClient* client);

/**
 * Set global PQ stable status
 *
 * @param client GBinder client instance
 * @param stable Stability status value
 * @return 0 if setGlobalPQStableStatus successfully executed, error code otherwise
 */
int set_global_pq_stable_status_hidl(GBinderClient* client,
                                     const int stable);

/**
 * Get current global PQ stable status
 *
 * @param client GBinder client instance
 * @return Current stable status value, error code on failure
 */
int get_global_pq_stable_status_hidl(GBinderClient* client);

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
