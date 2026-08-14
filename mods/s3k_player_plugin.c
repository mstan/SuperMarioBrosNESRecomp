#include "mod_runtime.h"

#include "game_sonic.h"
#include "game_smash64.h"
#include "s3k/sonic_controller.h"

#include <stdio.h>

#define S3K_PACKAGE_ID \
    "super-mario-bros.gameplay.s3k-sonic-player-replacement"
#define S3K_FEATURE_ID "s3k-sonic-player"
#define S3K_OWNER_ROM_ID "sonic-3-and-knuckles"

static void reset_s3k_player(void)
{
    game_sonic_set_enabled(0, NULL);
    if (game_smash64_sonic_selected())
        game_smash64_set_mod_enabled(0, NULL);
}

static void activate_sonic(void)
{
    const char *owner_rom = nes_mod_external_rom_path(
        S3K_PACKAGE_ID, S3K_FEATURE_ID, S3K_OWNER_ROM_ID);
    if (!owner_rom || !*owner_rom || !game_sonic_set_enabled(1, owner_rom)) {
        game_sonic_set_enabled(0, NULL);
        game_smash64_set_mod_enabled(0, NULL);
        fprintf(stderr, "[S3&K] Sonic player replacement stays OFF. "
                        "Recheck the selected Sonic 3 & Knuckles ROM.\n");
    }
}

NES_MOD_CONSTRUCTOR(register_s3k_player_plugin)
{
    if (!s3k_sonic_controller_register())
        fprintf(stderr, "[Mods] Failed to register the S3&K Sonic controller\n");
    if (!game_sonic_register_hooks())
        fprintf(stderr, "[Mods] Failed to register S3&K Sonic gameplay hooks\n");
    if (!nes_mod_register_reset_callback(reset_s3k_player) ||
        !nes_mod_register_activation_plugin(S3K_SONIC_CONTROLLER_ID,
                                             activate_sonic))
        fprintf(stderr, "[Mods] Failed to register the S3&K Sonic player mod\n");
}
