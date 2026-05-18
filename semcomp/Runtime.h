// semcomp/Runtime.h — C-compatible bridge so extras.c can drive semcomp.
//
// Phase 2: extras.c is C; semcomp/ is C++. The runtime singleton lives
// in Runtime.cpp and exposes a flat C ABI for the runner to call. All
// functions are no-ops / return zero when compiled with
// ENABLE_SEMCOMP=OFF (a separate Runtime_stub.c provides those).
#pragma once

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// One-time init. Idempotent.
void semcomp_runtime_init(void);

// ---- Trainer control ------------------------------------------------------
// Enabled state controls whether semcomp_runtime_apply_trainer() does work
// each frame. Set by extras.c when --trainer is passed at the CLI.
void semcomp_runtime_set_trainer_enabled(int enabled);
int  semcomp_runtime_trainer_enabled(void);

// Per-frame hook: runs all frozen writes if enabled. Called from
// game_post_nmi() in extras.c so the freeze happens AFTER the game's
// frame update, not before.
void semcomp_runtime_apply_trainer(void);

// Trainer table ops (raw addresses). Return 1 on success, 0 on failure
// (e.g., table full). Addresses outside the work-RAM window are masked
// to it by the underlying write8.
int semcomp_runtime_trainer_set(uint16_t addr, uint8_t val);
int semcomp_runtime_trainer_freeze(uint16_t addr, uint8_t val);
int semcomp_runtime_trainer_thaw(uint16_t addr);

// Enumeration for trainer_list TCP command.
size_t   semcomp_runtime_trainer_count(void);
uint16_t semcomp_runtime_trainer_entry_addr(size_t i);
uint8_t  semcomp_runtime_trainer_entry_value(size_t i);

// ---- Trainer UI overlay (in-game) -----------------------------------------
// Called every frame from extras.c::game_on_frame. Polls keyboard and
// updates overlay state (toggle on F8, navigate, freeze/thaw). No-op
// when --trainer is disabled.
void semcomp_runtime_trainer_ui_tick(void);

// Called from extras.c::game_post_render, after the game's frame has
// been rendered but before present. Blits the overlay onto the
// framebuffer if visible. width/height are the framebuffer dimensions
// (always 256/240 for stock SMB).
void semcomp_runtime_trainer_ui_render(uint32_t* fb, int width, int height);

// True while the overlay is visible and consuming keyboard input.
// extras.c suppresses g_controller1_buttons while this returns nonzero
// so arrow keys don't bleed into the game's controller.
int  semcomp_runtime_trainer_ui_grabbing_input(void);

// ---- Mario read accessors (for the semcomp_mario TCP command) -------------
// All return the same value Mario::*() would. This is the
// "read via semcomp facade" path used for verification.
uint8_t  semcomp_runtime_mario_x(void);
uint8_t  semcomp_runtime_mario_y(void);
uint8_t  semcomp_runtime_mario_page(void);
uint16_t semcomp_runtime_mario_world_x(void);
int8_t   semcomp_runtime_mario_x_velocity(void);
int8_t   semcomp_runtime_mario_y_velocity(void);
uint8_t  semcomp_runtime_mario_x_speed_absolute(void);
uint8_t  semcomp_runtime_mario_power(void);
uint8_t  semcomp_runtime_mario_physics_state(void);
int      semcomp_runtime_mario_on_ground(void);
uint8_t  semcomp_runtime_mario_facing(void);

// ---- Level / PlayerSession reads (for semcomp_level / semcomp_session) ---
// Same pattern as the Mario readers above; let the GUI/REPL validate
// the facade by comparing these against read_ram of the same addresses.
uint8_t  semcomp_runtime_level_world(void);
uint8_t  semcomp_runtime_level_level(void);
uint16_t semcomp_runtime_level_world_level_packed(void);
uint8_t  semcomp_runtime_session_lives(void);
uint8_t  semcomp_runtime_session_coins(void);

// ---- Semantic setters (Phase 2) ------------------------------------------
// Route through the C++ facade setters so coupled-byte and clamping
// logic actually fires. The Trainer's trainer_set/freeze write the
// raw byte and bypass these. The GUI defaults to semantic for fields
// where it matters (Power: couples Status+Size; Lives/Coins: clamps
// 0-99); each row has a "Raw bypass" checkbox to opt out for
// verification work.
void semcomp_runtime_set_mario_x(uint8_t v);
void semcomp_runtime_set_mario_y(uint8_t v);
void semcomp_runtime_set_mario_page(uint8_t v);
void semcomp_runtime_set_mario_power(uint8_t v);
void semcomp_runtime_set_mario_physics_state(uint8_t v);
void semcomp_runtime_set_mario_facing(uint8_t v);
void semcomp_runtime_set_session_lives(uint8_t v);
void semcomp_runtime_set_session_coins(uint8_t v);

