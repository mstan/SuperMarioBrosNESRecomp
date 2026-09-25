#include "mod_runtime.h"
#include "game_coop.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void reset_coop(void) { game_coop_configure(0, 0); }
static void activate_coop(void) {
    const char *package = "super-mario-bros.gameplay.simultaneous-coop";
    char count[16]="2", pause[16]="player";
    nes_mod_option_value(package,"coop","players",count,sizeof count);
    nes_mod_option_value(package,"coop","pause",pause,sizeof pause);
    game_coop_configure(atoi(count),!strcmp(pause,"shared"));
}
NES_MOD_CONSTRUCTOR(register_coop_plugin) {
    if (!game_coop_register() || !nes_mod_register_reset_callback(reset_coop) ||
        !nes_mod_register_activation_plugin("super-mario-bros.coop",activate_coop))
        fprintf(stderr,"[Co-op] Plugin registration failed\n");
}
