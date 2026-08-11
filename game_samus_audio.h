#pragma once

typedef enum SamusAudioCue {
    SAMUS_AUDIO_WALK,
    SAMUS_AUDIO_SCREW_ATTACK,
    SAMUS_AUDIO_MISSILE_LAUNCH,
    SAMUS_AUDIO_BOMB_EXPLODE,
    SAMUS_AUDIO_SAMUS_HIT,
    SAMUS_AUDIO_JUMP,
    SAMUS_AUDIO_ENEMY_HIT,
    SAMUS_AUDIO_WAVE_BEAM,
    SAMUS_AUDIO_BOMB_LAUNCH,
    SAMUS_AUDIO_MORPH_BALL,
    SAMUS_AUDIO_CUE_COUNT
} SamusAudioCue;

/* Builds disposable PCM from the verified owner's original APU register data.
 * No samples or Metroid register tables are linked into the executable. */
int game_samus_audio_prepare(const char *owner_rom_path);
void game_samus_audio_shutdown(void);
void game_samus_audio_play(SamusAudioCue cue);

