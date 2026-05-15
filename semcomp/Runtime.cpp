// semcomp/Runtime.cpp — singleton SemcompGame and C-ABI bridge.
//
// Hosts the one SemcompGame instance for the running process and exposes
// the C-callable functions declared in Runtime.h. The singleton is
// initialized on first call; semcomp_runtime_init() is provided as an
// explicit entry point so extras.c can warm it up at game_on_init time.
#include "semcomp/Runtime.h"

#include "semcomp/SemcompGame.h"

namespace {

smb::semcomp::SemcompGame& runtime() {
    static smb::semcomp::SemcompGame g;
    return g;
}

}  // namespace

extern "C" {

void semcomp_runtime_init(void) {
    // Force-construct the singleton.
    (void)runtime();
}

// ---- Trainer control ------------------------------------------------------

void semcomp_runtime_set_trainer_enabled(int enabled) {
    runtime().trainer().set_enabled(enabled != 0);
}
int semcomp_runtime_trainer_enabled(void) {
    return runtime().trainer().enabled() ? 1 : 0;
}
void semcomp_runtime_apply_trainer(void) {
    runtime().trainer().apply();
}
int semcomp_runtime_trainer_set(uint16_t addr, uint8_t val) {
    return runtime().trainer().set(addr, val) ? 1 : 0;
}
int semcomp_runtime_trainer_freeze(uint16_t addr, uint8_t val) {
    return runtime().trainer().freeze(addr, val) ? 1 : 0;
}
int semcomp_runtime_trainer_thaw(uint16_t addr) {
    return runtime().trainer().thaw(addr) ? 1 : 0;
}
size_t semcomp_runtime_trainer_count(void) {
    return runtime().trainer().count();
}
uint16_t semcomp_runtime_trainer_entry_addr(size_t i) {
    return runtime().trainer().entry_addr(i);
}
uint8_t semcomp_runtime_trainer_entry_value(size_t i) {
    return runtime().trainer().entry_value(i);
}

// ---- Trainer UI -----------------------------------------------------------

void semcomp_runtime_trainer_ui_tick(void) {
    // Only tick the UI when the trainer subsystem is enabled.
    if (!runtime().trainer().enabled()) return;
    runtime().trainer_ui().tick();
}
void semcomp_runtime_trainer_ui_render(uint32_t* fb, int width, int height) {
    if (!runtime().trainer().enabled()) return;
    runtime().trainer_ui().render(fb, width, height);
}
int semcomp_runtime_trainer_ui_grabbing_input(void) {
    if (!runtime().trainer().enabled()) return 0;
    return runtime().trainer_ui().grabbing_input() ? 1 : 0;
}

// ---- Mario reads ----------------------------------------------------------

uint8_t  semcomp_runtime_mario_x(void)        { return runtime().mario().x(); }
uint8_t  semcomp_runtime_mario_y(void)        { return runtime().mario().y(); }
uint8_t  semcomp_runtime_mario_page(void)     { return runtime().mario().page(); }
uint16_t semcomp_runtime_mario_world_x(void)  { return runtime().mario().world_x(); }
int8_t   semcomp_runtime_mario_x_velocity(void) { return runtime().mario().x_velocity(); }
int8_t   semcomp_runtime_mario_y_velocity(void) { return runtime().mario().y_velocity(); }
uint8_t  semcomp_runtime_mario_x_speed_absolute(void) {
    return runtime().mario().x_speed_absolute();
}
uint8_t  semcomp_runtime_mario_power(void) {
    return static_cast<uint8_t>(runtime().mario().power());
}
uint8_t  semcomp_runtime_mario_physics_state(void) {
    return runtime().mario().physics_state_raw();
}
int semcomp_runtime_mario_on_ground(void) {
    return runtime().mario().on_ground() ? 1 : 0;
}
uint8_t  semcomp_runtime_mario_facing(void) {
    return static_cast<uint8_t>(runtime().mario().facing());
}

// ---- Level / PlayerSession reads -----------------------------------------

uint8_t  semcomp_runtime_level_world(void)              { return runtime().level().world(); }
uint8_t  semcomp_runtime_level_level(void)              { return runtime().level().level(); }
uint16_t semcomp_runtime_level_world_level_packed(void) { return runtime().level().world_level_packed(); }
uint8_t  semcomp_runtime_session_lives(void)            { return runtime().session().lives(); }
uint8_t  semcomp_runtime_session_coins(void)            { return runtime().session().coins(); }

}  // extern "C"
