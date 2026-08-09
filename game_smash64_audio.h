#pragma once

#include "foreign_controller.h"

#include <stdint.h>

/* Local-only SSB64 clip loader and Captain Falcon cue mapper. */
int game_smash64_audio_prepare_root(const char *root);
int game_smash64_audio_set_enabled(int enabled);
void game_smash64_audio_play_events(const ForeignAudioEvents *events,
                                    uint64_t frame);
