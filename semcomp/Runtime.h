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
void semcomp_runtime_setup_floatey_number(void);      // $DA11 SetupFloateyNumber
void semcomp_runtime_init_normal_enemy(void);         // $C30E InitNormalEnemy
void semcomp_runtime_move_normal_enemy(void);         // $CA77 MoveNormalEnemy
void semcomp_runtime_auto_control_player(void);       // $B0E6 AutoControlPlayer
void semcomp_runtime_player_movement_subs(void);      // $B329 PlayerMovementSubs
void semcomp_runtime_player_change_size(void);        // $B233 PlayerChangeSize
void semcomp_runtime_player_injury_blink(void);       // $B245 PlayerInjuryBlink
void semcomp_runtime_player_death(void);              // $B269 PlayerDeath
void semcomp_runtime_player_fire_flower(void);        // $B27D PlayerFireFlower
void semcomp_runtime_on_ground_state_sub(void);       // $B35A OnGroundStateSub
void semcomp_runtime_falling_sub(void);               // $B36D FallingSub
void semcomp_runtime_jump_swim_sub(void);             // $B376 JumpSwimSub
void semcomp_runtime_climbing_sub(void);              // $B3CF ClimbingSub
void semcomp_runtime_physics_sub(void);               // $B450 PlayerPhysicsSub
void semcomp_runtime_move_player_y_axis(void);        // $B200 MovePlayerYAxis
void semcomp_runtime_move_player_horizontally(void);  // $BF09 MovePlayerHorizontally
void semcomp_runtime_ex_x_move(void);                 // $BF4C ExXMove
void semcomp_runtime_move_player_vertically(void);    // $BF4D MovePlayerVertically
void semcomp_runtime_player_bg_collision(void);       // $DC64 PlayerBGCollision

// Phase 17 — Player graphics.
void semcomp_runtime_get_player_colors(void);         // $85F1
void semcomp_runtime_draw_player_loop(void);          // $EFDC
void semcomp_runtime_relative_player_position(void);  // $F12A
void semcomp_runtime_relative_player_position_f12c(void); // $F12C
void semcomp_runtime_draw_player_intermediate(void);  // $EFA4
void semcomp_runtime_draw_player_intermediate_pintloop(void); // $EFA6
void semcomp_runtime_draw_player_intermediate_efac(void); // $EFAC
void semcomp_runtime_player_gfx_handler(void);        // $EEE9
void semcomp_runtime_player_gfx_handler_eef7(void);   // $EEF7
void semcomp_runtime_player_gfx_handler_ef85(void);   // $EF85
void semcomp_runtime_player_gfx_handler_eefc(void);   // $EEFC
void semcomp_runtime_player_gfx_handler_eefe(void);   // $EEFE
void semcomp_runtime_player_gfx_handler_eeee(void);   // $EEEE
void semcomp_runtime_player_gfx_handler_eef0(void);   // $EEF0
void semcomp_runtime_player_gfx_handler_eef1(void);   // $EEF1
void semcomp_runtime_player_gfx_handler_ef10(void);   // $EF10
void semcomp_runtime_player_gfx_handler_ef01(void);   // $EF01
void semcomp_runtime_player_gfx_handler_ef42(void);   // $EF42
void semcomp_runtime_player_gfx_handler_ef7a(void);   // $EF7A
void semcomp_runtime_player_gfx_handler_ef97(void);   // $EF97

// Phase 18 — Object handlers.
void semcomp_runtime_powerup_obj_handler(void);       // $BC85
void semcomp_runtime_fireball_obj_core(void);         // $B689
void semcomp_runtime_coin_block(void);                // $BB38

// Phase 19 — BumpBlock untangle.
void semcomp_runtime_bump_block(void);                // $BD9B
void semcomp_runtime_mush_flower_block(void);         // $BDD2
void semcomp_runtime_vine_block(void);                // $BDDF
void semcomp_runtime_star_block(void);                // $BDD5
void semcomp_runtime_extra_life_mush_block(void);     // $BDD8

// Phase 20 — HUD math untangle.
void semcomp_runtime_digits_math_routine(void);       // $8F5F
void semcomp_runtime_add_mod_loop(void);              // $8F68
void semcomp_runtime_store_new_d(void);               // $8F75
void semcomp_runtime_output_numbers(void);            // $8F11

// Phase 21 — Floatey per-frame untangle.
void semcomp_runtime_floatey_per_frame(void);         // $84C3
void semcomp_runtime_floatey_part_8534(void);         // $8534

// Phase 22 — Damage chain untangle.
void semcomp_runtime_injure_player(void);             // $D92C
void semcomp_runtime_force_injury(void);              // $D931
void semcomp_runtime_title_screen_mode(void);         // $8231 TitleScreenMode
void semcomp_runtime_game_mode_tick(void);            // $AEDC GameMode
void semcomp_runtime_game_over_mode(void);            // $9218 GameOverMode

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

// Phase 24 — Enemies mega (batch 1, bulk-ported).
void semcomp_runtime_init_goomba(void);  // $C2F1 InitGoomba
void semcomp_runtime_init_hammer_bro(void);  // $C328 InitHammerBro
void semcomp_runtime_init_bullet_bill(void);  // $C36B InitBulletBill
void semcomp_runtime_init_cheep_cheep(void);  // $C375 InitCheepCheep
void semcomp_runtime_init_lakitu(void);  // $C385 InitLakitu
void semcomp_runtime_setup_lakitu(void);  // $C38A SetupLakitu
void semcomp_runtime_init_short_firebar(void);  // $C45C InitShortFirebar
void semcomp_runtime_move_defeated_enemy(void);  // $CAE5 MoveDefeatedEnemy
void semcomp_runtime_move_jumping_enemy(void);  // $CAF9 MoveJumpingEnemy
void semcomp_runtime_move_bloober(void);  // $CB89 MoveBloober

void semcomp_runtime_bridge_collapse(void);  // $CFEC BridgeCollapse
void semcomp_runtime_kill_all_enemies_d071(void);  // $D071 KillAllEnemies
void semcomp_runtime_run_bowser(void);  // $D065 RunBowser
void semcomp_runtime_move_d_bowser(void);  // $D00F MoveD_Bowser
void semcomp_runtime_erase_enemy_object(void);  // $C998 EraseEnemyObject
void semcomp_runtime_init_vstf(void);  // $C363 InitVStf
void semcomp_runtime_init_enemy_object(void);  // $C226 InitEnemyObject
void semcomp_runtime_check_frenzy_buffer(void);  // $C216 CheckFrenzyBuffer
void semcomp_runtime_check_three_bytes(void);  // $C250 CheckThreeBytes
void semcomp_runtime_handle_group_enemies(void);  // $C71B HandleGroupEnemies
void semcomp_runtime_inc_3b(void);  // $C25B Inc3B
void semcomp_runtime_end_area_points(void);  // $D336 EndAreaPoints
void semcomp_runtime_award_game_timer_points(void);  // $D312 AwardGameTimerPoints


// Phase 25 — Level parser (batch 1)
void semcomp_runtime_get_area_palette(void);  // $85BF GetAreaPalette
void semcomp_runtime_area_parser_task_control(void);  // $86E6 AreaParserTaskControl
void semcomp_runtime_render_area_graphics(void);  // $88AE RenderAreaGraphics
void semcomp_runtime_initialize_area(void);  // $8FE4 InitializeArea
void semcomp_runtime_area_parser_task_handler(void);  // $92B0 AreaParserTaskHandler
void semcomp_runtime_area_parser_tasks(void);  // $92C8 AreaParserTasks
void semcomp_runtime_get_area_object_i_d(void);  // $9B36 GetAreaObjectID
void semcomp_runtime_get_area_obj_x_position(void);  // $9BCB GetAreaObjXPosition
void semcomp_runtime_get_area_obj_y_position(void);  // $9BD3 GetAreaObjYPosition
void semcomp_runtime_load_area_pointer(void);  // $9C03 LoadAreaPointer
void semcomp_runtime_get_area_type(void);  // $9C09 GetAreaType
void semcomp_runtime_get_area_data_addrs(void);  // $9C22 GetAreaDataAddrs

// Phase 25 — Level parser (batch 1)

// Phase 26 — BG renderer + VRAM
void semcomp_runtime_set_v_r_a_m_addr__a(void);  // $85C5 SetVRAMAddr_A
void semcomp_runtime_set_v_r_a_m_offset(void);  // $863F SetVRAMOffset
void semcomp_runtime_set_v_r_a_m_addr__b(void);  // $864C SetVRAMAddr_B
void semcomp_runtime_write_top_status_line(void);  // $8652 WriteTopStatusLine
void semcomp_runtime_write_bottom_status_line(void);  // $865A WriteBottomStatusLine
void semcomp_runtime_write_top_score(void);  // $8749 WriteTopScore
void semcomp_runtime_set_v_r_a_m_ctrl(void);  // $89BD SetVRAMCtrl
void semcomp_runtime_write_n_t_addr(void);  // $8E2D WriteNTAddr
void semcomp_runtime_write_buffer_to_screen(void);  // $8E92 WriteBufferToScreen
void semcomp_runtime_write_p_p_u_reg1(void);  // $8EED WritePPUReg1

// Phase 27-30 — Audio
void semcomp_runtime_run_offscr_bits_subs(void);  // $F1D7 RunOffscrBitsSubs
void semcomp_runtime_play_flagpole_slide(void);  // $F3BF PlayFlagpoleSlide
void semcomp_runtime_play_small_jump(void);  // $F3CD PlaySmallJump
void semcomp_runtime_play_big_jump(void);  // $F3D1 PlayBigJump
void semcomp_runtime_play_fireball_throw(void);  // $F3F9 PlayFireballThrow
void semcomp_runtime_play_bump(void);  // $F3FF PlayBump
void semcomp_runtime_play_timer_tick(void);  // $F51E PlayTimerTick
void semcomp_runtime_play_blast(void);  // $F53A PlayBlast
void semcomp_runtime_play_power_up_grab(void);  // $F552 PlayPowerUpGrab
void semcomp_runtime_play_noise_sfx(void);  // $F64D PlayNoiseSfx

// Phase 31 — Misc utilities
void semcomp_runtime_inc_subtask(void);  // $8745 IncSubtask
void semcomp_runtime_move_all_sprites_offscreen(void);  // $8220 MoveAllSpritesOffscreen
void semcomp_runtime_move_sprites_offscreen(void);  // $8223 MoveSpritesOffscreen
void semcomp_runtime_get_alternate_palette1(void);  // $8643 GetAlternatePalette1
void semcomp_runtime_get_m_tile_attrib(void);  // $DFB0 GetMTileAttrib
void semcomp_runtime_move_six_sprites_offscreen(void);  // $E5B3 MoveSixSpritesOffscreen
void semcomp_runtime_increment_column_pos(void);  // $92DB IncrementColumnPos
void semcomp_runtime_inc_area_obj_offset(void);  // $9589 IncAreaObjOffset
void semcomp_runtime_inc_mode_task__b(void);  // $874E IncModeTask_B

