#include "game_smash64_fighter_profile.h"

#include "mods/smash64/characters/captain_falcon.h"

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
    0.08,
    0x00,
    0,
    0,
    0,
    0x20,
    1,
    captain_falcon_state_traits
};

static const Smash64FighterProfile *const kProfiles[] = {
    &kCaptainFalconProfile
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

