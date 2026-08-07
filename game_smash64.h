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
 * M2 scope: horizontal ground movement only. SMB1 keeps jump, gravity,
 * vertical collision, horizontal collision and position integration.
 *
 * See game_smash64.c for the Ghidra-confirmed addresses and
 * docs/smb1_player_adapter.md for the write log.
 */

/* Launcher-facing switch, driven by the mod package. Selects the fighter by
 * ForeignController id; passing NULL or an unknown id leaves the mod off and
 * SMB1 completely stock. */
void game_smash64_set_mod_enabled(int enabled, const char *controller_id);

/* Register the trusted function-entry hook. Called before main() from the mod
 * plugin; the hook starts DISABLED so registration cannot change behaviour. */
int game_smash64_register_hooks(void);

/* Called once from game_on_init. */
void game_smash64_init(void);

/* Called every VBlank before NMI: samples the pad for this frame. */
void game_smash64_update_input(uint64_t frame_count);

/* Called every VBlank after NMI. */
void game_smash64_update(uint64_t frame_count);

/* 1 while Falcon is actually driving the player this frame. */
int game_smash64_active(void);

/* Frames on which Falcon supplied the horizontal velocity. Lets a scripted
 * run assert the takeover happened rather than inferring it from pixels. */
unsigned long game_smash64_owned_frames(void);

/* Frames on which SMB1 refused the proposed horizontal motion -- it zeroed
 * Player_X_Speed via ImpedePlayerMove and we honoured that. Nonzero proves the
 * collision feedback loop is live rather than silently ignored. */
unsigned long game_smash64_wall_frames(void);