// Phase 32 - AudioEngine bulk-port (116 entries across 12 multi-entry bodies + 2 single-entry)
void semcomp_runtime_square1_sfx_handler(void);  // $F41B Square1SfxHandler
void semcomp_runtime_square2_sfx_handler(void);  // $F57C Square2SfxHandler
void semcomp_runtime_sound_engine(void);  // $F2D0 SoundEngine
void semcomp_runtime_at_f2d3(void);  // $F2D3 at_f2d3
void semcomp_runtime_at_f2ea(void);  // $F2EA at_f2ea
void semcomp_runtime_at_f2f3(void);  // $F2F3 at_f2f3
void semcomp_runtime_at_f329(void);  // $F329 at_f329
void semcomp_runtime_at_f380(void);  // $F380 at_f380
void semcomp_runtime_at_f367(void);  // $F367 at_f367
void semcomp_runtime_no_inc_dac(void);  // $F377 NoIncDAC
void semcomp_runtime_dump_squ1_regs(void);  // $F381 Dump_Squ1_Regs
void semcomp_runtime_at_f384(void);  // $F384 at_f384
void semcomp_runtime_play_squ1_sfx(void);  // $F388 PlaySqu1Sfx
void semcomp_runtime_at_f38e(void);  // $F38E at_f38e
void semcomp_runtime_dump_sq2_regs(void);  // $F39F Dump_Sq2_Regs
void semcomp_runtime_at_f3a5(void);  // $F3A5 at_f3a5
void semcomp_runtime_play_squ2_sfx(void);  // $F3A6 PlaySqu2Sfx
void semcomp_runtime_no_p_dwn_l(void);  // $F4D1 NoPDwnL
void semcomp_runtime_at_f410(void);  // $F410 at_f410
void semcomp_runtime_at_f4b0(void);  // $F4B0 at_f4b0
void semcomp_runtime_fps2nd(void);  // $F3F2 FPS2nd
void semcomp_runtime_dmp_jp_fps(void);  // $F3F4 DmpJpFPS
void semcomp_runtime_at_f4be(void);  // $F4BE at_f4be
void semcomp_runtime_at_f4bf(void);  // $F4BF at_f4bf
void semcomp_runtime_at_f4a5(void);  // $F4A5 at_f4a5
void semcomp_runtime_at_f405(void);  // $F405 at_f405
void semcomp_runtime_at_f486(void);  // $F486 at_f486
void semcomp_runtime_at_f421(void);  // $F421 at_f421
void semcomp_runtime_at_f3ee(void);  // $F3EE at_f3ee
void semcomp_runtime_at_f490(void);  // $F490 at_f490
void semcomp_runtime_at_f462(void);  // $F462 at_f462
void semcomp_runtime_at_f4a9(void);  // $F4A9 at_f4a9
void semcomp_runtime_at_f44c(void);  // $F44C at_f44c
void semcomp_runtime_play_coin_grab(void);  // $F518 PlayCoinGrab
void semcomp_runtime_blst_s_jp(void);  // $F5D1 BlstSJp
void semcomp_runtime_grow_item_regs(void);  // $F602 GrowItemRegs
void semcomp_runtime_n2_tone(void);  // $F538 N2Tone
void semcomp_runtime_at_f607(void);  // $F607 at_f607
void semcomp_runtime_at_f621(void);  // $F621 at_f621
void semcomp_runtime_at_f5f6(void);  // $F5F6 at_f5f6
void semcomp_runtime_play_grow_power_up(void);  // $F5FC PlayGrowPowerUp
void semcomp_runtime_at_f624(void);  // $F624 at_f624
void semcomp_runtime_at_f586(void);  // $F586 at_f586
void semcomp_runtime_at_f5b2(void);  // $F5B2 at_f5b2
void semcomp_runtime_at_f5f8(void);  // $F5F8 at_f5f8
void semcomp_runtime_at_f5ed(void);  // $F5ED at_f5ed
void semcomp_runtime_jump_to_dec_length2(void);  // $F5C5 JumpToDecLength2
void semcomp_runtime_el_l_regs(void);  // $F5E0 EL_LRegs
void semcomp_runtime_at_f5cf(void);  // $F5CF at_f5cf
void semcomp_runtime_div_l_loop(void);  // $F5EC DivLLoop
void semcomp_runtime_at_f5b9(void);  // $F5B9 at_f5b9
void semcomp_runtime_at_f605(void);  // $F605 at_f605
void semcomp_runtime_c_grab_t_tick_reg_l(void);  // $F522 CGrab_TTickRegL
void semcomp_runtime_at_f617(void);  // $F617 at_f617
void semcomp_runtime_play_brick_shatter(void);  // $F63B PlayBrickShatter
void semcomp_runtime_decrement_sfx3_length(void);  // $F658 DecrementSfx3Length
void semcomp_runtime_at_f644(void);  // $F644 at_f644
void semcomp_runtime_noise_sfx_handler(void);  // $F667 NoiseSfxHandler
void semcomp_runtime_continue_bowser_flame(void);  // $F685 ContinueBowserFlame
void semcomp_runtime_at_f679(void);  // $F679 at_f679
void semcomp_runtime_at_f68f(void);  // $F68F at_f68f
void semcomp_runtime_music_handler(void);  // $F694 MusicHandler
void semcomp_runtime_silent_beat(void);  // $F8B9 SilentBeat
void semcomp_runtime_at_f7c3(void);  // $F7C3 at_f7c3
void semcomp_runtime_at_f860(void);  // $F860 at_f860
void semcomp_runtime_strong_beat(void);  // $F8A9 StrongBeat
void semcomp_runtime_find_event_music_header(void);  // $F6F1 FindEventMusicHeader
void semcomp_runtime_at_f80d(void);  // $F80D at_f80d
void semcomp_runtime_at_f720(void);  // $F720 at_f720
void semcomp_runtime_at_f710(void);  // $F710 at_f710
void semcomp_runtime_at_f6a1(void);  // $F6A1 at_f6a1
void semcomp_runtime_at_f8ad(void);  // $F8AD at_f8ad
void semcomp_runtime_at_f829(void);  // $F829 at_f829
void semcomp_runtime_at_f750(void);  // $F750 at_f750
void semcomp_runtime_at_f6fc(void);  // $F6FC at_f6fc
void semcomp_runtime_at_f7a9(void);  // $F7A9 at_f7a9
void semcomp_runtime_death_m_alt_reg(void);  // $F810 DeathMAltReg
void semcomp_runtime_at_f784(void);  // $F784 at_f784
void semcomp_runtime_at_f885(void);  // $F885 at_f885
void semcomp_runtime_squ2_note_handler(void);  // $F786 Squ2NoteHandler
void semcomp_runtime_at_f7a5(void);  // $F7A5 at_f7a5
void semcomp_runtime_at_f7e6(void);  // $F7E6 at_f7e6
void semcomp_runtime_at_f7e7(void);  // $F7E7 at_f7e7
void semcomp_runtime_at_f8a5(void);  // $F8A5 at_f8a5
void semcomp_runtime_at_f7e4(void);  // $F7E4 at_f7e4
void semcomp_runtime_misc_squ1_music_tasks(void);  // $F7F7 MiscSqu1MusicTasks
void semcomp_runtime_skip_ctrl_l(void);  // $F7F1 SkipCtrlL
void semcomp_runtime_load_header(void);  // $F6F5 LoadHeader
void semcomp_runtime_fetch_noise_beat_data(void);  // $F878 FetchNoiseBeatData
void semcomp_runtime_at_f6b8(void);  // $F6B8 at_f6b8
void semcomp_runtime_at_f7fb(void);  // $F7FB at_f7fb
void semcomp_runtime_at_f850(void);  // $F850 at_f850
void semcomp_runtime_at_f88d(void);  // $F88D at_f88d
void semcomp_runtime_at_f6b6(void);  // $F6B6 at_f6b6
void semcomp_runtime_medi_n(void);  // $F864 MediN
void semcomp_runtime_at_f862(void);  // $F862 at_f862
void semcomp_runtime_at_f741(void);  // $F741 at_f741
void semcomp_runtime_at_f844(void);  // $F844 at_f844
void semcomp_runtime_at_f807(void);  // $F807 at_f807
void semcomp_runtime_at_f706(void);  // $F706 at_f706
void semcomp_runtime_at_f729(void);  // $F729 at_f729
void semcomp_runtime_alternate_length_handler(void);  // $F8C5 AlternateLengthHandler
void semcomp_runtime_at_f8d0(void);  // $F8D0 at_f8d0
void semcomp_runtime_at_f8c9(void);  // $F8C9 at_f8c9
void semcomp_runtime_at_f8ca(void);  // $F8CA at_f8ca
void semcomp_runtime_at_f8c6(void);  // $F8C6 at_f8c6
void semcomp_runtime_at_f8ce(void);  // $F8CE at_f8ce
void semcomp_runtime_at_f8c8(void);  // $F8C8 at_f8c8
void semcomp_runtime_load_control_regs(void);  // $F8D8 LoadControlRegs
void semcomp_runtime_at_f8f1(void);  // $F8F1 at_f8f1
void semcomp_runtime_at_f8e7(void);  // $F8E7 at_f8e7
void semcomp_runtime_load_envelope_data(void);  // $F8F4 LoadEnvelopeData
void semcomp_runtime_at_f8fb(void);  // $F8FB at_f8fb
void semcomp_runtime_at_f90c(void);  // $F90C at_f90c
void semcomp_runtime_at_f903(void);  // $F903 at_f903
void semcomp_runtime_at_f905(void);  // $F905 at_f905

