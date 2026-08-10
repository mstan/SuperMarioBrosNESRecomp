/*
 * Owner-ROM-backed NES Metroid sound-effect renderer.
 *
 * Metroid's effects are APU programs, not stored PCM.  At activation we read
 * their four-register channel seeds from the launcher's already verified ROM,
 * replay the documented sound-driver changes, and register temporary mono PCM
 * with the host overlay mixer.  The executable therefore contains recipes and
 * an APU waveform implementation, but no original sound table or samples.
 */
#include "game_samus_audio.h"

#include "mod_audio.h"

#include <SDL.h>

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define METROID_PRG_SIZE 0x20000L
#define METROID_SFX_DATA_OFFSET 0x3230L
#define SAMPLES_PER_NTSC_FRAME (NES_MOD_AUDIO_SAMPLE_RATE / 60)
#define NES_CPU_HZ 1789773.0

/* Offsets within SFXData.  Only offsets and driver behavior are compiled;
 * every APU register value is supplied by the owner's ROM. */
enum {
    SFX_SCREW = 17,
    SFX_MISSILE = 21,
    SFX_BOMB_EXPLODE = 25,
    SFX_WALK = 29,
    SFX_SAMUS_HIT = 37,
    SFX_JUMP = 81,
    SFX_ENEMY_HIT = 85,
    SFX_WAVE = 93,
    SFX_BOMB_LAUNCH_1 = 101,
    SFX_BOMB_LAUNCH_2 = 105,
    SFX_MORPH_BALL = 109,
    SFX_BYTES_NEEDED = 113
};

typedef enum ChannelKind { CHANNEL_PULSE, CHANNEL_TRIANGLE, CHANNEL_NOISE } ChannelKind;

typedef struct SynthState {
    ChannelKind kind;
    uint8_t reg[4];
    double phase;
    uint16_t noise;
    int pulse_channel;
} SynthState;

static NESModAudioClip s_clips[SAMUS_AUDIO_CUE_COUNT];
static int s_ready;
static int s_trace;

static const int s_gain[SAMUS_AUDIO_CUE_COUNT] = {
    24, 34, 38, 36, 38, 30, 32, 30, 32, 30
};

static const char *const s_names[SAMUS_AUDIO_CUE_COUNT] = {
    "walk", "screw-attack", "missile-launch", "bomb-explode",
    "samus-hit", "jump", "enemy-hit", "wave-beam", "bomb-launch",
    "morph-ball"
};

static double channel_sample(SynthState *s)
{
    static const double duty[4] = { 0.125, 0.25, 0.5, 0.25 };
    static const int noise_period[16] = {
        4, 8, 16, 32, 64, 96, 128, 160,
        202, 254, 380, 508, 762, 1016, 2034, 4068
    };
    int timer = s->reg[2] | ((s->reg[3] & 7) << 8);
    double volume = (double)(s->reg[0] & 15) / 15.0;

    if (s->kind == CHANNEL_PULSE) {
        double frequency;
        if (timer < 8 || volume == 0.0) return 0.0;
        frequency = NES_CPU_HZ / (16.0 * (timer + 1));
        s->phase += frequency / NES_MOD_AUDIO_SAMPLE_RATE;
        s->phase -= floor(s->phase);
        return (s->phase < duty[s->reg[0] >> 6] ? 1.0 : -1.0) * volume;
    }
    if (s->kind == CHANNEL_TRIANGLE) {
        double frequency;
        double triangle;
        if ((s->reg[0] & 0x7f) == 0) return 0.0;
        frequency = NES_CPU_HZ / (32.0 * (timer + 1));
        s->phase += frequency / NES_MOD_AUDIO_SAMPLE_RATE;
        s->phase -= floor(s->phase);
        triangle = 1.0 - 4.0 * fabs(s->phase - 0.5);
        return triangle * 0.80;
    }
    {
        double clocks = NES_CPU_HZ /
                        ((double)noise_period[s->reg[2] & 15] *
                         NES_MOD_AUDIO_SAMPLE_RATE);
        s->phase += clocks;
        while (s->phase >= 1.0) {
            unsigned tap = (s->reg[2] & 0x80) ? 6u : 1u;
            unsigned feedback = (s->noise ^ (s->noise >> tap)) & 1u;
            s->noise = (uint16_t)((s->noise >> 1) | (feedback << 14));
            s->phase -= 1.0;
        }
        return (s->noise & 1 ? -1.0 : 1.0) * volume;
    }
}

