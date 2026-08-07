#pragma once

/*
 * Captain Falcon, as a ForeignController.
 *
 * A thin adapter: the state machine and physics live in
 * mods/smash64/ssb_ported/falcon_locomotion.c (quarantined, since that is a
 * direct port of an unlicensed decomp). This file only bridges it to the
 * engine's game-agnostic ForeignController ABI, which is why it stays
 * publishable while the port does not.
 *
 * Registered before main(); the mod package selects it by the plugin id below
 * when the Character dropdown resolves to "captain-falcon".
 */

#define SMASH64_CAPTAIN_FALCON_ID "super-mario-bros.smash64.captain-falcon"

/* State ids and their names come from the ported module -- there is exactly
 * one enum for Falcon's states and it lives with the physics that uses it.
 * Duplicating it here is how a trace ends up labelled IDLE while the fighter
 * is dashing. */
#include "../ssb_ported/falcon_locomotion.h"

/* Register with the engine's controller registry. Safe to call more than
 * once. Returns 1 on success. */
int smash64_captain_falcon_register(void);
