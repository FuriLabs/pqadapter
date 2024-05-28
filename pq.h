/*
 * Copyright (C) 2024 Bardia Moshiri
 * SPDX-License-Identifier: GPL-3.0+
 * Author: Bardia Moshiri <fakeshell@bardia.tech>
 */

#ifndef PQ_H
#define PQ_H

#include <gbinder.h>
#include <stdint.h>

enum PQFunctions : int32_t {
    SET_PQ_MODE = 1,
    ENABLE_BLUE_LIGHT,
    SET_BLUE_LIGHT_STRENGTH,
    ENABLE_CHAMELEON,
    SET_CHAMELEON_STRENGTH,
    SET_GAMMA_INDEX,
    SET_FEATURE_DISPLAY_COLOR,
    SET_FEATURE_CONTENT_COLOR,
    SET_FEATURE_CONTENT_COLOR_VIDEO,
    SET_FEATURE_SHARPNESS,
    SET_FEATURE_DYNAMIC_CONTRAST,
    SET_FEATURE_DYNAMIC_SHARPNESS,
    SET_FEATURE_DISPLAY_CCORR,
    SET_FEATURE_DISPLAY_GAMMA,
    SET_FEATURE_DISPLAY_OVER_DRIVE,
    SET_FEATURE_ISO_ADAPTIVE_SHARPNESS,
    SET_FEATURE_ULTRA_RESOLUTION,
    SET_FEATURE_VIDEO_HDR,
    PQ_FUNCTION_MAX
};

int init_pq_hidl(const int func, const int mode);

#endif // PQ_H
