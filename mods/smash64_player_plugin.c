/*
 * smash64_player_plugin.c — trusted-plugin registration for the Smash 64
 * player replacement package.
 *
 * The Character dropdown in the manifest selects which plugin activates via
 * when_option/when_value, so each fighter gets its own stable plugin id and
 * the roster grows without any string dispatch here. Adding a character is:
 * an [[option.choice]], a conditioned [[plugin]], a controller source file,
 * and one activation function below.
 */
#include "mod_runtime.h"

#include "game_smash64.h"
#include "smash64/characters/captain_falcon.h"

#include <stdio.h>

static void reset_smash64_player(void) {
    /* Reset callbacks run before active plugins on every launch, so
     * disabling the feature reliably restores stock SMB1. */
    game_smash64_set_mod_enabled(0, NULL);
}

static void activate_captain_falcon(void) {
    game_smash64_set_mod_enabled(1, SMASH64_CAPTAIN_FALCON_ID);
}

NES_MOD_CONSTRUCTOR(register_smash64_player_plugin) {
    /* Controllers register with the engine registry independently of the
     * mod plan; activation only selects one that is already present. */
    if (!smash64_captain_falcon_register())
        fprintf(stderr,
                "[Mods] Failed to register the Captain Falcon controller\n");

    if (!nes_mod_register_reset_callback(reset_smash64_player) ||
        !nes_mod_register_activation_plugin(
            SMASH64_CAPTAIN_FALCON_ID, activate_captain_falcon))
        fprintf(stderr,
                "[Mods] Failed to register the Smash 64 player replacement "
                "plugin\n");
}
