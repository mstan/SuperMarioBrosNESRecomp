/*
 * game_sonic_items.c -- SMB1's block objects, jumping coins and power-ups
 * beyond SMB1's own slots, while Sonic is the player.
 *
 * SMB1 bounces at most two blocks at once (its two block-object slots),
 * shows at most three coins jumping out of blocks (misc slots 6-8), and has
 * one power-up slot (enemy slot 5), so a second item out of a block replaces
 * the first. Sonic's spindash and roll hit blocks far faster than a head
 * can, so the blocks and coins his host hits set up move into pools of their
 * own, and a power-up a newer item would replace moves into a pool instead of
 * vanishing. SMB1's own slots are left exactly as they were.
 *
 * Every pooled object keeps SMB1's behaviour:
 *   blocks    BouncingBlockHandler's ImposeGravityBlock step, then the
 *             metatile write of BlockObjMT_Updater; drawn as DrawBlock does
 *   coins     ProcJumpCoin (JCoinRun, then the floatey "200"), drawn as
 *             JCoinGfxHandler does
 *   power-ups PowerUpObjHandler itself, run with the pooled object swapped
 *             into enemy slot 5; the sprites DrawPowerUp wrote are captured
 *             for the presentation to draw
 */
#include "game_sonic_items.h"

#include "game_smash64.h"

#include "mod_function_hooks.h"
#include "nes_runtime.h"

#include "generated/super-mario-bros_full_decls.h"

#include <string.h>

#define SONIC_SETUP_POWERUP_HOOK_ID "super-mario-bros.s3k.setup-powerup"
#define SONIC_SETUP_VINE_HOOK_ID "super-mario-bros.s3k.setup-vine"
#define SMB1_SETUP_POWERUP_ADDR 0xBC49
#define SMB1_SETUP_VINE_ADDR 0xB91E

/* SprObject arrays: blocks are objects 9-10 (Block_*), misc objects 13-21. */
#define SPROBJ_X_SPEED     0x0057
#define SPROBJ_PAGELOC     0x006D
#define SPROBJ_X_POSITION  0x0086
#define SPROBJ_Y_SPEED     0x009F
#define SPROBJ_Y_HIGHPOS   0x00B5
#define SPROBJ_Y_POSITION  0x00CE
#define SPROBJ_YMF_DUMMY   0x0416
#define SPROBJ_Y_MOVEFORCE 0x0433
#define BLOCK_OBJ(s)       (9 + (s))
#define MISC_OBJ(y)        (13 + (y))
#define JUMP_COIN_SLOT_FIRST 6    /* FindEmptyMiscSlot looks at 8, 7, 6 */

static int s_enabled;
static SonicItems s_items;
/* PowerUpType of the power-up in enemy slot 5. The global is the type of the
 * newest power-up, but MushFlowerBlock/StarBlock/ExtraLifeMushBlock store the
 * NEXT item's type before they jump to SetupPowerUp, so by that hook the live
 * item's own type is gone. SetupPowerUp is the only other writer. */
static uint8_t s_slot5_type;
#define POWERUP_TYPE_BYTE (SONIC_POWERUP_BYTES - 1)

static const uint16_t k_powerup_addrs[SONIC_POWERUP_BYTES] = {
    Enemy_Flag + 5, Enemy_ID + 5, Enemy_State + 5, Enemy_MovingDir + 5,
    Enemy_X_Speed + 5, Enemy_PageLoc + 5, Enemy_X_Position + 5,
    Enemy_Y_Speed + 5, Enemy_Y_HighPos + 5, Enemy_Y_Position + 5,
    Enemy_SprAttrib + 5, EnemyOffscrBitsMasked + 5, Enemy_X_MoveForce + 5,
    Enemy_YMF_Dummy + 5, Enemy_Y_MoveForce + 5, Enemy_CollisionBits + 5,
    Enemy_BoundBoxCtrl + 5, EnemyFrameTimer + 5, EnemyIntervalTimer + 5,
    BoundingBox_UL_XPos + 24, BoundingBox_UL_YPos + 24,
    BoundingBox_DR_XPos + 24, BoundingBox_DR_YPos + 24, PowerUpType,
};