// Phase 33 - EnemyEngine bulk-port (38 multi-entry bodies, 724 entries)
void semcomp_runtime_enemies_and_loops_core(void);  // $C047 EnemiesAndLoopsCore
void semcomp_runtime_at_c058(void);  // $C058 at_c058
void semcomp_runtime_at_c04e(void);  // $C04E at_c04e
void semcomp_runtime_at_c04d(void);  // $C04D at_c04d
void semcomp_runtime_exec_game_loopback(void);  // $C08C ExecGameLoopback
void semcomp_runtime_at_c0c8(void);  // $C0C8 at_c0c8
void semcomp_runtime_at_c0a0(void);  // $C0A0 at_c0a0
void semcomp_runtime_at_c0b7(void);  // $C0B7 at_c0b7
void semcomp_runtime_at_c0c2(void);  // $C0C2 at_c0c2
void semcomp_runtime_at_c0a9(void);  // $C0A9 at_c0a9
void semcomp_runtime_at_c0a8(void);  // $C0A8 at_c0a8
void semcomp_runtime_proc_loop_command(void);  // $C0CC ProcLoopCommand
void semcomp_runtime_at_c0e9(void);  // $C0E9 at_c0e9
void semcomp_runtime_at_c0e1(void);  // $C0E1 at_c0e1
void semcomp_runtime_at_c1be(void);  // $C1BE at_c1be
void semcomp_runtime_at_c0f0(void);  // $C0F0 at_c0f0
void semcomp_runtime_at_c14d(void);  // $C14D at_c14d
void semcomp_runtime_at_c0cf(void);  // $C0CF at_c0cf
void semcomp_runtime_at_c18e(void);  // $C18E at_c18e
void semcomp_runtime_at_c1ae(void);  // $C1AE at_c1ae
void semcomp_runtime_at_c219(void);  // $C219 at_c219
void semcomp_runtime_find_loop(void);  // $C0D8 FindLoop
void semcomp_runtime_at_c242(void);  // $C242 at_c242
void semcomp_runtime_at_c141(void);  // $C141 at_c141
void semcomp_runtime_at_c124(void);  // $C124 at_c124
void semcomp_runtime_do_group(void);  // $C22E DoGroup
void semcomp_runtime_at_c20e(void);  // $C20E at_c20e
void semcomp_runtime_at_c21e(void);  // $C21E at_c21e
void semcomp_runtime_at_c213(void);  // $C213 at_c213
void semcomp_runtime_wrong_chk(void);  // $C115 WrongChk
void semcomp_runtime_inc_m_loop(void);  // $C102 IncMLoop
void semcomp_runtime_at_c0d6(void);  // $C0D6 at_c0d6
void semcomp_runtime_at_c0ff(void);  // $C0FF at_c0ff
void semcomp_runtime_at_c15d(void);  // $C15D at_c15d
void semcomp_runtime_checkpoint_enemy_id(void);  // $C26C CheckpointEnemyID
void semcomp_runtime_no_init_code(void);  // $C2F0 NoInitCode
void semcomp_runtime_init_podoboo(void);  // $C2F7 InitPodoboo
void semcomp_runtime_at_c304(void);  // $C304 at_c304
void semcomp_runtime_at_c302(void);  // $C302 at_c302
void semcomp_runtime_at_c301(void);  // $C301 at_c301
void semcomp_runtime_init_retainer_obj(void);  // $C307 InitRetainerObj
void semcomp_runtime_at_c30b(void);  // $C30B at_c30b
void semcomp_runtime_init_red_koopa(void);  // $C31E InitRedKoopa
void semcomp_runtime_at_c321(void);  // $C321 at_c321
void semcomp_runtime_init_bloober(void);  // $C342 InitBloober
void semcomp_runtime_at_c365(void);  // $C365 at_c365
void semcomp_runtime_at_c367(void);  // $C367 at_c367
void semcomp_runtime_lakitu_and_spiny_handler(void);  // $C3A4 LakituAndSpinyHandler
void semcomp_runtime_chp_chp_ex(void);  // $C44E ChpChpEx
void semcomp_runtime_at_c40a(void);  // $C40A at_c40a
void semcomp_runtime_at_c3d1(void);  // $C3D1 at_c3d1
void semcomp_runtime_dif_loop(void);  // $C40F DifLoop
void semcomp_runtime_at_c420(void);  // $C420 at_c420
void semcomp_runtime_chk_no_en(void);  // $C3CA ChkNoEn
void semcomp_runtime_at_c3c4(void);  // $C3C4 at_c3c4
void semcomp_runtime_at_c424(void);  // $C424 at_c424
void semcomp_runtime_at_c402(void);  // $C402 at_c402
void semcomp_runtime_at_c3b9(void);  // $C3B9 at_c3b9
void semcomp_runtime_at_c416(void);  // $C416 at_c416
void semcomp_runtime_at_c40d(void);  // $C40D at_c40d
void semcomp_runtime_at_c412(void);  // $C412 at_c412
void semcomp_runtime_at_c442(void);  // $C442 at_c442
void semcomp_runtime_chk_lak(void);  // $C3B4 ChkLak
void semcomp_runtime_at_c3c1(void);  // $C3C1 at_c3c1
void semcomp_runtime_at_c3fd(void);  // $C3FD at_c3fd
void semcomp_runtime_init_long_firebar(void);  // $C459 InitLongFirebar
void semcomp_runtime_at_c47d(void);  // $C47D at_c47d
void semcomp_runtime_init_flying_cheep_cheep(void);  // $C4A8 InitFlyingCheepCheep
void semcomp_runtime_at_c511(void);  // $C511 at_c511
void semcomp_runtime_at_c500(void);  // $C500 at_c500
void semcomp_runtime_at_c504(void);  // $C504 at_c504
void semcomp_runtime_at_c4ad(void);  // $C4AD at_c4ad
void semcomp_runtime_at_c4fc(void);  // $C4FC at_c4fc
void semcomp_runtime_at_c4fd(void);  // $C4FD at_c4fd
void semcomp_runtime_at_c4ca(void);  // $C4CA at_c4ca
void semcomp_runtime_at_c502(void);  // $C502 at_c502
void semcomp_runtime_at_c508(void);  // $C508 at_c508
void semcomp_runtime_at_c4b0(void);  // $C4B0 at_c4b0
void semcomp_runtime_at_c521(void);  // $C521 at_c521
void semcomp_runtime_at_c4d1(void);  // $C4D1 at_c4d1
void semcomp_runtime_at_c51f(void);  // $C51F at_c51f
void semcomp_runtime_at_c506(void);  // $C506 at_c506
void semcomp_runtime_at_c50c(void);  // $C50C at_c50c
void semcomp_runtime_at_c533(void);  // $C533 at_c533
void semcomp_runtime_at_c516(void);  // $C516 at_c516
void semcomp_runtime_at_c518(void);  // $C518 at_c518
void semcomp_runtime_init_bowser(void);  // $C549 InitBowser
void semcomp_runtime_at_c56d(void);  // $C56D at_c56d
void semcomp_runtime_at_c54c(void);  // $C54C at_c54c
void semcomp_runtime_at_c563(void);  // $C563 at_c563
void semcomp_runtime_duplicate_enemy_obj(void);  // $C575 DuplicateEnemyObj
void semcomp_runtime_flm_ex(void);  // $C59C FlmEx
void semcomp_runtime_at_c588(void);  // $C588 at_c588
void semcomp_runtime_at_c586(void);  // $C586 at_c586
void semcomp_runtime_init_bowser_flame(void);  // $C5A3 InitBowserFlame
void semcomp_runtime_at_c5cf(void);  // $C5CF at_c5cf
void semcomp_runtime_at_c604(void);  // $C604 at_c604
void semcomp_runtime_set_fr_t(void);  // $C5C9 SetFrT
void semcomp_runtime_at_c606(void);  // $C606 at_c606
void semcomp_runtime_at_c609(void);  // $C609 at_c609
void semcomp_runtime_at_c5c6(void);  // $C5C6 at_c5c6
void semcomp_runtime_at_c5c7(void);  // $C5C7 at_c5c7
void semcomp_runtime_at_c5be(void);  // $C5BE at_c5be
void semcomp_runtime_at_c613(void);  // $C613 at_c613
void semcomp_runtime_set_mf(void);  // $C614 SetMF
void semcomp_runtime_at_c5ad(void);  // $C5AD at_c5ad
void semcomp_runtime_at_c624(void);  // $C624 at_c624
void semcomp_runtime_bullet_bill_cheep_cheep(void);  // $C69C BulletBillCheepCheep
void semcomp_runtime_at_c6d7(void);  // $C6D7 at_c6d7
void semcomp_runtime_at_c6c8(void);  // $C6C8 at_c6c8
void semcomp_runtime_at_c6b1(void);  // $C6B1 at_c6b1
void semcomp_runtime_at_c6ec(void);  // $C6EC at_c6ec
void semcomp_runtime_set17_id(void);  // $C6C3 Set17ID
void semcomp_runtime_at_c74c(void);  // $C74C at_c74c
void semcomp_runtime_at_c75d(void);  // $C75D at_c75d
void semcomp_runtime_at_c700(void);  // $C700 at_c700
void semcomp_runtime_at_c725(void);  // $C725 at_c725
void semcomp_runtime_at_c741(void);  // $C741 at_c741
void semcomp_runtime_at_c738(void);  // $C738 at_c738
void semcomp_runtime_at_c720(void);  // $C720 at_c720
void semcomp_runtime_at_c77a(void);  // $C77A at_c77a
void semcomp_runtime_cnt_grp(void);  // $C74D CntGrp
void semcomp_runtime_at_c772(void);  // $C772 at_c772
void semcomp_runtime_at_c734(void);  // $C734 at_c734
void semcomp_runtime_at_c6ce(void);  // $C6CE at_c6ce
void semcomp_runtime_bb_s_loop(void);  // $C6FF BB_SLoop
void semcomp_runtime_gr_loop(void);  // $C750 GrLoop
void semcomp_runtime_init_piranha_plant(void);  // $C787 InitPiranhaPlant
void semcomp_runtime_at_c78c(void);  // $C78C at_c78c
void semcomp_runtime_init_enemy_frenzy(void);  // $C7A0 InitEnemyFrenzy
void semcomp_runtime_at_c7c9(void);  // $C7C9 at_c7c9
void semcomp_runtime_end_frenzy(void);  // $C7B8 EndFrenzy
void semcomp_runtime_lakitu_chk(void);  // $C7BA LakituChk
void semcomp_runtime_init_bal_platform(void);  // $C7DF InitBalPlatform
void semcomp_runtime_at_c808(void);  // $C808 at_c808
void semcomp_runtime_at_c805(void);  // $C805 at_c805
void semcomp_runtime_at_c800(void);  // $C800 at_c800
void semcomp_runtime_at_c7ef(void);  // $C7EF at_c7ef
void semcomp_runtime_at_c7f7(void);  // $C7F7 at_c7f7
void semcomp_runtime_at_c7ff(void);  // $C7FF at_c7ff
void semcomp_runtime_init_hori_platform(void);  // $C80B InitHoriPlatform
void semcomp_runtime_at_c80f(void);  // $C80F at_c80f
void semcomp_runtime_at_c80d(void);  // $C80D at_c80d
void semcomp_runtime_init_vert_platform(void);  // $C812 InitVertPlatform
void semcomp_runtime_at_c814(void);  // $C814 at_c814
void semcomp_runtime_set_yo(void);  // $C81F SetYO
void semcomp_runtime_at_c816(void);  // $C816 at_c816
void semcomp_runtime_at_c81b(void);  // $C81B at_c81b
void semcomp_runtime_at_c824(void);  // $C824 at_c824
void semcomp_runtime_at_c834(void);  // $C834 at_c834
void semcomp_runtime_at_c81d(void);  // $C81D at_c81d
void semcomp_runtime_at_c818(void);  // $C818 at_c818
void semcomp_runtime_at_c81a(void);  // $C81A at_c81a
void semcomp_runtime_plat_lift_up(void);  // $C84B PlatLiftUp
void semcomp_runtime_at_c84d(void);  // $C84D at_c84d
void semcomp_runtime_plat_lift_down(void);  // $C857 PlatLiftDown
void semcomp_runtime_at_c859(void);  // $C859 at_c859
void semcomp_runtime_at_c85c(void);  // $C85C at_c85c
void semcomp_runtime_pos_platform(void);  // $C871 PosPlatform
void semcomp_runtime_at_c87e(void);  // $C87E at_c87e
void semcomp_runtime_at_c880(void);  // $C880 at_c880
void semcomp_runtime_run_enemy_objects_core(void);  // $C882 RunEnemyObjectsCore
void semcomp_runtime_no_run_code(void);  // $C8D6 NoRunCode
void semcomp_runtime_at_c888(void);  // $C888 at_c888
void semcomp_runtime_jmp_eo(void);  // $C88F JmpEO
void semcomp_runtime_at_c88a(void);  // $C88A at_c88a
void semcomp_runtime_run_normal_enemies(void);  // $C8E0 RunNormalEnemies
void semcomp_runtime_at_c8ff(void);  // $C8FF at_c8ff
void semcomp_runtime_skip_move(void);  // $C902 SkipMove
void semcomp_runtime_at_c8eb(void);  // $C8EB at_c8eb
void semcomp_runtime_at_c8e8(void);  // $C8E8 at_c8e8
void semcomp_runtime_at_c8ee(void);  // $C8EE at_c8ee
void semcomp_runtime_at_c8e5(void);  // $C8E5 at_c8e5
void semcomp_runtime_at_c8f7(void);  // $C8F7 at_c8f7
void semcomp_runtime_at_c8f1(void);  // $C8F1 at_c8f1
void semcomp_runtime_enemy_movement_subs(void);  // $C905 EnemyMovementSubs
void semcomp_runtime_no_move_code(void);  // $C934 NoMoveCode
void semcomp_runtime_run_bowser_flame(void);  // $C935 RunBowserFlame
void semcomp_runtime_at_c938(void);  // $C938 at_c938
void semcomp_runtime_at_c93e(void);  // $C93E at_c93e
void semcomp_runtime_run_firebar_obj(void);  // $C947 RunFirebarObj
void semcomp_runtime_at_c94a(void);  // $C94A at_c94a
void semcomp_runtime_run_small_platform(void);  // $C94D RunSmallPlatform
void semcomp_runtime_at_c959(void);  // $C959 at_c959
void semcomp_runtime_at_c953(void);  // $C953 at_c953
void semcomp_runtime_run_large_platform(void);  // $C965 RunLargePlatform
void semcomp_runtime_at_c96b(void);  // $C96B at_c96b
void semcomp_runtime_at_c96e(void);  // $C96E at_c96e
void semcomp_runtime_at_c97f(void);  // $C97F at_c97f
void semcomp_runtime_large_platform_subroutines(void);  // $C982 LargePlatformSubroutines
void semcomp_runtime_at_c987(void);  // $C987 at_c987
void semcomp_runtime_at_c9ac(void);  // $C9AC at_c9ac
void semcomp_runtime_move_podoboo(void);  // $C9B0 MovePodoboo
void semcomp_runtime_at_c9c0(void);  // $C9C0 at_c9c0
void semcomp_runtime_at_c9c9(void);  // $C9C9 at_c9c9
void semcomp_runtime_at_c9b5(void);  // $C9B5 at_c9b5
void semcomp_runtime_pdb_m(void);  // $C9CB PdbM
void semcomp_runtime_at_c9c7(void);  // $C9C7 at_c9c7
void semcomp_runtime_proc_hammer_bro(void);  // $C9D8 ProcHammerBro
void semcomp_runtime_star_flag_exit(void);  // $D311 StarFlagExit
void semcomp_runtime_no_p_up(void);  // $D84C NoPUp
void semcomp_runtime_ex_sfn(void);  // $DA24 ExSFN
void semcomp_runtime_ex_fl(void);  // $D1EA ExFl
void semcomp_runtime_ex_b_gfx_h(void);  // $D1BB ExBGfxH
void semcomp_runtime_at_d001(void);  // $D001 at_d001
void semcomp_runtime_at_d007(void);  // $D007 at_d007
void semcomp_runtime_at_d907(void);  // $D907 at_d907
void semcomp_runtime_at_d908(void);  // $D908 at_d908
void semcomp_runtime_at_d0c0(void);  // $D0C0 at_d0c0
void semcomp_runtime_at_cea5(void);  // $CEA5 at_cea5
void semcomp_runtime_at_d9cf(void);  // $D9CF at_d9cf
void semcomp_runtime_at_d9ee(void);  // $D9EE at_d9ee
void semcomp_runtime_at_d003(void);  // $D003 at_d003
void semcomp_runtime_at_d9ae(void);  // $D9AE at_d9ae
void semcomp_runtime_at_d98d(void);  // $D98D at_d98d
void semcomp_runtime_at_cdad(void);  // $CDAD at_cdad
void semcomp_runtime_at_cd8e(void);  // $CD8E at_cd8e
void semcomp_runtime_at_c9ea(void);  // $C9EA at_c9ea
void semcomp_runtime_at_d100(void);  // $D100 at_d100
void semcomp_runtime_at_cd87(void);  // $CD87 at_cd87
void semcomp_runtime_at_cf96(void);  // $CF96 at_cf96
void semcomp_runtime_at_ccae(void);  // $CCAE at_ccae
void semcomp_runtime_at_cd4b(void);  // $CD4B at_cd4b
void semcomp_runtime_at_cfb5(void);  // $CFB5 at_cfb5
void semcomp_runtime_at_d89d(void);  // $D89D at_d89d
void semcomp_runtime_at_d1c8(void);  // $D1C8 at_d1c8
void semcomp_runtime_at_d009(void);  // $D009 at_d009
void semcomp_runtime_at_cf76(void);  // $CF76 at_cf76
void semcomp_runtime_at_d18e(void);  // $D18E at_d18e
void semcomp_runtime_at_d94c(void);  // $D94C at_d94c
void semcomp_runtime_at_d1ee(void);  // $D1EE at_d1ee
void semcomp_runtime_at_d1ad(void);  // $D1AD at_d1ad
void semcomp_runtime_at_ca05(void);  // $CA05 at_ca05
void semcomp_runtime_shroom_flower_p_up(void);  // $D820 Shroom_Flower_PUp
void semcomp_runtime_at_cfb9(void);  // $CFB9 at_cfb9
void semcomp_runtime_revive_stunned(void);  // $CAC8 ReviveStunned
void semcomp_runtime_at_d058(void);  // $D058 at_d058
void semcomp_runtime_at_cf8d(void);  // $CF8D at_cf8d
void semcomp_runtime_at_cf9a(void);  // $CF9A at_cf9a
void semcomp_runtime_at_d920(void);  // $D920 at_d920
void semcomp_runtime_s_pixel_lak(void);  // $CFD6 SPixelLak
void semcomp_runtime_at_cb8d(void);  // $CB8D at_cb8d
void semcomp_runtime_at_d7cf(void);  // $D7CF at_d7cf
void semcomp_runtime_at_d031(void);  // $D031 at_d031
void semcomp_runtime_at_d7ae(void);  // $D7AE at_d7ae
void semcomp_runtime_at_d38c(void);  // $D38C at_d38c
void semcomp_runtime_at_d38d(void);  // $D38D at_d38d
void semcomp_runtime_at_cec2(void);  // $CEC2 at_cec2
void semcomp_runtime_chk_player_near_pipe(void);  // $D3CF ChkPlayerNearPipe
void semcomp_runtime_at_ccd0(void);  // $CCD0 at_ccd0
void semcomp_runtime_at_d012(void);  // $D012 at_d012
void semcomp_runtime_at_d660(void);  // $D660 at_d660
void semcomp_runtime_at_cfd7(void);  // $CFD7 at_cfd7
void semcomp_runtime_at_d6d0(void);  // $D6D0 at_d6d0
void semcomp_runtime_too_far(void);  // $D6D2 TooFar
void semcomp_runtime_at_d6c8(void);  // $D6C8 at_d6c8
void semcomp_runtime_at_d6ca(void);  // $D6CA at_d6ca
void semcomp_runtime_at_d6ba(void);  // $D6BA at_d6ba
void semcomp_runtime_at_d6b8(void);  // $D6B8 at_d6b8
void semcomp_runtime_at_d7b8(void);  // $D7B8 at_d7b8
void semcomp_runtime_at_d8cb(void);  // $D8CB at_d8cb
void semcomp_runtime_at_cb8a(void);  // $CB8A at_cb8a
void semcomp_runtime_at_cc4b(void);  // $CC4B at_cc4b
void semcomp_runtime_reverse_plant_speed(void);  // $D3D5 ReversePlantSpeed
void semcomp_runtime_at_d62d(void);  // $D62D at_d62d
void semcomp_runtime_at_d00c(void);  // $D00C at_d00c
void semcomp_runtime_get_v_adder(void);  // $CEBA GetVAdder
void semcomp_runtime_hammer_bro_jump_l_data(void);  // $CA10 HammerBroJumpLData
void semcomp_runtime_at_d041(void);  // $D041 at_d041
void semcomp_runtime_at_d079(void);  // $D079 at_d079
void semcomp_runtime_at_d4b9(void);  // $D4B9 at_d4b9
void semcomp_runtime_at_d4ba(void);  // $D4BA at_d4ba
void semcomp_runtime_set_m2(void);  // $D005 SetM2
void semcomp_runtime_at_cff7(void);  // $CFF7 at_cff7
void semcomp_runtime_ex_pf(void);  // $D5D0 ExPF
void semcomp_runtime_at_d6fa(void);  // $D6FA at_d6fa
void semcomp_runtime_at_d0cb(void);  // $D0CB at_d0cb
void semcomp_runtime_at_d089(void);  // $D089 at_d089
void semcomp_runtime_at_d069(void);  // $D069 at_d069
void semcomp_runtime_at_cec5(void);  // $CEC5 at_cec5
void semcomp_runtime_swim_ccx_move_data(void);  // $CC46 SwimCCXMoveData
void semcomp_runtime_at_cc47(void);  // $CC47 at_cc47
void semcomp_runtime_at_d018(void);  // $D018 at_d018
void semcomp_runtime_at_ce8f(void);  // $CE8F at_ce8f
void semcomp_runtime_at_cfad(void);  // $CFAD at_cfad
void semcomp_runtime_at_cd06(void);  // $CD06 at_cd06
void semcomp_runtime_at_cd07(void);  // $CD07 at_cd07
void semcomp_runtime_at_d0f8(void);  // $D0F8 at_d0f8
void semcomp_runtime_at_cea4(void);  // $CEA4 at_cea4
void semcomp_runtime_at_cd3b(void);  // $CD3B at_cd3b
void semcomp_runtime_at_ce33(void);  // $CE33 at_ce33
void semcomp_runtime_firebar_tbl_offsets(void);  // $CD2E FirebarTblOffsets
void semcomp_runtime_at_cd2f(void);  // $CD2F at_cd2f
void semcomp_runtime_firebar_pos_lookup_tbl(void);  // $CCC7 FirebarPosLookupTbl
void semcomp_runtime_at_ccc8(void);  // $CCC8 at_ccc8
void semcomp_runtime_firebar_mirror_data(void);  // $CD2A FirebarMirrorData
void semcomp_runtime_p_random_subtracter(void);  // $CED5 PRandomSubtracter
void semcomp_runtime_at_ced6(void);  // $CED6 at_ced6
void semcomp_runtime_at_cedb(void);  // $CEDB at_cedb
void semcomp_runtime_lakitu_diff_adj(void);  // $CF25 LakituDiffAdj
void semcomp_runtime_at_d599(void);  // $D599 at_d599
void semcomp_runtime_ex_y_pl(void);  // $D606 ExYPl
void semcomp_runtime_at_d0a1(void);  // $D0A1 at_d0a1
void semcomp_runtime_at_d02e(void);  // $D02E at_d02e
void semcomp_runtime_at_ced2(void);  // $CED2 at_ced2
void semcomp_runtime_bridge_collapse_data(void);  // $CFDD BridgeCollapseData
void semcomp_runtime_at_cfde(void);  // $CFDE at_cfde
void semcomp_runtime_p_random_range(void);  // $D061 PRandomRange
void semcomp_runtime_at_d609(void);  // $D609 at_d609
void semcomp_runtime_at_d721(void);  // $D721 at_d721
void semcomp_runtime_at_d01f(void);  // $D01F at_d01f
void semcomp_runtime_flame_timer_data(void);  // $D1D1 FlameTimerData
void semcomp_runtime_at_d991(void);  // $D991 at_d991
void semcomp_runtime_at_d78d(void);  // $D78D at_d78d
void semcomp_runtime_at_cd7d(void);  // $CD7D at_cd7d
void semcomp_runtime_star_flag_y_pos_adder(void);  // $D2CD StarFlagYPosAdder
void semcomp_runtime_at_d2ce(void);  // $D2CE at_d2ce
void semcomp_runtime_at_d5bd(void);  // $D5BD at_d5bd
void semcomp_runtime_star_flag_tile_data(void);  // $D2D5 StarFlagTileData
void semcomp_runtime_at_d17e(void);  // $D17E at_d17e
void semcomp_runtime_star_flag_x_pos_adder(void);  // $D2D1 StarFlagXPosAdder
void semcomp_runtime_at_d2d2(void);  // $D2D2 at_d2d2
void semcomp_runtime_at_da10(void);  // $DA10 at_da10
void semcomp_runtime_at_d5bc(void);  // $D5BC at_d5bc
void semcomp_runtime_at_d52d(void);  // $D52D at_d52d
void semcomp_runtime_at_d9d6(void);  // $D9D6 at_d9d6
void semcomp_runtime_at_cfd9(void);  // $CFD9 at_cfd9
void semcomp_runtime_at_cfda(void);  // $CFDA at_cfda
void semcomp_runtime_at_d01a(void);  // $D01A at_d01a
void semcomp_runtime_at_cff5(void);  // $CFF5 at_cff5
void semcomp_runtime_at_cf79(void);  // $CF79 at_cf79
void semcomp_runtime_at_d542(void);  // $D542 at_d542
void semcomp_runtime_at_cfb7(void);  // $CFB7 at_cfb7
void semcomp_runtime_at_d8be(void);  // $D8BE at_d8be
void semcomp_runtime_at_ca01(void);  // $CA01 at_ca01
void semcomp_runtime_at_ce2d(void);  // $CE2D at_ce2d
void semcomp_runtime_at_ce2e(void);  // $CE2E at_ce2e
void semcomp_runtime_bowser_identities(void);  // $D736 BowserIdentities
void semcomp_runtime_at_d81d(void);  // $D81D at_d81d
void semcomp_runtime_kicked_shell_x_spd_data(void);  // $D84F KickedShellXSpdData
void semcomp_runtime_kicked_shell_pts_data(void);  // $D892 KickedShellPtsData
void semcomp_runtime_at_d893(void);  // $D893 at_d893
void semcomp_runtime_at_d966(void);  // $D966 at_d966
void semcomp_runtime_demoted_koopa_x_spd_data(void);  // $D851 DemotedKoopaXSpdData
void semcomp_runtime_at_d852(void);  // $D852 at_d852
void semcomp_runtime_at_d2b9(void);  // $D2B9 at_d2b9
void semcomp_runtime_revival_rate_data(void);  // $D9D2 RevivalRateData
void semcomp_runtime_at_cadd(void);  // $CADD at_cadd
void semcomp_runtime_at_d081(void);  // $D081 at_d081
void semcomp_runtime_set_bits_mask(void);  // $DA25 SetBitsMask
void semcomp_runtime_at_d024(void);  // $D024 at_d024
void semcomp_runtime_no_col_fb(void);  // $CE85 NoColFB
void semcomp_runtime_at_ce86(void);  // $CE86 at_ce86
void semcomp_runtime_at_d0ae(void);  // $D0AE at_d0ae
void semcomp_runtime_at_cfc9(void);  // $CFC9 at_cfc9
void semcomp_runtime_at_c9dc(void);  // $C9DC at_c9dc
void semcomp_runtime_at_d0c5(void);  // $D0C5 at_d0c5
void semcomp_runtime_at_ce26(void);  // $CE26 at_ce26
void semcomp_runtime_at_d0e3(void);  // $D0E3 at_d0e3
void semcomp_runtime_at_d0e4(void);  // $D0E4 at_d0e4
void semcomp_runtime_at_cbd0(void);  // $CBD0 at_cbd0
void semcomp_runtime_at_cbd1(void);  // $CBD1 at_cbd1
void semcomp_runtime_at_ca03(void);  // $CA03 at_ca03
void semcomp_runtime_at_c9de(void);  // $C9DE at_c9de
void semcomp_runtime_at_d027(void);  // $D027 at_d027
void semcomp_runtime_at_d6ae(void);  // $D6AE at_d6ae
void semcomp_runtime_at_d0e1(void);  // $D0E1 at_d0e1
void semcomp_runtime_at_c9f9(void);  // $C9F9 at_c9f9
void semcomp_runtime_at_c9da(void);  // $C9DA at_c9da
void semcomp_runtime_at_d61f(void);  // $D61F at_d61f
void semcomp_runtime_at_d047(void);  // $D047 at_d047
void semcomp_runtime_skip_iy(void);  // $D5EC SkipIY
void semcomp_runtime_at_c9e3(void);  // $C9E3 at_c9e3
void semcomp_runtime_at_d595(void);  // $D595 at_d595
void semcomp_runtime_at_d12d(void);  // $D12D at_d12d
void semcomp_runtime_at_caf1(void);  // $CAF1 at_caf1
void semcomp_runtime_at_d905(void);  // $D905 at_d905
void semcomp_runtime_at_d913(void);  // $D913 at_d913
void semcomp_runtime_at_ceb5(void);  // $CEB5 at_ceb5
void semcomp_runtime_at_cc79(void);  // $CC79 at_cc79
void semcomp_runtime_at_cc7d(void);  // $CC7D at_cc7d
void semcomp_runtime_at_d0be(void);  // $D0BE at_d0be
void semcomp_runtime_draw_erase_rope(void);  // $D4BD DrawEraseRope
void semcomp_runtime_at_d603(void);  // $D603 at_d603
void semcomp_runtime_ex_lift_p(void);  // $D679 ExLiftP
void semcomp_runtime_at_cebe(void);  // $CEBE at_cebe
void semcomp_runtime_at_ca0d(void);  // $CA0D at_ca0d
void semcomp_runtime_at_d8db(void);  // $D8DB at_d8db
void semcomp_runtime_at_d8d9(void);  // $D8D9 at_d8d9
void semcomp_runtime_at_cdd9(void);  // $CDD9 at_cdd9
void semcomp_runtime_at_cecd(void);  // $CECD at_cecd
void semcomp_runtime_at_cece(void);  // $CECE at_cece
void semcomp_runtime_at_cecf(void);  // $CECF at_cecf
void semcomp_runtime_at_cfcf(void);  // $CFCF at_cfcf
void semcomp_runtime_at_d2d3(void);  // $D2D3 at_d2d3
void semcomp_runtime_at_d2d4(void);  // $D2D4 at_d2d4
void semcomp_runtime_at_d58a(void);  // $D58A at_d58a
void semcomp_runtime_at_d4d6(void);  // $D4D6 at_d4d6
void semcomp_runtime_at_d3e3(void);  // $D3E3 at_d3e3
void semcomp_runtime_at_d5d2(void);  // $D5D2 at_d5d2
void semcomp_runtime_get_pr_cmp(void);  // $D0D1 GetPRCmp
void semcomp_runtime_at_d7d1(void);  // $D7D1 at_d7d1
void semcomp_runtime_at_d7d7(void);  // $D7D7 at_d7d7
void semcomp_runtime_at_d7d8(void);  // $D7D8 at_d7d8
void semcomp_runtime_at_cabf(void);  // $CABF at_cabf
void semcomp_runtime_ex_sw_cc(void);  // $CCC6 ExSwCC
void semcomp_runtime_at_cbcd(void);  // $CBCD at_cbcd
void semcomp_runtime_at_cc49(void);  // $CC49 at_cc49
void semcomp_runtime_at_d29d(void);  // $D29D at_d29d
void semcomp_runtime_at_d8d3(void);  // $D8D3 at_d8d3
void semcomp_runtime_at_d036(void);  // $D036 at_d036
void semcomp_runtime_at_d033(void);  // $D033 at_d033
void semcomp_runtime_at_d091(void);  // $D091 at_d091
void semcomp_runtime_at_c9ec(void);  // $C9EC at_c9ec
void semcomp_runtime_at_d0b5(void);  // $D0B5 at_d0b5
void semcomp_runtime_at_d03c(void);  // $D03C at_d03c
void semcomp_runtime_remove_bridge(void);  // $D015 RemoveBridge
void semcomp_runtime_at_d0ec(void);  // $D0EC at_d0ec
void semcomp_runtime_at_d0ed(void);  // $D0ED at_d0ed
void semcomp_runtime_at_cdbd(void);  // $CDBD at_cdbd
void semcomp_runtime_at_ca07(void);  // $CA07 at_ca07
void semcomp_runtime_at_d4ad(void);  // $D4AD at_d4ad
void semcomp_runtime_at_d4ae(void);  // $D4AE at_d4ae
void semcomp_runtime_at_d903(void);  // $D903 at_d903
void semcomp_runtime_at_d3ad(void);  // $D3AD at_d3ad
void semcomp_runtime_at_d58d(void);  // $D58D at_d58d
void semcomp_runtime_at_caa9(void);  // $CAA9 at_caa9
void semcomp_runtime_at_d5af(void);  // $D5AF at_d5af
void semcomp_runtime_at_d04c(void);  // $D04C at_d04c
void semcomp_runtime_at_d0f0(void);  // $D0F0 at_d0f0
void semcomp_runtime_at_d5ad(void);  // $D5AD at_d5ad
void semcomp_runtime_at_d0c8(void);  // $D0C8 at_d0c8
void semcomp_runtime_at_d099(void);  // $D099 at_d099
void semcomp_runtime_at_c9f1(void);  // $C9F1 at_c9f1
void semcomp_runtime_at_c9f3(void);  // $C9F3 at_c9f3
void semcomp_runtime_at_d045(void);  // $D045 at_d045
void semcomp_runtime_at_cef4(void);  // $CEF4 at_cef4
void semcomp_runtime_set_v_fbr(void);  // $CE03 SetVFbr
void semcomp_runtime_at_d0f6(void);  // $D0F6 at_d0f6
void semcomp_runtime_at_d0f4(void);  // $D0F4 at_d0f4
void semcomp_runtime_at_d4b1(void);  // $D4B1 at_d4b1
void semcomp_runtime_at_cba0(void);  // $CBA0 at_cba0
void semcomp_runtime_at_ce40(void);  // $CE40 at_ce40
void semcomp_runtime_no_b_fall(void);  // $D05E NoBFall
void semcomp_runtime_at_d9b9(void);  // $D9B9 at_d9b9
void semcomp_runtime_at_d6b0(void);  // $D6B0 at_d6b0
void semcomp_runtime_at_cad7(void);  // $CAD7 at_cad7
void semcomp_runtime_at_d3b9(void);  // $D3B9 at_d3b9
void semcomp_runtime_bowser_control(void);  // $D07F BowserControl
void semcomp_runtime_at_cca8(void);  // $CCA8 at_cca8
void semcomp_runtime_at_d0fb(void);  // $D0FB at_d0fb
void semcomp_runtime_at_ca8e(void);  // $CA8E at_ca8e
void semcomp_runtime_at_d03e(void);  // $D03E at_d03e
void semcomp_runtime_chk_for_fall(void);  // $D44D ChkForFall
void semcomp_runtime_at_d0f2(void);  // $D0F2 at_d0f2
void semcomp_runtime_move_swimming_cheep_cheep(void);  // $CC4A MoveSwimmingCheepCheep
void semcomp_runtime_at_cc4c(void);  // $CC4C at_cc4c
void semcomp_runtime_player_enemy_collision(void);  // $D853 PlayerEnemyCollision
void semcomp_runtime_draw_vine(void);  // $E435 DrawVine
void semcomp_runtime_ex_jc_gfx(void);  // $E6BD ExJCGfx
void semcomp_runtime_ex_ebg(void);  // $DFB8 ExEBG
void semcomp_runtime_at_e539(void);  // $E539 at_e539
void semcomp_runtime_at_daae(void);  // $DAAE at_daae
void semcomp_runtime_at_e6f0(void);  // $E6F0 at_e6f0
void semcomp_runtime_at_e6f1(void);  // $E6F1 at_e6f1
void semcomp_runtime_at_da8d(void);  // $DA8D at_da8d
void semcomp_runtime_at_e00f(void);  // $E00F at_e00f
void semcomp_runtime_at_e0ca(void);  // $E0CA at_e0ca
void semcomp_runtime_at_dfc2(void);  // $DFC2 at_dfc2
void semcomp_runtime_at_e0a1(void);  // $E0A1 at_e0a1
void semcomp_runtime_at_e03d(void);  // $E03D at_e03d
void semcomp_runtime_at_e401(void);  // $E401 at_e401
void semcomp_runtime_at_dfa9(void);  // $DFA9 at_dfa9
void semcomp_runtime_at_dfaa(void);  // $DFAA at_dfaa
void semcomp_runtime_at_e058(void);  // $E058 at_e058
void semcomp_runtime_at_ddae(void);  // $DDAE at_ddae
void semcomp_runtime_at_dd8e(void);  // $DD8E at_dd8e
void semcomp_runtime_cont_chk(void);  // $DD2D ContChk
void semcomp_runtime_at_dd0d(void);  // $DD0D at_dd0d
void semcomp_runtime_at_e0e8(void);  // $E0E8 at_e0e8
void semcomp_runtime_at_db4d(void);  // $DB4D at_db4d
void semcomp_runtime_at_e08e(void);  // $E08E at_e08e
void semcomp_runtime_at_dfca(void);  // $DFCA at_dfca
void semcomp_runtime_at_e274(void);  // $E274 at_e274
void semcomp_runtime_at_e800(void);  // $E800 at_e800
void semcomp_runtime_at_decb(void);  // $DECB at_decb
void semcomp_runtime_at_df21(void);  // $DF21 at_df21
void semcomp_runtime_check_for_retainer_obj(void);  // $E8A9 CheckForRetainerObj
void semcomp_runtime_at_e003(void);  // $E003 at_e003
void semcomp_runtime_at_e5cf(void);  // $E5CF at_e5cf
void semcomp_runtime_at_e5d0(void);  // $E5D0 at_e5d0
void semcomp_runtime_at_e606(void);  // $E606 at_e606
void semcomp_runtime_at_e609(void);  // $E609 at_e609
void semcomp_runtime_at_e60a(void);  // $E60A at_e60a
void semcomp_runtime_at_e605(void);  // $E605 at_e605
void semcomp_runtime_at_e6cd(void);  // $E6CD at_e6cd
void semcomp_runtime_at_e802(void);  // $E802 at_e802
void semcomp_runtime_at_dab9(void);  // $DAB9 at_dab9
void semcomp_runtime_at_dc8e(void);  // $DC8E at_dc8e
void semcomp_runtime_at_dccd(void);  // $DCCD at_dccd
void semcomp_runtime_no_bump(void);  // $E131 NoBump
void semcomp_runtime_at_e603(void);  // $E603 at_e603
void semcomp_runtime_at_e8c9(void);  // $E8C9 at_e8c9
void semcomp_runtime_at_e40d(void);  // $E40D at_e40d
void semcomp_runtime_at_e029(void);  // $E029 at_e029
void semcomp_runtime_at_dc1a(void);  // $DC1A at_dc1a
void semcomp_runtime_at_e56f(void);  // $E56F at_e56f
void semcomp_runtime_at_e818(void);  // $E818 at_e818
void semcomp_runtime_at_e857(void);  // $E857 at_e857
void semcomp_runtime_at_e858(void);  // $E858 at_e858
void semcomp_runtime_at_e1d1(void);  // $E1D1 at_e1d1
void semcomp_runtime_at_dfc0(void);  // $DFC0 at_dfc0
void semcomp_runtime_at_daab(void);  // $DAAB at_daab
void semcomp_runtime_at_dc55(void);  // $DC55 at_dc55
void semcomp_runtime_at_e60d(void);  // $E60D at_e60d
void semcomp_runtime_at_e60e(void);  // $E60E at_e60e
void semcomp_runtime_at_dc16(void);  // $DC16 at_dc16
void semcomp_runtime_player_pos_s_plat_data(void);  // $DC17 PlayerPosSPlatData
void semcomp_runtime_block_buffer_adder_data(void);  // $E3AD BlockBufferAdderData
void semcomp_runtime_pipe_dwn_s(void);  // $DDCE PipeDwnS
void semcomp_runtime_player_bg_upper_extent(void);  // $DC62 PlayerBGUpperExtent
void semcomp_runtime_at_df90(void);  // $DF90 at_df90
void semcomp_runtime_at_e820(void);  // $E820 at_e820
void semcomp_runtime_at_df9b(void);  // $DF9B at_df9b
void semcomp_runtime_at_e4c9(void);  // $E4C9 at_e4c9
void semcomp_runtime_at_e4ca(void);  // $E4CA at_e4ca
void semcomp_runtime_at_de2f(void);  // $DE2F at_de2f
void semcomp_runtime_at_dd20(void);  // $DD20 at_dd20
void semcomp_runtime_area_change_timer_data(void);  // $DE03 AreaChangeTimerData
void semcomp_runtime_at_de8e(void);  // $DE8E at_de8e
void semcomp_runtime_at_dd07(void);  // $DD07 at_dd07
void semcomp_runtime_flagpole_y_pos_data(void);  // $DE29 FlagpoleYPosData
void semcomp_runtime_climb_x_pos_adder(void);  // $DE25 ClimbXPosAdder
void semcomp_runtime_at_db8e(void);  // $DB8E at_db8e
void semcomp_runtime_at_e807(void);  // $E807 at_e807
void semcomp_runtime_at_e80a(void);  // $E80A at_e80a
void semcomp_runtime_at_dfb1(void);  // $DFB1 at_dfb1
void semcomp_runtime_at_dde0(void);  // $DDE0 at_dde0
void semcomp_runtime_solid_m_tile_upper_ext(void);  // $DF8B SolidMTileUpperExt
void semcomp_runtime_climb_m_tile_upper_ext(void);  // $DF96 ClimbMTileUpperExt
void semcomp_runtime_at_e090(void);  // $E090 at_e090
void semcomp_runtime_enemy_bgc_state_data(void);  // $DFB9 EnemyBGCStateData
void semcomp_runtime_at_e389(void);  // $E389 at_e389
void semcomp_runtime_at_e791(void);  // $E791 at_e791
void semcomp_runtime_no_c_dir_f(void);  // $E060 NoCDirF
void semcomp_runtime_at_e061(void);  // $E061 at_e061
void semcomp_runtime_at_e27d(void);  // $E27D at_e27d
void semcomp_runtime_at_e1fe(void);  // $E1FE at_e1fe
void semcomp_runtime_at_e1ff(void);  // $E1FF at_e1ff
void semcomp_runtime_at_e804(void);  // $E804 at_e804
void semcomp_runtime_at_dd04(void);  // $DD04 at_dd04
void semcomp_runtime_at_dd2a(void);  // $DD2A at_dd2a
void semcomp_runtime_at_dd3b(void);  // $DD3B at_dd3b
void semcomp_runtime_at_dd60(void);  // $DD60 at_dd60
void semcomp_runtime_at_dd61(void);  // $DD61 at_dd61
void semcomp_runtime_award_touched_coin(void);  // $DD1A AwardTouchedCoin
void semcomp_runtime_at_e3f1(void);  // $E3F1 at_e3f1
void semcomp_runtime_block_buffer_x_adder(void);  // $E3B0 BlockBuffer_X_Adder
void semcomp_runtime_at_e121(void);  // $E121 at_e121
void semcomp_runtime_at_e3cd(void);  // $E3CD at_e3cd
void semcomp_runtime_at_e1a9(void);  // $E1A9 at_e1a9
void semcomp_runtime_at_e0a9(void);  // $E0A9 at_e0a9
void semcomp_runtime_first_spr_y_pos(void);  // $E4C4 FirstSprYPos
void semcomp_runtime_at_e4c5(void);  // $E4C5 at_e4c5
void semcomp_runtime_second_spr_y_pos(void);  // $E4CC SecondSprYPos
void semcomp_runtime_at_e4cd(void);  // $E4CD at_e4cd
void semcomp_runtime_first_spr_x_pos(void);  // $E4C0 FirstSprXPos
void semcomp_runtime_first_spr_tilenum(void);  // $E4D0 FirstSprTilenum
void semcomp_runtime_second_spr_tilenum(void);  // $E4D4 SecondSprTilenum
void semcomp_runtime_flagpole_score_num_tiles(void);  // $E541 FlagpoleScoreNumTiles
void semcomp_runtime_at_dbd6(void);  // $DBD6 at_dbd6
void semcomp_runtime_at_dbb5(void);  // $DBB5 at_dbb5
void semcomp_runtime_power_up_gfx_table(void);  // $E6BE PowerUpGfxTable
void semcomp_runtime_jumping_coin_tiles(void);  // $E682 JumpingCoinTiles
void semcomp_runtime_at_e683(void);  // $E683 at_e683
void semcomp_runtime_at_e48d(void);  // $E48D at_e48d
void semcomp_runtime_at_e4e4(void);  // $E4E4 at_e4e4
void semcomp_runtime_at_e6c0(void);  // $E6C0 at_e6c0
void semcomp_runtime_at_dcfc(void);  // $DCFC at_dcfc
void semcomp_runtime_at_dcdd(void);  // $DCDD at_dcdd
void semcomp_runtime_at_dfdc(void);  // $DFDC at_dfdc
void semcomp_runtime_hb_chk(void);  // $DFDF HBChk
void semcomp_runtime_at_dcdf(void);  // $DCDF at_dcdf
void semcomp_runtime_at_dddc(void);  // $DDDC at_dddc
void semcomp_runtime_at_ddde(void);  // $DDDE at_ddde
void semcomp_runtime_at_dedf(void);  // $DEDF at_dedf
void semcomp_runtime_at_da7b(void);  // $DA7B at_da7b
void semcomp_runtime_at_dbda(void);  // $DBDA at_dbda
void semcomp_runtime_at_e3d4(void);  // $E3D4 at_e3d4
void semcomp_runtime_at_e2e4(void);  // $E2E4 at_e2e4
void semcomp_runtime_at_e58a(void);  // $E58A at_e58a
void semcomp_runtime_at_e6e7(void);  // $E6E7 at_e6e7
void semcomp_runtime_at_e7e9(void);  // $E7E9 at_e7e9
void semcomp_runtime_jumpspring_frame_offsets(void);  // $E878 JumpspringFrameOffsets
void semcomp_runtime_at_e879(void);  // $E879 at_e879
void semcomp_runtime_enemy_gfx_table_offsets(void);  // $E840 EnemyGfxTableOffsets
void semcomp_runtime_at_dea3(void);  // $DEA3 at_dea3
void semcomp_runtime_next_v_sp(void);  // $E4A2 NextVSp
void semcomp_runtime_at_e4a3(void);  // $E4A3 at_e4a3
void semcomp_runtime_at_e0ea(void);  // $E0EA at_e0ea
void semcomp_runtime_at_e67f(void);  // $E67F at_e67f
void semcomp_runtime_at_e672(void);  // $E672 at_e672
void semcomp_runtime_at_e667(void);  // $E667 at_e667
void semcomp_runtime_at_e01d(void);  // $E01D at_e01d
void semcomp_runtime_at_e04e(void);  // $E04E at_e04e
void semcomp_runtime_at_e646(void);  // $E646 at_e646
void semcomp_runtime_enemy_anim_timing_b_mask(void);  // $E876 EnemyAnimTimingBMask
void semcomp_runtime_at_e877(void);  // $E877 at_e877
void semcomp_runtime_at_e005(void);  // $E005 at_e005
void semcomp_runtime_at_e041(void);  // $E041 at_e041
void semcomp_runtime_at_e007(void);  // $E007 at_e007
void semcomp_runtime_enemy_graphics_table(void);  // $E73E EnemyGraphicsTable
void semcomp_runtime_at_e57d(void);  // $E57D at_e57d
void semcomp_runtime_chk2_msb_st(void);  // $E0EC Chk2MSBSt
void semcomp_runtime_check_for_bullet_bill_cv(void);  // $E8BE CheckForBulletBillCV
void semcomp_runtime_set_wy_spd(void);  // $E048 SetWYSpd
void semcomp_runtime_at_e0ab(void);  // $E0AB at_e0ab
void semcomp_runtime_at_e4ad(void);  // $E4AD at_e4ad
void semcomp_runtime_at_e7bd(void);  // $E7BD at_e7bd
void semcomp_runtime_at_dc20(void);  // $DC20 at_dc20
void semcomp_runtime_at_def0(void);  // $DEF0 at_def0
void semcomp_runtime_at_e8a8(void);  // $E8A8 at_e8a8
void semcomp_runtime_at_e0d0(void);  // $E0D0 at_e0d0
void semcomp_runtime_at_dcd1(void);  // $DCD1 at_dcd1
void semcomp_runtime_p_up_draw_loop(void);  // $E6F7 PUpDrawLoop
void semcomp_runtime_at_e6fa(void);  // $E6FA at_e6fa
void semcomp_runtime_at_e301(void);  // $E301 at_e301
void semcomp_runtime_at_ddd5(void);  // $DDD5 at_ddd5
void semcomp_runtime_at_e3de(void);  // $E3DE at_e3de
void semcomp_runtime_at_dfda(void);  // $DFDA at_dfda
void semcomp_runtime_ex_ste_chk(void);  // $E0A4 ExSteChk
void semcomp_runtime_at_e763(void);  // $E763 at_e763
void semcomp_runtime_at_e1e4(void);  // $E1E4 at_e1e4
void semcomp_runtime_at_e3e1(void);  // $E3E1 at_e3e1
void semcomp_runtime_at_e3e2(void);  // $E3E2 at_e3e2
void semcomp_runtime_at_de1e(void);  // $DE1E at_de1e
void semcomp_runtime_at_e0df(void);  // $E0DF at_e0df
void semcomp_runtime_at_df01(void);  // $DF01 at_df01
void semcomp_runtime_side_check_loop(void);  // $DD66 SideCheckLoop
void semcomp_runtime_at_e7e6(void);  // $E7E6 at_e7e6
void semcomp_runtime_at_de59(void);  // $DE59 at_de59
void semcomp_runtime_at_e850(void);  // $E850 at_e850
void semcomp_runtime_at_df77(void);  // $DF77 at_df77
void semcomp_runtime_at_df71(void);  // $DF71 at_df71
void semcomp_runtime_at_ddd3(void);  // $DDD3 at_ddd3
void semcomp_runtime_chk_small_plat_loop(void);  // $DB8C ChkSmallPlatLoop
void semcomp_runtime_at_e38b(void);  // $E38B at_e38b
void semcomp_runtime_sde_c_loop(void);  // $E10A SdeCLoop
void semcomp_runtime_at_e3b1(void);  // $E3B1 at_e3b1
void semcomp_runtime_at_e3ba(void);  // $E3BA at_e3ba
void semcomp_runtime_no_h_offscr(void);  // $E540 NoHOffscr
void semcomp_runtime_at_e53b(void);  // $E53B at_e53b
void semcomp_runtime_chk_f_top(void);  // $E492 ChkFTop
void semcomp_runtime_at_dec9(void);  // $DEC9 at_dec9
void semcomp_runtime_at_de8a(void);  // $DE8A at_de8a
void semcomp_runtime_at_debf(void);  // $DEBF at_debf
void semcomp_runtime_at_e629(void);  // $E629 at_e629
void semcomp_runtime_at_e6f5(void);  // $E6F5 at_e6f5
void semcomp_runtime_at_e4bd(void);  // $E4BD at_e4bd
void semcomp_runtime_at_e179(void);  // $E179 at_e179
void semcomp_runtime_at_e49d(void);  // $E49D at_e49d
void semcomp_runtime_at_e710(void);  // $E710 at_e710
void semcomp_runtime_set_fall_s(void);  // $DC82 SetFallS
void semcomp_runtime_at_e385(void);  // $E385 at_e385
void semcomp_runtime_at_dc23(void);  // $DC23 at_dc23
void semcomp_runtime_at_e600(void);  // $E600 at_e600
void semcomp_runtime_at_ddbd(void);  // $DDBD at_ddbd
void semcomp_runtime_at_e38d(void);  // $E38D at_e38d
void semcomp_runtime_at_e28d(void);  // $E28D at_e28d
void semcomp_runtime_at_e7b9(void);  // $E7B9 at_e7b9
void semcomp_runtime_at_db93(void);  // $DB93 at_db93
void semcomp_runtime_at_dcb9(void);  // $DCB9 at_dcb9
void semcomp_runtime_at_dd90(void);  // $DD90 at_dd90
void semcomp_runtime_at_e7b1(void);  // $E7B1 at_e7b1
void semcomp_runtime_at_dfd0(void);  // $DFD0 at_dfd0
void semcomp_runtime_at_e59a(void);  // $E59A at_e59a
void semcomp_runtime_at_e61b(void);  // $E61B at_e61b
void semcomp_runtime_at_e0b9(void);  // $E0B9 at_e0b9
void semcomp_runtime_at_e4b9(void);  // $E4B9 at_e4b9
void semcomp_runtime_at_e7a5(void);  // $E7A5 at_e7a5
void semcomp_runtime_at_dd76(void);  // $DD76 at_dd76
void semcomp_runtime_at_db04(void);  // $DB04 at_db04
void semcomp_runtime_at_dd3d(void);  // $DD3D at_dd3d
void semcomp_runtime_at_db5c(void);  // $DB5C at_db5c
void semcomp_runtime_at_db0c(void);  // $DB0C at_db0c
void semcomp_runtime_at_de82(void);  // $DE82 at_de82
void semcomp_runtime_check_left_screen_b_box(void);  // $E30C CheckLeftScreenBBox
void semcomp_runtime_at_e286(void);  // $E286 at_e286
void semcomp_runtime_at_e528(void);  // $E528 at_e528
void semcomp_runtime_at_db3b(void);  // $DB3B at_db3b
void semcomp_runtime_ex_hc(void);  // $DE38 ExHC
void semcomp_runtime_at_dece(void);  // $DECE at_dece
void semcomp_runtime_at_dba7(void);  // $DBA7 at_dba7
void semcomp_runtime_at_e730(void);  // $E730 at_e730
void semcomp_runtime_at_e347(void);  // $E347 at_e347
void semcomp_runtime_at_db47(void);  // $DB47 at_db47
void semcomp_runtime_at_e406(void);  // $E406 at_e406
void semcomp_runtime_at_e001(void);  // $E001 at_e001
void semcomp_runtime_at_e431(void);  // $E431 at_e431
void semcomp_runtime_ex_csm(void);  // $DE02 ExCSM
void semcomp_runtime_at_e408(void);  // $E408 at_e408
void semcomp_runtime_at_e70a(void);  // $E70A at_e70a
void semcomp_runtime_at_dd06(void);  // $DD06 at_dd06
void semcomp_runtime_at_de4b(void);  // $DE4B at_de4b
void semcomp_runtime_at_dd0a(void);  // $DD0A at_dd0a
void semcomp_runtime_at_e112(void);  // $E112 at_e112
void semcomp_runtime_at_df11(void);  // $DF11 at_df11
void semcomp_runtime_at_e139(void);  // $E139 at_e139
void semcomp_runtime_at_e278(void);  // $E278 at_e278
void semcomp_runtime_at_dc27(void);  // $DC27 at_dc27
void semcomp_runtime_at_e722(void);  // $E722 at_e722
void semcomp_runtime_no_ofs2(void);  // $E322 NoOfs2
void semcomp_runtime_at_e372(void);  // $E372 at_e372
void semcomp_runtime_at_e781(void);  // $E781 at_e781
void semcomp_runtime_check_for_p_up_collision(void);  // $D881 CheckForPUpCollision
void semcomp_runtime_at_e8e3(void);  // $E8E3 at_e8e3
void semcomp_runtime_at_e8e5(void);  // $E8E5 at_e8e5
void semcomp_runtime_at_e8fd(void);  // $E8FD at_e8fd
void semcomp_runtime_check_bowser_gfx_flag(void);  // $E8F2 CheckBowserGfxFlag
void semcomp_runtime_at_e8e9(void);  // $E8E9 at_e8e9
void semcomp_runtime_at_e8fb(void);  // $E8FB at_e8fb
void semcomp_runtime_at_e8d9(void);  // $E8D9 at_e8d9
void semcomp_runtime_enemy_to_bg_collision_det(void);  // $DFC1 EnemyToBGCollisionDet
void semcomp_runtime_at_dfc3(void);  // $DFC3 at_dfc3

