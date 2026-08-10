#pragma once

#include <stdint.h>

/*
 * Character-specific facts consumed by the SMB1 adapter.
 *
 * The host owns tiles, scrolling and native lifecycle state, but it must know
 * how a selected controller projects into that world.  Keep those facts in a
 * profile keyed by controller id instead of teaching game_smash64.c a second
 * character's private state enum.
 */

typedef enum Smash64FighterStateTrait {
    SMASH64_STATE_TRAIT_NONE = 0,
    SMASH64_STATE_TRAIT_STREAM_LIMIT = 1u << 0,
    SMASH64_STATE_TRAIT_KEEP_AIRBORNE_AT_TOP = 1u << 1,
    SMASH64_STATE_TRAIT_CLAMP_AT_GAMEPLAY_TOP = 1u << 2,
    SMASH64_STATE_TRAIT_HEAD_BUMP_BARRIER = 1u << 3,
    SMASH64_STATE_TRAIT_SUPPRESS_UPWARD_SPEED_ON_CEILING = 1u << 4,
    SMASH64_STATE_TRAIT_ROOT_BURST = 1u << 5
} Smash64FighterStateTrait;

typedef struct Smash64FighterProfile {
    const char *controller_id;
    const char *display_name;

    /* Source-space to SMB pixel conversion. */
    double units_to_smb_px;

    /* Stable native collision presentation. These deliberately do not alter
     * PlayerSize itself, which remains SMB1's health/power-up state. */
    uint8_t block_adder_index;
    uint8_t player_bbox_ctrl;
    uint8_t collision_player_size;
    uint8_t collision_crouching;
    uint8_t head_upper_extent;

    /* Falcon alone needs the controlled one-tile descent used to enter a
     * proven two-tile cavity. Small-profile fighters already fit directly. */
    uint8_t allow_one_tile_step_down;

    uint32_t (*state_traits)(unsigned state);
} Smash64FighterProfile;

const Smash64FighterProfile *smash64_fighter_profile_find(
    const char *controller_id);
uint32_t smash64_fighter_profile_state_traits(
    const Smash64FighterProfile *profile, unsigned state);