/* --------------------------------------------------------------- gravity -- */

void game_sonic_items_impose_gravity(SonicBrickChunkRow *r, uint8_t down,
                                     uint8_t max)
{
    unsigned sum;
    uint8_t carry, high_adder;

    sum = (unsigned)r->ymf_dummy + r->y_force;
    r->ymf_dummy = (uint8_t)sum;
    carry = (uint8_t)(sum >> 8);
    high_adder = (r->y_speed & 0x80) ? 0xFF : 0x00;
    sum = (unsigned)r->y_pos + r->y_speed + carry;
    r->y_pos = (uint8_t)sum;
    carry = (uint8_t)(sum >> 8);
    r->y_high = (uint8_t)(r->y_high + high_adder + carry);
    sum = (unsigned)r->y_force + down;
    r->y_force = (uint8_t)sum;
    r->y_speed = (uint8_t)(r->y_speed + (sum >> 8));
    /* cmp $02 / bmi: the N flag of the 8-bit difference. */
    if (!((uint8_t)(r->y_speed - max) & 0x80) && r->y_force >= 0x80) {
        r->y_speed = max;
        r->y_force = 0x00;
    }
}

/* ---------------------------------------------------------------- blocks -- */

/* BlockObjMT_Updater for one pooled block: the metatile goes back into the
 * block buffer and, through WriteBlockMetatile, the name table. Returns 0
 * while the VRAM buffer has no room this frame. A block whose buffer column
 * the area parser has since reused for newer level (32 columns on) is
 * dropped: that cell is no longer its own. */
static int put_block_back(const SonicBumpBlock *b)
{
    const int parser_col = ((int)g_ram[CurrentPageLoc] << 4) |
                           (int)g_ram[CurrentColumnPos];
    const uint16_t cell = (uint16_t)(0x0500 + b->bbuf_low + b->orig_ypos);
    CPU6502State save_cpu;
    uint8_t save_scratch[8];

    if (((parser_col - (b->x >> 4)) & 0xFFF) >= 32) return 1;
    if (g_ram[VRAM_Buffer1_Offset] > 0x28) return 0;
    save_cpu = g_cpu;
    memcpy(save_scratch, &g_ram[0x00], sizeof save_scratch);
    g_ram[0x02] = b->orig_ypos;
    g_ram[0x06] = b->bbuf_low;
    g_ram[0x07] = 0x05;
    g_ram[cell] = b->metatile;
    g_cpu.A = b->metatile;
    g_cpu.X = 0;
    WriteBlockMetatile();
    memcpy(&g_ram[0x00], save_scratch, sizeof save_scratch);
    g_cpu = save_cpu;
    return 1;
}

static void update_blocks(void)
{
    for (int i = 0; i < SONIC_BUMP_BLOCK_MAX; ++i) {
        SonicBumpBlock *b = &s_items.blocks[i];
        if (b->active >= 2) {
            /* Settled last frame: BlockObjMT_Updater runs first. */
            b->active = put_block_back(b) ? 0 : 3;
        } else if (b->active == 1) {
            /* BouncingBlockHandler: ImposeGravityBlock ($50, maximum $08),
             * drawn, and settled once the low nybble is back under 5. */
            game_sonic_items_impose_gravity(&b->row, 0x50, 0x08);
            if ((b->row.y_pos & 0x0F) < 5) b->active = 2;
        }
    }
}

int game_sonic_items_owns_cell(uint8_t bbuf_low, uint8_t row)
{
    for (int i = 0; i < SONIC_BUMP_BLOCK_MAX; ++i) {
        const SonicBumpBlock *b = &s_items.blocks[i];
        if (b->active && b->bbuf_low == bbuf_low && b->orig_ypos == row)
            return 1;
    }
    return 0;
}