// ---- Semantic freezes (Phase 2.5) ----------------------------------------
// Route a freeze request through the C++ semcomp class so coupling
// logic re-runs every frame.  freeze_* records the value AND asserts
// it immediately; thaw_* clears the freeze record (the Trainer's
// per-frame apply will stop re-writing the bytes).  Listings are
// returned by trainer_list via its "semantic" array.
void semcomp_runtime_freeze_mario_power(uint8_t v);
void semcomp_runtime_thaw_mario_power(void);
int  semcomp_runtime_is_mario_power_frozen(void);
uint8_t semcomp_runtime_frozen_mario_power_value(void);

void semcomp_runtime_freeze_session_lives(uint8_t v);
void semcomp_runtime_thaw_session_lives(void);
int  semcomp_runtime_is_session_lives_frozen(void);
uint8_t semcomp_runtime_frozen_session_lives_value(void);

void semcomp_runtime_freeze_session_coins(uint8_t v);
void semcomp_runtime_thaw_session_coins(void);
int  semcomp_runtime_is_session_coins_frozen(void);
uint8_t semcomp_runtime_frozen_session_coins_value(void);

// ---- Phase 3 routine replacement -----------------------------------------
// Each replaced 6502 routine has a semantic C++ implementation in
// semcomp/SmbRoutines.cpp; this bridge exposes invocation entry points
// that extras.c can stitch into the replace_func body it provides to
// the generated code (when game.toml's [[replace_func]] excludes the
// generated body).
//
// Calling these directly from non-replace_func code paths is also
// supported and useful — e.g. the Trainer's "Add coin" semantic setter
// invokes semcomp_runtime_give_coin() so the full HUD refresh + 1-Up
// side effects fire, rather than just incrementing $075E.
//
// Each call bumps the routine's invocation counter, queryable via
// semcomp_runtime_routine_count / _entry_*.
void semcomp_runtime_give_coin(void);

// Grant N coins in a row — equivalent to N natural pickups, full side
// effects (SFX, score, 1-Up at 100, HUD refresh). Bumps the GiveOneCoin
// invocation counter by N. Driven by the trainer's "Add Coins" action
// (positive N).
void semcomp_runtime_add_coins(uint8_t n);

// Subtract N from CoinTally (clamped at 0), refresh HUD. Driven by
// negative N in the trainer's "Add Coins" input — no real-game verb
// matches this; it's trainer-only.
void semcomp_runtime_remove_coins(uint8_t n);

// Coin grants pending in the per-frame ticker (see Runtime.cpp).
// semcomp_runtime_add_coins(N) returns immediately after enqueueing,
// and the grants drain one per frame from apply_post_nmi. Callers
// that want the live $075E should poll, not trust the immediate
// TCP-response echo.
uint32_t semcomp_runtime_pending_coin_grants(void);

// Same shape for lives. semcomp_runtime_add_lives bumps NumberofLives
// by N (clamped at 99) and plays the extra-life jingle.
// semcomp_runtime_remove_lives decrements (clamped at 0), silent.
void semcomp_runtime_add_lives(uint8_t n);
void semcomp_runtime_remove_lives(uint8_t n);

// Score (6 BCD digits, max 999999). add takes a SIGNED delta.
void     semcomp_runtime_set_score(uint32_t value);
void     semcomp_runtime_add_score(int32_t  delta);
uint32_t semcomp_runtime_get_score(void);

// Game timer (3 BCD digits, 0..999). add takes a SIGNED delta.
void     semcomp_runtime_set_timer(uint16_t seconds);
void     semcomp_runtime_add_timer(int16_t  delta);
uint16_t semcomp_runtime_get_timer(void);

// Mario power: Small / Big / Fire. give_power_up steps up one tier
// (capped at Fire); take_damage steps down one tier (stays at Small
// rather than auto-killing). Both go through Mario::set_power so the
// PlayerStatus / PlayerSize / PlayerChangeSizeFlag bytes stay coupled.
// Return 1 iff a tier transition actually happened, 0 if at the limit.
int semcomp_runtime_give_power_up(void);
int semcomp_runtime_take_damage(void);

