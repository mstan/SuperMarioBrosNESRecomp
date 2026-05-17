// semcomp/Runtime.cpp — singleton SemcompGame and C-ABI bridge.
//
// Hosts the one SemcompGame instance for the running process and exposes
// the C-callable functions declared in Runtime.h. The singleton is
// initialized on first call; semcomp_runtime_init() is provided as an
// explicit entry point so extras.c can warm it up at game_on_init time.
#include "semcomp/Runtime.h"

#include "semcomp/SemcompGame.h"
#include "semcomp/SmbRoutines.h"

extern "C" {
#include "nes_runtime.h"
}

namespace {

smb::semcomp::SemcompGame& runtime() {
    static smb::semcomp::SemcompGame g;
    return g;
}

// Pending trainer coin grants. semcomp_runtime_add_coins bumps this;
// apply_post_nmi drains one per frame by invoking the full give_coin()
// path (= our $BBFE GiveOneCoin replacement). One grant per frame keeps
// VRAM_Buffer1 to a single PrintStatusBarNumbers entry — bursting N in
// a single frame overflows the ~64-byte buffer and corrupts the HUD
// row with garbled tiles (observed for N>=10 or so).
int g_pending_coin_grants = 0;

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
    // Despite the legacy name, this now runs all per-frame post-NMI
    // semcomp work: raw byte freezes (Trainer) AND semantic freezes
    // (Mario, PlayerSession). Renaming the C symbol would break the
    // existing extras.c integration; the name is kept and the
    // semantics broadened.
    runtime().apply_post_nmi();

