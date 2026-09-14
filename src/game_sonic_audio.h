#pragma once

#include "foreign_controller.h"

#include <stddef.h>
#include <stdint.h>

/* Start the emulated Genesis sound board on the verified S3&K image, which
 * must stay loaded until game_sonic_audio_shutdown(). */
int game_sonic_audio_prepare(const uint8_t *owner_rom, size_t size);
void game_sonic_audio_shutdown(void);
/* S3K_SONIC_AUDIO_CUE(id) events become Play_SFX(id). */
void game_sonic_audio_play_events(const ForeignAudioEvents *events,
                                  uint64_t frame);
