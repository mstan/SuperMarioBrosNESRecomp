/*
 * game_sonic_adapter.c -- SMB1 consequences for S3K Sonic.
 *
 * S3K decides what a touch means (sonic3k.asm TouchResponse / Touch_Enemy /
 * Touch_ChkHurt / HurtCharacter); SMB1 keeps deciding what the consequence
 * does to its own objects (ShellOrBlockDefeat, the shell kick, power-up
 * erasure, the death sequence). This file is the translation between them.
 *
 * SMB1's items are read as S3K's:
 *   coins         -> rings: a hit with no shield spills up to 32 of them as
 *                    Obj_Bouncing_Ring, which can be collected again; a hit
 *                    with no rings and no shield is Kill_Character
 *   PlayerStatus 1 (Mushroom)    -> the standard shield
 *   PlayerStatus 2 (Fire Flower) -> the Fire Shield
 *   Starman       -> invincibility
 * A shield absorbs one hit and is lost (HurtCharacter's andi #$8E).
 */
#include "game_sonic_adapter.h"

#include "game_smash64.h"
#include "game_sonic.h"
#include "game_sonic_audio.h"
#include "game_sonic_items.h"
#include "mods/s3k/s3k_rings.h"
#include "mods/s3k/sonic_controller.h"

#include "foreign_controller.h"
#include "mapper.h"
#include "mod_function_hooks.h"
#include "mod_savestate.h"
#include "nes_runtime.h"

#include "generated/super-mario-bros_full_decls.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SONIC_CONTACT_HOOK_ID "super-mario-bros.s3k.enemy-contact"
#define SONIC_POWERUP_HOOK_ID "super-mario-bros.s3k.powerup"
#define SONIC_WHIRLPOOL_HOOK_ID "super-mario-bros.s3k.whirlpool"
#define SONIC_LARGE_PLATFORM_HOOK_ID "super-mario-bros.s3k.large-platform"
#define SONIC_SMALL_PLATFORM_HOOK_ID "super-mario-bros.s3k.small-platform"
#define SONIC_LOOPBACK_HOOK_ID "super-mario-bros.s3k.loopback"
#define SONIC_ADAPTER_SAVE_ID "super-mario-bros.s3k.adapter"

#define SMB1_PLAYER_ENEMY_COLLISION_ADDR 0xD853
#define SMB1_POWERUP_COLLISION_ADDR 0xD800
#define SMB1_PROCESS_WHIRLPOOLS_ADDR 0xB7B8
#define SMB1_LARGE_PLATFORM_COLLISION_ADDR 0xDB45
#define SMB1_SMALL_PLATFORM_COLLISION_ADDR 0xDB7B
#define SMB1_EXEC_GAME_LOOPBACK_ADDR 0xC08C
#define SMB1_GAMEMODE_PLAYER_CTRL 8

/* ExecGameLoopback subtracts four pages from every page location. */
#define SMB1_LOOPBACK_DX (-4 * 256)

/* SMB1's water surface: ProcSwim and InitJS stop a swimmer whose
 * Player_Y_Position is above $14, i.e. whose 32px body centre is above the
 * waves at screen y $24. That centre crossing is S3K's Water_level test. */
#define SMB1_WATER_TOP_Y 0x14

/* SMB1 Square1/Square2 sound queue bits (smb.asm). */
#define SFX_ENEMY_SMACK 0x08
#define SFX_POWERUP_GRAB 0x20

/* Jumpspring launches, re-expressed for S3K gravity. SMB1 launches with a
 * whole-pixel Player_Y_Speed of -7 (JumpspringForce $F9) or -12 (A pressed,
 * $F4) under VerticalForce $70 (0.4375 px/f^2), peaking about 59.5 and 170.6
 * pixels above the spring. These S3K y_vel values reach the same apex under
 * S3K's $38 (0.21875 px/f^2) gravity, so the level's spring targets remain
 * reachable without inventing S3K spring strengths SMB1's rooms were never
 * built for. */
#define SONIC_SPRING_Y_VEL        (-0x520)
#define SONIC_SPRING_BOOST_Y_VEL  (-0x8A0)

static int s_enabled;
/* Diagnostic: NESRECOMP_SONIC_DIAG_POWER=0|1|2 forces SMB's PlayerStatus at
 * every ordinary-control frame, so scripted traversal tests are not ended by
 * an early contact. Announced on stderr; never set in normal play. */
static int s_diag_power = -1;
/* Diagnostic: NESRECOMP_SONIC_DIAG_SPEED=<hex 8.8 speed>, e.g. 600, gives
 * Sonic that ground speed at once whenever Right is held on the ground, so
 * scripted tests reach top speed without a run-up. */
static int s_diag_speed;
static int s_force_native_injury;
static int s_hazard_pending;
static int s_hazard_world_x;
static int s_hazard_fire;
/* Sonic's ball is in, or jumped out of, a gap his standing body does not
 * fit (update_tunnel_roll). */
static uint8_t s_tunnel_ball;
/* Frames left in which a landing Fire Shield dash is still plowing through
 * bricks (update_dash_plow). */
#define SONIC_DASH_PLOW_FRAMES 8
static uint8_t s_dash_plow;

/* Rings are SMB1's coins. */
#define SMB1_COIN_DIGITS_ONES 0x17   /* CoinTallyOffsets for player 1 */
#define SMB1_COIN_DIGITS_ONES_P2 0x1D
#define SMB1_SFX_COIN_GRAB 0x01      /* Square2SoundQueue */
static S3KRingSpill s_rings;
static SonicBrickDebris s_debris[SONIC_BRICK_DEBRIS_MAX];
static int16_t s_sine[320];
static int s_sine_ready;
static uint8_t s_prev_coins;
static int s_prev_coins_valid;
static int s_death_coins_cleared;

static int player_world_x(void)
{
    return ((int)g_ram[Player_PageLoc] << 8) | (int)g_ram[Player_X_Position];
}

static int sonic_active(void)
{
    return s_enabled && game_smash64_sonic_selected() &&
           nes_foreign_ownership() == FOREIGN_OWNERSHIP_FOREIGN;
}

/* Sonic is the player at all, including SMB1's scripted sequences. */
static int sonic_selected_player(void)
{
    return s_enabled && game_smash64_sonic_selected();
}

static int wrap16(int v)
{
    return (int)(int16_t)(uint16_t)v;
}

/* NESRECOMP_SONIC_DEBUG=1: per-frame SD lines and SX sound-id lines. */
static int sonic_debug_enabled(void)
{
    static int s_debug = -1;
    if (s_debug < 0) {
        const char *e = getenv("NESRECOMP_SONIC_DEBUG");
        s_debug = e && *e && *e != '0';
    }
    return s_debug;
}

static int screen_left_world_x(void)
{
    return ((int)g_ram[ScreenLeft_PageLoc] << 8) | (int)g_ram[ScreenLeft_X_Pos];
}

/* ------------------------------------------------------------- sensors -- */

/* Metatile in SMB1's block buffer at a world pixel, or 0 outside the
 * collision window. Mirrors BlockBufferCollision's column/row math. */
static uint8_t block_at(int world_x, int screen_y)
{
    int col, row;
    uint16_t base;

    if (world_x < 0 || screen_y < 0x20 || screen_y >= 0xF0) return 0;
    col = (world_x >> 4) & 0x1F;
    row = (screen_y - 0x20) >> 4;
    if (row > 12) return 0;
    base = (col & 0x10) ? Block_Buffer_2 : Block_Buffer_1;
    return g_ram[(uint16_t)(base + row * 16 + (col & 0x0F))];
}

static int metatile_is_floor(uint8_t tile)
{
    CPU6502State save;
    int climb;

    /* DoFootCheck: any nonzero metatile except climbables, coins and the
     * invisible coin/1-up blocks. */
    if (tile == 0 || tile == 0xC2 || tile == 0xC3 ||
        tile == 0x5F || tile == 0x60)
        return 0;
    save = g_cpu;
    g_cpu.A = tile;
    CheckForClimbMTiles();
    climb = g_cpu.C;
    g_cpu = save;
    return !climb;
}

static int metatile_is_solid_ceiling(uint8_t tile)
{
    CPU6502State save;
    int solid;

    if (tile == 0 || tile == 0xC2 || tile == 0xC3) return 0;
    save = g_cpu;
    g_cpu.A = tile;
    CheckForSolidMTiles();
    solid = g_cpu.C;
    g_cpu = save;
    return solid;
}

/* A tile a standing body cannot share: anything but air, coins and the
 * hidden coin/1-up blocks. */
static int tile_blocks_standing(uint8_t tile)
{
    return tile != 0 && tile != 0xC2 && tile != 0xC3 &&
           tile != 0x5F && tile != 0x60;
}

/* Would Sonic's standing (Big) body overlap the level here? Big Mario's
 * head probe (x+8, y+4) and upper side probes (x+2 / x+13, y+8). */
static int standing_body_blocked(void)
{
    const int x = player_world_x();
    const int y = (int)g_ram[Player_Y_Position];
    if (g_ram[Player_Y_HighPos] != 1) return 0;
    return tile_blocks_standing(block_at(x + 8, y + 4)) ||
           tile_blocks_standing(block_at(x + 2, y + 8)) ||
           tile_blocks_standing(block_at(x + 13, y + 8));
}

