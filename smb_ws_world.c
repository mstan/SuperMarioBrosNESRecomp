/* SMB's room compiler feeds a host-owned world cache, never wider PPU RAM.
 * The original bounded area helper is run against private working RAM outside
 * rendering. No CPU/APU time advances; all guest state is restored afterwards.
 * Live streamed columns validate it and preserve later block/coin edits. */
#include "smb_ws_world.h"
#include "nes_runtime.h"
#include "mapper.h"
#include "recomp_stack.h"
#include <string.h>

extern void func_93FC_b0(void); /* AreaParserCore */
extern uint16_t g_rts_target;
SmbWsWorld g_smb_ws_world;
static int s_decoding;

static unsigned area_data(void) { return g_ram[0xe7] | (g_ram[0xe8] << 8); }
static uint8_t rom(unsigned addr) { return mapper_peek_prg((uint16_t)addr); }
static uint8_t tile_for(uint8_t meta, int x, int y) {
    int bank = meta >> 6;
    unsigned table = rom(0x8b08 + bank) | (rom(0x8b0c + bank) << 8);
    return rom(table + (meta & 63) * 4 + x * 2 + y);
}
void smb_ws_world_reset(void) {
    memset(&g_smb_ws_world, 0, sizeof g_smb_ws_world);
    g_smb_ws_world.version = 3;
    g_smb_ws_world.flag_x = -1;
    memset(g_smb_ws_world.block_world, 0xff, sizeof g_smb_ws_world.block_world);
    memset(g_smb_ws_world.nt_world, 0xff, sizeof g_smb_ws_world.nt_world);
    memset(g_smb_ws_world.pending_world, 0xff, sizeof g_smb_ws_world.pending_world);
    g_smb_ws_world.first_mismatch_column = -1;
}
int smb_ws_world_busy(void) { return s_decoding; }

