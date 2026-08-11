#pragma once

#define SMASH64_PIKACHU_ID "super-mario-bros.smash64.pikachu"

#include "../ssb_ported/pikachu_locomotion.h"

/* Cue ids are controller-private and deliberately outside Captain Falcon's
 * legacy 1..11 range. The SMB audio adapter selects exactly one character
 * table before activation, but disjoint ids keep traces and saves unambiguous. */
typedef enum PikachuAudioCue {
    PIKACHU_AUDIO_SPECIAL_N = 0x100,
    PIKACHU_AUDIO_SPECIAL_HI,
    PIKACHU_AUDIO_SPECIAL_LW,
    PIKACHU_AUDIO_LIGHT_S,
    PIKACHU_AUDIO_LIGHT_M,
    PIKACHU_AUDIO_LIGHT_L,
    PIKACHU_AUDIO_ELECTRIC_1,
    PIKACHU_AUDIO_ELECTRIC_2,
    PIKACHU_AUDIO_ELECTRIC_3,
    PIKACHU_AUDIO_ELECTRIC_5,
    PIKACHU_AUDIO_QUICK_ATTACK_START,
    PIKACHU_AUDIO_THUNDER,
    PIKACHU_AUDIO_LANDING,
    PIKACHU_AUDIO_DEAD_SLAM,
    PIKACHU_AUDIO_ELECTRIC_LOOP,
    PIKACHU_AUDIO_CUE_COUNT
} PikachuAudioCue;

/* Registers the generic controller and its versioned private state callbacks. */
int smash64_pikachu_register(void);
/* Controller-local event/projectile interface until the SMB host ABI consumes it. */
const PikachuMotion *smash64_pikachu_last_motion(void);
void smash64_pikachu_thunder_self_contact(void);
/* SpecialHi Start's source motion id is -1. Query the serialized pose frozen
 * on entry; succeeds only while `active_state` is the matching Start phase. */
int smash64_pikachu_quick_entry_pose(int active_state, int *entry_state,
                                     unsigned *entry_frame);
