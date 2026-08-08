#pragma once

#include <stdint.h>

/*
 * game_smash64_render.h — M6.1/M6.2 presentation glue for the Smash 64
 * player replacement mod.
 *
 * Deliberately separate from game_smash64.c (owned by the physics
 * workstream): this file only draws. It reads game_smash64_active() and
 * g_ram's screen-space player mirror bytes and writes nothing back into NES
 * state, RAM, or the physics/ownership machinery.
 *
 * SCOPE (M6.1/M6.2): replace Mario's on-screen sprite with a hardcoded
 * flat-shaded 3D cube, positioned and gated on game_smash64_active() so it
 * tracks the player only while Falcon is actually driving and disappears
 * the instant SMB1 takes back a scripted sequence. No model, no animation
 * yet -- that is M6.3+.
 *
 * Screen-to-world convention (there is no tile grid here, so this file's
 * camera and vertex data define what world space means -- see
 * voxel_renderer.h's mesh API doc):
 *   world X = screen column, i.e. the same coordinate space as OAM X and
 *             g_ram[0x03AD], offset by g_widescreen_left so the cube lands
 *             on the correct framebuffer column under widescreen too.
 *   world Y = height in pixels above the player's own foot row, positive
 *             up. Y = 0 is the screen row one past the OAM sprite's bottom
 *             edge (g_ram[0x03B8] + sprite height), matching the "foot" of
 *             the metasprite it replaces.
 *   world Z = depth around 0, existing purely to give the cube volume --
 *             there is no world geometry to align it with.
 * The camera sits at a fixed offset (back along -Z, up along +Y, a small
 * lateral X) from a look-at pinned to the cube's center, rather than
 * straight-on: a straight-on axis-aligned view of a box degenerates to a
 * flat square and would show no 3D cue at all. Exact pixel registration
 * with the OAM box it replaces is not a goal -- the visual mismatch between
 * a 3D actor and the flat 8-bit world is the point of M6, not a bug to hide.
 */

/* Register the OAM suppression predicate. Call once from game_on_init();
 * the predicate self-gates on game_smash64_active(), so registering it
 * early does not change behavior before the mod is enabled. */
void game_smash64_render_init(void);

/* Draw the cube in place of the player's sprite when game_smash64_active()
 * is true; a no-op otherwise. Call from game_post_render(), alongside the
 * existing game_voxel_post_render() call. */
void game_smash64_render_post_render(uint32_t *framebuffer);