static void decode(void) {
    SmbWsWorld *w = &g_smb_ws_world;
    uint8_t ram[0x800];
    uint8_t runtime[1024];
    int runtime_len = runtime_get_state_blob(runtime, sizeof runtime);
    if (!runtime_len) return;
    CPU6502State cpu = g_cpu;
    int bail = g_bail_active, stack = g_recomp_stack_top;
    uint16_t rts = g_rts_target;
    unsigned data = area_data();
    uint8_t header0 = rom(data - 2), header1 = rom(data - 1);
    memcpy(ram, g_ram, sizeof ram);
    smb_ws_world_reset();
    w->area_data = (uint16_t)data; w->area_type = ram[0x74e]; w->world = ram[0x75f];
    s_decoding = 1;
    runtime_begin_unclocked();
    /* Match InitializeArea's cleared working set and original area header.
     * AreaPointer can already refer to the next pipe destination; the live
     * AreaData pointer identifies the area actually being rendered. */
    memset(g_ram, 0, 0x74c);
    g_ram[0xe7] = (uint8_t)data; g_ram[0xe8] = (uint8_t)(data >> 8);
    g_ram[0x730] = g_ram[0x731] = g_ram[0x732] = 0xff;
    g_ram[0x741] = (header0 & 7) < 4 ? header0 & 7 : 0;
    g_ram[0x744] = (header0 & 7) >= 4 ? header0 & 7 : 0;
    g_ram[0x727] = header1 & 15;
    g_ram[0x742] = (header1 >> 4) & 3;
    g_ram[0x733] = header1 >> 6;
    if (g_ram[0x733] == 3) { g_ram[0x743] = 3; g_ram[0x733] = 0; }
    g_bail_active = 0;
    for (int col = 0; col < SMB_WS_META_COLUMNS; col++) {
        g_ram[0x725] = (uint8_t)(col >> 4);
        g_ram[0x726] = (uint8_t)(col & 15);
        g_ram[0x6a0] = (uint8_t)(col & 31);
        /* Area objects create plants directly, outside EnemyData. Capacity
         * in this private parser must not discard later pipe seeds. */
        memset(g_ram+0x0f,0,5);
        g_cpu.S = 0xfd;
        func_93FC_b0();
        for (int slot=0;slot<5;slot++) if (g_ram[0x0f+slot] && g_ram[0x16+slot]==0x0d) {
            if (w->plant_count<SMB_WS_MAX_PLANTS) {
                SmbWsPlant *p=&w->plants[w->plant_count++];
                p->x=(uint16_t)((g_ram[0x6e + slot]<<8)|g_ram[0x87+slot]);
                p->y=g_ram[0xcf+slot];
            }
        }
        if (g_ram[0x14] && g_ram[0x1b]==0x30 &&
            ((g_ram[0x73]<<8)|g_ram[0x8c])==col*16-8)
            w->flag_x=(int16_t)(col*16-8);
        memcpy(w->metatiles[col], g_ram + 0x6a1, 13);
        int block=0x500+((col&16)?0xd0:0)+(col&15);
        for (int row=0;row<13;row++) w->collision[col][row]=g_ram[block+row*16];
        for (int row = 0; row < 26; row++) {
            uint8_t meta = g_ram[0x6a1 + row / 2];
            for (int x = 0; x < 2; x++) {
                w->tiles[col * 2 + x][row] = tile_for(meta, x, row & 1);
                w->palettes[col * 2 + x][row] = meta >> 6;
            }
        }
        w->decoded_columns++;
    }
    memcpy(g_ram, ram, sizeof ram);
    g_cpu = cpu; g_bail_active = bail; g_recomp_stack_top = stack; g_rts_target = rts;
    runtime_end_unclocked();
    runtime_set_state_blob(runtime, runtime_len);
    s_decoding = 0;
    w->valid = 1;
}
static int ensure_world(void) {
    unsigned data = area_data();
    if (s_decoding || data < 0x8002 || data > 0xff00) return 0;
    SmbWsWorld *w = &g_smb_ws_world;
    if (!w->valid || w->area_data != data || w->area_type != g_ram[0x74e] || w->world != g_ram[0x75f]) decode();
    return w->valid;
}
void smb_ws_world_observe_column(void) {
    if (!ensure_world()) return;
    SmbWsWorld *w = &g_smb_ws_world;
    int col = g_ram[0x725] * 16 + g_ram[0x726];
    int side = (g_ram[0x71f] ^ 1) & 1;
    if (col >= SMB_WS_META_COLUMNS) return;
    /* Each 16-pixel column is submitted as two separate VRAM writes. */
    if (side == 0) {
        w->block_world[col&31]=(int16_t)col;
        int mismatch = 0;
        for (int row = 0; row < 13; row++) {
            uint8_t actual = g_ram[0x6a1 + row];
            if (actual != w->metatiles[col][row]) {
                mismatch = 1;
                if (w->first_mismatch_column < 0) {
                    w->first_mismatch_column = col; w->first_mismatch_row = row;
                    w->first_expected = w->metatiles[col][row]; w->first_actual = actual;
                }
            }
        }
        if (mismatch) w->mismatched_columns++; else w->verified_columns++;
    }
    int nt = (g_ram[0x720] >> 2) & 1, tx = g_ram[0x721] & 31;
    w->pending_world[nt][tx] = (int16_t)(col * 2 + side);
    for (int row = 0; row < 26; row++)
        w->pending_tiles[nt][tx][row] = tile_for(g_ram[0x6a1 + row/2], side, row & 1);
    /* Attributes are uploaded later, in four-tile groups. Their old physical
     * contents do not belong to this column just because its tiles arrived. */
    for (int row=0;row<26;row++)
        w->palettes[col*2+side][row]=g_ram[0x6a1+row/2]>>6;
}
void smb_ws_world_update(void) {
    if (!ensure_world()) return;
    SmbWsWorld *w = &g_smb_ws_world;
    for (int c=0;c<32;c++) {
        int world=w->block_world[c];
        if (world<0) continue;
        int block=0x500+((c&16)?0xd0:0)+(c&15);
        for (int row=0;row<13;row++) w->collision[world][row]=g_ram[block+row*16];
    }
    for (int nt = 0; nt < 2; nt++) for (int tx = 0; tx < 32; tx++) {
        if (w->pending_world[nt][tx] >= 0) {
            int matches = 1;
            for (int row = 0; row < 26; row++)
                if (g_ppu_nt[nt*1024 + (row+4)*32 + tx] != w->pending_tiles[nt][tx][row]) { matches = 0; break; }
            if (matches) {
                w->nt_world[nt][tx] = w->pending_world[nt][tx];
                w->pending_world[nt][tx] = -1;
            }
        }
        int world = w->nt_world[nt][tx];
        /* A pending replacement makes the old binding untrustworthy. */
        if (world < 0 || w->pending_world[nt][tx] >= 0) continue;
        for (int row = 0; row < 26; row++) {
            int ty = row + 4;
            w->tiles[world][row] = g_ppu_nt[nt*1024 + ty*32 + tx];
        }
    }
}
int smb_ws_world_flag_x(void) {
    return g_smb_ws_world.valid?g_smb_ws_world.flag_x:-1;
}
int smb_ws_world_pixel(int world_x, int y, uint8_t *palette, uint8_t *tile) {
    if (!g_smb_ws_world.valid || world_x < 0 || world_x >= SMB_WS_TILE_COLUMNS*8 || y < 32 || y >= 240) return 0;
    int col = world_x / 8, row = (y - 32) / 8;
    *tile = g_smb_ws_world.tiles[col][row];
    *palette = g_smb_ws_world.palettes[col][row];
    return 1;
}
void smb_ws_world_begin_column(void) {
    if (!s_decoding && g_smb_ws_world.valid)
        g_smb_ws_world.block_world[g_ram[0x6a0]&31]=-1;
}
