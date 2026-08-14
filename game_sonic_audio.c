/*
 * Sonic 3 & Knuckles movement SFX adapter.
 *
 * The cue recipes below mirror the short SMPS SFX scripts in skdisasm:
 *   $62 Jump, $3C Roll, $AB Spin Dash, $B6 Dash, $43 Fire Shield Attack.
 * They are rendered to temporary host PCM at activation and mixed through the
 * mod overlay path. No original samples are embedded in the executable.
 */
#include "game_sonic_audio.h"

#include "mod_audio.h"
#include "mods/s3k/sonic_controller.h"

#include <SDL.h>

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define S3K_ROM_BYTES 4194304L
#define SAMPLES_PER_NTSC_FRAME (NES_MOD_AUDIO_SAMPLE_RATE / 60)
#define PI 3.14159265358979323846

typedef enum SonicAudioCue {
    SONIC_AUDIO_JUMP,
    SONIC_AUDIO_ROLL,
    SONIC_AUDIO_SPINDASH,
    SONIC_AUDIO_DASH,
    SONIC_AUDIO_FIRE_DASH,
    SONIC_AUDIO_CUE_COUNT
} SonicAudioCue;

static NESModAudioClip s_clips[SONIC_AUDIO_CUE_COUNT];
static int s_ready;
static int s_trace;

static const uint32_t s_cue_ids[SONIC_AUDIO_CUE_COUNT] = {
    S3K_SONIC_AUDIO_JUMP,
    S3K_SONIC_AUDIO_ROLL,
    S3K_SONIC_AUDIO_SPINDASH,
    S3K_SONIC_AUDIO_DASH,
    S3K_SONIC_AUDIO_FIRE_DASH
};

static const char *const s_names[SONIC_AUDIO_CUE_COUNT] = {
    "jump", "roll", "spindash", "dash", "fire-dash"
};

static double clamp_sample(double s)
{
    if (s > 1.0) return 1.0;
    if (s < -1.0) return -1.0;
    return s;
}

static double square(double *phase, double hz, double volume)
{
    *phase += hz / NES_MOD_AUDIO_SAMPLE_RATE;
    *phase -= floor(*phase);
    return (*phase < 0.5 ? 1.0 : -1.0) * volume;
}

static double soft_square(double *phase, double hz, double volume)
{
    *phase += hz / NES_MOD_AUDIO_SAMPLE_RATE;
    *phase -= floor(*phase);
    return tanh(sin(2.0 * PI * *phase) * 3.2) * volume;
}

static double fm_tone(double *phase, double hz, double mod_hz,
                      double mod_depth, double volume)
{
    double t = *phase;
    double mod = sin(2.0 * PI * t * mod_hz / hz) * mod_depth;
    *phase += hz / NES_MOD_AUDIO_SAMPLE_RATE;
    return sin(2.0 * PI * t + mod) * volume;
}

static double midi_note(int semitone)
{
    return 440.0 * pow(2.0, ((double)semitone - 69.0) / 12.0);
}

static double smps_note_hz(int octave, int note)
{
    return midi_note((octave + 1) * 12 + note);
}

static double psg_jump_note_hz(int octave, int note)
{
    /* The jump script is labelled nF2/nBb2, but the PSG cue's recognizable
     * game sound sits in the brighter register after the driver's octave
     * convention and modulation are accounted for. */
    return midi_note((octave + 3) * 12 + note);
}

static double noise_sample(uint32_t *noise)
{
    *noise = *noise * 1103515245u + 12345u;
    return ((*noise >> 16) & 1u) ? 1.0 : -1.0;
}

static NESModAudioClip register_clip(int16_t *pcm, uint32_t count)
{
    NESModAudioClip clip = nes_mod_audio_register_pcm_s16_mono(pcm, count);
    free(pcm);
    return clip;
}

