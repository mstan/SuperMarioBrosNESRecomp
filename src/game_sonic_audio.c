/*
 * Sonic 3 & Knuckles sound for the Sonic player replacement.
 *
 * Sonic's sound effects are played by S3K's own sound driver, running on an
 * emulated Genesis sound board (mods/s3k/audio): the Z80 SMPS driver and its
 * data are decompressed from the owner ROM, and it programs a YM2612 (ymfm)
 * and an SN76489 exactly as on the console. A gameplay sound is a Play_SFX
 * request with S3K's own sound id; the board's mono output is streamed into
 * the runner's mod mixer alongside SMB1's NES audio. No sound is rendered
 * ahead of time and nothing is embedded in the executable.
 */
#include "game_sonic_audio.h"

#include "mod_audio.h"
#include "mods/s3k/audio/s3k_sound_board.h"
#include "mods/s3k/sonic_controller.h"

#include <SDL.h>

#include <stdio.h>

static S3KSoundBoard *s_board;
static int s_trace;

static void stream_render(void *user, int16_t *samples, int frame_count)
{
    (void)user;
    s3k_sound_board_render(s_board, samples, frame_count);
}

static void stream_reset(void *user)
{
    (void)user;
    /* A save-state load discards delivery state: SndDrvInit again. */
    s3k_sound_board_reset(s_board);
}

void game_sonic_audio_shutdown(void)
{
    nes_mod_audio_set_stream(NULL, NULL, NULL);
    s3k_sound_board_destroy(s_board);
    s_board = NULL;
}

int game_sonic_audio_prepare(const uint8_t *owner_rom, size_t size)
{
    game_sonic_audio_shutdown();
    if (!owner_rom) return 0;
    s_board = s3k_sound_board_create(owner_rom, size, NES_MOD_AUDIO_SAMPLE_RATE);
    if (!s_board) return 0;
    nes_mod_audio_set_stream(stream_render, stream_reset, NULL);
    {
        const char *trace = SDL_getenv("NESRECOMP_SONIC_AUDIO_TRACE");
        s_trace = trace && *trace && *trace != '0';
    }
    fprintf(stderr, "[S3KAudio] S3&K sound driver running on the emulated "
                    "Genesis sound board (Z80 + YM2612 + SN76489)\n");
    return 1;
}

void game_sonic_audio_play_events(const ForeignAudioEvents *events,
                                  uint64_t frame)
{
    if (!events || !s_board) return;
    for (uint32_t i = 0; i < events->count &&
                         i < FOREIGN_AUDIO_EVENT_CAPACITY; ++i) {
        const uint32_t cue = events->events[i].cue;
        if ((cue & 0xFFFFFF00u) != S3K_SONIC_AUDIO_TAG) continue;
        s3k_sound_board_play_sfx(s_board, (uint8_t)cue);
        if (s_trace)
            fprintf(stderr, "[S3KAudio] frame=%llu Play_SFX $%02X\n",
                    (unsigned long long)frame, (unsigned)(uint8_t)cue);
    }
}
