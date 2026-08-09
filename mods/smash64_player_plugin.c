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
#include "game_smash64_assets.h"
#include "game_smash64_audio.h"
#include "smash64/characters/captain_falcon.h"
#include "smash64_owner_assets.h"

#include <SDL.h>

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
#define SMASH64_OWNER_ROM_ID "smash-64-us-v1"

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
    const char *owner_rom;
    char cache_root[1024];
    report_selected_character("captain-falcon");
    owner_rom = nes_mod_external_rom_path(SMASH64_PACKAGE_ID,
                                          SMASH64_FEATURE_ID,
                                          SMASH64_OWNER_ROM_ID);
    if (!owner_rom || !*owner_rom ||
        !smash64_owner_assets_prepare(owner_rom, cache_root, sizeof(cache_root)) ||
        SDL_setenv("NESRECOMP_SSB64_ASSETS", cache_root, 1) != 0 ||
        !game_smash64_assets_prepare_root(cache_root) ||
        !game_smash64_audio_prepare_root(cache_root) ||
        !game_smash64_set_mod_enabled(1, SMASH64_CAPTAIN_FALCON_ID)) {
        game_smash64_set_mod_enabled(0, NULL);
        fprintf(stderr,
                "[Smash64] Captain Falcon assets could not be prepared. "
                "Recheck the selected verified Smash 64 ROM and writable "
                "user-data folder; player replacement stays OFF.\n");
    }
}

NES_MOD_CONSTRUCTOR(register_smash64_player_plugin) {
    /* Controllers register with the engine registry independently of the
     * mod plan; activation only selects one that is already present. */
    if (!smash64_captain_falcon_register())
        fprintf(stderr,
                "[Mods] Failed to register the Captain Falcon controller\n");

    /* The trusted 6502 function-entry hook that takes over SMB1's horizontal
     * velocity integrator. Registered DISABLED, so registration alone cannot
     * change behaviour; activation enables it. */
    if (!game_smash64_register_hooks())
        fprintf(stderr,
                "[Mods] Failed to register the SMB1 ImposeFriction hook\n");

    if (!nes_mod_register_reset_callback(reset_smash64_player) ||
        !nes_mod_register_activation_plugin(
            SMASH64_CAPTAIN_FALCON_ID, activate_captain_falcon))
        fprintf(stderr,
                "[Mods] Failed to register the Smash 64 player replacement "
                "plugin\n");
}
