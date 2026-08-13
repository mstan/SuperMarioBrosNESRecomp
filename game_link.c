/*
 * Zelda II Link gameplay/presentation layer for SMB1.
 *
 * Movement and sword hitboxes stay in the ForeignController. This file loads
 * Link graphics from the launcher-verified Zelda II owner ROM and composites
 * the side-view Link sprite after SMB's native PPU frame.
 */
#include "game_link.h"

#include "game_smash64.h"
#include "mods/zelda2/link_controller.h"

#include "foreign_controller.h"
#include "nes_runtime.h"
#include "generated/super-mario-bros_full_decls.h"

#include <SDL.h>

#include <stdio.h>
#include <string.h>

#define ZELDA2_PRG_BYTES 131072L
#define ZELDA2_CHR_BANK_BYTES 8192
#define ZELDA2_HEADERED_BYTES 262160
#define ZELDA2_HEADERLESS_BYTES 262144

#define PAD_UP   0x08
#define PAD_DOWN 0x04

static int s_enabled;
static int s_assets_ready;
static uint64_t s_present_frame;
static uint8_t s_chr[ZELDA2_CHR_BANK_BYTES];
static int s_draw_behind_background;

/* Zelda II's side-view sprite palette 0. The source tables use $FF for the
 * transparent slot; the compositor uses the NES universal black entry. */
static const uint8_t k_link_palette[4] = {0x0F, 0x18, 0x36, 0x2A};

/* EB25 body-tile table and EB97 frame-offset table from the byte-exact
 * Zelda II disassembly. $F5 is the hidden-sprite marker. */
static const uint8_t k_link_body_tiles[] = {
    0xF5,0x00,0x02,0xF5,0x04,0x06,0xF5,0x08,0x0A,0xF5,0x0C,0x0E,
    0xF5,0x00,0x02,0xF5,0x10,0x12,0xF5,0x46,0x48,0xF5,0x4A,0x4C,
    0xF5,0x00,0x02,0xF5,0x26,0x06,0x28,0x2A,0x30,0x2C,0x2E,0xF5,
    0x34,0x36,0x38,0xF5,0x3A,0x3C,0xF5,0x46,0x48,0x4E,0x50,0x52,
    0x56,0x58,0xF5,0x5A,0x5C,0x5E,0xF5,0x1C,0x1E,0xF5,0x20,0x22,
    0xF5,0x08,0x0A,0xF5,0x0C,0x24,0x28,0x2A,0x2C,0xF5,0x2E,0x60,
    0x34,0x36,0x38,0xF5,0x3A,0x62,0xF5,0x14,0x16,0xF5,0x18,0x1A,
    0xF5,0x3E,0x40,0xF5,0x42,0x44,0xF5,0x01,0x01,0xF5,0x03,0x03,
    0xF5,0x71,0x73,0xF5,0x75,0x77,0xF5,0x21,0x23,0xF5,0x25,0x27,
    0xF5,0x81,0x83,0xF5,0xAD,0xAF
};

static const uint8_t k_link_frame_offsets[] = {
    0x00,0x06,0x0C,0x18,0x1E,0x24,0x12,0x30,0x36,0x54,
    0x4E,0x5A,0x60,0x66,0x6C,0x10,0x0C,0x00,0x04,0x04
};

static int load_owner_chr(const char *rom_path)
{
    SDL_RWops *file;
    unsigned char header[16];
    Sint64 size;
    long base = 0;

    if (!rom_path || !*rom_path) return 0;
    file = SDL_RWFromFile(rom_path, "rb");
    if (!file) return 0;
    size = SDL_RWsize(file);
    if (size == ZELDA2_HEADERED_BYTES) {
        if (SDL_RWread(file, header, 1, sizeof(header)) != sizeof(header) ||
            memcmp(header, "NES\x1a", 4) != 0 || (header[6] & 0x04) != 0 ||
            header[4] != 8 || header[5] < 1) {
            SDL_RWclose(file);
            return 0;
        }
        base = 16;
    } else if (size != ZELDA2_HEADERLESS_BYTES) {
        SDL_RWclose(file);
        return 0;
    }

    if (SDL_RWseek(file, (Sint64)base + ZELDA2_PRG_BYTES, RW_SEEK_SET) < 0 ||
        SDL_RWread(file, s_chr, 1, sizeof(s_chr)) != sizeof(s_chr)) {
        SDL_RWclose(file);
        return 0;
    }
    SDL_RWclose(file);
    return 1;
}

