/*
 * s3k_rings.h -- Obj_Bouncing_Ring: the rings Sonic scatters when he is hit.
 *
 * Ported from sonic3k.asm (Obj_Bouncing_Ring loc_1A67A/loc_1A75C,
 * ChangeRingFrame, Touch_ChkValue's ring branch, Ani_RingSparkle). Positions
 * are host world pixels in 16.8 fixed point with S3K's +Y-down axis; the host
 * supplies the floor probe (RingCheckFloorDist) and consumes collections.
 */
#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define S3K_RING_SPILL_MAX 32

typedef enum S3KRingState {
    S3K_RING_FREE = 0,
    S3K_RING_BOUNCING,
    S3K_RING_SPARKLE
} S3KRingState;

typedef struct S3KRing {
    uint8_t  state;
    uint8_t  mapping_frame;
    uint8_t  anim_frame;
    uint8_t  anim_timer;
    int32_t  x;        /* 16.8 */
    int32_t  y;        /* 16.8 */
    int16_t  x_vel;
    int16_t  y_vel;
} S3KRing;

typedef struct S3KRingSpill {
    S3KRing  rings[S3K_RING_SPILL_MAX];
    uint8_t  spill_anim_counter;  /* Ring_spill_anim_counter */
    uint8_t  spill_anim_frame;    /* Ring_spill_anim_frame   */
    uint16_t spill_anim_accum;    /* Ring_spill_anim_accum   */
    uint8_t  vint_counter;        /* V_int_run_count+3        */
} S3KRingSpill;

/* RingCheckFloorDist: distance from (x, y_bottom) to the floor surface,
 * negative when the point is inside solid floor. */
typedef int (*S3KRingFloorDist)(int world_x, int y_bottom, void *user);

/* Obj_Bouncing_Ring init: spill `count` rings (capped at 32) from a point.
 * `sine` is S3K's SineTable (GetSineCosine: sin = sine[a], cos = sine[a+$40]). */
void s3k_rings_spill(S3KRingSpill *s, const int16_t *sine, int count,
                     int world_x, int y);

/* One frame of ChangeRingFrame + every bouncing ring. `bottom_y` is the
 * Camera_max_Y_pos+$E0 kill line in the same Y space as the rings. */
void s3k_rings_update(S3KRingSpill *s, S3KRingFloorDist floor_dist,
                      void *user, int bottom_y);

/* Touch_Process against the player's touch box. Touch_ChkValue refuses rings
 * while invulnerability_timer >= 90. Returns the number of rings collected
 * (each becomes a sparkle). */
int s3k_rings_collect(S3KRingSpill *s, int left, int top, int right,
                      int bottom, uint8_t invulnerability_timer);

void s3k_rings_clear(S3KRingSpill *s);
int s3k_rings_active(const S3KRingSpill *s);

#ifdef __cplusplus
}
#endif
