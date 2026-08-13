#include "game_smash64_fighter_profile.h"

#include "mods/smash64/characters/captain_falcon.h"
#include "mods/smash64/characters/pikachu.h"
#include "mods/zelda2/link_controller.h"
#include "mods/metroid/samus_controller.h"

#include <math.h>
#include <string.h>

static uint32_t captain_falcon_state_traits(unsigned state)
{
    switch (state) {
    case FL_WAIT:
    case FL_WALK_SLOW:
    case FL_WALK_MIDDLE:
    case FL_WALK_FAST:
    case FL_DASH:
    case FL_RUN:
    case FL_RUN_BRAKE:
    case FL_TURN:
    case FL_TURN_RUN:
    case FL_KNEEBEND:
    case FL_JUMP_F:
    case FL_JUMP_B:
    case FL_JUMP_AERIAL_F:
    case FL_JUMP_AERIAL_B:
    case FL_FALL:
    case FL_FALL_AERIAL:
    case FL_LANDING_LIGHT:
    case FL_LANDING_HEAVY:
        return SMASH64_STATE_TRAIT_STREAM_LIMIT;

    case FL_FALCON_KICK_BOUND:
        return SMASH64_STATE_TRAIT_KEEP_AIRBORNE_AT_TOP |
               SMASH64_STATE_TRAIT_CLAMP_AT_GAMEPLAY_TOP |
               SMASH64_STATE_TRAIT_ROOT_BURST;

    case FL_FALCON_DIVE_GROUND:
    case FL_FALCON_DIVE_AIR:
        return SMASH64_STATE_TRAIT_HEAD_BUMP_BARRIER |
               SMASH64_STATE_TRAIT_SUPPRESS_UPWARD_SPEED_ON_CEILING |
               SMASH64_STATE_TRAIT_ROOT_BURST;

    case FL_FALCON_KICK_GROUND:
    case FL_FALCON_KICK_GROUND_AIR:
    case FL_FALCON_KICK_LANDING:
    case FL_FALCON_KICK_AIR:
    case FL_FALCON_DIVE_CATCH:
    case FL_FALCON_DIVE_THROW:
        return SMASH64_STATE_TRAIT_ROOT_BURST;

    default:
        return SMASH64_STATE_TRAIT_NONE;
    }
}

static const Smash64FighterProfile kCaptainFalconProfile = {
    SMASH64_CAPTAIN_FALCON_ID,
    "Captain Falcon",
    0x43463634u, /* CF64 */
    0.08,
    64,
    0x00,
    0,
    0,
    0,
    0x20,
    1,
    NULL,
    captain_falcon_state_traits
};

static uint32_t pikachu_state_traits(unsigned state)
{
    uint32_t traits = state < PK_STATE_COUNT
                          ? SMASH64_STATE_TRAIT_STREAM_LIMIT
                          : SMASH64_STATE_TRAIT_NONE;
    switch (state) {
    case PK_QUICK_ATTACK_START:
    case PK_QUICK_ATTACK_GROUND_START:
        /* Source sets every hurt part intangible while the 20-frame aim
         * status is entered. The following zip uses PRESERVE_NONE, which
         * resets hit status to normal in ftMainSetStatus. */
        traits |= SMASH64_STATE_TRAIT_INTANGIBLE |
                  SMASH64_STATE_TRAIT_HEAD_BUMP_BARRIER |
                  SMASH64_STATE_TRAIT_SUPPRESS_UPWARD_SPEED_ON_CEILING |
                  SMASH64_STATE_TRAIT_ROOT_BURST |
                  SMASH64_STATE_TRAIT_COUPLED_2D_SWEEP;
        break;
    case PK_QUICK_ATTACK_ZIP1:
    case PK_QUICK_ATTACK_ZIP2:
    case PK_QUICK_ATTACK_GROUND_ZIP1:
    case PK_QUICK_ATTACK_GROUND_ZIP2:
        traits |= SMASH64_STATE_TRAIT_HEAD_BUMP_BARRIER |
                  SMASH64_STATE_TRAIT_SUPPRESS_UPWARD_SPEED_ON_CEILING |
                  SMASH64_STATE_TRAIT_ROOT_BURST |
                  SMASH64_STATE_TRAIT_COUPLED_2D_SWEEP;
        break;
    case PK_QUICK_ATTACK_WINDOW:
    case PK_QUICK_ATTACK_RECOVERY:
    case PK_QUICK_ATTACK_GROUND_WINDOW:
    case PK_QUICK_ATTACK_GROUND_RECOVERY:
        traits |= SMASH64_STATE_TRAIT_HEAD_BUMP_BARRIER |
                  SMASH64_STATE_TRAIT_SUPPRESS_UPWARD_SPEED_ON_CEILING |
                  SMASH64_STATE_TRAIT_ROOT_BURST |
                  SMASH64_STATE_TRAIT_COUPLED_2D_SWEEP;
        break;
    /* PK_FALL_SPECIAL intentionally takes the default STREAM_LIMIT only.
     * It has left the 46-frame Quick Attack end status and must not inherit a
     * root burst, coupled-DDA plan, or ceiling barrier. */
    default:
        break;
    }
    return traits;
}

