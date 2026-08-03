#include "mod_runtime.h"
#include "game_voxel.h"

#include <stdio.h>

static void reset_voxel(void) {
    game_voxel_set_mod_enabled(0);
}

static void activate_voxel(void) {
    const char *package =
        "super-mario-bros.enhancement.voxel-first-person";
    const char *feature = "voxel-first-person";
    game_voxel_configure_mod(
        nes_mod_get_option_int(package, feature, "pitch", 15),
        nes_mod_get_option_int(package, feature, "yaw", 0),
        nes_mod_get_option_int(package, feature, "roll", 0),
        nes_mod_get_option_int(package, feature, "zoom", 100),
        nes_mod_get_option_int(package, feature, "sprite-scale", 120));
    game_voxel_set_mod_enabled(1);
}

NES_MOD_CONSTRUCTOR(register_voxel_plugin) {
    if (!nes_mod_register_reset_callback(reset_voxel) ||
        !nes_mod_register_activation_plugin(
            "super-mario-bros.voxel-first-person", activate_voxel))
        fprintf(stderr,
                "[Mods] Failed to register SMB first-person voxel plugin\n");
}
