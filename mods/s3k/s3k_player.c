/*
 * s3k_player.c -- Sonic 3 & Knuckles player object, ported routine by
 * routine from skdisasm/sonic3k.asm. See s3k_player.h for the host split.
 *
 * Arithmetic is done on uint16_t/uint8_t with the 68000's carry and sign
 * tests spelled out, because several of S3K's behaviours depend on them:
 * the direction-dependent skid threshold (the documented FixBugs item in
 * sub_113F6/sub_11482), JumpPeakDecelerate's unsigned y_vel window, and the
 * bcc/bcs clamps in the friction code. The retail (non-FixBugs) behaviour is
 * what is reproduced.
 */
#include "s3k_player.h"

#include <string.h>

/* sonic3k.asm Sonic_Init / Sonic_Water / SonicKnux_Spindash constants. */
#define S3K_DEFAULT_Y_RADIUS 0x13
#define S3K_DEFAULT_X_RADIUS 0x09
#define S3K_ROLL_Y_RADIUS    0x0E
#define S3K_ROLL_X_RADIUS    0x07

static const uint16_t k_spindash_speeds[9] = {
    0x800, 0x880, 0x900, 0x980, 0xA00, 0xA80, 0xB00, 0xB80, 0xC00
};

/* AniSonic (General/Sprites/Sonic/Anim - Sonic.asm), verbatim. */
static const uint8_t k_ani00[] = { 0xFF, 0x07, 0x08, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0xFF };
static const uint8_t k_ani01[] = { 0xFF, 0x21, 0x22, 0x23, 0x24, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
static const uint8_t k_ani02[] = { 0xFE, 0x96, 0x97, 0x96, 0x98, 0x96, 0x99, 0x96, 0x9A, 0xFF };
static const uint8_t k_ani04[] = { 0xFD, 0xB6, 0xB7, 0xB8, 0xB9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
static const uint8_t k_ani05[] = {
    0x05, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA,
    0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA,
    0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA, 0xBA,
    0xBA, 0xBA, 0xBA, 0xBB, 0xBC, 0xBC, 0xBD, 0xBD, 0xBE, 0xBE, 0xBD, 0xBD, 0xBE, 0xBE, 0xBD, 0xBD,
    0xBE, 0xBE, 0xBD, 0xBD, 0xBE, 0xBE, 0xBD, 0xBD, 0xBE, 0xBE, 0xBD, 0xBD, 0xBE, 0xBE, 0xBD, 0xBD,
    0xBE, 0xBE, 0xBD, 0xBD, 0xBE, 0xBE, 0xAD, 0xAD, 0xAD, 0xAD, 0xAD, 0xAD, 0xAE, 0xAE, 0xAE, 0xAE,
    0xAE, 0xAE, 0xAF, 0xD9, 0xD9, 0xD9, 0xD9, 0xD9, 0xD9, 0xAF, 0xAF, 0xFE, 0x35
};
static const uint8_t k_ani06[] = { 0x07, 0xA4, 0xA5, 0xA6, 0xFF };
static const uint8_t k_ani07[] = { 0x05, 0xC3, 0xC4, 0xFE, 0x01 };
static const uint8_t k_ani08[] = { 0x05, 0x9B, 0x9C, 0xFE, 0x01 };
static const uint8_t k_ani09[] = { 0x00, 0x86, 0x87, 0x86, 0x88, 0x86, 0x89, 0x86, 0x8A, 0x86, 0x8B, 0xFF };
static const uint8_t k_ani0A[] = {
    0x09, 0xBA, 0xC5, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7,
    0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xFD, 0x00
};
static const uint8_t k_ani0B[] = { 0x0F, 0x8F, 0xFF };
static const uint8_t k_ani0C[] = { 0x05, 0xA1, 0xA2, 0xA3, 0xFF };
static const uint8_t k_ani0D[] = { 0x03, 0x9D, 0x9E, 0x9F, 0xA0, 0xFD, 0x00 };
static const uint8_t k_ani0E[] = { 0x07, 0xC8, 0xFF };
static const uint8_t k_ani0F[] = { 0x07, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xFF };
static const uint8_t k_ani10[] = { 0x2F, 0x8E, 0xFD, 0x00 };
static const uint8_t k_ani11[] = { 0x01, 0xAA, 0xAB, 0xFF };
static const uint8_t k_ani12[] = { 0x0F, 0x43, 0x43, 0x43, 0xFE, 0x01 };
static const uint8_t k_ani13[] = { 0x07, 0xB0, 0xB2, 0xB2, 0xB2, 0xB2, 0xB2, 0xB2, 0xB1, 0xB2, 0xB3, 0xB2, 0xFE, 0x04 };
static const uint8_t k_ani14[] = { 0x13, 0x91, 0xFF };
static const uint8_t k_ani15[] = { 0x0B, 0xAC, 0xAC, 0x03, 0x04, 0xFD, 0x00 };
static const uint8_t k_ani16[] = { 0x20, 0xA8, 0xFF };
static const uint8_t k_ani17[] = { 0x20, 0xA9, 0xFF };
static const uint8_t k_ani18[] = { 0x20, 0xA7, 0xFF };
static const uint8_t k_ani19[] = { 0x09, 0xD7, 0xD8, 0xFF };
static const uint8_t k_ani1A[] = { 0x40, 0x8D, 0xFF };
static const uint8_t k_ani1B[] = { 0x09, 0x8C, 0x8D, 0xFF };
static const uint8_t k_ani1C[] = { 0x77, 0x00, 0xFF };
static const uint8_t k_ani1D[] = { 0x13, 0xD0, 0xD1, 0xFF };
static const uint8_t k_ani1E[] = { 0x03, 0xCF, 0xC8, 0xC9, 0xCA, 0xCB, 0xFE, 0x04 };
static const uint8_t k_ani20[] = { 0x09, 0x08, 0x09, 0xFF };
static const uint8_t k_ani21[] = { 0x03, 0x07, 0xFD, 0x00 };
static const uint8_t k_ani22[] = { 0x0B, 0x90, 0x91, 0x92, 0x91, 0xFF };
static const uint8_t k_ani23[] = { 0x0B, 0x90, 0x91, 0x92, 0x91, 0xFD, 0x00 };
/* AniSonic1F is shared with AniSuperSonic and only reachable from the Super
 * transformation, which SMB1 has no emeralds for. Use the regular table's
 * entry $1F slot as the transform script anyway so indices stay aligned. */
static const uint8_t k_ani1F[] = {
    0x02, 0xD2, 0xD2, 0xD3, 0xD3, 0xD4, 0xD5, 0xD6, 0xD5, 0xD6, 0xD5, 0xD6, 0xD5, 0xD6, 0xFD, 0x00
};

static const struct { const uint8_t *data; uint8_t len; } k_ani_sonic[] = {
#define ANI(t) { t, (uint8_t)sizeof(t) }
    ANI(k_ani00), ANI(k_ani01), ANI(k_ani02), ANI(k_ani02), ANI(k_ani04),
    ANI(k_ani05), ANI(k_ani06), ANI(k_ani07), ANI(k_ani08), ANI(k_ani09),
    ANI(k_ani0A), ANI(k_ani0B), ANI(k_ani0C), ANI(k_ani0D), ANI(k_ani0E),
    ANI(k_ani0F), ANI(k_ani10), ANI(k_ani11), ANI(k_ani12), ANI(k_ani13),
    ANI(k_ani14), ANI(k_ani15), ANI(k_ani16), ANI(k_ani17), ANI(k_ani18),
    ANI(k_ani19), ANI(k_ani1A), ANI(k_ani1B), ANI(k_ani1C), ANI(k_ani1D),
    ANI(k_ani1E), ANI(k_ani1F), ANI(k_ani20), ANI(k_ani21), ANI(k_ani22),
    ANI(k_ani23)
#undef ANI
};
#define S3K_ANI_COUNT (sizeof(k_ani_sonic) / sizeof(k_ani_sonic[0]))

/* Ani_InstaShield / Ani_FireShield (General/Sprites/Shields). */
static const uint8_t k_insta0[] = { 0x1F, 0x06, 0xFF };
static const uint8_t k_insta1[] = {
    0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x07, 0xFD, 0x00
};
static const uint8_t k_fire0[] = {
    0x01, 0x00, 0x0F, 0x01, 0x10, 0x02, 0x11, 0x03, 0x12, 0x04, 0x13, 0x05, 0x14, 0x06, 0x15, 0x07, 0x16, 0x08, 0x17, 0xFF
};
static const uint8_t k_fire1[] = {
    0x01, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0xFD, 0x00
};
/* Ani_S2Shield: Obj_S2Shield, S3K's standard shield. S3K keeps the object,
 * its mappings and this script but ships no art for it; the presentation
 * draws it with Sonic 2's shield art when that ROM is supplied. */
static const uint8_t k_s2shield[] = {
    0x00, 0x05, 0x00, 0x05, 0x01, 0x05, 0x02, 0x05, 0x03, 0x05, 0x04, 0xFF
};

static uint8_t script_byte(const uint8_t *script, uint8_t len, unsigned index)
{
    /* Every retail script terminates in a command before running out; a
     * malformed index reads a loop command rather than out-of-bounds data. */
    return index < len ? script[index] : 0xFF;
}

static void play_sfx(S3KPlayer *p, uint8_t id)
{
    if (p->sfx_count < S3K_PLAYER_SFX_CAPACITY)
        p->sfx[p->sfx_count++] = id;
}

static int16_t s16(uint16_t v) { return (int16_t)v; }

/* ---------------------------------------------------------------- init -- */

void s3k_player_init(S3KPlayer *p)
{
    memset(p, 0, sizeof(*p));
    p->routine = S3K_ROUTINE_CONTROL;
    p->y_radius = S3K_DEFAULT_Y_RADIUS;
    p->x_radius = S3K_DEFAULT_X_RADIUS;
    p->max_speed = 0x600;
    p->acceleration = 0x0C;
    p->deceleration = 0x80;
    p->air_left = 30;
    p->anim = S3K_ANIM_WAIT;
    p->prev_anim = 0xFF;
    p->mapping_frame = 0xBA;
    /* Obj_InstaShield init: move.w #1,anim(a0) clears anim, prev_anim = 1. */
    p->shield_anim = 0;
    p->shield_prev_anim = 1;
    p->shield_mapping_frame = 0x06;
}

static void set_normal_speeds(S3KPlayer *p)
{
    if (p->status & S3K_STATUS_UNDERWATER) {
        p->max_speed = 0x300;
        p->acceleration = 0x06;
        p->deceleration = 0x40;
    } else if (p->status_secondary & S3K_STATUS2_SPEED_SHOES) {
        p->max_speed = 0xC00;
        p->acceleration = 0x18;
        p->deceleration = 0x80;
    } else {
        p->max_speed = 0x600;
        p->acceleration = 0x0C;
        p->deceleration = 0x80;
    }
}

/* --------------------------------------------------------- Player_TouchFloor */

static void bubble_shield_bounce(S3KPlayer *p)
{
    /* BubbleShield_Bounce on flat ground: sin/cos of angle-$40 = (-$100, 0). */
    int16_t d2 = (p->status & S3K_STATUS_UNDERWATER) ? 0x400 : 0x780;
    p->y_vel = s16((uint16_t)(p->y_vel - d2));
    p->status |= S3K_STATUS_IN_AIR;
    p->status &= (uint8_t)~S3K_STATUS_PUSH;
    p->jumping = 1;
    p->y_radius = S3K_ROLL_Y_RADIUS;
    p->x_radius = S3K_ROLL_X_RADIUS;
    p->anim = S3K_ANIM_ROLL;
    p->status |= S3K_STATUS_ROLL;
    p->shield_anim = 2;
    play_sfx(p, S3K_SFX_BUBBLE_ATTACK);
}

static void player_touch_floor(S3KPlayer *p)
{
    p->y_radius = S3K_DEFAULT_Y_RADIUS;
    p->x_radius = S3K_DEFAULT_X_RADIUS;
    if (p->status & S3K_STATUS_ROLL) {
        p->status &= (uint8_t)~S3K_STATUS_ROLL;
        p->anim = S3K_ANIM_WALK;
        /* y_pos adjustment by the radius difference is a centre-origin
         * detail; the host tracks the feet. */
    }
    p->status &= (uint8_t)~(S3K_STATUS_IN_AIR | S3K_STATUS_PUSH |
                            S3K_STATUS_ROLL_JUMP);
    p->jumping = 0;
    p->scroll_delay_counter = 0;
    if (p->double_jump_flag) {
        if ((p->status_secondary & S3K_STATUS2_BUBBLE) &&
            !(p->status_secondary & S3K_STATUS2_INVINCIBLE))
            bubble_shield_bounce(p);
        p->double_jump_flag = 0;
    }
}

static void player_touch_floor_check_spindash(S3KPlayer *p)
{
    if (!p->spin_dash_flag) p->anim = S3K_ANIM_WALK;
    player_touch_floor(p);
}

/* ----------------------------------------------------------- Sonic_Move -- */

/* sub_113F6: left held on the ground. */
static void move_left(S3KPlayer *p, uint16_t d6, uint16_t d5, uint16_t d4)
{
    uint16_t d0 = (uint16_t)p->ground_vel;

    if (d0 == 0 || (int16_t)d0 < 0) {
        if (!(p->status & S3K_STATUS_FACING_LEFT)) {
            p->status |= S3K_STATUS_FACING_LEFT;
            p->status &= (uint8_t)~S3K_STATUS_PUSH;
            p->prev_anim = 1;
        }
        {
            int16_t d1 = s16((uint16_t)(-(int)d6));
            d0 = (uint16_t)(d0 - d5);
            if (!((int16_t)d0 > d1)) {
                d0 = (uint16_t)(d0 + d5);
                if (!((int16_t)d0 <= d1)) d0 = (uint16_t)d1;
            }
        }
        p->ground_vel = (int16_t)d0;
        p->anim = S3K_ANIM_WALK;
        return;
    }

    /* loc_11430: turning around while moving right. */
    {
        uint16_t before = d0;
        d0 = (uint16_t)(d0 - d4);
        if (before < d4) d0 = (uint16_t)-0x80;   /* bcc fails: borrow */
    }
    p->ground_vel = (int16_t)d0;
    /* Retail bug: `move.b angle(a0),d0` overwrites the low byte of the new
     * inertia before the $400 compare, so the threshold is the high byte. */
    d0 = (uint16_t)((d0 & 0xFF00u) | ((0x00 + 0x20) & 0xC0));
    if ((int16_t)d0 < 0x400) return;
    play_sfx(p, S3K_SFX_SKID);
    p->anim = S3K_ANIM_SKID;
    p->status &= (uint8_t)~S3K_STATUS_FACING_LEFT;
    if (p->air_left >= 12) {
        p->dust_state = S3K_DUST_SKID;
        p->dust_timer = 0;
    }
}

/* sub_11482: right held on the ground. */
static void move_right(S3KPlayer *p, uint16_t d6, uint16_t d5, uint16_t d4)
{
    uint16_t d0 = (uint16_t)p->ground_vel;

    if ((int16_t)d0 >= 0) {
        if (p->status & S3K_STATUS_FACING_LEFT) {
            p->status &= (uint8_t)~S3K_STATUS_FACING_LEFT;
            p->status &= (uint8_t)~S3K_STATUS_PUSH;
            p->prev_anim = 1;
        }
        d0 = (uint16_t)(d0 + d5);
        if (!((int16_t)d0 < (int16_t)d6)) {
            d0 = (uint16_t)(d0 - d5);
            if (!((int16_t)d0 >= (int16_t)d6)) d0 = d6;
        }
        p->ground_vel = (int16_t)d0;
        p->anim = S3K_ANIM_WALK;
        return;
    }

    /* loc_114B6: turning around while moving left. */
    {
        uint32_t sum = (uint32_t)d0 + d4;
        d0 = (uint16_t)sum;
        if (sum > 0xFFFFu) d0 = 0x80;             /* bcc fails: carry */
    }
    p->ground_vel = (int16_t)d0;
    d0 = (uint16_t)((d0 & 0xFF00u) | ((0x00 + 0x20) & 0xC0));
    if ((int16_t)d0 > -0x400) return;
    play_sfx(p, S3K_SFX_SKID);
    p->anim = S3K_ANIM_SKID;
    p->status |= S3K_STATUS_FACING_LEFT;
    if (p->air_left >= 12) {
        p->dust_state = S3K_DUST_SKID;
        p->dust_timer = 0;
    }
}

/* Sonic_Balance for a static (level) edge. Returns 1 when a balance
 * animation was chosen (branches to loc_112EA). */
static int sonic_balance(S3KPlayer *p, const S3KPlayerEnvironment *probe)
{
    if (!probe || probe->floor_center) return 0;
    if (!probe->floor_right) {            /* next_tilt == 3 */
        p->status &= (uint8_t)~S3K_STATUS_FACING_LEFT;
        p->anim = S3K_ANIM_BALANCE;
        if (!probe->floor_center_left6) p->anim = S3K_ANIM_BALANCE2;
        return 1;
    }
    if (!probe->floor_left) {             /* tilt == 3 */
        p->status |= S3K_STATUS_FACING_LEFT;
        p->anim = S3K_ANIM_BALANCE;
        if (!probe->floor_center_right6) p->anim = S3K_ANIM_BALANCE2;
        return 1;
    }
    return 0;
}

static void ground_friction(S3KPlayer *p, uint16_t d5)
{
    uint16_t d0 = (uint16_t)p->ground_vel;
    if (d0 == 0) return;
    if ((int16_t)d0 < 0) {
        uint32_t sum = (uint32_t)d0 + d5;
        d0 = sum > 0xFFFFu ? 0 : (uint16_t)sum;
    } else {
        d0 = d0 < d5 ? 0 : (uint16_t)(d0 - d5);
    }
    p->ground_vel = (int16_t)d0;
}

static void sonic_move(S3KPlayer *p, uint8_t held,
                       const S3KPlayerEnvironment *probe)
{
    uint16_t d6 = (uint16_t)p->max_speed;
    uint16_t d5 = (uint16_t)p->acceleration;
    uint16_t d4 = (uint16_t)p->deceleration;
    int keep_scroll_counter = 0;

    if (p->move_lock == 0) {
        if (held & S3K_BTN_LEFT) move_left(p, d6, d5, d4);
        if (held & S3K_BTN_RIGHT) move_right(p, d6, d5, d4);

        /* Flat ground: the slope test never branches. */
        if (p->ground_vel == 0) {
            p->status &= (uint8_t)~S3K_STATUS_PUSH;
            p->anim = S3K_ANIM_WAIT;
            if (!sonic_balance(p, probe)) {
                /* loc_11276 */
                if (held & S3K_BTN_DOWN) {
                    p->anim = S3K_ANIM_DUCK;
                    p->scroll_delay_counter++;
                    if (p->scroll_delay_counter >= 120)
                        p->scroll_delay_counter = 120;
                    keep_scroll_counter = 1;
                } else if (held & S3K_BTN_UP) {
                    p->anim = S3K_ANIM_LOOK_UP;
                    p->scroll_delay_counter++;
                    if (p->scroll_delay_counter >= 120)
                        p->scroll_delay_counter = 120;
                    keep_scroll_counter = 1;
                }
            }
        }
    }
    if (!keep_scroll_counter) p->scroll_delay_counter = 0;

    /* loc_11306: friction only when neither left nor right is held. */
    if (!(held & (S3K_BTN_LEFT | S3K_BTN_RIGHT)))
        ground_friction(p, d5);

    /* loc_11332 on flat ground: cos(0)=$100, sin(0)=0. */
    p->x_vel = p->ground_vel;
    p->y_vel = 0;
}

/* ------------------------------------------------------- SonicKnux_Roll -- */

static void sonic_roll(S3KPlayer *p, uint8_t held)
{
    uint16_t d0;

    if (held & (S3K_BTN_LEFT | S3K_BTN_RIGHT)) return;
    if (!(held & S3K_BTN_DOWN)) {
        if (p->anim == S3K_ANIM_DUCK) p->anim = S3K_ANIM_WALK;
        return;
    }
    d0 = (uint16_t)p->ground_vel;
    if ((int16_t)d0 < 0) d0 = (uint16_t)-(int)d0;
    if (d0 >= 0x100) {
        if (p->status & S3K_STATUS_ROLL) return;
        p->status |= S3K_STATUS_ROLL;
        p->y_radius = S3K_ROLL_Y_RADIUS;
        p->x_radius = S3K_ROLL_X_RADIUS;
        p->anim = S3K_ANIM_ROLL;
        play_sfx(p, S3K_SFX_ROLL);
        if (p->ground_vel == 0) p->ground_vel = 0x200;
        return;
    }
    if (p->status & S3K_STATUS_ON_OBJ) return;
    p->anim = S3K_ANIM_DUCK;
}

/* ------------------------------------------------------ Sonic_RollSpeed -- */

static void sonic_roll_speed(S3KPlayer *p, uint8_t held)
{
    uint16_t d5 = (uint16_t)(s16((uint16_t)p->acceleration) >> 1);
    const uint16_t d4 = 0x20;
    uint16_t d0;
    int16_t d1;

    if (!((int8_t)p->spin_dash_flag < 0)) {
        if (p->move_lock == 0) {
            if (held & S3K_BTN_LEFT) {
                /* sub_11608 */
                d0 = (uint16_t)p->ground_vel;
                if (d0 == 0 || (int16_t)d0 < 0) {
                    p->status |= S3K_STATUS_FACING_LEFT;
                    p->anim = S3K_ANIM_ROLL;
                } else {
                    uint16_t before = d0;
                    d0 = (uint16_t)(d0 - d4);
                    if (before < d4) d0 = (uint16_t)-0x80;
                    p->ground_vel = (int16_t)d0;
                }
            }
            if (held & S3K_BTN_RIGHT) {
                /* sub_1162C */
                d0 = (uint16_t)p->ground_vel;
                if ((int16_t)d0 >= 0) {
                    p->status &= (uint8_t)~S3K_STATUS_FACING_LEFT;
                    p->anim = S3K_ANIM_ROLL;
                } else {
                    uint32_t sum = (uint32_t)d0 + d4;
                    d0 = sum > 0xFFFFu ? 0x80 : (uint16_t)sum;
                    p->ground_vel = (int16_t)d0;
                }
            }
        }

        /* loc_1154E: rolling friction is always applied. */
        ground_friction(p, d5);

        d0 = (uint16_t)p->ground_vel;
        if ((int16_t)d0 < 0) d0 = (uint16_t)-(int)d0;
        if (d0 < 0x80) {
            if (!p->spin_dash_flag) {
                p->status &= (uint8_t)~S3K_STATUS_ROLL;
                p->y_radius = S3K_DEFAULT_Y_RADIUS;
                p->x_radius = S3K_DEFAULT_X_RADIUS;
                p->anim = S3K_ANIM_WAIT;
            } else {
                p->ground_vel = 0x400;
                if (p->status & S3K_STATUS_FACING_LEFT)
                    p->ground_vel = -0x400;
            }
        }
    }

    /* loc_115D2: x_vel clamps to +-$1000, ground_vel does not. */
    p->y_vel = 0;
    d1 = p->ground_vel;
    if (d1 > 0x1000) d1 = 0x1000;
    if (d1 < -0x1000) d1 = -0x1000;
    p->x_vel = d1;
}

/* ----------------------------------------------------------- Sonic_Jump -- */

/* Returns 1 when the jump started (addq.l #4,sp skips the rest of the mode). */
static int sonic_jump(S3KPlayer *p, uint8_t pressed,
                      const S3KPlayerEnvironment *env)
{
    int16_t d2;

    if (!(pressed & S3K_BTN_ABC)) return 0;
    if (env && !env->room_overhead) return 0;

    d2 = 0x680;
    if (p->status & S3K_STATUS_UNDERWATER) d2 = 0x380;
    /* sin/cos of angle-$40 on flat ground: x += 0, y += -d2. */
    p->y_vel = s16((uint16_t)(p->y_vel - d2));
    p->status |= S3K_STATUS_IN_AIR;
    p->status &= (uint8_t)~S3K_STATUS_PUSH;
    p->jumping = 1;
    p->launched_jump = 1;
    play_sfx(p, S3K_SFX_JUMP);
    p->y_radius = S3K_DEFAULT_Y_RADIUS;
    p->x_radius = S3K_DEFAULT_X_RADIUS;
    if (p->status & S3K_STATUS_ROLL) {
        p->status |= S3K_STATUS_ROLL_JUMP;
    } else {
        p->y_radius = S3K_ROLL_Y_RADIUS;
        p->x_radius = S3K_ROLL_X_RADIUS;
        p->anim = S3K_ANIM_ROLL;
        p->status |= S3K_STATUS_ROLL;
    }
    return 1;
}

/* ------------------------------------------------------ Sonic_ShieldMoves */

static void sonic_shield_moves(S3KPlayer *p, uint8_t pressed)
{
    if (p->double_jump_flag) return;
    if (!(pressed & S3K_BTN_ABC)) return;
    p->status &= (uint8_t)~S3K_STATUS_ROLL_JUMP;

    /* Sonic_FireShield. S3K refuses every shield move while invincible
     * (btst #Status_Invincible); SMB1's Starman keeps them, so the Fire
     * Shield dash and the Insta-Shield still work under the stars. */
    if (p->status_secondary & S3K_STATUS2_FIRE) {
        int16_t d0 = 0x800;
        p->shield_anim = 1;
        p->double_jump_flag = 1;
        if (p->status & S3K_STATUS_FACING_LEFT) d0 = -0x800;
        p->x_vel = d0;
        p->ground_vel = d0;
        p->y_vel = 0;
        p->h_scroll_frame_offset = 0x2000;
        play_sfx(p, S3K_SFX_FIRE_ATTACK);
        return;
    }
    if (p->status_secondary & S3K_STATUS2_LIGHTNING) {
        p->shield_anim = 1;
        p->double_jump_flag = 1;
        p->y_vel = -0x580;
        p->jumping = 0;
        play_sfx(p, S3K_SFX_ELECTRIC_ATTACK);
        return;
    }
    if (p->status_secondary & S3K_STATUS2_BUBBLE) {
        p->shield_anim = 1;
        p->double_jump_flag = 1;
        p->x_vel = 0;
        p->ground_vel = 0;
        p->y_vel = 0x800;
        play_sfx(p, S3K_SFX_BUBBLE_ATTACK);
        return;
    }
    /* Sonic_CheckTransform needs seven emeralds; SMB1 has none. */
    /* Sonic_InstaShield. S3K refuses it under the standard shield (btst
     * #Status_Shield); SMB1's Mushroom shield keeps it, because the
     * Insta-Shield is also Sonic's way to hit blocks. */
    p->shield_anim = 1;
    p->double_jump_flag = 1;
    play_sfx(p, S3K_SFX_INSTA_ATTACK);
}

/* ------------------------------------------------------ Sonic_JumpHeight -- */

static void sonic_jump_height(S3KPlayer *p, uint8_t held, uint8_t pressed)
{
    int16_t d1;

    if (!p->jumping) {
        /* Sonic_UpVelCap */
        if (!p->spin_dash_flag && p->y_vel < -0xFC0) p->y_vel = -0xFC0;
        return;
    }
    d1 = (p->status & S3K_STATUS_UNDERWATER) ? -0x200 : -0x400;
    if (d1 <= p->y_vel) {
        sonic_shield_moves(p, pressed);
        return;
    }
    if (!(held & S3K_BTN_ABC)) p->y_vel = d1;
}

/* ------------------------------------------------------ Sonic_ChgJumpDir -- */

static void sonic_chg_jump_dir(S3KPlayer *p, uint8_t held)
{
    uint16_t d6 = (uint16_t)p->max_speed;
    uint16_t d5 = (uint16_t)(p->acceleration << 1);

    if (!(p->status & S3K_STATUS_ROLL_JUMP)) {
        uint16_t d0 = (uint16_t)p->x_vel;
        if (held & S3K_BTN_LEFT) {
            int16_t d1 = s16((uint16_t)(-(int)d6));
            p->status |= S3K_STATUS_FACING_LEFT;
            d0 = (uint16_t)(d0 - d5);
            if (!((int16_t)d0 > d1)) {
                d0 = (uint16_t)(d0 + d5);
                if (!((int16_t)d0 <= d1)) d0 = (uint16_t)d1;
            }
        }
        if (held & S3K_BTN_RIGHT) {
            p->status &= (uint8_t)~S3K_STATUS_FACING_LEFT;
            d0 = (uint16_t)(d0 + d5);
            if (!((int16_t)d0 < (int16_t)d6)) {
                d0 = (uint16_t)(d0 - d5);
                if (!((int16_t)d0 >= (int16_t)d6)) d0 = d6;
            }
        }
        p->x_vel = (int16_t)d0;
    }

    /* Sonic_JumpPeakDecelerate: `cmpi.w #-$400,y_vel / blo` is unsigned. */
    if ((uint16_t)p->y_vel < (uint16_t)-0x400) return;
    {
        uint16_t d0 = (uint16_t)p->x_vel;
        int16_t d1 = (int16_t)(s16(d0) >> 5);
        if (d1 == 0) return;
        if (d1 < 0) {
            uint16_t before = d0;
            d0 = (uint16_t)(d0 - (uint16_t)d1);
            if (!(before < (uint16_t)d1)) d0 = 0;   /* bcs keeps */
        } else {
            uint16_t before = d0;
            d0 = (uint16_t)(d0 - (uint16_t)d1);
            if (before < (uint16_t)d1) d0 = 0;      /* bcc keeps */
        }
        p->x_vel = (int16_t)d0;
    }
}

/* ---------------------------------------------------- SonicKnux_Spindash -- */

/* Returns 1 when the spindash code consumed the frame (no MoveSprite). */
static int sonic_spindash(S3KPlayer *p, uint8_t held, uint8_t pressed)
{
    if (!p->spin_dash_flag) {
        if (p->anim != S3K_ANIM_DUCK) return 0;
        if (!(pressed & S3K_BTN_ABC)) return 0;
        p->anim = S3K_ANIM_SPINDASH;
        play_sfx(p, S3K_SFX_SPINDASH);
        p->spin_dash_flag = 1;
        p->spin_dash_counter = 0;
        if (p->air_left >= 12) p->dust_state = S3K_DUST_SPINDASH;
        return 1;
    }

    if (!(held & S3K_BTN_DOWN)) {
        /* Release */
        uint8_t index;
        uint16_t d0;
        p->y_radius = S3K_ROLL_Y_RADIUS;
        p->x_radius = S3K_ROLL_X_RADIUS;
        p->anim = S3K_ANIM_ROLL;
        p->spin_dash_flag = 0;
        /* move.b spin_dash_counter(a0),d0 reads the counter's HIGH byte. */
        index = (uint8_t)(p->spin_dash_counter >> 8);
        if (index > 8) index = 8;
        p->ground_vel = (int16_t)k_spindash_speeds[index];
        d0 = (uint16_t)(p->ground_vel - 0x800);
        d0 = (uint16_t)(d0 + d0);
        d0 &= 0x1F00u;
        d0 = (uint16_t)(-(int)d0);
        d0 = (uint16_t)(d0 + 0x2000u);
        p->h_scroll_frame_offset = d0;
        if (p->status & S3K_STATUS_FACING_LEFT)
            p->ground_vel = (int16_t)-p->ground_vel;
        p->status |= S3K_STATUS_ROLL;
        p->dust_state = S3K_DUST_NONE;
        play_sfx(p, S3K_SFX_DASH);
        return 1;
    }

    /* loc_11D16: charging. */
    if (p->spin_dash_counter) {
        uint16_t d0 = (uint16_t)(p->spin_dash_counter >> 5);
        if (p->spin_dash_counter < d0) p->spin_dash_counter = 0;
        else p->spin_dash_counter = (uint16_t)(p->spin_dash_counter - d0);
    }
    if (pressed & S3K_BTN_ABC) {
        p->anim = S3K_ANIM_SPINDASH;
        p->prev_anim = 0;
        play_sfx(p, S3K_SFX_SPINDASH);
        p->spin_dash_counter = (uint16_t)(p->spin_dash_counter + 0x200);
        if (p->spin_dash_counter >= 0x800) p->spin_dash_counter = 0x800;
    }
    return 1;
}

/* ------------------------------------------------------------ Control -- */

void s3k_player_control(S3KPlayer *p, uint8_t held, uint8_t pressed,
                        const S3KPlayerEnvironment *env,
                        int16_t *move_dx, int16_t *move_dy)
{
    int16_t dx = 0, dy = 0;
    uint8_t mode;

    p->launched_jump = 0;
    if (env) s3k_player_set_underwater(p, env->underwater);

    if (p->routine == S3K_ROUTINE_HURT) {
        /* loc_122D8: MoveSprite_TestGravity2 then +$30 (-$20 underwater). */
        dx = p->x_vel;
        dy = p->y_vel;
        p->y_vel = s16((uint16_t)(p->y_vel + 0x30));
        if (p->status & S3K_STATUS_UNDERWATER)
            p->y_vel = s16((uint16_t)(p->y_vel - 0x20));
        goto done;
    }
    if (p->routine == S3K_ROUTINE_DEATH) {
        /* loc_123AA: MoveSprite_TestGravity. */
        dx = p->x_vel;
        dy = p->y_vel;
        p->y_vel = s16((uint16_t)(p->y_vel + 0x38));
        goto done;
    }

    mode = p->status & (S3K_STATUS_IN_AIR | S3K_STATUS_ROLL);
    if (mode == 0) {
        /* Sonic_MdNormal */
        if (sonic_spindash(p, held, pressed)) goto done;
        if (sonic_jump(p, pressed, env)) goto done;
        sonic_move(p, held, env);
        sonic_roll(p, held);
        dx = p->x_vel;
        dy = p->y_vel;
    } else if (mode == S3K_STATUS_ROLL) {
        /* Sonic_MdRoll: a roll held by spin_dash_flag cannot jump, except
         * out of a host tunnel, which the jump leaves. */
        if ((!p->spin_dash_flag || (env && env->tunnel_jump)) &&
            sonic_jump(p, pressed, env)) {
            p->spin_dash_flag = 0;
            goto done;
        }
        sonic_roll_speed(p, held);
        dx = p->x_vel;
        dy = p->y_vel;
    } else {
        /* Sonic_MdAir / Sonic_MdJump */
        sonic_jump_height(p, held, pressed);
        sonic_chg_jump_dir(p, held);
        dx = p->x_vel;
        dy = p->y_vel;
        p->y_vel = s16((uint16_t)(p->y_vel + 0x38));
        if (p->status & S3K_STATUS_UNDERWATER)
            p->y_vel = s16((uint16_t)(p->y_vel - 0x28));
    }

done:
    if (move_dx) *move_dx = dx;
    if (move_dy) *move_dy = dy;
}

/* ------------------------------------------------------- Animate_Sonic -- */

static void animate_advance(S3KPlayer *p, const uint8_t *s, uint8_t len)
{
    /* loc_1265A */
    unsigned d1 = p->anim_frame;
    uint8_t d0 = script_byte(s, len, 1u + d1);

    if (d0 < 0xFC) {
        p->mapping_frame = d0;
        p->anim_frame++;
        return;
    }
    if (d0 == 0xFF) {
        p->anim_frame = 0;
        p->mapping_frame = script_byte(s, len, 1);
        p->anim_frame++;
        return;
    }
    if (d0 == 0xFE) {
        uint8_t back = script_byte(s, len, 2u + d1);
        p->anim_frame = (uint8_t)(p->anim_frame - back);
        d1 = (uint8_t)(d1 - back);
        p->mapping_frame = script_byte(s, len, 1u + d1);
        p->anim_frame++;
        return;
    }
    if (d0 == 0xFD) {
        p->anim = script_byte(s, len, 2u + d1);
        return;
    }
    /* $FC: no-op for the player */
}

static void animate_sonic(S3KPlayer *p)
{
    const uint8_t *s;
    uint8_t len;
    uint8_t d0;

    if (p->anim >= S3K_ANI_COUNT) p->anim = S3K_ANIM_WALK;
    if (p->anim != p->prev_anim) {
        p->prev_anim = p->anim;
        p->anim_frame = 0;
        p->anim_frame_timer = 0;
        p->status &= (uint8_t)~S3K_STATUS_PUSH;
    }
    s = k_ani_sonic[p->anim].data;
    len = k_ani_sonic[p->anim].len;
    d0 = s[0];

    if (!(d0 & 0x80)) {
        p->render_hflip = (uint8_t)(p->status & S3K_STATUS_FACING_LEFT);
        p->anim_frame_timer--;
        if (!(p->anim_frame_timer & 0x80)) return;
        p->anim_frame_timer = d0;
        animate_advance(p, s, len);
        return;
    }

    if (d0 == 0xFF) {
        /* Walk / run, flat ground and no tumbling. */
        uint16_t d2;
        uint8_t d3, frame;
        const uint8_t *ws;
        uint8_t wlen;

        p->render_hflip = (uint8_t)(p->status & S3K_STATUS_FACING_LEFT);
        if (p->status & S3K_STATUS_PUSH) goto push;

        d2 = (uint16_t)p->ground_vel;
        if ((int16_t)d2 < 0) d2 = (uint16_t)-(int)d2;
        if (d2 >= 0x600) {
            ws = k_ani01;
            wlen = sizeof(k_ani01);
        } else {
            ws = k_ani00;
            wlen = sizeof(k_ani00);
        }
        d3 = 0;  /* angle quadrant offset is 0 on flat ground */
        frame = script_byte(ws, wlen, 1u + p->anim_frame);
        if (frame == 0xFF) {
            p->anim_frame = 0;
            frame = script_byte(ws, wlen, 1);
        }
        p->mapping_frame = (uint8_t)(frame + d3);
        p->anim_frame_timer--;
        if (!(p->anim_frame_timer & 0x80)) return;
        {
            int32_t t = 0x800 - (int32_t)d2;
            if (t < 0) t = 0;
            p->anim_frame_timer = (uint8_t)((uint16_t)t >> 8);
        }
        p->anim_frame++;
        return;
    }

    /* loc_12A2A: rolling ($FE) -- and the unused $FD push script id. */
    p->render_hflip = (uint8_t)(p->status & S3K_STATUS_FACING_LEFT);
    p->anim_frame_timer--;
    if (!(p->anim_frame_timer & 0x80)) return;
    {
        uint16_t d2 = (uint16_t)p->ground_vel;
        int32_t t;
        if ((int16_t)d2 < 0) d2 = (uint16_t)-(int)d2;
        t = 0x400 - (int32_t)d2;
        if (t < 0) t = 0;
        p->anim_frame_timer = (uint8_t)((uint16_t)t >> 8);
    }
    animate_advance(p, k_ani02, sizeof(k_ani02));
    return;

push:
    /* loc_12A72 */
    p->anim_frame_timer--;
    if (!(p->anim_frame_timer & 0x80)) return;
    {
        int32_t d2 = p->ground_vel;
        int32_t t;
        if (d2 >= 0) d2 = -d2;
        t = d2 + 0x800;
        if (t < 0) t = 0;
        p->anim_frame_timer = (uint8_t)((uint16_t)t >> 6);
    }
    animate_advance(p, k_ani04, sizeof(k_ani04));
}

/* Animate_Sprite for the shield object. */
static void animate_shield_script(S3KPlayer *p, const uint8_t *s, uint8_t len)
{
    unsigned d1;
    uint8_t d0;

    if (p->shield_anim != p->shield_prev_anim) {
        p->shield_prev_anim = p->shield_anim;
        p->shield_anim_frame = 0;
        p->shield_anim_timer = 0;
    }
    if (p->shield_anim_timer != 0) {
        p->shield_anim_timer--;
        return;
    }
    p->shield_anim_timer = s[0];
    d1 = p->shield_anim_frame;
    d0 = script_byte(s, len, 1u + d1);
    if (d0 & 0x80) {
        if (d0 == 0xFF) {
            p->shield_anim_frame = 0;
            d0 = script_byte(s, len, 1);
        } else if (d0 == 0xFE) {
            uint8_t back = script_byte(s, len, 2u + d1);
            p->shield_anim_frame = (uint8_t)(p->shield_anim_frame - back);
            d1 = (uint8_t)(d1 - back);
            d0 = script_byte(s, len, 1u + d1);
        } else if (d0 == 0xFD) {
            p->shield_anim = script_byte(s, len, 2u + d1);
            return;
        } else {
            return;
        }
    }
    p->shield_mapping_frame = d0;
    p->shield_hflip = p->shield_facing;
    p->shield_anim_frame++;
}

static void run_shield_object(S3KPlayer *p)
{
    /* Every shield object hides and holds still while its player is
     * invincible. A shield move started under the stars (see
     * sonic_shield_moves) still plays its attack animation, which is what
     * ends the Insta-Shield, before the shield hides again. */
    if ((p->status_secondary & S3K_STATUS2_INVINCIBLE) && p->shield_anim != 1)
        return;
    if (p->status_secondary & S3K_STATUS2_FIRE) {
        /* Obj_FireShield_Main: while the dash anim plays, the shield keeps
         * the orientation it had when the dash began. */
        if (p->shield_anim == 0)
            p->shield_facing = (uint8_t)(p->status & S3K_STATUS_FACING_LEFT);
        if (p->shield_anim == 0)
            animate_shield_script(p, k_fire0, sizeof(k_fire0));
        else
            animate_shield_script(p, k_fire1, sizeof(k_fire1));
        return;
    }
    if (p->status_secondary & S3K_STATUS2_ELEMENTAL) return;
    if (p->status_secondary & S3K_STATUS2_SHIELD) {
        /* Obj_S2Shield_Main: inherits status every frame, one animation.
         * An Insta-Shield started under it (anim 1) plays Ani_InstaShield's
         * attack first, and the shield resumes on the frame that ends it. */
        p->shield_facing = (uint8_t)(p->status & S3K_STATUS_FACING_LEFT);
        if (p->shield_anim == 1) {
            animate_shield_script(p, k_insta1, sizeof(k_insta1));
            if (p->shield_mapping_frame == 7 && p->double_jump_flag)
                p->double_jump_flag = 2;
            if (p->shield_anim == 1) return;
        }
        p->shield_anim = 0;
        animate_shield_script(p, k_s2shield, sizeof(k_s2shield));
        return;
    }

    /* Obj_InstaShield_Main inherits the orientation every frame. */
    p->shield_facing = (uint8_t)(p->status & S3K_STATUS_FACING_LEFT);
    if (p->shield_anim == 0)
        animate_shield_script(p, k_insta0, sizeof(k_insta0));
    else
        animate_shield_script(p, k_insta1, sizeof(k_insta1));
    if (p->shield_mapping_frame == 7 && p->double_jump_flag)
        p->double_jump_flag = 2;
}

/* --------------------------------------------------------- Display ----- */

static void sonic_display_timers(S3KPlayer *p)
{
    const uint8_t t = p->invulnerability_timer;

    /* move.b invulnerability_timer,d0 / subq / lsr.b #3,d0 / bcc skip:
     * the sprite is drawn only when bit 2 of the pre-decrement timer is set. */
    p->display_hidden = (uint8_t)(t != 0 && !(t & 0x04));
    if (t) p->invulnerability_timer--;

    if ((p->status_secondary & S3K_STATUS2_INVINCIBLE) &&
        p->invincibility_timer && (p->level_frame_counter & 7) == 0) {
        if (--p->invincibility_timer == 0)
            p->status_secondary &= (uint8_t)~S3K_STATUS2_INVINCIBLE;
    }
    if ((p->status_secondary & S3K_STATUS2_SPEED_SHOES) &&
        p->speed_shoes_timer && (p->level_frame_counter & 7) == 0) {
        if (--p->speed_shoes_timer == 0) {
            p->status_secondary &= (uint8_t)~S3K_STATUS2_SPEED_SHOES;
            set_normal_speeds(p);
        }
    }
}

static void run_dust_object(S3KPlayer *p)
{
    if (p->dust_state == S3K_DUST_SKID) {
        /* Obj_DashDust routine 6 spawns a puff every 4 frames while the
         * player keeps the skid animation. */
        if (p->anim != S3K_ANIM_SKID) {
            p->dust_state = S3K_DUST_NONE;
            return;
        }
        p->dust_timer++;
    } else if (p->dust_state == S3K_DUST_SPINDASH) {
        if (!p->spin_dash_flag) p->dust_state = S3K_DUST_NONE;
        else p->dust_timer++;
    }
}

/* ----------------------------------------------------------- Reconcile -- */

void s3k_player_reconcile(S3KPlayer *p, const S3KPlayerCollision *hit,
                          uint8_t held)
{
    static const S3KPlayerCollision k_none = { 1, 0, 0, 0, 0, 0, 0 };
    const uint8_t routine = p->routine;
    (void)held;
    if (!hit) hit = &k_none;

    p->level_frame_counter++;

    if (routine != S3K_ROUTINE_DEATH) {
        if (hit->has_imposed_y_vel) {
            if ((p->status & S3K_STATUS_IN_AIR) && p->y_vel < 0 &&
                hit->imposed_y_vel >= 0) {
                /* A host block bump is a ceiling (Player_HitCeiling). */
                p->y_vel = 0;
            } else if (hit->imposed_y_vel < 0) {
                /* Obj_Spring sub_22F98 (up spring): y_vel, InAir, clear
                 * OnObj/jumping/spindash, anim $10, routine 2, sfx_Spring.
                 * Roll and x_vel are left as they were. */
                p->y_vel = hit->imposed_y_vel;
                p->status |= S3K_STATUS_IN_AIR;
                p->status &= (uint8_t)~S3K_STATUS_ON_OBJ;
                p->jumping = 0;
                p->spin_dash_flag = 0;
                if (hit->spring) {
                    p->anim = S3K_ANIM_SPRING;
                    p->routine = S3K_ROUTINE_CONTROL;
                    play_sfx(p, S3K_SFX_SPRING);
                }
            }
        }

        if (!(p->status & S3K_STATUS_IN_AIR)) {
            /* Ground frame: the wall check at the end of Sonic_Move and
             * Sonic_RollSpeed (loc_11350), then Player_AnglePos. Spindash
             * charge frames never reach MoveSprite, so they never push; a
             * roll kept going by spin_dash_flag (a tunnel) still does. */
            if (hit->hit_wall && p->ground_vel != 0 &&
                !(p->spin_dash_flag && !(p->status & S3K_STATUS_ROLL))) {
                if (p->ground_vel > 0) {
                    if (!(p->status & S3K_STATUS_FACING_LEFT))
                        p->status |= S3K_STATUS_PUSH;
                } else {
                    if (p->status & S3K_STATUS_FACING_LEFT)
                        p->status |= S3K_STATUS_PUSH;
                }
                p->ground_vel = 0;
                p->x_vel = 0;
            }
            if (!hit->on_ground) {
                p->status |= S3K_STATUS_IN_AIR;
                p->status &= (uint8_t)~S3K_STATUS_PUSH;
                p->prev_anim = 1;
            }
        } else {
            /* SonicKnux_DoLevelCollision on a flat level. */
            if (hit->hit_wall) p->x_vel = 0;
            if (hit->hit_ceiling && p->y_vel < 0) p->y_vel = 0;
            if (hit->on_ground && p->y_vel >= 0) {
                p->y_vel = 0;
                p->ground_vel = p->x_vel;
                player_touch_floor_check_spindash(p);
                if (routine == S3K_ROUTINE_HURT) {
                    /* sub_12318: landing ends the hurt bounce. */
                    p->y_vel = 0;
                    p->x_vel = 0;
                    p->ground_vel = 0;
                    p->anim = S3K_ANIM_WALK;
                    p->routine = S3K_ROUTINE_CONTROL;
                    p->invulnerability_timer = 2 * 60;
                    p->spin_dash_flag = 0;
                }
            }
        }
    }

    /* Sonic_Display runs only from the control routine; the hurt and death
     * routines call Draw_Sprite unconditionally (sub_125E0). */
    if (routine == S3K_ROUTINE_CONTROL) sonic_display_timers(p);
    else p->display_hidden = 0;
    animate_sonic(p);
    /* The shield and dust are separate objects that run every frame. */
    run_shield_object(p);
    run_dust_object(p);
}

/* -------------------------------------------------------------- Water -- */

int s3k_player_set_underwater(S3KPlayer *p, int underwater)
{
    if (underwater) {
        /* Sonic_InWater */
        if (p->status & S3K_STATUS_UNDERWATER) return 0;
        p->status |= S3K_STATUS_UNDERWATER;
        set_normal_speeds(p);
        /* Obj_FireShield / Obj_LightningShield destroy themselves in water
         * (andi.b #$8E,status_secondary). */
        if (p->status_secondary & (S3K_STATUS2_FIRE | S3K_STATUS2_LIGHTNING))
            p->status_secondary &= (uint8_t)0x8E;
        p->x_vel = (int16_t)(p->x_vel >> 1);
        p->y_vel = (int16_t)(p->y_vel >> 2);
        if (p->y_vel == 0) return 0;
        play_sfx(p, S3K_SFX_SPLASH);
        return 1;
    }
    /* Sonic_OutWater */
    if (!(p->status & S3K_STATUS_UNDERWATER)) return 0;
    p->status &= (uint8_t)~S3K_STATUS_UNDERWATER;
    set_normal_speeds(p);
    if (p->routine != S3K_ROUTINE_HURT && p->y_vel >= -0x400)
        p->y_vel = (int16_t)(p->y_vel * 2);
    if (p->y_vel == 0) return 0;
    if (p->y_vel <= -0x1000) p->y_vel = -0x1000;
    play_sfx(p, S3K_SFX_SPLASH);
    return 1;
}

/* ------------------------------------------------------ Hurt and death -- */

void s3k_player_hurt(S3KPlayer *p, int from_left, int spike)
{
    if (p->status_secondary & S3K_STATUS2_SHIELD)
        p->status_secondary &= (uint8_t)0x8E;
    p->routine = S3K_ROUTINE_HURT;
    player_touch_floor(p);
    p->status |= S3K_STATUS_IN_AIR;
    p->y_vel = -0x400;
    p->x_vel = -0x200;
    if (p->status & S3K_STATUS_UNDERWATER) {
        p->y_vel = -0x200;
        p->x_vel = -0x100;
    }
    if (from_left) p->x_vel = (int16_t)-p->x_vel;
    p->ground_vel = 0;
    p->anim = S3K_ANIM_HURT;
    p->invulnerability_timer = 120;
    p->spin_dash_flag = 0;
    p->double_jump_flag = 0;
    play_sfx(p, spike ? S3K_SFX_SPIKE_HIT : S3K_SFX_DEATH);
}

void s3k_player_kill(S3KPlayer *p)
{
    p->status_secondary = 0;
    p->routine = S3K_ROUTINE_DEATH;
    player_touch_floor(p);
    p->status |= S3K_STATUS_IN_AIR;
    p->y_vel = -0x700;
    p->x_vel = 0;
    p->ground_vel = 0;
    p->anim = S3K_ANIM_DEATH;
    p->spin_dash_flag = 0;
    play_sfx(p, S3K_SFX_DEATH);
}

void s3k_player_enemy_bounce(S3KPlayer *p, int player_below)
{
    /* Touch_EnemyNormal */
    if (p->y_vel < 0) {
        p->y_vel = s16((uint16_t)(p->y_vel + 0x100));
    } else if (player_below) {
        p->y_vel = s16((uint16_t)(p->y_vel - 0x100));
    } else {
        p->y_vel = (int16_t)-p->y_vel;
    }
}

void s3k_player_curl(S3KPlayer *p)
{
    p->status |= S3K_STATUS_ROLL;
    p->y_radius = S3K_ROLL_Y_RADIUS;
    p->x_radius = S3K_ROLL_X_RADIUS;
    p->anim = S3K_ANIM_ROLL;
}

void s3k_player_set_shield(S3KPlayer *p, uint8_t shield_bits)
{
    uint8_t want = shield_bits & (S3K_STATUS2_SHIELD | S3K_STATUS2_ELEMENTAL);
    /* Every shield monitor sets Status_Shield; elementals add their own bit. */
    if (want & S3K_STATUS2_ELEMENTAL) want |= S3K_STATUS2_SHIELD;
    if ((p->status & S3K_STATUS_UNDERWATER) &&
        (want & (S3K_STATUS2_FIRE | S3K_STATUS2_LIGHTNING)))
        want = 0;
    if ((p->status_secondary & (S3K_STATUS2_SHIELD | S3K_STATUS2_ELEMENTAL)) ==
        want)
        return;
    p->status_secondary &= (uint8_t)0x8E;
    p->status_secondary |= want;
    /* A new shield object (or Obj_FireShield_Destroy's Insta-Shield)
     * starts with anim 0 / prev_anim 1. */
    p->shield_anim = 0;
    p->shield_prev_anim = 1;
    p->shield_anim_frame = 0;
    p->shield_anim_timer = 0;
}

void s3k_player_set_invincible(S3KPlayer *p, int invincible)
{
    if (invincible) p->status_secondary |= S3K_STATUS2_INVINCIBLE;
    else p->status_secondary &= (uint8_t)~S3K_STATUS2_INVINCIBLE;
    p->invincibility_timer = 0;
}

/* ---------------------------------------------------------- Predicates -- */

int s3k_player_touch_attacking(const S3KPlayer *p)
{
    return p->anim == S3K_ANIM_ROLL || p->anim == S3K_ANIM_SPINDASH;
}

int s3k_player_insta_shield_active(const S3KPlayer *p)
{
    /* TouchResponse's andi.b #$73: no invincibility or elemental shield.
     * The standard shield and invincibility bits are ignored, since here
     * both can carry an Insta-Shield. */
    return !(p->status_secondary & S3K_STATUS2_ELEMENTAL) &&
           p->double_jump_flag == 1;
}

int s3k_player_invincible(const S3KPlayer *p)
{
    return (p->status_secondary & S3K_STATUS2_INVINCIBLE) != 0;
}

int s3k_player_is_ball(const S3KPlayer *p)
{
    return (p->status & S3K_STATUS_ROLL) != 0 || p->spin_dash_flag != 0;
}

void s3k_player_touch_box(const S3KPlayer *p, int *left, int *top,
                          int *width, int *height)
{
    if (s3k_player_insta_shield_active(p)) {
        *left = -0x18;
        *top = -0x18;
        *width = 0x30;
        *height = 0x30;
        return;
    }
    {
        int half_h = (int)p->y_radius - 3;
        *left = -8;
        *top = -half_h;
        *width = 0x10;
        *height = half_h * 2;
    }
}

int s3k_player_take_sfx(S3KPlayer *p, uint8_t *out, int cap)
{
    int n = p->sfx_count;
    if (n > cap) n = cap;
    if (out && n > 0) memcpy(out, p->sfx, (size_t)n);
    p->sfx_count = 0;
    return n;
}
