/*
 * Owner-ROM-backed Zelda II sound-effect renderer.
 *
 * Zelda II queues the flying blade with sound-effects type 4 bit $08
 * (prg0 $9872-$9876). Bank 6's handler at $9334 initializes pulse 1, then
 * $934C-$939E advances its 59-frame volume/duty and pitch sequence. The clip
 * below reads those tables from the verified owner ROM and replays the same
 * driver recipe through the host overlay mixer.
 */
#include "game_link_audio.h"

#include "mod_audio.h"
#include "foreign_controller.h"
#include "mods/zelda2/link_controller.h"

#include <SDL.h>

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ZELDA2_HEADERED_BYTES 262160
#define ZELDA2_HEADERLESS_BYTES 262144
#define ZELDA2_FLYING_BLADE_TABLE_OFFSET 0x19104L
#define ZELDA2_FLYING_BLADE_TABLE_BYTES 0xEFL
#define ZELDA2_ENVELOPE_OFFSET 0x00
#define ZELDA2_NOTE_HIGH_OFFSET 0x8B
#define ZELDA2_NOTE_LOW_OFFSET 0x8C
#define ZELDA2_NOTE_LOW 0x54
#define ZELDA2_NOTE_HIGH 0x62
#define ZELDA2_FLYING_BLADE_FRAMES 0x3B
#define SAMPLES_PER_NTSC_FRAME (NES_MOD_AUDIO_SAMPLE_RATE / 60)
#define NES_CPU_HZ 1789773.0

static NESModAudioClip s_clips[LINK_AUDIO_CUE_COUNT];
static int s_ready;
static int s_trace;

static double pulse_sample(double *phase, int timer, double duty,
                           double volume)
{
    double frequency;
    if (timer < 8 || volume <= 0.0) return 0.0;
    frequency = NES_CPU_HZ / (16.0 * (double)(timer + 1));
    *phase += frequency / NES_MOD_AUDIO_SAMPLE_RATE;
    *phase -= floor(*phase);
    return (*phase < duty ? 1.0 : -1.0) * volume;
}

static int note_timer(const uint8_t *data, unsigned note)
{
    return data[ZELDA2_NOTE_LOW_OFFSET + note] |
           ((data[ZELDA2_NOTE_HIGH_OFFSET + note] & 7) << 8);
}

static int pulse1_negate_sweep(int timer)
{
    int target = timer - (timer >> 2) - 1;
    return target >= 8 ? target : 0;
}

static NESModAudioClip build_flying_blade_clip(const uint8_t *data)
{
    const uint32_t count =
        ZELDA2_FLYING_BLADE_FRAMES * SAMPLES_PER_NTSC_FRAME;
    int16_t *pcm = (int16_t *)malloc((size_t)count * sizeof(*pcm));
    uint32_t pos = 0;
    double phase = 0.0;
    NESModAudioClip clip;
    if (!pcm) return NES_MOD_AUDIO_CLIP_INVALID;

    for (int remaining = ZELDA2_FLYING_BLADE_FRAMES;
         remaining > 0; --remaining) {
        unsigned sequence = (unsigned)remaining >> 2;
        uint8_t control = data[ZELDA2_ENVELOPE_OFFSET + sequence];
        unsigned note = (sequence & 1u) ? ZELDA2_NOTE_LOW
                                        : ZELDA2_NOTE_HIGH;
        int timer = note_timer(data, note);
        double duty = ((control >> 6) & 3) == 1 ? 0.25 : 0.50;
        double volume = (double)(control & 15) / 15.0;

        /* $4001=$8A is pulse 1's enabled, period-zero, negate-by-four
         * sweep. Zelda II rewrites the base timer each video frame; model the
         * two half-frame clocks within that interval. */
        for (int i = 0; i < SAMPLES_PER_NTSC_FRAME; ++i) {
            double sample = pulse_sample(&phase, timer, duty, volume);
            if (sample > 1.0) sample = 1.0;
            if (sample < -1.0) sample = -1.0;
            pcm[pos++] = (int16_t)(sample * 9000.0);
            if (i == SAMPLES_PER_NTSC_FRAME / 2 - 1 ||
                i == SAMPLES_PER_NTSC_FRAME - 1)
                timer = pulse1_negate_sweep(timer);
        }
    }
    clip = nes_mod_audio_register_pcm_s16_mono(pcm, count);
    free(pcm);
    return clip;
}

void game_link_audio_shutdown(void)
{
    for (int i = 0; i < LINK_AUDIO_CUE_COUNT; ++i) {
        if (s_clips[i]) nes_mod_audio_unregister(s_clips[i]);
        s_clips[i] = NES_MOD_AUDIO_CLIP_INVALID;
    }
    s_ready = 0;
}

int game_link_audio_prepare(const char *owner_rom_path)
{
    SDL_RWops *file;
    Sint64 size;
    long header = 0;
    uint8_t data[ZELDA2_FLYING_BLADE_TABLE_BYTES];

    game_link_audio_shutdown();
    if (!owner_rom_path || !*owner_rom_path) return 0;
    file = SDL_RWFromFile(owner_rom_path, "rb");
    if (!file) return 0;
    size = SDL_RWsize(file);
    if (size == ZELDA2_HEADERED_BYTES) header = 16;
    else if (size != ZELDA2_HEADERLESS_BYTES) {
        SDL_RWclose(file);
        return 0;
    }
    if (SDL_RWseek(file, header + ZELDA2_FLYING_BLADE_TABLE_OFFSET,
                   RW_SEEK_SET) < 0 ||
        SDL_RWread(file, data, 1, sizeof(data)) != sizeof(data)) {
        SDL_RWclose(file);
        return 0;
    }
    SDL_RWclose(file);

    s_clips[LINK_AUDIO_SWORD_BEAM] = build_flying_blade_clip(data);
    if (!s_clips[LINK_AUDIO_SWORD_BEAM]) {
        game_link_audio_shutdown();
        return 0;
    }
    {
        const char *trace = SDL_getenv("NESRECOMP_LINK_AUDIO_TRACE");
        s_trace = trace && *trace && *trace != '0';
    }
    s_ready = 1;
    fprintf(stderr, "[ZeldaIIAudio] built 59-frame flying-blade cue from "
                    "owner ROM\n");
    return 1;
}

void game_link_audio_play(LinkAudioCue cue)
{
    if (!s_ready || cue < 0 || cue >= LINK_AUDIO_CUE_COUNT) return;
    if (nes_mod_audio_play(s_clips[cue], 72) && s_trace)
        fprintf(stderr, "[ZeldaIIAudio] cue=sword-beam\n");
}

void game_link_audio_play_events(const ForeignAudioEvents *events,
                                 uint64_t frame)
{
    if (!events) return;
    for (uint32_t i = 0; i < events->count &&
                         i < FOREIGN_AUDIO_EVENT_CAPACITY; ++i) {
        if (events->events[i].cue == ZELDA2_LINK_AUDIO_SWORD_BEAM) {
            int gain = 72 * events->events[i].gain_percent / 100;
            if (s_ready && nes_mod_audio_play(
                    s_clips[LINK_AUDIO_SWORD_BEAM], gain) && s_trace)
                fprintf(stderr, "[ZeldaIIAudio] frame=%llu cue=sword-beam\n",
                        (unsigned long long)frame);
        }
    }
}
