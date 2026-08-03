#include "mod_runtime.h"
#include "game_widescreen.h"

#include <stdio.h>

static void reset_widescreen(void) {
    game_widescreen_set_mod_enabled(0);
}

static void activate_widescreen(void) {
    game_widescreen_set_mod_enabled(1);
}

NES_MOD_CONSTRUCTOR(register_widescreen_plugin) {
    if (!nes_mod_register_reset_callback(reset_widescreen) ||
        !nes_mod_register_activation_plugin(
            "super-mario-bros.widescreen", activate_widescreen))
        fprintf(stderr,
                "[Mods] Failed to register SMB widescreen plugin\n");
}