/* S3K keeps a player rolling through a tunnel by holding spin_dash_flag
 * (Sonic_RollSpeed then restores $400 of ground speed instead of standing
 * him up, and Sonic_MdRoll refuses the jump). A ground roll under one of
 * SMB1's one-tile gaps is that tunnel: hold the flag while a standing body
 * would not fit, release it once it would. A roll only carries the flag
 * this way; the spindash charge sets it without Status_Roll.
 *
 * SMB1's tunnels are not S3K's: a spindash carves them out of bricks, and
 * the screen's left edge, which never scrolls back, can seal one. So the
 * tunnel ball may jump, like Big Mario's crouch jump: it keeps the crouching
 * collision profile in the air (its head meets the brick above the tunnel
 * rather than starting inside it) until the standing body fits, and lands
 * curled if it still does not. Returns 1 when that jump is allowed. */
static int update_tunnel_roll(S3KPlayer *p)
{
    const int blocked = standing_body_blocked();
    int rolling, held_tunnel;

    if (p->routine != S3K_ROUTINE_CONTROL || !blocked)
        s_tunnel_ball = 0;
    else if (s_tunnel_ball &&
             !(p->status & (S3K_STATUS_IN_AIR | S3K_STATUS_ROLL)))
        s3k_player_curl(p);

    rolling = (p->status & (S3K_STATUS_ROLL | S3K_STATUS_IN_AIR)) ==
              S3K_STATUS_ROLL;
    held_tunnel = p->spin_dash_flag && (p->status & S3K_STATUS_ROLL);
    if (!rolling || !blocked) {
        if (held_tunnel) p->spin_dash_flag = 0;
        return 0;
    }
    s_tunnel_ball = 1;
    if (!p->spin_dash_flag) p->spin_dash_flag = 1;
    /* Stopped by a wall inside the gap: the restored $400 follows the pad,
     * or turns back out when no direction is held. */
    if ((uint16_t)(p->ground_vel + 0x7F) < 0xFF) {
        const uint8_t pad = g_controller1_buttons;
        if (pad & 0x02) p->status |= S3K_STATUS_FACING_LEFT;
        else if (pad & 0x01) p->status &= (uint8_t)~S3K_STATUS_FACING_LEFT;
        else p->status ^= S3K_STATUS_FACING_LEFT;
    }
    return 1;
}

/* A Fire Shield dash that lands while it is still breaking its way through a
 * brick wall (it broke a block in the last few frames) stays curled and rolls
 * on at the dash's speed, which is itself breakable-wall speed. S3K's dash
 * would uncurl on landing; inside an SMB1 brick wall that landing is on the
 * next brick row down, and an uncurled Sonic would stop at the next brick. */
static void update_dash_plow(S3KPlayer *p)
{
    if (!s_dash_plow) return;
    if (p->routine != S3K_ROUTINE_CONTROL) {
        s_dash_plow = 0;
        return;
    }
    if (p->status & S3K_STATUS_IN_AIR) {
        s_dash_plow--;
        return;
    }
    if (!(p->status & S3K_STATUS_ROLL) &&
        (p->ground_vel >= 0x480 || p->ground_vel <= -0x480))
        s3k_player_curl(p);
    s_dash_plow = 0;
}

void game_sonic_adapter_note_dash_plow(void)
{
    s_dash_plow = SONIC_DASH_PLOW_FRAMES;
}

int game_sonic_adapter_low_profile(void)
{
    return s3k_sonic_low_profile() ||
           (s_tunnel_ball && (s3k_sonic_player()->status & S3K_STATUS_ROLL));
}

void game_sonic_adapter_prepare_control(void)
{
    S3KPlayer *p = s3k_sonic_player_mut();
    S3KPlayerEnvironment env;
    const int x = player_world_x() + 8;
    const int y = (int)g_ram[Player_Y_Position];
    const int on_screen = g_ram[Player_Y_HighPos] == 1;
    const int feet = y + 32;
    const int underwater = g_ram[SwimmingFlag] != 0 &&
        ((int8_t)g_ram[Player_Y_HighPos] > 1 ||
         (on_screen && y >= SMB1_WATER_TOP_Y));
    int r, tunnel_jump;

    if (s_diag_power >= 0 && g_ram[PlayerStatus] != (uint8_t)s_diag_power) {
        g_ram[PlayerStatus] = (uint8_t)s_diag_power;
        g_ram[PlayerSize] = s_diag_power ? 0 : 1;
    }
    /* Obj_FireShield destroys itself in water and leaves no shield behind
     * (andi.b #$8E,status_secondary): SMB1's Fire Flower goes with it. */
    if (underwater && g_ram[PlayerStatus] >= 2) {
        g_ram[PlayerStatus] = 0;
        g_ram[PlayerSize] = 1;
    }
    /* Persistent S3K status from SMB1's own state. */
    s3k_player_set_shield(p, g_ram[PlayerStatus] >= 2 ? S3K_STATUS2_FIRE :
                             g_ram[PlayerStatus] == 1 ? S3K_STATUS2_SHIELD : 0);
    s3k_player_set_invincible(p, g_ram[StarInvincibleTimer] != 0);
    if (s_diag_speed && p->routine == S3K_ROUTINE_CONTROL &&
        !(p->status & (S3K_STATUS_IN_AIR | S3K_STATUS_ROLL)) &&
        !p->spin_dash_flag && (g_controller1_buttons & 0x01) &&
        p->ground_vel < s_diag_speed)
        p->ground_vel = (int16_t)s_diag_speed;
    update_dash_plow(p);
    tunnel_jump = update_tunnel_roll(p);
    r = p->x_radius;

    memset(&env, 0, sizeof(env));
    env.underwater = (uint8_t)underwater;
    env.tunnel_jump = (uint8_t)tunnel_jump;
    /* CalcRoomOverHead must find 6 pixels above the head probe of the body
     * SMB1 collides (a crouching Big Mario's for a ball in a gap). Bumpable
     * bricks and ? blocks are not a ceiling here: SMB1 expects the player to
     * jump into them. */
    env.room_overhead = !on_screen ||
        !metatile_is_solid_ceiling(block_at(
            x, y + (game_sonic_adapter_low_profile() ? 0x12 : 0x04) - 6));
    if (on_screen) {
        env.floor_center = (uint8_t)metatile_is_floor(block_at(x, feet));
        env.floor_right = (uint8_t)metatile_is_floor(block_at(x + r, feet));
        env.floor_left = (uint8_t)metatile_is_floor(block_at(x - r, feet));
        env.floor_center_left6 =
            (uint8_t)metatile_is_floor(block_at(x - 6, feet));
        env.floor_center_right6 =
            (uint8_t)metatile_is_floor(block_at(x + 6, feet));
    } else {
        env.floor_center = env.floor_right = env.floor_left = 1;
        env.floor_center_left6 = env.floor_center_right6 = 1;
    }
    s3k_sonic_set_environment(&env);
}

/* ------------------------------------------------------------ springs -- */

void game_sonic_adapter_spring_launch(int8_t force)
{
    S3KPlayer *p = s3k_sonic_player_mut();
    ForeignCollisionResult hit;

    memset(&hit, 0, sizeof(hit));
    hit.has_imposed_vy = 1;
    hit.imposed_vy = -(force <= -12 ? SONIC_SPRING_BOOST_Y_VEL
                                    : SONIC_SPRING_Y_VEL) / 256.0;
    (void)p;
    s3k_sonic_set_collision_extras(1);
    nes_foreign_resolve(&hit);
}

/* --------------------------------------------------------------- audio -- */

void game_sonic_adapter_play_sfx(uint64_t frame)
{
    uint8_t ids[S3K_PLAYER_SFX_CAPACITY];
    ForeignAudioEvents events;
    int n = s3k_sonic_take_sfx(ids, S3K_PLAYER_SFX_CAPACITY);

    if (n <= 0) return;
    memset(&events, 0, sizeof(events));
    for (int i = 0; i < n && i < FOREIGN_AUDIO_EVENT_CAPACITY; ++i) {
        if (sonic_debug_enabled())
            fprintf(stderr, "SX %llu sfx=%02X\n", (unsigned long long)frame,
                    ids[i]);
        events.events[i].cue = S3K_SONIC_AUDIO_CUE(ids[i]);
        events.events[i].gain_percent = 100;
        events.count++;
    }
    game_sonic_audio_play_events(&events, frame);
}

/* ------------------------------------------------------- hurt / death -- */

static void sonic_native_death(void)
{
    CPU6502State save = g_cpu;
    S3KPlayer *p = s3k_sonic_player_mut();
    int kept = 0;

    /* ForceInjury's KillPlayer branch owns SMB1's death music, timer halt
     * and GameEngineSubroutine $0B. */
    s_force_native_injury = 1;
    g_ram[PlayerStatus] = 0;
    g_ram[InjuryTimer] = 0;
    InjurePlayer();
    s_force_native_injury = 0;
    g_cpu = save;
    s3k_player_kill(p);
    /* SMB1's death music plays alone: Kill_Character's sfx_Death is dropped
     * (a hit that only costs rings or a shield keeps it). */
    for (int i = 0; i < p->sfx_count; ++i) {
        if (p->sfx[i] != S3K_SFX_DEATH) p->sfx[kept++] = p->sfx[i];
    }
    p->sfx_count = kept;
}

static uint8_t coin_digit_ones_offset(void)
{
    return g_ram[CurrentPlayer] ? SMB1_COIN_DIGITS_ONES_P2 : SMB1_COIN_DIGITS_ONES;
}

