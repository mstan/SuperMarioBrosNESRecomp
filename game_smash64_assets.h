#pragma once

/*
 * Runtime-only selected Smash 64 fighter presentation.
 *
 * The loader consumes assets_ssb64/falcon_runtime.bin, which is generated
 * locally from the owner's ignored ROM extraction. No model, texture, or
 * animation bytes are compiled into the repository. The function returns 0
 * when the blob is absent or invalid so the caller can draw the cube fallback.
 * A voxel mesh session must already be active. output_scale converts the
 * native-pixel presentation size to the current render target (1 for native,
 * 2 for the Falcon-only supersample surface).
 */
int game_smash64_assets_prepare_root(const char *root);
int game_smash64_assets_prepare_character_root(const char *root,
                                                const char *controller_id);
void game_smash64_assets_clear(void);

/* Owner-baked Pikachu special-effect cards.  These are deliberately exposed
 * as read-only texture views rather than making the generic model layout part
 * of the presentation API.  Returns zero when an older/incomplete cache is
 * active, so callers can simply omit the effect rather than inventing a
 * misleading flat replacement. */
enum {
    SMASH64_PIKACHU_EFFECT_THUNDER_JOLT = 0,
    SMASH64_PIKACHU_EFFECT_THUNDER = 1,
};
int game_smash64_assets_pikachu_effect_texture(
    unsigned effect, unsigned frame, const unsigned int **pixels,
    int *width, int *height);

int game_smash64_assets_draw(float center_x, float foot_y,
                             float output_scale);

/* Sample one frame of an animation's hidden Smash 64 TransN stream. Values
 * are returned in Falcon source units after Captain's exact 1.05 TopN scale;
 * the SMB host performs its ordinary single world conversion afterward. */
int game_smash64_assets_root_delta(const char *animation_name, float frame,
                                   float *delta_y, float *delta_z);

/* Draw the planted midpoint of Falcon's grounded Wait window. Used while
 * SMB1 owns a scripted power-up or injury transformation. */
int game_smash64_assets_draw_idle(float center_x, float foot_y,
                                  float output_scale);

/* Draw a neutral presentation while SMB1 owns native swimming. facing_right
 * comes from SMB1's player-facing byte; the frozen foreign controller is not
 * mutated merely to keep the render facing the direction of travel. */
int game_smash64_assets_draw_swim(float center_x, float foot_y,
                                  float output_scale, int facing_right);

/* Draw a presentation-only source pose for SMB1-owned scripted movement.
 * Flagpole uses Falcon's closest available airborne pose; autowalk uses the
 * authentic middle walk cycle. */
int game_smash64_assets_draw_scripted(float center_x, float foot_y,
                                      float output_scale,
                                      int scripted_presentation,
                                      float presentation_frame);

/* Draw Falcon around a center point in the aerial tumble used by the
 * presentation-only SMB1 death replacement. spin_radians rotates the whole
 * fighter in the 2D screen plane; SMB1 remains authoritative for life loss. */
int game_smash64_assets_draw_death(float center_x, float center_y,
                                   float output_scale, float spin_radians,
                                   float animation_frame);
