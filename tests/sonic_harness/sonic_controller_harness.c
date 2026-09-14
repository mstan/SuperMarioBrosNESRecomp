/*
 * S3K Sonic core harness.
 *
 * Every expected value below is derived by hand from sonic3k.asm, not read
 * back from the implementation: frame counts come from Max_speed $600 /
 * Acceleration $C, the jump from $680 and gravity $38, the spindash from
 * word_11CF2 with SonicKnux_Spindash's counter decay, and so on. A small host
 * simulation provides a flat floor at y = 0 (positions in 16.8, +Y down) so
 * the ForeignController ABI is exercised the way the SMB adapter drives it.
 */
#include "../../mods/s3k/sonic_controller.h"
#include "../../mods/s3k/s3k_player.h"

#include "foreign_controller.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int failures;

#define EXPECT(cond, ...) do { \
    if (!(cond)) { \
        fprintf(stderr, "FAIL %s:%d: ", __FILE__, __LINE__); \
        fprintf(stderr, __VA_ARGS__); \
        fputc('\n', stderr); \
        failures++; \
    } \
} while (0)

/* Host simulation: world position in 16.8 fixed point, feet at y. */
static int32_t host_x, host_y;
static int32_t wall_x = 0x7FFFFFFF;   /* right wall, 16.8 */

enum { PAD_A = 1, PAD_B = 2, PAD_L = 4, PAD_R = 8, PAD_U = 16, PAD_D = 32 };
static int prev_pad;
/* The host reports its roll as a tunnel a jump may leave. */
static int env_tunnel_jump;

static void reset_sonic(void)
{
    EXPECT(nes_foreign_select(S3K_SONIC_CONTROLLER_ID), "select");
    nes_foreign_set_ownership(FOREIGN_OWNERSHIP_FOREIGN);
    host_x = 0;
    host_y = 0;
    wall_x = 0x7FFFFFFF;
    prev_pad = 0;
    env_tunnel_jump = 0;
}

/* One full S3K frame: tick (control), host move + collide, resolve. */
static void frame(int pad)
{
    ForeignInput in;
    ForeignMoveResult out;
    ForeignCollisionResult hit;
    S3KPlayerEnvironment env;
    const S3KPlayer *p;
    int32_t dx, dy, nx;
    int was_air;
    int jump_bits = PAD_A | PAD_B;

    memset(&env, 0, sizeof(env));
    env.room_overhead = 1;
    env.floor_center = env.floor_left = env.floor_right = 1;
    env.floor_center_left6 = env.floor_center_right6 = 1;
    env.tunnel_jump = (uint8_t)env_tunnel_jump;
    s3k_sonic_set_environment(&env);

    memset(&in, 0, sizeof(in));
    in.stick_x = (float)(((pad & PAD_R) ? 1 : 0) - ((pad & PAD_L) ? 1 : 0));
    in.stick_y = (float)(((pad & PAD_U) ? 1 : 0) - ((pad & PAD_D) ? 1 : 0));
    in.jump_held = (pad & jump_bits) != 0;
    in.jump_pressed = ((pad & ~prev_pad) & jump_bits) != 0;
    prev_pad = pad;

    was_air = (s3k_sonic_player()->status & S3K_STATUS_IN_AIR) != 0;
    memset(&out, 0, sizeof(out));
    nes_foreign_tick(0, &in, &out);

    dx = s3k_sonic_move_dx();
    dy = s3k_sonic_move_dy();
    memset(&hit, 0, sizeof(hit));
    nx = host_x + dx;
    if (nx > wall_x) {
        nx = wall_x;
        hit.hit_wall = 1;
    }
    host_x = nx;
    p = s3k_sonic_player();
    if ((p->status & S3K_STATUS_IN_AIR) || was_air) {
        host_y += dy;
        if (host_y >= 0 && !s3k_sonic_launched_jump()) {
            host_y = 0;
            hit.grounded = 1;
        } else {
            hit.grounded = 0;
        }
    } else {
        hit.grounded = 1;
    }
    nes_foreign_resolve(&hit);
}

static int sfx_seen(const uint8_t *ids, int n, uint8_t id)
{
    for (int i = 0; i < n; ++i) if (ids[i] == id) return 1;
    return 0;
}

