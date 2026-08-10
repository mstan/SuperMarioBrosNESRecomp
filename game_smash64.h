#pragma once

#include <stdint.h>

/*
 * SMB1 host adapter for the Smash 64 player replacement mod.
 *
 * Answers "where is the player allowed to go" and owns everything the fighter
 * controllers must not see: NES RAM layout, SMB1's fixed-point velocity
 * representation, its scripted player states, and the one world-scale
 * conversion.
 *
 * Scope (M2 + M3): Falcon supplies horizontal velocity and vertical motion
 * (jump velocity, gravity, terminal velocity, fast fall, air drift). SMB1 still
 * decides when a jump starts and when a landing happens, and owns all
 * collision.
 *
 * See game_smash64.c for the Ghidra-confirmed addresses and
 * docs/smb1_player_adapter.md for the write log.
 */

/* Launcher-facing switch, driven by the mod package. Selects the fighter by
 * ForeignController id; passing NULL or an unknown id leaves the mod off and
 * SMB1 completely stock. */
int game_smash64_set_mod_enabled(int enabled, const char *controller_id);

/* Register the trusted function-entry hook. Called before main() from the mod
 * plugin; the hook starts DISABLED so registration cannot change behaviour. */
int game_smash64_register_hooks(void);

/* Called once from game_on_init. */
void game_smash64_init(void);

/* Called every VBlank before NMI: samples the pad for this frame. */
void game_smash64_update_input(uint64_t frame_count);

/* Called every VBlank after NMI. */
void game_smash64_update(uint64_t frame_count);

/* PC-scoped RAM-read adaptation used by extras.c. Only PlayerBGCollision's
 * size/crouch geometry reads are changed; native gameplay consequences keep
 * the real hidden Mario power-up state. */
uint8_t game_smash64_ram_read_hook(uint16_t pc, uint16_t addr, uint8_t val);

/* 1 while Falcon is actually driving the player this frame. */
int game_smash64_active(void);

/* Controller identity gates for presentation and character-specific policy. */
int game_smash64_falcon_selected(void);
int game_smash64_samus_selected(void);

/* Native SMB consequences shared by player-replacement combat adapters. */
int game_smash64_defeat_enemies(double left, double right,
                                double top, double bottom, int max_hits);
int game_smash64_break_bricks(double left, double right,
                              double top, double bottom);

/* Presentation-only exception for SMB1's native PlayerDeath routine. Falcon
 * never owns death physics or progression, but the renderer may replace the
 * Mario death metasprite with a falling Smash-style tumble while this is 1. */
int game_smash64_death_presentation_active(void);

/* 1 during SMB1's grow/shrink, injury-blink, and fire-flower scripts. These
 * mechanics remain native, but presentation holds Falcon in a planted pose
 * instead of exposing Mario's transformation frames. */
int game_smash64_still_presentation_active(void);

/* 1 during ordinary player control in a water area. SMB1 keeps native swim
 * input and physics, while the renderer replaces only Mario's presentation. */
int game_smash64_swim_presentation_active(void);

typedef enum Smash64ScriptedPresentation {
    SMASH64_SCRIPTED_PRESENTATION_NONE = 0,
    SMASH64_SCRIPTED_PRESENTATION_FLAGPOLE,
    SMASH64_SCRIPTED_PRESENTATION_WALK,
    SMASH64_SCRIPTED_PRESENTATION_PIPE_SIDE,
    SMASH64_SCRIPTED_PRESENTATION_PIPE_VERTICAL
} Smash64ScriptedPresentation;

/* Presentation-only replacements for native scripted movement that visibly
 * represents the player: pipes, flagpole sliding, and entrance/end autowalk.
 * SMB1 retains complete ownership of movement, timing, and progression. */
Smash64ScriptedPresentation game_smash64_scripted_presentation(void);

/* Frames on which Falcon supplied the horizontal velocity. Lets a scripted
 * run assert the takeover happened rather than inferring it from pixels. */
unsigned long game_smash64_owned_frames(void);

/* Frames on which SMB1 refused the proposed horizontal motion -- it zeroed
 * Player_X_Speed via ImpedePlayerMove and we honoured that. Nonzero proves the
 * collision feedback loop is live rather than silently ignored. */
unsigned long game_smash64_wall_frames(void);

/* Frames on which Falcon supplied the vertical motion, replacing SMB1's own
 * integrator and its 4px/frame fall cap. */
unsigned long game_smash64_air_frames(void);

/* M3.5 jumpsquat handshake. Frames on which SMB1's A bit was withheld so
 * Falcon's KneeBend could run, and frames on which it was presented to launch
 * him. A squat count of 0 across a run that jumped means the window never
 * opened and every jump was a full hop -- the M3 behaviour this replaces. */
unsigned long game_smash64_squat_frames(void);
unsigned long game_smash64_launch_frames(void);

/* Frames on which SMB1 imposed a vertical velocity of its own -- a stomp
 * bounce, a jumpspring, a shattered brick, or a jump killed against a block --
 * and Falcon adopted it. Zero across a run that stomped something means those
 * events are being discarded again. */
unsigned long game_smash64_imposed_frames(void);