/* Finite Quick Attack parser credit is character policy, not a generic SMB
 * adapter guess. These entry snapshots leave room below signed $A0 for the
 * entire phase: 5*16px ZIP1 from <$20 and 5*14.4px ZIP2 from <$6C. */
static double pikachu_coupled_burst_plan(unsigned state, uint8_t parser_debt)
{
    switch (state) {
    case PK_QUICK_ATTACK_ZIP1:
    case PK_QUICK_ATTACK_GROUND_ZIP1:
        return parser_debt < 0x20u ? 16.0 : 4.0;
    case PK_QUICK_ATTACK_ZIP2:
    case PK_QUICK_ATTACK_GROUND_ZIP2:
        return parser_debt < 0x6Cu ? 14.4 : 4.0;
    default:
        /* Start/window/recovery carry only residual motion. Keeping that
         * conservative avoids treating a non-zip state as fresh credit. */
        return 4.0;
    }
}

static const Smash64FighterProfile kPikachuProfile = {
    SMASH64_PIKACHU_ID,
    "Pikachu",
    0x504B3634u, /* PK64 */
    PIKACHU_SOURCE_SCALE,
    48,
    0x0E,
    1,
    1,
    0,
    0x10,
    0,
    pikachu_coupled_burst_plan,
    pikachu_state_traits
};

static uint32_t samus_state_traits(unsigned state)
{
    switch (state) {
    case METROID_SAMUS_STAND:
    case METROID_SAMUS_RUN:
    case METROID_SAMUS_JUMP:
    case METROID_SAMUS_SPIN:
    case METROID_SAMUS_MORPH:
    case METROID_SAMUS_ROLL:
    case METROID_SAMUS_HURT:
        return SMASH64_STATE_TRAIT_STREAM_LIMIT;
    default:
        return SMASH64_STATE_TRAIT_NONE;
    }
}

static const Smash64FighterProfile kSamusProfile = {
    METROID_SAMUS_CONTROLLER_ID,
    "Samus",
    0x534D5553u, /* SMUS */
    0.08,
    40,
    0x00,
    0,
    0,
    0,
    0x20,
    0,
    NULL,
    samus_state_traits
};

static uint32_t link_state_traits(unsigned state)
{
    switch (state) {
    case ZELDA2_LINK_STAND:
    case ZELDA2_LINK_WALK:
    case ZELDA2_LINK_CROUCH:
    case ZELDA2_LINK_JUMP:
    case ZELDA2_LINK_FALL:
    case ZELDA2_LINK_SLASH_START:
    case ZELDA2_LINK_SLASH_ACTIVE:
    case ZELDA2_LINK_SLASH_RECOVER:
    case ZELDA2_LINK_CROUCH_SLASH:
    case ZELDA2_LINK_UPSTAB:
    case ZELDA2_LINK_DOWNSTAB:
        return SMASH64_STATE_TRAIT_STREAM_LIMIT;
    default:
        return SMASH64_STATE_TRAIT_NONE;
    }
}

static const Smash64FighterProfile kLinkProfile = {
    ZELDA2_LINK_CONTROLLER_ID,
    "Link",
    0x4C494E4Bu, /* LINK */
    0.08,
    40,
    0x00,
    0,
    0,
    0,
    0x20,
    0,
    NULL,
    link_state_traits
};

static const Smash64FighterProfile *const kProfiles[] = {
    &kCaptainFalconProfile,
    &kPikachuProfile,
    &kLinkProfile,
    &kSamusProfile
};

const Smash64FighterProfile *smash64_fighter_profile_find(
    const char *controller_id)
{
    unsigned i;

    if (!controller_id || !controller_id[0]) return NULL;
    for (i = 0; i < sizeof(kProfiles) / sizeof(kProfiles[0]); ++i) {
        if (strcmp(kProfiles[i]->controller_id, controller_id) == 0)
            return kProfiles[i];
    }
    return NULL;
}

uint32_t smash64_fighter_profile_state_traits(
    const Smash64FighterProfile *profile, unsigned state)
{
    if (!profile || !profile->state_traits) return SMASH64_STATE_TRAIT_NONE;
    return profile->state_traits(state);
}

double smash64_fighter_profile_coupled_burst_component_px_limit(
    const Smash64FighterProfile *profile, unsigned state,
    uint8_t parser_debt)
{
    if (!profile || !profile->coupled_burst_plan) return 0.0;
    return profile->coupled_burst_plan(state, parser_debt);
}

int smash64_pikachu_thunder_source_contact(
    double action_x, double action_y, double fighter_left,
    double fighter_right, double fighter_bottom)
{
    /* ftPikachuSpecialLwCheckCollideThunder compares fighter TopN against
     * weapon X and weapon Y+225 with strict source thresholds 200/800.
     * Screen Y points down, hence action_y - 225*scale. */
    return fabs((fighter_left + fighter_right) * 0.5 - action_x) <
               200.0 * PIKACHU_SOURCE_SCALE &&
           fabs(fighter_bottom -
                (action_y - 225.0 * PIKACHU_SOURCE_SCALE)) <
               800.0 * PIKACHU_SOURCE_SCALE;
}