// Phase 34 - LevelEngine bulk-port (10 multi-entry bodies, 25 entries)
void semcomp_runtime_get_background_color(void);  // $85E3 GetBackgroundColor
void semcomp_runtime_at_862e(void);  // $862E at_862e
void semcomp_runtime_write_game_text(void);  // $8808 WriteGameText
void semcomp_runtime_at_8887(void);  // $8887 at_8887
void semcomp_runtime_at_8846(void);  // $8846 at_8846
void semcomp_runtime_write_block_metatile(void);  // $8A6D WriteBlockMetatile
void semcomp_runtime_move_v_offset(void);  // $8A8F MoveVOffset
void semcomp_runtime_put_block_metatile(void);  // $8A97 PutBlockMetatile
void semcomp_runtime_rem_bridge(void);  // $8ACD RemBridge
void semcomp_runtime_at_8a9d(void);  // $8A9D at_8a9d
void semcomp_runtime_get_area_music(void);  // $90ED GetAreaMusic
void semcomp_runtime_at_9100(void);  // $9100 at_9100
void semcomp_runtime_area_parser_core(void);  // $93FC AreaParserCore
void semcomp_runtime_at_9494(void);  // $9494 at_9494
void semcomp_runtime_terr_loop(void);  // $9491 TerrLoop
void semcomp_runtime_process_area_data(void);  // $9508 ProcessAreaData
void semcomp_runtime_end_a_parse(void);  // $9588 EndAParse
void semcomp_runtime_decode_area_data(void);  // $9595 DecodeAreaData
void semcomp_runtime_loop_cmd_e(void);  // $9645 LoopCmdE
void semcomp_runtime_at_95df(void);  // $95DF at_95df
void semcomp_runtime_area_style_object(void);  // $9740 AreaStyleObject
void semcomp_runtime_at_9792(void);  // $9792 at_9792
void semcomp_runtime_at_9989(void);  // $9989 at_9989
void semcomp_runtime_set_hi_max(void);  // $BF94 SetHiMax
void semcomp_runtime_set_x_move_amt(void);  // $BF96 SetXMoveAmt