/* Zero the onscreen coin tally and its HUD digits, then let SMB1 print the
 * status bar numbers through its own GetSBNybbles path. */
static void clear_coins(void)
{
    const uint8_t ones = coin_digit_ones_offset();
    CPU6502State save = g_cpu;

    g_ram[CoinTally] = 0;
    g_ram[DisplayDigits + ones] = 0;
    g_ram[DisplayDigits + ones - 1] = 0;
    runtime_begin_unclocked();
    GetSBNybbles();
    runtime_end_unclocked();
    g_cpu = save;
    s_prev_coins = 0;
    s_prev_coins_valid = 1;
}

static void queue_sfx(uint8_t id)
{
    S3KPlayer *p = s3k_sonic_player_mut();
    if (p->sfx_count < S3K_PLAYER_SFX_CAPACITY) p->sfx[p->sfx_count++] = id;
}

static void sonic_take_hit(int hazard_world_x)
{
    S3KPlayer *p = s3k_sonic_player_mut();
    const int had_shield = s3k_sonic_has_shield();
    const uint8_t rings = g_ram[CoinTally];

    if (s3k_sonic_touch_immune()) return;
    /* HurtCharacter: a shield absorbs the hit; otherwise rings spill, and
     * with no rings the hit is Kill_Character. */
    if (!had_shield && rings == 0) {
        sonic_native_death();
        return;
    }
    /* x_vel -$200 unless Sonic's x >= the hazard's. */
    s3k_player_hurt(p, player_world_x() + 8 >= hazard_world_x, 0);
    if (had_shield) {
        g_ram[PlayerStatus] = 0;
        g_ram[PlayerSize] = 1;
    } else {
        /* Obj_Bouncing_Ring, spawned at the player's (presented) centre. */
        const int cy = (int)g_ram[Player_Y_Position] + 32 -
                       sonic_scale_px((int)p->y_radius);
        s3k_rings_spill(&s_rings, s_sine_ready ? s_sine : NULL, rings,
                        player_world_x() + 8, cy);
        clear_coins();
        p->sfx_count = 0;
        queue_sfx(S3K_SFX_RING_LOSS);
    }
    /* SMB1 must process the knockback on its airborne path. */
    g_ram[Player_State] = 1;
    g_ram[Player_Y_Speed] = (uint8_t)(int8_t)-4;
    g_ram[InjuryTimer] = 0;
}

static int ring_floor_dist(int world_x, int y_bottom, void *user)
{
    uint8_t tile;
    (void)user;
    tile = block_at(world_x, y_bottom);
    if (!metatile_is_floor(tile)) return 16;
    /* Block rows start at screen y $20, so every surface is a multiple of
     * 16; a sensor on the surface row is distance 0, deeper is negative. */
    return ((y_bottom >> 4) << 4) - y_bottom;
}

static void update_rings(void)
{
    const S3KPlayer *p = s3k_sonic_player();
    const int left = screen_left_world_x();
    int collected;

    if (!s3k_rings_active(&s_rings)) return;
    /* Obj_Bouncing_Ring is an object: it stops with the rest of the world
     * while the game is paused. */
    if (g_ram[GamePauseStatus] & 0x01) return;
    /* Keep each ring on the screen's page numbering (Player_PageLoc wraps
     * through $FF/$00) so distances to Sonic and the tiles stay small. */
    for (int i = 0; i < S3K_RING_SPILL_MAX; ++i) {
        S3KRing *r = &s_rings.rings[i];
        const int sub = r->x & 0xFF;
        if (r->state == S3K_RING_FREE) continue;
        r->x = (left + wrap16((r->x >> 8) - left)) * 256 + sub;
    }
    /* Camera_max_Y_pos+$E0: just below SMB1's 240-line screen. */
    s3k_rings_update(&s_rings, ring_floor_dist, NULL, 0x100);
    if (nes_foreign_ownership() != FOREIGN_OWNERSHIP_FOREIGN) return;
    {
        int l, t, w, h;
        const int cx = left + wrap16(player_world_x() + 8 - left);
        const int cy = (int)g_ram[Player_Y_Position] + 32 -
                       sonic_scale_px((int)p->y_radius);
        s3k_player_touch_box(p, &l, &t, &w, &h);
        collected = s3k_rings_collect(&s_rings, cx + sonic_scale_px(l),
                                      cy + sonic_scale_px(t),
                                      cx + sonic_scale_px(l + w),
                                      cy + sonic_scale_px(t + h),
                                      p->invulnerability_timer);
    }
    for (int i = 0; i < collected; ++i) {
        CPU6502State save = g_cpu;
        /* GiveRing: SMB1's GiveOneCoin keeps the tally, the 100-coin 1-up and
         * the HUD; the ring sound replaces the coin chime below. */
        runtime_begin_unclocked();
        GiveOneCoin();
        runtime_end_unclocked();
        g_cpu = save;
    }
}

/* Coins picked up from blocks and the level are rings too: swap SMB1's coin
 * chime for sfx_RingRight whenever the tally rises. */
static void update_coin_sounds(void)
{
    const uint8_t coins = g_ram[CoinTally];
    if (s_prev_coins_valid && coins != s_prev_coins &&
        (coins > s_prev_coins || coins == 0)) {
        g_ram[Square2SoundQueue] &= (uint8_t)~SMB1_SFX_COIN_GRAB;
        queue_sfx(0x33);   /* sfx_RingRight */
    }
    s_prev_coins = coins;
    s_prev_coins_valid = 1;
}

uint8_t game_sonic_adapter_injury_read(uint16_t pc, uint8_t val)
{
    if (s_force_native_injury) return val;
    if (!sonic_active()) return val;
    if (pc == 0xD92C && !s_hazard_pending) {
        /* A native hazard (firebar, hammer) reached InjurePlayer. Firebars
         * run in the enemy loop with ObjectOffset naming their slot. */
        const uint8_t slot = g_ram[ObjectOffset];
        s_hazard_pending = 1;
        s_hazard_fire = 0;
        s_hazard_world_x = player_world_x() + 8 +
            ((s3k_sonic_player()->status & S3K_STATUS_FACING_LEFT) ? -1 : 1);
        if (slot < 6 && g_ram[Enemy_Flag + slot]) {
            const uint8_t id = g_ram[Enemy_ID + slot];
            s_hazard_world_x = (((int)g_ram[Enemy_PageLoc + slot] << 8) |
                                (int)g_ram[Enemy_X_Position + slot]) + 8;
            s_hazard_fire = id >= 0x1B && id <= 0x1F;   /* firebars */
        }
    }
    /* Nonzero: SMB1's own injury bails out; S3K applies the hit post-NMI. */
    return 1;
}

/* ----------------------------------------------------- touch response -- */

/* Touch_Enemy's destroyable set: SMB1's badniks. */
static int ball_destroys(uint8_t id)
{
    switch (id) {
    case 0x00: /* GreenKoopa */
    case 0x01: /* red Koopa, as a Red Paratroopa demotes to */
    case 0x02: /* BuzzyBeetle */
    case 0x03: /* RedKoopa */
    case 0x04: /* Koopa variant (EnemyStomped shells every id below $09) */
    case 0x05: /* HammerBro */
    case 0x06: /* Goomba */
    case 0x07: /* Bloober */
    case 0x08: /* BulletBill_FrenzyVar */
    case 0x0A: /* GreyCheepCheep */
    case 0x0B: /* RedCheepCheep */
    case 0x0D: /* PiranhaPlant */
    case 0x0E: /* GreenParatroopaJump */
    case 0x0F: /* RedParatroopa */
    case 0x10: /* GreenParatroopaFly */
    case 0x11: /* Lakitu */
    case 0x12: /* Spiny: spiked on top only, see sonic_stomps */
    case 0x14: /* FlyingCheepCheep */
    case 0x33: /* BulletBill_CannonVar */
        return 1;
    default:
        /* Podoboo, Bowser's flame and Bowser are hazards and bosses, which a
         * rolling S3K player cannot destroy. */
        return 0;
    }
}

/* The enemies EnemyStomped demotes (paratroopas, ids $0E-$10, to $00/$01)
 * or shells (every other id below $09 it does not score separately: the
 * Koopa variants $00-$04 and Buzzy Beetle), kept for SMB1's stomp-and-kick
 * play. */
static int shell_family(uint8_t id)
{
    return id <= 0x04 || id == GreenParatroopaJump || id == RedParatroopa ||
           id == GreenParatroopaFly;
}

/* S3K shield_reaction: the Fire Shield ignores fire. */
static int hazard_is_fire(uint8_t id)
{
    return id == 0x0C || id == 0x15;
}

typedef struct TouchBox { int left, top, right, bottom; } TouchBox;

/* Touch_NoInstaShield / Insta-Shield box in SMB1 screen coordinates (the
 * Fire Shield dash's flames reach as far as the Insta-Shield). S3K's
 * y_pos is the body centre y_radius above the floor the feet touch; both
 * are measured at Sonic's presentation scale, like everything he draws. */
