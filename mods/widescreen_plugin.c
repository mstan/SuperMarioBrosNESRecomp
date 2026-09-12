#include "mod_runtime.h"
#include "game_widescreen.h"

#include <stdio.h>

static void reset_widescreen(void) {
    game_widescreen_set_mod_enabled(0);
}

static void activate_widescreen(void) {
    const char *package = "super-mario-bros.enhancement.widescreen";
    char aspect[32] = "fit", hud[32] = "edges", enemies[32]="viewport";
    nes_mod_option_value(package, "widescreen", "aspect", aspect, sizeof aspect);
    nes_mod_option_value(package, "widescreen", "hud", hud, sizeof hud);
    nes_mod_option_value(package,"widescreen","enemy_activation",enemies,sizeof enemies);
    game_widescreen_configure(aspect, hud, enemies);
    char camera[32] = "edges";
    nes_mod_option_value(package, "widescreen", "camera", camera, sizeof camera);
    game_widescreen_set_camera(camera);
    game_widescreen_set_mod_enabled(1);
}

NES_MOD_CONSTRUCTOR(register_widescreen_plugin) {
    if (!nes_mod_register_reset_callback(reset_widescreen) ||
        !nes_mod_register_activation_plugin(
            "super-mario-bros.widescreen", activate_widescreen))
        fprintf(stderr,
                "[Mods] Failed to register SMB widescreen plugin\n");
}
