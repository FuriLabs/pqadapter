/*
 * Copyright (C) 2024 Bardia Moshiri
 * SPDX-License-Identifier: GPL-3.0+
 * Author: Bardia Moshiri <fakeshell@bardia.tech>
 */

#ifndef ALSA_H
#define ALSA_H

#include <stdio.h>
#include <alsa/asoundlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Set the capture state of an ALSA mixer element.
 *
 * @param card The identifier for the sound card (e.g., "hw:0").
 * @param selem_name The name of the mixer simple element.
 * @param capture The capture state to set (0 for mute, 1 for unmute).
 * @return 0 on success, negative error code on failure.
 */
int set_capture_state(const char *card, const char *selem_name, int capture);

#ifdef __cplusplus
}
#endif

#endif // ALSA_H
