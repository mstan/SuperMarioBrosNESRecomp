#pragma once

#include <stdint.h>

/*
 * SMB1 host adapter for the Smash 64 player replacement mod.
 *
 * Answers "where is the player allowed to go" and owns everything the
 * fighter controllers must not see: NES RAM layout, SMB1's page+pixel
 * coordinates, its tiles, and its scripted player states.
 *
 * See game_smash64.c for the ownership policy and the scale constants, and
 * nesrecomp/docs/FOREIGN_CONTROLLER.md for the boundary contract.
 */

/* Launcher-facing switch, driven by the mod package. Selects the fighter by
 * ForeignController id; passing NULL or an unknown id leaves the mod off and
 * SMB1 completely stock. */
void game_smash64_set_mod_enabled(int enabled, const char *controller_id);

/* Called once from game_on_init. */
void game_smash64_init(void);

/* Called every VBlank before NMI: samples input, decides ownership, ticks
 * the active controller. */
void game_smash64_update_input(uint64_t frame_count);

/* Called every VBlank after NMI: syncs resolved state back into SMB1 and
 * completes this tick's trace row. */
void game_smash64_update(uint64_t frame_count);

/* 1 while a fighter is actually driving the player. */
int game_smash64_active(void);