int game_sonic_items_cell_bouncing(uint8_t bbuf_low, uint8_t row)
{
    for (int s = 0; s < 2; ++s) {
        /* A bouncing block ($x1), or one settled and waiting for
         * BlockObjMT_Updater to put back a non-blank metatile; brick chunks
         * put back blank. */
        const int bouncing = (g_ram[Block_State + s] & 0x0F) == 1 ||
                             (g_ram[Block_RepFlag + s] && g_ram[Block_Metatile + s]);
        if (bouncing && g_ram[Block_BBuf_Low + s] == bbuf_low &&
            g_ram[Block_Orig_YPos + s] == row)
            return 1;
    }
    return game_sonic_items_owns_cell(bbuf_low, row);
}

static SonicBumpBlock *new_block(void)
{
    SonicBumpBlock *oldest = &s_items.blocks[0];
    for (int i = 0; i < SONIC_BUMP_BLOCK_MAX; ++i) {
        SonicBumpBlock *b = &s_items.blocks[i];
        if (!b->active) return b;
        if (b->row.y_pos > oldest->row.y_pos) oldest = b;
    }
    /* Full: the block furthest down its bounce settles now. */
    if (!put_block_back(oldest))
        g_ram[(uint16_t)(0x0500 + oldest->bbuf_low + oldest->orig_ypos)] =
            oldest->metatile;
    return oldest;
}

/* ----------------------------------------------------------------- coins -- */

static void update_coins(void)
{
    for (int i = 0; i < SONIC_JUMP_COIN_MAX; ++i) {
        SonicJumpCoin *c = &s_items.coins[i];
        if (!c->state) continue;
        if (c->state == 1) {
            /* JCoinRun: gravity $50 down, maximum speed $06; falling at 5
             * it becomes the floatey number. */
            game_sonic_items_impose_gravity(&c->row, 0x50, 0x06);
            if (c->row.y_speed == 0x05) c->state++;
        } else {
            /* The number rides the scroll, so it stays put on screen. */
            c->state++;
            c->x = (int16_t)(c->x + g_ram[ScrollAmount]);
            if (c->state == 0x30) {
                c->state = 0;
                continue;
            }
        }
        /* DrawFloateyNumber_Coin raises it a line every other frame. */
        if (c->state >= 2 && !(g_ram[FrameCounter] & 0x01)) c->row.y_pos--;
    }
}

static SonicJumpCoin *new_coin(void)
{
    SonicJumpCoin *latest = &s_items.coins[0];
    for (int i = 0; i < SONIC_JUMP_COIN_MAX; ++i) {
        SonicJumpCoin *c = &s_items.coins[i];
        if (!c->state) return c;
        if (c->state > latest->state) latest = c;
    }
    return latest;   /* full: the number closest to disappearing */
}

/* ------------------------------------------------------------- host hits -- */

#define BLOCK_BYTES 13
#define MISC_BYTES 6

static struct {
    uint8_t slot;
    uint8_t ctrl;
    uint8_t bounce_timer;
    uint8_t coin_offset;
    uint8_t block[BLOCK_BYTES];
    uint8_t misc[3][MISC_BYTES];
} s_hit;

static void block_slot_addrs(int s, uint16_t *a)
{
    a[0] = (uint16_t)(Block_State + s);
    a[1] = (uint16_t)(Block_RepFlag + s);
    a[2] = (uint16_t)(Block_Orig_YPos + s);
    a[3] = (uint16_t)(Block_BBuf_Low + s);
    a[4] = (uint16_t)(Block_Metatile + s);
    a[5] = (uint16_t)(Block_PageLoc2 + s);
    a[6] = (uint16_t)(SPROBJ_X_SPEED + BLOCK_OBJ(s));
    a[7] = (uint16_t)(SPROBJ_PAGELOC + BLOCK_OBJ(s));
    a[8] = (uint16_t)(SPROBJ_X_POSITION + BLOCK_OBJ(s));
    a[9] = (uint16_t)(SPROBJ_Y_SPEED + BLOCK_OBJ(s));
    a[10] = (uint16_t)(SPROBJ_Y_HIGHPOS + BLOCK_OBJ(s));
    a[11] = (uint16_t)(SPROBJ_Y_POSITION + BLOCK_OBJ(s));
    a[12] = (uint16_t)(SPROBJ_Y_MOVEFORCE + BLOCK_OBJ(s));
}