static void test_ground_acceleration(void)
{
    const S3KPlayer *p;
    reset_sonic();
    for (int i = 1; i <= 127; ++i) frame(PAD_R);
    p = s3k_sonic_player();
    EXPECT(p->ground_vel == 127 * 0xC, "127 frames of $C accel: got %d", p->ground_vel);
    frame(PAD_R);
    EXPECT(p->ground_vel == 0x600, "frame 128 reaches Max_speed $600: %d", p->ground_vel);
    frame(PAD_R);
    EXPECT(p->ground_vel == 0x600, "Max_speed holds");
    EXPECT(p->anim == S3K_ANIM_WALK, "walk anim id at speed");
    EXPECT(p->mapping_frame >= 0x21 && p->mapping_frame <= 0x24,
           "run frames $21-$24 at $600: %02X", p->mapping_frame);

    /* Friction: Acceleration per frame with no direction held. */
    frame(0);
    EXPECT(p->ground_vel == 0x600 - 0xC, "friction $C: %d", p->ground_vel);
    for (int i = 0; i < 126; ++i) frame(0);
    EXPECT(p->ground_vel == 0xC, "friction stepping: %d", p->ground_vel);
    frame(0);
    EXPECT(p->ground_vel == 0, "friction stops at zero");
}

static void test_skid_asymmetry(void)
{
    const S3KPlayer *p;
    uint8_t ids[8];
    int n;

    /* Moving right at $600, press left: $580,$500,$480,$400 skid; $380 not. */
    reset_sonic();
    for (int i = 0; i < 130; ++i) frame(PAD_R);
    p = s3k_sonic_player();
    s3k_sonic_take_sfx(ids, 8);
    frame(PAD_L);
    n = s3k_sonic_take_sfx(ids, 8);
    EXPECT(p->ground_vel == 0x580, "decel $80: %X", p->ground_vel);
    EXPECT(sfx_seen(ids, n, S3K_SFX_SKID), "skid sfx at $580");
    EXPECT(!(p->status & S3K_STATUS_FACING_LEFT), "skid faces motion (right)");
    frame(PAD_L); frame(PAD_L);
    s3k_sonic_take_sfx(ids, 8);
    frame(PAD_L);
    n = s3k_sonic_take_sfx(ids, 8);
    EXPECT(p->ground_vel == 0x400 && sfx_seen(ids, n, S3K_SFX_SKID),
           "$400 still skids moving right");
    frame(PAD_L);
    n = s3k_sonic_take_sfx(ids, 8);
    EXPECT(p->ground_vel == 0x380 && !sfx_seen(ids, n, S3K_SFX_SKID),
           "$380 does not skid moving right");

    /* Moving left: the retail high-byte bug skids at -$380 too. */
    reset_sonic();
    for (int i = 0; i < 130; ++i) frame(PAD_L);
    for (int i = 0; i < 4; ++i) frame(PAD_R);
    s3k_sonic_take_sfx(ids, 8);
    frame(PAD_R);
    n = s3k_sonic_take_sfx(ids, 8);
    EXPECT(p->ground_vel == -0x380, "left decel to -$380: %d", p->ground_vel);
    EXPECT(sfx_seen(ids, n, S3K_SFX_SKID), "-$380 skids moving left (retail bug)");
    frame(PAD_R);
    n = s3k_sonic_take_sfx(ids, 8);
    EXPECT(p->ground_vel == -0x300 && !sfx_seen(ids, n, S3K_SFX_SKID),
           "-$300 no longer skids");
}

