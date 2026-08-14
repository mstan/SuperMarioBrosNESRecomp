#pragma once

#include "foreign_controller.h"

#include <stdint.h>

int game_sonic_audio_prepare(const char *owner_rom_path);
void game_sonic_audio_shutdown(void);
void game_sonic_audio_play_events(const ForeignAudioEvents *events,
                                  uint64_t frame);
