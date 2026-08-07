#pragma once

/*
 * Captain Falcon's Super Smash Bros. 64 locomotion, as a ForeignController.
 *
 * Registered before main(); the mod package selects it by the plugin id
 * below when the Character dropdown resolves to "captain-falcon".
 */

#define SMASH64_CAPTAIN_FALCON_ID "super-mario-bros.smash64.captain-falcon"

/* Locomotion states. These mirror the Smash 64 action set that ftcommon owns
 * for ordinary movement; combat, shields, grabs and cliff states are out of
 * scope and must never appear here. */
typedef enum {
    FALCON_IDLE = 0,
    FALCON_WALK,
    FALCON_DASH,
    FALCON_RUN,
    FALCON_TURN,
    FALCON_JUMPSQUAT,
    FALCON_AIR,
    FALCON_LANDING,
} FalconMoveState;

/* Register with the engine's controller registry. Safe to call more than
 * once. Returns 1 on success. */
int smash64_captain_falcon_register(void);