static void put_pixel(uint32_t *fb, int x, int y, uint32_t color)
{
    if (x >= 0 && x < g_render_width && y >= 0 && y < 240 &&
        !(s_draw_behind_background &&
          ppu_renderer_background_opaque(x, y)))
        fb[y * g_render_width + x] = color;
}

static void draw_tile_8x8(uint32_t *fb, int tile, int x, int y, int hflip,
                          int vflip, const uint8_t palette[4])
{
    const uint8_t *p;
    if (!s_assets_ready || tile < 0 ||
        tile * 16 + 15 >= ZELDA2_CHR_BANK_BYTES)
        return;
    p = s_chr + tile * 16;
    for (int row = 0; row < 8; ++row) {
        int sy = vflip ? 7 - row : row;
        uint8_t lo = p[sy], hi = p[sy + 8];
        for (int col = 0; col < 8; ++col) {
            int sx = hflip ? col : 7 - col;
            int value = ((lo >> sx) & 1) | (((hi >> sx) & 1) << 1);
            if (value)
                put_pixel(fb, x + col, y + row,
                          g_nes_palette[palette[value] & 0x3F]);
        }
    }
}

static void draw_sprite_8x16(uint32_t *fb, int tile, int x, int y, int hflip,
                             int vflip, const uint8_t palette[4])
{
    int pattern_table = tile & 1;
    int top = pattern_table * 0x100 + (tile & 0xFE);
    int bottom = top + 1;
    if (vflip) {
        draw_tile_8x8(fb, bottom, x, y, hflip, 1, palette);
        draw_tile_8x8(fb, top, x, y + 8, hflip, 1, palette);
    } else {
        draw_tile_8x8(fb, top, x, y, hflip, 0, palette);
        draw_tile_8x8(fb, bottom, x, y + 8, hflip, 0, palette);
    }
}

static unsigned link_display_frame(const ForeignState *state)
{
    if (!state) return 0;
    switch (state->state) {
    case ZELDA2_LINK_CROUCH: return 6;
    case ZELDA2_LINK_CROUCH_SLASH: return 7;
    case ZELDA2_LINK_SLASH_ACTIVE: return 5;
    case ZELDA2_LINK_SLASH_START:
    case ZELDA2_LINK_SLASH_RECOVER: return 4;
    case ZELDA2_LINK_UPSTAB: return 8;
    case ZELDA2_LINK_DOWNSTAB: return 9;
    case ZELDA2_LINK_JUMP:
    case ZELDA2_LINK_FALL: return 3;
    case ZELDA2_LINK_WALK:
        return 1u + ((state->state_frame / 8u) % 2u);
    case ZELDA2_LINK_STAND:
    default:
        return 0;
    }
}

static void draw_body(uint32_t *fb, int origin_x, int origin_y, int mirror,
                      unsigned frame)
{
    unsigned offset;

    if (frame >= sizeof(k_link_frame_offsets)) frame = 0;
    offset = k_link_frame_offsets[frame];
    for (unsigned row = 0; row < 2; ++row) {
        unsigned row_offset = offset + row * 3u;
        for (unsigned col = 0; col < 3; ++col) {
            unsigned src_col = mirror ? 2u - col : col;
            int tile;
            if (row_offset + src_col >= sizeof(k_link_body_tiles)) break;
            tile = k_link_body_tiles[row_offset + src_col];
            if (tile == 0xF5) continue;
            draw_sprite_8x16(fb, tile, origin_x + (int)col * 8,
                             origin_y + (int)row * 16,
                             mirror, 0, k_link_palette);
        }
    }
}