static TouchBox sonic_touch_box(void)
{
    const S3KPlayer *p = s3k_sonic_player();
    TouchBox b;
    int l, t, w, h;
    /* Not Player_Rel_XPos: that byte wraps a player just off the left edge
     * to the right one. */
    const int cx = wrap16(player_world_x() - screen_left_world_x()) + 8;
    const int cy = (int)g_ram[Player_Y_Position] + 32 -
                   sonic_scale_px((int)p->y_radius);

    if (s3k_sonic_fire_dash_flames()) {
        l = t = -0x18;
        w = h = 0x30;
    } else {
        s3k_player_touch_box(p, &l, &t, &w, &h);
    }
    b.left = cx + sonic_scale_px(l);
    b.top = cy + sonic_scale_px(t);
    b.right = cx + sonic_scale_px(l + w);
    b.bottom = cy + sonic_scale_px(t + h);
    return b;
}

static int touch_overlaps(const TouchBox *b, int box_ofs)
{
    const int el = g_ram[BoundingBox_UL_XPos + box_ofs];
    const int et = g_ram[BoundingBox_UL_YPos + box_ofs];
    const int er = g_ram[BoundingBox_DR_XPos + box_ofs];
    const int eb = g_ram[BoundingBox_DR_YPos + box_ofs];
    /* Touch_Width/Touch_Height accept both inclusive ends. */
    return el <= b->right && er >= b->left && et <= b->bottom && eb >= b->top;
}

static void defeat_slot(int slot)
{
    CPU6502State save = g_cpu;
    g_cpu.X = (uint8_t)slot;
    RelativeEnemyPosition();
    g_cpu.X = (uint8_t)slot;
    ShellOrBlockDefeat();
    g_cpu = save;
}

static void kick_shell(int slot)
{
    static const uint8_t k_kick_speed[2] = { 0x30, 0xD0 };  /* KickedShellXSpdData */
    static const uint8_t k_kick_pts[3] = { 0x0A, 0x06, 0x04 }; /* KickedShellPtsData */
    CPU6502State save = g_cpu;
    uint8_t dir, pts, timer;

    g_ram[Square1SoundQueue] = SFX_ENEMY_SMACK;
    g_ram[Enemy_State + slot] |= 0x80;
    g_cpu.X = (uint8_t)slot;
    EnemyFacePlayer();
    dir = g_cpu.Y > 1 ? 1 : g_cpu.Y;
    g_ram[Enemy_X_Speed + slot] = k_kick_speed[dir];
    pts = (uint8_t)(3 + g_ram[StompChainCounter]);
    timer = g_ram[EnemyIntervalTimer + slot];
    if (timer < 3) pts = k_kick_pts[timer];
    g_cpu.X = (uint8_t)slot;
    g_cpu.A = pts;
    SetupFloateyNumber();
    g_cpu = save;
}

/* Landing on an enemy from above: falling, the body centre above the
 * enemy's, and not in a shield attack (those hit whatever they touch). */
static int sonic_stomps(const S3KPlayer *p, const TouchBox *box, int box_ofs)
{
    const int enemy_mid_y = ((int)g_ram[BoundingBox_UL_YPos + box_ofs] +
                             (int)g_ram[BoundingBox_DR_YPos + box_ofs]) / 2;
    const int sonic_mid_y = (box->top + box->bottom) / 2;
    return p->routine == S3K_ROUTINE_CONTROL &&
           (p->status & S3K_STATUS_IN_AIR) && p->y_vel > 0 &&
           !s3k_player_insta_shield_active(p) && !s3k_sonic_fire_dashing() &&
           sonic_mid_y < enemy_mid_y;
}

/* EnemyStomped: paratroopas lose their wings, koopas and beetles become
 * shells, a sliding shell stops. Its points, stomp chain and sound are
 * SMB1's; its Player_Y_Speed bounce is replaced by S3K's own. */
static void stomp_slot(int slot)
{
    CPU6502State save = g_cpu;
    g_cpu.X = (uint8_t)slot;
    RelativeEnemyPosition();
    g_cpu.X = (uint8_t)slot;
    EnemyStomped();
    g_cpu = save;
}

/* The Fire Shield's dash is Sonic's fireball: one dash finishes Bowser the
 * way HurtBowser's last fireball does, turning a fake Bowser into the
 * enemy it disguised (BowserIdentities) with SMB1's own score and sound. */
static void fire_dash_hits_bowser(int slot)
{
    CPU6502State save = g_cpu;
    g_ram[BowserHitPoints] = 1;
    g_ram[0x01] = (uint8_t)slot;
    g_cpu.X = (uint8_t)slot;
    HandleEnemyFBallCol();
    g_cpu = save;
}

/* A spiny in the air: Lakitu's egg (state $05 until LandEnemyInitState
 * hatches it) or a spiny that walked off a ledge (EnemyBGCStateData's $01). */
static int spiny_falling(uint8_t state)
{
    return state == 0x05 || state == 0x01;
}

static int shell_kickable(int slot, uint8_t id, uint8_t state)
{
    if (id == Spiny || id == PiranhaPlant || id == Podoboo ||
        id == BulletBill_CannonVar || id >= 0x15)
        return 0;
    if (g_ram[AreaType] == 0) return 0;
    if (state & 0x80) return 0;               /* already a moving shell */
    (void)slot;
    return (state & 0x07) >= 2;
}

static int sonic_contact_hook(uint16_t addr)
{
    const int slot = g_cpu.X;
    CPU6502State save;
    TouchBox box;
    uint8_t id, state;
    int box_ofs, attacking;
    S3KPlayer *p;

    (void)addr;
    if (!sonic_active() || slot < 0 || slot > 5) return 0;
    id = g_ram[Enemy_ID + slot];
    /* Power-ups, flags, vines and the rest of SMB1's non-hostile objects
     * keep their native collision routines. */
    if (id >= 0x16 && id != Bowser && id != BulletBill_CannonVar) return 0;

    game_smash64_sonic_reconcile_in_enemy_loop(slot);

    /* PlayerEnemyCollision's own guards, minus its every-other-frame skip:
     * S3K runs TouchResponse on every frame, and at S3K speeds a
     * half-sampled touch would let Sonic pass through enemies. */
    save = g_cpu;
    CheckPlayerVertical();
    if (g_cpu.C) {
        g_cpu = save;
        return 1;
    }
    g_cpu = save;
    if (g_ram[EnemyOffscrBitsMasked + slot]) return 1;
    if (g_ram[GameEngineSubroutine] != SMB1_GAMEMODE_PLAYER_CTRL) return 1;
    state = g_ram[Enemy_State + slot];
    if (state & 0x20) return 1;

    box_ofs = 4 + slot * 4;
    box = sonic_touch_box();
    if (!touch_overlaps(&box, box_ofs)) {
        g_ram[Enemy_CollisionBits + slot] &= 0xFE;
        return 1;
    }

    p = s3k_sonic_player_mut();
    /* SMB1's ChkForPlayerInjury for the enemies that walk the ground (every
     * id below Bloober, and the Spiny): a player touching one while rising or
     * at the top of a jump is hurt, and only coming down on it stomps it. In
     * S3K a jump curls Sonic up and destroys whatever badnik he meets on the
     * way up, even one he had just walked into, so a jump pressed as a Goomba
     * or a Spiny reached him killed it from the side. A jump (a roll's jump
     * too) meets them as SMB1's player does; a roll, a spindash, the
     * Insta-Shield and the Fire Shield's dash and flames still destroy them,
     * and invincibility is handled above. */
    attacking = s3k_sonic_touch_attacking();
    if (attacking && p->jumping && p->y_vel <= 0 &&
        (id < Bloober || id == Spiny) &&
        !s3k_player_insta_shield_active(p) && !s3k_sonic_fire_dashing() &&
        !s3k_sonic_fire_dash_flames())
        attacking = 0;
    {
        const int enemy_mid_y = ((int)g_ram[BoundingBox_UL_YPos + box_ofs] +
                                 (int)g_ram[BoundingBox_DR_YPos + box_ofs]) / 2;
        const int sonic_below = (box.top + box.bottom) / 2 >= enemy_mid_y;
        const int stomp = sonic_stomps(p, &box, box_ofs);

        if (g_ram[StarInvincibleTimer]) {
            defeat_slot(slot);
            s3k_player_enemy_bounce(p, sonic_below);   /* Touch_EnemyNormal */
            return 1;
        }
        if (id == Bowser &&
            (s3k_sonic_fire_dashing() || s3k_sonic_fire_dash_flames())) {
            if (!(g_ram[Enemy_CollisionBits + slot] & 0x01)) {
                g_ram[Enemy_CollisionBits + slot] |= 0x01;
                fire_dash_hits_bowser(slot);
                s3k_player_enemy_bounce(p, sonic_below);
            }
            return 1;
        }
        if (shell_family(id)) {
            const int resting_shell = !(state & 0x80) && (state & 0x07) >= 2;
            /* One consequence per contact, as HandlePECollisions latches:
             * a demoted paratroopa is not destroyed by the same bounce. */
            if (g_ram[Enemy_CollisionBits + slot] & 0x01) return 1;
            if (attacking && stomp) {
                g_ram[Enemy_CollisionBits + slot] |= 0x01;
                /* HandlePECollisions kicks a resting shell whichever way
                 * the player meets it; anything else is EnemyStomped. */
                if (resting_shell && g_ram[AreaType] != 0) kick_shell(slot);
                else stomp_slot(slot);
                s3k_player_enemy_bounce(p, 0);
                return 1;
            }
        }
        if (id == Spiny &&
            (stomp || (spiny_falling(state) && p->jumping &&
                       !s3k_player_insta_shield_active(p) &&
                       !s3k_sonic_fire_dashing() &&
                       !s3k_sonic_fire_dash_flames()))) {
            /* EnemyStomped: a spiny's back hurts whatever lands on it, and
             * a falling spiny hurts a jumping ball from any side unless a
             * shield attack (Insta-Shield, Fire Shield dash) destroys it.
             * A roll or spindash, which never set jumping, destroys it. */
            if (g_ram[Enemy_CollisionBits + slot] & 0x01) return 1;
            g_ram[Enemy_CollisionBits + slot] |= 0x01;
            if (!s3k_sonic_touch_immune())
                sonic_take_hit(((int)g_ram[Enemy_PageLoc + slot] << 8 |
                                (int)g_ram[Enemy_X_Position + slot]) + 8);
            return 1;
        }
        if (attacking && ball_destroys(id)) {
            defeat_slot(slot);
            s3k_player_enemy_bounce(p, sonic_below);   /* Touch_EnemyNormal */
            return 1;
        }
    }

    /* HandlePECollisions' contact latch. */
    if (g_ram[Enemy_CollisionBits + slot] & 0x01) return 1;
    g_ram[Enemy_CollisionBits + slot] |= 0x01;

    if (!attacking && shell_kickable(slot, id, state)) {
        if (id != Goomba) kick_shell(slot);
        return 1;
    }

    if (s3k_sonic_touch_immune()) return 1;
    if (s3k_sonic_has_fire_shield() && hazard_is_fire(id)) return 1;
    sonic_take_hit((((int)g_ram[Enemy_PageLoc + slot] << 8) |
                    (int)g_ram[Enemy_X_Position + slot]) + 8);
    return 1;
}