static void misc_slot_addrs(int y, uint16_t *a)
{
    a[0] = (uint16_t)(Misc_State + y);
    a[1] = (uint16_t)(SPROBJ_PAGELOC + MISC_OBJ(y));
    a[2] = (uint16_t)(SPROBJ_X_POSITION + MISC_OBJ(y));
    a[3] = (uint16_t)(SPROBJ_Y_SPEED + MISC_OBJ(y));
    a[4] = (uint16_t)(SPROBJ_Y_HIGHPOS + MISC_OBJ(y));
    a[5] = (uint16_t)(SPROBJ_Y_POSITION + MISC_OBJ(y));
}

void game_sonic_items_begin_host_hit(void)
{
    uint16_t a[BLOCK_BYTES];

    /* PlayerHeadCollision fills the block slot SprDataOffset_Ctrl names and
     * FindEmptyMiscSlot takes the first free of misc slots 8, 7, 6. */
    s_hit.ctrl = g_ram[SprDataOffset_Ctrl];
    s_hit.slot = (uint8_t)(s_hit.ctrl & 1);
    s_hit.bounce_timer = g_ram[BlockBounceTimer];
    s_hit.coin_offset = g_ram[JumpCoinMiscOffset];
    block_slot_addrs(s_hit.slot, a);
    for (int i = 0; i < BLOCK_BYTES; ++i) s_hit.block[i] = g_ram[a[i]];
    g_ram[Block_State + s_hit.slot] = 0;
    g_ram[Block_RepFlag + s_hit.slot] = 0;
    for (int k = 0; k < 3; ++k) {
        uint16_t m[MISC_BYTES];
        misc_slot_addrs(JUMP_COIN_SLOT_FIRST + k, m);
        for (int i = 0; i < MISC_BYTES; ++i) s_hit.misc[k][i] = g_ram[m[i]];
        g_ram[Misc_State + JUMP_COIN_SLOT_FIRST + k] = 0;
    }
    g_ram[SprDataOffset_Ctrl] = s_hit.slot;
}

void game_sonic_items_end_host_hit(void)
{
    const int s = s_hit.slot;
    uint16_t a[BLOCK_BYTES];

    if (g_ram[Block_State + s] == 0x11) {
        SonicBumpBlock *b = new_block();
        const int obj = BLOCK_OBJ(s);
        memset(b, 0, sizeof(*b));
        b->active = 1;
        b->metatile = g_ram[Block_Metatile + s];
        b->bbuf_low = g_ram[Block_BBuf_Low + s];
        b->orig_ypos = g_ram[Block_Orig_YPos + s];
        b->x = (int16_t)((g_ram[SPROBJ_PAGELOC + obj] << 8) |
                         g_ram[SPROBJ_X_POSITION + obj]);
        b->row.y_pos = g_ram[SPROBJ_Y_POSITION + obj];
        b->row.y_high = g_ram[SPROBJ_Y_HIGHPOS + obj];
        b->row.y_speed = g_ram[SPROBJ_Y_SPEED + obj];
        b->row.y_force = g_ram[SPROBJ_Y_MOVEFORCE + obj];
        b->row.ymf_dummy = g_ram[SPROBJ_YMF_DUMMY + obj];
    }
    for (int k = 2; k >= 0; --k) {
        const int y = JUMP_COIN_SLOT_FIRST + k;
        const int obj = MISC_OBJ(y);
        uint16_t m[MISC_BYTES];
        if (g_ram[Misc_State + y] == 1) {
            SonicJumpCoin *c = new_coin();
            memset(c, 0, sizeof(*c));
            c->state = 1;
            c->x = (int16_t)((g_ram[SPROBJ_PAGELOC + obj] << 8) |
                             g_ram[SPROBJ_X_POSITION + obj]);
            c->row.y_pos = g_ram[SPROBJ_Y_POSITION + obj];
            c->row.y_high = g_ram[SPROBJ_Y_HIGHPOS + obj];
            c->row.y_speed = g_ram[SPROBJ_Y_SPEED + obj];
            c->row.y_force = g_ram[SPROBJ_Y_MOVEFORCE + obj];
            c->row.ymf_dummy = g_ram[SPROBJ_YMF_DUMMY + obj];
        }
        misc_slot_addrs(y, m);
        for (int i = 0; i < MISC_BYTES; ++i) g_ram[m[i]] = s_hit.misc[k][i];
    }
    block_slot_addrs(s, a);
    for (int i = 0; i < BLOCK_BYTES; ++i) g_ram[a[i]] = s_hit.block[i];
    g_ram[SprDataOffset_Ctrl] = s_hit.ctrl;
    g_ram[BlockBounceTimer] = s_hit.bounce_timer;
    g_ram[JumpCoinMiscOffset] = s_hit.coin_offset;
}