// Phase 35 - RenderEngine bulk-port (33 bodies, 217 entries)
void semcomp_runtime_sprite_shuffler(void);  // $81C6 SpriteShuffler
void semcomp_runtime_at_8200(void);  // $8200 at_8200
void semcomp_runtime_set_misc_offset(void);  // $81F9 SetMiscOffset
void semcomp_runtime_oper_mode_execution_tree(void);  // $8212 OperModeExecutionTree
void semcomp_runtime_at_8222(void);  // $8222 at_8222
void semcomp_runtime_draw_mushroom_icon(void);  // $8325 DrawMushroomIcon
void semcomp_runtime_at_8330(void);  // $8330 at_8330
void semcomp_runtime_player_victory_walk(void);  // $83BD PlayerVictoryWalk
void semcomp_runtime_eval_for_music(void);  // $8434 EvalForMusic
void semcomp_runtime_at_8436(void);  // $8436 at_8436
void semcomp_runtime_at_842c(void);  // $842C at_842c
void semcomp_runtime_at_8404(void);  // $8404 at_8404
void semcomp_runtime_player_end_world(void);  // $8461 PlayerEndWorld
void semcomp_runtime_end_exit_one(void);  // $8486 EndExitOne
void semcomp_runtime_screen_routines(void);  // $8567 ScreenRoutines
void semcomp_runtime_at_85ad(void);  // $85AD at_85ad
void semcomp_runtime_do_nothing1(void);  // $92AA DoNothing1
void semcomp_runtime_do_nothing2(void);  // $92AF DoNothing2
void semcomp_runtime_scroll_handler(void);  // $AF93 ScrollHandler
void semcomp_runtime_at_afb1(void);  // $AFB1 at_afb1
void semcomp_runtime_run_game_timer(void);  // $B74F RunGameTimer
void semcomp_runtime_ex_g_timer(void);  // $B7A3 ExGTimer
void semcomp_runtime_move_d_enemy_vertically(void);  // $BF63 MoveD_EnemyVertically
void semcomp_runtime_move_falling_platform(void);  // $BF6B MoveFallingPlatform
void semcomp_runtime_enemy_gfx_handler(void);  // $E87D EnemyGfxHandler
void semcomp_runtime_at_e9a0(void);  // $E9A0 at_e9a0
void semcomp_runtime_at_e939(void);  // $E939 at_e939
void semcomp_runtime_at_e9b2(void);  // $E9B2 at_e9b2
void semcomp_runtime_at_e96d(void);  // $E96D at_e96d
void semcomp_runtime_check_for_goomba(void);  // $E900 CheckForGoomba
void semcomp_runtime_at_e998(void);  // $E998 at_e998
void semcomp_runtime_at_eb20(void);  // $EB20 at_eb20
void semcomp_runtime_at_e96f(void);  // $E96F at_e96f
void semcomp_runtime_at_e987(void);  // $E987 at_e987
void semcomp_runtime_at_e9b6(void);  // $E9B6 at_e9b6
void semcomp_runtime_at_e9d6(void);  // $E9D6 at_e9d6
void semcomp_runtime_at_e908(void);  // $E908 at_e908
void semcomp_runtime_at_eb86(void);  // $EB86 at_eb86
void semcomp_runtime_at_e921(void);  // $E921 at_e921
void semcomp_runtime_at_eba4(void);  // $EBA4 at_eba4
void semcomp_runtime_at_eb84(void);  // $EB84 at_eb84
void semcomp_runtime_at_eba6(void);  // $EBA6 at_eba6
void semcomp_runtime_at_eaad(void);  // $EAAD at_eaad
void semcomp_runtime_at_eae7(void);  // $EAE7 at_eae7
void semcomp_runtime_at_e9eb(void);  // $E9EB at_e9eb
void semcomp_runtime_at_ea3d(void);  // $EA3D at_ea3d
void semcomp_runtime_at_eaba(void);  // $EABA at_eaba
void semcomp_runtime_at_e9d0(void);  // $E9D0 at_e9d0
void semcomp_runtime_at_e9e0(void);  // $E9E0 at_e9e0
void semcomp_runtime_at_e919(void);  // $E919 at_e919
void semcomp_runtime_at_ea20(void);  // $EA20 at_ea20
void semcomp_runtime_check_bowser_rear(void);  // $E94C CheckBowserRear
void semcomp_runtime_at_e960(void);  // $E960 at_e960
void semcomp_runtime_at_e9a4(void);  // $E9A4 at_e9a4
void semcomp_runtime_at_ead0(void);  // $EAD0 at_ead0
void semcomp_runtime_at_ea85(void);  // $EA85 at_ea85
void semcomp_runtime_at_e928(void);  // $E928 at_e928
void semcomp_runtime_at_eb80(void);  // $EB80 at_eb80
void semcomp_runtime_at_ea32(void);  // $EA32 at_ea32
void semcomp_runtime_at_e962(void);  // $E962 at_e962
void semcomp_runtime_skip_to_off_scr_chk(void);  // $EA61 SkipToOffScrChk
void semcomp_runtime_at_e953(void);  // $E953 at_e953
void semcomp_runtime_at_e9b0(void);  // $E9B0 at_e9b0
void semcomp_runtime_at_e9d4(void);  // $E9D4 at_e9d4
void semcomp_runtime_at_eb79(void);  // $EB79 at_eb79
void semcomp_runtime_at_e902(void);  // $E902 at_e902
void semcomp_runtime_draw_bowser(void);  // $E949 DrawBowser
void semcomp_runtime_at_eae1(void);  // $EAE1 at_eae1
void semcomp_runtime_move_e_spr_row_offscreen(void);  // $EBB7 MoveESprRowOffscreen
void semcomp_runtime_at_ebb8(void);  // $EBB8 at_ebb8
void semcomp_runtime_at_ebbc(void);  // $EBBC at_ebbc
void semcomp_runtime_move_e_spr_col_offscreen(void);  // $EBC1 MoveESprColOffscreen
void semcomp_runtime_at_ebc6(void);  // $EBC6 at_ebc6
void semcomp_runtime_at_ebc2(void);  // $EBC2 at_ebc2
void semcomp_runtime_draw_block(void);  // $EBD1 DrawBlock
void semcomp_runtime_at_ec20(void);  // $EC20 at_ec20
void semcomp_runtime_set_b_flip(void);  // $EC21 SetBFlip
void semcomp_runtime_d_blk_loop(void);  // $EBE7 DBlkLoop
void semcomp_runtime_at_ebec(void);  // $EBEC at_ebec
void semcomp_runtime_at_ec23(void);  // $EC23 at_ec23
void semcomp_runtime_at_ebea(void);  // $EBEA at_ebea
void semcomp_runtime_blk_offscr(void);  // $EC35 BlkOffscr
void semcomp_runtime_at_ec00(void);  // $EC00 at_ec00
void semcomp_runtime_draw_brick_chunks(void);  // $EC53 DrawBrickChunks
void semcomp_runtime_at_ec91(void);  // $EC91 at_ec91
void semcomp_runtime_at_ec85(void);  // $EC85 at_ec85
void semcomp_runtime_at_eca5(void);  // $ECA5 at_eca5
void semcomp_runtime_d_chunks(void);  // $EC65 DChunks
void semcomp_runtime_draw_fireball(void);  // $ECDE DrawFireball
void semcomp_runtime_at_ecf0(void);  // $ECF0 at_ecf0
void semcomp_runtime_at_ecf1(void);  // $ECF1 at_ecf1
void semcomp_runtime_draw_explosion_fireball(void);  // $ED09 DrawExplosion_Fireball
void semcomp_runtime_at_ed20(void);  // $ED20 at_ed20
void semcomp_runtime_at_ed18(void);  // $ED18 at_ed18
void semcomp_runtime_at_ed2e(void);  // $ED2E at_ed2e
void semcomp_runtime_draw_small_platform(void);  // $ED66 DrawSmallPlatform
void semcomp_runtime_s_ofs2(void);  // $EDD1 SOfs2
void semcomp_runtime_at_ed6f(void);  // $ED6F at_ed6f
void semcomp_runtime_at_edc5(void);  // $EDC5 at_edc5
void semcomp_runtime_at_ed86(void);  // $ED86 at_ed86
void semcomp_runtime_at_eda6(void);  // $EDA6 at_eda6
void semcomp_runtime_at_edb9(void);  // $EDB9 at_edb9
void semcomp_runtime_at_ed76(void);  // $ED76 at_ed76
void semcomp_runtime_draw_bubble(void);  // $EDE1 DrawBubble
void semcomp_runtime_ex_d_bub(void);  // $EE06 ExDBub
void semcomp_runtime_at_ee03(void);  // $EE03 at_ee03
void semcomp_runtime_at_eded(void);  // $EDED at_eded
void semcomp_runtime_at_ede3(void);  // $EDE3 at_ede3
void semcomp_runtime_at_ede4(void);  // $EDE4 at_ede4
void semcomp_runtime_at_ede6(void);  // $EDE6 at_ede6
void semcomp_runtime_at_ee01(void);  // $EE01 at_ee01
void semcomp_runtime_render_player_sub(void);  // $EFBE RenderPlayerSub
void semcomp_runtime_at_efd1(void);  // $EFD1 at_efd1
void semcomp_runtime_at_efdf(void);  // $EFDF at_efdf
void semcomp_runtime_process_player_action(void);  // $EFEC ProcessPlayerAction
void semcomp_runtime_at_f008(void);  // $F008 at_f008
void semcomp_runtime_at_f041(void);  // $F041 at_f041
void semcomp_runtime_at_f004(void);  // $F004 at_f004
void semcomp_runtime_at_f006(void);  // $F006 at_f006
void semcomp_runtime_at_f012(void);  // $F012 at_f012
void semcomp_runtime_at_f010(void);  // $F010 at_f010
void semcomp_runtime_at_f058(void);  // $F058 at_f058
void semcomp_runtime_at_f02d(void);  // $F02D at_f02d
void semcomp_runtime_at_f001(void);  // $F001 at_f001
void semcomp_runtime_at_f021(void);  // $F021 at_f021
void semcomp_runtime_action_walk_run(void);  // $F03C ActionWalkRun
void semcomp_runtime_at_f01f(void);  // $F01F at_f01f
void semcomp_runtime_at_eff0(void);  // $EFF0 at_eff0
void semcomp_runtime_at_f046(void);  // $F046 at_f046
void semcomp_runtime_at_f014(void);  // $F014 at_f014
void semcomp_runtime_at_f00d(void);  // $F00D at_f00d
void semcomp_runtime_at_f030(void);  // $F030 at_f030
void semcomp_runtime_at_f033(void);  // $F033 at_f033
void semcomp_runtime_at_f025(void);  // $F025 at_f025
void semcomp_runtime_action_falling(void);  // $F034 ActionFalling
void semcomp_runtime_at_f02b(void);  // $F02B at_f02b
void semcomp_runtime_proc_on_ground_acts(void);  // $F00B ProcOnGroundActs
void semcomp_runtime_at_f01d(void);  // $F01D at_f01d
void semcomp_runtime_at_f027(void);  // $F027 at_f027
void semcomp_runtime_at_f05f(void);  // $F05F at_f05f
void semcomp_runtime_at_f060(void);  // $F060 at_f060
void semcomp_runtime_at_f016(void);  // $F016 at_f016
void semcomp_runtime_at_effd(void);  // $EFFD at_effd
void semcomp_runtime_at_f048(void);  // $F048 at_f048
void semcomp_runtime_action_swimming(void);  // $F050 ActionSwimming
void semcomp_runtime_at_f03e(void);  // $F03E at_f03e
void semcomp_runtime_at_f065(void);  // $F065 at_f065
void semcomp_runtime_at_f018(void);  // $F018 at_f018
void semcomp_runtime_at_f05d(void);  // $F05D at_f05d
void semcomp_runtime_at_f052(void);  // $F052 at_f052
void semcomp_runtime_at_f01a(void);  // $F01A at_f01a
void semcomp_runtime_at_f06a(void);  // $F06A at_f06a
void semcomp_runtime_at_f023(void);  // $F023 at_f023
void semcomp_runtime_at_f039(void);  // $F039 at_f039
void semcomp_runtime_three_frame_extent(void);  // $F06D ThreeFrameExtent
void semcomp_runtime_at_f090(void);  // $F090 at_f090
void semcomp_runtime_at_f086(void);  // $F086 at_f086
void semcomp_runtime_at_f07d(void);  // $F07D at_f07d
void semcomp_runtime_at_f074(void);  // $F074 at_f074
void semcomp_runtime_at_f075(void);  // $F075 at_f075
void semcomp_runtime_at_f080(void);  // $F080 at_f080
void semcomp_runtime_at_f088(void);  // $F088 at_f088
void semcomp_runtime_get_gfx_offset_adder(void);  // $F091 GetGfxOffsetAdder
void semcomp_runtime_at_f098(void);  // $F098 at_f098
void semcomp_runtime_handle_change_size(void);  // $F0B0 HandleChangeSize
void semcomp_runtime_at_f0e1(void);  // $F0E1 at_f0e1
void semcomp_runtime_c_sz_next(void);  // $F0C3 CSzNext
void semcomp_runtime_at_f0b9(void);  // $F0B9 at_f0b9
void semcomp_runtime_at_f0ba(void);  // $F0BA at_f0ba
void semcomp_runtime_at_f0c9(void);  // $F0C9 at_f0c9
void semcomp_runtime_gor_s_log(void);  // $F0C6 GorSLog
void semcomp_runtime_at_f0e3(void);  // $F0E3 at_f0e3
void semcomp_runtime_at_f0de(void);  // $F0DE at_f0de
void semcomp_runtime_at_f0cb(void);  // $F0CB at_f0cb
void semcomp_runtime_at_f0d8(void);  // $F0D8 at_f0d8
void semcomp_runtime_at_f0d9(void);  // $F0D9 at_f0d9
void semcomp_runtime_at_f0d1(void);  // $F0D1 at_f0d1
void semcomp_runtime_at_f0c0(void);  // $F0C0 at_f0c0
void semcomp_runtime_at_f0e8(void);  // $F0E8 at_f0e8
void semcomp_runtime_at_f0be(void);  // $F0BE at_f0be
void semcomp_runtime_chk_for_player_attrib(void);  // $F0E9 ChkForPlayerAttrib
void semcomp_runtime_at_f0f0(void);  // $F0F0 at_f0f0
void semcomp_runtime_at_f110(void);  // $F110 at_f110
void semcomp_runtime_at_f0f9(void);  // $F0F9 at_f0f9
void semcomp_runtime_at_f0fd(void);  // $F0FD at_f0fd
void semcomp_runtime_at_f0ee(void);  // $F0EE at_f0ee
void semcomp_runtime_at_f0fb(void);  // $F0FB at_f0fb
void semcomp_runtime_at_f0ff(void);  // $F0FF at_f0ff
void semcomp_runtime_at_f0f2(void);  // $F0F2 at_f0f2
void semcomp_runtime_at_f0f5(void);  // $F0F5 at_f0f5
void semcomp_runtime_at_f11f(void);  // $F11F at_f11f
void semcomp_runtime_relative_misc_position(void);  // $F148 RelativeMiscPosition
void semcomp_runtime_at_f14d(void);  // $F14D at_f14d
void semcomp_runtime_get_obj_relative_position(void);  // $F171 GetObjRelativePosition
void semcomp_runtime_get_player_offscreen_bits(void);  // $F180 GetPlayerOffscreenBits
void semcomp_runtime_at_f184(void);  // $F184 at_f184
void semcomp_runtime_get_misc_offscreen_bits(void);  // $F19B GetMiscOffscreenBits
void semcomp_runtime_at_f19d(void);  // $F19D at_f19d
void semcomp_runtime_get_proper_obj_offset(void);  // $F1A8 GetProperObjOffset
void semcomp_runtime_at_f1a9(void);  // $F1A9 at_f1a9
void semcomp_runtime_get_enemy_offscreen_bits(void);  // $F1AF GetEnemyOffscreenBits
void semcomp_runtime_at_f1b1(void);  // $F1B1 at_f1b1
void semcomp_runtime_get_block_offscreen_bits(void);  // $F1B6 GetBlockOffscreenBits
void semcomp_runtime_at_f1d1(void);  // $F1D1 at_f1d1
void semcomp_runtime_at_f1bd(void);  // $F1BD at_f1bd
void semcomp_runtime_at_f1bc(void);  // $F1BC at_f1bc
void semcomp_runtime_at_f1c1(void);  // $F1C1 at_f1c1
void semcomp_runtime_at_f1ce(void);  // $F1CE at_f1ce
void semcomp_runtime_get_y_offscreen_bits(void);  // $F239 GetYOffscreenBits
void semcomp_runtime_y_ofs_loop(void);  // $F23D YOfsLoop
void semcomp_runtime_draw_sprite_object(void);  // $F282 DrawSpriteObject
void semcomp_runtime_at_f2bd(void);  // $F2BD at_f2bd
void semcomp_runtime_at_f285(void);  // $F285 at_f285
void semcomp_runtime_at_f286(void);  // $F286 at_f286
void semcomp_runtime_at_f2a5(void);  // $F2A5 at_f2a5
void semcomp_runtime_at_f284(void);  // $F284 at_f284
void semcomp_runtime_at_f2c8(void);  // $F2C8 at_f2c8
void semcomp_runtime_at_f288(void);  // $F288 at_f288