static NESModAudioClip build_jump_clip(void)
{
    uint32_t count = 26u * SAMPLES_PER_NTSC_FRAME;
    int16_t *pcm = (int16_t *)calloc(count, sizeof(*pcm));
    double phase = 0.0;
    uint32_t pos = 0;
    if (!pcm) return NES_MOD_AUDIO_CLIP_INVALID;
    for (int f = 0; f < 26; ++f) {
        double base = f < 5 ? psg_jump_note_hz(2, 5)   /* nF2, $05 */
                            : psg_jump_note_hz(2, 10); /* nBb2, $15 */
        for (int i = 0; i < SAMPLES_PER_NTSC_FRAME; ++i) {
            double progress = f < 5 ? 0.0 : (double)(f - 5) / 21.0;
            double vibrato = f < 5 ? 0.0 :
                sin((double)(f * SAMPLES_PER_NTSC_FRAME + i) * 0.021) *
                    (28.0 + progress * 35.0);
            double bend = f < 5 ? 0.0 : -95.0 * progress;
            double env = 0.95 - (double)f / 38.0;
            double s = soft_square(&phase, base + bend + vibrato, env);
            pcm[pos++] = (int16_t)(clamp_sample(s) * 8200.0);
        }
    }
    return register_clip(pcm, count);
}

static NESModAudioClip build_roll_clip(void)
{
    uint32_t count = 122u * SAMPLES_PER_NTSC_FRAME;
    int16_t *pcm = (int16_t *)calloc(count, sizeof(*pcm));
    double phase_a = 0.0, phase_b = 0.0, phase_c = 0.0;
    uint32_t pos = 0;
    if (!pcm) return NES_MOD_AUDIO_CLIP_INVALID;
    for (int f = 0; f < 122; ++f) {
        for (int i = 0; i < SAMPLES_PER_NTSC_FRAME; ++i) {
            if (f == 0) {
                pcm[pos++] = 0;
                continue;
            }
            {
                double step = f < 38 ? 0.0 : floor((double)(f - 38) / 2.0);
                double env = 0.92 - step * 0.021;
                double hz = smps_note_hz(6, 1) +
                            sin((double)(f * SAMPLES_PER_NTSC_FRAME + i) *
                                0.0047) * 26.0;
                double s;
                if (env < 0.035) env = 0.035;
                s = fm_tone(&phase_a, hz, 36.0, 2.9, env * 0.80);
                s += fm_tone(&phase_b, hz * 0.502, 19.0, 1.4, env * 0.32);
                s += soft_square(&phase_c, hz * 0.251, env * 0.12);
                pcm[pos++] = (int16_t)(clamp_sample(s) * 7600.0);
            }
        }
    }
    return register_clip(pcm, count);
}

static NESModAudioClip build_spindash_clip(void)
{
    uint32_t count = 122u * SAMPLES_PER_NTSC_FRAME;
    int16_t *pcm = (int16_t *)calloc(count, sizeof(*pcm));
    double phase_a = 0.0, phase_b = 0.0;
    uint32_t pos = 0;
    if (!pcm) return NES_MOD_AUDIO_CLIP_INVALID;
    for (int f = 0; f < 122; ++f) {
        for (int i = 0; i < SAMPLES_PER_NTSC_FRAME; ++i) {
            double step = f < 26 ? 0.0 : floor((double)(f - 26) / 2.0);
            double env = 1.0 - step * 0.026;
            double sweep = f < 24 ? (double)f * 7.5 : 180.0;
            double hz = smps_note_hz(5, 0) + sweep;
            double s;
            if (env < 0.02) env = 0.02;
            s = fm_tone(&phase_a, hz, 41.0, 4.4, env * 0.92);
            s += soft_square(&phase_b, hz * 2.0, env * 0.18);
            pcm[pos++] = (int16_t)(clamp_sample(s) * 8200.0);
        }
    }
    return register_clip(pcm, count);
}

static NESModAudioClip build_dash_clip(void)
{
    uint32_t count = 79u * SAMPLES_PER_NTSC_FRAME;
    int16_t *pcm = (int16_t *)calloc(count, sizeof(*pcm));
    double phase_a = 0.0, phase_b = 0.0;
    uint32_t noise = 0xB6u;
    uint32_t pos = 0;
    if (!pcm) return NES_MOD_AUDIO_CLIP_INVALID;
    for (int f = 0; f < 79; ++f) {
        for (int i = 0; i < SAMPLES_PER_NTSC_FRAME; ++i) {
            double env = 1.0 - (double)f / 96.0;
            double hz = smps_note_hz(6, 4); /* nE6 */
            double s = 0.0;
            if (f < 15)
                s += fm_tone(&phase_a, hz, 63.0, 4.8, env * 0.70);
            if (f >= 6)
                s += noise_sample(&noise) * env * 0.46;
            s += soft_square(&phase_b, hz + sin((double)f * 0.23) * 24.0,
                             env * 0.18);
            pcm[pos++] = (int16_t)(clamp_sample(s) * 8200.0);
        }
    }
    return register_clip(pcm, count);
}

