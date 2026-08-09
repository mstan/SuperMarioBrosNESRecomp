/*
 * Captain Falcon's local-only audio asset adapter.
 *
 * No sample bytes are linked into the executable. When the Smash64 player mod
 * is enabled, this loader looks for ordinary WAV files beneath the ignored
 * assets_ssb64/audio quarantine, converts them to the runner's mono S16/44100
 * contract, and registers copied PCM with the generic mod overlay mixer.
 */
#include "game_smash64_audio.h"

#include "mod_audio.h"
#include "mods/smash64/characters/captain_falcon.h"

#include <SDL.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct FalconAudioAsset {
    FalconAudioCue cue;
    const char *name;
    const char *filename;
    int gain_percent;
    NESModAudioClip clip;
} FalconAudioAsset;

static FalconAudioAsset s_assets[] = {
    { FALCON_AUDIO_JUMP_EFFORT,   "jump-effort", "falcon_jump_effort.wav",   82, 0 },
    { FALCON_AUDIO_PUNCH_FALCON,  "falcon",      "falcon_punch_falcon.wav",  88, 0 },
    { FALCON_AUDIO_PUNCH_PUNCH,   "punch",       "falcon_punch_punch.wav",   92, 0 },
    { FALCON_AUDIO_KICK,          "kick",        "falcon_kick.wav",          90, 0 },
    { FALCON_AUDIO_PUNCH_IMPACT,  "punch-impact",
      "falcon_punch_impact_fgm.wav", 58, 0 },
    { FALCON_AUDIO_KICK_SWING,    "kick-swing",
      "falcon_kick_swing_fgm.wav", 55, 0 },
    { FALCON_AUDIO_KICK_START,    "kick-start",
      "falcon_kick_start_fgm.wav", 55, 0 },
    { FALCON_AUDIO_DIVE_LAUNCH,   "dive-launch",
      "falcon_dive_launch_fgm.wav", 55, 0 },
    { FALCON_AUDIO_DIVE_CATCH,    "dive-catch",
      "falcon_dive_catch_fgm.wav", 55, 0 },
    { FALCON_AUDIO_DIVE_EXPLODE,  "dive-explosion",
      "falcon_dive_explosion_fgm.wav", 60, 0 },
    { FALCON_AUDIO_DIVE_VOICE,    "dive-voice",
      "falcon_dive_voice.wav", 90, 0 },
};

static int s_enabled;
static int s_trace;

static NESModAudioClip load_wav(const char *path)
{
    SDL_AudioSpec source;
    SDL_AudioCVT cvt;
    Uint8 *source_data = NULL;
    Uint32 source_len = 0;
    NESModAudioClip clip = NES_MOD_AUDIO_CLIP_INVALID;

    if (!SDL_LoadWAV(path, &source, &source_data, &source_len)) return clip;
    if (source_len == 0 || source.channels == 0 ||
        SDL_BuildAudioCVT(&cvt, source.format, source.channels, source.freq,
                          AUDIO_S16SYS, 1, NES_MOD_AUDIO_SAMPLE_RATE) < 0) {
        SDL_FreeWAV(source_data);
        return clip;
    }

    cvt.len = (int)source_len;
    cvt.buf = (Uint8 *)SDL_malloc((size_t)cvt.len * (size_t)cvt.len_mult);
    if (!cvt.buf) {
        SDL_FreeWAV(source_data);
        return clip;
    }
    memcpy(cvt.buf, source_data, source_len);
    SDL_FreeWAV(source_data);
    if (SDL_ConvertAudio(&cvt) == 0 && cvt.len_cvt >= (int)sizeof(int16_t))
        clip = nes_mod_audio_register_pcm_s16_mono(
            (const int16_t *)cvt.buf,
            (uint32_t)cvt.len_cvt / (uint32_t)sizeof(int16_t));
    SDL_free(cvt.buf);
    return clip;
}

static NESModAudioClip try_root(const char *root, const char *filename)
{
    char path[1024];
    size_t len;
    if (!root || !*root) return NES_MOD_AUDIO_CLIP_INVALID;
    len = strlen(root);
    snprintf(path, sizeof(path), "%s%saudio/%s", root,
             (len && (root[len - 1] == '/' || root[len - 1] == '\\')) ? "" : "/",
             filename);
    return load_wav(path);
}

static NESModAudioClip load_asset(const char *filename)
{
    const char *configured = SDL_getenv("NESRECOMP_SSB64_ASSETS");
    NESModAudioClip clip;
    char *base;
    char root[1024];

    clip = try_root(configured, filename);
    if (clip) return clip;
    clip = try_root("assets_ssb64", filename);
    if (clip) return clip;

    base = SDL_GetBasePath();
    if (!base) return NES_MOD_AUDIO_CLIP_INVALID;
    snprintf(root, sizeof(root), "%sassets_ssb64", base);
    clip = try_root(root, filename);
    if (!clip) {
        snprintf(root, sizeof(root), "%s../../assets_ssb64", base);
        clip = try_root(root, filename);
    }
    SDL_free(base);
    return clip;
}

void game_smash64_audio_set_enabled(int enabled)
{
    size_t i;
    int loaded = 0;

    s_enabled = 0;
    for (i = 0; i < sizeof(s_assets) / sizeof(s_assets[0]); ++i) {
        if (s_assets[i].clip)
            nes_mod_audio_unregister(s_assets[i].clip);
        s_assets[i].clip = NES_MOD_AUDIO_CLIP_INVALID;
    }
    if (!enabled) return;

    s_trace = 0;
    {
        const char *trace = SDL_getenv("NESRECOMP_SMASH64_AUDIO_TRACE");
        s_trace = trace && *trace && *trace != '0';
    }
    for (i = 0; i < sizeof(s_assets) / sizeof(s_assets[0]); ++i) {
        s_assets[i].clip = load_asset(s_assets[i].filename);
        if (s_assets[i].clip) loaded++;
    }
    s_enabled = 1;
    if (loaded)
        fprintf(stderr, "[Smash64Audio] loaded %d/%u local Falcon clips\n",
                loaded, (unsigned)(sizeof(s_assets) / sizeof(s_assets[0])));
    else
        fprintf(stderr,
                "[Smash64Audio] local Falcon clips unavailable; continuing silently\n");
}

void game_smash64_audio_play_events(const ForeignAudioEvents *events,
                                    uint64_t frame)
{
    uint32_t i;
    size_t a;
    if (!s_enabled || !events) return;

    for (i = 0; i < events->count && i < FOREIGN_AUDIO_EVENT_CAPACITY; ++i) {
        for (a = 0; a < sizeof(s_assets) / sizeof(s_assets[0]); ++a) {
            int gain;
            if ((uint32_t)s_assets[a].cue != events->events[i].cue) continue;
            gain = s_assets[a].gain_percent * events->events[i].gain_percent / 100;
            if (nes_mod_audio_play(s_assets[a].clip, gain) && s_trace)
                fprintf(stderr, "[Smash64Audio] frame=%llu cue=%s\n",
                        (unsigned long long)frame, s_assets[a].name);
            break;
        }
    }
}