    // Drain one trainer coin grant per frame via the natural-pickup
    // pattern: queue $00FE |= $01 (matches JCoinC at $BB79) then JSR
    // give_coin (our $BBFE GiveOneCoin replacement). give_coin runs
    // DigitsMathRoutine on BOTH the BCD coin-display digits and the
    // score, increments the $075E byte (with 100-coin -> 1-Up rollover
    // and extra-life jingle), and queues one HUD refresh entry.
    if (g_pending_coin_grants > 0) {
        const uint8_t q = nes_read(0x00FE);
        nes_write(0x00FE, static_cast<uint8_t>(q | 0x01));
        runtime().routines().note_invocation(0xBBFE);
        smb::semcomp::give_coin();
        g_pending_coin_grants--;
    }
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

// ---- Semantic setters ----------------------------------------------------

void semcomp_runtime_set_mario_x(uint8_t v)    { runtime().mario().set_x(v); }
void semcomp_runtime_set_mario_y(uint8_t v)    { runtime().mario().set_y(v); }
void semcomp_runtime_set_mario_page(uint8_t v) { runtime().mario().set_page(v); }
void semcomp_runtime_set_mario_power(uint8_t v) {
    runtime().mario().set_power(static_cast<smb::semcomp::PowerStatus>(v));
}
void semcomp_runtime_set_mario_physics_state(uint8_t v) {
    runtime().mario().set_physics_state_raw(v);
}
void semcomp_runtime_set_mario_facing(uint8_t v) {
    runtime().mario().set_facing(static_cast<smb::semcomp::Direction>(v));
}
void semcomp_runtime_set_session_lives(uint8_t v) {
    runtime().session().set_lives(v);
}
void semcomp_runtime_set_session_coins(uint8_t v) {
    runtime().session().set_coins(v);
}

// ---- Semantic freezes ----------------------------------------------------

void semcomp_runtime_freeze_mario_power(uint8_t v) {
    runtime().mario().freeze_power(static_cast<smb::semcomp::PowerStatus>(v));
}
void semcomp_runtime_thaw_mario_power(void) {
    runtime().mario().thaw_power();
}
int semcomp_runtime_is_mario_power_frozen(void) {
    return runtime().mario().is_power_frozen() ? 1 : 0;
}
uint8_t semcomp_runtime_frozen_mario_power_value(void) {
    return static_cast<uint8_t>(runtime().mario().frozen_power_value());
}

void semcomp_runtime_freeze_session_lives(uint8_t v) {
    runtime().session().freeze_lives(v);
}
void semcomp_runtime_thaw_session_lives(void) {
    runtime().session().thaw_lives();
}
int semcomp_runtime_is_session_lives_frozen(void) {
    return runtime().session().is_lives_frozen() ? 1 : 0;
}
uint8_t semcomp_runtime_frozen_session_lives_value(void) {
    return runtime().session().frozen_lives_value();
}

void semcomp_runtime_freeze_session_coins(uint8_t v) {
    runtime().session().freeze_coins(v);
}
void semcomp_runtime_thaw_session_coins(void) {
    runtime().session().thaw_coins();
}
int semcomp_runtime_is_session_coins_frozen(void) {
    return runtime().session().is_coins_frozen() ? 1 : 0;
}
uint8_t semcomp_runtime_frozen_session_coins_value(void) {
    return runtime().session().frozen_coins_value();
}

// ---- Phase 3 routine replacement -----------------------------------------

void semcomp_runtime_give_coin(void) {
    runtime().routines().register_routine(0xBBFE, "GiveOneCoin");
    runtime().routines().note_invocation(0xBBFE);
    smb::semcomp::give_coin();
}

void semcomp_runtime_add_coins(uint8_t n) {
    // Queue N grants for the per-frame ticker. Each frame's apply_post_nmi
    // drains one (full give_coin invocation, full HUD + BCD-digit update,
    // rollover handling, SFX). Two earlier approaches both had bugs:
    //
    //   - Loop give_coin() N times inline: VRAM_Buffer1 overflow on
    //     N>~7 (HUD row corrupted with stray '6' tiles).
    //   - Atomic smb::semcomp::add_coins(N): only wrote the $075E byte,
    //     not the BCD display digits — rollover fired internally but
    //     the on-screen count never changed.
    //
    // Per-frame draining mirrors natural in-game pickup pacing exactly:
    // 25 coins -> 25 frames -> ~0.42 seconds, visibly tickering up,
    // with the 1-Up jingle landing on the natural rollover frame.
    runtime().routines().register_routine(0xBBFE, "GiveOneCoin");
    g_pending_coin_grants += n;
}

void semcomp_runtime_remove_coins(uint8_t n) {
    smb::semcomp::remove_coins(n);
}

uint32_t semcomp_runtime_pending_coin_grants(void) {
    return (uint32_t)(g_pending_coin_grants > 0 ? g_pending_coin_grants : 0);
}

void semcomp_runtime_add_lives(uint8_t n) {
    smb::semcomp::add_lives(n);
}

void semcomp_runtime_remove_lives(uint8_t n) {
    smb::semcomp::remove_lives(n);
}

void semcomp_runtime_set_score(uint32_t value)  { smb::semcomp::set_score(value); }
void semcomp_runtime_add_score(int32_t  delta)  { smb::semcomp::add_score(delta); }
uint32_t semcomp_runtime_get_score(void)        { return smb::semcomp::read_player_score(); }

void semcomp_runtime_set_timer(uint16_t s)      { smb::semcomp::set_timer(s); }
void semcomp_runtime_add_timer(int16_t  d)      { smb::semcomp::add_timer(d); }
uint16_t semcomp_runtime_get_timer(void)        { return smb::semcomp::read_game_timer(); }

int semcomp_runtime_give_power_up(void) {
    return runtime().mario().give_power_up() ? 1 : 0;
}
int semcomp_runtime_take_damage(void) {
    return runtime().mario().take_damage() ? 1 : 0;
}

// ---- Enemies --------------------------------------------------------------

int semcomp_runtime_enemy_active(uint8_t slot) {
    return runtime().enemies().slot(slot).active() ? 1 : 0;
}
uint8_t semcomp_runtime_enemy_id(uint8_t slot) {
    return runtime().enemies().slot(slot).id_raw();
}
uint8_t semcomp_runtime_enemy_state(uint8_t slot) {
    return runtime().enemies().slot(slot).state_raw();
}
uint16_t semcomp_runtime_enemy_world_x(uint8_t slot) {
    return runtime().enemies().slot(slot).world_x();
}
uint8_t semcomp_runtime_enemy_y(uint8_t slot) {
    return runtime().enemies().slot(slot).y();
}
int8_t semcomp_runtime_enemy_x_velocity(uint8_t slot) {
    return runtime().enemies().slot(slot).x_velocity();
}
int8_t semcomp_runtime_enemy_y_velocity(uint8_t slot) {
    return runtime().enemies().slot(slot).y_velocity();
}
int semcomp_runtime_enemy_active_count(void) {
    return runtime().enemies().active_count();
}

int semcomp_runtime_kill_all_enemies(void) {
    int n = runtime().enemies().active_count();
    runtime().enemies().kill_all();
    return n;
}
int semcomp_runtime_stomp_all_enemies(void) {
    int n = runtime().enemies().active_count();
    runtime().enemies().stomp_all();
    return n;
}
int semcomp_runtime_freeze_enemies(void) {
    int n = runtime().enemies().active_count();
    runtime().enemies().freeze_all();
    return n;
}

int semcomp_runtime_kill_enemy(uint8_t slot) {
    if (slot >= smb::semcomp::Enemies::kSlotCount) return 0;
    auto e = runtime().enemies().slot(slot);
    if (!e.active()) return 0;
    e.kill();
    return 1;
}
int semcomp_runtime_stomp_enemy(uint8_t slot) {
    if (slot >= smb::semcomp::Enemies::kSlotCount) return 0;
    auto e = runtime().enemies().slot(slot);
    if (!e.active()) return 0;
    e.stomp();
    return 1;
}

size_t semcomp_runtime_routine_count(void) {
    return runtime().routines().count();
}
uint16_t semcomp_runtime_routine_entry_pc(size_t i) {
    if (i >= runtime().routines().count()) return 0;
    return runtime().routines().entry(i).pc;
}
const char* semcomp_runtime_routine_entry_name(size_t i) {
    if (i >= runtime().routines().count()) return "";
    return runtime().routines().entry(i).name;
}
uint64_t semcomp_runtime_routine_entry_invocations(size_t i) {
    if (i >= runtime().routines().count()) return 0;
    return runtime().routines().entry(i).invocations;
}

}  // extern "C"