/* ----------------------------------------------------------- power-ups -- */

static int sonic_powerup_hook(uint16_t addr)
{
    CPU6502State save;
    const uint8_t type = g_ram[PowerUpType];

    (void)addr;
    if (!sonic_active()) return 0;
    if (type >= 2) return 0;   /* Starman and 1-up stay native */

    save = g_cpu;
    EraseEnemyObject();
    g_cpu = save;
    g_cpu.A = 0x06;           /* 1000 points, as HandlePowerUpCollision */
    SetupFloateyNumber();
    g_cpu = save;

    /* A shield monitor, without PlayerChangeSize/PlayerFireFlower: S3K never
     * freezes the world to break a monitor, and a new shield replaces the
     * old one. The Mushroom is the standard shield, the Fire Flower the Fire
     * Shield. PlayerStatus keeps SMB1's own item progression (small players
     * get Mushrooms from blocks, shielded ones get Fire Flowers). */
    {
        S3KPlayer *p = s3k_sonic_player_mut();
        (void)SFX_POWERUP_GRAB;
        if (type == 0) {
            g_ram[PlayerStatus] = 1;
            s3k_player_set_shield(p, S3K_STATUS2_SHIELD);
            queue_sfx(0x3A);                       /* sfx_Shield */
        } else {
            g_ram[PlayerStatus] = 2;
            s3k_player_set_shield(p, S3K_STATUS2_FIRE);
            queue_sfx(S3K_SFX_FIRE_SHIELD);
        }
        g_ram[PlayerSize] = 0;
    }
    return 1;
}

/* ---------------------------------------------------- water and platforms -- */

/* ProcessWhirlpools: no pull on Sonic. Whirlpool_Flag (Cannon_Timer's first
 * byte, only meaningful in water levels) is left cleared as the routine's
 * own first write leaves it when no whirlpool holds the player. */
static int sonic_whirlpool_hook(uint16_t addr)
{
    (void)addr;
    if (!sonic_selected_player()) return 0;
    /* ProcessWhirlpools is also where every GameEngine frame has finished
     * SMB1's own objects: the pooled power-ups run here. */
    game_sonic_items_run_power_ups();
    if (g_ram[AreaType] != 0) return 0;
    g_ram[Whirlpool_Flag] = 0;
    return 1;
}

/* CheckPlayerVertical's verdict: player on screen and above $D0. */
static int player_vertical_ok(void)
{
    CPU6502State save = g_cpu;
    int ok;
    CheckPlayerVertical();
    ok = !g_cpu.C;
    g_cpu = save;
    return ok;
}

/* PlayerCollisionCore against the enemy bounding box at `box_ofs`. */
static int player_box_overlaps(int box_ofs)
{
    CPU6502State save = g_cpu;
    const uint8_t s6 = g_ram[0x06], s7 = g_ram[0x07];
    int hit;
    g_cpu.Y = (uint8_t)box_ofs;
    PlayerCollisionCore();
    hit = g_cpu.C;
    g_ram[0x06] = s6;
    g_ram[0x07] = s7;
    g_cpu = save;
    return hit;
}

/* S3K's platforms (SolidObjectTop / PlatformObject) are solid from above
 * only: a player whose y_vel is not rising lands when the feet are no more
 * than 4px above the top and not yet 12px through it. SMB1 asks the same
 * question with a 6px window at the end of the frame, which S3K fall speeds
 * step straight over, and turns every other overlap into a head bump or a
 * side push (whose SideCollisionTimer also freezes the scroll). Here the
 * window is measured across the whole of this frame's fall, and every
 * other overlap is simply passed through. */
/* Enemy slots (one bit each) whose platform put Sonic on it at its latest
 * collision check. PlatformCollisionFlag says the same once that check has
 * run, but the platform inits leave the byte as the slot's previous object
 * had it, so a lift spawned this frame would read as carrying Sonic. */
static uint8_t s_platform_riders;

static void set_platform_rider(int slot, int carried)
{
    if (carried) s_platform_riders |= (uint8_t)(1u << slot);
    else s_platform_riders &= (uint8_t)~(1u << slot);
}

static int slot_is_platform(int slot)
{
    const uint8_t id = g_ram[Enemy_ID + slot];
    return g_ram[Enemy_Flag + slot] != 0 && id >= 0x24 && id <= 0x2C;
}

int game_sonic_adapter_platform_carried(int slot)
{
    return slot >= 0 && slot < 6 && slot_is_platform(slot) &&
           (s_platform_riders & (1u << slot)) != 0;
}

/* MoveObjectHorizontally's whole-pixel step for an X speed and sub-pixel
 * force: the high nybble, sign-extended, plus the carry of force + low
 * nybble. */
static int object_x_step(uint8_t speed, uint8_t force)
{
    const int high = (speed >> 4) >= 8 ? (int)(speed >> 4) - 16 : speed >> 4;
    return high + (force + ((speed << 4) & 0xF0) > 0xFF ? 1 : 0);
}

int game_sonic_adapter_lift_step(void)
{
    const S3KPlayer *p = s3k_sonic_player();
    int step = 0;

    if (g_ram[TimerControl] || (p->status & S3K_STATUS_IN_AIR) ||
        s3k_sonic_launched_jump())
        return 0;
    for (int slot = 0; slot < 6; ++slot) {
        const uint8_t id = g_ram[Enemy_ID + slot];
        const uint8_t force = g_ram[Enemy_X_MoveForce + slot];
        if (!game_sonic_adapter_platform_carried(slot) ||
            (g_ram[Enemy_State + slot] & 0x80))
            continue;
        if (id == 0x28) {
            /* XMovingPlatform: XMoveCntr_Platform (maximum $0E, every fourth
             * frame; FrameCounter already has this frame's value), then
             * MoveWithXMCntrs moves by the secondary counter, negated while
             * d1 of the primary counter is clear. */
            uint8_t primary = g_ram[XMovePrimaryCounter + slot];
            uint8_t secondary = g_ram[XMoveSecondaryCounter + slot];
            if ((g_ram[FrameCounter] & 3) == 0) {
                if (primary & 1) {
                    if (secondary == 0) primary++;
                    else secondary--;
                } else {
                    if (secondary == 0x0E) primary++;
                    else secondary++;
                }
            }
            step += object_x_step((primary & 2) ? secondary
                                                : (uint8_t)-secondary, force);
        } else if (id == 0x2A) {
            /* RightPlatform moves with its current speed, and only then
             * gives a ridden platform its $10. */
            step += object_x_step(g_ram[Enemy_X_Speed + slot], force);
        }
    }
    return step;
}

static int sonic_lands_on_platform(int box_ofs)
{
    const int feet = g_ram[BoundingBox_DR_YPos];
    const int top = g_ram[BoundingBox_UL_YPos + box_ofs];
    const int feet_before = feet - game_smash64_sonic_frame_dy();

    if (g_ram[GameEngineSubroutine] != SMB1_GAMEMODE_PLAYER_CTRL) return 0;
    if ((int8_t)g_ram[Player_Y_Speed] < 0) return 0;
    if (!player_box_overlaps(box_ofs)) return 0;
    return feet >= top - 4 && feet_before <= top + 12;
}

static void sonic_check_large_platform(int slot, int ofs)
{
    if (!player_vertical_ok()) return;
    if (!sonic_lands_on_platform((ofs * 4 + 4) & 0xFF)) return;
    /* SetCollisionFlag */
    g_ram[PlatformCollisionFlag + slot] = (uint8_t)ofs;
    g_ram[Player_State] = 0;
}

