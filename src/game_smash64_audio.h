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
/* Reconcile a controller-owned persistent cue with its host-owned action.
 * This may be called every frame and is idempotent. */
void game_smash64_audio_set_persistent_cue_active(uint32_t cue, int active);
