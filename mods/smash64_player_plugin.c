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
#include <string.h>

static void reset_smash64_player(void) {
    /* Reset callbacks run before active plugins on every launch, so
     * disabling the feature reliably restores stock SMB1. */
    game_smash64_set_mod_enabled(0, NULL);
}

#define SMASH64_PACKAGE_ID \
    "super-mario-bros.gameplay.smash64-player-replacement"
#define SMASH64_FEATURE_ID "smash64-player"

/*
 * Read back the committed dropdown value. The condition on [[plugin]] is
 * what actually selected this callback, so this is a cross-check, not the
 * selection mechanism: if the two ever disagree, the manifest and the
 * resolver have drifted apart and the log says so instead of hiding it.
 */
static void report_selected_character(const char *expected) {
    char selected[64];
    if (!nes_mod_option_value(SMASH64_PACKAGE_ID, SMASH64_FEATURE_ID,
                              "character", selected, sizeof selected)) {
        fprintf(stderr, "[Smash64] Could not read the Character option; "
                        "assuming '%s'\n", expected);
        return;
    }
    if (strcmp(selected, expected) != 0)
        fprintf(stderr,
                "[Smash64] Character option is '%s' but the '%s' plugin "
                "activated - manifest conditions and resolver disagree\n",
                selected, expected);
    else
        printf("[Smash64] Character: %s\n", selected);
}

static void activate_captain_falcon(void) {
    report_selected_character("captain-falcon");
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