static void test_jump_arc(void)
{
    const S3KPlayer *p;
    int32_t peak = 0;
    int frames = 0;

    reset_sonic();
    frame(PAD_A);
    p = s3k_sonic_player();
    EXPECT(s3k_sonic_launched_jump(), "Sonic_Jump launches");
    EXPECT(p->y_vel == -0x680, "jump speed $680: %d", p->y_vel);
    EXPECT(host_y == 0, "jump frame skips MoveSprite");
    EXPECT(p->anim == S3K_ANIM_ROLL && (p->status & S3K_STATUS_ROLL),
           "jump curls into a ball");

    /* Held: y moves by -$680, -$648, ... Peak is the sum of the rising
     * velocities: $680 - k*$38 for k = 0..29 (the 30th is $680-$658 = $28). */
    while (frames < 200) {
        frame(PAD_A);
        frames++;
        if (host_y < peak) peak = host_y;
        if (!(p->status & S3K_STATUS_IN_AIR)) break;
    }
    {
        int32_t expect_peak = 0;
        for (int k = 0; k < 30; ++k) expect_peak -= 0x680 - k * 0x38;
        EXPECT(peak == expect_peak, "held jump apex %d, expected %d",
               peak, expect_peak);
    }
    EXPECT(!(p->status & S3K_STATUS_IN_AIR) &&
           !(p->status & S3K_STATUS_ROLL) && p->anim == S3K_ANIM_WALK,
           "landing uncurls into walk");

    /* Tap: release on the first airborne frame caps y_vel to -$400 before
     * MoveSprite. */
    reset_sonic();
    frame(PAD_A);
    frame(0);
    EXPECT(host_y == -0x400, "released jump moves -$400: %d", host_y);
    EXPECT(p->y_vel == -0x400 + 0x38, "gravity after the cap: %d", p->y_vel);
}

static void test_air_drag_and_control(void)
{
    const S3KPlayer *p;
    reset_sonic();
    for (int i = 0; i < 130; ++i) frame(PAD_R);
    frame(PAD_R | PAD_A);
    p = s3k_sonic_player();
    EXPECT(p->x_vel == 0x600, "jump keeps ground x_vel");
    /* Rise until y_vel enters [-$400, 0): drag x_vel -= x_vel >> 5. */
    while (p->y_vel < -0x400) frame(PAD_A);
    {
        int16_t before = p->x_vel;
        int16_t yv = p->y_vel;
        frame(PAD_A);
        EXPECT(yv >= -0x400 && yv < 0, "in drag window: %d", yv);
        EXPECT(p->x_vel == before - (before >> 5),
               "JumpPeakDecelerate: %d -> %d", before, p->x_vel);
    }
    /* Air acceleration is 2*Acceleration with a soft cap. */
    reset_sonic();
    frame(PAD_A);
    frame(PAD_A | PAD_R);
    EXPECT(p->x_vel == 0x18, "air accel $18: %d", p->x_vel);
}

static void test_spindash(void)
{
    const S3KPlayer *p;
    uint8_t ids[8];
    int n;

    reset_sonic();
    frame(PAD_D);
    p = s3k_sonic_player();
    EXPECT(p->anim == S3K_ANIM_DUCK, "down while still ducks");
    frame(PAD_D | PAD_A);
    n = s3k_sonic_take_sfx(ids, 8);
    EXPECT(p->spin_dash_flag == 1 && p->anim == S3K_ANIM_SPINDASH,
           "duck + A starts spindash");
    EXPECT(sfx_seen(ids, n, S3K_SFX_SPINDASH), "rev sfx");
    EXPECT(p->spin_dash_counter == 0, "starting press does not charge");

    /* Charge presses: counter -= counter>>5 every frame, +$200 per press. */
    frame(PAD_D);            /* 0 */
    frame(PAD_D | PAD_A);    /* 0 -> $200 */
    EXPECT(p->spin_dash_counter == 0x200, "first rev $200: %X", p->spin_dash_counter);
    frame(PAD_D);            /* $200 - $10 = $1F0 */
    EXPECT(p->spin_dash_counter == 0x1F0, "decay $10: %X", p->spin_dash_counter);
    frame(PAD_D | PAD_A);    /* $1F0 - $F = $1E1, + $200 = $3E1 */
    EXPECT(p->spin_dash_counter == 0x3E1, "rev 2: %X", p->spin_dash_counter);
    EXPECT(host_x == 0, "charging never moves");

    frame(0);                /* release: index = high byte 3 -> $980 */
    n = s3k_sonic_take_sfx(ids, 8);
    EXPECT(p->ground_vel == 0x980, "release speed word_11CF2[3]: %X", p->ground_vel);
    EXPECT((p->status & S3K_STATUS_ROLL) && p->anim == S3K_ANIM_ROLL,
           "release rolls");
    EXPECT(sfx_seen(ids, n, S3K_SFX_DASH), "dash sfx");
    EXPECT(host_x == 0, "release frame skips MoveSprite");
    frame(0);
    /* Sonic_RollSpeed: friction Acceleration>>1 = 6, x_vel = ground_vel. */
    EXPECT(p->ground_vel == 0x980 - 6 && host_x == 0x980 - 6,
           "roll friction 6: gv %X x %X", p->ground_vel, host_x);

    /* Maxed charge: three extra presses saturate at $800 -> $C00. */
    reset_sonic();
    frame(PAD_D);
    frame(PAD_D | PAD_A);
    for (int i = 0; i < 8; ++i) { frame(PAD_D | PAD_A); frame(PAD_D); }
    frame(PAD_D | PAD_A);
    EXPECT(p->spin_dash_counter == 0x800, "counter caps at $800: %X",
           p->spin_dash_counter);
    frame(0);
    EXPECT(p->ground_vel == 0xC00, "max spindash $C00: %X", p->ground_vel);
}