/* LargePlatformCollision with S3K top-solid landing. */
static int sonic_large_platform_hook(uint16_t addr)
{
    const int slot = g_cpu.X;
    (void)addr;
    if (!sonic_selected_player() || slot > 5) return 0;
    g_ram[PlatformCollisionFlag + slot] = 0xFF;
    if (!g_ram[TimerControl] && !(g_ram[Enemy_State + slot] & 0x80)) {
        /* A balance platform checks its partner first, then itself. */
        if (g_ram[Enemy_ID + slot] == 0x24)
            sonic_check_large_platform(slot, g_ram[Enemy_State + slot] & 0x0F);
        sonic_check_large_platform(slot, slot);
    }
    set_platform_rider(slot, g_ram[PlatformCollisionFlag + slot] != 0xFF);
    g_cpu.X = g_ram[ObjectOffset];
    return 1;
}

/* SmallPlatformCollision with S3K top-solid landing: the same two bounding
 * boxes, the second 128px below the first. */
static int sonic_small_platform_hook(uint16_t addr)
{
    const int slot = g_cpu.X;
    (void)addr;
    if (!sonic_selected_player() || slot > 5) return 0;
    if (!g_ram[TimerControl]) {
        const int box = slot * 4 + 4;
        g_ram[PlatformCollisionFlag + slot] = 0;
        if (player_vertical_ok()) {
            for (int counter = 2; counter > 0; --counter) {
                if (g_ram[Enemy_OffscreenBits] & 0x02) break;
                if (g_ram[BoundingBox_UL_YPos + box] >= 0x20 &&
                    player_box_overlaps(box)) {
                    if (sonic_lands_on_platform(box)) {
                        g_ram[PlatformCollisionFlag + slot] = (uint8_t)counter;
                        g_ram[Player_State] = 0;
                    }
                    break;
                }
                g_ram[BoundingBox_UL_YPos + box] =
                    (uint8_t)(g_ram[BoundingBox_UL_YPos + box] + 0x80);
                g_ram[BoundingBox_DR_YPos + box] =
                    (uint8_t)(g_ram[BoundingBox_DR_YPos + box] + 0x80);
            }
        }
        set_platform_rider(slot, g_ram[PlatformCollisionFlag + slot] != 0);
    }
    g_cpu.X = g_ram[ObjectOffset];
    return 1;
}

/* ScrollHandler's ChkPOffscr keeps the player from going left of the screen,
 * but it runs before the enemy loop, where a lift (PositionPlayerOnHPlat)
 * can carry Sonic past that edge again. KeepOnscr would put him back on the
 * next frame; do it as the frame ends, so he is never shown beyond the edge
 * and a lift dragging him into it slides away under him instead. */
static void keep_sonic_on_screen(void)
{
    const int left = screen_left_world_x();

    if (!sonic_active() ||
        g_ram[GameEngineSubroutine] != SMB1_GAMEMODE_PLAYER_CTRL ||
        wrap16(player_world_x() - left) >= 0)
        return;
    g_ram[Player_X_Position] = (uint8_t)left;
    g_ram[Player_PageLoc] = (uint8_t)(left >> 8);
}

/* ---------------------------------------------------------- loopbacks -- */

static void shift_adapter_world_x(int dx)
{
    for (int i = 0; i < S3K_RING_SPILL_MAX; ++i)
        if (s_rings.rings[i].state != S3K_RING_FREE)
            s_rings.rings[i].x += dx * 256;
    for (int i = 0; i < SONIC_BRICK_DEBRIS_MAX; ++i) {
        s_debris[i].orig_x = (int16_t)(s_debris[i].orig_x + dx);
        s_debris[i].x = (int16_t)(s_debris[i].x + dx);
    }
    game_sonic_items_shift_world_x(dx);
    s_hazard_world_x += dx;
}

/* ExecGameLoopback runs after this returns and moves the player, screen and
 * parser back four pages; Sonic's own world-x records move with them. */
static int sonic_loopback_hook(uint16_t addr)
{
    (void)addr;
    if (!sonic_selected_player()) return 0;
    game_smash64_sonic_shift_world_x(SMB1_LOOPBACK_DX);
    shift_adapter_world_x(SMB1_LOOPBACK_DX);
    game_sonic_shift_world_x(SMB1_LOOPBACK_DX);
    return 0;
}

/* -------------------------------------------------------- brick debris -- */

void game_sonic_adapter_spawn_brick_debris(int tile_x, int tile_top)
{
    SonicBrickDebris *d = NULL;

    if (!s_enabled || tile_x < 0 || tile_top < 0x20 || tile_top > 0xE0) return;
    for (int i = 0; i < SONIC_BRICK_DEBRIS_MAX; ++i) {
        if (!s_debris[i].active) {
            d = &s_debris[i];
            break;
        }
    }
    if (!d) {
        /* Full: the oldest pair is the one nearest the bottom of the screen. */
        d = &s_debris[0];
        for (int i = 1; i < SONIC_BRICK_DEBRIS_MAX; ++i)
            if (s_debris[i].row[0].y_pos > d->row[0].y_pos) d = &s_debris[i];
    }
    memset(d, 0, sizeof(*d));
    d->active = 1;
    /* SpawnBrickChunks: X speed $F0 for both pairs, Y speed $FA for the top
     * pair and $FC for the pair 8px lower, move forces cleared. */
    d->orig_x = (int16_t)tile_x;
    d->x = (int16_t)tile_x;
    d->row[0].y_pos = (uint8_t)tile_top;
    d->row[0].y_high = 1;
    d->row[0].y_speed = 0xFA;
    d->row[1].y_pos = (uint8_t)(tile_top + 8);
    d->row[1].y_high = 1;
    d->row[1].y_speed = 0xFC;
}

const SonicBrickDebris *game_sonic_adapter_brick_debris(void)
{
    return s_debris;
}

/* ImposeGravityBlock: ImposeGravity with a $50 downward force, maximum
 * speed MaxSpdBlockData+1 ($08) and no upward force. */
static void brick_chunk_gravity(SonicBrickChunkRow *r)
{
    game_sonic_items_impose_gravity(r, 0x50, 0x08);
}

static void update_brick_debris(void)
{
    if (g_ram[OperMode_Task] != 3) {
        memset(s_debris, 0, sizeof(s_debris));
        return;
    }
    if (g_ram[GamePauseStatus] & 0x01) return;
    for (int i = 0; i < SONIC_BRICK_DEBRIS_MAX; ++i) {
        SonicBrickDebris *d = &s_debris[i];
        if (!d->active) continue;
        /* BlockObjectsCore, chunk path: gravity then MoveObjectHorizontally
         * for each pair. X speed $F0 is exactly -1 pixel per frame. */
        brick_chunk_gravity(&d->row[0]);
        brick_chunk_gravity(&d->row[1]);
        d->x = (int16_t)(d->x - 1);
        if (d->row[1].y_pos > 0xF0) d->row[1].y_pos = 0xF0;
        if (d->row[0].y_pos >= 0xF0) d->active = 0;
    }
}

/* --------------------------------------------------------- area parser -- */

/* Commit VRAM_Buffer2 straight into nametable RAM, exactly as the NMI's
 * UpdateScreen would, then reinitialize the buffer as NMI does. Writing the
 * nametable directly leaves the PPU address and scroll latches untouched. */
static void flush_vram_buffer2(void)
{
    unsigned i = 0;
    const int mirroring = mapper_get_mirroring();

    if (g_ram[VRAM_Buffer_AddrCtrl] != 0x06) return;
    while (i < 0xB0) {
        const uint8_t hi = g_ram[VRAM_Buffer2 + i];
        uint16_t a;
        uint8_t ctl, count;
        int vertical, repeat;

        if (hi == 0) break;
        a = (uint16_t)(((uint16_t)hi << 8) | g_ram[VRAM_Buffer2 + i + 1]);
        ctl = g_ram[VRAM_Buffer2 + i + 2];
        vertical = (ctl & 0x80) != 0;
        repeat = (ctl & 0x40) != 0;
        count = (uint8_t)(ctl & 0x3F);
        if (count == 0) count = 0x40;
        i += 3;
        for (unsigned n = 0; n < count; ++n) {
            const uint8_t v = g_ram[VRAM_Buffer2 + i + (repeat ? 0 : n)];
            uint16_t aa = (uint16_t)(a & 0x3FFF);
            if (aa >= 0x2000 && aa < 0x3F00) {
                int vnt = ((aa - 0x2000) / 0x400) & 3;
                int pnt = mirroring == 0 ? 0 : mirroring == 1 ? 1 :
                          mirroring == 3 ? (vnt >> 1) : (vnt & 1);
                g_ppu_nt[pnt * 0x400 + (aa & 0x3FF)] = v;
            }
            a = (uint16_t)(a + (vertical ? 32 : 1));
        }
        i += repeat ? 1u : count;
    }
    g_ram[VRAM_Buffer2_Offset] = 0;
    g_ram[VRAM_Buffer2] = 0;
    g_ram[VRAM_Buffer_AddrCtrl] = 0;
}

/* UpdScrollVar services one AreaParserTaskHandler task per frame: 32px of
 * new world per eight frames, 4px/frame. S3K Sonic scrolls up to 16px/frame,
 * so after each guest frame keep running UpdScrollVar's own logic until the
 * parser has caught up with ScrollThirtyTwo. Each task's VRAM_Buffer2 output
 * is committed before the next, because the buffer holds exactly one column
 * before it would run into BowserBodyControls at $0363. */