// ---- Enemies (5-slot array facade) ---------------------------------------
// Read accessors target one slot at a time (0..4). The "active" check
// reads $000F+slot — every other accessor returns garbage for inactive
// slots, so callers should gate on it first.
int     semcomp_runtime_enemy_active(uint8_t slot);
uint8_t semcomp_runtime_enemy_id(uint8_t slot);
uint8_t semcomp_runtime_enemy_state(uint8_t slot);
uint16_t semcomp_runtime_enemy_world_x(uint8_t slot);
uint8_t semcomp_runtime_enemy_y(uint8_t slot);
int8_t  semcomp_runtime_enemy_x_velocity(uint8_t slot);
int8_t  semcomp_runtime_enemy_y_velocity(uint8_t slot);
int     semcomp_runtime_enemy_active_count(void);

// Bulk verbs (every active slot).
//   kill_all_enemies  — instant remove via $E18E. No score, no anim.
//   stomp_all_enemies — score grant + stomp anim via $D969 per slot.
//   freeze_enemies    — zero $0058 / $00B6 per slot (best effort;
//                       enemies that recompute velocity each frame
//                       will resist).
// Return the number of slots that were affected.
int semcomp_runtime_kill_all_enemies(void);
int semcomp_runtime_stomp_all_enemies(void);
int semcomp_runtime_freeze_enemies(void);

// Per-slot verbs.
int semcomp_runtime_kill_enemy(uint8_t slot);
int semcomp_runtime_stomp_enemy(uint8_t slot);

// ---- Camera (Phase 4) ----------------------------------------------------
uint16_t semcomp_runtime_camera_left_world_x(void);
uint16_t semcomp_runtime_camera_right_world_x(void);
int      semcomp_runtime_camera_is_locked(void);
void     semcomp_runtime_camera_set_world_x(uint16_t world_x);
void     semcomp_runtime_camera_lock(void);
void     semcomp_runtime_camera_unlock(void);

// ---- World verbs (Phase 4) -----------------------------------------------
// Bump a block at Mario's metatile column. Returns 1 (always — best
// effort; if BumpBlock didn't match it silently does nothing).
int semcomp_runtime_bump_block_under_mario(uint8_t block_code);

// Spawn a power-up entity in slot 5. type: 0=mushroom, 1=fire flower,
// 2=star, 3=1-up. Returns 1.
int semcomp_runtime_spawn_powerup(uint8_t type);

// Pop a floatey number above Mario. points_table_index: 0..9 mapping
// to {100, 200, 400, 500, 800, 1000, 2000, 4000, 5000, 8000}.
// Returns the clamped index used.
uint8_t semcomp_runtime_spawn_floatey(uint8_t points_table_index);

// ---- Replace_func bridges (called from extras.c shims) -------------------
// These are the entry points game.toml's [[replace_func]] suppresses
// the generated body of. extras.c provides the linker symbol
// func_XXXX_b0() and forwards into these. The C++ class methods own
// the routine semantics; the natural in-game caller continues to
// drive them.
void semcomp_runtime_bump_block_replacement(void);    // $BD9B BumpBlock
void semcomp_runtime_setup_powerup_replacement(void); // $BC49 SetupPowerUp
void semcomp_runtime_pause_tick(void);                // $8182 PauseRoutine
void semcomp_runtime_print_status_bar_numbers(void);  // $8F06
void semcomp_runtime_add_to_score(void);              // $BC27 AddToScore

// ---- GameMode reads + verbs (Phase 5) ------------------------------------
uint8_t semcomp_runtime_mode_oper_mode(void);
uint8_t semcomp_runtime_mode_oper_mode_task(void);
uint8_t semcomp_runtime_mode_player_ctrl_routine(void);
uint8_t semcomp_runtime_mode_pause_status(void);
uint8_t semcomp_runtime_mode_pause_timer(void);
int     semcomp_runtime_mode_is_paused(void);
void    semcomp_runtime_mode_set_paused(int paused);
void    semcomp_runtime_mode_end_level(void);
void    semcomp_runtime_mode_warp_to(uint8_t world, uint8_t level);

// Diagnostics: list of registered (replaced) routine PCs and their
// invocation counters. Populated lazily as semcomp_runtime_give_coin
// (and future replacements) get called.
size_t        semcomp_runtime_routine_count(void);
uint16_t      semcomp_runtime_routine_entry_pc(size_t i);
const char*   semcomp_runtime_routine_entry_name(size_t i);
uint64_t      semcomp_runtime_routine_entry_invocations(size_t i);

#ifdef __cplusplus
}
#endif
