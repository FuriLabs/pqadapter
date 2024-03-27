/*
 * Copyright (C) 2024 Bardia Moshiri
 * SPDX-License-Identifier: GPL-3.0+
 * Author: Bardia Moshiri <fakeshell@bardia.tech>
 */

#include "pq.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_func_valid(int func) {
    return func >= 1 && func <= 18;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s function_id input\n"
               "id 1: setPQMode, inputs: <0: standard mode, 1: vivid mode>\n"
               "id 2: enableBlueLight, inputs: <0: disable, 1: enable>\n"
               "id 3: setBlueLightStrength, inputs: <0-1000>\n"
               "id 4: enableChameleon, inputs: <0: disable, 1: enable>\n"
               "id 5: setChameleonStrength, inputs: <0-1000>\n"
               "id 6: setGammaIndex, inputs: <0-1000>\n"
               "id 7: setFeatureDisplayColor, inputs: <mode>\n"
               "id 8: setFeatureContentColor, inputs: <mode>\n"
               "id 9: setFeatureContentColorVideo, inputs: <mode>\n"
               "id 10: setFeatureSharpness, inputs: <mode>\n"
               "id 11: setFeatureDynamicContrast, inputs: <mode>\n"
               "id 12: setFeatureDynamicSharpness, inputs: <mode>\n"
               "id 13: setFeatureDisplayCcorr, inputs: <mode>\n"
               "id 14: setFeatureDisplayGamma, inputs: <mode>\n"
               "id 15: setFeatureDisplayOverDrive, inputs: <mode>\n"
               "id 16: setFeatureIsoAdaptiveSharpness, inputs: <mode>\n"
               "id 17: setFeatureUltraResolution, inputs: <mode>\n"
               "id 18: setFeatureVideoHdr, inputs: <mode>\n", argv[0]);
        return 1;
    }

    int func = atoi(argv[1]);
    int input = atoi(argv[2]);

    if (is_func_valid(func)) {
        int ret = init_pq_hidl(func, input);

        if (ret != 0) {
           printf("None of the backends are available for PQ. Exiting.\n");
           return 1;
        } else {
           printf("Using HIDL backend\n");
        }
    } else {
        printf("Invalid function ID. Please check the usage and try again.\n");
        return 1;
    }

    return 0;
}