static void service_area_parser(void)
{
    int tasks = 0;

    if (g_ram[OperMode] != 1 || g_ram[OperMode_Task] != 3) return;
    if (g_ram[GamePauseStatus] & 0x01) return;

    runtime_begin_unclocked();
    flush_vram_buffer2();
    while (tasks < 24) {
        CPU6502State save;
        if (g_ram[AreaParserTaskNum] == 0) {
            if (g_ram[ScrollThirtyTwo] < 0x20) break;
            g_ram[ScrollThirtyTwo] = (uint8_t)(g_ram[ScrollThirtyTwo] - 0x20);
            g_ram[VRAM_Buffer2_Offset] = 0;
        }
        save = g_cpu;
        AreaParserTaskHandler();
        g_cpu = save;
        flush_vram_buffer2();
        tasks++;
    }
    runtime_end_unclocked();
}

/* ------------------------------------------------------------- frame -- */

/* A PH stderr line whenever the body SMB1 collides for Sonic (Big Mario's
 * x+$02..x+$0D, from the head probe's row to the pixel above the feet) sits
 * deep inside a tile a body cannot share. A head bump or a wall contact
 * reaches a few pixels in; only a collision bug gets further. */
static void debug_phasing(uint64_t frame)
{
    const int x = player_world_x();
    const int y = (int)g_ram[Player_Y_Position];
    const int top = y + (game_sonic_adapter_low_profile() ? 0x12 : 0x04);
    const int bottom = y + 0x1F;
    const int left = x + 0x02;
    const int right = x + 0x0D;

    if (g_ram[OperMode] != 1 || g_ram[Player_Y_HighPos] != 1 ||
        g_ram[GameEngineSubroutine] != SMB1_GAMEMODE_PLAYER_CTRL)
        return;
    for (int tile_top = 0x20; tile_top <= 0xE0; tile_top += 16) {
        const int oy = (bottom < tile_top + 15 ? bottom : tile_top + 15) -
                       (top > tile_top ? top : tile_top) + 1;
        if (oy < 1) continue;
        for (int col = left >> 4; col <= right >> 4; ++col) {
            const int ox = (right < col * 16 + 15 ? right : col * 16 + 15) -
                           (left > col * 16 ? left : col * 16) + 1;
            const uint8_t tile = block_at(col * 16, tile_top);
            /* A bouncing block is there even where its cell reads as air. */
            const int bouncing = game_sonic_items_cell_bouncing(
                (uint8_t)(((col & 0x10) ? 0xD0 : 0x00) | (col & 0x0F)),
                (uint8_t)(tile_top - 0x20));
            if (ox < 1 || (!metatile_is_floor(tile) && !bouncing)) continue;
            /* OV: any overlap at all with a block as the buffer has it now,
             * but the pixel a bumping head is parked in. */
            if (!(oy == 1 && top == tile_top + 15))
                fprintf(stderr, "OV %llu col=%X row=%d tile=%02X ox=%d oy=%d "
                                "x=%d y=%d\n",
                        (unsigned long long)frame, col, (tile_top - 0x20) >> 4,
                        tile, ox, oy, x, y);
            if (ox < 4 || oy < 9) continue;
            fprintf(stderr, "PH %llu col=%X row=%d tile=%02X%s ox=%d oy=%d "
                            "x=%d y=%d\n",
                    (unsigned long long)frame, col, (tile_top - 0x20) >> 4,
                    tile, bouncing ? " bouncing" : "", ox, oy, x, y);
        }
    }
}

/* One SD stderr line per guest frame with the player, camera and platform
 * bytes the Sonic host paths negotiate over. */
static void debug_frame(uint64_t frame)
{
    const S3KPlayer *p = s3k_sonic_player();
    if (!sonic_debug_enabled()) return;
    fprintf(stderr, "SD %llu x=%d y=%d/%d scr=%d st=%d eng=%d pxs=%d plx=%d "
            "lk=%d sct=%d pfs=%d xv=%d yv=%d gv=%d s=%02X s2=%02X an=%02X rt=%d "
            "tb=%d dp=%d dj=%d |",
            (unsigned long long)frame, player_world_x(),
            (int)(int8_t)g_ram[Player_Y_HighPos], g_ram[Player_Y_Position],
            ((int)g_ram[ScreenLeft_PageLoc] << 8) | g_ram[ScreenLeft_X_Pos],
            g_ram[Player_State], g_ram[GameEngineSubroutine],
            (int)(int8_t)g_ram[Player_X_Scroll],
            (int)(int8_t)g_ram[Platform_X_Scroll], g_ram[ScrollLock],
            g_ram[SideCollisionTimer], g_ram[Player_Pos_ForScroll],
            p->x_vel, p->y_vel,
            p->ground_vel, p->status, p->status_secondary, p->anim,
            p->routine, s_tunnel_ball, s_dash_plow, p->double_jump_flag);
    for (int i = 0; i < 6; ++i) {
        if (!g_ram[Enemy_Flag + i]) continue;
        fprintf(stderr, " %d:%02X@%d,%d/%d st%02X pc%02X", i,
                g_ram[Enemy_ID + i],
                ((int)g_ram[Enemy_PageLoc + i] << 8) | g_ram[Enemy_X_Position + i],
                (int)(int8_t)g_ram[Enemy_Y_HighPos + i],
                g_ram[Enemy_Y_Position + i], g_ram[Enemy_State + i],
                g_ram[PlatformCollisionFlag + i]);
    }
    /* Block objects: SMB1's two slots (SprObject 9/10) and the host pool,
     * with the cell each one owns (buffer low byte, row offset). */
    for (int s = 0; s < 2; ++s) {
        if (!g_ram[Block_State + s] && !g_ram[Block_RepFlag + s]) continue;
        fprintf(stderr, " B%d:st%02X rf%d mt%02X@%d,%d cell%02X/%02X", s,
                g_ram[Block_State + s], g_ram[Block_RepFlag + s],
                g_ram[Block_Metatile + s],
                ((int)g_ram[0x006D + 9 + s] << 8) | g_ram[0x0086 + 9 + s],
                g_ram[0x00CE + 9 + s], g_ram[Block_BBuf_Low + s],
                g_ram[Block_Orig_YPos + s]);
    }
    {
        const SonicItems *items = game_sonic_items();
        for (int i = 0; i < SONIC_BUMP_BLOCK_MAX; ++i) {
            const SonicBumpBlock *b = &items->blocks[i];
            if (!b->active) continue;
            fprintf(stderr, " P%d:a%d mt%02X@%d,%d cell%02X/%02X", i,
                    b->active, b->metatile, b->x, b->row.y_pos, b->bbuf_low,
                    b->orig_ypos);
        }
    }
    fputc('\n', stderr);
    debug_phasing(frame);
}

void game_sonic_adapter_post_frame(uint64_t frame)
{
    if (!s_enabled) return;
    debug_frame(frame);

    if (g_ram[OperMode] != 1) {
        s3k_rings_clear(&s_rings);
        memset(s_debris, 0, sizeof(s_debris));
        game_sonic_items_clear();
        s_prev_coins_valid = 0;
        s_tunnel_ball = 0;
        s_dash_plow = 0;
        s_platform_riders = 0;
        return;
    }
    /* A slot's next platform starts unchecked: a platform is erased in its
     * own turn of the enemy loop, and its slot refilled on a later frame. */
    for (int slot = 0; slot < 6; ++slot)
        if (!slot_is_platform(slot)) set_platform_rider(slot, 0);
    if (g_ram[GameEngineSubroutine] != SMB1_GAMEMODE_PLAYER_CTRL) {
        /* A scripted sequence (pipe, flagpole, death) ends both. */
        s_tunnel_ball = 0;
        s_dash_plow = 0;
    }
    keep_sonic_on_screen();
    update_brick_debris();
    game_sonic_items_post_frame();

    if (s_hazard_pending) {
        s_hazard_pending = 0;
        if (nes_foreign_ownership() == FOREIGN_OWNERSHIP_FOREIGN &&
            g_ram[GameEngineSubroutine] == SMB1_GAMEMODE_PLAYER_CTRL &&
            !(s_hazard_fire && s3k_sonic_has_fire_shield()))
            sonic_take_hit(s_hazard_world_x);
    }

    /* Rings do not survive Sonic: S3K respawns him with none. */
    if (g_ram[GameEngineSubroutine] == 0x0B ||
        g_ram[GameEngineSubroutine] == 0x06) {
        if (!s_death_coins_cleared) {
            s_death_coins_cleared = 1;
            s3k_rings_clear(&s_rings);
            if (g_ram[CoinTally]) clear_coins();
        }
    } else if (g_ram[GameEngineSubroutine] == SMB1_GAMEMODE_PLAYER_CTRL) {
        s_death_coins_cleared = 0;
    }

    update_rings();
    update_coin_sounds();
    game_sonic_adapter_play_sfx(frame);
    service_area_parser();
}

const S3KRingSpill *game_sonic_adapter_rings(void)
{
    return &s_rings;
}

void game_sonic_adapter_load_owner_data(const uint8_t *rom, size_t size)
{
    /* SineTable (Levels/Misc/sine.bin) in the S&K half of the lock-on ROM. */
    const size_t off = 0x1D64u;
    s_sine_ready = 0;
    if (!rom || size < off + sizeof(s_sine)) return;
    for (unsigned i = 0; i < 320u; ++i)
        s_sine[i] = (int16_t)(uint16_t)((rom[off + i * 2u] << 8) |
                                        rom[off + i * 2u + 1u]);
    s_sine_ready = s_sine[0x40] == 0x100 && s_sine[0x80] == 0 &&
                   s_sine[0xC0] == -0x100;
}