static void pulse_sweep(SynthState *s)
{
    unsigned shift = s->reg[1] & 7u;
    int timer, delta;
    if (!(s->reg[1] & 0x80) || !shift) return;
    timer = s->reg[2] | ((s->reg[3] & 7) << 8);
    delta = timer >> shift;
    if (s->reg[1] & 8)
        timer -= delta + (s->pulse_channel == 1 ? 1 : 0);
    else
        timer += delta;
    if (timer < 0) timer = 0;
    if (timer > 0x7ff) timer = 0x7ff;
    s->reg[2] = (uint8_t)timer;
    s->reg[3] = (uint8_t)((s->reg[3] & 0xf8) | (timer >> 8));
}

static void update_driver_frame(SamusAudioCue cue, int frame,
                                SynthState *a, SynthState *b,
                                const uint8_t *data)
{
    if (cue == SAMUS_AUDIO_WAVE_BEAM) {
        /* WaveBeamSFXCont alternates pitch each frame and steps $19->$13->$11
         * in eight-frame blocks before silencing the channel. */
        a->reg[2] = (frame & 1) ? data[SFX_WAVE + 2] : 0x58;
        if (frame == 8) a->reg[0] = 0x13;
        if (frame == 16) a->reg[0] = 0x11;
    } else if (cue == SAMUS_AUDIO_MISSILE_LAUNCH && frame > 0) {
        a->reg[2] = (uint8_t)(0x0a + frame);
    } else if (cue == SAMUS_AUDIO_SCREW_ATTACK && frame >= 10) {
        int p = frame - 9;
        p -= ((frame - 10) / 5) * 3;
        a->reg[2] = (uint8_t)p;
    } else if (cue == SAMUS_AUDIO_BOMB_LAUNCH && frame == 4) {
        memcpy(a->reg, data + SFX_BOMB_LAUNCH_2, 4);
    } else if (cue == SAMUS_AUDIO_MORPH_BALL && frame > 0) {
        int timer = a->reg[2] | ((a->reg[3] & 7) << 8);
        timer -= timer / 5;
        if (timer < 1) timer = 1;
        a->reg[2] = (uint8_t)timer;
        a->reg[3] = (uint8_t)((a->reg[3] & 0xf8) | (timer >> 8));
    } else if (cue == SAMUS_AUDIO_SAMUS_HIT) {
        /* The original uses RandomNumber1 each frame.  Seed the same bounded
         * period ranges deterministically from the owner's two-channel seed. */
        unsigned r = (unsigned)(data[SFX_SAMUS_HIT] + frame * 13u);
        a->reg[2] = (uint8_t)(r & 15u);
        b->reg[2] = (uint8_t)((r >> 2) & 15u);
    } else if ((cue == SAMUS_AUDIO_JUMP || cue == SAMUS_AUDIO_ENEMY_HIT) &&
               (frame & 1)) {
        pulse_sweep(a);
    }
}

