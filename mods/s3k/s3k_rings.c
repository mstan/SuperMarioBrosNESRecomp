/*
 * s3k_rings.c -- Obj_Bouncing_Ring, ported from sonic3k.asm.
 */
#include "s3k_rings.h"

#include <string.h>

/* Ani_RingSparkle: delay 5, Map_Ring frames 4-7, then $FC (delete). */
static const uint8_t k_sparkle[] = { 0x05, 0x04, 0x05, 0x06, 0x07, 0xFC };

void s3k_rings_clear(S3KRingSpill *s)
{
    memset(s, 0, sizeof(*s));
}

int s3k_rings_active(const S3KRingSpill *s)
{
    for (int i = 0; i < S3K_RING_SPILL_MAX; ++i)
        if (s->rings[i].state != S3K_RING_FREE) return 1;
    return 0;
}

void s3k_rings_spill(S3KRingSpill *s, const int16_t *sine, int count,
                     int world_x, int y)
{
    uint16_t d4 = 0x288;
    int16_t d2 = 0, d3 = 0;
    int placed = 0;

    if (count > 0x20) count = 0x20;
    for (int n = 0; n < count; ++n) {
        S3KRing *r = NULL;
        for (int i = 0; i < S3K_RING_SPILL_MAX; ++i) {
            if (s->rings[i].state == S3K_RING_FREE) {
                r = &s->rings[i];
                break;
            }
        }
        if (!r) break;   /* AllocateObjectAfterCurrent failed */

        memset(r, 0, sizeof(*r));
        r->state = S3K_RING_BOUNCING;
        r->x = world_x * 256;
        r->y = y * 256;

        if (!(d4 & 0x8000u)) {
            const uint8_t angle = (uint8_t)d4;
            const uint8_t shift = (uint8_t)(d4 >> 8);
            int16_t d0 = sine ? sine[angle] : 0;
            int16_t d1 = sine ? sine[(unsigned)angle + 0x40u] : 0;
            d0 = (int16_t)(uint16_t)((uint16_t)d0 << shift);
            d1 = (int16_t)(uint16_t)((uint16_t)d1 << shift);
            d2 = d0;
            d3 = d1;
            {
                const unsigned low = (d4 & 0xFFu) + 0x10u;
                d4 = (uint16_t)((d4 & 0xFF00u) | (low & 0xFFu));
                if (low > 0xFFu) {
                    if (d4 < 0x80u) d4 = 0x288;     /* subi.w #$80 borrowed */
                    else d4 = (uint16_t)(d4 - 0x80u);
                }
            }
        }
        r->x_vel = d2;
        r->y_vel = d3;
        d2 = (int16_t)-d2;
        d4 = (uint16_t)-(int16_t)d4;
        placed++;
    }
    if (placed) s->spill_anim_counter = 0xFF;
}

void s3k_rings_update(S3KRingSpill *s, S3KRingFloorDist floor_dist,
                      void *user, int bottom_y)
{
    /* ChangeRingFrame's spill animation. */
    if (s->spill_anim_counter) {
        uint16_t d0 = (uint16_t)(s->spill_anim_counter + s->spill_anim_accum);
        s->spill_anim_accum = d0;
        d0 = (uint16_t)((d0 << 7) | (d0 >> 9));   /* rol.w #7 */
        s->spill_anim_frame = (uint8_t)(d0 & 3u);
        s->spill_anim_counter--;
    }
    s->vint_counter++;

    for (int i = 0; i < S3K_RING_SPILL_MAX; ++i) {
        S3KRing *r = &s->rings[i];
        if (r->state == S3K_RING_SPARKLE) {
            /* Animate_Sprite on Ani_RingSparkle. */
            if (r->anim_timer) {
                r->anim_timer--;
                continue;
            }
            r->anim_timer = k_sparkle[0];
            if (k_sparkle[1u + r->anim_frame] == 0xFC) {
                r->state = S3K_RING_FREE;
                continue;
            }
            r->mapping_frame = k_sparkle[1u + r->anim_frame];
            r->anim_frame++;
            continue;
        }
        if (r->state != S3K_RING_BOUNCING) continue;

        /* loc_1A75C */
        r->mapping_frame = s->spill_anim_frame;
        r->x += r->x_vel;
        r->y += r->y_vel;
        r->y_vel = (int16_t)(uint16_t)((uint16_t)r->y_vel + 0x18u);
        if (r->y_vel < 0) continue;
        /* d7 is the object loop counter, distinct per object. */
        if (((uint8_t)(s->vint_counter + (uint8_t)i) & 7u) == 0 && floor_dist) {
            const int px = r->x >> 8;
            const int py = r->y >> 8;
            const int d1 = floor_dist(px, py + 8, user);
            if (d1 < 0) {
                r->y += d1 * 256;
                r->y_vel = (int16_t)(r->y_vel - (r->y_vel >> 2));
                r->y_vel = (int16_t)-r->y_vel;
            }
        }
        if (s->spill_anim_counter == 0 || (r->y >> 8) > bottom_y) {
            r->state = S3K_RING_FREE;
        }
    }
}

int s3k_rings_collect(S3KRingSpill *s, int left, int top, int right,
                      int bottom, uint8_t invulnerability_timer)
{
    int got = 0;
    if (invulnerability_timer >= 90) return 0;
    for (int i = 0; i < S3K_RING_SPILL_MAX; ++i) {
        S3KRing *r = &s->rings[i];
        int rx, ry;
        if (r->state != S3K_RING_BOUNCING) continue;
        rx = r->x >> 8;
        ry = r->y >> 8;
        /* Touch_Sizes entry 7: 6x6 half extents. */
        if (rx - 6 <= right && rx + 6 >= left &&
            ry - 6 <= bottom && ry + 6 >= top) {
            r->state = S3K_RING_SPARKLE;
            r->anim_frame = 0;
            r->anim_timer = 0;
            r->mapping_frame = 4;
            got++;
        }
    }
    return got;
}
