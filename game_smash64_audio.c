/*
 * Selected Smash 64 fighter audio asset adapter.
 *
 * No sample bytes are linked into the executable. When the Smash64 player mod
 * is enabled, this loader looks for ordinary WAV files beneath the ignored
 * assets_ssb64/audio quarantine, converts them to the runner's mono S16/44100
 * contract, and registers copied PCM with the generic mod overlay mixer.
 */
#include "game_smash64_audio.h"

#include "mod_audio.h"
#include "mods/smash64/characters/captain_falcon.h"
#include "mods/smash64/characters/pikachu.h"

#include <SDL.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Smash64AudioAsset {
    uint32_t cue;
    const char *name;
    const char *filename;
    int gain_percent;
    NESModAudioClip clip;
} Smash64AudioAsset;

static Smash64AudioAsset s_falcon_assets[] = {
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

static Smash64AudioAsset s_pikachu_assets[] = {
    { PIKACHU_AUDIO_SPECIAL_N, "special-n", "pikachu_special_n.wav", 88, 0 },
    { PIKACHU_AUDIO_SPECIAL_HI, "special-hi", "pikachu_special_hi.wav", 88, 0 },
    { PIKACHU_AUDIO_SPECIAL_LW, "special-lw", "pikachu_special_lw.wav", 88, 0 },
    { PIKACHU_AUDIO_LIGHT_S, "light-s", "pikachu_light_swing_s.wav", 54, 0 },
    { PIKACHU_AUDIO_LIGHT_M, "light-m", "pikachu_light_swing_m.wav", 56, 0 },
    { PIKACHU_AUDIO_LIGHT_L, "light-l", "pikachu_light_swing_l.wav", 58, 0 },
    { PIKACHU_AUDIO_ELECTRIC_1, "electric-1", "pikachu_electric_1.wav", 58, 0 },
    { PIKACHU_AUDIO_ELECTRIC_2, "electric-2", "pikachu_electric_2.wav", 58, 0 },
    { PIKACHU_AUDIO_ELECTRIC_3, "electric-3", "pikachu_electric_3.wav", 58, 0 },
    { PIKACHU_AUDIO_ELECTRIC_5, "electric-5", "pikachu_electric_5.wav", 58, 0 },
    { PIKACHU_AUDIO_QUICK_ATTACK_START, "quick-attack-start",
      "pikachu_quick_attack_start.wav", 60, 0 },
    { PIKACHU_AUDIO_THUNDER, "thunder", "pikachu_thunder.wav", 64, 0 },
    { PIKACHU_AUDIO_ELECTRIC_LOOP, "electric-loop",
      "pikachu_electric_loop.wav", 52, 0 },
};

static Smash64AudioAsset *s_assets = s_falcon_assets;
static size_t s_asset_count = sizeof(s_falcon_assets) / sizeof(s_falcon_assets[0]);
static const char *s_character_name = "Captain Falcon";

static int s_enabled;
static int s_prepared;
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
    int written = snprintf(path, sizeof(path), "%s%saudio/%s", root,
                           (len && (root[len - 1] == '/' ||
                                    root[len - 1] == '\\')) ? "" : "/",
                           filename);
    if (written < 0 || (size_t)written >= sizeof(path))
        return NES_MOD_AUDIO_CLIP_INVALID;
    return load_wav(path);
}

static NESModAudioClip load_asset(const char *filename)
{
    const char *configured = SDL_getenv("NESRECOMP_SSB64_ASSETS");
    NESModAudioClip clip;
    char *base;
    char root[1024];

    if (configured && *configured)
        return try_root(configured, filename);
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

static void clear_assets(void)
{
    size_t i;
    s_enabled = 0;
    for (i = 0; i < s_asset_count; ++i) {
        if (s_assets[i].clip)
            nes_mod_audio_unregister(s_assets[i].clip);
        s_assets[i].clip = NES_MOD_AUDIO_CLIP_INVALID;
    }
    s_prepared = 0;
}

int game_smash64_audio_prepare_character_root(const char *root,
                                              const char *controller_id)
{
    size_t i;
    clear_assets();
    if (controller_id && strcmp(controller_id, SMASH64_PIKACHU_ID) == 0) {
        s_assets = s_pikachu_assets;
        s_asset_count = sizeof(s_pikachu_assets) / sizeof(s_pikachu_assets[0]);
        s_character_name = "Pikachu";
    } else if (!controller_id ||
               strcmp(controller_id, SMASH64_CAPTAIN_FALCON_ID) == 0) {
        s_assets = s_falcon_assets;
        s_asset_count = sizeof(s_falcon_assets) / sizeof(s_falcon_assets[0]);
        s_character_name = "Captain Falcon";
    } else {
        return 0;
    }
    if (!root || !*root) return 0;
    for (i = 0; i < s_asset_count; ++i) {
        s_assets[i].clip = try_root(root, s_assets[i].filename);
        if (!s_assets[i].clip) {
            clear_assets();
            return 0;
        }
    }
    s_prepared = 1;
    return 1;
}

int game_smash64_audio_prepare_root(const char *root)
{
    return game_smash64_audio_prepare_character_root(
        root, SMASH64_CAPTAIN_FALCON_ID);
}

int game_smash64_audio_set_enabled(int enabled)
{
    size_t i;
    int loaded = 0;
    const int expected = (int)s_asset_count;

    s_enabled = 0;
    if (!enabled) {
        clear_assets();
        return 1;
    }

    s_trace = 0;
    {
        const char *trace = SDL_getenv("NESRECOMP_SMASH64_AUDIO_TRACE");
        s_trace = trace && *trace && *trace != '0';
    }
    if (s_prepared) {
        loaded = expected;
    } else {
        for (i = 0; i < s_asset_count; ++i) {
            s_assets[i].clip = load_asset(s_assets[i].filename);
            if (s_assets[i].clip) loaded++;
        }
    }
    if (loaded == expected) {
        s_enabled = 1;
        fprintf(stderr, "[Smash64Audio] loaded %d/%u owner-cache %s clips\n",
                loaded, (unsigned)s_asset_count, s_character_name);
        return 1;
    }
    fprintf(stderr,
            "[Smash64Audio] required %s clips unavailable (%d/%d); "
            "player replacement stays OFF\n", s_character_name,
            loaded, expected);
    clear_assets();
    return 0;
}

void game_smash64_audio_play_events(const ForeignAudioEvents *events,
                                    uint64_t frame)
{
    uint32_t i;
    size_t a;
    if (!s_enabled || !events) return;

    for (i = 0; i < events->count && i < FOREIGN_AUDIO_EVENT_CAPACITY; ++i) {
        for (a = 0; a < s_asset_count; ++a) {
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

void game_smash64_audio_set_persistent_cue_active(uint32_t cue, int active)
{
    size_t a;
    for (a = 0; a < s_asset_count; ++a) {
        Smash64AudioAsset *asset = &s_assets[a];
        if (asset->cue != cue) continue;
        /* Teardown is useful even after a failed activation; playback only
         * begins when every selected-character asset has been verified. */
        if (!active || !s_enabled)
            nes_mod_audio_stop_loop(asset->clip);
        else
            (void)nes_mod_audio_play_loop(asset->clip, asset->gain_percent);
        return;
    }
}
