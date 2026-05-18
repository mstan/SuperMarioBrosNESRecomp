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

// ---- Camera ---------------------------------------------------------------

uint16_t semcomp_runtime_camera_left_world_x(void) {
    return runtime().camera().left_world_x();
}
uint16_t semcomp_runtime_camera_right_world_x(void) {
    return runtime().camera().right_world_x();
}
int semcomp_runtime_camera_is_locked(void) {
    return runtime().camera().is_locked() ? 1 : 0;
}
void semcomp_runtime_camera_set_world_x(uint16_t world_x) {
    runtime().camera().set_world_x(world_x);
}
void semcomp_runtime_camera_lock(void)   { runtime().camera().lock();   }
void semcomp_runtime_camera_unlock(void) { runtime().camera().unlock(); }

// ---- World verbs ---------------------------------------------------------

int semcomp_runtime_bump_block_under_mario(uint8_t block_code) {
    smb::semcomp::bump_block_under_mario(block_code);
    return 1;
}
int semcomp_runtime_spawn_powerup(uint8_t type) {
    smb::semcomp::spawn_powerup(type);
    return 1;
}
uint8_t semcomp_runtime_spawn_floatey(uint8_t points_table_index) {
    return smb::semcomp::spawn_floatey_above_mario(points_table_index);
}

// ---- Replace_func bridges ------------------------------------------------

void semcomp_runtime_bump_block_replacement(void) {
    runtime().routines().register_routine(0xBD9B, "BumpBlock");
    runtime().routines().note_invocation(0xBD9B);
    runtime().blocks().bump_block();
}
void semcomp_runtime_setup_powerup_replacement(void) {
    runtime().routines().register_routine(0xBC49, "SetupPowerUp");
    runtime().routines().note_invocation(0xBC49);
    runtime().powerups().setup();
}
void semcomp_runtime_pause_tick(void) {
    runtime().routines().register_routine(0x8182, "PauseRoutine");
    runtime().routines().note_invocation(0x8182);
    runtime().mode().on_pause_tick();
}
void semcomp_runtime_print_status_bar_numbers(void) {
    runtime().routines().register_routine(0x8F06, "PrintStatusBarNumbers");
    runtime().routines().note_invocation(0x8F06);
    runtime().hud().print_status_bar_numbers();
}
void semcomp_runtime_add_to_score(void) {
    runtime().routines().register_routine(0xBC27, "AddToScore");
    runtime().routines().note_invocation(0xBC27);
    runtime().hud().add_to_score();
}
void semcomp_runtime_setup_floatey_number(void) {
    runtime().routines().register_routine(0xDA11, "SetupFloateyNumber");
    runtime().routines().note_invocation(0xDA11);
    runtime().floateys().setup();
}
void semcomp_runtime_init_normal_enemy(void) {
    runtime().routines().register_routine(0xC30E, "InitNormalEnemy");
    runtime().routines().note_invocation(0xC30E);
    runtime().enemies().init_normal_enemy();
}
void semcomp_runtime_move_normal_enemy(void) {
    runtime().routines().register_routine(0xCA77, "MoveNormalEnemy");
    runtime().routines().note_invocation(0xCA77);
    runtime().enemies().move_normal_enemy();
}
void semcomp_runtime_auto_control_player(void) {
    runtime().routines().register_routine(0xB0E6, "AutoControlPlayer");
    runtime().routines().note_invocation(0xB0E6);
    runtime().player_physics().auto_control();
}
void semcomp_runtime_player_movement_subs(void) {
    runtime().routines().register_routine(0xB329, "PlayerMovementSubs");
    runtime().routines().note_invocation(0xB329);
    runtime().player_physics().movement_subs();
}
void semcomp_runtime_player_change_size(void) {
    runtime().routines().register_routine(0xB233, "PlayerChangeSize");
    runtime().routines().note_invocation(0xB233);
    runtime().player_anim().change_size();
}
void semcomp_runtime_player_injury_blink(void) {
    runtime().routines().register_routine(0xB245, "PlayerInjuryBlink");
    runtime().routines().note_invocation(0xB245);
    runtime().player_anim().injury_blink();
}
void semcomp_runtime_player_death(void) {
    runtime().routines().register_routine(0xB269, "PlayerDeath");
    runtime().routines().note_invocation(0xB269);
    runtime().player_anim().player_death();
}
void semcomp_runtime_player_fire_flower(void) {
    runtime().routines().register_routine(0xB27D, "PlayerFireFlower");
    runtime().routines().note_invocation(0xB27D);
    runtime().player_anim().fire_flower();
}
void semcomp_runtime_on_ground_state_sub(void) {
    runtime().routines().register_routine(0xB35A, "OnGroundStateSub");
    runtime().routines().note_invocation(0xB35A);
    runtime().player_physics().on_ground_state_sub();
}
void semcomp_runtime_falling_sub(void) {
    runtime().routines().register_routine(0xB36D, "FallingSub");
    runtime().routines().note_invocation(0xB36D);
    runtime().player_physics().falling_sub();
}
void semcomp_runtime_jump_swim_sub(void) {
    runtime().routines().register_routine(0xB376, "JumpSwimSub");
    runtime().routines().note_invocation(0xB376);
    runtime().player_physics().jump_swim_sub();
}
void semcomp_runtime_climbing_sub(void) {
    runtime().routines().register_routine(0xB3CF, "ClimbingSub");
    runtime().routines().note_invocation(0xB3CF);
    runtime().player_physics().climbing_sub();
}
void semcomp_runtime_physics_sub(void) {
    runtime().routines().register_routine(0xB450, "PlayerPhysicsSub");
    runtime().routines().note_invocation(0xB450);
    runtime().player_physics().physics_sub();
}
void semcomp_runtime_move_player_y_axis(void) {
    runtime().routines().register_routine(0xB200, "MovePlayerYAxis");
    runtime().routines().note_invocation(0xB200);
    runtime().player_physics().move_player_y_axis();
}
void semcomp_runtime_move_player_horizontally(void) {
    runtime().routines().register_routine(0xBF09, "MovePlayerHorizontally");
    runtime().routines().note_invocation(0xBF09);
    runtime().player_physics().move_player_horizontally();
}
void semcomp_runtime_ex_x_move(void) {
    runtime().routines().register_routine(0xBF4C, "ExXMove");
    runtime().routines().note_invocation(0xBF4C);
    runtime().player_physics().ex_x_move();
}
void semcomp_runtime_move_player_vertically(void) {
    runtime().routines().register_routine(0xBF4D, "MovePlayerVertically");
    runtime().routines().note_invocation(0xBF4D);
    runtime().player_physics().move_player_vertically();
}
void semcomp_runtime_player_bg_collision(void) {
    runtime().routines().register_routine(0xDC64, "PlayerBGCollision");
    runtime().routines().note_invocation(0xDC64);
    runtime().player_collision().player_bg_collision();
}

// Phase 17 — Player graphics bridges.
#define SEMCOMP_GFX_BRIDGE(fn, pc, name, method) \
    void fn(void) { \
        runtime().routines().register_routine(pc, name); \
        runtime().routines().note_invocation(pc); \
        runtime().player_graphics().method(); \
    }

SEMCOMP_GFX_BRIDGE(semcomp_runtime_get_player_colors, 0x85F1, "GetPlayerColors", get_player_colors)
SEMCOMP_GFX_BRIDGE(semcomp_runtime_draw_player_loop, 0xEFDC, "DrawPlayerLoop", draw_player_loop)
SEMCOMP_GFX_BRIDGE(semcomp_runtime_relative_player_position, 0xF12A, "RelativePlayerPosition", relative_player_position)
SEMCOMP_GFX_BRIDGE(semcomp_runtime_relative_player_position_f12c, 0xF12C, "RelativePlayerPosition_F12C", relative_player_position_f12c)
SEMCOMP_GFX_BRIDGE(semcomp_runtime_draw_player_intermediate, 0xEFA4, "DrawPlayer_Intermediate", draw_player_intermediate)
SEMCOMP_GFX_BRIDGE(semcomp_runtime_draw_player_intermediate_pintloop, 0xEFA6, "PIntLoop", draw_player_intermediate_pintloop)
SEMCOMP_GFX_BRIDGE(semcomp_runtime_draw_player_intermediate_efac, 0xEFAC, "DrawPI_EFAC", draw_player_intermediate_efac)
SEMCOMP_GFX_BRIDGE(semcomp_runtime_player_gfx_handler, 0xEEE9, "PlayerGfxHandler", player_gfx_handler)
SEMCOMP_GFX_BRIDGE(semcomp_runtime_player_gfx_handler_eef7, 0xEEF7, "PGH_EEF7", player_gfx_handler_eef7)
SEMCOMP_GFX_BRIDGE(semcomp_runtime_player_gfx_handler_ef85, 0xEF85, "PGH_EF85", player_gfx_handler_ef85)
SEMCOMP_GFX_BRIDGE(semcomp_runtime_player_gfx_handler_eefc, 0xEEFC, "PGH_EEFC", player_gfx_handler_eefc)
SEMCOMP_GFX_BRIDGE(semcomp_runtime_player_gfx_handler_eefe, 0xEEFE, "PGH_EEFE", player_gfx_handler_eefe)
SEMCOMP_GFX_BRIDGE(semcomp_runtime_player_gfx_handler_eeee, 0xEEEE, "PGH_EEEE", player_gfx_handler_eeee)
SEMCOMP_GFX_BRIDGE(semcomp_runtime_player_gfx_handler_eef0, 0xEEF0, "PGH_EEF0", player_gfx_handler_eef0)
SEMCOMP_GFX_BRIDGE(semcomp_runtime_player_gfx_handler_eef1, 0xEEF1, "PGH_EEF1", player_gfx_handler_eef1)
SEMCOMP_GFX_BRIDGE(semcomp_runtime_player_gfx_handler_ef10, 0xEF10, "PGH_EF10", player_gfx_handler_ef10)
SEMCOMP_GFX_BRIDGE(semcomp_runtime_player_gfx_handler_ef01, 0xEF01, "PGH_EF01", player_gfx_handler_ef01)
SEMCOMP_GFX_BRIDGE(semcomp_runtime_player_gfx_handler_ef42, 0xEF42, "PGH_EF42", player_gfx_handler_ef42)
SEMCOMP_GFX_BRIDGE(semcomp_runtime_player_gfx_handler_ef7a, 0xEF7A, "PlayerOffscreenChk", player_gfx_handler_ef7a)
SEMCOMP_GFX_BRIDGE(semcomp_runtime_player_gfx_handler_ef97, 0xEF97, "PGH_EF97", player_gfx_handler_ef97)

#undef SEMCOMP_GFX_BRIDGE

void semcomp_runtime_powerup_obj_handler(void) {
    runtime().routines().register_routine(0xBC85, "PowerUpObjHandler");
    runtime().routines().note_invocation(0xBC85);
    runtime().object_handlers().powerup_obj_handler();
}
void semcomp_runtime_fireball_obj_core(void) {
    runtime().routines().register_routine(0xB689, "FireballObjCore");
    runtime().routines().note_invocation(0xB689);
    runtime().object_handlers().fireball_obj_core();
}
void semcomp_runtime_coin_block(void) {
    runtime().routines().register_routine(0xBB38, "CoinBlock");
    runtime().routines().note_invocation(0xBB38);
    runtime().object_handlers().coin_block();
}

// Phase 19 — BumpBlock untangle.
void semcomp_runtime_bump_block(void) {
    runtime().routines().register_routine(0xBD9B, "BumpBlock");
    runtime().routines().note_invocation(0xBD9B);
    runtime().blocks().bump_block();
}
void semcomp_runtime_mush_flower_block(void) {
    runtime().routines().register_routine(0xBDD2, "MushFlowerBlock");
    runtime().routines().note_invocation(0xBDD2);
    runtime().blocks().mush_flower_block();
}
void semcomp_runtime_vine_block(void) {
    runtime().routines().register_routine(0xBDDF, "VineBlock");
    runtime().routines().note_invocation(0xBDDF);
    runtime().blocks().vine_block();
}
void semcomp_runtime_star_block(void) {
    runtime().routines().register_routine(0xBDD5, "StarBlock");
    runtime().routines().note_invocation(0xBDD5);
    runtime().blocks().star_block();
}
void semcomp_runtime_extra_life_mush_block(void) {
    runtime().routines().register_routine(0xBDD8, "ExtraLifeMushBlock");
    runtime().routines().note_invocation(0xBDD8);
    runtime().blocks().extra_life_mush_block();
}

// Phase 20 — HUD math untangle.
void semcomp_runtime_digits_math_routine(void) {
    runtime().routines().register_routine(0x8F5F, "DigitsMathRoutine");
    runtime().routines().note_invocation(0x8F5F);
    runtime().hud().digits_math_routine();
}
void semcomp_runtime_add_mod_loop(void) {
    runtime().routines().register_routine(0x8F68, "AddModLoop");
    runtime().routines().note_invocation(0x8F68);
    runtime().hud().add_mod_loop();
}
void semcomp_runtime_store_new_d(void) {
    runtime().routines().register_routine(0x8F75, "StoreNewD");
    runtime().routines().note_invocation(0x8F75);
    runtime().hud().store_new_d();
}
void semcomp_runtime_output_numbers(void) {
    runtime().routines().register_routine(0x8F11, "OutputNumbers");
    runtime().routines().note_invocation(0x8F11);
    runtime().hud().output_numbers();
}

// Phase 21 — Floatey per-frame untangle.
void semcomp_runtime_floatey_per_frame(void) {
    runtime().routines().register_routine(0x84C3, "FloateyNumbersRoutine");
    runtime().routines().note_invocation(0x84C3);
    runtime().floateys().per_frame_tick();
}
void semcomp_runtime_floatey_part_8534(void) {
    runtime().routines().register_routine(0x8534, "FloateyPart");
    runtime().routines().note_invocation(0x8534);
    runtime().floateys().floatey_part_8534();
}

// Phase 22 — Damage chain untangle.
void semcomp_runtime_injure_player(void) {
    runtime().routines().register_routine(0xD92C, "InjurePlayer");
    runtime().routines().note_invocation(0xD92C);
    runtime().damage_chain().injure_player();
}
void semcomp_runtime_force_injury(void) {
    runtime().routines().register_routine(0xD931, "ForceInjury");
    runtime().routines().note_invocation(0xD931);
    runtime().damage_chain().force_injury();
}
void semcomp_runtime_title_screen_mode(void) {
    runtime().routines().register_routine(0x8231, "TitleScreenMode");
    runtime().routines().note_invocation(0x8231);
    runtime().mode().title_screen_mode();
}
void semcomp_runtime_game_mode_tick(void) {
    runtime().routines().register_routine(0xAEDC, "GameMode");
    runtime().routines().note_invocation(0xAEDC);
    runtime().mode().game_mode_tick();
}
void semcomp_runtime_game_over_mode(void) {
    runtime().routines().register_routine(0x9218, "GameOverMode");
    runtime().routines().note_invocation(0x9218);
    runtime().mode().game_over_mode();
}

// ---- GameMode reads + verbs ----------------------------------------------

