#pragma once

#include <stdint.h>

#include "foreign_controller.h"

typedef enum LinkAudioCue {
    LINK_AUDIO_SWORD_BEAM,
    LINK_AUDIO_CUE_COUNT
} LinkAudioCue;

int game_link_audio_prepare(const char *owner_rom_path);
void game_link_audio_shutdown(void);
void game_link_audio_play(LinkAudioCue cue);
void game_link_audio_play_events(const ForeignAudioEvents *events,
                                 uint64_t frame);