/* ------------------------------------------------------------- power-ups -- */

static int slot5_holds_power_up(void)
{
    return g_ram[Enemy_Flag + 5] && g_ram[Enemy_ID + 5] == PowerUpObject &&
           g_ram[Enemy_State + 5];
}

/* SetupPowerUp and Setup_Vine write enemy slot 5 whatever it holds. A
 * power-up still out there moves into the pool first. */
static int slot5_setup_hook(uint16_t addr)
{
    const int setup_power_up = addr == SMB1_SETUP_POWERUP_ADDR;
    SonicPowerUp *p = NULL;

    if (!s_enabled || !game_smash64_sonic_selected()) return 0;
    if (slot5_holds_power_up()) {
        for (int i = 0; i < SONIC_POWERUP_MAX && !p; ++i)
            if (!s_items.powerups[i].active) p = &s_items.powerups[i];
        if (!p) {
            /* Full: the oldest pooled item gives way. */
            memmove(&s_items.powerups[0], &s_items.powerups[1],
                    sizeof(s_items.powerups[0]) * (SONIC_POWERUP_MAX - 1));
            p = &s_items.powerups[SONIC_POWERUP_MAX - 1];
        }
        p->active = 1;
        for (int i = 0; i < SONIC_POWERUP_BYTES; ++i)
            p->bytes[i] = g_ram[k_powerup_addrs[i]];
        p->bytes[POWERUP_TYPE_BYTE] = s_slot5_type;
        memset(p->oam, 0xF8, sizeof(p->oam));
    }
    if (setup_power_up) {
        /* SetupPowerUp: a star or 1-up keeps its type; a Mushroom becomes the
         * Fire Flower for a player at PlayerStatus 1 or 2 (lsr of 2). */
        const uint8_t type = g_ram[PowerUpType];
        const uint8_t status = g_ram[PlayerStatus];
        s_slot5_type = type >= 2 ? type : status >= 2 ? (uint8_t)(status >> 1)
                                                      : status;
    }
    return 0;
}

void game_sonic_items_run_power_ups(void)
{
    const uint16_t oam = (uint16_t)(Sprite_Data + g_ram[Enemy_SprDataOffset + 5]);
    uint8_t live[SONIC_POWERUP_BYTES], live_oam[16], scratch[8];
    uint8_t rel_x, rel_y, offscreen, object_offset;
    CPU6502State save_cpu;
    int any = 0;

    for (int i = 0; i < SONIC_POWERUP_MAX; ++i)
        any |= s_items.powerups[i].active;
    if (!s_enabled || !any) return;

    save_cpu = g_cpu;
    memcpy(scratch, &g_ram[0x00], sizeof scratch);
    rel_x = g_ram[Enemy_Rel_XPos];
    rel_y = g_ram[Enemy_Rel_YPos];
    offscreen = g_ram[Enemy_OffscreenBits];
    object_offset = g_ram[ObjectOffset];
    for (int i = 0; i < SONIC_POWERUP_BYTES; ++i)
        live[i] = g_ram[k_powerup_addrs[i]];
    memcpy(live_oam, &g_ram[oam], sizeof live_oam);

    for (int n = 0; n < SONIC_POWERUP_MAX; ++n) {
        SonicPowerUp *p = &s_items.powerups[n];
        if (!p->active) continue;
        for (int i = 0; i < SONIC_POWERUP_BYTES; ++i)
            g_ram[k_powerup_addrs[i]] = p->bytes[i];
        /* A power-up still inside its block draws nothing. */
        for (int i = 0; i < 16; i += 4) g_ram[oam + i] = 0xF8;
        g_cpu.X = 5;
        PowerUpObjHandler__b0();
        for (int i = 0; i < SONIC_POWERUP_BYTES; ++i)
            p->bytes[i] = g_ram[k_powerup_addrs[i]];
        memcpy(p->oam, &g_ram[oam], sizeof p->oam);
        /* Collected (EraseEnemyObject) or gone off screen. */
        p->active = g_ram[Enemy_Flag + 5] && g_ram[Enemy_State + 5];
    }

    for (int i = 0; i < SONIC_POWERUP_BYTES; ++i)
        g_ram[k_powerup_addrs[i]] = live[i];
    memcpy(&g_ram[oam], live_oam, sizeof live_oam);
    g_ram[Enemy_Rel_XPos] = rel_x;
    g_ram[Enemy_Rel_YPos] = rel_y;
    g_ram[Enemy_OffscreenBits] = offscreen;
    g_ram[ObjectOffset] = object_offset;
    memcpy(&g_ram[0x00], scratch, sizeof scratch);
    g_cpu = save_cpu;
}

