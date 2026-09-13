#pragma once

#include <stdint.h>

/*
 * PikachuMainMotion's ThunderHitColor material script.  ``normal_gameplay``
 * prevents a stale controller special state from tinting SMB-owned death,
 * water, or scripted presentation.  The arguments are deliberately status
 * predicates so this source-exact material rule stays independent of the
 * controller ABI.
 */
static inline uint32_t game_smash64_pikachu_thunder_color_overlay(
    int normal_gameplay, int thunder_self_hit, int thunder_end,
    unsigned frame)
{
    if (!normal_gameplay)
        return 0u;
    if (thunder_self_hit) {
        switch (frame % 3u) {
        case 0u: return 0x5A0000FFu; /* SetColor1(0, 0, 255, 90) */
        case 1u: return 0x64FFFFFFu; /* SetColor1(255, 255, 255, 100) */
        default: return 0u;           /* explicit material clear */
        }
    }
    if (thunder_end) {
        /* The End script's Goto repeats this four-frame sequence for all
         * 38 status frames, rather than playing it only once on entry. */
        switch (frame % 4u) {
        case 0u: return 0x50FFFFFFu; /* white, alpha 80 */
        case 1u: return 0x50000000u; /* black, alpha 80 */
        default: return 0u;           /* two explicit clear frames */
        }
    }
    return 0u;
}

/* ftPikachu SpecialHi's Start and both zip motions run at source speed 0.
 * Its End motion restarts at local frame 0 after each zip. The bridge
 * publishes its End-local counter only for WINDOW/RECOVERY; Recovery can
 * continue at frame 9 after Window rejects a second point. Keeping this seam
 * boolean avoids borrowing the prior full-action clock. */
static inline float game_smash64_pikachu_quick_animation_frame(
    int static_source_motion, unsigned phase_frame)
{
    return static_source_motion ? 0.0f : (float)phase_frame;
}

/* wpPikachuThunderJoltGroundAddAnim advances at half NES cadence and resets
 * before the 7.5 source-frame boundary. The serialized action owner supplies
 * the bounded 0..14 host tick clock. */
static inline float game_smash64_pikachu_jolt_source_frame(
    unsigned surface_anim_age)
{
    return 0.5f * (float)(surface_anim_age % 15u);
}