static NESModAudioClip build_clip(SamusAudioCue cue, const uint8_t *data)
{
    static const uint8_t source_offset[SAMUS_AUDIO_CUE_COUNT] = {
        SFX_WALK, SFX_SCREW, SFX_MISSILE, SFX_BOMB_EXPLODE,
        SFX_SAMUS_HIT, SFX_JUMP, SFX_ENEMY_HIT, SFX_WAVE,
        SFX_BOMB_LAUNCH_1, SFX_MORPH_BALL
    };
    static const uint8_t frames[SAMUS_AUDIO_CUE_COUNT] = {
        3, 85, 24, 48, 4, 12, 8, 24, 8, 8
    };
    static const uint8_t kind[SAMUS_AUDIO_CUE_COUNT] = {
        CHANNEL_NOISE, CHANNEL_NOISE, CHANNEL_NOISE, CHANNEL_NOISE,
        CHANNEL_PULSE, CHANNEL_PULSE, CHANNEL_PULSE, CHANNEL_PULSE,
        CHANNEL_TRIANGLE, CHANNEL_TRIANGLE
    };
    uint32_t count = (uint32_t)frames[cue] * SAMPLES_PER_NTSC_FRAME;
    int16_t *pcm = (int16_t *)malloc((size_t)count * sizeof(*pcm));
    SynthState a, b;
    uint32_t pos = 0;
    int f, i;
    NESModAudioClip clip;
    if (!pcm) return NES_MOD_AUDIO_CLIP_INVALID;
    memset(&a, 0, sizeof(a));
    memset(&b, 0, sizeof(b));
    a.kind = (ChannelKind)kind[cue];
    b.kind = CHANNEL_PULSE;
    a.noise = b.noise = 1;
    a.pulse_channel = 1;
    b.pulse_channel = 2;
    memcpy(a.reg, data + source_offset[cue], 4);
    if (cue == SAMUS_AUDIO_SAMUS_HIT) memcpy(b.reg, a.reg, 4);

    for (f = 0; f < frames[cue]; ++f) {
        update_driver_frame(cue, f, &a, &b, data);
        for (i = 0; i < SAMPLES_PER_NTSC_FRAME; ++i) {
            double sample = channel_sample(&a);
            if (cue == SAMUS_AUDIO_SAMUS_HIT) sample += channel_sample(&b);
            if (sample > 1.0) sample = 1.0;
            if (sample < -1.0) sample = -1.0;
            pcm[pos++] = (int16_t)(sample * 9500.0);
        }
    }
    clip = nes_mod_audio_register_pcm_s16_mono(pcm, count);
    free(pcm);
    return clip;
}

void game_samus_audio_shutdown(void)
{
    int i;
    s_ready = 0;
    for (i = 0; i < SAMUS_AUDIO_CUE_COUNT; ++i) {
        if (s_clips[i]) nes_mod_audio_unregister(s_clips[i]);
        s_clips[i] = NES_MOD_AUDIO_CLIP_INVALID;
    }
}

int game_samus_audio_prepare(const char *owner_rom_path)
{
    SDL_RWops *file;
    Sint64 size;
    long header = 0;
    uint8_t data[SFX_BYTES_NEEDED];
    int i;
    game_samus_audio_shutdown();
    if (!owner_rom_path || !*owner_rom_path) return 0;
    file = SDL_RWFromFile(owner_rom_path, "rb");
    if (!file) return 0;
    size = SDL_RWsize(file);
    if (size == METROID_PRG_SIZE + 16) header = 16;
    else if (size != METROID_PRG_SIZE) {
        SDL_RWclose(file);
        return 0;
    }
    if (SDL_RWseek(file, header + METROID_SFX_DATA_OFFSET, RW_SEEK_SET) < 0 ||
        SDL_RWread(file, data, 1, sizeof(data)) != sizeof(data)) {
        SDL_RWclose(file);
        return 0;
    }
    SDL_RWclose(file);

    for (i = 0; i < SAMUS_AUDIO_CUE_COUNT; ++i) {
        s_clips[i] = build_clip((SamusAudioCue)i, data);
        if (!s_clips[i]) {
            game_samus_audio_shutdown();
            return 0;
        }
    }
    s_trace = 0;
    {
        const char *trace = SDL_getenv("NESRECOMP_SAMUS_AUDIO_TRACE");
        s_trace = trace && *trace && *trace != '0';
    }
    s_ready = 1;
    fprintf(stderr, "[MetroidAudio] built %d faithful APU cues from owner ROM\n",
            SAMUS_AUDIO_CUE_COUNT);
    return 1;
}

void game_samus_audio_play(SamusAudioCue cue)
{
    if (!s_ready || cue < 0 || cue >= SAMUS_AUDIO_CUE_COUNT) return;
    if (nes_mod_audio_play(s_clips[cue], s_gain[cue]) && s_trace)
        fprintf(stderr, "[MetroidAudio] cue=%s\n", s_names[cue]);
}
