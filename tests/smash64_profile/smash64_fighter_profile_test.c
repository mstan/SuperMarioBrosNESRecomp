#include "game_smash64_fighter_profile.h"
#include "mods/smash64/characters/captain_falcon.h"
#include "mods/zelda2/link_controller.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>

static int has_trait(const Smash64FighterProfile *profile, unsigned state,
                     uint32_t trait)
{
    return (smash64_fighter_profile_state_traits(profile, state) & trait) != 0;
}

int main(void)
{
    const Smash64FighterProfile *profile =
        smash64_fighter_profile_find(SMASH64_CAPTAIN_FALCON_ID);

    assert(profile != NULL);
    assert(smash64_fighter_profile_find(NULL) == NULL);
    assert(smash64_fighter_profile_find("missing") == NULL);
    assert(fabs(profile->units_to_smb_px - 0.08) < 0.000001);
    assert(profile->block_adder_index == 0x00);
    assert(profile->player_bbox_ctrl == 0);
    assert(profile->collision_player_size == 0);
    assert(profile->head_upper_extent == 0x20);
    assert(profile->allow_one_tile_step_down == 1);

    assert(has_trait(profile, FL_RUN, SMASH64_STATE_TRAIT_STREAM_LIMIT));
    assert(has_trait(profile, FL_FALCON_KICK_BOUND,
                     SMASH64_STATE_TRAIT_CLAMP_AT_GAMEPLAY_TOP));
    assert(has_trait(profile, FL_FALCON_KICK_BOUND,
                     SMASH64_STATE_TRAIT_KEEP_AIRBORNE_AT_TOP));
    assert(has_trait(profile, FL_FALCON_DIVE_AIR,
                     SMASH64_STATE_TRAIT_HEAD_BUMP_BARRIER));
    assert(has_trait(profile, FL_FALCON_DIVE_AIR,
                     SMASH64_STATE_TRAIT_SUPPRESS_UPWARD_SPEED_ON_CEILING));
    assert(!has_trait(profile, FL_JAB,
                      SMASH64_STATE_TRAIT_HEAD_BUMP_BARRIER));

    profile = smash64_fighter_profile_find(ZELDA2_LINK_CONTROLLER_ID);
    assert(profile != NULL);
    assert(fabs(profile->units_to_smb_px - 0.08) < 0.000001);
    assert(profile->ordinary_stream_xspeed_limit == 40);
    assert(profile->allow_one_tile_step_down == 0);
    assert(has_trait(profile, ZELDA2_LINK_WALK,
                     SMASH64_STATE_TRAIT_STREAM_LIMIT));
    assert(has_trait(profile, ZELDA2_LINK_SLASH_ACTIVE,
                     SMASH64_STATE_TRAIT_STREAM_LIMIT));
    assert(!has_trait(profile, 9999, SMASH64_STATE_TRAIT_STREAM_LIMIT));

    puts("smash64_fighter_profile_test: PASS");
    return 0;
}
