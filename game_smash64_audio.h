#pragma once

#include "foreign_controller.h"

#include <stdint.h>

/* Owner-cache SSB64 clip loader and selected-character cue mapper. */
int game_smash64_audio_prepare_root(const char *root);
int game_smash64_audio_prepare_character_root(const char *root,
                                              const char *controller_id);
int game_smash64_audio_set_enabled(int enabled);
void game_smash64_audio_play_events(const ForeignAudioEvents *events,
                                    uint64_t frame);