/* ----------------------------------------------------------------- frame -- */

void game_sonic_items_post_frame(void)
{
    if (!s_enabled) return;
    /* Between frames the global is the live item's type again. */
    s_slot5_type = g_ram[PowerUpType];
    if (g_ram[OperMode] != 1 || g_ram[OperMode_Task] != 3) {
        game_sonic_items_clear();
        return;
    }
    if (g_ram[GamePauseStatus] & 0x01) return;
    update_blocks();
    update_coins();
}

void game_sonic_items_shift_world_x(int dx)
{
    for (int i = 0; i < SONIC_BUMP_BLOCK_MAX; ++i)
        s_items.blocks[i].x = (int16_t)(s_items.blocks[i].x + dx);
    for (int i = 0; i < SONIC_JUMP_COIN_MAX; ++i)
        s_items.coins[i].x = (int16_t)(s_items.coins[i].x + dx);
}

const SonicItems *game_sonic_items(void)
{
    return &s_items;
}

void game_sonic_items_clear(void)
{
    memset(&s_items, 0, sizeof(s_items));
    s_slot5_type = g_ram[PowerUpType];
}

void game_sonic_items_save(SonicItems *out)
{
    *out = s_items;
}

void game_sonic_items_load(const SonicItems *in)
{
    if (!in) {
        game_sonic_items_clear();
        return;
    }
    s_items = *in;
    /* Saves are taken between frames, and RAM is restored first. */
    s_slot5_type = g_ram[PowerUpType];
    for (int i = 0; i < SONIC_BUMP_BLOCK_MAX; ++i)
        if (s_items.blocks[i].active > 3) s_items.blocks[i].active = 0;
    for (int i = 0; i < SONIC_JUMP_COIN_MAX; ++i)
        if (s_items.coins[i].state >= 0x30) s_items.coins[i].state = 0;
    for (int i = 0; i < SONIC_POWERUP_MAX; ++i)
        s_items.powerups[i].active = s_items.powerups[i].active != 0;
}

void game_sonic_items_set_enabled(int enabled)
{
    s_enabled = enabled != 0;
    game_sonic_items_clear();
    nes_mod_set_function_hook_enabled(SONIC_SETUP_POWERUP_HOOK_ID, s_enabled);
    nes_mod_set_function_hook_enabled(SONIC_SETUP_VINE_HOOK_ID, s_enabled);
}

int game_sonic_items_register_hooks(void)
{
    int ok = nes_mod_register_function_entry_plugin(
        SONIC_SETUP_POWERUP_HOOK_ID, SMB1_SETUP_POWERUP_ADDR, slot5_setup_hook);
    ok &= nes_mod_register_function_entry_plugin(
        SONIC_SETUP_VINE_HOOK_ID, SMB1_SETUP_VINE_ADDR, slot5_setup_hook);
    return ok;
}
