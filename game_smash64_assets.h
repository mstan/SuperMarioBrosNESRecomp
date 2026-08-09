#pragma once

/*
 * Runtime-only Captain Falcon asset presentation.
 *
 * The loader consumes assets_ssb64/falcon_runtime.bin, which is generated
 * locally from the owner's ignored ROM extraction. No model, texture, or
 * animation bytes are compiled into the repository. The function returns 0
 * when the blob is absent or invalid so the caller can draw the cube fallback.
 * A voxel mesh session must already be active. output_scale converts the
 * native-pixel presentation size to the current render target (1 for native,
 * 2 for the Falcon-only supersample surface).
 */
int game_smash64_assets_draw(float center_x, float foot_y,
                             float output_scale);

/* Draw the planted midpoint of Falcon's grounded Wait window. Used while
 * SMB1 owns a scripted power-up or injury transformation. */
int game_smash64_assets_draw_idle(float center_x, float foot_y,
                                  float output_scale);

/* Draw Falcon around a center point in the aerial tumble used by the
 * presentation-only SMB1 death replacement. spin_radians rotates the whole
 * fighter in the 2D screen plane; SMB1 remains authoritative for life loss. */
int game_smash64_assets_draw_death(float center_x, float center_y,
                                   float output_scale, float spin_radians,
                                   float animation_frame);