void game_sonic_adapter_set_enabled(int enabled)
{
    s_enabled = enabled != 0;
    s_force_native_injury = 0;
    s_hazard_pending = 0;
    s_diag_power = -1;
    s_diag_speed = 0;
    s3k_rings_clear(&s_rings);
    memset(s_debris, 0, sizeof(s_debris));
    s_prev_coins_valid = 0;
    s_death_coins_cleared = 0;
    s_tunnel_ball = 0;
    s_dash_plow = 0;
    s_platform_riders = 0;
    if (s_enabled) {
        const char *e = getenv("NESRECOMP_SONIC_DIAG_POWER");
        if (e && (*e == '0' || *e == '1' || *e == '2') && !e[1]) {
            s_diag_power = *e - '0';
            fprintf(stderr, "[S3&K] DIAGNOSTIC: PlayerStatus forced to %d "
                            "(NESRECOMP_SONIC_DIAG_POWER) - this run is not "
                            "representative of normal play\n", s_diag_power);
        }
    }
    if (s_enabled) {
        const char *e = getenv("NESRECOMP_SONIC_DIAG_SPEED");
        if (e && *e) {
            const long speed = strtol(e, NULL, 16);
            if (speed > 0 && speed <= 0x1000) {
                s_diag_speed = (int)speed;
                fprintf(stderr, "[S3&K] DIAGNOSTIC: ground speed $%X with Right "
                                "held (NESRECOMP_SONIC_DIAG_SPEED) - this run is "
                                "not representative of normal play\n",
                        s_diag_speed);
            }
        }
    }
    nes_mod_set_function_hook_enabled(SONIC_CONTACT_HOOK_ID, s_enabled);
    nes_mod_set_function_hook_enabled(SONIC_POWERUP_HOOK_ID, s_enabled);
    nes_mod_set_function_hook_enabled(SONIC_WHIRLPOOL_HOOK_ID, s_enabled);
    nes_mod_set_function_hook_enabled(SONIC_LARGE_PLATFORM_HOOK_ID, s_enabled);
    nes_mod_set_function_hook_enabled(SONIC_SMALL_PLATFORM_HOOK_ID, s_enabled);
    nes_mod_set_function_hook_enabled(SONIC_LOOPBACK_HOOK_ID, s_enabled);
    game_sonic_items_set_enabled(s_enabled);
}

typedef struct SonicAdapterSave {
    uint8_t version;
    uint8_t hazard_pending;
    uint8_t hazard_fire;
    uint8_t prev_coins;
    uint8_t prev_coins_valid;
    uint8_t death_coins_cleared;
    uint8_t pad[2];
    int32_t hazard_world_x;
    S3KRingSpill rings;
    /* Version 3 appends the brick debris; a version 2 record ends here. */
    SonicBrickDebris debris[SONIC_BRICK_DEBRIS_MAX];
    /* Version 4 appends the tunnel ball and dash plow; a version 3 record
     * ends here. Version 5 uses the first pad byte for the platform riders. */
    uint8_t tunnel_ball;
    uint8_t dash_plow;
    uint8_t platform_riders;
    uint8_t pad2;
    /* Version 6 appends the host's camera history and sub-pixels, and the
     * pooled blocks, coins and power-ups; a version 4 or 5 record ends here. */
    SonicHostSave host;
    SonicItems items;
} SonicAdapterSave;

#define SONIC_ADAPTER_SAVE_V2_SIZE offsetof(SonicAdapterSave, debris)
#define SONIC_ADAPTER_SAVE_V3_SIZE offsetof(SonicAdapterSave, tunnel_ball)
#define SONIC_ADAPTER_SAVE_V5_SIZE offsetof(SonicAdapterSave, host)

static int adapter_save_get(uint8_t *buf, int cap)
{
    SonicAdapterSave save;
    if (!s_enabled) return 0;
    if (cap < (int)sizeof(save)) return -1;
    memset(&save, 0, sizeof(save));
    save.version = 6;
    save.hazard_pending = (uint8_t)s_hazard_pending;
    save.hazard_fire = (uint8_t)s_hazard_fire;
    save.prev_coins = s_prev_coins;
    save.prev_coins_valid = (uint8_t)s_prev_coins_valid;
    save.death_coins_cleared = (uint8_t)s_death_coins_cleared;
    save.hazard_world_x = s_hazard_world_x;
    save.rings = s_rings;
    memcpy(save.debris, s_debris, sizeof(s_debris));
    save.tunnel_ball = s_tunnel_ball;
    save.dash_plow = s_dash_plow;
    save.platform_riders = s_platform_riders;
    game_smash64_sonic_save_host(&save.host);
    game_sonic_items_save(&save.items);
    memcpy(buf, &save, sizeof(save));
    return (int)sizeof(save);
}

static int adapter_save_set(const uint8_t *buf, int len)
{
    SonicAdapterSave save;
    game_sonic_note_state_loaded();
    /* Whatever the record holds, nothing from before the load may survive
     * in the host: an older record starts it as a fresh session would. */
    game_smash64_sonic_load_host(NULL);
    game_sonic_items_load(NULL);
    if (len == 0) return 1;
    memset(&save, 0, sizeof(save));
    if (len == (int)SONIC_ADAPTER_SAVE_V2_SIZE) {
        memcpy(&save, buf, SONIC_ADAPTER_SAVE_V2_SIZE);
        if (save.version != 2) return 0;
    } else if (len == (int)SONIC_ADAPTER_SAVE_V3_SIZE) {
        memcpy(&save, buf, SONIC_ADAPTER_SAVE_V3_SIZE);
        if (save.version != 3) return 0;
    } else if (len == (int)SONIC_ADAPTER_SAVE_V5_SIZE) {
        memcpy(&save, buf, SONIC_ADAPTER_SAVE_V5_SIZE);
        if (save.version != 4 && save.version != 5) return 0;
    } else if (len == (int)sizeof(save)) {
        memcpy(&save, buf, sizeof(save));
        if (save.version != 6) return 0;
    } else {
        return 0;
    }
    for (int i = 0; i < S3K_RING_SPILL_MAX; ++i)
        if (save.rings.rings[i].state > S3K_RING_SPARKLE) return 0;
    for (int i = 0; i < SONIC_BRICK_DEBRIS_MAX; ++i)
        save.debris[i].active = save.debris[i].active != 0;
    memcpy(s_debris, save.debris, sizeof(s_debris));
    s_hazard_pending = save.hazard_pending != 0;
    s_hazard_fire = save.hazard_fire != 0;
    s_prev_coins = save.prev_coins;
    s_prev_coins_valid = save.prev_coins_valid != 0;
    s_death_coins_cleared = save.death_coins_cleared != 0;
    s_hazard_world_x = save.hazard_world_x;
    s_rings = save.rings;
    s_tunnel_ball = save.tunnel_ball != 0;
    s_dash_plow = save.dash_plow <= SONIC_DASH_PLOW_FRAMES ? save.dash_plow : 0;
    if (save.version >= 5) {
        s_platform_riders = (uint8_t)(save.platform_riders & 0x3F);
    } else {
        /* Older records: trust the flags the platforms left last frame. */
        s_platform_riders = 0;
        for (int slot = 0; slot < 6; ++slot) {
            const uint8_t flag = g_ram[PlatformCollisionFlag + slot];
            if (slot_is_platform(slot) &&
                (g_ram[Enemy_ID + slot] <= 0x2A ? flag != 0xFF : flag != 0))
                set_platform_rider(slot, 1);
        }
    }
    if (save.version >= 6) {
        game_smash64_sonic_load_host(&save.host);
        game_sonic_items_load(&save.items);
    }
    return 1;
}

int game_sonic_adapter_register_hooks(void)
{
    int ok = nes_mod_register_function_entry_plugin(
        SONIC_CONTACT_HOOK_ID, SMB1_PLAYER_ENEMY_COLLISION_ADDR,
        sonic_contact_hook);
    ok &= nes_mod_register_function_entry_plugin(
        SONIC_POWERUP_HOOK_ID, SMB1_POWERUP_COLLISION_ADDR,
        sonic_powerup_hook);
    ok &= nes_mod_register_function_entry_plugin(
        SONIC_WHIRLPOOL_HOOK_ID, SMB1_PROCESS_WHIRLPOOLS_ADDR,
        sonic_whirlpool_hook);
    ok &= nes_mod_register_function_entry_plugin(
        SONIC_LARGE_PLATFORM_HOOK_ID, SMB1_LARGE_PLATFORM_COLLISION_ADDR,
        sonic_large_platform_hook);
    ok &= nes_mod_register_function_entry_plugin(
        SONIC_SMALL_PLATFORM_HOOK_ID, SMB1_SMALL_PLATFORM_COLLISION_ADDR,
        sonic_small_platform_hook);
    ok &= nes_mod_register_function_entry_plugin(
        SONIC_LOOPBACK_HOOK_ID, SMB1_EXEC_GAME_LOOPBACK_ADDR,
        sonic_loopback_hook);
    ok &= game_sonic_items_register_hooks();
    ok &= nes_mod_register_savestate_hook(SONIC_ADAPTER_SAVE_ID,
                                          adapter_save_get, adapter_save_set);
    return ok;
}
