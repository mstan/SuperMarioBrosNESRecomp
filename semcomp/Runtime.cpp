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

}  // extern "C"