uint8_t semcomp_runtime_mode_oper_mode(void) {
    return runtime().mode().oper_mode_raw();
}
uint8_t semcomp_runtime_mode_oper_mode_task(void) {
    return runtime().mode().oper_mode_task();
}
uint8_t semcomp_runtime_mode_player_ctrl_routine(void) {
    return runtime().mode().player_ctrl_routine_raw();
}
uint8_t semcomp_runtime_mode_pause_status(void) {
    return runtime().mode().pause_status_raw();
}
uint8_t semcomp_runtime_mode_pause_timer(void) {
    return runtime().mode().pause_timer();
}
int semcomp_runtime_mode_is_paused(void) {
    return runtime().mode().is_paused() ? 1 : 0;
}
void semcomp_runtime_mode_set_paused(int paused) {
    runtime().mode().set_paused(paused != 0);
}
void semcomp_runtime_mode_end_level(void) {
    runtime().mode().end_level();
}
void semcomp_runtime_mode_warp_to(uint8_t world, uint8_t level) {
    runtime().mode().warp_to(world, level);
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

// Phase 24 — Enemies mega (batch 1).
void semcomp_runtime_init_goomba(void) {
    runtime().routines().register_routine(0xC2F1, "InitGoomba");
    runtime().routines().note_invocation(0xC2F1);
    runtime().enemy_handlers().init_goomba();
}

void semcomp_runtime_init_hammer_bro(void) {
    runtime().routines().register_routine(0xC328, "InitHammerBro");
    runtime().routines().note_invocation(0xC328);
    runtime().enemy_handlers().init_hammer_bro();
}

void semcomp_runtime_init_bullet_bill(void) {
    runtime().routines().register_routine(0xC36B, "InitBulletBill");
    runtime().routines().note_invocation(0xC36B);
    runtime().enemy_handlers().init_bullet_bill();
}

void semcomp_runtime_init_cheep_cheep(void) {
    runtime().routines().register_routine(0xC375, "InitCheepCheep");
    runtime().routines().note_invocation(0xC375);
    runtime().enemy_handlers().init_cheep_cheep();
}

void semcomp_runtime_init_lakitu(void) {
    runtime().routines().register_routine(0xC385, "InitLakitu");
    runtime().routines().note_invocation(0xC385);
    runtime().enemy_handlers().init_lakitu();
}

void semcomp_runtime_setup_lakitu(void) {
    runtime().routines().register_routine(0xC38A, "SetupLakitu");
    runtime().routines().note_invocation(0xC38A);
    runtime().enemy_handlers().setup_lakitu();
}

void semcomp_runtime_init_short_firebar(void) {
    runtime().routines().register_routine(0xC45C, "InitShortFirebar");
    runtime().routines().note_invocation(0xC45C);
    runtime().enemy_handlers().init_short_firebar();
}

void semcomp_runtime_move_defeated_enemy(void) {
    runtime().routines().register_routine(0xCAE5, "MoveDefeatedEnemy");
    runtime().routines().note_invocation(0xCAE5);
    runtime().enemy_handlers().move_defeated_enemy();
}

void semcomp_runtime_move_jumping_enemy(void) {
    runtime().routines().register_routine(0xCAF9, "MoveJumpingEnemy");
    runtime().routines().note_invocation(0xCAF9);
    runtime().enemy_handlers().move_jumping_enemy();
}

void semcomp_runtime_move_bloober(void) {
    runtime().routines().register_routine(0xCB89, "MoveBloober");
    runtime().routines().note_invocation(0xCB89);
    runtime().enemy_handlers().move_bloober();
}

// Phase 24 batch 2 — enemies.
void semcomp_runtime_bridge_collapse(void) {
    runtime().routines().register_routine(0xCFEC, "BridgeCollapse");
    runtime().routines().note_invocation(0xCFEC);
    runtime().enemy_handlers2().bridge_collapse();
}

void semcomp_runtime_kill_all_enemies_d071(void) {
    runtime().routines().register_routine(0xD071, "KillAllEnemies");
    runtime().routines().note_invocation(0xD071);
    runtime().enemy_handlers2().kill_all_enemies_d071();
}

void semcomp_runtime_run_bowser(void) {
    runtime().routines().register_routine(0xD065, "RunBowser");
    runtime().routines().note_invocation(0xD065);
    runtime().enemy_handlers2().run_bowser();
}

void semcomp_runtime_move_d_bowser(void) {
    runtime().routines().register_routine(0xD00F, "MoveD_Bowser");
    runtime().routines().note_invocation(0xD00F);
    runtime().enemy_handlers2().move_d_bowser();
}

void semcomp_runtime_erase_enemy_object(void) {
    runtime().routines().register_routine(0xC998, "EraseEnemyObject");
    runtime().routines().note_invocation(0xC998);
    runtime().enemy_handlers2().erase_enemy_object();
}

void semcomp_runtime_init_vstf(void) {
    runtime().routines().register_routine(0xC363, "InitVStf");
    runtime().routines().note_invocation(0xC363);
    runtime().enemy_handlers2().init_vstf();
}

void semcomp_runtime_init_enemy_object(void) {
    runtime().routines().register_routine(0xC226, "InitEnemyObject");
    runtime().routines().note_invocation(0xC226);
    runtime().enemy_handlers2().init_enemy_object();
}

void semcomp_runtime_check_frenzy_buffer(void) {
    runtime().routines().register_routine(0xC216, "CheckFrenzyBuffer");
    runtime().routines().note_invocation(0xC216);
    runtime().enemy_handlers2().check_frenzy_buffer();
}

void semcomp_runtime_check_three_bytes(void) {
    runtime().routines().register_routine(0xC250, "CheckThreeBytes");
    runtime().routines().note_invocation(0xC250);
    runtime().enemy_handlers2().check_three_bytes();
}

void semcomp_runtime_handle_group_enemies(void) {
    runtime().routines().register_routine(0xC71B, "HandleGroupEnemies");
    runtime().routines().note_invocation(0xC71B);
    runtime().enemy_handlers2().handle_group_enemies();
}

void semcomp_runtime_inc_3b(void) {
    runtime().routines().register_routine(0xC25B, "Inc3B");
    runtime().routines().note_invocation(0xC25B);
    runtime().enemy_handlers2().inc_3b();
}

void semcomp_runtime_end_area_points(void) {
    runtime().routines().register_routine(0xD336, "EndAreaPoints");
    runtime().routines().note_invocation(0xD336);
    runtime().enemy_handlers2().end_area_points();
}

void semcomp_runtime_award_game_timer_points(void) {
    runtime().routines().register_routine(0xD312, "AwardGameTimerPoints");
    runtime().routines().note_invocation(0xD312);
    runtime().enemy_handlers2().award_game_timer_points();
}

// Phase 25 — Level parser (batch 1)
void semcomp_runtime_get_area_palette(void) {
    runtime().routines().register_routine(0x85BF, "GetAreaPalette");
    runtime().routines().note_invocation(0x85BF);
    runtime().level_parser().get_area_palette();
}

void semcomp_runtime_area_parser_task_control(void) {
    runtime().routines().register_routine(0x86E6, "AreaParserTaskControl");
    runtime().routines().note_invocation(0x86E6);
    runtime().level_parser().area_parser_task_control();
}

void semcomp_runtime_render_area_graphics(void) {
    runtime().routines().register_routine(0x88AE, "RenderAreaGraphics");
    runtime().routines().note_invocation(0x88AE);
    runtime().level_parser().render_area_graphics();
}

void semcomp_runtime_initialize_area(void) {
    runtime().routines().register_routine(0x8FE4, "InitializeArea");
    runtime().routines().note_invocation(0x8FE4);
    runtime().level_parser().initialize_area();
}

void semcomp_runtime_area_parser_task_handler(void) {
    runtime().routines().register_routine(0x92B0, "AreaParserTaskHandler");
    runtime().routines().note_invocation(0x92B0);
    runtime().level_parser().area_parser_task_handler();
}

void semcomp_runtime_area_parser_tasks(void) {
    runtime().routines().register_routine(0x92C8, "AreaParserTasks");
    runtime().routines().note_invocation(0x92C8);
    runtime().level_parser().area_parser_tasks();
}

void semcomp_runtime_get_area_object_i_d(void) {
    runtime().routines().register_routine(0x9B36, "GetAreaObjectID");
    runtime().routines().note_invocation(0x9B36);
    runtime().level_parser().get_area_object_i_d();
}

void semcomp_runtime_get_area_obj_x_position(void) {
    runtime().routines().register_routine(0x9BCB, "GetAreaObjXPosition");
    runtime().routines().note_invocation(0x9BCB);
    runtime().level_parser().get_area_obj_x_position();
}

void semcomp_runtime_get_area_obj_y_position(void) {
    runtime().routines().register_routine(0x9BD3, "GetAreaObjYPosition");
    runtime().routines().note_invocation(0x9BD3);
    runtime().level_parser().get_area_obj_y_position();
}

void semcomp_runtime_load_area_pointer(void) {
    runtime().routines().register_routine(0x9C03, "LoadAreaPointer");
    runtime().routines().note_invocation(0x9C03);
    runtime().level_parser().load_area_pointer();
}

void semcomp_runtime_get_area_type(void) {
    runtime().routines().register_routine(0x9C09, "GetAreaType");
    runtime().routines().note_invocation(0x9C09);
    runtime().level_parser().get_area_type();
}

void semcomp_runtime_get_area_data_addrs(void) {
    runtime().routines().register_routine(0x9C22, "GetAreaDataAddrs");
    runtime().routines().note_invocation(0x9C22);
    runtime().level_parser().get_area_data_addrs();
}

// Phase 25 — Level parser (batch 1)

// Phase 26 — BG renderer + VRAM
void semcomp_runtime_set_v_r_a_m_addr__a(void) {
    runtime().routines().register_routine(0x85C5, "SetVRAMAddr_A");
    runtime().routines().note_invocation(0x85C5);
    runtime().bg_renderer().set_v_r_a_m_addr__a();
}

void semcomp_runtime_set_v_r_a_m_offset(void) {
    runtime().routines().register_routine(0x863F, "SetVRAMOffset");
    runtime().routines().note_invocation(0x863F);
    runtime().bg_renderer().set_v_r_a_m_offset();
}

void semcomp_runtime_set_v_r_a_m_addr__b(void) {
    runtime().routines().register_routine(0x864C, "SetVRAMAddr_B");
    runtime().routines().note_invocation(0x864C);
    runtime().bg_renderer().set_v_r_a_m_addr__b();
}

void semcomp_runtime_write_top_status_line(void) {
    runtime().routines().register_routine(0x8652, "WriteTopStatusLine");
    runtime().routines().note_invocation(0x8652);
    runtime().bg_renderer().write_top_status_line();
}

void semcomp_runtime_write_bottom_status_line(void) {
    runtime().routines().register_routine(0x865A, "WriteBottomStatusLine");
    runtime().routines().note_invocation(0x865A);
    runtime().bg_renderer().write_bottom_status_line();
}

void semcomp_runtime_write_top_score(void) {
    runtime().routines().register_routine(0x8749, "WriteTopScore");
    runtime().routines().note_invocation(0x8749);
    runtime().bg_renderer().write_top_score();
}

void semcomp_runtime_set_v_r_a_m_ctrl(void) {
    runtime().routines().register_routine(0x89BD, "SetVRAMCtrl");
    runtime().routines().note_invocation(0x89BD);
    runtime().bg_renderer().set_v_r_a_m_ctrl();
}

void semcomp_runtime_write_n_t_addr(void) {
    runtime().routines().register_routine(0x8E2D, "WriteNTAddr");
    runtime().routines().note_invocation(0x8E2D);
    runtime().bg_renderer().write_n_t_addr();
}

void semcomp_runtime_write_buffer_to_screen(void) {
    runtime().routines().register_routine(0x8E92, "WriteBufferToScreen");
    runtime().routines().note_invocation(0x8E92);
    runtime().bg_renderer().write_buffer_to_screen();
}

void semcomp_runtime_write_p_p_u_reg1(void) {
    runtime().routines().register_routine(0x8EED, "WritePPUReg1");
    runtime().routines().note_invocation(0x8EED);
    runtime().bg_renderer().write_p_p_u_reg1();
}

// Phase 27-30 — Audio
void semcomp_runtime_run_offscr_bits_subs(void) {
    runtime().routines().register_routine(0xF1D7, "RunOffscrBitsSubs");
    runtime().routines().note_invocation(0xF1D7);
    runtime().sound_engine().run_offscr_bits_subs();
}

void semcomp_runtime_play_flagpole_slide(void) {
    runtime().routines().register_routine(0xF3BF, "PlayFlagpoleSlide");
    runtime().routines().note_invocation(0xF3BF);
    runtime().sound_engine().play_flagpole_slide();
}

void semcomp_runtime_play_small_jump(void) {
    runtime().routines().register_routine(0xF3CD, "PlaySmallJump");
    runtime().routines().note_invocation(0xF3CD);
    runtime().sound_engine().play_small_jump();
}

void semcomp_runtime_play_big_jump(void) {
    runtime().routines().register_routine(0xF3D1, "PlayBigJump");
    runtime().routines().note_invocation(0xF3D1);
    runtime().sound_engine().play_big_jump();
}

void semcomp_runtime_play_fireball_throw(void) {
    runtime().routines().register_routine(0xF3F9, "PlayFireballThrow");
    runtime().routines().note_invocation(0xF3F9);
    runtime().sound_engine().play_fireball_throw();
}

void semcomp_runtime_play_bump(void) {
    runtime().routines().register_routine(0xF3FF, "PlayBump");
    runtime().routines().note_invocation(0xF3FF);
    runtime().sound_engine().play_bump();
}

void semcomp_runtime_play_timer_tick(void) {
    runtime().routines().register_routine(0xF51E, "PlayTimerTick");
    runtime().routines().note_invocation(0xF51E);
    runtime().sound_engine().play_timer_tick();
}

void semcomp_runtime_play_blast(void) {
    runtime().routines().register_routine(0xF53A, "PlayBlast");
    runtime().routines().note_invocation(0xF53A);
    runtime().sound_engine().play_blast();
}

void semcomp_runtime_play_power_up_grab(void) {
    runtime().routines().register_routine(0xF552, "PlayPowerUpGrab");
    runtime().routines().note_invocation(0xF552);
    runtime().sound_engine().play_power_up_grab();
}

void semcomp_runtime_play_noise_sfx(void) {
    runtime().routines().register_routine(0xF64D, "PlayNoiseSfx");
    runtime().routines().note_invocation(0xF64D);
    runtime().sound_engine().play_noise_sfx();
}

// Phase 31 — Misc utilities
void semcomp_runtime_inc_subtask(void) {
    runtime().routines().register_routine(0x8745, "IncSubtask");
    runtime().routines().note_invocation(0x8745);
    runtime().misc_utilities().inc_subtask();
}

void semcomp_runtime_move_all_sprites_offscreen(void) {
    runtime().routines().register_routine(0x8220, "MoveAllSpritesOffscreen");
    runtime().routines().note_invocation(0x8220);
    runtime().misc_utilities().move_all_sprites_offscreen();
}

void semcomp_runtime_move_sprites_offscreen(void) {
    runtime().routines().register_routine(0x8223, "MoveSpritesOffscreen");
    runtime().routines().note_invocation(0x8223);
    runtime().misc_utilities().move_sprites_offscreen();
}

void semcomp_runtime_get_alternate_palette1(void) {
    runtime().routines().register_routine(0x8643, "GetAlternatePalette1");
    runtime().routines().note_invocation(0x8643);
    runtime().misc_utilities().get_alternate_palette1();
}

void semcomp_runtime_get_m_tile_attrib(void) {
    runtime().routines().register_routine(0xDFB0, "GetMTileAttrib");
    runtime().routines().note_invocation(0xDFB0);
    runtime().misc_utilities().get_m_tile_attrib();
}

void semcomp_runtime_move_six_sprites_offscreen(void) {
    runtime().routines().register_routine(0xE5B3, "MoveSixSpritesOffscreen");
    runtime().routines().note_invocation(0xE5B3);
    runtime().misc_utilities().move_six_sprites_offscreen();
}

void semcomp_runtime_increment_column_pos(void) {
    runtime().routines().register_routine(0x92DB, "IncrementColumnPos");
    runtime().routines().note_invocation(0x92DB);
    runtime().misc_utilities().increment_column_pos();
}

void semcomp_runtime_inc_area_obj_offset(void) {
    runtime().routines().register_routine(0x9589, "IncAreaObjOffset");
    runtime().routines().note_invocation(0x9589);
    runtime().misc_utilities().inc_area_obj_offset();
}

void semcomp_runtime_inc_mode_task__b(void) {
    runtime().routines().register_routine(0x874E, "IncModeTask_B");
    runtime().routines().note_invocation(0x874E);
    runtime().misc_utilities().inc_mode_task__b();
}

// Phase 32 - AudioEngine bulk-port (116 entries across 12 multi-entry bodies + 2 single-entry)
void semcomp_runtime_square1_sfx_handler(void) {
    runtime().routines().register_routine(0xF41B, "Square1SfxHandler");
    runtime().routines().note_invocation(0xF41B);
    runtime().audio_engine().square1_sfx_handler();
}

void semcomp_runtime_square2_sfx_handler(void) {
    runtime().routines().register_routine(0xF57C, "Square2SfxHandler");
    runtime().routines().note_invocation(0xF57C);
    runtime().audio_engine().square2_sfx_handler();
}

void semcomp_runtime_sound_engine(void) {
    runtime().routines().register_routine(0xF2D0, "SoundEngine");
    runtime().routines().note_invocation(0xF2D0);
    runtime().audio_engine().sound_engine();
}

void semcomp_runtime_at_f2d3(void) {
    runtime().routines().register_routine(0xF2D3, "at_f2d3");
    runtime().routines().note_invocation(0xF2D3);
    runtime().audio_engine().at_f2d3();
}

void semcomp_runtime_at_f2ea(void) {
    runtime().routines().register_routine(0xF2EA, "at_f2ea");
    runtime().routines().note_invocation(0xF2EA);
    runtime().audio_engine().at_f2ea();
}

void semcomp_runtime_at_f2f3(void) {
    runtime().routines().register_routine(0xF2F3, "at_f2f3");
    runtime().routines().note_invocation(0xF2F3);
    runtime().audio_engine().at_f2f3();
}

void semcomp_runtime_at_f329(void) {
    runtime().routines().register_routine(0xF329, "at_f329");
    runtime().routines().note_invocation(0xF329);
    runtime().audio_engine().at_f329();
}

void semcomp_runtime_at_f380(void) {
    runtime().routines().register_routine(0xF380, "at_f380");
    runtime().routines().note_invocation(0xF380);
    runtime().audio_engine().at_f380();
}

void semcomp_runtime_at_f367(void) {
    runtime().routines().register_routine(0xF367, "at_f367");
    runtime().routines().note_invocation(0xF367);
    runtime().audio_engine().at_f367();
}

void semcomp_runtime_no_inc_dac(void) {
    runtime().routines().register_routine(0xF377, "NoIncDAC");
    runtime().routines().note_invocation(0xF377);
    runtime().audio_engine().no_inc_dac();
}

void semcomp_runtime_dump_squ1_regs(void) {
    runtime().routines().register_routine(0xF381, "Dump_Squ1_Regs");
    runtime().routines().note_invocation(0xF381);
    runtime().audio_engine().dump_squ1_regs();
}

void semcomp_runtime_at_f384(void) {
    runtime().routines().register_routine(0xF384, "at_f384");
    runtime().routines().note_invocation(0xF384);
    runtime().audio_engine().at_f384();
}

void semcomp_runtime_play_squ1_sfx(void) {
    runtime().routines().register_routine(0xF388, "PlaySqu1Sfx");
    runtime().routines().note_invocation(0xF388);
    runtime().audio_engine().play_squ1_sfx();
}

void semcomp_runtime_at_f38e(void) {
    runtime().routines().register_routine(0xF38E, "at_f38e");
    runtime().routines().note_invocation(0xF38E);
    runtime().audio_engine().at_f38e();
}

void semcomp_runtime_dump_sq2_regs(void) {
    runtime().routines().register_routine(0xF39F, "Dump_Sq2_Regs");
    runtime().routines().note_invocation(0xF39F);
    runtime().audio_engine().dump_sq2_regs();
}

void semcomp_runtime_at_f3a5(void) {
    runtime().routines().register_routine(0xF3A5, "at_f3a5");
    runtime().routines().note_invocation(0xF3A5);
    runtime().audio_engine().at_f3a5();
}

void semcomp_runtime_play_squ2_sfx(void) {
    runtime().routines().register_routine(0xF3A6, "PlaySqu2Sfx");
    runtime().routines().note_invocation(0xF3A6);
    runtime().audio_engine().play_squ2_sfx();
}

void semcomp_runtime_no_p_dwn_l(void) {
    runtime().routines().register_routine(0xF4D1, "NoPDwnL");
    runtime().routines().note_invocation(0xF4D1);
    runtime().audio_engine().no_p_dwn_l();
}

void semcomp_runtime_at_f410(void) {
    runtime().routines().register_routine(0xF410, "at_f410");
    runtime().routines().note_invocation(0xF410);
    runtime().audio_engine().at_f410();
}

void semcomp_runtime_at_f4b0(void) {
    runtime().routines().register_routine(0xF4B0, "at_f4b0");
    runtime().routines().note_invocation(0xF4B0);
    runtime().audio_engine().at_f4b0();
}

void semcomp_runtime_fps2nd(void) {
    runtime().routines().register_routine(0xF3F2, "FPS2nd");
    runtime().routines().note_invocation(0xF3F2);
    runtime().audio_engine().fps2nd();
}

void semcomp_runtime_dmp_jp_fps(void) {
    runtime().routines().register_routine(0xF3F4, "DmpJpFPS");
    runtime().routines().note_invocation(0xF3F4);
    runtime().audio_engine().dmp_jp_fps();
}

void semcomp_runtime_at_f4be(void) {
    runtime().routines().register_routine(0xF4BE, "at_f4be");
    runtime().routines().note_invocation(0xF4BE);
    runtime().audio_engine().at_f4be();
}

void semcomp_runtime_at_f4bf(void) {
    runtime().routines().register_routine(0xF4BF, "at_f4bf");
    runtime().routines().note_invocation(0xF4BF);
    runtime().audio_engine().at_f4bf();
}

void semcomp_runtime_at_f4a5(void) {
    runtime().routines().register_routine(0xF4A5, "at_f4a5");
    runtime().routines().note_invocation(0xF4A5);
    runtime().audio_engine().at_f4a5();
}

void semcomp_runtime_at_f405(void) {
    runtime().routines().register_routine(0xF405, "at_f405");
    runtime().routines().note_invocation(0xF405);
    runtime().audio_engine().at_f405();
}

void semcomp_runtime_at_f486(void) {
    runtime().routines().register_routine(0xF486, "at_f486");
    runtime().routines().note_invocation(0xF486);
    runtime().audio_engine().at_f486();
}

void semcomp_runtime_at_f421(void) {
    runtime().routines().register_routine(0xF421, "at_f421");
    runtime().routines().note_invocation(0xF421);
    runtime().audio_engine().at_f421();
}

void semcomp_runtime_at_f3ee(void) {
    runtime().routines().register_routine(0xF3EE, "at_f3ee");
    runtime().routines().note_invocation(0xF3EE);
    runtime().audio_engine().at_f3ee();
}

void semcomp_runtime_at_f490(void) {
    runtime().routines().register_routine(0xF490, "at_f490");
    runtime().routines().note_invocation(0xF490);
    runtime().audio_engine().at_f490();
}

void semcomp_runtime_at_f462(void) {
    runtime().routines().register_routine(0xF462, "at_f462");
    runtime().routines().note_invocation(0xF462);
    runtime().audio_engine().at_f462();
}

void semcomp_runtime_at_f4a9(void) {
    runtime().routines().register_routine(0xF4A9, "at_f4a9");
    runtime().routines().note_invocation(0xF4A9);
    runtime().audio_engine().at_f4a9();
}

void semcomp_runtime_at_f44c(void) {
    runtime().routines().register_routine(0xF44C, "at_f44c");
    runtime().routines().note_invocation(0xF44C);
    runtime().audio_engine().at_f44c();
}

void semcomp_runtime_play_coin_grab(void) {
    runtime().routines().register_routine(0xF518, "PlayCoinGrab");
    runtime().routines().note_invocation(0xF518);
    runtime().audio_engine().play_coin_grab();
}

void semcomp_runtime_blst_s_jp(void) {
    runtime().routines().register_routine(0xF5D1, "BlstSJp");
    runtime().routines().note_invocation(0xF5D1);
    runtime().audio_engine().blst_s_jp();
}

void semcomp_runtime_grow_item_regs(void) {
    runtime().routines().register_routine(0xF602, "GrowItemRegs");
    runtime().routines().note_invocation(0xF602);
    runtime().audio_engine().grow_item_regs();
}

void semcomp_runtime_n2_tone(void) {
    runtime().routines().register_routine(0xF538, "N2Tone");
    runtime().routines().note_invocation(0xF538);
    runtime().audio_engine().n2_tone();
}

void semcomp_runtime_at_f607(void) {
    runtime().routines().register_routine(0xF607, "at_f607");
    runtime().routines().note_invocation(0xF607);
    runtime().audio_engine().at_f607();
}

void semcomp_runtime_at_f621(void) {
    runtime().routines().register_routine(0xF621, "at_f621");
    runtime().routines().note_invocation(0xF621);
    runtime().audio_engine().at_f621();
}

void semcomp_runtime_at_f5f6(void) {
    runtime().routines().register_routine(0xF5F6, "at_f5f6");
    runtime().routines().note_invocation(0xF5F6);
    runtime().audio_engine().at_f5f6();
}

void semcomp_runtime_play_grow_power_up(void) {
    runtime().routines().register_routine(0xF5FC, "PlayGrowPowerUp");
    runtime().routines().note_invocation(0xF5FC);
    runtime().audio_engine().play_grow_power_up();
}

void semcomp_runtime_at_f624(void) {
    runtime().routines().register_routine(0xF624, "at_f624");
    runtime().routines().note_invocation(0xF624);
    runtime().audio_engine().at_f624();
}

void semcomp_runtime_at_f586(void) {
    runtime().routines().register_routine(0xF586, "at_f586");
    runtime().routines().note_invocation(0xF586);
    runtime().audio_engine().at_f586();
}

void semcomp_runtime_at_f5b2(void) {
    runtime().routines().register_routine(0xF5B2, "at_f5b2");
    runtime().routines().note_invocation(0xF5B2);
    runtime().audio_engine().at_f5b2();
}

void semcomp_runtime_at_f5f8(void) {
    runtime().routines().register_routine(0xF5F8, "at_f5f8");
    runtime().routines().note_invocation(0xF5F8);
    runtime().audio_engine().at_f5f8();
}

void semcomp_runtime_at_f5ed(void) {
    runtime().routines().register_routine(0xF5ED, "at_f5ed");
    runtime().routines().note_invocation(0xF5ED);
    runtime().audio_engine().at_f5ed();
}

void semcomp_runtime_jump_to_dec_length2(void) {
    runtime().routines().register_routine(0xF5C5, "JumpToDecLength2");
    runtime().routines().note_invocation(0xF5C5);
    runtime().audio_engine().jump_to_dec_length2();
}

void semcomp_runtime_el_l_regs(void) {
    runtime().routines().register_routine(0xF5E0, "EL_LRegs");
    runtime().routines().note_invocation(0xF5E0);
    runtime().audio_engine().el_l_regs();
}

void semcomp_runtime_at_f5cf(void) {
    runtime().routines().register_routine(0xF5CF, "at_f5cf");
    runtime().routines().note_invocation(0xF5CF);
    runtime().audio_engine().at_f5cf();
}

void semcomp_runtime_div_l_loop(void) {
    runtime().routines().register_routine(0xF5EC, "DivLLoop");
    runtime().routines().note_invocation(0xF5EC);
    runtime().audio_engine().div_l_loop();
}

void semcomp_runtime_at_f5b9(void) {
    runtime().routines().register_routine(0xF5B9, "at_f5b9");
    runtime().routines().note_invocation(0xF5B9);
    runtime().audio_engine().at_f5b9();
}

void semcomp_runtime_at_f605(void) {
    runtime().routines().register_routine(0xF605, "at_f605");
    runtime().routines().note_invocation(0xF605);
    runtime().audio_engine().at_f605();
}

void semcomp_runtime_c_grab_t_tick_reg_l(void) {
    runtime().routines().register_routine(0xF522, "CGrab_TTickRegL");
    runtime().routines().note_invocation(0xF522);
    runtime().audio_engine().c_grab_t_tick_reg_l();
}

void semcomp_runtime_at_f617(void) {
    runtime().routines().register_routine(0xF617, "at_f617");
    runtime().routines().note_invocation(0xF617);
    runtime().audio_engine().at_f617();
}

void semcomp_runtime_play_brick_shatter(void) {
    runtime().routines().register_routine(0xF63B, "PlayBrickShatter");
    runtime().routines().note_invocation(0xF63B);
    runtime().audio_engine().play_brick_shatter();
}

void semcomp_runtime_decrement_sfx3_length(void) {
    runtime().routines().register_routine(0xF658, "DecrementSfx3Length");
    runtime().routines().note_invocation(0xF658);
    runtime().audio_engine().decrement_sfx3_length();
}

void semcomp_runtime_at_f644(void) {
    runtime().routines().register_routine(0xF644, "at_f644");
    runtime().routines().note_invocation(0xF644);
    runtime().audio_engine().at_f644();
}

void semcomp_runtime_noise_sfx_handler(void) {
    runtime().routines().register_routine(0xF667, "NoiseSfxHandler");
    runtime().routines().note_invocation(0xF667);
    runtime().audio_engine().noise_sfx_handler();
}

void semcomp_runtime_continue_bowser_flame(void) {
    runtime().routines().register_routine(0xF685, "ContinueBowserFlame");
    runtime().routines().note_invocation(0xF685);
    runtime().audio_engine().continue_bowser_flame();
}

void semcomp_runtime_at_f679(void) {
    runtime().routines().register_routine(0xF679, "at_f679");
    runtime().routines().note_invocation(0xF679);
    runtime().audio_engine().at_f679();
}

void semcomp_runtime_at_f68f(void) {
    runtime().routines().register_routine(0xF68F, "at_f68f");
    runtime().routines().note_invocation(0xF68F);
    runtime().audio_engine().at_f68f();
}

void semcomp_runtime_music_handler(void) {
    runtime().routines().register_routine(0xF694, "MusicHandler");
    runtime().routines().note_invocation(0xF694);
    runtime().audio_engine().music_handler();
}

void semcomp_runtime_silent_beat(void) {
    runtime().routines().register_routine(0xF8B9, "SilentBeat");
    runtime().routines().note_invocation(0xF8B9);
    runtime().audio_engine().silent_beat();
}

void semcomp_runtime_at_f7c3(void) {
    runtime().routines().register_routine(0xF7C3, "at_f7c3");
    runtime().routines().note_invocation(0xF7C3);
    runtime().audio_engine().at_f7c3();
}

void semcomp_runtime_at_f860(void) {
    runtime().routines().register_routine(0xF860, "at_f860");
    runtime().routines().note_invocation(0xF860);
    runtime().audio_engine().at_f860();
}

void semcomp_runtime_strong_beat(void) {
    runtime().routines().register_routine(0xF8A9, "StrongBeat");
    runtime().routines().note_invocation(0xF8A9);
    runtime().audio_engine().strong_beat();
}

void semcomp_runtime_find_event_music_header(void) {
    runtime().routines().register_routine(0xF6F1, "FindEventMusicHeader");
    runtime().routines().note_invocation(0xF6F1);
    runtime().audio_engine().find_event_music_header();
}

void semcomp_runtime_at_f80d(void) {
    runtime().routines().register_routine(0xF80D, "at_f80d");
    runtime().routines().note_invocation(0xF80D);
    runtime().audio_engine().at_f80d();
}

void semcomp_runtime_at_f720(void) {
    runtime().routines().register_routine(0xF720, "at_f720");
    runtime().routines().note_invocation(0xF720);
    runtime().audio_engine().at_f720();
}

void semcomp_runtime_at_f710(void) {
    runtime().routines().register_routine(0xF710, "at_f710");
    runtime().routines().note_invocation(0xF710);
    runtime().audio_engine().at_f710();
}

void semcomp_runtime_at_f6a1(void) {
    runtime().routines().register_routine(0xF6A1, "at_f6a1");
    runtime().routines().note_invocation(0xF6A1);
    runtime().audio_engine().at_f6a1();
}

void semcomp_runtime_at_f8ad(void) {
    runtime().routines().register_routine(0xF8AD, "at_f8ad");
    runtime().routines().note_invocation(0xF8AD);
    runtime().audio_engine().at_f8ad();
}

void semcomp_runtime_at_f829(void) {
    runtime().routines().register_routine(0xF829, "at_f829");
    runtime().routines().note_invocation(0xF829);
    runtime().audio_engine().at_f829();
}

void semcomp_runtime_at_f750(void) {
    runtime().routines().register_routine(0xF750, "at_f750");
    runtime().routines().note_invocation(0xF750);
    runtime().audio_engine().at_f750();
}

void semcomp_runtime_at_f6fc(void) {
    runtime().routines().register_routine(0xF6FC, "at_f6fc");
    runtime().routines().note_invocation(0xF6FC);
    runtime().audio_engine().at_f6fc();
}

void semcomp_runtime_at_f7a9(void) {
    runtime().routines().register_routine(0xF7A9, "at_f7a9");
    runtime().routines().note_invocation(0xF7A9);
    runtime().audio_engine().at_f7a9();
}

void semcomp_runtime_death_m_alt_reg(void) {
    runtime().routines().register_routine(0xF810, "DeathMAltReg");
    runtime().routines().note_invocation(0xF810);
    runtime().audio_engine().death_m_alt_reg();
}

void semcomp_runtime_at_f784(void) {
    runtime().routines().register_routine(0xF784, "at_f784");
    runtime().routines().note_invocation(0xF784);
    runtime().audio_engine().at_f784();
}

void semcomp_runtime_at_f885(void) {
    runtime().routines().register_routine(0xF885, "at_f885");
    runtime().routines().note_invocation(0xF885);
    runtime().audio_engine().at_f885();
}

void semcomp_runtime_squ2_note_handler(void) {
    runtime().routines().register_routine(0xF786, "Squ2NoteHandler");
    runtime().routines().note_invocation(0xF786);
    runtime().audio_engine().squ2_note_handler();
}

void semcomp_runtime_at_f7a5(void) {
    runtime().routines().register_routine(0xF7A5, "at_f7a5");
    runtime().routines().note_invocation(0xF7A5);
    runtime().audio_engine().at_f7a5();
}

void semcomp_runtime_at_f7e6(void) {
    runtime().routines().register_routine(0xF7E6, "at_f7e6");
    runtime().routines().note_invocation(0xF7E6);
    runtime().audio_engine().at_f7e6();
}

void semcomp_runtime_at_f7e7(void) {
    runtime().routines().register_routine(0xF7E7, "at_f7e7");
    runtime().routines().note_invocation(0xF7E7);
    runtime().audio_engine().at_f7e7();
}

void semcomp_runtime_at_f8a5(void) {
    runtime().routines().register_routine(0xF8A5, "at_f8a5");
    runtime().routines().note_invocation(0xF8A5);
    runtime().audio_engine().at_f8a5();
}

void semcomp_runtime_at_f7e4(void) {
    runtime().routines().register_routine(0xF7E4, "at_f7e4");
    runtime().routines().note_invocation(0xF7E4);
    runtime().audio_engine().at_f7e4();
}

void semcomp_runtime_misc_squ1_music_tasks(void) {
    runtime().routines().register_routine(0xF7F7, "MiscSqu1MusicTasks");
    runtime().routines().note_invocation(0xF7F7);
    runtime().audio_engine().misc_squ1_music_tasks();
}

void semcomp_runtime_skip_ctrl_l(void) {
    runtime().routines().register_routine(0xF7F1, "SkipCtrlL");
    runtime().routines().note_invocation(0xF7F1);
    runtime().audio_engine().skip_ctrl_l();
}

void semcomp_runtime_load_header(void) {
    runtime().routines().register_routine(0xF6F5, "LoadHeader");
    runtime().routines().note_invocation(0xF6F5);
    runtime().audio_engine().load_header();
}

void semcomp_runtime_fetch_noise_beat_data(void) {
    runtime().routines().register_routine(0xF878, "FetchNoiseBeatData");
    runtime().routines().note_invocation(0xF878);
    runtime().audio_engine().fetch_noise_beat_data();
}

void semcomp_runtime_at_f6b8(void) {
    runtime().routines().register_routine(0xF6B8, "at_f6b8");
    runtime().routines().note_invocation(0xF6B8);
    runtime().audio_engine().at_f6b8();
}

void semcomp_runtime_at_f7fb(void) {
    runtime().routines().register_routine(0xF7FB, "at_f7fb");
    runtime().routines().note_invocation(0xF7FB);
    runtime().audio_engine().at_f7fb();
}

void semcomp_runtime_at_f850(void) {
    runtime().routines().register_routine(0xF850, "at_f850");
    runtime().routines().note_invocation(0xF850);
    runtime().audio_engine().at_f850();
}

void semcomp_runtime_at_f88d(void) {
    runtime().routines().register_routine(0xF88D, "at_f88d");
    runtime().routines().note_invocation(0xF88D);
    runtime().audio_engine().at_f88d();
}

void semcomp_runtime_at_f6b6(void) {
    runtime().routines().register_routine(0xF6B6, "at_f6b6");
    runtime().routines().note_invocation(0xF6B6);
    runtime().audio_engine().at_f6b6();
}

void semcomp_runtime_medi_n(void) {
    runtime().routines().register_routine(0xF864, "MediN");
    runtime().routines().note_invocation(0xF864);
    runtime().audio_engine().medi_n();
}

void semcomp_runtime_at_f862(void) {
    runtime().routines().register_routine(0xF862, "at_f862");
    runtime().routines().note_invocation(0xF862);
    runtime().audio_engine().at_f862();
}

void semcomp_runtime_at_f741(void) {
    runtime().routines().register_routine(0xF741, "at_f741");
    runtime().routines().note_invocation(0xF741);
    runtime().audio_engine().at_f741();
}

void semcomp_runtime_at_f844(void) {
    runtime().routines().register_routine(0xF844, "at_f844");
    runtime().routines().note_invocation(0xF844);
    runtime().audio_engine().at_f844();
}

void semcomp_runtime_at_f807(void) {
    runtime().routines().register_routine(0xF807, "at_f807");
    runtime().routines().note_invocation(0xF807);
    runtime().audio_engine().at_f807();
}

void semcomp_runtime_at_f706(void) {
    runtime().routines().register_routine(0xF706, "at_f706");
    runtime().routines().note_invocation(0xF706);
    runtime().audio_engine().at_f706();
}

void semcomp_runtime_at_f729(void) {
    runtime().routines().register_routine(0xF729, "at_f729");
    runtime().routines().note_invocation(0xF729);
    runtime().audio_engine().at_f729();
}

void semcomp_runtime_alternate_length_handler(void) {
    runtime().routines().register_routine(0xF8C5, "AlternateLengthHandler");
    runtime().routines().note_invocation(0xF8C5);
    runtime().audio_engine().alternate_length_handler();
}

void semcomp_runtime_at_f8d0(void) {
    runtime().routines().register_routine(0xF8D0, "at_f8d0");
    runtime().routines().note_invocation(0xF8D0);
    runtime().audio_engine().at_f8d0();
}

void semcomp_runtime_at_f8c9(void) {
    runtime().routines().register_routine(0xF8C9, "at_f8c9");
    runtime().routines().note_invocation(0xF8C9);
    runtime().audio_engine().at_f8c9();
}

void semcomp_runtime_at_f8ca(void) {
    runtime().routines().register_routine(0xF8CA, "at_f8ca");
    runtime().routines().note_invocation(0xF8CA);
    runtime().audio_engine().at_f8ca();
}

void semcomp_runtime_at_f8c6(void) {
    runtime().routines().register_routine(0xF8C6, "at_f8c6");
    runtime().routines().note_invocation(0xF8C6);
    runtime().audio_engine().at_f8c6();
}

void semcomp_runtime_at_f8ce(void) {
    runtime().routines().register_routine(0xF8CE, "at_f8ce");
    runtime().routines().note_invocation(0xF8CE);
    runtime().audio_engine().at_f8ce();
}

void semcomp_runtime_at_f8c8(void) {
    runtime().routines().register_routine(0xF8C8, "at_f8c8");
    runtime().routines().note_invocation(0xF8C8);
    runtime().audio_engine().at_f8c8();
}

void semcomp_runtime_load_control_regs(void) {
    runtime().routines().register_routine(0xF8D8, "LoadControlRegs");
    runtime().routines().note_invocation(0xF8D8);
    runtime().audio_engine().load_control_regs();
}

void semcomp_runtime_at_f8f1(void) {
    runtime().routines().register_routine(0xF8F1, "at_f8f1");
    runtime().routines().note_invocation(0xF8F1);
    runtime().audio_engine().at_f8f1();
}

void semcomp_runtime_at_f8e7(void) {
    runtime().routines().register_routine(0xF8E7, "at_f8e7");
    runtime().routines().note_invocation(0xF8E7);
    runtime().audio_engine().at_f8e7();
}

void semcomp_runtime_load_envelope_data(void) {
    runtime().routines().register_routine(0xF8F4, "LoadEnvelopeData");
    runtime().routines().note_invocation(0xF8F4);
    runtime().audio_engine().load_envelope_data();
}

void semcomp_runtime_at_f8fb(void) {
    runtime().routines().register_routine(0xF8FB, "at_f8fb");
    runtime().routines().note_invocation(0xF8FB);
    runtime().audio_engine().at_f8fb();
}

void semcomp_runtime_at_f90c(void) {
    runtime().routines().register_routine(0xF90C, "at_f90c");
    runtime().routines().note_invocation(0xF90C);
    runtime().audio_engine().at_f90c();
}

void semcomp_runtime_at_f903(void) {
    runtime().routines().register_routine(0xF903, "at_f903");
    runtime().routines().note_invocation(0xF903);
    runtime().audio_engine().at_f903();
}

void semcomp_runtime_at_f905(void) {
    runtime().routines().register_routine(0xF905, "at_f905");
    runtime().routines().note_invocation(0xF905);
    runtime().audio_engine().at_f905();
}

// Phase 33 - EnemyEngine bulk-port (38 multi-entry bodies, 724 entries)
void semcomp_runtime_enemies_and_loops_core(void) {
    runtime().routines().register_routine(0xC047, "EnemiesAndLoopsCore");
    runtime().routines().note_invocation(0xC047);
    runtime().enemy_engine().enemies_and_loops_core();
}

void semcomp_runtime_at_c058(void) {
    runtime().routines().register_routine(0xC058, "at_c058");
    runtime().routines().note_invocation(0xC058);
    runtime().enemy_engine().at_c058();
}

void semcomp_runtime_at_c04e(void) {
    runtime().routines().register_routine(0xC04E, "at_c04e");
    runtime().routines().note_invocation(0xC04E);
    runtime().enemy_engine().at_c04e();
}

void semcomp_runtime_at_c04d(void) {
    runtime().routines().register_routine(0xC04D, "at_c04d");
    runtime().routines().note_invocation(0xC04D);
    runtime().enemy_engine().at_c04d();
}

void semcomp_runtime_exec_game_loopback(void) {
    runtime().routines().register_routine(0xC08C, "ExecGameLoopback");
    runtime().routines().note_invocation(0xC08C);
    runtime().enemy_engine().exec_game_loopback();
}

void semcomp_runtime_at_c0c8(void) {
    runtime().routines().register_routine(0xC0C8, "at_c0c8");
    runtime().routines().note_invocation(0xC0C8);
    runtime().enemy_engine().at_c0c8();
}

void semcomp_runtime_at_c0a0(void) {
    runtime().routines().register_routine(0xC0A0, "at_c0a0");
    runtime().routines().note_invocation(0xC0A0);
    runtime().enemy_engine().at_c0a0();
}

void semcomp_runtime_at_c0b7(void) {
    runtime().routines().register_routine(0xC0B7, "at_c0b7");
    runtime().routines().note_invocation(0xC0B7);
    runtime().enemy_engine().at_c0b7();
}

void semcomp_runtime_at_c0c2(void) {
    runtime().routines().register_routine(0xC0C2, "at_c0c2");
    runtime().routines().note_invocation(0xC0C2);
    runtime().enemy_engine().at_c0c2();
}

void semcomp_runtime_at_c0a9(void) {
    runtime().routines().register_routine(0xC0A9, "at_c0a9");
    runtime().routines().note_invocation(0xC0A9);
    runtime().enemy_engine().at_c0a9();
}

void semcomp_runtime_at_c0a8(void) {
    runtime().routines().register_routine(0xC0A8, "at_c0a8");
    runtime().routines().note_invocation(0xC0A8);
    runtime().enemy_engine().at_c0a8();
}

void semcomp_runtime_proc_loop_command(void) {
    runtime().routines().register_routine(0xC0CC, "ProcLoopCommand");
    runtime().routines().note_invocation(0xC0CC);
    runtime().enemy_engine().proc_loop_command();
}

void semcomp_runtime_at_c0e9(void) {
    runtime().routines().register_routine(0xC0E9, "at_c0e9");
    runtime().routines().note_invocation(0xC0E9);
    runtime().enemy_engine().at_c0e9();
}

void semcomp_runtime_at_c0e1(void) {
    runtime().routines().register_routine(0xC0E1, "at_c0e1");
    runtime().routines().note_invocation(0xC0E1);
    runtime().enemy_engine().at_c0e1();
}

void semcomp_runtime_at_c1be(void) {
    runtime().routines().register_routine(0xC1BE, "at_c1be");
    runtime().routines().note_invocation(0xC1BE);
    runtime().enemy_engine().at_c1be();
}

void semcomp_runtime_at_c0f0(void) {
    runtime().routines().register_routine(0xC0F0, "at_c0f0");
    runtime().routines().note_invocation(0xC0F0);
    runtime().enemy_engine().at_c0f0();
}

void semcomp_runtime_at_c14d(void) {
    runtime().routines().register_routine(0xC14D, "at_c14d");
    runtime().routines().note_invocation(0xC14D);
    runtime().enemy_engine().at_c14d();
}

void semcomp_runtime_at_c0cf(void) {
    runtime().routines().register_routine(0xC0CF, "at_c0cf");
    runtime().routines().note_invocation(0xC0CF);
    runtime().enemy_engine().at_c0cf();
}

void semcomp_runtime_at_c18e(void) {
    runtime().routines().register_routine(0xC18E, "at_c18e");
    runtime().routines().note_invocation(0xC18E);
    runtime().enemy_engine().at_c18e();
}

void semcomp_runtime_at_c1ae(void) {
    runtime().routines().register_routine(0xC1AE, "at_c1ae");
    runtime().routines().note_invocation(0xC1AE);
    runtime().enemy_engine().at_c1ae();
}

void semcomp_runtime_at_c219(void) {
    runtime().routines().register_routine(0xC219, "at_c219");
    runtime().routines().note_invocation(0xC219);
    runtime().enemy_engine().at_c219();
}

void semcomp_runtime_find_loop(void) {
    runtime().routines().register_routine(0xC0D8, "FindLoop");
    runtime().routines().note_invocation(0xC0D8);
    runtime().enemy_engine().find_loop();
}

void semcomp_runtime_at_c242(void) {
    runtime().routines().register_routine(0xC242, "at_c242");
    runtime().routines().note_invocation(0xC242);
    runtime().enemy_engine().at_c242();
}

void semcomp_runtime_at_c141(void) {
    runtime().routines().register_routine(0xC141, "at_c141");
    runtime().routines().note_invocation(0xC141);
    runtime().enemy_engine().at_c141();
}

void semcomp_runtime_at_c124(void) {
    runtime().routines().register_routine(0xC124, "at_c124");
    runtime().routines().note_invocation(0xC124);
    runtime().enemy_engine().at_c124();
}

void semcomp_runtime_do_group(void) {
    runtime().routines().register_routine(0xC22E, "DoGroup");
    runtime().routines().note_invocation(0xC22E);
    runtime().enemy_engine().do_group();
}

void semcomp_runtime_at_c20e(void) {
    runtime().routines().register_routine(0xC20E, "at_c20e");
    runtime().routines().note_invocation(0xC20E);
    runtime().enemy_engine().at_c20e();
}

void semcomp_runtime_at_c21e(void) {
    runtime().routines().register_routine(0xC21E, "at_c21e");
    runtime().routines().note_invocation(0xC21E);
    runtime().enemy_engine().at_c21e();
}

void semcomp_runtime_at_c213(void) {
    runtime().routines().register_routine(0xC213, "at_c213");
    runtime().routines().note_invocation(0xC213);
    runtime().enemy_engine().at_c213();
}

void semcomp_runtime_wrong_chk(void) {
    runtime().routines().register_routine(0xC115, "WrongChk");
    runtime().routines().note_invocation(0xC115);
    runtime().enemy_engine().wrong_chk();
}

void semcomp_runtime_inc_m_loop(void) {
    runtime().routines().register_routine(0xC102, "IncMLoop");
    runtime().routines().note_invocation(0xC102);
    runtime().enemy_engine().inc_m_loop();
}

void semcomp_runtime_at_c0d6(void) {
    runtime().routines().register_routine(0xC0D6, "at_c0d6");
    runtime().routines().note_invocation(0xC0D6);
    runtime().enemy_engine().at_c0d6();
}

void semcomp_runtime_at_c0ff(void) {
    runtime().routines().register_routine(0xC0FF, "at_c0ff");
    runtime().routines().note_invocation(0xC0FF);
    runtime().enemy_engine().at_c0ff();
}

void semcomp_runtime_at_c15d(void) {
    runtime().routines().register_routine(0xC15D, "at_c15d");
    runtime().routines().note_invocation(0xC15D);
    runtime().enemy_engine().at_c15d();
}

void semcomp_runtime_checkpoint_enemy_id(void) {
    runtime().routines().register_routine(0xC26C, "CheckpointEnemyID");
    runtime().routines().note_invocation(0xC26C);
    runtime().enemy_engine().checkpoint_enemy_id();
}

void semcomp_runtime_no_init_code(void) {
    runtime().routines().register_routine(0xC2F0, "NoInitCode");
    runtime().routines().note_invocation(0xC2F0);
    runtime().enemy_engine().no_init_code();
}

void semcomp_runtime_init_podoboo(void) {
    runtime().routines().register_routine(0xC2F7, "InitPodoboo");
    runtime().routines().note_invocation(0xC2F7);
    runtime().enemy_engine().init_podoboo();
}

void semcomp_runtime_at_c304(void) {
    runtime().routines().register_routine(0xC304, "at_c304");
    runtime().routines().note_invocation(0xC304);
    runtime().enemy_engine().at_c304();
}

void semcomp_runtime_at_c302(void) {
    runtime().routines().register_routine(0xC302, "at_c302");
    runtime().routines().note_invocation(0xC302);
    runtime().enemy_engine().at_c302();
}

void semcomp_runtime_at_c301(void) {
    runtime().routines().register_routine(0xC301, "at_c301");
    runtime().routines().note_invocation(0xC301);
    runtime().enemy_engine().at_c301();
}

void semcomp_runtime_init_retainer_obj(void) {
    runtime().routines().register_routine(0xC307, "InitRetainerObj");
    runtime().routines().note_invocation(0xC307);
    runtime().enemy_engine().init_retainer_obj();
}

void semcomp_runtime_at_c30b(void) {
    runtime().routines().register_routine(0xC30B, "at_c30b");
    runtime().routines().note_invocation(0xC30B);
    runtime().enemy_engine().at_c30b();
}

void semcomp_runtime_init_red_koopa(void) {
    runtime().routines().register_routine(0xC31E, "InitRedKoopa");
    runtime().routines().note_invocation(0xC31E);
    runtime().enemy_engine().init_red_koopa();
}

void semcomp_runtime_at_c321(void) {
    runtime().routines().register_routine(0xC321, "at_c321");
    runtime().routines().note_invocation(0xC321);
    runtime().enemy_engine().at_c321();
}

void semcomp_runtime_init_bloober(void) {
    runtime().routines().register_routine(0xC342, "InitBloober");
    runtime().routines().note_invocation(0xC342);
    runtime().enemy_engine().init_bloober();
}

void semcomp_runtime_at_c365(void) {
    runtime().routines().register_routine(0xC365, "at_c365");
    runtime().routines().note_invocation(0xC365);
    runtime().enemy_engine().at_c365();
}

void semcomp_runtime_at_c367(void) {
    runtime().routines().register_routine(0xC367, "at_c367");
    runtime().routines().note_invocation(0xC367);
    runtime().enemy_engine().at_c367();
}

void semcomp_runtime_lakitu_and_spiny_handler(void) {
    runtime().routines().register_routine(0xC3A4, "LakituAndSpinyHandler");
    runtime().routines().note_invocation(0xC3A4);
    runtime().enemy_engine().lakitu_and_spiny_handler();
}

void semcomp_runtime_chp_chp_ex(void) {
    runtime().routines().register_routine(0xC44E, "ChpChpEx");
    runtime().routines().note_invocation(0xC44E);
    runtime().enemy_engine().chp_chp_ex();
}

void semcomp_runtime_at_c40a(void) {
    runtime().routines().register_routine(0xC40A, "at_c40a");
    runtime().routines().note_invocation(0xC40A);
    runtime().enemy_engine().at_c40a();
}

void semcomp_runtime_at_c3d1(void) {
    runtime().routines().register_routine(0xC3D1, "at_c3d1");
    runtime().routines().note_invocation(0xC3D1);
    runtime().enemy_engine().at_c3d1();
}

void semcomp_runtime_dif_loop(void) {
    runtime().routines().register_routine(0xC40F, "DifLoop");
    runtime().routines().note_invocation(0xC40F);
    runtime().enemy_engine().dif_loop();
}

void semcomp_runtime_at_c420(void) {
    runtime().routines().register_routine(0xC420, "at_c420");
    runtime().routines().note_invocation(0xC420);
    runtime().enemy_engine().at_c420();
}

void semcomp_runtime_chk_no_en(void) {
    runtime().routines().register_routine(0xC3CA, "ChkNoEn");
    runtime().routines().note_invocation(0xC3CA);
    runtime().enemy_engine().chk_no_en();
}

void semcomp_runtime_at_c3c4(void) {
    runtime().routines().register_routine(0xC3C4, "at_c3c4");
    runtime().routines().note_invocation(0xC3C4);
    runtime().enemy_engine().at_c3c4();
}

void semcomp_runtime_at_c424(void) {
    runtime().routines().register_routine(0xC424, "at_c424");
    runtime().routines().note_invocation(0xC424);
    runtime().enemy_engine().at_c424();
}

void semcomp_runtime_at_c402(void) {
    runtime().routines().register_routine(0xC402, "at_c402");
    runtime().routines().note_invocation(0xC402);
    runtime().enemy_engine().at_c402();
}

void semcomp_runtime_at_c3b9(void) {
    runtime().routines().register_routine(0xC3B9, "at_c3b9");
    runtime().routines().note_invocation(0xC3B9);
    runtime().enemy_engine().at_c3b9();
}

void semcomp_runtime_at_c416(void) {
    runtime().routines().register_routine(0xC416, "at_c416");
    runtime().routines().note_invocation(0xC416);
    runtime().enemy_engine().at_c416();
}

void semcomp_runtime_at_c40d(void) {
    runtime().routines().register_routine(0xC40D, "at_c40d");
    runtime().routines().note_invocation(0xC40D);
    runtime().enemy_engine().at_c40d();
}

void semcomp_runtime_at_c412(void) {
    runtime().routines().register_routine(0xC412, "at_c412");
    runtime().routines().note_invocation(0xC412);
    runtime().enemy_engine().at_c412();
}

void semcomp_runtime_at_c442(void) {
    runtime().routines().register_routine(0xC442, "at_c442");
    runtime().routines().note_invocation(0xC442);
    runtime().enemy_engine().at_c442();
}

void semcomp_runtime_chk_lak(void) {
    runtime().routines().register_routine(0xC3B4, "ChkLak");
    runtime().routines().note_invocation(0xC3B4);
    runtime().enemy_engine().chk_lak();
}

void semcomp_runtime_at_c3c1(void) {
    runtime().routines().register_routine(0xC3C1, "at_c3c1");
    runtime().routines().note_invocation(0xC3C1);
    runtime().enemy_engine().at_c3c1();
}

void semcomp_runtime_at_c3fd(void) {
    runtime().routines().register_routine(0xC3FD, "at_c3fd");
    runtime().routines().note_invocation(0xC3FD);
    runtime().enemy_engine().at_c3fd();
}

void semcomp_runtime_init_long_firebar(void) {
    runtime().routines().register_routine(0xC459, "InitLongFirebar");
    runtime().routines().note_invocation(0xC459);
    runtime().enemy_engine().init_long_firebar();
}

void semcomp_runtime_at_c47d(void) {
    runtime().routines().register_routine(0xC47D, "at_c47d");
    runtime().routines().note_invocation(0xC47D);
    runtime().enemy_engine().at_c47d();
}

void semcomp_runtime_init_flying_cheep_cheep(void) {
    runtime().routines().register_routine(0xC4A8, "InitFlyingCheepCheep");
    runtime().routines().note_invocation(0xC4A8);
    runtime().enemy_engine().init_flying_cheep_cheep();
}

void semcomp_runtime_at_c511(void) {
    runtime().routines().register_routine(0xC511, "at_c511");
    runtime().routines().note_invocation(0xC511);
    runtime().enemy_engine().at_c511();
}

void semcomp_runtime_at_c500(void) {
    runtime().routines().register_routine(0xC500, "at_c500");
    runtime().routines().note_invocation(0xC500);
    runtime().enemy_engine().at_c500();
}

void semcomp_runtime_at_c504(void) {
    runtime().routines().register_routine(0xC504, "at_c504");
    runtime().routines().note_invocation(0xC504);
    runtime().enemy_engine().at_c504();
}

void semcomp_runtime_at_c4ad(void) {
    runtime().routines().register_routine(0xC4AD, "at_c4ad");
    runtime().routines().note_invocation(0xC4AD);
    runtime().enemy_engine().at_c4ad();
}

void semcomp_runtime_at_c4fc(void) {
    runtime().routines().register_routine(0xC4FC, "at_c4fc");
    runtime().routines().note_invocation(0xC4FC);
    runtime().enemy_engine().at_c4fc();
}

void semcomp_runtime_at_c4fd(void) {
    runtime().routines().register_routine(0xC4FD, "at_c4fd");
    runtime().routines().note_invocation(0xC4FD);
    runtime().enemy_engine().at_c4fd();
}

void semcomp_runtime_at_c4ca(void) {
    runtime().routines().register_routine(0xC4CA, "at_c4ca");
    runtime().routines().note_invocation(0xC4CA);
    runtime().enemy_engine().at_c4ca();
}

void semcomp_runtime_at_c502(void) {
    runtime().routines().register_routine(0xC502, "at_c502");
    runtime().routines().note_invocation(0xC502);
    runtime().enemy_engine().at_c502();
}

void semcomp_runtime_at_c508(void) {
    runtime().routines().register_routine(0xC508, "at_c508");
    runtime().routines().note_invocation(0xC508);
    runtime().enemy_engine().at_c508();
}

void semcomp_runtime_at_c4b0(void) {
    runtime().routines().register_routine(0xC4B0, "at_c4b0");
    runtime().routines().note_invocation(0xC4B0);
    runtime().enemy_engine().at_c4b0();
}

void semcomp_runtime_at_c521(void) {
    runtime().routines().register_routine(0xC521, "at_c521");
    runtime().routines().note_invocation(0xC521);
    runtime().enemy_engine().at_c521();
}

void semcomp_runtime_at_c4d1(void) {
    runtime().routines().register_routine(0xC4D1, "at_c4d1");
    runtime().routines().note_invocation(0xC4D1);
    runtime().enemy_engine().at_c4d1();
}

void semcomp_runtime_at_c51f(void) {
    runtime().routines().register_routine(0xC51F, "at_c51f");
    runtime().routines().note_invocation(0xC51F);
    runtime().enemy_engine().at_c51f();
}

void semcomp_runtime_at_c506(void) {
    runtime().routines().register_routine(0xC506, "at_c506");
    runtime().routines().note_invocation(0xC506);
    runtime().enemy_engine().at_c506();
}

void semcomp_runtime_at_c50c(void) {
    runtime().routines().register_routine(0xC50C, "at_c50c");
    runtime().routines().note_invocation(0xC50C);
    runtime().enemy_engine().at_c50c();
}

void semcomp_runtime_at_c533(void) {
    runtime().routines().register_routine(0xC533, "at_c533");
    runtime().routines().note_invocation(0xC533);
    runtime().enemy_engine().at_c533();
}

void semcomp_runtime_at_c516(void) {
    runtime().routines().register_routine(0xC516, "at_c516");
    runtime().routines().note_invocation(0xC516);
    runtime().enemy_engine().at_c516();
}

void semcomp_runtime_at_c518(void) {
    runtime().routines().register_routine(0xC518, "at_c518");
    runtime().routines().note_invocation(0xC518);
    runtime().enemy_engine().at_c518();
}

void semcomp_runtime_init_bowser(void) {
    runtime().routines().register_routine(0xC549, "InitBowser");
    runtime().routines().note_invocation(0xC549);
    runtime().enemy_engine().init_bowser();
}

void semcomp_runtime_at_c56d(void) {
    runtime().routines().register_routine(0xC56D, "at_c56d");
    runtime().routines().note_invocation(0xC56D);
    runtime().enemy_engine().at_c56d();
}

void semcomp_runtime_at_c54c(void) {
    runtime().routines().register_routine(0xC54C, "at_c54c");
    runtime().routines().note_invocation(0xC54C);
    runtime().enemy_engine().at_c54c();
}

void semcomp_runtime_at_c563(void) {
    runtime().routines().register_routine(0xC563, "at_c563");
    runtime().routines().note_invocation(0xC563);
    runtime().enemy_engine().at_c563();
}

void semcomp_runtime_duplicate_enemy_obj(void) {
    runtime().routines().register_routine(0xC575, "DuplicateEnemyObj");
    runtime().routines().note_invocation(0xC575);
    runtime().enemy_engine().duplicate_enemy_obj();
}

void semcomp_runtime_flm_ex(void) {
    runtime().routines().register_routine(0xC59C, "FlmEx");
    runtime().routines().note_invocation(0xC59C);
    runtime().enemy_engine().flm_ex();
}

void semcomp_runtime_at_c588(void) {
    runtime().routines().register_routine(0xC588, "at_c588");
    runtime().routines().note_invocation(0xC588);
    runtime().enemy_engine().at_c588();
}

void semcomp_runtime_at_c586(void) {
    runtime().routines().register_routine(0xC586, "at_c586");
    runtime().routines().note_invocation(0xC586);
    runtime().enemy_engine().at_c586();
}

void semcomp_runtime_init_bowser_flame(void) {
    runtime().routines().register_routine(0xC5A3, "InitBowserFlame");
    runtime().routines().note_invocation(0xC5A3);
    runtime().enemy_engine().init_bowser_flame();
}

void semcomp_runtime_at_c5cf(void) {
    runtime().routines().register_routine(0xC5CF, "at_c5cf");
    runtime().routines().note_invocation(0xC5CF);
    runtime().enemy_engine().at_c5cf();
}

void semcomp_runtime_at_c604(void) {
    runtime().routines().register_routine(0xC604, "at_c604");
    runtime().routines().note_invocation(0xC604);
    runtime().enemy_engine().at_c604();
}

void semcomp_runtime_set_fr_t(void) {
    runtime().routines().register_routine(0xC5C9, "SetFrT");
    runtime().routines().note_invocation(0xC5C9);
    runtime().enemy_engine().set_fr_t();
}

void semcomp_runtime_at_c606(void) {
    runtime().routines().register_routine(0xC606, "at_c606");
    runtime().routines().note_invocation(0xC606);
    runtime().enemy_engine().at_c606();
}

void semcomp_runtime_at_c609(void) {
    runtime().routines().register_routine(0xC609, "at_c609");
    runtime().routines().note_invocation(0xC609);
    runtime().enemy_engine().at_c609();
}

void semcomp_runtime_at_c5c6(void) {
    runtime().routines().register_routine(0xC5C6, "at_c5c6");
    runtime().routines().note_invocation(0xC5C6);
    runtime().enemy_engine().at_c5c6();
}

void semcomp_runtime_at_c5c7(void) {
    runtime().routines().register_routine(0xC5C7, "at_c5c7");
    runtime().routines().note_invocation(0xC5C7);
    runtime().enemy_engine().at_c5c7();
}

void semcomp_runtime_at_c5be(void) {
    runtime().routines().register_routine(0xC5BE, "at_c5be");
    runtime().routines().note_invocation(0xC5BE);
    runtime().enemy_engine().at_c5be();
}

void semcomp_runtime_at_c613(void) {
    runtime().routines().register_routine(0xC613, "at_c613");
    runtime().routines().note_invocation(0xC613);
    runtime().enemy_engine().at_c613();
}

void semcomp_runtime_set_mf(void) {
    runtime().routines().register_routine(0xC614, "SetMF");
    runtime().routines().note_invocation(0xC614);
    runtime().enemy_engine().set_mf();
}

void semcomp_runtime_at_c5ad(void) {
    runtime().routines().register_routine(0xC5AD, "at_c5ad");
    runtime().routines().note_invocation(0xC5AD);
    runtime().enemy_engine().at_c5ad();
}

void semcomp_runtime_at_c624(void) {
    runtime().routines().register_routine(0xC624, "at_c624");
    runtime().routines().note_invocation(0xC624);
    runtime().enemy_engine().at_c624();
}

void semcomp_runtime_bullet_bill_cheep_cheep(void) {
    runtime().routines().register_routine(0xC69C, "BulletBillCheepCheep");
    runtime().routines().note_invocation(0xC69C);
    runtime().enemy_engine().bullet_bill_cheep_cheep();
}

void semcomp_runtime_at_c6d7(void) {
    runtime().routines().register_routine(0xC6D7, "at_c6d7");
    runtime().routines().note_invocation(0xC6D7);
    runtime().enemy_engine().at_c6d7();
}

void semcomp_runtime_at_c6c8(void) {
    runtime().routines().register_routine(0xC6C8, "at_c6c8");
    runtime().routines().note_invocation(0xC6C8);
    runtime().enemy_engine().at_c6c8();
}

void semcomp_runtime_at_c6b1(void) {
    runtime().routines().register_routine(0xC6B1, "at_c6b1");
    runtime().routines().note_invocation(0xC6B1);
    runtime().enemy_engine().at_c6b1();
}

void semcomp_runtime_at_c6ec(void) {
    runtime().routines().register_routine(0xC6EC, "at_c6ec");
    runtime().routines().note_invocation(0xC6EC);
    runtime().enemy_engine().at_c6ec();
}

void semcomp_runtime_set17_id(void) {
    runtime().routines().register_routine(0xC6C3, "Set17ID");
    runtime().routines().note_invocation(0xC6C3);
    runtime().enemy_engine().set17_id();
}

void semcomp_runtime_at_c74c(void) {
    runtime().routines().register_routine(0xC74C, "at_c74c");
    runtime().routines().note_invocation(0xC74C);
    runtime().enemy_engine().at_c74c();
}

void semcomp_runtime_at_c75d(void) {
    runtime().routines().register_routine(0xC75D, "at_c75d");
    runtime().routines().note_invocation(0xC75D);
    runtime().enemy_engine().at_c75d();
}

void semcomp_runtime_at_c700(void) {
    runtime().routines().register_routine(0xC700, "at_c700");
    runtime().routines().note_invocation(0xC700);
    runtime().enemy_engine().at_c700();
}

void semcomp_runtime_at_c725(void) {
    runtime().routines().register_routine(0xC725, "at_c725");
    runtime().routines().note_invocation(0xC725);
    runtime().enemy_engine().at_c725();
}

void semcomp_runtime_at_c741(void) {
    runtime().routines().register_routine(0xC741, "at_c741");
    runtime().routines().note_invocation(0xC741);
    runtime().enemy_engine().at_c741();
}

void semcomp_runtime_at_c738(void) {
    runtime().routines().register_routine(0xC738, "at_c738");
    runtime().routines().note_invocation(0xC738);
    runtime().enemy_engine().at_c738();
}

void semcomp_runtime_at_c720(void) {
    runtime().routines().register_routine(0xC720, "at_c720");
    runtime().routines().note_invocation(0xC720);
    runtime().enemy_engine().at_c720();
}

void semcomp_runtime_at_c77a(void) {
    runtime().routines().register_routine(0xC77A, "at_c77a");
    runtime().routines().note_invocation(0xC77A);
    runtime().enemy_engine().at_c77a();
}

void semcomp_runtime_cnt_grp(void) {
    runtime().routines().register_routine(0xC74D, "CntGrp");
    runtime().routines().note_invocation(0xC74D);
    runtime().enemy_engine().cnt_grp();
}

void semcomp_runtime_at_c772(void) {
    runtime().routines().register_routine(0xC772, "at_c772");
    runtime().routines().note_invocation(0xC772);
    runtime().enemy_engine().at_c772();
}

void semcomp_runtime_at_c734(void) {
    runtime().routines().register_routine(0xC734, "at_c734");
    runtime().routines().note_invocation(0xC734);
    runtime().enemy_engine().at_c734();
}

void semcomp_runtime_at_c6ce(void) {
    runtime().routines().register_routine(0xC6CE, "at_c6ce");
    runtime().routines().note_invocation(0xC6CE);
    runtime().enemy_engine().at_c6ce();
}

void semcomp_runtime_bb_s_loop(void) {
    runtime().routines().register_routine(0xC6FF, "BB_SLoop");
    runtime().routines().note_invocation(0xC6FF);
    runtime().enemy_engine().bb_s_loop();
}

void semcomp_runtime_gr_loop(void) {
    runtime().routines().register_routine(0xC750, "GrLoop");
    runtime().routines().note_invocation(0xC750);
    runtime().enemy_engine().gr_loop();
}

void semcomp_runtime_init_piranha_plant(void) {
    runtime().routines().register_routine(0xC787, "InitPiranhaPlant");
    runtime().routines().note_invocation(0xC787);
    runtime().enemy_engine().init_piranha_plant();
}

void semcomp_runtime_at_c78c(void) {
    runtime().routines().register_routine(0xC78C, "at_c78c");
    runtime().routines().note_invocation(0xC78C);
    runtime().enemy_engine().at_c78c();
}

void semcomp_runtime_init_enemy_frenzy(void) {
    runtime().routines().register_routine(0xC7A0, "InitEnemyFrenzy");
    runtime().routines().note_invocation(0xC7A0);
    runtime().enemy_engine().init_enemy_frenzy();
}

void semcomp_runtime_at_c7c9(void) {
    runtime().routines().register_routine(0xC7C9, "at_c7c9");
    runtime().routines().note_invocation(0xC7C9);
    runtime().enemy_engine().at_c7c9();
}

void semcomp_runtime_end_frenzy(void) {
    runtime().routines().register_routine(0xC7B8, "EndFrenzy");
    runtime().routines().note_invocation(0xC7B8);
    runtime().enemy_engine().end_frenzy();
}

void semcomp_runtime_lakitu_chk(void) {
    runtime().routines().register_routine(0xC7BA, "LakituChk");
    runtime().routines().note_invocation(0xC7BA);
    runtime().enemy_engine().lakitu_chk();
}

void semcomp_runtime_init_bal_platform(void) {
    runtime().routines().register_routine(0xC7DF, "InitBalPlatform");
    runtime().routines().note_invocation(0xC7DF);
    runtime().enemy_engine().init_bal_platform();
}

void semcomp_runtime_at_c808(void) {
    runtime().routines().register_routine(0xC808, "at_c808");
    runtime().routines().note_invocation(0xC808);
    runtime().enemy_engine().at_c808();
}

void semcomp_runtime_at_c805(void) {
    runtime().routines().register_routine(0xC805, "at_c805");
    runtime().routines().note_invocation(0xC805);
    runtime().enemy_engine().at_c805();
}

void semcomp_runtime_at_c800(void) {
    runtime().routines().register_routine(0xC800, "at_c800");
    runtime().routines().note_invocation(0xC800);
    runtime().enemy_engine().at_c800();
}

void semcomp_runtime_at_c7ef(void) {
    runtime().routines().register_routine(0xC7EF, "at_c7ef");
    runtime().routines().note_invocation(0xC7EF);
    runtime().enemy_engine().at_c7ef();
}

void semcomp_runtime_at_c7f7(void) {
    runtime().routines().register_routine(0xC7F7, "at_c7f7");
    runtime().routines().note_invocation(0xC7F7);
    runtime().enemy_engine().at_c7f7();
}

void semcomp_runtime_at_c7ff(void) {
    runtime().routines().register_routine(0xC7FF, "at_c7ff");
    runtime().routines().note_invocation(0xC7FF);
    runtime().enemy_engine().at_c7ff();
}

void semcomp_runtime_init_hori_platform(void) {
    runtime().routines().register_routine(0xC80B, "InitHoriPlatform");
    runtime().routines().note_invocation(0xC80B);
    runtime().enemy_engine().init_hori_platform();
}

void semcomp_runtime_at_c80f(void) {
    runtime().routines().register_routine(0xC80F, "at_c80f");
    runtime().routines().note_invocation(0xC80F);
    runtime().enemy_engine().at_c80f();
}

void semcomp_runtime_at_c80d(void) {
    runtime().routines().register_routine(0xC80D, "at_c80d");
    runtime().routines().note_invocation(0xC80D);
    runtime().enemy_engine().at_c80d();
}

void semcomp_runtime_init_vert_platform(void) {
    runtime().routines().register_routine(0xC812, "InitVertPlatform");
    runtime().routines().note_invocation(0xC812);
    runtime().enemy_engine().init_vert_platform();
}

void semcomp_runtime_at_c814(void) {
    runtime().routines().register_routine(0xC814, "at_c814");
    runtime().routines().note_invocation(0xC814);
    runtime().enemy_engine().at_c814();
}

void semcomp_runtime_set_yo(void) {
    runtime().routines().register_routine(0xC81F, "SetYO");
    runtime().routines().note_invocation(0xC81F);
    runtime().enemy_engine().set_yo();
}

void semcomp_runtime_at_c816(void) {
    runtime().routines().register_routine(0xC816, "at_c816");
    runtime().routines().note_invocation(0xC816);
    runtime().enemy_engine().at_c816();
}

void semcomp_runtime_at_c81b(void) {
    runtime().routines().register_routine(0xC81B, "at_c81b");
    runtime().routines().note_invocation(0xC81B);
    runtime().enemy_engine().at_c81b();
}

void semcomp_runtime_at_c824(void) {
    runtime().routines().register_routine(0xC824, "at_c824");
    runtime().routines().note_invocation(0xC824);
    runtime().enemy_engine().at_c824();
}

void semcomp_runtime_at_c834(void) {
    runtime().routines().register_routine(0xC834, "at_c834");
    runtime().routines().note_invocation(0xC834);
    runtime().enemy_engine().at_c834();
}

void semcomp_runtime_at_c81d(void) {
    runtime().routines().register_routine(0xC81D, "at_c81d");
    runtime().routines().note_invocation(0xC81D);
    runtime().enemy_engine().at_c81d();
}

void semcomp_runtime_at_c818(void) {
    runtime().routines().register_routine(0xC818, "at_c818");
    runtime().routines().note_invocation(0xC818);
    runtime().enemy_engine().at_c818();
}

void semcomp_runtime_at_c81a(void) {
    runtime().routines().register_routine(0xC81A, "at_c81a");
    runtime().routines().note_invocation(0xC81A);
    runtime().enemy_engine().at_c81a();
}

void semcomp_runtime_plat_lift_up(void) {
    runtime().routines().register_routine(0xC84B, "PlatLiftUp");
    runtime().routines().note_invocation(0xC84B);
    runtime().enemy_engine().plat_lift_up();
}

void semcomp_runtime_at_c84d(void) {
    runtime().routines().register_routine(0xC84D, "at_c84d");
    runtime().routines().note_invocation(0xC84D);
    runtime().enemy_engine().at_c84d();
}

void semcomp_runtime_plat_lift_down(void) {
    runtime().routines().register_routine(0xC857, "PlatLiftDown");
    runtime().routines().note_invocation(0xC857);
    runtime().enemy_engine().plat_lift_down();
}

void semcomp_runtime_at_c859(void) {
    runtime().routines().register_routine(0xC859, "at_c859");
    runtime().routines().note_invocation(0xC859);
    runtime().enemy_engine().at_c859();
}

void semcomp_runtime_at_c85c(void) {
    runtime().routines().register_routine(0xC85C, "at_c85c");
    runtime().routines().note_invocation(0xC85C);
    runtime().enemy_engine().at_c85c();
}

void semcomp_runtime_pos_platform(void) {
    runtime().routines().register_routine(0xC871, "PosPlatform");
    runtime().routines().note_invocation(0xC871);
    runtime().enemy_engine().pos_platform();
}

void semcomp_runtime_at_c87e(void) {
    runtime().routines().register_routine(0xC87E, "at_c87e");
    runtime().routines().note_invocation(0xC87E);
    runtime().enemy_engine().at_c87e();
}

void semcomp_runtime_at_c880(void) {
    runtime().routines().register_routine(0xC880, "at_c880");
    runtime().routines().note_invocation(0xC880);
    runtime().enemy_engine().at_c880();
}

void semcomp_runtime_run_enemy_objects_core(void) {
    runtime().routines().register_routine(0xC882, "RunEnemyObjectsCore");
    runtime().routines().note_invocation(0xC882);
    runtime().enemy_engine().run_enemy_objects_core();
}

void semcomp_runtime_no_run_code(void) {
    runtime().routines().register_routine(0xC8D6, "NoRunCode");
    runtime().routines().note_invocation(0xC8D6);
    runtime().enemy_engine().no_run_code();
}

void semcomp_runtime_at_c888(void) {
    runtime().routines().register_routine(0xC888, "at_c888");
    runtime().routines().note_invocation(0xC888);
    runtime().enemy_engine().at_c888();
}

void semcomp_runtime_jmp_eo(void) {
    runtime().routines().register_routine(0xC88F, "JmpEO");
    runtime().routines().note_invocation(0xC88F);
    runtime().enemy_engine().jmp_eo();
}

void semcomp_runtime_at_c88a(void) {
    runtime().routines().register_routine(0xC88A, "at_c88a");
    runtime().routines().note_invocation(0xC88A);
    runtime().enemy_engine().at_c88a();
}

void semcomp_runtime_run_normal_enemies(void) {
    runtime().routines().register_routine(0xC8E0, "RunNormalEnemies");
    runtime().routines().note_invocation(0xC8E0);
    runtime().enemy_engine().run_normal_enemies();
}

void semcomp_runtime_at_c8ff(void) {
    runtime().routines().register_routine(0xC8FF, "at_c8ff");
    runtime().routines().note_invocation(0xC8FF);
    runtime().enemy_engine().at_c8ff();
}

void semcomp_runtime_skip_move(void) {
    runtime().routines().register_routine(0xC902, "SkipMove");
    runtime().routines().note_invocation(0xC902);
    runtime().enemy_engine().skip_move();
}

void semcomp_runtime_at_c8eb(void) {
    runtime().routines().register_routine(0xC8EB, "at_c8eb");
    runtime().routines().note_invocation(0xC8EB);
    runtime().enemy_engine().at_c8eb();
}

void semcomp_runtime_at_c8e8(void) {
    runtime().routines().register_routine(0xC8E8, "at_c8e8");
    runtime().routines().note_invocation(0xC8E8);
    runtime().enemy_engine().at_c8e8();
}

void semcomp_runtime_at_c8ee(void) {
    runtime().routines().register_routine(0xC8EE, "at_c8ee");
    runtime().routines().note_invocation(0xC8EE);
    runtime().enemy_engine().at_c8ee();
}

void semcomp_runtime_at_c8e5(void) {
    runtime().routines().register_routine(0xC8E5, "at_c8e5");
    runtime().routines().note_invocation(0xC8E5);
    runtime().enemy_engine().at_c8e5();
}

void semcomp_runtime_at_c8f7(void) {
    runtime().routines().register_routine(0xC8F7, "at_c8f7");
    runtime().routines().note_invocation(0xC8F7);
    runtime().enemy_engine().at_c8f7();
}

void semcomp_runtime_at_c8f1(void) {
    runtime().routines().register_routine(0xC8F1, "at_c8f1");
    runtime().routines().note_invocation(0xC8F1);
    runtime().enemy_engine().at_c8f1();
}

void semcomp_runtime_enemy_movement_subs(void) {
    runtime().routines().register_routine(0xC905, "EnemyMovementSubs");
    runtime().routines().note_invocation(0xC905);
    runtime().enemy_engine().enemy_movement_subs();
}

void semcomp_runtime_no_move_code(void) {
    runtime().routines().register_routine(0xC934, "NoMoveCode");
    runtime().routines().note_invocation(0xC934);
    runtime().enemy_engine().no_move_code();
}

void semcomp_runtime_run_bowser_flame(void) {
    runtime().routines().register_routine(0xC935, "RunBowserFlame");
    runtime().routines().note_invocation(0xC935);
    runtime().enemy_engine().run_bowser_flame();
}

void semcomp_runtime_at_c938(void) {
    runtime().routines().register_routine(0xC938, "at_c938");
    runtime().routines().note_invocation(0xC938);
    runtime().enemy_engine().at_c938();
}

void semcomp_runtime_at_c93e(void) {
    runtime().routines().register_routine(0xC93E, "at_c93e");
    runtime().routines().note_invocation(0xC93E);
    runtime().enemy_engine().at_c93e();
}

void semcomp_runtime_run_firebar_obj(void) {
    runtime().routines().register_routine(0xC947, "RunFirebarObj");
    runtime().routines().note_invocation(0xC947);
    runtime().enemy_engine().run_firebar_obj();
}

void semcomp_runtime_at_c94a(void) {
    runtime().routines().register_routine(0xC94A, "at_c94a");
    runtime().routines().note_invocation(0xC94A);
    runtime().enemy_engine().at_c94a();
}

void semcomp_runtime_run_small_platform(void) {
    runtime().routines().register_routine(0xC94D, "RunSmallPlatform");
    runtime().routines().note_invocation(0xC94D);
    runtime().enemy_engine().run_small_platform();
}

void semcomp_runtime_at_c959(void) {
    runtime().routines().register_routine(0xC959, "at_c959");
    runtime().routines().note_invocation(0xC959);
    runtime().enemy_engine().at_c959();
}

void semcomp_runtime_at_c953(void) {
    runtime().routines().register_routine(0xC953, "at_c953");
    runtime().routines().note_invocation(0xC953);
    runtime().enemy_engine().at_c953();
}

void semcomp_runtime_run_large_platform(void) {
    runtime().routines().register_routine(0xC965, "RunLargePlatform");
    runtime().routines().note_invocation(0xC965);
    runtime().enemy_engine().run_large_platform();
}

void semcomp_runtime_at_c96b(void) {
    runtime().routines().register_routine(0xC96B, "at_c96b");
    runtime().routines().note_invocation(0xC96B);
    runtime().enemy_engine().at_c96b();
}

void semcomp_runtime_at_c96e(void) {
    runtime().routines().register_routine(0xC96E, "at_c96e");
    runtime().routines().note_invocation(0xC96E);
    runtime().enemy_engine().at_c96e();
}

void semcomp_runtime_at_c97f(void) {
    runtime().routines().register_routine(0xC97F, "at_c97f");
    runtime().routines().note_invocation(0xC97F);
    runtime().enemy_engine().at_c97f();
}

void semcomp_runtime_large_platform_subroutines(void) {
    runtime().routines().register_routine(0xC982, "LargePlatformSubroutines");
    runtime().routines().note_invocation(0xC982);
    runtime().enemy_engine().large_platform_subroutines();
}

void semcomp_runtime_at_c987(void) {
    runtime().routines().register_routine(0xC987, "at_c987");
    runtime().routines().note_invocation(0xC987);
    runtime().enemy_engine().at_c987();
}

void semcomp_runtime_at_c9ac(void) {
    runtime().routines().register_routine(0xC9AC, "at_c9ac");
    runtime().routines().note_invocation(0xC9AC);
    runtime().enemy_engine().at_c9ac();
}

void semcomp_runtime_move_podoboo(void) {
    runtime().routines().register_routine(0xC9B0, "MovePodoboo");
    runtime().routines().note_invocation(0xC9B0);
    runtime().enemy_engine().move_podoboo();
}

void semcomp_runtime_at_c9c0(void) {
    runtime().routines().register_routine(0xC9C0, "at_c9c0");
    runtime().routines().note_invocation(0xC9C0);
    runtime().enemy_engine().at_c9c0();
}

void semcomp_runtime_at_c9c9(void) {
    runtime().routines().register_routine(0xC9C9, "at_c9c9");
    runtime().routines().note_invocation(0xC9C9);
    runtime().enemy_engine().at_c9c9();
}

void semcomp_runtime_at_c9b5(void) {
    runtime().routines().register_routine(0xC9B5, "at_c9b5");
    runtime().routines().note_invocation(0xC9B5);
    runtime().enemy_engine().at_c9b5();
}

void semcomp_runtime_pdb_m(void) {
    runtime().routines().register_routine(0xC9CB, "PdbM");
    runtime().routines().note_invocation(0xC9CB);
    runtime().enemy_engine().pdb_m();
}

void semcomp_runtime_at_c9c7(void) {
    runtime().routines().register_routine(0xC9C7, "at_c9c7");
    runtime().routines().note_invocation(0xC9C7);
    runtime().enemy_engine().at_c9c7();
}

void semcomp_runtime_proc_hammer_bro(void) {
    runtime().routines().register_routine(0xC9D8, "ProcHammerBro");
    runtime().routines().note_invocation(0xC9D8);
    runtime().enemy_engine().proc_hammer_bro();
}

void semcomp_runtime_star_flag_exit(void) {
    runtime().routines().register_routine(0xD311, "StarFlagExit");
    runtime().routines().note_invocation(0xD311);
    runtime().enemy_engine().star_flag_exit();
}

void semcomp_runtime_no_p_up(void) {
    runtime().routines().register_routine(0xD84C, "NoPUp");
    runtime().routines().note_invocation(0xD84C);
    runtime().enemy_engine().no_p_up();
}

void semcomp_runtime_ex_sfn(void) {
    runtime().routines().register_routine(0xDA24, "ExSFN");
    runtime().routines().note_invocation(0xDA24);
    runtime().enemy_engine().ex_sfn();
}

void semcomp_runtime_ex_fl(void) {
    runtime().routines().register_routine(0xD1EA, "ExFl");
    runtime().routines().note_invocation(0xD1EA);
    runtime().enemy_engine().ex_fl();
}

void semcomp_runtime_ex_b_gfx_h(void) {
    runtime().routines().register_routine(0xD1BB, "ExBGfxH");
    runtime().routines().note_invocation(0xD1BB);
    runtime().enemy_engine().ex_b_gfx_h();
}

void semcomp_runtime_at_d001(void) {
    runtime().routines().register_routine(0xD001, "at_d001");
    runtime().routines().note_invocation(0xD001);
    runtime().enemy_engine().at_d001();
}

void semcomp_runtime_at_d007(void) {
    runtime().routines().register_routine(0xD007, "at_d007");
    runtime().routines().note_invocation(0xD007);
    runtime().enemy_engine().at_d007();
}

void semcomp_runtime_at_d907(void) {
    runtime().routines().register_routine(0xD907, "at_d907");
    runtime().routines().note_invocation(0xD907);
    runtime().enemy_engine().at_d907();
}

void semcomp_runtime_at_d908(void) {
    runtime().routines().register_routine(0xD908, "at_d908");
    runtime().routines().note_invocation(0xD908);
    runtime().enemy_engine().at_d908();
}

void semcomp_runtime_at_d0c0(void) {
    runtime().routines().register_routine(0xD0C0, "at_d0c0");
    runtime().routines().note_invocation(0xD0C0);
    runtime().enemy_engine().at_d0c0();
}

void semcomp_runtime_at_cea5(void) {
    runtime().routines().register_routine(0xCEA5, "at_cea5");
    runtime().routines().note_invocation(0xCEA5);
    runtime().enemy_engine().at_cea5();
}

void semcomp_runtime_at_d9cf(void) {
    runtime().routines().register_routine(0xD9CF, "at_d9cf");
    runtime().routines().note_invocation(0xD9CF);
    runtime().enemy_engine().at_d9cf();
}

void semcomp_runtime_at_d9ee(void) {
    runtime().routines().register_routine(0xD9EE, "at_d9ee");
    runtime().routines().note_invocation(0xD9EE);
    runtime().enemy_engine().at_d9ee();
}

void semcomp_runtime_at_d003(void) {
    runtime().routines().register_routine(0xD003, "at_d003");
    runtime().routines().note_invocation(0xD003);
    runtime().enemy_engine().at_d003();
}

void semcomp_runtime_at_d9ae(void) {
    runtime().routines().register_routine(0xD9AE, "at_d9ae");
    runtime().routines().note_invocation(0xD9AE);
    runtime().enemy_engine().at_d9ae();
}

void semcomp_runtime_at_d98d(void) {
    runtime().routines().register_routine(0xD98D, "at_d98d");
    runtime().routines().note_invocation(0xD98D);
    runtime().enemy_engine().at_d98d();
}

void semcomp_runtime_at_cdad(void) {
    runtime().routines().register_routine(0xCDAD, "at_cdad");
    runtime().routines().note_invocation(0xCDAD);
    runtime().enemy_engine().at_cdad();
}

void semcomp_runtime_at_cd8e(void) {
    runtime().routines().register_routine(0xCD8E, "at_cd8e");
    runtime().routines().note_invocation(0xCD8E);
    runtime().enemy_engine().at_cd8e();
}

void semcomp_runtime_at_c9ea(void) {
    runtime().routines().register_routine(0xC9EA, "at_c9ea");
    runtime().routines().note_invocation(0xC9EA);
    runtime().enemy_engine().at_c9ea();
}

void semcomp_runtime_at_d100(void) {
    runtime().routines().register_routine(0xD100, "at_d100");
    runtime().routines().note_invocation(0xD100);
    runtime().enemy_engine().at_d100();
}

void semcomp_runtime_at_cd87(void) {
    runtime().routines().register_routine(0xCD87, "at_cd87");
    runtime().routines().note_invocation(0xCD87);
    runtime().enemy_engine().at_cd87();
}

void semcomp_runtime_at_cf96(void) {
    runtime().routines().register_routine(0xCF96, "at_cf96");
    runtime().routines().note_invocation(0xCF96);
    runtime().enemy_engine().at_cf96();
}

void semcomp_runtime_at_ccae(void) {
    runtime().routines().register_routine(0xCCAE, "at_ccae");
    runtime().routines().note_invocation(0xCCAE);
    runtime().enemy_engine().at_ccae();
}

void semcomp_runtime_at_cd4b(void) {
    runtime().routines().register_routine(0xCD4B, "at_cd4b");
    runtime().routines().note_invocation(0xCD4B);
    runtime().enemy_engine().at_cd4b();
}

void semcomp_runtime_at_cfb5(void) {
    runtime().routines().register_routine(0xCFB5, "at_cfb5");
    runtime().routines().note_invocation(0xCFB5);
    runtime().enemy_engine().at_cfb5();
}

void semcomp_runtime_at_d89d(void) {
    runtime().routines().register_routine(0xD89D, "at_d89d");
    runtime().routines().note_invocation(0xD89D);
    runtime().enemy_engine().at_d89d();
}

void semcomp_runtime_at_d1c8(void) {
    runtime().routines().register_routine(0xD1C8, "at_d1c8");
    runtime().routines().note_invocation(0xD1C8);
    runtime().enemy_engine().at_d1c8();
}

void semcomp_runtime_at_d009(void) {
    runtime().routines().register_routine(0xD009, "at_d009");
    runtime().routines().note_invocation(0xD009);
    runtime().enemy_engine().at_d009();
}

void semcomp_runtime_at_cf76(void) {
    runtime().routines().register_routine(0xCF76, "at_cf76");
    runtime().routines().note_invocation(0xCF76);
    runtime().enemy_engine().at_cf76();
}

void semcomp_runtime_at_d18e(void) {
    runtime().routines().register_routine(0xD18E, "at_d18e");
    runtime().routines().note_invocation(0xD18E);
    runtime().enemy_engine().at_d18e();
}

void semcomp_runtime_at_d94c(void) {
    runtime().routines().register_routine(0xD94C, "at_d94c");
    runtime().routines().note_invocation(0xD94C);
    runtime().enemy_engine().at_d94c();
}

void semcomp_runtime_at_d1ee(void) {
    runtime().routines().register_routine(0xD1EE, "at_d1ee");
    runtime().routines().note_invocation(0xD1EE);
    runtime().enemy_engine().at_d1ee();
}

void semcomp_runtime_at_d1ad(void) {
    runtime().routines().register_routine(0xD1AD, "at_d1ad");
    runtime().routines().note_invocation(0xD1AD);
    runtime().enemy_engine().at_d1ad();
}

void semcomp_runtime_at_ca05(void) {
    runtime().routines().register_routine(0xCA05, "at_ca05");
    runtime().routines().note_invocation(0xCA05);
    runtime().enemy_engine().at_ca05();
}

void semcomp_runtime_shroom_flower_p_up(void) {
    runtime().routines().register_routine(0xD820, "Shroom_Flower_PUp");
    runtime().routines().note_invocation(0xD820);
    runtime().enemy_engine().shroom_flower_p_up();
}

void semcomp_runtime_at_cfb9(void) {
    runtime().routines().register_routine(0xCFB9, "at_cfb9");
    runtime().routines().note_invocation(0xCFB9);
    runtime().enemy_engine().at_cfb9();
}

void semcomp_runtime_revive_stunned(void) {
    runtime().routines().register_routine(0xCAC8, "ReviveStunned");
    runtime().routines().note_invocation(0xCAC8);
    runtime().enemy_engine().revive_stunned();
}

void semcomp_runtime_at_d058(void) {
    runtime().routines().register_routine(0xD058, "at_d058");
    runtime().routines().note_invocation(0xD058);
    runtime().enemy_engine().at_d058();
}

void semcomp_runtime_at_cf8d(void) {
    runtime().routines().register_routine(0xCF8D, "at_cf8d");
    runtime().routines().note_invocation(0xCF8D);
    runtime().enemy_engine().at_cf8d();
}

void semcomp_runtime_at_cf9a(void) {
    runtime().routines().register_routine(0xCF9A, "at_cf9a");
    runtime().routines().note_invocation(0xCF9A);
    runtime().enemy_engine().at_cf9a();
}

void semcomp_runtime_at_d920(void) {
    runtime().routines().register_routine(0xD920, "at_d920");
    runtime().routines().note_invocation(0xD920);
    runtime().enemy_engine().at_d920();
}

void semcomp_runtime_s_pixel_lak(void) {
    runtime().routines().register_routine(0xCFD6, "SPixelLak");
    runtime().routines().note_invocation(0xCFD6);
    runtime().enemy_engine().s_pixel_lak();
}

void semcomp_runtime_at_cb8d(void) {
    runtime().routines().register_routine(0xCB8D, "at_cb8d");
    runtime().routines().note_invocation(0xCB8D);
    runtime().enemy_engine().at_cb8d();
}

void semcomp_runtime_at_d7cf(void) {
    runtime().routines().register_routine(0xD7CF, "at_d7cf");
    runtime().routines().note_invocation(0xD7CF);
    runtime().enemy_engine().at_d7cf();
}

void semcomp_runtime_at_d031(void) {
    runtime().routines().register_routine(0xD031, "at_d031");
    runtime().routines().note_invocation(0xD031);
    runtime().enemy_engine().at_d031();
}

void semcomp_runtime_at_d7ae(void) {
    runtime().routines().register_routine(0xD7AE, "at_d7ae");
    runtime().routines().note_invocation(0xD7AE);
    runtime().enemy_engine().at_d7ae();
}

void semcomp_runtime_at_d38c(void) {
    runtime().routines().register_routine(0xD38C, "at_d38c");
    runtime().routines().note_invocation(0xD38C);
    runtime().enemy_engine().at_d38c();
}

void semcomp_runtime_at_d38d(void) {
    runtime().routines().register_routine(0xD38D, "at_d38d");
    runtime().routines().note_invocation(0xD38D);
    runtime().enemy_engine().at_d38d();
}

void semcomp_runtime_at_cec2(void) {
    runtime().routines().register_routine(0xCEC2, "at_cec2");
    runtime().routines().note_invocation(0xCEC2);
    runtime().enemy_engine().at_cec2();
}

void semcomp_runtime_chk_player_near_pipe(void) {
    runtime().routines().register_routine(0xD3CF, "ChkPlayerNearPipe");
    runtime().routines().note_invocation(0xD3CF);
    runtime().enemy_engine().chk_player_near_pipe();
}

void semcomp_runtime_at_ccd0(void) {
    runtime().routines().register_routine(0xCCD0, "at_ccd0");
    runtime().routines().note_invocation(0xCCD0);
    runtime().enemy_engine().at_ccd0();
}

void semcomp_runtime_at_d012(void) {
    runtime().routines().register_routine(0xD012, "at_d012");
    runtime().routines().note_invocation(0xD012);
    runtime().enemy_engine().at_d012();
}

void semcomp_runtime_at_d660(void) {
    runtime().routines().register_routine(0xD660, "at_d660");
    runtime().routines().note_invocation(0xD660);
    runtime().enemy_engine().at_d660();
}

void semcomp_runtime_at_cfd7(void) {
    runtime().routines().register_routine(0xCFD7, "at_cfd7");
    runtime().routines().note_invocation(0xCFD7);
    runtime().enemy_engine().at_cfd7();
}

void semcomp_runtime_at_d6d0(void) {
    runtime().routines().register_routine(0xD6D0, "at_d6d0");
    runtime().routines().note_invocation(0xD6D0);
    runtime().enemy_engine().at_d6d0();
}

void semcomp_runtime_too_far(void) {
    runtime().routines().register_routine(0xD6D2, "TooFar");
    runtime().routines().note_invocation(0xD6D2);
    runtime().enemy_engine().too_far();
}

void semcomp_runtime_at_d6c8(void) {
    runtime().routines().register_routine(0xD6C8, "at_d6c8");
    runtime().routines().note_invocation(0xD6C8);
    runtime().enemy_engine().at_d6c8();
}

void semcomp_runtime_at_d6ca(void) {
    runtime().routines().register_routine(0xD6CA, "at_d6ca");
    runtime().routines().note_invocation(0xD6CA);
    runtime().enemy_engine().at_d6ca();
}

void semcomp_runtime_at_d6ba(void) {
    runtime().routines().register_routine(0xD6BA, "at_d6ba");
    runtime().routines().note_invocation(0xD6BA);
    runtime().enemy_engine().at_d6ba();
}

void semcomp_runtime_at_d6b8(void) {
    runtime().routines().register_routine(0xD6B8, "at_d6b8");
    runtime().routines().note_invocation(0xD6B8);
    runtime().enemy_engine().at_d6b8();
}

void semcomp_runtime_at_d7b8(void) {
    runtime().routines().register_routine(0xD7B8, "at_d7b8");
    runtime().routines().note_invocation(0xD7B8);
    runtime().enemy_engine().at_d7b8();
}

void semcomp_runtime_at_d8cb(void) {
    runtime().routines().register_routine(0xD8CB, "at_d8cb");
    runtime().routines().note_invocation(0xD8CB);
    runtime().enemy_engine().at_d8cb();
}

void semcomp_runtime_at_cb8a(void) {
    runtime().routines().register_routine(0xCB8A, "at_cb8a");
    runtime().routines().note_invocation(0xCB8A);
    runtime().enemy_engine().at_cb8a();
}

void semcomp_runtime_at_cc4b(void) {
    runtime().routines().register_routine(0xCC4B, "at_cc4b");
    runtime().routines().note_invocation(0xCC4B);
    runtime().enemy_engine().at_cc4b();
}

void semcomp_runtime_reverse_plant_speed(void) {
    runtime().routines().register_routine(0xD3D5, "ReversePlantSpeed");
    runtime().routines().note_invocation(0xD3D5);
    runtime().enemy_engine().reverse_plant_speed();
}

void semcomp_runtime_at_d62d(void) {
    runtime().routines().register_routine(0xD62D, "at_d62d");
    runtime().routines().note_invocation(0xD62D);
    runtime().enemy_engine().at_d62d();
}

void semcomp_runtime_at_d00c(void) {
    runtime().routines().register_routine(0xD00C, "at_d00c");
    runtime().routines().note_invocation(0xD00C);
    runtime().enemy_engine().at_d00c();
}

void semcomp_runtime_get_v_adder(void) {
    runtime().routines().register_routine(0xCEBA, "GetVAdder");
    runtime().routines().note_invocation(0xCEBA);
    runtime().enemy_engine().get_v_adder();
}

void semcomp_runtime_hammer_bro_jump_l_data(void) {
    runtime().routines().register_routine(0xCA10, "HammerBroJumpLData");
    runtime().routines().note_invocation(0xCA10);
    runtime().enemy_engine().hammer_bro_jump_l_data();
}

void semcomp_runtime_at_d041(void) {
    runtime().routines().register_routine(0xD041, "at_d041");
    runtime().routines().note_invocation(0xD041);
    runtime().enemy_engine().at_d041();
}

void semcomp_runtime_at_d079(void) {
    runtime().routines().register_routine(0xD079, "at_d079");
    runtime().routines().note_invocation(0xD079);
    runtime().enemy_engine().at_d079();
}

void semcomp_runtime_at_d4b9(void) {
    runtime().routines().register_routine(0xD4B9, "at_d4b9");
    runtime().routines().note_invocation(0xD4B9);
    runtime().enemy_engine().at_d4b9();
}

void semcomp_runtime_at_d4ba(void) {
    runtime().routines().register_routine(0xD4BA, "at_d4ba");
    runtime().routines().note_invocation(0xD4BA);
    runtime().enemy_engine().at_d4ba();
}

void semcomp_runtime_set_m2(void) {
    runtime().routines().register_routine(0xD005, "SetM2");
    runtime().routines().note_invocation(0xD005);
    runtime().enemy_engine().set_m2();
}

void semcomp_runtime_at_cff7(void) {
    runtime().routines().register_routine(0xCFF7, "at_cff7");
    runtime().routines().note_invocation(0xCFF7);
    runtime().enemy_engine().at_cff7();
}

void semcomp_runtime_ex_pf(void) {
    runtime().routines().register_routine(0xD5D0, "ExPF");
    runtime().routines().note_invocation(0xD5D0);
    runtime().enemy_engine().ex_pf();
}

void semcomp_runtime_at_d6fa(void) {
    runtime().routines().register_routine(0xD6FA, "at_d6fa");
    runtime().routines().note_invocation(0xD6FA);
    runtime().enemy_engine().at_d6fa();
}

void semcomp_runtime_at_d0cb(void) {
    runtime().routines().register_routine(0xD0CB, "at_d0cb");
    runtime().routines().note_invocation(0xD0CB);
    runtime().enemy_engine().at_d0cb();
}

void semcomp_runtime_at_d089(void) {
    runtime().routines().register_routine(0xD089, "at_d089");
    runtime().routines().note_invocation(0xD089);
    runtime().enemy_engine().at_d089();
}

void semcomp_runtime_at_d069(void) {
    runtime().routines().register_routine(0xD069, "at_d069");
    runtime().routines().note_invocation(0xD069);
    runtime().enemy_engine().at_d069();
}

void semcomp_runtime_at_cec5(void) {
    runtime().routines().register_routine(0xCEC5, "at_cec5");
    runtime().routines().note_invocation(0xCEC5);
    runtime().enemy_engine().at_cec5();
}

void semcomp_runtime_swim_ccx_move_data(void) {
    runtime().routines().register_routine(0xCC46, "SwimCCXMoveData");
    runtime().routines().note_invocation(0xCC46);
    runtime().enemy_engine().swim_ccx_move_data();
}

void semcomp_runtime_at_cc47(void) {
    runtime().routines().register_routine(0xCC47, "at_cc47");
    runtime().routines().note_invocation(0xCC47);
    runtime().enemy_engine().at_cc47();
}

void semcomp_runtime_at_d018(void) {
    runtime().routines().register_routine(0xD018, "at_d018");
    runtime().routines().note_invocation(0xD018);
    runtime().enemy_engine().at_d018();
}

void semcomp_runtime_at_ce8f(void) {
    runtime().routines().register_routine(0xCE8F, "at_ce8f");
    runtime().routines().note_invocation(0xCE8F);
    runtime().enemy_engine().at_ce8f();
}

void semcomp_runtime_at_cfad(void) {
    runtime().routines().register_routine(0xCFAD, "at_cfad");
    runtime().routines().note_invocation(0xCFAD);
    runtime().enemy_engine().at_cfad();
}

void semcomp_runtime_at_cd06(void) {
    runtime().routines().register_routine(0xCD06, "at_cd06");
    runtime().routines().note_invocation(0xCD06);
    runtime().enemy_engine().at_cd06();
}

void semcomp_runtime_at_cd07(void) {
    runtime().routines().register_routine(0xCD07, "at_cd07");
    runtime().routines().note_invocation(0xCD07);
    runtime().enemy_engine().at_cd07();
}

void semcomp_runtime_at_d0f8(void) {
    runtime().routines().register_routine(0xD0F8, "at_d0f8");
    runtime().routines().note_invocation(0xD0F8);
    runtime().enemy_engine().at_d0f8();
}

void semcomp_runtime_at_cea4(void) {
    runtime().routines().register_routine(0xCEA4, "at_cea4");
    runtime().routines().note_invocation(0xCEA4);
    runtime().enemy_engine().at_cea4();
}

void semcomp_runtime_at_cd3b(void) {
    runtime().routines().register_routine(0xCD3B, "at_cd3b");
    runtime().routines().note_invocation(0xCD3B);
    runtime().enemy_engine().at_cd3b();
}

void semcomp_runtime_at_ce33(void) {
    runtime().routines().register_routine(0xCE33, "at_ce33");
    runtime().routines().note_invocation(0xCE33);
    runtime().enemy_engine().at_ce33();
}

void semcomp_runtime_firebar_tbl_offsets(void) {
    runtime().routines().register_routine(0xCD2E, "FirebarTblOffsets");
    runtime().routines().note_invocation(0xCD2E);
    runtime().enemy_engine().firebar_tbl_offsets();
}

void semcomp_runtime_at_cd2f(void) {
    runtime().routines().register_routine(0xCD2F, "at_cd2f");
    runtime().routines().note_invocation(0xCD2F);
    runtime().enemy_engine().at_cd2f();
}

void semcomp_runtime_firebar_pos_lookup_tbl(void) {
    runtime().routines().register_routine(0xCCC7, "FirebarPosLookupTbl");
    runtime().routines().note_invocation(0xCCC7);
    runtime().enemy_engine().firebar_pos_lookup_tbl();
}

void semcomp_runtime_at_ccc8(void) {
    runtime().routines().register_routine(0xCCC8, "at_ccc8");
    runtime().routines().note_invocation(0xCCC8);
    runtime().enemy_engine().at_ccc8();
}

void semcomp_runtime_firebar_mirror_data(void) {
    runtime().routines().register_routine(0xCD2A, "FirebarMirrorData");
    runtime().routines().note_invocation(0xCD2A);
    runtime().enemy_engine().firebar_mirror_data();
}

void semcomp_runtime_p_random_subtracter(void) {
    runtime().routines().register_routine(0xCED5, "PRandomSubtracter");
    runtime().routines().note_invocation(0xCED5);
    runtime().enemy_engine().p_random_subtracter();
}

void semcomp_runtime_at_ced6(void) {
    runtime().routines().register_routine(0xCED6, "at_ced6");
    runtime().routines().note_invocation(0xCED6);
    runtime().enemy_engine().at_ced6();
}

void semcomp_runtime_at_cedb(void) {
    runtime().routines().register_routine(0xCEDB, "at_cedb");
    runtime().routines().note_invocation(0xCEDB);
    runtime().enemy_engine().at_cedb();
}

void semcomp_runtime_lakitu_diff_adj(void) {
    runtime().routines().register_routine(0xCF25, "LakituDiffAdj");
    runtime().routines().note_invocation(0xCF25);
    runtime().enemy_engine().lakitu_diff_adj();
}

void semcomp_runtime_at_d599(void) {
    runtime().routines().register_routine(0xD599, "at_d599");
    runtime().routines().note_invocation(0xD599);
    runtime().enemy_engine().at_d599();
}

void semcomp_runtime_ex_y_pl(void) {
    runtime().routines().register_routine(0xD606, "ExYPl");
    runtime().routines().note_invocation(0xD606);
    runtime().enemy_engine().ex_y_pl();
}

void semcomp_runtime_at_d0a1(void) {
    runtime().routines().register_routine(0xD0A1, "at_d0a1");
    runtime().routines().note_invocation(0xD0A1);
    runtime().enemy_engine().at_d0a1();
}

void semcomp_runtime_at_d02e(void) {
    runtime().routines().register_routine(0xD02E, "at_d02e");
    runtime().routines().note_invocation(0xD02E);
    runtime().enemy_engine().at_d02e();
}

void semcomp_runtime_at_ced2(void) {
    runtime().routines().register_routine(0xCED2, "at_ced2");
    runtime().routines().note_invocation(0xCED2);
    runtime().enemy_engine().at_ced2();
}

void semcomp_runtime_bridge_collapse_data(void) {
    runtime().routines().register_routine(0xCFDD, "BridgeCollapseData");
    runtime().routines().note_invocation(0xCFDD);
    runtime().enemy_engine().bridge_collapse_data();
}

void semcomp_runtime_at_cfde(void) {
    runtime().routines().register_routine(0xCFDE, "at_cfde");
    runtime().routines().note_invocation(0xCFDE);
    runtime().enemy_engine().at_cfde();
}

void semcomp_runtime_p_random_range(void) {
    runtime().routines().register_routine(0xD061, "PRandomRange");
    runtime().routines().note_invocation(0xD061);
    runtime().enemy_engine().p_random_range();
}

void semcomp_runtime_at_d609(void) {
    runtime().routines().register_routine(0xD609, "at_d609");
    runtime().routines().note_invocation(0xD609);
    runtime().enemy_engine().at_d609();
}

void semcomp_runtime_at_d721(void) {
    runtime().routines().register_routine(0xD721, "at_d721");
    runtime().routines().note_invocation(0xD721);
    runtime().enemy_engine().at_d721();
}

void semcomp_runtime_at_d01f(void) {
    runtime().routines().register_routine(0xD01F, "at_d01f");
    runtime().routines().note_invocation(0xD01F);
    runtime().enemy_engine().at_d01f();
}

void semcomp_runtime_flame_timer_data(void) {
    runtime().routines().register_routine(0xD1D1, "FlameTimerData");
    runtime().routines().note_invocation(0xD1D1);
    runtime().enemy_engine().flame_timer_data();
}

void semcomp_runtime_at_d991(void) {
    runtime().routines().register_routine(0xD991, "at_d991");
    runtime().routines().note_invocation(0xD991);
    runtime().enemy_engine().at_d991();
}

void semcomp_runtime_at_d78d(void) {
    runtime().routines().register_routine(0xD78D, "at_d78d");
    runtime().routines().note_invocation(0xD78D);
    runtime().enemy_engine().at_d78d();
}

void semcomp_runtime_at_cd7d(void) {
    runtime().routines().register_routine(0xCD7D, "at_cd7d");
    runtime().routines().note_invocation(0xCD7D);
    runtime().enemy_engine().at_cd7d();
}

void semcomp_runtime_star_flag_y_pos_adder(void) {
    runtime().routines().register_routine(0xD2CD, "StarFlagYPosAdder");
    runtime().routines().note_invocation(0xD2CD);
    runtime().enemy_engine().star_flag_y_pos_adder();
}

void semcomp_runtime_at_d2ce(void) {
    runtime().routines().register_routine(0xD2CE, "at_d2ce");
    runtime().routines().note_invocation(0xD2CE);
    runtime().enemy_engine().at_d2ce();
}

void semcomp_runtime_at_d5bd(void) {
    runtime().routines().register_routine(0xD5BD, "at_d5bd");
    runtime().routines().note_invocation(0xD5BD);
    runtime().enemy_engine().at_d5bd();
}

void semcomp_runtime_star_flag_tile_data(void) {
    runtime().routines().register_routine(0xD2D5, "StarFlagTileData");
    runtime().routines().note_invocation(0xD2D5);
    runtime().enemy_engine().star_flag_tile_data();
}

void semcomp_runtime_at_d17e(void) {
    runtime().routines().register_routine(0xD17E, "at_d17e");
    runtime().routines().note_invocation(0xD17E);
    runtime().enemy_engine().at_d17e();
}

void semcomp_runtime_star_flag_x_pos_adder(void) {
    runtime().routines().register_routine(0xD2D1, "StarFlagXPosAdder");
    runtime().routines().note_invocation(0xD2D1);
    runtime().enemy_engine().star_flag_x_pos_adder();
}

void semcomp_runtime_at_d2d2(void) {
    runtime().routines().register_routine(0xD2D2, "at_d2d2");
    runtime().routines().note_invocation(0xD2D2);
    runtime().enemy_engine().at_d2d2();
}

void semcomp_runtime_at_da10(void) {
    runtime().routines().register_routine(0xDA10, "at_da10");
    runtime().routines().note_invocation(0xDA10);
    runtime().enemy_engine().at_da10();
}

void semcomp_runtime_at_d5bc(void) {
    runtime().routines().register_routine(0xD5BC, "at_d5bc");
    runtime().routines().note_invocation(0xD5BC);
    runtime().enemy_engine().at_d5bc();
}

void semcomp_runtime_at_d52d(void) {
    runtime().routines().register_routine(0xD52D, "at_d52d");
    runtime().routines().note_invocation(0xD52D);
    runtime().enemy_engine().at_d52d();
}

void semcomp_runtime_at_d9d6(void) {
    runtime().routines().register_routine(0xD9D6, "at_d9d6");
    runtime().routines().note_invocation(0xD9D6);
    runtime().enemy_engine().at_d9d6();
}

void semcomp_runtime_at_cfd9(void) {
    runtime().routines().register_routine(0xCFD9, "at_cfd9");
    runtime().routines().note_invocation(0xCFD9);
    runtime().enemy_engine().at_cfd9();
}

void semcomp_runtime_at_cfda(void) {
    runtime().routines().register_routine(0xCFDA, "at_cfda");
    runtime().routines().note_invocation(0xCFDA);
    runtime().enemy_engine().at_cfda();
}

void semcomp_runtime_at_d01a(void) {
    runtime().routines().register_routine(0xD01A, "at_d01a");
    runtime().routines().note_invocation(0xD01A);
    runtime().enemy_engine().at_d01a();
}

void semcomp_runtime_at_cff5(void) {
    runtime().routines().register_routine(0xCFF5, "at_cff5");
    runtime().routines().note_invocation(0xCFF5);
    runtime().enemy_engine().at_cff5();
}

void semcomp_runtime_at_cf79(void) {
    runtime().routines().register_routine(0xCF79, "at_cf79");
    runtime().routines().note_invocation(0xCF79);
    runtime().enemy_engine().at_cf79();
}

void semcomp_runtime_at_d542(void) {
    runtime().routines().register_routine(0xD542, "at_d542");
    runtime().routines().note_invocation(0xD542);
    runtime().enemy_engine().at_d542();
}

void semcomp_runtime_at_cfb7(void) {
    runtime().routines().register_routine(0xCFB7, "at_cfb7");
    runtime().routines().note_invocation(0xCFB7);
    runtime().enemy_engine().at_cfb7();
}

void semcomp_runtime_at_d8be(void) {
    runtime().routines().register_routine(0xD8BE, "at_d8be");
    runtime().routines().note_invocation(0xD8BE);
    runtime().enemy_engine().at_d8be();
}

void semcomp_runtime_at_ca01(void) {
    runtime().routines().register_routine(0xCA01, "at_ca01");
    runtime().routines().note_invocation(0xCA01);
    runtime().enemy_engine().at_ca01();
}

void semcomp_runtime_at_ce2d(void) {
    runtime().routines().register_routine(0xCE2D, "at_ce2d");
    runtime().routines().note_invocation(0xCE2D);
    runtime().enemy_engine().at_ce2d();
}

void semcomp_runtime_at_ce2e(void) {
    runtime().routines().register_routine(0xCE2E, "at_ce2e");
    runtime().routines().note_invocation(0xCE2E);
    runtime().enemy_engine().at_ce2e();
}

void semcomp_runtime_bowser_identities(void) {
    runtime().routines().register_routine(0xD736, "BowserIdentities");
    runtime().routines().note_invocation(0xD736);
    runtime().enemy_engine().bowser_identities();
}

void semcomp_runtime_at_d81d(void) {
    runtime().routines().register_routine(0xD81D, "at_d81d");
    runtime().routines().note_invocation(0xD81D);
    runtime().enemy_engine().at_d81d();
}

void semcomp_runtime_kicked_shell_x_spd_data(void) {
    runtime().routines().register_routine(0xD84F, "KickedShellXSpdData");
    runtime().routines().note_invocation(0xD84F);
    runtime().enemy_engine().kicked_shell_x_spd_data();
}

void semcomp_runtime_kicked_shell_pts_data(void) {
    runtime().routines().register_routine(0xD892, "KickedShellPtsData");
    runtime().routines().note_invocation(0xD892);
    runtime().enemy_engine().kicked_shell_pts_data();
}

void semcomp_runtime_at_d893(void) {
    runtime().routines().register_routine(0xD893, "at_d893");
    runtime().routines().note_invocation(0xD893);
    runtime().enemy_engine().at_d893();
}

void semcomp_runtime_at_d966(void) {
    runtime().routines().register_routine(0xD966, "at_d966");
    runtime().routines().note_invocation(0xD966);
    runtime().enemy_engine().at_d966();
}

void semcomp_runtime_demoted_koopa_x_spd_data(void) {
    runtime().routines().register_routine(0xD851, "DemotedKoopaXSpdData");
    runtime().routines().note_invocation(0xD851);
    runtime().enemy_engine().demoted_koopa_x_spd_data();
}

void semcomp_runtime_at_d852(void) {
    runtime().routines().register_routine(0xD852, "at_d852");
    runtime().routines().note_invocation(0xD852);
    runtime().enemy_engine().at_d852();
}

void semcomp_runtime_at_d2b9(void) {
    runtime().routines().register_routine(0xD2B9, "at_d2b9");
    runtime().routines().note_invocation(0xD2B9);
    runtime().enemy_engine().at_d2b9();
}

void semcomp_runtime_revival_rate_data(void) {
    runtime().routines().register_routine(0xD9D2, "RevivalRateData");
    runtime().routines().note_invocation(0xD9D2);
    runtime().enemy_engine().revival_rate_data();
}

void semcomp_runtime_at_cadd(void) {
    runtime().routines().register_routine(0xCADD, "at_cadd");
    runtime().routines().note_invocation(0xCADD);
    runtime().enemy_engine().at_cadd();
}

void semcomp_runtime_at_d081(void) {
    runtime().routines().register_routine(0xD081, "at_d081");
    runtime().routines().note_invocation(0xD081);
    runtime().enemy_engine().at_d081();
}

void semcomp_runtime_set_bits_mask(void) {
    runtime().routines().register_routine(0xDA25, "SetBitsMask");
    runtime().routines().note_invocation(0xDA25);
    runtime().enemy_engine().set_bits_mask();
}

void semcomp_runtime_at_d024(void) {
    runtime().routines().register_routine(0xD024, "at_d024");
    runtime().routines().note_invocation(0xD024);
    runtime().enemy_engine().at_d024();
}

void semcomp_runtime_no_col_fb(void) {
    runtime().routines().register_routine(0xCE85, "NoColFB");
    runtime().routines().note_invocation(0xCE85);
    runtime().enemy_engine().no_col_fb();
}

void semcomp_runtime_at_ce86(void) {
    runtime().routines().register_routine(0xCE86, "at_ce86");
    runtime().routines().note_invocation(0xCE86);
    runtime().enemy_engine().at_ce86();
}

void semcomp_runtime_at_d0ae(void) {
    runtime().routines().register_routine(0xD0AE, "at_d0ae");
    runtime().routines().note_invocation(0xD0AE);
    runtime().enemy_engine().at_d0ae();
}

void semcomp_runtime_at_cfc9(void) {
    runtime().routines().register_routine(0xCFC9, "at_cfc9");
    runtime().routines().note_invocation(0xCFC9);
    runtime().enemy_engine().at_cfc9();
}

void semcomp_runtime_at_c9dc(void) {
    runtime().routines().register_routine(0xC9DC, "at_c9dc");
    runtime().routines().note_invocation(0xC9DC);
    runtime().enemy_engine().at_c9dc();
}

void semcomp_runtime_at_d0c5(void) {
    runtime().routines().register_routine(0xD0C5, "at_d0c5");
    runtime().routines().note_invocation(0xD0C5);
    runtime().enemy_engine().at_d0c5();
}

void semcomp_runtime_at_ce26(void) {
    runtime().routines().register_routine(0xCE26, "at_ce26");
    runtime().routines().note_invocation(0xCE26);
    runtime().enemy_engine().at_ce26();
}

void semcomp_runtime_at_d0e3(void) {
    runtime().routines().register_routine(0xD0E3, "at_d0e3");
    runtime().routines().note_invocation(0xD0E3);
    runtime().enemy_engine().at_d0e3();
}

void semcomp_runtime_at_d0e4(void) {
    runtime().routines().register_routine(0xD0E4, "at_d0e4");
    runtime().routines().note_invocation(0xD0E4);
    runtime().enemy_engine().at_d0e4();
}

void semcomp_runtime_at_cbd0(void) {
    runtime().routines().register_routine(0xCBD0, "at_cbd0");
    runtime().routines().note_invocation(0xCBD0);
    runtime().enemy_engine().at_cbd0();
}

void semcomp_runtime_at_cbd1(void) {
    runtime().routines().register_routine(0xCBD1, "at_cbd1");
    runtime().routines().note_invocation(0xCBD1);
    runtime().enemy_engine().at_cbd1();
}

void semcomp_runtime_at_ca03(void) {
    runtime().routines().register_routine(0xCA03, "at_ca03");
    runtime().routines().note_invocation(0xCA03);
    runtime().enemy_engine().at_ca03();
}

void semcomp_runtime_at_c9de(void) {
    runtime().routines().register_routine(0xC9DE, "at_c9de");
    runtime().routines().note_invocation(0xC9DE);
    runtime().enemy_engine().at_c9de();
}

void semcomp_runtime_at_d027(void) {
    runtime().routines().register_routine(0xD027, "at_d027");
    runtime().routines().note_invocation(0xD027);
    runtime().enemy_engine().at_d027();
}

void semcomp_runtime_at_d6ae(void) {
    runtime().routines().register_routine(0xD6AE, "at_d6ae");
    runtime().routines().note_invocation(0xD6AE);
    runtime().enemy_engine().at_d6ae();
}

void semcomp_runtime_at_d0e1(void) {
    runtime().routines().register_routine(0xD0E1, "at_d0e1");
    runtime().routines().note_invocation(0xD0E1);
    runtime().enemy_engine().at_d0e1();
}

void semcomp_runtime_at_c9f9(void) {
    runtime().routines().register_routine(0xC9F9, "at_c9f9");
    runtime().routines().note_invocation(0xC9F9);
    runtime().enemy_engine().at_c9f9();
}

void semcomp_runtime_at_c9da(void) {
    runtime().routines().register_routine(0xC9DA, "at_c9da");
    runtime().routines().note_invocation(0xC9DA);
    runtime().enemy_engine().at_c9da();
}

void semcomp_runtime_at_d61f(void) {
    runtime().routines().register_routine(0xD61F, "at_d61f");
    runtime().routines().note_invocation(0xD61F);
    runtime().enemy_engine().at_d61f();
}

void semcomp_runtime_at_d047(void) {
    runtime().routines().register_routine(0xD047, "at_d047");
    runtime().routines().note_invocation(0xD047);
    runtime().enemy_engine().at_d047();
}

void semcomp_runtime_skip_iy(void) {
    runtime().routines().register_routine(0xD5EC, "SkipIY");
    runtime().routines().note_invocation(0xD5EC);
    runtime().enemy_engine().skip_iy();
}

void semcomp_runtime_at_c9e3(void) {
    runtime().routines().register_routine(0xC9E3, "at_c9e3");
    runtime().routines().note_invocation(0xC9E3);
    runtime().enemy_engine().at_c9e3();
}

void semcomp_runtime_at_d595(void) {
    runtime().routines().register_routine(0xD595, "at_d595");
    runtime().routines().note_invocation(0xD595);
    runtime().enemy_engine().at_d595();
}

void semcomp_runtime_at_d12d(void) {
    runtime().routines().register_routine(0xD12D, "at_d12d");
    runtime().routines().note_invocation(0xD12D);
    runtime().enemy_engine().at_d12d();
}

void semcomp_runtime_at_caf1(void) {
    runtime().routines().register_routine(0xCAF1, "at_caf1");
    runtime().routines().note_invocation(0xCAF1);
    runtime().enemy_engine().at_caf1();
}

void semcomp_runtime_at_d905(void) {
    runtime().routines().register_routine(0xD905, "at_d905");
    runtime().routines().note_invocation(0xD905);
    runtime().enemy_engine().at_d905();
}

void semcomp_runtime_at_d913(void) {
    runtime().routines().register_routine(0xD913, "at_d913");
    runtime().routines().note_invocation(0xD913);
    runtime().enemy_engine().at_d913();
}

void semcomp_runtime_at_ceb5(void) {
    runtime().routines().register_routine(0xCEB5, "at_ceb5");
    runtime().routines().note_invocation(0xCEB5);
    runtime().enemy_engine().at_ceb5();
}

void semcomp_runtime_at_cc79(void) {
    runtime().routines().register_routine(0xCC79, "at_cc79");
    runtime().routines().note_invocation(0xCC79);
    runtime().enemy_engine().at_cc79();
}

void semcomp_runtime_at_cc7d(void) {
    runtime().routines().register_routine(0xCC7D, "at_cc7d");
    runtime().routines().note_invocation(0xCC7D);
    runtime().enemy_engine().at_cc7d();
}

void semcomp_runtime_at_d0be(void) {
    runtime().routines().register_routine(0xD0BE, "at_d0be");
    runtime().routines().note_invocation(0xD0BE);
    runtime().enemy_engine().at_d0be();
}

void semcomp_runtime_draw_erase_rope(void) {
    runtime().routines().register_routine(0xD4BD, "DrawEraseRope");
    runtime().routines().note_invocation(0xD4BD);
    runtime().enemy_engine().draw_erase_rope();
}

void semcomp_runtime_at_d603(void) {
    runtime().routines().register_routine(0xD603, "at_d603");
    runtime().routines().note_invocation(0xD603);
    runtime().enemy_engine().at_d603();
}

void semcomp_runtime_ex_lift_p(void) {
    runtime().routines().register_routine(0xD679, "ExLiftP");
    runtime().routines().note_invocation(0xD679);
    runtime().enemy_engine().ex_lift_p();
}

void semcomp_runtime_at_cebe(void) {
    runtime().routines().register_routine(0xCEBE, "at_cebe");
    runtime().routines().note_invocation(0xCEBE);
    runtime().enemy_engine().at_cebe();
}

void semcomp_runtime_at_ca0d(void) {
    runtime().routines().register_routine(0xCA0D, "at_ca0d");
    runtime().routines().note_invocation(0xCA0D);
    runtime().enemy_engine().at_ca0d();
}

void semcomp_runtime_at_d8db(void) {
    runtime().routines().register_routine(0xD8DB, "at_d8db");
    runtime().routines().note_invocation(0xD8DB);
    runtime().enemy_engine().at_d8db();
}

void semcomp_runtime_at_d8d9(void) {
    runtime().routines().register_routine(0xD8D9, "at_d8d9");
    runtime().routines().note_invocation(0xD8D9);
    runtime().enemy_engine().at_d8d9();
}

void semcomp_runtime_at_cdd9(void) {
    runtime().routines().register_routine(0xCDD9, "at_cdd9");
    runtime().routines().note_invocation(0xCDD9);
    runtime().enemy_engine().at_cdd9();
}

void semcomp_runtime_at_cecd(void) {
    runtime().routines().register_routine(0xCECD, "at_cecd");
    runtime().routines().note_invocation(0xCECD);
    runtime().enemy_engine().at_cecd();
}

void semcomp_runtime_at_cece(void) {
    runtime().routines().register_routine(0xCECE, "at_cece");
    runtime().routines().note_invocation(0xCECE);
    runtime().enemy_engine().at_cece();
}

void semcomp_runtime_at_cecf(void) {
    runtime().routines().register_routine(0xCECF, "at_cecf");
    runtime().routines().note_invocation(0xCECF);
    runtime().enemy_engine().at_cecf();
}

void semcomp_runtime_at_cfcf(void) {
    runtime().routines().register_routine(0xCFCF, "at_cfcf");
    runtime().routines().note_invocation(0xCFCF);
    runtime().enemy_engine().at_cfcf();
}

void semcomp_runtime_at_d2d3(void) {
    runtime().routines().register_routine(0xD2D3, "at_d2d3");
    runtime().routines().note_invocation(0xD2D3);
    runtime().enemy_engine().at_d2d3();
}

void semcomp_runtime_at_d2d4(void) {
    runtime().routines().register_routine(0xD2D4, "at_d2d4");
    runtime().routines().note_invocation(0xD2D4);
    runtime().enemy_engine().at_d2d4();
}

void semcomp_runtime_at_d58a(void) {
    runtime().routines().register_routine(0xD58A, "at_d58a");
    runtime().routines().note_invocation(0xD58A);
    runtime().enemy_engine().at_d58a();
}

void semcomp_runtime_at_d4d6(void) {
    runtime().routines().register_routine(0xD4D6, "at_d4d6");
    runtime().routines().note_invocation(0xD4D6);
    runtime().enemy_engine().at_d4d6();
}

void semcomp_runtime_at_d3e3(void) {
    runtime().routines().register_routine(0xD3E3, "at_d3e3");
    runtime().routines().note_invocation(0xD3E3);
    runtime().enemy_engine().at_d3e3();
}

void semcomp_runtime_at_d5d2(void) {
    runtime().routines().register_routine(0xD5D2, "at_d5d2");
    runtime().routines().note_invocation(0xD5D2);
    runtime().enemy_engine().at_d5d2();
}

void semcomp_runtime_get_pr_cmp(void) {
    runtime().routines().register_routine(0xD0D1, "GetPRCmp");
    runtime().routines().note_invocation(0xD0D1);
    runtime().enemy_engine().get_pr_cmp();
}

void semcomp_runtime_at_d7d1(void) {
    runtime().routines().register_routine(0xD7D1, "at_d7d1");
    runtime().routines().note_invocation(0xD7D1);
    runtime().enemy_engine().at_d7d1();
}

void semcomp_runtime_at_d7d7(void) {
    runtime().routines().register_routine(0xD7D7, "at_d7d7");
    runtime().routines().note_invocation(0xD7D7);
    runtime().enemy_engine().at_d7d7();
}

void semcomp_runtime_at_d7d8(void) {
    runtime().routines().register_routine(0xD7D8, "at_d7d8");
    runtime().routines().note_invocation(0xD7D8);
    runtime().enemy_engine().at_d7d8();
}

void semcomp_runtime_at_cabf(void) {
    runtime().routines().register_routine(0xCABF, "at_cabf");
    runtime().routines().note_invocation(0xCABF);
    runtime().enemy_engine().at_cabf();
}

void semcomp_runtime_ex_sw_cc(void) {
    runtime().routines().register_routine(0xCCC6, "ExSwCC");
    runtime().routines().note_invocation(0xCCC6);
    runtime().enemy_engine().ex_sw_cc();
}

void semcomp_runtime_at_cbcd(void) {
    runtime().routines().register_routine(0xCBCD, "at_cbcd");
    runtime().routines().note_invocation(0xCBCD);
    runtime().enemy_engine().at_cbcd();
}

void semcomp_runtime_at_cc49(void) {
    runtime().routines().register_routine(0xCC49, "at_cc49");
    runtime().routines().note_invocation(0xCC49);
    runtime().enemy_engine().at_cc49();
}

void semcomp_runtime_at_d29d(void) {
    runtime().routines().register_routine(0xD29D, "at_d29d");
    runtime().routines().note_invocation(0xD29D);
    runtime().enemy_engine().at_d29d();
}

void semcomp_runtime_at_d8d3(void) {
    runtime().routines().register_routine(0xD8D3, "at_d8d3");
    runtime().routines().note_invocation(0xD8D3);
    runtime().enemy_engine().at_d8d3();
}

void semcomp_runtime_at_d036(void) {
    runtime().routines().register_routine(0xD036, "at_d036");
    runtime().routines().note_invocation(0xD036);
    runtime().enemy_engine().at_d036();
}

void semcomp_runtime_at_d033(void) {
    runtime().routines().register_routine(0xD033, "at_d033");
    runtime().routines().note_invocation(0xD033);
    runtime().enemy_engine().at_d033();
}

void semcomp_runtime_at_d091(void) {
    runtime().routines().register_routine(0xD091, "at_d091");
    runtime().routines().note_invocation(0xD091);
    runtime().enemy_engine().at_d091();
}

void semcomp_runtime_at_c9ec(void) {
    runtime().routines().register_routine(0xC9EC, "at_c9ec");
    runtime().routines().note_invocation(0xC9EC);
    runtime().enemy_engine().at_c9ec();
}

void semcomp_runtime_at_d0b5(void) {
    runtime().routines().register_routine(0xD0B5, "at_d0b5");
    runtime().routines().note_invocation(0xD0B5);
    runtime().enemy_engine().at_d0b5();
}

void semcomp_runtime_at_d03c(void) {
    runtime().routines().register_routine(0xD03C, "at_d03c");
    runtime().routines().note_invocation(0xD03C);
    runtime().enemy_engine().at_d03c();
}

void semcomp_runtime_remove_bridge(void) {
    runtime().routines().register_routine(0xD015, "RemoveBridge");
    runtime().routines().note_invocation(0xD015);
    runtime().enemy_engine().remove_bridge();
}

void semcomp_runtime_at_d0ec(void) {
    runtime().routines().register_routine(0xD0EC, "at_d0ec");
    runtime().routines().note_invocation(0xD0EC);
    runtime().enemy_engine().at_d0ec();
}

void semcomp_runtime_at_d0ed(void) {
    runtime().routines().register_routine(0xD0ED, "at_d0ed");
    runtime().routines().note_invocation(0xD0ED);
    runtime().enemy_engine().at_d0ed();
}

void semcomp_runtime_at_cdbd(void) {
    runtime().routines().register_routine(0xCDBD, "at_cdbd");
    runtime().routines().note_invocation(0xCDBD);
    runtime().enemy_engine().at_cdbd();
}

void semcomp_runtime_at_ca07(void) {
    runtime().routines().register_routine(0xCA07, "at_ca07");
    runtime().routines().note_invocation(0xCA07);
    runtime().enemy_engine().at_ca07();
}

void semcomp_runtime_at_d4ad(void) {
    runtime().routines().register_routine(0xD4AD, "at_d4ad");
    runtime().routines().note_invocation(0xD4AD);
    runtime().enemy_engine().at_d4ad();
}

void semcomp_runtime_at_d4ae(void) {
    runtime().routines().register_routine(0xD4AE, "at_d4ae");
    runtime().routines().note_invocation(0xD4AE);
    runtime().enemy_engine().at_d4ae();
}

void semcomp_runtime_at_d903(void) {
    runtime().routines().register_routine(0xD903, "at_d903");
    runtime().routines().note_invocation(0xD903);
    runtime().enemy_engine().at_d903();
}

void semcomp_runtime_at_d3ad(void) {
    runtime().routines().register_routine(0xD3AD, "at_d3ad");
    runtime().routines().note_invocation(0xD3AD);
    runtime().enemy_engine().at_d3ad();
}

void semcomp_runtime_at_d58d(void) {
    runtime().routines().register_routine(0xD58D, "at_d58d");
    runtime().routines().note_invocation(0xD58D);
    runtime().enemy_engine().at_d58d();
}

void semcomp_runtime_at_caa9(void) {
    runtime().routines().register_routine(0xCAA9, "at_caa9");
    runtime().routines().note_invocation(0xCAA9);
    runtime().enemy_engine().at_caa9();
}

void semcomp_runtime_at_d5af(void) {
    runtime().routines().register_routine(0xD5AF, "at_d5af");
    runtime().routines().note_invocation(0xD5AF);
    runtime().enemy_engine().at_d5af();
}

void semcomp_runtime_at_d04c(void) {
    runtime().routines().register_routine(0xD04C, "at_d04c");
    runtime().routines().note_invocation(0xD04C);
    runtime().enemy_engine().at_d04c();
}

void semcomp_runtime_at_d0f0(void) {
    runtime().routines().register_routine(0xD0F0, "at_d0f0");
    runtime().routines().note_invocation(0xD0F0);
    runtime().enemy_engine().at_d0f0();
}

void semcomp_runtime_at_d5ad(void) {
    runtime().routines().register_routine(0xD5AD, "at_d5ad");
    runtime().routines().note_invocation(0xD5AD);
    runtime().enemy_engine().at_d5ad();
}

void semcomp_runtime_at_d0c8(void) {
    runtime().routines().register_routine(0xD0C8, "at_d0c8");
    runtime().routines().note_invocation(0xD0C8);
    runtime().enemy_engine().at_d0c8();
}

void semcomp_runtime_at_d099(void) {
    runtime().routines().register_routine(0xD099, "at_d099");
    runtime().routines().note_invocation(0xD099);
    runtime().enemy_engine().at_d099();
}

void semcomp_runtime_at_c9f1(void) {
    runtime().routines().register_routine(0xC9F1, "at_c9f1");
    runtime().routines().note_invocation(0xC9F1);
    runtime().enemy_engine().at_c9f1();
}

void semcomp_runtime_at_c9f3(void) {
    runtime().routines().register_routine(0xC9F3, "at_c9f3");
    runtime().routines().note_invocation(0xC9F3);
    runtime().enemy_engine().at_c9f3();
}

void semcomp_runtime_at_d045(void) {
    runtime().routines().register_routine(0xD045, "at_d045");
    runtime().routines().note_invocation(0xD045);
    runtime().enemy_engine().at_d045();
}

void semcomp_runtime_at_cef4(void) {
    runtime().routines().register_routine(0xCEF4, "at_cef4");
    runtime().routines().note_invocation(0xCEF4);
    runtime().enemy_engine().at_cef4();
}

void semcomp_runtime_set_v_fbr(void) {
    runtime().routines().register_routine(0xCE03, "SetVFbr");
    runtime().routines().note_invocation(0xCE03);
    runtime().enemy_engine().set_v_fbr();
}

void semcomp_runtime_at_d0f6(void) {
    runtime().routines().register_routine(0xD0F6, "at_d0f6");
    runtime().routines().note_invocation(0xD0F6);
    runtime().enemy_engine().at_d0f6();
}

void semcomp_runtime_at_d0f4(void) {
    runtime().routines().register_routine(0xD0F4, "at_d0f4");
    runtime().routines().note_invocation(0xD0F4);
    runtime().enemy_engine().at_d0f4();
}

void semcomp_runtime_at_d4b1(void) {
    runtime().routines().register_routine(0xD4B1, "at_d4b1");
    runtime().routines().note_invocation(0xD4B1);
    runtime().enemy_engine().at_d4b1();
}

void semcomp_runtime_at_cba0(void) {
    runtime().routines().register_routine(0xCBA0, "at_cba0");
    runtime().routines().note_invocation(0xCBA0);
    runtime().enemy_engine().at_cba0();
}

void semcomp_runtime_at_ce40(void) {
    runtime().routines().register_routine(0xCE40, "at_ce40");
    runtime().routines().note_invocation(0xCE40);
    runtime().enemy_engine().at_ce40();
}

void semcomp_runtime_no_b_fall(void) {
    runtime().routines().register_routine(0xD05E, "NoBFall");
    runtime().routines().note_invocation(0xD05E);
    runtime().enemy_engine().no_b_fall();
}

void semcomp_runtime_at_d9b9(void) {
    runtime().routines().register_routine(0xD9B9, "at_d9b9");
    runtime().routines().note_invocation(0xD9B9);
    runtime().enemy_engine().at_d9b9();
}

void semcomp_runtime_at_d6b0(void) {
    runtime().routines().register_routine(0xD6B0, "at_d6b0");
    runtime().routines().note_invocation(0xD6B0);
    runtime().enemy_engine().at_d6b0();
}

void semcomp_runtime_at_cad7(void) {
    runtime().routines().register_routine(0xCAD7, "at_cad7");
    runtime().routines().note_invocation(0xCAD7);
    runtime().enemy_engine().at_cad7();
}

void semcomp_runtime_at_d3b9(void) {
    runtime().routines().register_routine(0xD3B9, "at_d3b9");
    runtime().routines().note_invocation(0xD3B9);
    runtime().enemy_engine().at_d3b9();
}

void semcomp_runtime_bowser_control(void) {
    runtime().routines().register_routine(0xD07F, "BowserControl");
    runtime().routines().note_invocation(0xD07F);
    runtime().enemy_engine().bowser_control();
}

void semcomp_runtime_at_cca8(void) {
    runtime().routines().register_routine(0xCCA8, "at_cca8");
    runtime().routines().note_invocation(0xCCA8);
    runtime().enemy_engine().at_cca8();
}

void semcomp_runtime_at_d0fb(void) {
    runtime().routines().register_routine(0xD0FB, "at_d0fb");
    runtime().routines().note_invocation(0xD0FB);
    runtime().enemy_engine().at_d0fb();
}

void semcomp_runtime_at_ca8e(void) {
    runtime().routines().register_routine(0xCA8E, "at_ca8e");
    runtime().routines().note_invocation(0xCA8E);
    runtime().enemy_engine().at_ca8e();
}

void semcomp_runtime_at_d03e(void) {
    runtime().routines().register_routine(0xD03E, "at_d03e");
    runtime().routines().note_invocation(0xD03E);
    runtime().enemy_engine().at_d03e();
}

void semcomp_runtime_chk_for_fall(void) {
    runtime().routines().register_routine(0xD44D, "ChkForFall");
    runtime().routines().note_invocation(0xD44D);
    runtime().enemy_engine().chk_for_fall();
}

void semcomp_runtime_at_d0f2(void) {
    runtime().routines().register_routine(0xD0F2, "at_d0f2");
    runtime().routines().note_invocation(0xD0F2);
    runtime().enemy_engine().at_d0f2();
}

void semcomp_runtime_move_swimming_cheep_cheep(void) {
    runtime().routines().register_routine(0xCC4A, "MoveSwimmingCheepCheep");
    runtime().routines().note_invocation(0xCC4A);
    runtime().enemy_engine().move_swimming_cheep_cheep();
}

void semcomp_runtime_at_cc4c(void) {
    runtime().routines().register_routine(0xCC4C, "at_cc4c");
    runtime().routines().note_invocation(0xCC4C);
    runtime().enemy_engine().at_cc4c();
}

void semcomp_runtime_player_enemy_collision(void) {
    runtime().routines().register_routine(0xD853, "PlayerEnemyCollision");
    runtime().routines().note_invocation(0xD853);
    runtime().enemy_engine().player_enemy_collision();
}

void semcomp_runtime_draw_vine(void) {
    runtime().routines().register_routine(0xE435, "DrawVine");
    runtime().routines().note_invocation(0xE435);
    runtime().enemy_engine().draw_vine();
}

void semcomp_runtime_ex_jc_gfx(void) {
    runtime().routines().register_routine(0xE6BD, "ExJCGfx");
    runtime().routines().note_invocation(0xE6BD);
    runtime().enemy_engine().ex_jc_gfx();
}

void semcomp_runtime_ex_ebg(void) {
    runtime().routines().register_routine(0xDFB8, "ExEBG");
    runtime().routines().note_invocation(0xDFB8);
    runtime().enemy_engine().ex_ebg();
}

void semcomp_runtime_at_e539(void) {
    runtime().routines().register_routine(0xE539, "at_e539");
    runtime().routines().note_invocation(0xE539);
    runtime().enemy_engine().at_e539();
}

void semcomp_runtime_at_daae(void) {
    runtime().routines().register_routine(0xDAAE, "at_daae");
    runtime().routines().note_invocation(0xDAAE);
    runtime().enemy_engine().at_daae();
}

void semcomp_runtime_at_e6f0(void) {
    runtime().routines().register_routine(0xE6F0, "at_e6f0");
    runtime().routines().note_invocation(0xE6F0);
    runtime().enemy_engine().at_e6f0();
}

void semcomp_runtime_at_e6f1(void) {
    runtime().routines().register_routine(0xE6F1, "at_e6f1");
    runtime().routines().note_invocation(0xE6F1);
    runtime().enemy_engine().at_e6f1();
}

void semcomp_runtime_at_da8d(void) {
    runtime().routines().register_routine(0xDA8D, "at_da8d");
    runtime().routines().note_invocation(0xDA8D);
    runtime().enemy_engine().at_da8d();
}

void semcomp_runtime_at_e00f(void) {
    runtime().routines().register_routine(0xE00F, "at_e00f");
    runtime().routines().note_invocation(0xE00F);
    runtime().enemy_engine().at_e00f();
}

void semcomp_runtime_at_e0ca(void) {
    runtime().routines().register_routine(0xE0CA, "at_e0ca");
    runtime().routines().note_invocation(0xE0CA);
    runtime().enemy_engine().at_e0ca();
}

void semcomp_runtime_at_dfc2(void) {
    runtime().routines().register_routine(0xDFC2, "at_dfc2");
    runtime().routines().note_invocation(0xDFC2);
    runtime().enemy_engine().at_dfc2();
}

void semcomp_runtime_at_e0a1(void) {
    runtime().routines().register_routine(0xE0A1, "at_e0a1");
    runtime().routines().note_invocation(0xE0A1);
    runtime().enemy_engine().at_e0a1();
}

void semcomp_runtime_at_e03d(void) {
    runtime().routines().register_routine(0xE03D, "at_e03d");
    runtime().routines().note_invocation(0xE03D);
    runtime().enemy_engine().at_e03d();
}

void semcomp_runtime_at_e401(void) {
    runtime().routines().register_routine(0xE401, "at_e401");
    runtime().routines().note_invocation(0xE401);
    runtime().enemy_engine().at_e401();
}

void semcomp_runtime_at_dfa9(void) {
    runtime().routines().register_routine(0xDFA9, "at_dfa9");
    runtime().routines().note_invocation(0xDFA9);
    runtime().enemy_engine().at_dfa9();
}

void semcomp_runtime_at_dfaa(void) {
    runtime().routines().register_routine(0xDFAA, "at_dfaa");
    runtime().routines().note_invocation(0xDFAA);
    runtime().enemy_engine().at_dfaa();
}

void semcomp_runtime_at_e058(void) {
    runtime().routines().register_routine(0xE058, "at_e058");
    runtime().routines().note_invocation(0xE058);
    runtime().enemy_engine().at_e058();
}

void semcomp_runtime_at_ddae(void) {
    runtime().routines().register_routine(0xDDAE, "at_ddae");
    runtime().routines().note_invocation(0xDDAE);
    runtime().enemy_engine().at_ddae();
}

void semcomp_runtime_at_dd8e(void) {
    runtime().routines().register_routine(0xDD8E, "at_dd8e");
    runtime().routines().note_invocation(0xDD8E);
    runtime().enemy_engine().at_dd8e();
}

void semcomp_runtime_cont_chk(void) {
    runtime().routines().register_routine(0xDD2D, "ContChk");
    runtime().routines().note_invocation(0xDD2D);
    runtime().enemy_engine().cont_chk();
}

void semcomp_runtime_at_dd0d(void) {
    runtime().routines().register_routine(0xDD0D, "at_dd0d");
    runtime().routines().note_invocation(0xDD0D);
    runtime().enemy_engine().at_dd0d();
}

void semcomp_runtime_at_e0e8(void) {
    runtime().routines().register_routine(0xE0E8, "at_e0e8");
    runtime().routines().note_invocation(0xE0E8);
    runtime().enemy_engine().at_e0e8();
}

void semcomp_runtime_at_db4d(void) {
    runtime().routines().register_routine(0xDB4D, "at_db4d");
    runtime().routines().note_invocation(0xDB4D);
    runtime().enemy_engine().at_db4d();
}

void semcomp_runtime_at_e08e(void) {
    runtime().routines().register_routine(0xE08E, "at_e08e");
    runtime().routines().note_invocation(0xE08E);
    runtime().enemy_engine().at_e08e();
}

void semcomp_runtime_at_dfca(void) {
    runtime().routines().register_routine(0xDFCA, "at_dfca");
    runtime().routines().note_invocation(0xDFCA);
    runtime().enemy_engine().at_dfca();
}

void semcomp_runtime_at_e274(void) {
    runtime().routines().register_routine(0xE274, "at_e274");
    runtime().routines().note_invocation(0xE274);
    runtime().enemy_engine().at_e274();
}

void semcomp_runtime_at_e800(void) {
    runtime().routines().register_routine(0xE800, "at_e800");
    runtime().routines().note_invocation(0xE800);
    runtime().enemy_engine().at_e800();
}

void semcomp_runtime_at_decb(void) {
    runtime().routines().register_routine(0xDECB, "at_decb");
    runtime().routines().note_invocation(0xDECB);
    runtime().enemy_engine().at_decb();
}

void semcomp_runtime_at_df21(void) {
    runtime().routines().register_routine(0xDF21, "at_df21");
    runtime().routines().note_invocation(0xDF21);
    runtime().enemy_engine().at_df21();
}

void semcomp_runtime_check_for_retainer_obj(void) {
    runtime().routines().register_routine(0xE8A9, "CheckForRetainerObj");
    runtime().routines().note_invocation(0xE8A9);
    runtime().enemy_engine().check_for_retainer_obj();
}

void semcomp_runtime_at_e003(void) {
    runtime().routines().register_routine(0xE003, "at_e003");
    runtime().routines().note_invocation(0xE003);
    runtime().enemy_engine().at_e003();
}

void semcomp_runtime_at_e5cf(void) {
    runtime().routines().register_routine(0xE5CF, "at_e5cf");
    runtime().routines().note_invocation(0xE5CF);
    runtime().enemy_engine().at_e5cf();
}

void semcomp_runtime_at_e5d0(void) {
    runtime().routines().register_routine(0xE5D0, "at_e5d0");
    runtime().routines().note_invocation(0xE5D0);
    runtime().enemy_engine().at_e5d0();
}

void semcomp_runtime_at_e606(void) {
    runtime().routines().register_routine(0xE606, "at_e606");
    runtime().routines().note_invocation(0xE606);
    runtime().enemy_engine().at_e606();
}

void semcomp_runtime_at_e609(void) {
    runtime().routines().register_routine(0xE609, "at_e609");
    runtime().routines().note_invocation(0xE609);
    runtime().enemy_engine().at_e609();
}

void semcomp_runtime_at_e60a(void) {
    runtime().routines().register_routine(0xE60A, "at_e60a");
    runtime().routines().note_invocation(0xE60A);
    runtime().enemy_engine().at_e60a();
}

void semcomp_runtime_at_e605(void) {
    runtime().routines().register_routine(0xE605, "at_e605");
    runtime().routines().note_invocation(0xE605);
    runtime().enemy_engine().at_e605();
}

void semcomp_runtime_at_e6cd(void) {
    runtime().routines().register_routine(0xE6CD, "at_e6cd");
    runtime().routines().note_invocation(0xE6CD);
    runtime().enemy_engine().at_e6cd();
}

void semcomp_runtime_at_e802(void) {
    runtime().routines().register_routine(0xE802, "at_e802");
    runtime().routines().note_invocation(0xE802);
    runtime().enemy_engine().at_e802();
}

void semcomp_runtime_at_dab9(void) {
    runtime().routines().register_routine(0xDAB9, "at_dab9");
    runtime().routines().note_invocation(0xDAB9);
    runtime().enemy_engine().at_dab9();
}

void semcomp_runtime_at_dc8e(void) {
    runtime().routines().register_routine(0xDC8E, "at_dc8e");
    runtime().routines().note_invocation(0xDC8E);
    runtime().enemy_engine().at_dc8e();
}

void semcomp_runtime_at_dccd(void) {
    runtime().routines().register_routine(0xDCCD, "at_dccd");
    runtime().routines().note_invocation(0xDCCD);
    runtime().enemy_engine().at_dccd();
}

void semcomp_runtime_no_bump(void) {
    runtime().routines().register_routine(0xE131, "NoBump");
    runtime().routines().note_invocation(0xE131);
    runtime().enemy_engine().no_bump();
}

void semcomp_runtime_at_e603(void) {
    runtime().routines().register_routine(0xE603, "at_e603");
    runtime().routines().note_invocation(0xE603);
    runtime().enemy_engine().at_e603();
}

void semcomp_runtime_at_e8c9(void) {
    runtime().routines().register_routine(0xE8C9, "at_e8c9");
    runtime().routines().note_invocation(0xE8C9);
    runtime().enemy_engine().at_e8c9();
}

void semcomp_runtime_at_e40d(void) {
    runtime().routines().register_routine(0xE40D, "at_e40d");
    runtime().routines().note_invocation(0xE40D);
    runtime().enemy_engine().at_e40d();
}

void semcomp_runtime_at_e029(void) {
    runtime().routines().register_routine(0xE029, "at_e029");
    runtime().routines().note_invocation(0xE029);
    runtime().enemy_engine().at_e029();
}

void semcomp_runtime_at_dc1a(void) {
    runtime().routines().register_routine(0xDC1A, "at_dc1a");
    runtime().routines().note_invocation(0xDC1A);
    runtime().enemy_engine().at_dc1a();
}

void semcomp_runtime_at_e56f(void) {
    runtime().routines().register_routine(0xE56F, "at_e56f");
    runtime().routines().note_invocation(0xE56F);
    runtime().enemy_engine().at_e56f();
}

void semcomp_runtime_at_e818(void) {
    runtime().routines().register_routine(0xE818, "at_e818");
    runtime().routines().note_invocation(0xE818);
    runtime().enemy_engine().at_e818();
}

void semcomp_runtime_at_e857(void) {
    runtime().routines().register_routine(0xE857, "at_e857");
    runtime().routines().note_invocation(0xE857);
    runtime().enemy_engine().at_e857();
}

void semcomp_runtime_at_e858(void) {
    runtime().routines().register_routine(0xE858, "at_e858");
    runtime().routines().note_invocation(0xE858);
    runtime().enemy_engine().at_e858();
}

void semcomp_runtime_at_e1d1(void) {
    runtime().routines().register_routine(0xE1D1, "at_e1d1");
    runtime().routines().note_invocation(0xE1D1);
    runtime().enemy_engine().at_e1d1();
}

void semcomp_runtime_at_dfc0(void) {
    runtime().routines().register_routine(0xDFC0, "at_dfc0");
    runtime().routines().note_invocation(0xDFC0);
    runtime().enemy_engine().at_dfc0();
}

void semcomp_runtime_at_daab(void) {
    runtime().routines().register_routine(0xDAAB, "at_daab");
    runtime().routines().note_invocation(0xDAAB);
    runtime().enemy_engine().at_daab();
}

void semcomp_runtime_at_dc55(void) {
    runtime().routines().register_routine(0xDC55, "at_dc55");
    runtime().routines().note_invocation(0xDC55);
    runtime().enemy_engine().at_dc55();
}

void semcomp_runtime_at_e60d(void) {
    runtime().routines().register_routine(0xE60D, "at_e60d");
    runtime().routines().note_invocation(0xE60D);
    runtime().enemy_engine().at_e60d();
}

void semcomp_runtime_at_e60e(void) {
    runtime().routines().register_routine(0xE60E, "at_e60e");
    runtime().routines().note_invocation(0xE60E);
    runtime().enemy_engine().at_e60e();
}

void semcomp_runtime_at_dc16(void) {
    runtime().routines().register_routine(0xDC16, "at_dc16");
    runtime().routines().note_invocation(0xDC16);
    runtime().enemy_engine().at_dc16();
}

void semcomp_runtime_player_pos_s_plat_data(void) {
    runtime().routines().register_routine(0xDC17, "PlayerPosSPlatData");
    runtime().routines().note_invocation(0xDC17);
    runtime().enemy_engine().player_pos_s_plat_data();
}

void semcomp_runtime_block_buffer_adder_data(void) {
    runtime().routines().register_routine(0xE3AD, "BlockBufferAdderData");
    runtime().routines().note_invocation(0xE3AD);
    runtime().enemy_engine().block_buffer_adder_data();
}

void semcomp_runtime_pipe_dwn_s(void) {
    runtime().routines().register_routine(0xDDCE, "PipeDwnS");
    runtime().routines().note_invocation(0xDDCE);
    runtime().enemy_engine().pipe_dwn_s();
}

void semcomp_runtime_player_bg_upper_extent(void) {
    runtime().routines().register_routine(0xDC62, "PlayerBGUpperExtent");
    runtime().routines().note_invocation(0xDC62);
    runtime().enemy_engine().player_bg_upper_extent();
}

void semcomp_runtime_at_df90(void) {
    runtime().routines().register_routine(0xDF90, "at_df90");
    runtime().routines().note_invocation(0xDF90);
    runtime().enemy_engine().at_df90();
}

void semcomp_runtime_at_e820(void) {
    runtime().routines().register_routine(0xE820, "at_e820");
    runtime().routines().note_invocation(0xE820);
    runtime().enemy_engine().at_e820();
}

void semcomp_runtime_at_df9b(void) {
    runtime().routines().register_routine(0xDF9B, "at_df9b");
    runtime().routines().note_invocation(0xDF9B);
    runtime().enemy_engine().at_df9b();
}

void semcomp_runtime_at_e4c9(void) {
    runtime().routines().register_routine(0xE4C9, "at_e4c9");
    runtime().routines().note_invocation(0xE4C9);
    runtime().enemy_engine().at_e4c9();
}

void semcomp_runtime_at_e4ca(void) {
    runtime().routines().register_routine(0xE4CA, "at_e4ca");
    runtime().routines().note_invocation(0xE4CA);
    runtime().enemy_engine().at_e4ca();
}

void semcomp_runtime_at_de2f(void) {
    runtime().routines().register_routine(0xDE2F, "at_de2f");
    runtime().routines().note_invocation(0xDE2F);
    runtime().enemy_engine().at_de2f();
}

void semcomp_runtime_at_dd20(void) {
    runtime().routines().register_routine(0xDD20, "at_dd20");
    runtime().routines().note_invocation(0xDD20);
    runtime().enemy_engine().at_dd20();
}

void semcomp_runtime_area_change_timer_data(void) {
    runtime().routines().register_routine(0xDE03, "AreaChangeTimerData");
    runtime().routines().note_invocation(0xDE03);
    runtime().enemy_engine().area_change_timer_data();
}

void semcomp_runtime_at_de8e(void) {
    runtime().routines().register_routine(0xDE8E, "at_de8e");
    runtime().routines().note_invocation(0xDE8E);
    runtime().enemy_engine().at_de8e();
}

void semcomp_runtime_at_dd07(void) {
    runtime().routines().register_routine(0xDD07, "at_dd07");
    runtime().routines().note_invocation(0xDD07);
    runtime().enemy_engine().at_dd07();
}

void semcomp_runtime_flagpole_y_pos_data(void) {
    runtime().routines().register_routine(0xDE29, "FlagpoleYPosData");
    runtime().routines().note_invocation(0xDE29);
    runtime().enemy_engine().flagpole_y_pos_data();
}

void semcomp_runtime_climb_x_pos_adder(void) {
    runtime().routines().register_routine(0xDE25, "ClimbXPosAdder");
    runtime().routines().note_invocation(0xDE25);
    runtime().enemy_engine().climb_x_pos_adder();
}

void semcomp_runtime_at_db8e(void) {
    runtime().routines().register_routine(0xDB8E, "at_db8e");
    runtime().routines().note_invocation(0xDB8E);
    runtime().enemy_engine().at_db8e();
}

void semcomp_runtime_at_e807(void) {
    runtime().routines().register_routine(0xE807, "at_e807");
    runtime().routines().note_invocation(0xE807);
    runtime().enemy_engine().at_e807();
}

void semcomp_runtime_at_e80a(void) {
    runtime().routines().register_routine(0xE80A, "at_e80a");
    runtime().routines().note_invocation(0xE80A);
    runtime().enemy_engine().at_e80a();
}

void semcomp_runtime_at_dfb1(void) {
    runtime().routines().register_routine(0xDFB1, "at_dfb1");
    runtime().routines().note_invocation(0xDFB1);
    runtime().enemy_engine().at_dfb1();
}

void semcomp_runtime_at_dde0(void) {
    runtime().routines().register_routine(0xDDE0, "at_dde0");
    runtime().routines().note_invocation(0xDDE0);
    runtime().enemy_engine().at_dde0();
}

void semcomp_runtime_solid_m_tile_upper_ext(void) {
    runtime().routines().register_routine(0xDF8B, "SolidMTileUpperExt");
    runtime().routines().note_invocation(0xDF8B);
    runtime().enemy_engine().solid_m_tile_upper_ext();
}

void semcomp_runtime_climb_m_tile_upper_ext(void) {
    runtime().routines().register_routine(0xDF96, "ClimbMTileUpperExt");
    runtime().routines().note_invocation(0xDF96);
    runtime().enemy_engine().climb_m_tile_upper_ext();
}

void semcomp_runtime_at_e090(void) {
    runtime().routines().register_routine(0xE090, "at_e090");
    runtime().routines().note_invocation(0xE090);
    runtime().enemy_engine().at_e090();
}

void semcomp_runtime_enemy_bgc_state_data(void) {
    runtime().routines().register_routine(0xDFB9, "EnemyBGCStateData");
    runtime().routines().note_invocation(0xDFB9);
    runtime().enemy_engine().enemy_bgc_state_data();
}

void semcomp_runtime_at_e389(void) {
    runtime().routines().register_routine(0xE389, "at_e389");
    runtime().routines().note_invocation(0xE389);
    runtime().enemy_engine().at_e389();
}

void semcomp_runtime_at_e791(void) {
    runtime().routines().register_routine(0xE791, "at_e791");
    runtime().routines().note_invocation(0xE791);
    runtime().enemy_engine().at_e791();
}

void semcomp_runtime_no_c_dir_f(void) {
    runtime().routines().register_routine(0xE060, "NoCDirF");
    runtime().routines().note_invocation(0xE060);
    runtime().enemy_engine().no_c_dir_f();
}

void semcomp_runtime_at_e061(void) {
    runtime().routines().register_routine(0xE061, "at_e061");
    runtime().routines().note_invocation(0xE061);
    runtime().enemy_engine().at_e061();
}

void semcomp_runtime_at_e27d(void) {
    runtime().routines().register_routine(0xE27D, "at_e27d");
    runtime().routines().note_invocation(0xE27D);
    runtime().enemy_engine().at_e27d();
}

void semcomp_runtime_at_e1fe(void) {
    runtime().routines().register_routine(0xE1FE, "at_e1fe");
    runtime().routines().note_invocation(0xE1FE);
    runtime().enemy_engine().at_e1fe();
}

void semcomp_runtime_at_e1ff(void) {
    runtime().routines().register_routine(0xE1FF, "at_e1ff");
    runtime().routines().note_invocation(0xE1FF);
    runtime().enemy_engine().at_e1ff();
}

void semcomp_runtime_at_e804(void) {
    runtime().routines().register_routine(0xE804, "at_e804");
    runtime().routines().note_invocation(0xE804);
    runtime().enemy_engine().at_e804();
}

void semcomp_runtime_at_dd04(void) {
    runtime().routines().register_routine(0xDD04, "at_dd04");
    runtime().routines().note_invocation(0xDD04);
    runtime().enemy_engine().at_dd04();
}

void semcomp_runtime_at_dd2a(void) {
    runtime().routines().register_routine(0xDD2A, "at_dd2a");
    runtime().routines().note_invocation(0xDD2A);
    runtime().enemy_engine().at_dd2a();
}

void semcomp_runtime_at_dd3b(void) {
    runtime().routines().register_routine(0xDD3B, "at_dd3b");
    runtime().routines().note_invocation(0xDD3B);
    runtime().enemy_engine().at_dd3b();
}

void semcomp_runtime_at_dd60(void) {
    runtime().routines().register_routine(0xDD60, "at_dd60");
    runtime().routines().note_invocation(0xDD60);
    runtime().enemy_engine().at_dd60();
}

void semcomp_runtime_at_dd61(void) {
    runtime().routines().register_routine(0xDD61, "at_dd61");
    runtime().routines().note_invocation(0xDD61);
    runtime().enemy_engine().at_dd61();
}

void semcomp_runtime_award_touched_coin(void) {
    runtime().routines().register_routine(0xDD1A, "AwardTouchedCoin");
    runtime().routines().note_invocation(0xDD1A);
    runtime().enemy_engine().award_touched_coin();
}

void semcomp_runtime_at_e3f1(void) {
    runtime().routines().register_routine(0xE3F1, "at_e3f1");
    runtime().routines().note_invocation(0xE3F1);
    runtime().enemy_engine().at_e3f1();
}

void semcomp_runtime_block_buffer_x_adder(void) {
    runtime().routines().register_routine(0xE3B0, "BlockBuffer_X_Adder");
    runtime().routines().note_invocation(0xE3B0);
    runtime().enemy_engine().block_buffer_x_adder();
}

void semcomp_runtime_at_e121(void) {
    runtime().routines().register_routine(0xE121, "at_e121");
    runtime().routines().note_invocation(0xE121);
    runtime().enemy_engine().at_e121();
}

void semcomp_runtime_at_e3cd(void) {
    runtime().routines().register_routine(0xE3CD, "at_e3cd");
    runtime().routines().note_invocation(0xE3CD);
    runtime().enemy_engine().at_e3cd();
}

void semcomp_runtime_at_e1a9(void) {
    runtime().routines().register_routine(0xE1A9, "at_e1a9");
    runtime().routines().note_invocation(0xE1A9);
    runtime().enemy_engine().at_e1a9();
}

void semcomp_runtime_at_e0a9(void) {
    runtime().routines().register_routine(0xE0A9, "at_e0a9");
    runtime().routines().note_invocation(0xE0A9);
    runtime().enemy_engine().at_e0a9();
}

void semcomp_runtime_first_spr_y_pos(void) {
    runtime().routines().register_routine(0xE4C4, "FirstSprYPos");
    runtime().routines().note_invocation(0xE4C4);
    runtime().enemy_engine().first_spr_y_pos();
}

void semcomp_runtime_at_e4c5(void) {
    runtime().routines().register_routine(0xE4C5, "at_e4c5");
    runtime().routines().note_invocation(0xE4C5);
    runtime().enemy_engine().at_e4c5();
}

void semcomp_runtime_second_spr_y_pos(void) {
    runtime().routines().register_routine(0xE4CC, "SecondSprYPos");
    runtime().routines().note_invocation(0xE4CC);
    runtime().enemy_engine().second_spr_y_pos();
}

void semcomp_runtime_at_e4cd(void) {
    runtime().routines().register_routine(0xE4CD, "at_e4cd");
    runtime().routines().note_invocation(0xE4CD);
    runtime().enemy_engine().at_e4cd();
}

void semcomp_runtime_first_spr_x_pos(void) {
    runtime().routines().register_routine(0xE4C0, "FirstSprXPos");
    runtime().routines().note_invocation(0xE4C0);
    runtime().enemy_engine().first_spr_x_pos();
}

void semcomp_runtime_first_spr_tilenum(void) {
    runtime().routines().register_routine(0xE4D0, "FirstSprTilenum");
    runtime().routines().note_invocation(0xE4D0);
    runtime().enemy_engine().first_spr_tilenum();
}

void semcomp_runtime_second_spr_tilenum(void) {
    runtime().routines().register_routine(0xE4D4, "SecondSprTilenum");
    runtime().routines().note_invocation(0xE4D4);
    runtime().enemy_engine().second_spr_tilenum();
}

void semcomp_runtime_flagpole_score_num_tiles(void) {
    runtime().routines().register_routine(0xE541, "FlagpoleScoreNumTiles");
    runtime().routines().note_invocation(0xE541);
    runtime().enemy_engine().flagpole_score_num_tiles();
}

void semcomp_runtime_at_dbd6(void) {
    runtime().routines().register_routine(0xDBD6, "at_dbd6");
    runtime().routines().note_invocation(0xDBD6);
    runtime().enemy_engine().at_dbd6();
}

void semcomp_runtime_at_dbb5(void) {
    runtime().routines().register_routine(0xDBB5, "at_dbb5");
    runtime().routines().note_invocation(0xDBB5);
    runtime().enemy_engine().at_dbb5();
}

void semcomp_runtime_power_up_gfx_table(void) {
    runtime().routines().register_routine(0xE6BE, "PowerUpGfxTable");
    runtime().routines().note_invocation(0xE6BE);
    runtime().enemy_engine().power_up_gfx_table();
}

void semcomp_runtime_jumping_coin_tiles(void) {
    runtime().routines().register_routine(0xE682, "JumpingCoinTiles");
    runtime().routines().note_invocation(0xE682);
    runtime().enemy_engine().jumping_coin_tiles();
}

void semcomp_runtime_at_e683(void) {
    runtime().routines().register_routine(0xE683, "at_e683");
    runtime().routines().note_invocation(0xE683);
    runtime().enemy_engine().at_e683();
}

void semcomp_runtime_at_e48d(void) {
    runtime().routines().register_routine(0xE48D, "at_e48d");
    runtime().routines().note_invocation(0xE48D);
    runtime().enemy_engine().at_e48d();
}

void semcomp_runtime_at_e4e4(void) {
    runtime().routines().register_routine(0xE4E4, "at_e4e4");
    runtime().routines().note_invocation(0xE4E4);
    runtime().enemy_engine().at_e4e4();
}

void semcomp_runtime_at_e6c0(void) {
    runtime().routines().register_routine(0xE6C0, "at_e6c0");
    runtime().routines().note_invocation(0xE6C0);
    runtime().enemy_engine().at_e6c0();
}

void semcomp_runtime_at_dcfc(void) {
    runtime().routines().register_routine(0xDCFC, "at_dcfc");
    runtime().routines().note_invocation(0xDCFC);
    runtime().enemy_engine().at_dcfc();
}

void semcomp_runtime_at_dcdd(void) {
    runtime().routines().register_routine(0xDCDD, "at_dcdd");
    runtime().routines().note_invocation(0xDCDD);
    runtime().enemy_engine().at_dcdd();
}

void semcomp_runtime_at_dfdc(void) {
    runtime().routines().register_routine(0xDFDC, "at_dfdc");
    runtime().routines().note_invocation(0xDFDC);
    runtime().enemy_engine().at_dfdc();
}

void semcomp_runtime_hb_chk(void) {
    runtime().routines().register_routine(0xDFDF, "HBChk");
    runtime().routines().note_invocation(0xDFDF);
    runtime().enemy_engine().hb_chk();
}

void semcomp_runtime_at_dcdf(void) {
    runtime().routines().register_routine(0xDCDF, "at_dcdf");
    runtime().routines().note_invocation(0xDCDF);
    runtime().enemy_engine().at_dcdf();
}

void semcomp_runtime_at_dddc(void) {
    runtime().routines().register_routine(0xDDDC, "at_dddc");
    runtime().routines().note_invocation(0xDDDC);
    runtime().enemy_engine().at_dddc();
}

void semcomp_runtime_at_ddde(void) {
    runtime().routines().register_routine(0xDDDE, "at_ddde");
    runtime().routines().note_invocation(0xDDDE);
    runtime().enemy_engine().at_ddde();
}

void semcomp_runtime_at_dedf(void) {
    runtime().routines().register_routine(0xDEDF, "at_dedf");
    runtime().routines().note_invocation(0xDEDF);
    runtime().enemy_engine().at_dedf();
}

void semcomp_runtime_at_da7b(void) {
    runtime().routines().register_routine(0xDA7B, "at_da7b");
    runtime().routines().note_invocation(0xDA7B);
    runtime().enemy_engine().at_da7b();
}

void semcomp_runtime_at_dbda(void) {
    runtime().routines().register_routine(0xDBDA, "at_dbda");
    runtime().routines().note_invocation(0xDBDA);
    runtime().enemy_engine().at_dbda();
}

void semcomp_runtime_at_e3d4(void) {
    runtime().routines().register_routine(0xE3D4, "at_e3d4");
    runtime().routines().note_invocation(0xE3D4);
    runtime().enemy_engine().at_e3d4();
}

void semcomp_runtime_at_e2e4(void) {
    runtime().routines().register_routine(0xE2E4, "at_e2e4");
    runtime().routines().note_invocation(0xE2E4);
    runtime().enemy_engine().at_e2e4();
}

void semcomp_runtime_at_e58a(void) {
    runtime().routines().register_routine(0xE58A, "at_e58a");
    runtime().routines().note_invocation(0xE58A);
    runtime().enemy_engine().at_e58a();
}

void semcomp_runtime_at_e6e7(void) {
    runtime().routines().register_routine(0xE6E7, "at_e6e7");
    runtime().routines().note_invocation(0xE6E7);
    runtime().enemy_engine().at_e6e7();
}

void semcomp_runtime_at_e7e9(void) {
    runtime().routines().register_routine(0xE7E9, "at_e7e9");
    runtime().routines().note_invocation(0xE7E9);
    runtime().enemy_engine().at_e7e9();
}

void semcomp_runtime_jumpspring_frame_offsets(void) {
    runtime().routines().register_routine(0xE878, "JumpspringFrameOffsets");
    runtime().routines().note_invocation(0xE878);
    runtime().enemy_engine().jumpspring_frame_offsets();
}

void semcomp_runtime_at_e879(void) {
    runtime().routines().register_routine(0xE879, "at_e879");
    runtime().routines().note_invocation(0xE879);
    runtime().enemy_engine().at_e879();
}

void semcomp_runtime_enemy_gfx_table_offsets(void) {
    runtime().routines().register_routine(0xE840, "EnemyGfxTableOffsets");
    runtime().routines().note_invocation(0xE840);
    runtime().enemy_engine().enemy_gfx_table_offsets();
}

void semcomp_runtime_at_dea3(void) {
    runtime().routines().register_routine(0xDEA3, "at_dea3");
    runtime().routines().note_invocation(0xDEA3);
    runtime().enemy_engine().at_dea3();
}

void semcomp_runtime_next_v_sp(void) {
    runtime().routines().register_routine(0xE4A2, "NextVSp");
    runtime().routines().note_invocation(0xE4A2);
    runtime().enemy_engine().next_v_sp();
}

void semcomp_runtime_at_e4a3(void) {
    runtime().routines().register_routine(0xE4A3, "at_e4a3");
    runtime().routines().note_invocation(0xE4A3);
    runtime().enemy_engine().at_e4a3();
}

void semcomp_runtime_at_e0ea(void) {
    runtime().routines().register_routine(0xE0EA, "at_e0ea");
    runtime().routines().note_invocation(0xE0EA);
    runtime().enemy_engine().at_e0ea();
}

void semcomp_runtime_at_e67f(void) {
    runtime().routines().register_routine(0xE67F, "at_e67f");
    runtime().routines().note_invocation(0xE67F);
    runtime().enemy_engine().at_e67f();
}

void semcomp_runtime_at_e672(void) {
    runtime().routines().register_routine(0xE672, "at_e672");
    runtime().routines().note_invocation(0xE672);
    runtime().enemy_engine().at_e672();
}

void semcomp_runtime_at_e667(void) {
    runtime().routines().register_routine(0xE667, "at_e667");
    runtime().routines().note_invocation(0xE667);
    runtime().enemy_engine().at_e667();
}

void semcomp_runtime_at_e01d(void) {
    runtime().routines().register_routine(0xE01D, "at_e01d");
    runtime().routines().note_invocation(0xE01D);
    runtime().enemy_engine().at_e01d();
}

void semcomp_runtime_at_e04e(void) {
    runtime().routines().register_routine(0xE04E, "at_e04e");
    runtime().routines().note_invocation(0xE04E);
    runtime().enemy_engine().at_e04e();
}

void semcomp_runtime_at_e646(void) {
    runtime().routines().register_routine(0xE646, "at_e646");
    runtime().routines().note_invocation(0xE646);
    runtime().enemy_engine().at_e646();
}

void semcomp_runtime_enemy_anim_timing_b_mask(void) {
    runtime().routines().register_routine(0xE876, "EnemyAnimTimingBMask");
    runtime().routines().note_invocation(0xE876);
    runtime().enemy_engine().enemy_anim_timing_b_mask();
}

void semcomp_runtime_at_e877(void) {
    runtime().routines().register_routine(0xE877, "at_e877");
    runtime().routines().note_invocation(0xE877);
    runtime().enemy_engine().at_e877();
}

void semcomp_runtime_at_e005(void) {
    runtime().routines().register_routine(0xE005, "at_e005");
    runtime().routines().note_invocation(0xE005);
    runtime().enemy_engine().at_e005();
}

void semcomp_runtime_at_e041(void) {
    runtime().routines().register_routine(0xE041, "at_e041");
    runtime().routines().note_invocation(0xE041);
    runtime().enemy_engine().at_e041();
}

void semcomp_runtime_at_e007(void) {
    runtime().routines().register_routine(0xE007, "at_e007");
    runtime().routines().note_invocation(0xE007);
    runtime().enemy_engine().at_e007();
}

void semcomp_runtime_enemy_graphics_table(void) {
    runtime().routines().register_routine(0xE73E, "EnemyGraphicsTable");
    runtime().routines().note_invocation(0xE73E);
    runtime().enemy_engine().enemy_graphics_table();
}

void semcomp_runtime_at_e57d(void) {
    runtime().routines().register_routine(0xE57D, "at_e57d");
    runtime().routines().note_invocation(0xE57D);
    runtime().enemy_engine().at_e57d();
}

void semcomp_runtime_chk2_msb_st(void) {
    runtime().routines().register_routine(0xE0EC, "Chk2MSBSt");
    runtime().routines().note_invocation(0xE0EC);
    runtime().enemy_engine().chk2_msb_st();
}

void semcomp_runtime_check_for_bullet_bill_cv(void) {
    runtime().routines().register_routine(0xE8BE, "CheckForBulletBillCV");
    runtime().routines().note_invocation(0xE8BE);
    runtime().enemy_engine().check_for_bullet_bill_cv();
}

void semcomp_runtime_set_wy_spd(void) {
    runtime().routines().register_routine(0xE048, "SetWYSpd");
    runtime().routines().note_invocation(0xE048);
    runtime().enemy_engine().set_wy_spd();
}

void semcomp_runtime_at_e0ab(void) {
    runtime().routines().register_routine(0xE0AB, "at_e0ab");
    runtime().routines().note_invocation(0xE0AB);
    runtime().enemy_engine().at_e0ab();
}

void semcomp_runtime_at_e4ad(void) {
    runtime().routines().register_routine(0xE4AD, "at_e4ad");
    runtime().routines().note_invocation(0xE4AD);
    runtime().enemy_engine().at_e4ad();
}

void semcomp_runtime_at_e7bd(void) {
    runtime().routines().register_routine(0xE7BD, "at_e7bd");
    runtime().routines().note_invocation(0xE7BD);
    runtime().enemy_engine().at_e7bd();
}

void semcomp_runtime_at_dc20(void) {
    runtime().routines().register_routine(0xDC20, "at_dc20");
    runtime().routines().note_invocation(0xDC20);
    runtime().enemy_engine().at_dc20();
}

void semcomp_runtime_at_def0(void) {
    runtime().routines().register_routine(0xDEF0, "at_def0");
    runtime().routines().note_invocation(0xDEF0);
    runtime().enemy_engine().at_def0();
}

void semcomp_runtime_at_e8a8(void) {
    runtime().routines().register_routine(0xE8A8, "at_e8a8");
    runtime().routines().note_invocation(0xE8A8);
    runtime().enemy_engine().at_e8a8();
}

void semcomp_runtime_at_e0d0(void) {
    runtime().routines().register_routine(0xE0D0, "at_e0d0");
    runtime().routines().note_invocation(0xE0D0);
    runtime().enemy_engine().at_e0d0();
}

void semcomp_runtime_at_dcd1(void) {
    runtime().routines().register_routine(0xDCD1, "at_dcd1");
    runtime().routines().note_invocation(0xDCD1);
    runtime().enemy_engine().at_dcd1();
}

void semcomp_runtime_p_up_draw_loop(void) {
    runtime().routines().register_routine(0xE6F7, "PUpDrawLoop");
    runtime().routines().note_invocation(0xE6F7);
    runtime().enemy_engine().p_up_draw_loop();
}

void semcomp_runtime_at_e6fa(void) {
    runtime().routines().register_routine(0xE6FA, "at_e6fa");
    runtime().routines().note_invocation(0xE6FA);
    runtime().enemy_engine().at_e6fa();
}

void semcomp_runtime_at_e301(void) {
    runtime().routines().register_routine(0xE301, "at_e301");
    runtime().routines().note_invocation(0xE301);
    runtime().enemy_engine().at_e301();
}

void semcomp_runtime_at_ddd5(void) {
    runtime().routines().register_routine(0xDDD5, "at_ddd5");
    runtime().routines().note_invocation(0xDDD5);
    runtime().enemy_engine().at_ddd5();
}

void semcomp_runtime_at_e3de(void) {
    runtime().routines().register_routine(0xE3DE, "at_e3de");
    runtime().routines().note_invocation(0xE3DE);
    runtime().enemy_engine().at_e3de();
}

void semcomp_runtime_at_dfda(void) {
    runtime().routines().register_routine(0xDFDA, "at_dfda");
    runtime().routines().note_invocation(0xDFDA);
    runtime().enemy_engine().at_dfda();
}

void semcomp_runtime_ex_ste_chk(void) {
    runtime().routines().register_routine(0xE0A4, "ExSteChk");
    runtime().routines().note_invocation(0xE0A4);
    runtime().enemy_engine().ex_ste_chk();
}

void semcomp_runtime_at_e763(void) {
    runtime().routines().register_routine(0xE763, "at_e763");
    runtime().routines().note_invocation(0xE763);
    runtime().enemy_engine().at_e763();
}

void semcomp_runtime_at_e1e4(void) {
    runtime().routines().register_routine(0xE1E4, "at_e1e4");
    runtime().routines().note_invocation(0xE1E4);
    runtime().enemy_engine().at_e1e4();
}

void semcomp_runtime_at_e3e1(void) {
    runtime().routines().register_routine(0xE3E1, "at_e3e1");
    runtime().routines().note_invocation(0xE3E1);
    runtime().enemy_engine().at_e3e1();
}

void semcomp_runtime_at_e3e2(void) {
    runtime().routines().register_routine(0xE3E2, "at_e3e2");
    runtime().routines().note_invocation(0xE3E2);
    runtime().enemy_engine().at_e3e2();
}

void semcomp_runtime_at_de1e(void) {
    runtime().routines().register_routine(0xDE1E, "at_de1e");
    runtime().routines().note_invocation(0xDE1E);
    runtime().enemy_engine().at_de1e();
}

void semcomp_runtime_at_e0df(void) {
    runtime().routines().register_routine(0xE0DF, "at_e0df");
    runtime().routines().note_invocation(0xE0DF);
    runtime().enemy_engine().at_e0df();
}

void semcomp_runtime_at_df01(void) {
    runtime().routines().register_routine(0xDF01, "at_df01");
    runtime().routines().note_invocation(0xDF01);
    runtime().enemy_engine().at_df01();
}

void semcomp_runtime_side_check_loop(void) {
    runtime().routines().register_routine(0xDD66, "SideCheckLoop");
    runtime().routines().note_invocation(0xDD66);
    runtime().enemy_engine().side_check_loop();
}

void semcomp_runtime_at_e7e6(void) {
    runtime().routines().register_routine(0xE7E6, "at_e7e6");
    runtime().routines().note_invocation(0xE7E6);
    runtime().enemy_engine().at_e7e6();
}

void semcomp_runtime_at_de59(void) {
    runtime().routines().register_routine(0xDE59, "at_de59");
    runtime().routines().note_invocation(0xDE59);
    runtime().enemy_engine().at_de59();
}

void semcomp_runtime_at_e850(void) {
    runtime().routines().register_routine(0xE850, "at_e850");
    runtime().routines().note_invocation(0xE850);
    runtime().enemy_engine().at_e850();
}

void semcomp_runtime_at_df77(void) {
    runtime().routines().register_routine(0xDF77, "at_df77");
    runtime().routines().note_invocation(0xDF77);
    runtime().enemy_engine().at_df77();
}

void semcomp_runtime_at_df71(void) {
    runtime().routines().register_routine(0xDF71, "at_df71");
    runtime().routines().note_invocation(0xDF71);
    runtime().enemy_engine().at_df71();
}

void semcomp_runtime_at_ddd3(void) {
    runtime().routines().register_routine(0xDDD3, "at_ddd3");
    runtime().routines().note_invocation(0xDDD3);
    runtime().enemy_engine().at_ddd3();
}

void semcomp_runtime_chk_small_plat_loop(void) {
    runtime().routines().register_routine(0xDB8C, "ChkSmallPlatLoop");
    runtime().routines().note_invocation(0xDB8C);
    runtime().enemy_engine().chk_small_plat_loop();
}

void semcomp_runtime_at_e38b(void) {
    runtime().routines().register_routine(0xE38B, "at_e38b");
    runtime().routines().note_invocation(0xE38B);
    runtime().enemy_engine().at_e38b();
}

void semcomp_runtime_sde_c_loop(void) {
    runtime().routines().register_routine(0xE10A, "SdeCLoop");
    runtime().routines().note_invocation(0xE10A);
    runtime().enemy_engine().sde_c_loop();
}

void semcomp_runtime_at_e3b1(void) {
    runtime().routines().register_routine(0xE3B1, "at_e3b1");
    runtime().routines().note_invocation(0xE3B1);
    runtime().enemy_engine().at_e3b1();
}

void semcomp_runtime_at_e3ba(void) {
    runtime().routines().register_routine(0xE3BA, "at_e3ba");
    runtime().routines().note_invocation(0xE3BA);
    runtime().enemy_engine().at_e3ba();
}

void semcomp_runtime_no_h_offscr(void) {
    runtime().routines().register_routine(0xE540, "NoHOffscr");
    runtime().routines().note_invocation(0xE540);
    runtime().enemy_engine().no_h_offscr();
}

void semcomp_runtime_at_e53b(void) {
    runtime().routines().register_routine(0xE53B, "at_e53b");
    runtime().routines().note_invocation(0xE53B);
    runtime().enemy_engine().at_e53b();
}

void semcomp_runtime_chk_f_top(void) {
    runtime().routines().register_routine(0xE492, "ChkFTop");
    runtime().routines().note_invocation(0xE492);
    runtime().enemy_engine().chk_f_top();
}

void semcomp_runtime_at_dec9(void) {
    runtime().routines().register_routine(0xDEC9, "at_dec9");
    runtime().routines().note_invocation(0xDEC9);
    runtime().enemy_engine().at_dec9();
}

void semcomp_runtime_at_de8a(void) {
    runtime().routines().register_routine(0xDE8A, "at_de8a");
    runtime().routines().note_invocation(0xDE8A);
    runtime().enemy_engine().at_de8a();
}

void semcomp_runtime_at_debf(void) {
    runtime().routines().register_routine(0xDEBF, "at_debf");
    runtime().routines().note_invocation(0xDEBF);
    runtime().enemy_engine().at_debf();
}

void semcomp_runtime_at_e629(void) {
    runtime().routines().register_routine(0xE629, "at_e629");
    runtime().routines().note_invocation(0xE629);
    runtime().enemy_engine().at_e629();
}

void semcomp_runtime_at_e6f5(void) {
    runtime().routines().register_routine(0xE6F5, "at_e6f5");
    runtime().routines().note_invocation(0xE6F5);
    runtime().enemy_engine().at_e6f5();
}

void semcomp_runtime_at_e4bd(void) {
    runtime().routines().register_routine(0xE4BD, "at_e4bd");
    runtime().routines().note_invocation(0xE4BD);
    runtime().enemy_engine().at_e4bd();
}

void semcomp_runtime_at_e179(void) {
    runtime().routines().register_routine(0xE179, "at_e179");
    runtime().routines().note_invocation(0xE179);
    runtime().enemy_engine().at_e179();
}

void semcomp_runtime_at_e49d(void) {
    runtime().routines().register_routine(0xE49D, "at_e49d");
    runtime().routines().note_invocation(0xE49D);
    runtime().enemy_engine().at_e49d();
}

void semcomp_runtime_at_e710(void) {
    runtime().routines().register_routine(0xE710, "at_e710");
    runtime().routines().note_invocation(0xE710);
    runtime().enemy_engine().at_e710();
}

void semcomp_runtime_set_fall_s(void) {
    runtime().routines().register_routine(0xDC82, "SetFallS");
    runtime().routines().note_invocation(0xDC82);
    runtime().enemy_engine().set_fall_s();
}

void semcomp_runtime_at_e385(void) {
    runtime().routines().register_routine(0xE385, "at_e385");
    runtime().routines().note_invocation(0xE385);
    runtime().enemy_engine().at_e385();
}

void semcomp_runtime_at_dc23(void) {
    runtime().routines().register_routine(0xDC23, "at_dc23");
    runtime().routines().note_invocation(0xDC23);
    runtime().enemy_engine().at_dc23();
}

void semcomp_runtime_at_e600(void) {
    runtime().routines().register_routine(0xE600, "at_e600");
    runtime().routines().note_invocation(0xE600);
    runtime().enemy_engine().at_e600();
}

void semcomp_runtime_at_ddbd(void) {
    runtime().routines().register_routine(0xDDBD, "at_ddbd");
    runtime().routines().note_invocation(0xDDBD);
    runtime().enemy_engine().at_ddbd();
}

void semcomp_runtime_at_e38d(void) {
    runtime().routines().register_routine(0xE38D, "at_e38d");
    runtime().routines().note_invocation(0xE38D);
    runtime().enemy_engine().at_e38d();
}

void semcomp_runtime_at_e28d(void) {
    runtime().routines().register_routine(0xE28D, "at_e28d");
    runtime().routines().note_invocation(0xE28D);
    runtime().enemy_engine().at_e28d();
}

void semcomp_runtime_at_e7b9(void) {
    runtime().routines().register_routine(0xE7B9, "at_e7b9");
    runtime().routines().note_invocation(0xE7B9);
    runtime().enemy_engine().at_e7b9();
}

void semcomp_runtime_at_db93(void) {
    runtime().routines().register_routine(0xDB93, "at_db93");
    runtime().routines().note_invocation(0xDB93);
    runtime().enemy_engine().at_db93();
}

void semcomp_runtime_at_dcb9(void) {
    runtime().routines().register_routine(0xDCB9, "at_dcb9");
    runtime().routines().note_invocation(0xDCB9);
    runtime().enemy_engine().at_dcb9();
}

void semcomp_runtime_at_dd90(void) {
    runtime().routines().register_routine(0xDD90, "at_dd90");
    runtime().routines().note_invocation(0xDD90);
    runtime().enemy_engine().at_dd90();
}

void semcomp_runtime_at_e7b1(void) {
    runtime().routines().register_routine(0xE7B1, "at_e7b1");
    runtime().routines().note_invocation(0xE7B1);
    runtime().enemy_engine().at_e7b1();
}

void semcomp_runtime_at_dfd0(void) {
    runtime().routines().register_routine(0xDFD0, "at_dfd0");
    runtime().routines().note_invocation(0xDFD0);
    runtime().enemy_engine().at_dfd0();
}

void semcomp_runtime_at_e59a(void) {
    runtime().routines().register_routine(0xE59A, "at_e59a");
    runtime().routines().note_invocation(0xE59A);
    runtime().enemy_engine().at_e59a();
}

void semcomp_runtime_at_e61b(void) {
    runtime().routines().register_routine(0xE61B, "at_e61b");
    runtime().routines().note_invocation(0xE61B);
    runtime().enemy_engine().at_e61b();
}

void semcomp_runtime_at_e0b9(void) {
    runtime().routines().register_routine(0xE0B9, "at_e0b9");
    runtime().routines().note_invocation(0xE0B9);
    runtime().enemy_engine().at_e0b9();
}

void semcomp_runtime_at_e4b9(void) {
    runtime().routines().register_routine(0xE4B9, "at_e4b9");
    runtime().routines().note_invocation(0xE4B9);
    runtime().enemy_engine().at_e4b9();
}

void semcomp_runtime_at_e7a5(void) {
    runtime().routines().register_routine(0xE7A5, "at_e7a5");
    runtime().routines().note_invocation(0xE7A5);
    runtime().enemy_engine().at_e7a5();
}

void semcomp_runtime_at_dd76(void) {
    runtime().routines().register_routine(0xDD76, "at_dd76");
    runtime().routines().note_invocation(0xDD76);
    runtime().enemy_engine().at_dd76();
}

void semcomp_runtime_at_db04(void) {
    runtime().routines().register_routine(0xDB04, "at_db04");
    runtime().routines().note_invocation(0xDB04);
    runtime().enemy_engine().at_db04();
}

void semcomp_runtime_at_dd3d(void) {
    runtime().routines().register_routine(0xDD3D, "at_dd3d");
    runtime().routines().note_invocation(0xDD3D);
    runtime().enemy_engine().at_dd3d();
}

void semcomp_runtime_at_db5c(void) {
    runtime().routines().register_routine(0xDB5C, "at_db5c");
    runtime().routines().note_invocation(0xDB5C);
    runtime().enemy_engine().at_db5c();
}

void semcomp_runtime_at_db0c(void) {
    runtime().routines().register_routine(0xDB0C, "at_db0c");
    runtime().routines().note_invocation(0xDB0C);
    runtime().enemy_engine().at_db0c();
}

void semcomp_runtime_at_de82(void) {
    runtime().routines().register_routine(0xDE82, "at_de82");
    runtime().routines().note_invocation(0xDE82);
    runtime().enemy_engine().at_de82();
}

void semcomp_runtime_check_left_screen_b_box(void) {
    runtime().routines().register_routine(0xE30C, "CheckLeftScreenBBox");
    runtime().routines().note_invocation(0xE30C);
    runtime().enemy_engine().check_left_screen_b_box();
}

void semcomp_runtime_at_e286(void) {
    runtime().routines().register_routine(0xE286, "at_e286");
    runtime().routines().note_invocation(0xE286);
    runtime().enemy_engine().at_e286();
}

void semcomp_runtime_at_e528(void) {
    runtime().routines().register_routine(0xE528, "at_e528");
    runtime().routines().note_invocation(0xE528);
    runtime().enemy_engine().at_e528();
}

void semcomp_runtime_at_db3b(void) {
    runtime().routines().register_routine(0xDB3B, "at_db3b");
    runtime().routines().note_invocation(0xDB3B);
    runtime().enemy_engine().at_db3b();
}

void semcomp_runtime_ex_hc(void) {
    runtime().routines().register_routine(0xDE38, "ExHC");
    runtime().routines().note_invocation(0xDE38);
    runtime().enemy_engine().ex_hc();
}

void semcomp_runtime_at_dece(void) {
    runtime().routines().register_routine(0xDECE, "at_dece");
    runtime().routines().note_invocation(0xDECE);
    runtime().enemy_engine().at_dece();
}

void semcomp_runtime_at_dba7(void) {
    runtime().routines().register_routine(0xDBA7, "at_dba7");
    runtime().routines().note_invocation(0xDBA7);
    runtime().enemy_engine().at_dba7();
}

void semcomp_runtime_at_e730(void) {
    runtime().routines().register_routine(0xE730, "at_e730");
    runtime().routines().note_invocation(0xE730);
    runtime().enemy_engine().at_e730();
}

void semcomp_runtime_at_e347(void) {
    runtime().routines().register_routine(0xE347, "at_e347");
    runtime().routines().note_invocation(0xE347);
    runtime().enemy_engine().at_e347();
}

void semcomp_runtime_at_db47(void) {
    runtime().routines().register_routine(0xDB47, "at_db47");
    runtime().routines().note_invocation(0xDB47);
    runtime().enemy_engine().at_db47();
}

void semcomp_runtime_at_e406(void) {
    runtime().routines().register_routine(0xE406, "at_e406");
    runtime().routines().note_invocation(0xE406);
    runtime().enemy_engine().at_e406();
}

void semcomp_runtime_at_e001(void) {
    runtime().routines().register_routine(0xE001, "at_e001");
    runtime().routines().note_invocation(0xE001);
    runtime().enemy_engine().at_e001();
}

void semcomp_runtime_at_e431(void) {
    runtime().routines().register_routine(0xE431, "at_e431");
    runtime().routines().note_invocation(0xE431);
    runtime().enemy_engine().at_e431();
}

void semcomp_runtime_ex_csm(void) {
    runtime().routines().register_routine(0xDE02, "ExCSM");
    runtime().routines().note_invocation(0xDE02);
    runtime().enemy_engine().ex_csm();
}

void semcomp_runtime_at_e408(void) {
    runtime().routines().register_routine(0xE408, "at_e408");
    runtime().routines().note_invocation(0xE408);
    runtime().enemy_engine().at_e408();
}

void semcomp_runtime_at_e70a(void) {
    runtime().routines().register_routine(0xE70A, "at_e70a");
    runtime().routines().note_invocation(0xE70A);
    runtime().enemy_engine().at_e70a();
}

void semcomp_runtime_at_dd06(void) {
    runtime().routines().register_routine(0xDD06, "at_dd06");
    runtime().routines().note_invocation(0xDD06);
    runtime().enemy_engine().at_dd06();
}

void semcomp_runtime_at_de4b(void) {
    runtime().routines().register_routine(0xDE4B, "at_de4b");
    runtime().routines().note_invocation(0xDE4B);
    runtime().enemy_engine().at_de4b();
}

void semcomp_runtime_at_dd0a(void) {
    runtime().routines().register_routine(0xDD0A, "at_dd0a");
    runtime().routines().note_invocation(0xDD0A);
    runtime().enemy_engine().at_dd0a();
}

void semcomp_runtime_at_e112(void) {
    runtime().routines().register_routine(0xE112, "at_e112");
    runtime().routines().note_invocation(0xE112);
    runtime().enemy_engine().at_e112();
}

void semcomp_runtime_at_df11(void) {
    runtime().routines().register_routine(0xDF11, "at_df11");
    runtime().routines().note_invocation(0xDF11);
    runtime().enemy_engine().at_df11();
}

void semcomp_runtime_at_e139(void) {
    runtime().routines().register_routine(0xE139, "at_e139");
    runtime().routines().note_invocation(0xE139);
    runtime().enemy_engine().at_e139();
}

void semcomp_runtime_at_e278(void) {
    runtime().routines().register_routine(0xE278, "at_e278");
    runtime().routines().note_invocation(0xE278);
    runtime().enemy_engine().at_e278();
}

void semcomp_runtime_at_dc27(void) {
    runtime().routines().register_routine(0xDC27, "at_dc27");
    runtime().routines().note_invocation(0xDC27);
    runtime().enemy_engine().at_dc27();
}

void semcomp_runtime_at_e722(void) {
    runtime().routines().register_routine(0xE722, "at_e722");
    runtime().routines().note_invocation(0xE722);
    runtime().enemy_engine().at_e722();
}

void semcomp_runtime_no_ofs2(void) {
    runtime().routines().register_routine(0xE322, "NoOfs2");
    runtime().routines().note_invocation(0xE322);
    runtime().enemy_engine().no_ofs2();
}

void semcomp_runtime_at_e372(void) {
    runtime().routines().register_routine(0xE372, "at_e372");
    runtime().routines().note_invocation(0xE372);
    runtime().enemy_engine().at_e372();
}

void semcomp_runtime_at_e781(void) {
    runtime().routines().register_routine(0xE781, "at_e781");
    runtime().routines().note_invocation(0xE781);
    runtime().enemy_engine().at_e781();
}

void semcomp_runtime_check_for_p_up_collision(void) {
    runtime().routines().register_routine(0xD881, "CheckForPUpCollision");
    runtime().routines().note_invocation(0xD881);
    runtime().enemy_engine().check_for_p_up_collision();
}

void semcomp_runtime_at_e8e3(void) {
    runtime().routines().register_routine(0xE8E3, "at_e8e3");
    runtime().routines().note_invocation(0xE8E3);
    runtime().enemy_engine().at_e8e3();
}

void semcomp_runtime_at_e8e5(void) {
    runtime().routines().register_routine(0xE8E5, "at_e8e5");
    runtime().routines().note_invocation(0xE8E5);
    runtime().enemy_engine().at_e8e5();
}

void semcomp_runtime_at_e8fd(void) {
    runtime().routines().register_routine(0xE8FD, "at_e8fd");
    runtime().routines().note_invocation(0xE8FD);
    runtime().enemy_engine().at_e8fd();
}

void semcomp_runtime_check_bowser_gfx_flag(void) {
    runtime().routines().register_routine(0xE8F2, "CheckBowserGfxFlag");
    runtime().routines().note_invocation(0xE8F2);
    runtime().enemy_engine().check_bowser_gfx_flag();
}

void semcomp_runtime_at_e8e9(void) {
    runtime().routines().register_routine(0xE8E9, "at_e8e9");
    runtime().routines().note_invocation(0xE8E9);
    runtime().enemy_engine().at_e8e9();
}

void semcomp_runtime_at_e8fb(void) {
    runtime().routines().register_routine(0xE8FB, "at_e8fb");
    runtime().routines().note_invocation(0xE8FB);
    runtime().enemy_engine().at_e8fb();
}

void semcomp_runtime_at_e8d9(void) {
    runtime().routines().register_routine(0xE8D9, "at_e8d9");
    runtime().routines().note_invocation(0xE8D9);
    runtime().enemy_engine().at_e8d9();
}

void semcomp_runtime_enemy_to_bg_collision_det(void) {
    runtime().routines().register_routine(0xDFC1, "EnemyToBGCollisionDet");
    runtime().routines().note_invocation(0xDFC1);
    runtime().enemy_engine().enemy_to_bg_collision_det();
}

void semcomp_runtime_at_dfc3(void) {
    runtime().routines().register_routine(0xDFC3, "at_dfc3");
    runtime().routines().note_invocation(0xDFC3);
    runtime().enemy_engine().at_dfc3();
}

// Phase 34 - LevelEngine bulk-port (10 multi-entry bodies, 25 entries)
void semcomp_runtime_get_background_color(void) {
    runtime().routines().register_routine(0x85E3, "GetBackgroundColor");
    runtime().routines().note_invocation(0x85E3);
    runtime().level_engine().get_background_color();
}

void semcomp_runtime_at_862e(void) {
    runtime().routines().register_routine(0x862E, "at_862e");
    runtime().routines().note_invocation(0x862E);
    runtime().level_engine().at_862e();
}

void semcomp_runtime_write_game_text(void) {
    runtime().routines().register_routine(0x8808, "WriteGameText");
    runtime().routines().note_invocation(0x8808);
    runtime().level_engine().write_game_text();
}

void semcomp_runtime_at_8887(void) {
    runtime().routines().register_routine(0x8887, "at_8887");
    runtime().routines().note_invocation(0x8887);
    runtime().level_engine().at_8887();
}

void semcomp_runtime_at_8846(void) {
    runtime().routines().register_routine(0x8846, "at_8846");
    runtime().routines().note_invocation(0x8846);
    runtime().level_engine().at_8846();
}

void semcomp_runtime_write_block_metatile(void) {
    runtime().routines().register_routine(0x8A6D, "WriteBlockMetatile");
    runtime().routines().note_invocation(0x8A6D);
    runtime().level_engine().write_block_metatile();
}

void semcomp_runtime_move_v_offset(void) {
    runtime().routines().register_routine(0x8A8F, "MoveVOffset");
    runtime().routines().note_invocation(0x8A8F);
    runtime().level_engine().move_v_offset();
}

void semcomp_runtime_put_block_metatile(void) {
    runtime().routines().register_routine(0x8A97, "PutBlockMetatile");
    runtime().routines().note_invocation(0x8A97);
    runtime().level_engine().put_block_metatile();
}

void semcomp_runtime_rem_bridge(void) {
    runtime().routines().register_routine(0x8ACD, "RemBridge");
    runtime().routines().note_invocation(0x8ACD);
    runtime().level_engine().rem_bridge();
}

void semcomp_runtime_at_8a9d(void) {
    runtime().routines().register_routine(0x8A9D, "at_8a9d");
    runtime().routines().note_invocation(0x8A9D);
    runtime().level_engine().at_8a9d();
}

void semcomp_runtime_get_area_music(void) {
    runtime().routines().register_routine(0x90ED, "GetAreaMusic");
    runtime().routines().note_invocation(0x90ED);
    runtime().level_engine().get_area_music();
}

void semcomp_runtime_at_9100(void) {
    runtime().routines().register_routine(0x9100, "at_9100");
    runtime().routines().note_invocation(0x9100);
    runtime().level_engine().at_9100();
}

void semcomp_runtime_area_parser_core(void) {
    runtime().routines().register_routine(0x93FC, "AreaParserCore");
    runtime().routines().note_invocation(0x93FC);
    runtime().level_engine().area_parser_core();
}

void semcomp_runtime_at_9494(void) {
    runtime().routines().register_routine(0x9494, "at_9494");
    runtime().routines().note_invocation(0x9494);
    runtime().level_engine().at_9494();
}

void semcomp_runtime_terr_loop(void) {
    runtime().routines().register_routine(0x9491, "TerrLoop");
    runtime().routines().note_invocation(0x9491);
    runtime().level_engine().terr_loop();
}

void semcomp_runtime_process_area_data(void) {
    runtime().routines().register_routine(0x9508, "ProcessAreaData");
    runtime().routines().note_invocation(0x9508);
    runtime().level_engine().process_area_data();
}

void semcomp_runtime_end_a_parse(void) {
    runtime().routines().register_routine(0x9588, "EndAParse");
    runtime().routines().note_invocation(0x9588);
    runtime().level_engine().end_a_parse();
}

void semcomp_runtime_decode_area_data(void) {
    runtime().routines().register_routine(0x9595, "DecodeAreaData");
    runtime().routines().note_invocation(0x9595);
    runtime().level_engine().decode_area_data();
}

void semcomp_runtime_loop_cmd_e(void) {
    runtime().routines().register_routine(0x9645, "LoopCmdE");
    runtime().routines().note_invocation(0x9645);
    runtime().level_engine().loop_cmd_e();
}

void semcomp_runtime_at_95df(void) {
    runtime().routines().register_routine(0x95DF, "at_95df");
    runtime().routines().note_invocation(0x95DF);
    runtime().level_engine().at_95df();
}

void semcomp_runtime_area_style_object(void) {
    runtime().routines().register_routine(0x9740, "AreaStyleObject");
    runtime().routines().note_invocation(0x9740);
    runtime().level_engine().area_style_object();
}

void semcomp_runtime_at_9792(void) {
    runtime().routines().register_routine(0x9792, "at_9792");
    runtime().routines().note_invocation(0x9792);
    runtime().level_engine().at_9792();
}

void semcomp_runtime_at_9989(void) {
    runtime().routines().register_routine(0x9989, "at_9989");
    runtime().routines().note_invocation(0x9989);
    runtime().level_engine().at_9989();
}

void semcomp_runtime_set_hi_max(void) {
    runtime().routines().register_routine(0xBF94, "SetHiMax");
    runtime().routines().note_invocation(0xBF94);
    runtime().level_engine().set_hi_max();
}

void semcomp_runtime_set_x_move_amt(void) {
    runtime().routines().register_routine(0xBF96, "SetXMoveAmt");
    runtime().routines().note_invocation(0xBF96);
    runtime().level_engine().set_x_move_amt();
}

}  // extern "C"