static void test_roll(void)
{
    const S3KPlayer *p;
    uint8_t ids[8];
    int n, frames = 0;

    reset_sonic();
    for (int i = 0; i < 64; ++i) frame(PAD_R);  /* gv = $300 */
    p = s3k_sonic_player();
    s3k_sonic_take_sfx(ids, 8);
    frame(PAD_D);
    n = s3k_sonic_take_sfx(ids, 8);
    EXPECT((p->status & S3K_STATUS_ROLL) && sfx_seen(ids, n, S3K_SFX_ROLL),
           "down at $300 rolls");
    /* Holding forward while rolling does not accelerate. */
    frame(PAD_R | PAD_D);
    EXPECT(p->ground_vel == 0x300 - 0xC - 6, "roll ignores forward: %X",
           p->ground_vel);
    while ((p->status & S3K_STATUS_ROLL) && frames < 400) {
        frame(PAD_D);
        frames++;
    }
    EXPECT(!(p->status & S3K_STATUS_ROLL) && p->anim == S3K_ANIM_WAIT,
           "roll ends below $80");
}

static void test_insta_shield(void)
{
    const S3KPlayer *p;
    uint8_t ids[8];
    int n, active = 0;

    reset_sonic();
    frame(PAD_A);
    p = s3k_sonic_player();
    /* Releasing caps y_vel at -$400, so the only way to press while rising
     * faster is a second jump button: hold A and press B. S3K ignores it. */
    frame(PAD_A);
    frame(PAD_A | PAD_B);
    EXPECT(p->double_jump_flag == 0, "no shield move while rising fast");
    while (p->y_vel < -0x400) frame(PAD_A);
    s3k_sonic_take_sfx(ids, 8);
    frame(PAD_A | PAD_B);
    n = s3k_sonic_take_sfx(ids, 8);
    EXPECT(p->double_jump_flag == 1, "Insta-Shield armed");
    EXPECT(sfx_seen(ids, n, S3K_SFX_INSTA_ATTACK), "sfx_InstaAttack");
    EXPECT(s3k_sonic_touch_attacking() && s3k_sonic_touch_immune(),
           "Insta-Shield attacks and is immune");
    {
        int l, t, w, h;
        s3k_player_touch_box(p, &l, &t, &w, &h);
        EXPECT(l == -0x18 && t == -0x18 && w == 0x30 && h == 0x30,
               "Insta-Shield touch box $30x$30");
    }
    active = 1;  /* the press frame itself */
    while (p->double_jump_flag == 1 && active < 40) {
        frame(0);
        if (p->double_jump_flag == 1) active++;
    }
    /* Ani_InstaShield anim 1 shows frames 0-6, six more 6s, then 7 on the
     * 14th object update, which writes double_jump_flag = 2. Sonic's own
     * TouchResponse runs before the shield object each frame, so the flag is
     * 1 for 14 touch checks and still 1 after 13 complete frames. */
    EXPECT(active == 13, "Insta-Shield frames with flag 1: %d", active);
    EXPECT(p->double_jump_flag == 2, "attack ends with flag 2");
    frame(PAD_A);
    EXPECT(p->double_jump_flag == 2, "one shield move per jump");
    while (p->status & S3K_STATUS_IN_AIR) frame(0);
    EXPECT(p->double_jump_flag == 0, "landing re-arms");

    /* SMB1's Mushroom (the standard shield) keeps the Insta-Shield, which
     * plays its attack and then hands the shield its own animation back. */
    reset_sonic();
    s3k_player_set_shield(s3k_sonic_player_mut(), S3K_STATUS2_SHIELD);
    p = s3k_sonic_player();
    frame(PAD_A);
    frame(0);
    while (p->y_vel < -0x400) frame(0);
    s3k_sonic_take_sfx(ids, 8);
    frame(PAD_A);
    n = s3k_sonic_take_sfx(ids, 8);
    EXPECT(p->double_jump_flag == 1 && sfx_seen(ids, n, S3K_SFX_INSTA_ATTACK),
           "Insta-Shield under the standard shield");
    EXPECT(s3k_sonic_insta_shield_active() && s3k_sonic_touch_immune(),
           "shielded Insta-Shield attacks and is immune");
    active = 1;
    while (p->double_jump_flag == 1 && active < 40) {
        frame(0);
        if (p->double_jump_flag == 1) active++;
    }
    EXPECT(active == 13, "shielded Insta-Shield frames with flag 1: %d", active);
    frame(0);
    EXPECT(p->shield_anim == 0 && (p->status_secondary & S3K_STATUS2_SHIELD),
           "standard shield animation resumes, shield kept");

    /* The Fire Shield ball breaks blocks in the air only in its dash. */
    reset_sonic();
    s3k_sonic_set_fire_shield(1);
    p = s3k_sonic_player();
    frame(PAD_A);
    frame(0);
    s3k_sonic_player_mut()->x_vel = 0x600;
    EXPECT(!s3k_sonic_breaks_side_blocks() && !s3k_sonic_fire_dash_hits_blocks(),
           "fast Fire Shield ball without the dash hits no blocks");
    while (p->y_vel < -0x400) frame(0);
    frame(PAD_A);
    EXPECT(s3k_sonic_breaks_side_blocks() && s3k_sonic_fire_dash_hits_blocks(),
           "Fire Shield dash hits blocks");

    /* Walking off a ledge is not `jumping`: no Insta-Shield. */
    reset_sonic();
    s3k_player_set_underwater(s3k_sonic_player_mut(), 0);
    s3k_sonic_player_mut()->status |= S3K_STATUS_IN_AIR;
    host_y = -0x4000;
    frame(0);
    frame(PAD_A);
    EXPECT(s3k_sonic_player()->double_jump_flag == 0,
           "no Insta-Shield without a jump");
}