static NESModAudioClip build_fire_dash_clip(void)
{
    uint32_t count = 53u * SAMPLES_PER_NTSC_FRAME;
    int16_t *pcm = (int16_t *)calloc(count, sizeof(*pcm));
    double phase = 0.0;
    uint32_t noise = 0x43u;
    uint32_t pos = 0;
    if (!pcm) return NES_MOD_AUDIO_CLIP_INVALID;
    for (int f = 0; f < 53; ++f) {
        for (int i = 0; i < SAMPLES_PER_NTSC_FRAME; ++i) {
            double step = f < 21 ? 0.0 : floor((double)(f - 21) / 2.0);
            double env = 1.0 - step * 0.045;
            double flame;
            if (env < 0.03) env = 0.03;
            flame = noise_sample(&noise) * env * 0.86;
            flame += soft_square(&phase,
                                  smps_note_hz(3, 2) +
                                      sin((double)(f + i) * 0.06) * 35.0,
                                  env * 0.24);
            pcm[pos++] = (int16_t)(clamp_sample(flame) * 7600.0);
        }
    }
    return register_clip(pcm, count);
}

void game_sonic_audio_shutdown(void)
{
    s_ready = 0;
    for (int i = 0; i < SONIC_AUDIO_CUE_COUNT; ++i) {
        if (s_clips[i]) nes_mod_audio_unregister(s_clips[i]);
        s_clips[i] = NES_MOD_AUDIO_CLIP_INVALID;
    }
}

int game_sonic_audio_prepare(const char *owner_rom_path)
{
    SDL_RWops *file;
    Sint64 size;

    game_sonic_audio_shutdown();
    if (!owner_rom_path || !*owner_rom_path) return 0;
    file = SDL_RWFromFile(owner_rom_path, "rb");
    if (!file) return 0;
    size = SDL_RWsize(file);
    SDL_RWclose(file);
    if (size != S3K_ROM_BYTES) return 0;

    s_clips[SONIC_AUDIO_JUMP] = build_jump_clip();
    s_clips[SONIC_AUDIO_ROLL] = build_roll_clip();
    s_clips[SONIC_AUDIO_SPINDASH] = build_spindash_clip();
    s_clips[SONIC_AUDIO_DASH] = build_dash_clip();
    s_clips[SONIC_AUDIO_FIRE_DASH] = build_fire_dash_clip();
    for (int i = 0; i < SONIC_AUDIO_CUE_COUNT; ++i) {
        if (!s_clips[i]) {
            game_sonic_audio_shutdown();
            return 0;
        }
    }

    {
        const char *trace = SDL_getenv("NESRECOMP_SONIC_AUDIO_TRACE");
        s_trace = trace && *trace && *trace != '0';
    }
    s_ready = 1;
    fprintf(stderr, "[S3KAudio] built SMPS-timed Sonic movement cues\n");
    return 1;
}

void game_sonic_audio_play_events(const ForeignAudioEvents *events,
                                  uint64_t frame)
{
    if (!events) return;
    for (uint32_t i = 0; i < events->count &&
                         i < FOREIGN_AUDIO_EVENT_CAPACITY; ++i) {
        for (int c = 0; c < SONIC_AUDIO_CUE_COUNT; ++c) {
            if (events->events[i].cue != s_cue_ids[c]) continue;
            if (s_ready && nes_mod_audio_play(
                    s_clips[c], events->events[i].gain_percent) && s_trace)
                fprintf(stderr, "[S3KAudio] frame=%llu cue=%s\n",
                        (unsigned long long)frame, s_names[c]);
            break;
        }
    }
}
