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

#ifdef __cplusplus
}
#endif