static void test_fire_shield(void)
{
    const S3KPlayer *p;
    uint8_t ids[8];
    int n;

    reset_sonic();
    s3k_sonic_set_fire_shield(1);
    p = s3k_sonic_player();
    EXPECT(p->status_secondary == (S3K_STATUS2_SHIELD | S3K_STATUS2_FIRE),
           "fire shield status bits");
    frame(PAD_A);
    frame(0);
    while (p->y_vel < -0x400) frame(0);
    s3k_sonic_take_sfx(ids, 8);
    frame(PAD_A);
    n = s3k_sonic_take_sfx(ids, 8);
    EXPECT(p->x_vel == 0x800 + 0 && p->y_vel == 0x38,
           "fire dash x $800, y zeroed then gravity: %X %X", p->x_vel, p->y_vel);
    EXPECT(sfx_seen(ids, n, S3K_SFX_FIRE_ATTACK), "sfx_FireAttack");
    EXPECT(p->shield_anim == 1 || p->shield_prev_anim == 1, "dash shield anim");
}

/* SMB1 deviation: the Starman keeps the shield moves S3K refuses under
 * invincibility, and the shield object still plays their attack. */
static void test_invincible_shield_moves(void)
{
    const S3KPlayer *p;
    uint8_t ids[8];
    int n, active;

    reset_sonic();
    s3k_sonic_set_fire_shield(1);
    s3k_player_set_invincible(s3k_sonic_player_mut(), 1);
    p = s3k_sonic_player();
    frame(PAD_A);
    frame(0);
    while (p->y_vel < -0x400) frame(0);
    s3k_sonic_take_sfx(ids, 8);
    frame(PAD_A);
    n = s3k_sonic_take_sfx(ids, 8);
    EXPECT(p->double_jump_flag == 1 && p->x_vel == 0x800 &&
           sfx_seen(ids, n, S3K_SFX_FIRE_ATTACK),
           "Fire Shield dash under invincibility");
    EXPECT(p->shield_anim == 1 && s3k_sonic_fire_dash_flames(),
           "dash flames animate under invincibility");
    active = 1;
    while (p->shield_anim == 1 && active < 60) {
        frame(0);
        active++;
    }
    /* Ani_FireShield anim 1: twelve mappings at two frames each, then its
     * $FD reached on the 25th shield update (the press frame's included). */
    EXPECT(active == 25, "dash flames last 25 frames: %d", active);
    frame(0);   /* the flag is sampled by the next frame's control */
    EXPECT(p->shield_anim == 0 && !s3k_sonic_fire_dash_flames(),
           "dash flames burn out");

    reset_sonic();
    s3k_player_set_invincible(s3k_sonic_player_mut(), 1);
    p = s3k_sonic_player();
    frame(PAD_A);
    frame(0);
    while (p->y_vel < -0x400) frame(0);
    s3k_sonic_take_sfx(ids, 8);
    frame(PAD_A);
    n = s3k_sonic_take_sfx(ids, 8);
    EXPECT(s3k_sonic_insta_shield_active() && sfx_seen(ids, n, S3K_SFX_INSTA_ATTACK),
           "Insta-Shield under invincibility");
    active = 1;
    while (p->double_jump_flag == 1 && active < 40) {
        frame(0);
        if (p->double_jump_flag == 1) active++;
    }
    EXPECT(active == 13 && p->double_jump_flag == 2,
           "invincible Insta-Shield ends on schedule: %d", active);
}

