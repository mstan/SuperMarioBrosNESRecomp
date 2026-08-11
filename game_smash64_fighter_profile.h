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
    SMASH64_STATE_TRAIT_ROOT_BURST = 1u << 5,
    /* Move both axes through one <=1px DDA. Quick Attack cannot use the
     * ordinary horizontal-then-vertical L-shaped integration without cutting
     * a solid tile corner that its authored diagonal never cleared. */
    SMASH64_STATE_TRAIT_COUPLED_2D_SWEEP = 1u << 6,
    /* Suppress only the host's final injury-timer decision. Collision,
     * stomps, enemy movement and every non-injury consequence remain native. */
    SMASH64_STATE_TRAIT_INTANGIBLE = 1u << 7
} Smash64FighterStateTrait;

/* Return the maximum SMB pixels/tick for one component of a coupled burst.
 * The fighter profile owns phase/debt policy; the generic SMB adapter only
 * latches and applies the resulting direction-preserving projection. */
typedef double (*Smash64CoupledBurstPlanProducer)(unsigned state,
                                                  uint8_t parser_debt);

typedef struct Smash64FighterProfile {
    const char *controller_id;
    const char *display_name;
    /* Stable host-local identity for adapter/action save records. */
    uint32_t savestate_tag;

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

    /* NULL means no coupled-burst projection. A producer makes the
     * character-specific phase/debt decision; the adapter persists that plan
     * over saves so it can never change heading or cap mid-zip. */
    Smash64CoupledBurstPlanProducer coupled_burst_plan;

    uint32_t (*state_traits)(unsigned state);
} Smash64FighterProfile;

const Smash64FighterProfile *smash64_fighter_profile_find(
    const char *controller_id);
uint32_t smash64_fighter_profile_state_traits(
    const Smash64FighterProfile *profile, unsigned state);
double smash64_fighter_profile_coupled_burst_component_px_limit(
    const Smash64FighterProfile *profile, unsigned state,
    uint8_t parser_debt);

/* Source-authored Pikachu Thunder self-contact geometry, projected through
 * the profile scale. The host callback and tests share this strict-boundary
 * implementation. */
int smash64_pikachu_thunder_source_contact(
    double action_x, double action_y, double fighter_left,
    double fighter_right, double fighter_bottom);
