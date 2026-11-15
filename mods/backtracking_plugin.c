#include "mod_runtime.h"
#include "game_widescreen.h"
#include <stdio.h>
static void reset(void) { game_backtracking_set_enabled(0); }
static void activate(void) { game_backtracking_set_enabled(1); }
NES_MOD_CONSTRUCTOR(register_backtracking_plugin) {
    if (!nes_mod_register_reset_callback(reset) ||
        !nes_mod_register_activation_plugin("super-mario-bros.backtracking",activate))
        fprintf(stderr,"[Mods] Failed to register free-backtracking plugin\n");
}
