#include "mod_runtime.h"

#include "game_link.h"
#include "game_smash64.h"
#include "zelda2/link_controller.h"

#include <stdio.h>

#define ZELDA2_PACKAGE_ID \
    "super-mario-bros.gameplay.zelda2-link-player-replacement"
#define ZELDA2_FEATURE_ID "zelda2-link-player"
#define ZELDA2_OWNER_ROM_ID "zelda2-us"

static void reset_zelda2_player(void)
{
    game_link_set_enabled(0, NULL);
    if (game_smash64_link_selected())
        game_smash64_set_mod_enabled(0, NULL);
}

static void activate_link(void)
{
    const char *owner_rom = nes_mod_external_rom_path(
        ZELDA2_PACKAGE_ID, ZELDA2_FEATURE_ID, ZELDA2_OWNER_ROM_ID);
    if (!owner_rom || !*owner_rom || !game_link_set_enabled(1, owner_rom)) {
        game_link_set_enabled(0, NULL);
        game_smash64_set_mod_enabled(0, NULL);
        fprintf(stderr, "[Zelda II] Link player replacement stays OFF. "
                        "Recheck the selected canonical Zelda II ROM.\n");
    }
}

NES_MOD_CONSTRUCTOR(register_zelda2_player_plugin)
{
    if (!zelda2_link_controller_register())
        fprintf(stderr, "[Mods] Failed to register the Zelda II Link "
                        "controller\n");
    if (!game_link_register_hooks())
        fprintf(stderr, "[Mods] Failed to register Zelda II Link gameplay "
                        "hooks\n");
    if (!nes_mod_register_reset_callback(reset_zelda2_player) ||
        !nes_mod_register_activation_plugin(ZELDA2_LINK_CONTROLLER_ID,
                                             activate_link))
        fprintf(stderr, "[Mods] Failed to register the Zelda II player mod\n");
}
