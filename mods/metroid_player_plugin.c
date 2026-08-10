#include "mod_runtime.h"

#include "game_samus.h"
#include "game_smash64.h"
#include "metroid/samus_controller.h"

#include <stdio.h>

#define METROID_PACKAGE_ID \
    "super-mario-bros.gameplay.metroid-samus-player-replacement"
#define METROID_FEATURE_ID "metroid-samus-player"
#define METROID_OWNER_ROM_ID "metroid-us-prg0"

static void reset_metroid_player(void)
{
    game_samus_set_enabled(0, NULL);
    if (game_smash64_samus_selected())
        game_smash64_set_mod_enabled(0, NULL);
}

static void activate_samus(void)
{
    const char *owner_rom = nes_mod_external_rom_path(
        METROID_PACKAGE_ID, METROID_FEATURE_ID, METROID_OWNER_ROM_ID);
    if (!owner_rom || !*owner_rom || !game_samus_set_enabled(1, owner_rom)) {
        game_samus_set_enabled(0, NULL);
        game_smash64_set_mod_enabled(0, NULL);
        fprintf(stderr, "[Metroid] Samus player replacement stays OFF. "
                        "Recheck the selected canonical Metroid ROM.\n");
    }
}

NES_MOD_CONSTRUCTOR(register_metroid_player_plugin)
{
    if (!metroid_samus_controller_register())
        fprintf(stderr, "[Mods] Failed to register the Samus controller\n");
    if (!game_samus_register_hooks())
        fprintf(stderr, "[Mods] Failed to register Samus gameplay hooks\n");
    if (!nes_mod_register_reset_callback(reset_metroid_player) ||
        !nes_mod_register_activation_plugin(METROID_SAMUS_CONTROLLER_ID,
                                             activate_samus))
        fprintf(stderr, "[Mods] Failed to register the Metroid player mod\n");
}