/* Sonic_MdRoll refuses the jump while spin_dash_flag holds the roll, unless
 * the host calls the roll its own tunnel; the jump then leaves it. */
static void test_tunnel_jump(void)
{
    S3KPlayer *p;

    reset_sonic();
    p = s3k_sonic_player_mut();
    for (int i = 0; i < 40; ++i) frame(PAD_R);
    frame(PAD_D);
    EXPECT(p->status & S3K_STATUS_ROLL, "rolling");
    p->spin_dash_flag = 1;
    frame(PAD_A);
    EXPECT(!(p->status & S3K_STATUS_IN_AIR), "no jump in an S3K tunnel");
    frame(0);
    env_tunnel_jump = 1;
    frame(PAD_A);
    EXPECT((p->status & S3K_STATUS_IN_AIR) && p->spin_dash_flag == 0 &&
           (p->status & S3K_STATUS_ROLL_JUMP),
           "roll jump out of a host tunnel");
}

static void test_wall_push(void)
{
    const S3KPlayer *p;
    reset_sonic();
    wall_x = 0x2000;
    for (int i = 0; i < 80; ++i) frame(PAD_R);
    p = s3k_sonic_player();
    EXPECT(p->ground_vel == 0 && (p->status & S3K_STATUS_PUSH),
           "pushing a wall zeroes inertia and sets Push");
    EXPECT(p->mapping_frame >= 0xB6 && p->mapping_frame <= 0xB9,
           "push frames $B6-$B9: %02X", p->mapping_frame);
}

static void test_hurt(void)
{
    S3KPlayer *p;
    reset_sonic();
    p = s3k_sonic_player_mut();
    s3k_player_hurt(p, 0, 0);
    EXPECT(p->routine == S3K_ROUTINE_HURT && p->y_vel == -0x400 &&
           p->x_vel == -0x200, "HurtCharacter knockback");
    while (p->routine == S3K_ROUTINE_HURT) frame(PAD_R);
    EXPECT(p->invulnerability_timer == 120 && p->anim == S3K_ANIM_WALK &&
           p->ground_vel == 0, "landing sets 120 invulnerability frames");
}

int main(void)
{
    EXPECT(s3k_sonic_controller_register(), "register");
    test_ground_acceleration();
    test_skid_asymmetry();
    test_jump_arc();
    test_air_drag_and_control();
    test_spindash();
    test_roll();
    test_insta_shield();
    test_fire_shield();
    test_invincible_shield_moves();
    test_tunnel_jump();
    test_wall_push();
    test_hurt();
    if (failures) {
        fprintf(stderr, "%d S3K Sonic assertion(s) failed\n", failures);
        return 1;
    }
    puts("S3K Sonic core harness passed");
    return 0;
}
