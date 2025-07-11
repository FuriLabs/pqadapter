/*
 * Copyright (C) 2024 Bardia Moshiri
 * SPDX-License-Identifier: GPL-3.0+
 * Author: Bardia Moshiri <fakeshell@bardia.tech>
 */

#include "alsa.h"

int set_capture_state(const char *card, const char *selem_name, int capture) {
    snd_mixer_t *handle;
    snd_mixer_selem_id_t *sid;
    snd_mixer_elem_t *elem;
    int ret = 0;

    if ((ret = snd_mixer_open(&handle, 0)) < 0) {
        fprintf(stderr, "Failed to open mixer: %s\n", snd_strerror(ret));
        return ret;
    }

    if ((ret = snd_mixer_attach(handle, card)) < 0) {
        fprintf(stderr, "Failed to attach mixer: %s\n", snd_strerror(ret));
        snd_mixer_close(handle);
        return ret;
    }

    if ((ret = snd_mixer_selem_register(handle, NULL, NULL)) < 0) {
        fprintf(stderr, "Failed to register mixer element: %s\n", snd_strerror(ret));
        snd_mixer_close(handle);
        return ret;
    }

    if ((ret = snd_mixer_load(handle)) < 0) {
        fprintf(stderr, "Failed to load mixer element: %s\n", snd_strerror(ret));
        snd_mixer_close(handle);
        return ret;
    }

    snd_mixer_selem_id_alloca(&sid);
    snd_mixer_selem_id_set_index(sid, 0);
    snd_mixer_selem_id_set_name(sid, selem_name);

    elem = snd_mixer_find_selem(handle, sid);
    if (!elem) {
        fprintf(stderr, "Failed to find mixer element\n");
        snd_mixer_close(handle);
        return -1;
    }

    if ((ret = snd_mixer_selem_set_capture_switch_all(elem, capture)) < 0) {
        fprintf(stderr, "Failed to set capture: %s\n", snd_strerror(ret));
    }

    snd_mixer_close(handle);
    return ret;
}