// Phase 36 - FinalBodies remaining multi-entry (22 bodies, 229 entries)
void semcomp_runtime_bank_switch_8286(void);  // $8286 BankSwitch_8286
void semcomp_runtime_at_82bd(void);  // $82BD at_82bd
void semcomp_runtime_bank_switch_838_e(void);  // $838E BankSwitch_838E
void semcomp_runtime_at_8426(void);  // $8426 at_8426
void semcomp_runtime_bank_switch_8653(void);  // $8653 BankSwitch_8653
void semcomp_runtime_at_8660(void);  // $8660 at_8660
void semcomp_runtime_bank_switch_8750(void);  // $8750 BankSwitch_8750
void semcomp_runtime_at_8759(void);  // $8759 at_8759
void semcomp_runtime_bank_switch_9_a56(void);  // $9A56 BankSwitch_9A56
void semcomp_runtime_at_9a5c(void);  // $9A5C at_9a5c
void semcomp_runtime_at_9a9b(void);  // $9A9B at_9a9b
void semcomp_runtime_bank_switch_b2_ce(void);  // $B2CE BankSwitch_B2CE
void semcomp_runtime_at_b396(void);  // $B396 at_b396
void semcomp_runtime_at_b5c8(void);  // $B5C8 at_b5c8
void semcomp_runtime_at_b67c(void);  // $B67C at_b67c
void semcomp_runtime_bank_switch_b976(void);  // $B976 BankSwitch_B976
void semcomp_runtime_at_bfc6(void);  // $BFC6 at_bfc6
void semcomp_runtime_at_b9a9(void);  // $B9A9 at_b9a9
void semcomp_runtime_at_bb33(void);  // $BB33 at_bb33
void semcomp_runtime_at_bb48(void);  // $BB48 at_bb48
void semcomp_runtime_at_bc57(void);  // $BC57 at_bc57
void semcomp_runtime_at_bc9e(void);  // $BC9E at_bc9e
void semcomp_runtime_at_bd35(void);  // $BD35 at_bd35
void semcomp_runtime_at_bd8c(void);  // $BD8C at_bd8c
void semcomp_runtime_at_bedb(void);  // $BEDB at_bedb
void semcomp_runtime_body_c11_e(void);  // $C11E Body_C11E
void semcomp_runtime_at_c120(void);  // $C120 at_c120
void semcomp_runtime_body_c4_ce(void);  // $C4CE Body_C4CE
void semcomp_runtime_at_c4d0(void);  // $C4D0 at_c4d0
void semcomp_runtime_body_c8_dc(void);  // $C8DC Body_C8DC
void semcomp_runtime_at_c8e1(void);  // $C8E1 at_c8e1
void semcomp_runtime_body_c923(void);  // $C923 Body_C923
void semcomp_runtime_at_c927(void);  // $C927 at_c927
void semcomp_runtime_at_c930(void);  // $C930 at_c930
void semcomp_runtime_body_c9_f0(void);  // $C9F0 Body_C9F0
void semcomp_runtime_at_c9fa(void);  // $C9FA at_c9fa
void semcomp_runtime_at_c9f4(void);  // $C9F4 at_c9f4
void semcomp_runtime_at_c9f2(void);  // $C9F2 at_c9f2
void semcomp_runtime_body_ca47(void);  // $CA47 Body_CA47
void semcomp_runtime_at_ca49(void);  // $CA49 at_ca49
void semcomp_runtime_body_d0_c7(void);  // $D0C7 Body_D0C7
void semcomp_runtime_at_d0c9(void);  // $D0C9 at_d0c9
void semcomp_runtime_body_d3_d2(void);  // $D3D2 Body_D3D2
void semcomp_runtime_at_d3d4(void);  // $D3D4 at_d3d4
void semcomp_runtime_body_e1_ac(void);  // $E1AC Body_E1AC
void semcomp_runtime_at_e1af(void);  // $E1AF at_e1af
void semcomp_runtime_body_e23_e(void);  // $E23E Body_E23E
void semcomp_runtime_at_e244(void);  // $E244 at_e244
void semcomp_runtime_body_e7_b3(void);  // $E7B3 Body_E7B3
void semcomp_runtime_at_e7d1(void);  // $E7D1 at_e7d1
void semcomp_runtime_at_e7de(void);  // $E7DE at_e7de
void semcomp_runtime_body_ee5_b(void);  // $EE5B Body_EE5B
void semcomp_runtime_at_ee61(void);  // $EE61 at_ee61
void semcomp_runtime_at_eeb6(void);  // $EEB6 at_eeb6
void semcomp_runtime_at_eed1(void);  // $EED1 at_eed1
void semcomp_runtime_body_f4_c0(void);  // $F4C0 Body_F4C0
void semcomp_runtime_at_f507(void);  // $F507 at_f507
void semcomp_runtime_at_f4f9(void);  // $F4F9 at_f4f9
void semcomp_runtime_at_f911(void);  // $F911 at_f911
void semcomp_runtime_at_f938(void);  // $F938 at_f938
void semcomp_runtime_music_header_data(void);  // $F90D MusicHeaderData
void semcomp_runtime_at_f4f1(void);  // $F4F1 at_f4f1
void semcomp_runtime_victory_mus_hdr(void);  // $F961 VictoryMusHdr
void semcomp_runtime_at_f4fd(void);  // $F4FD at_f4fd
void semcomp_runtime_at_f4f4(void);  // $F4F4 at_f4f4
void semcomp_runtime_at_f508(void);  // $F508 at_f508
void semcomp_runtime_at_f501(void);  // $F501 at_f501
void semcomp_runtime_extra_life_freq_data(void);  // $F4D4 ExtraLifeFreqData
void semcomp_runtime_brick_shatter_freq_data(void);  // $F62B BrickShatterFreqData
void semcomp_runtime_at_f90f(void);  // $F90F at_f90f
void semcomp_runtime_at_f919(void);  // $F919 at_f919
void semcomp_runtime_at_f92b(void);  // $F92B at_f92b
void semcomp_runtime_at_f96d(void);  // $F96D at_f96d
void semcomp_runtime_at_f914(void);  // $F914 at_f914
void semcomp_runtime_body_f693(void);  // $F693 Body_F693
void semcomp_runtime_at_f695(void);  // $F695 at_f695
void semcomp_runtime_ground_level_part1_hdr(void);  // $F976 GroundLevelPart1Hdr
void semcomp_runtime_at_ffaa(void);  // $FFAA at_ffaa
void semcomp_runtime_bowser_flame_env_data(void);  // $FFCA BowserFlameEnvData
void semcomp_runtime_at_f990(void);  // $F990 at_f990
void semcomp_runtime_at_f991(void);  // $F991 at_f991
void semcomp_runtime_at_fdaa(void);  // $FDAA at_fdaa
void semcomp_runtime_at_fbaa(void);  // $FBAA at_fbaa
void semcomp_runtime_at_ffa0(void);  // $FFA0 at_ffa0
void semcomp_runtime_at_fad1(void);  // $FAD1 at_fad1
void semcomp_runtime_at_fda6(void);  // $FDA6 at_fda6
void semcomp_runtime_at_fea5(void);  // $FEA5 at_fea5
void semcomp_runtime_water_event_mus_env_data(void);  // $FFA2 WaterEventMusEnvData
void semcomp_runtime_at_ff01(void);  // $FF01 at_ff01
void semcomp_runtime_at_f9a9(void);  // $F9A9 at_f9a9
void semcomp_runtime_at_faa1(void);  // $FAA1 at_faa1
void semcomp_runtime_at_fda0(void);  // $FDA0 at_fda0
void semcomp_runtime_at_fca1(void);  // $FCA1 at_fca1
void semcomp_runtime_at_faf1(void);  // $FAF1 at_faf1
void semcomp_runtime_at_fd38(void);  // $FD38 at_fd38
void semcomp_runtime_at_fa10(void);  // $FA10 at_fa10
void semcomp_runtime_at_fc86(void);  // $FC86 at_fc86
void semcomp_runtime_at_fea9(void);  // $FEA9 at_fea9
void semcomp_runtime_at_faad(void);  // $FAAD at_faad
void semcomp_runtime_at_fa0e(void);  // $FA0E at_fa0e
void semcomp_runtime_at_ff4c(void);  // $FF4C at_ff4c
void semcomp_runtime_at_ff4d(void);  // $FF4D at_ff4d
void semcomp_runtime_at_fe4d(void);  // $FE4D at_fe4d
void semcomp_runtime_at_ff86(void);  // $FF86 at_ff86
void semcomp_runtime_at_fe29(void);  // $FE29 at_fe29
void semcomp_runtime_at_fca9(void);  // $FCA9 at_fca9
void semcomp_runtime_at_fbf7(void);  // $FBF7 at_fbf7
void semcomp_runtime_at_fdfc(void);  // $FDFC at_fdfc
void semcomp_runtime_at_fe08(void);  // $FE08 at_fe08
void semcomp_runtime_at_fe02(void);  // $FE02 at_fe02
void semcomp_runtime_at_ff07(void);  // $FF07 at_ff07
void semcomp_runtime_at_f9f0(void);  // $F9F0 at_f9f0
void semcomp_runtime_at_fc4c(void);  // $FC4C at_fc4c
void semcomp_runtime_at_fec9(void);  // $FEC9 at_fec9
void semcomp_runtime_at_fd7d(void);  // $FD7D at_fd7d
void semcomp_runtime_at_ff7e(void);  // $FF7E at_ff7e
void semcomp_runtime_at_fc29(void);  // $FC29 at_fc29
void semcomp_runtime_at_fa50(void);  // $FA50 at_fa50
void semcomp_runtime_at_fbfa(void);  // $FBFA at_fbfa
void semcomp_runtime_at_fbf9(void);  // $FBF9 at_fbf9
void semcomp_runtime_at_fcfd(void);  // $FCFD at_fcfd
void semcomp_runtime_at_fcad(void);  // $FCAD at_fcad
void semcomp_runtime_at_fcb2(void);  // $FCB2 at_fcb2
void semcomp_runtime_at_fca5(void);  // $FCA5 at_fca5
void semcomp_runtime_at_fc99(void);  // $FC99 at_fc99
void semcomp_runtime_at_fc8f(void);  // $FC8F at_fc8f
void semcomp_runtime_at_fc95(void);  // $FC95 at_fc95
void semcomp_runtime_at_fc96(void);  // $FC96 at_fc96
void semcomp_runtime_at_fc74(void);  // $FC74 at_fc74
void semcomp_runtime_at_fc70(void);  // $FC70 at_fc70
void semcomp_runtime_at_fc6e(void);  // $FC6E at_fc6e
void semcomp_runtime_at_fcf6(void);  // $FCF6 at_fcf6
void semcomp_runtime_at_fcf4(void);  // $FCF4 at_fcf4
void semcomp_runtime_at_fcbc(void);  // $FCBC at_fcbc
void semcomp_runtime_at_fcbd(void);  // $FCBD at_fcbd
void semcomp_runtime_at_fcef(void);  // $FCEF at_fcef
void semcomp_runtime_at_fcc2(void);  // $FCC2 at_fcc2
void semcomp_runtime_at_fccc(void);  // $FCCC at_fccc
void semcomp_runtime_at_fcf1(void);  // $FCF1 at_fcf1
void semcomp_runtime_at_ff24(void);  // $FF24 at_ff24
void semcomp_runtime_at_ff02(void);  // $FF02 at_ff02
void semcomp_runtime_at_fc0f(void);  // $FC0F at_fc0f
void semcomp_runtime_at_fc36(void);  // $FC36 at_fc36
void semcomp_runtime_at_fc39(void);  // $FC39 at_fc39
void semcomp_runtime_at_fc40(void);  // $FC40 at_fc40
void semcomp_runtime_at_fc41(void);  // $FC41 at_fc41
void semcomp_runtime_at_fc43(void);  // $FC43 at_fc43
void semcomp_runtime_at_fc44(void);  // $FC44 at_fc44
void semcomp_runtime_at_fc47(void);  // $FC47 at_fc47
void semcomp_runtime_at_fc4a(void);  // $FC4A at_fc4a
void semcomp_runtime_at_fc91(void);  // $FC91 at_fc91
void semcomp_runtime_at_fc93(void);  // $FC93 at_fc93
void semcomp_runtime_at_fc94(void);  // $FC94 at_fc94
void semcomp_runtime_at_fc9f(void);  // $FC9F at_fc9f
void semcomp_runtime_at_fc50(void);  // $FC50 at_fc50
void semcomp_runtime_at_fcf9(void);  // $FCF9 at_fcf9
void semcomp_runtime_at_fefc(void);  // $FEFC at_fefc
void semcomp_runtime_at_faa5(void);  // $FAA5 at_faa5
void semcomp_runtime_at_fa85(void);  // $FA85 at_fa85
void semcomp_runtime_at_ff47(void);  // $FF47 at_ff47
void semcomp_runtime_brick_shatter_env_data(void);  // $FFEA BrickShatterEnvData
void semcomp_runtime_at_fda4(void);  // $FDA4 at_fda4
void semcomp_runtime_at_fd46(void);  // $FD46 at_fd46
void semcomp_runtime_at_fba6(void);  // $FBA6 at_fba6
void semcomp_runtime_ground_level_part4_b_hdr(void);  // $F9A6 GroundLevelPart4BHdr
void semcomp_runtime_at_f9a4(void);  // $F9A4 at_f9a4
void semcomp_runtime_at_f9e6(void);  // $F9E6 at_f9e6
void semcomp_runtime_music_length_lookup_tbl(void);  // $FF66 MusicLengthLookupTbl
void semcomp_runtime_at_ff97(void);  // $FF97 at_ff97
void semcomp_runtime_area_music_env_data(void);  // $FF9A AreaMusicEnvData
void semcomp_runtime_time_run_out_mus_data(void);  // $FC72 TimeRunOutMusData
void semcomp_runtime_at_fcc5(void);  // $FCC5 at_fcc5
void semcomp_runtime_silence_data(void);  // $FA1C SilenceData
void semcomp_runtime_at_fa1d(void);  // $FA1D at_fa1d
void semcomp_runtime_castle_mus_data(void);  // $FBA4 CastleMusData
void semcomp_runtime_water_mus_data(void);  // $FD52 WaterMusData
void semcomp_runtime_end_of_castle_mus_data(void);  // $FE51 EndOfCastleMusData
void semcomp_runtime_ground_m_p1_data(void);  // $FA01 GroundM_P1Data
void semcomp_runtime_ground_m_p2_a_data(void);  // $FA49 GroundM_P2AData
void semcomp_runtime_ground_m_p2_c_data(void);  // $FA9D GroundM_P2CData
void semcomp_runtime_ground_m_p3_a_data(void);  // $FAC2 GroundM_P3AData
void semcomp_runtime_ground_m_p3_b_data(void);  // $FADB GroundM_P3BData
void semcomp_runtime_ground_m_p4_a_data(void);  // $FB25 GroundM_P4AData
void semcomp_runtime_ground_m_p4_b_data(void);  // $FB4B GroundM_P4BData
void semcomp_runtime_ground_m_p4_c_data(void);  // $FB74 GroundM_P4CData
void semcomp_runtime_death_mus_data(void);  // $FB72 DeathMusData
void semcomp_runtime_at_ffc0(void);  // $FFC0 at_ffc0
void semcomp_runtime_at_ff14(void);  // $FF14 at_ff14
void semcomp_runtime_at_fe00(void);  // $FE00 at_fe00
void semcomp_runtime_at_ff35(void);  // $FF35 at_ff35
void semcomp_runtime_at_fe54(void);  // $FE54 at_fe54
void semcomp_runtime_at_fa80(void);  // $FA80 at_fa80
void semcomp_runtime_at_fa84(void);  // $FA84 at_fa84
void semcomp_runtime_at_fd0c(void);  // $FD0C at_fd0c
void semcomp_runtime_at_fafb(void);  // $FAFB at_fafb
void semcomp_runtime_at_fd50(void);  // $FD50 at_fd50
void semcomp_runtime_at_faa9(void);  // $FAA9 at_faa9
void semcomp_runtime_at_ffba(void);  // $FFBA at_ffba
void semcomp_runtime_at_f9bd(void);  // $F9BD at_f9bd
void semcomp_runtime_at_fb29(void);  // $FB29 at_fb29
void semcomp_runtime_at_ff18(void);  // $FF18 at_ff18
void semcomp_runtime_at_fa8d(void);  // $FA8D at_fa8d
void semcomp_runtime_at_fc88(void);  // $FC88 at_fc88
void semcomp_runtime_at_fdc9(void);  // $FDC9 at_fdc9
void semcomp_runtime_at_fe05(void);  // $FE05 at_fe05
void semcomp_runtime_at_fb82(void);  // $FB82 at_fb82
void semcomp_runtime_at_ffbc(void);  // $FFBC at_ffbc
void semcomp_runtime_at_fb0e(void);  // $FB0E at_fb0e
void semcomp_runtime_at_ffb4(void);  // $FFB4 at_ffb4
void semcomp_runtime_at_fa07(void);  // $FA07 at_fa07
void semcomp_runtime_at_fe0b(void);  // $FE0B at_fe0b
void semcomp_runtime_at_fa12(void);  // $FA12 at_fa12
void semcomp_runtime_at_fe87(void);  // $FE87 at_fe87
void semcomp_runtime_at_fc00(void);  // $FC00 at_fc00
void semcomp_runtime_at_fc62(void);  // $FC62 at_fc62
void semcomp_runtime_at_fc15(void);  // $FC15 at_fc15
void semcomp_runtime_at_fc21(void);  // $FC21 at_fc21
void semcomp_runtime_at_fc26(void);  // $FC26 at_fc26
void semcomp_runtime_at_fa42(void);  // $FA42 at_fa42
void semcomp_runtime_at_ffac(void);  // $FFAC at_ffac
void semcomp_runtime_at_fc84(void);  // $FC84 at_fc84
void semcomp_runtime_at_fc04(void);  // $FC04 at_fc04
void semcomp_runtime_at_fc09(void);  // $FC09 at_fc09
void semcomp_runtime_at_fbfc(void);  // $FBFC at_fbfc
void semcomp_runtime_at_ff20(void);  // $FF20 at_ff20
void semcomp_runtime_at_fabc(void);  // $FABC at_fabc
void semcomp_runtime_at_f99e(void);  // $F99E at_f99e
void semcomp_runtime_at_f9df(void);  // $F9DF at_f9df
void semcomp_runtime_at_fb2b(void);  // $FB2B at_fb2b

#ifdef __cplusplus
}
#endif