static void draw_sword(uint32_t *fb, int origin_x, int origin_y, int mirror,
                       const ForeignState *state)
{
    /* EBAB/LEBAD place the one-tile blade immediately outside Zelda II's
     * assembled body: eight pixels left or 24 pixels right. The original
     * routine's +32 uses logical Link X, before its +8 right-facing body
     * shift; origin_x here is already the body origin. */
    int dx = mirror ? -8 : 24;
    int dy = 0;
    int tile = 0x32;

    if (!state) return;
    if (state->state != ZELDA2_LINK_SLASH_START &&
        state->state != ZELDA2_LINK_SLASH_ACTIVE &&
        state->state != ZELDA2_LINK_SLASH_RECOVER &&
        state->state != ZELDA2_LINK_CROUCH_SLASH)
        return;
    if (state->state == ZELDA2_LINK_CROUCH_SLASH) {
        tile = 0x54;
        dy = 16;
    }
    draw_sprite_8x16(fb, tile, origin_x + dx, origin_y + dy, mirror, 0,
                     k_link_palette);
    if (state->state != ZELDA2_LINK_CROUCH_SLASH) {
        int tip_dx = mirror ? dx - 7 : dx + 7;
        draw_sprite_8x16(fb, tile, origin_x + tip_dx, origin_y + dy, mirror, 0,
                         k_link_palette);
    }
}

static void draw_link(uint32_t *fb)
{
    const ForeignState *state = nes_foreign_state();
    int x = g_ram[Player_Rel_XPos] + g_widescreen_left - 4;
    int y = g_ram[Player_Rel_YPos] +
            (((int)(int8_t)g_ram[Player_Y_HighPos] - 1) * 256);
    int face_left = state && state->facing < 0.0f;
    int body_mirror = !face_left;
    unsigned frame = link_display_frame(state);

    if (game_smash64_scripted_presentation() ==
        SMASH64_SCRIPTED_PRESENTATION_WALK)
        frame = 1u + ((s_present_frame / 8u) % 2u);
    if (game_smash64_swim_presentation_active())
        frame = 3u;

    draw_body(fb, x, y, body_mirror, frame);
    draw_sword(fb, x, y, face_left, state);
}

int game_link_set_enabled(int enabled, const char *owner_rom_path)
{
    s_enabled = 0;
    s_assets_ready = 0;
    s_present_frame = 0;
    if (!enabled) return 1;
    if (!load_owner_chr(owner_rom_path)) {
        fprintf(stderr, "[Zelda II] Could not extract Link tiles from the "
                        "verified owner ROM.\n");
        return 0;
    }
    if (!game_smash64_set_mod_enabled(1, ZELDA2_LINK_CONTROLLER_ID)) {
        game_smash64_set_mod_enabled(0, NULL);
        return 0;
    }
    s_assets_ready = 1;
    s_enabled = 1;
    printf("[Zelda II] Link armed: A jump, B sword, Down crouch, Up/Down stab "
           "in the air. Sword hits enemies and can break bricks.\n");
    return 1;
}

int game_link_active(void)
{
    return s_enabled && game_smash64_link_selected();
}

int game_link_register_hooks(void)
{
    return 1;
}

void game_link_update_input(uint64_t frame_count)
{
    (void)frame_count;
}

void game_link_update(uint64_t frame_count)
{
    (void)frame_count;
    if (game_link_active()) s_present_frame++;
}

void game_link_render_post_render(uint32_t *framebuffer)
{
    Smash64ScriptedPresentation scripted_presentation;
    if (!framebuffer || !game_link_active() || g_ram[OperMode] != 1) return;
    scripted_presentation = game_smash64_scripted_presentation();
    if (!game_smash64_active() &&
        !game_smash64_death_presentation_active() &&
        !game_smash64_still_presentation_active() &&
        !game_smash64_swim_presentation_active() &&
        scripted_presentation == SMASH64_SCRIPTED_PRESENTATION_NONE)
        return;

    s_draw_behind_background =
        (scripted_presentation == SMASH64_SCRIPTED_PRESENTATION_PIPE_SIDE ||
         scripted_presentation ==
             SMASH64_SCRIPTED_PRESENTATION_PIPE_VERTICAL) &&
        (g_ram[Player_SprAttrib] & 0x20) != 0;
    draw_link(framebuffer);
    s_draw_behind_background = 0;
}
