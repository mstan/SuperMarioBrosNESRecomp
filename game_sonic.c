/*
 * Sonic 3 & Knuckles Sonic presentation layer for SMB1.
 *
 * The required S3&K ROM is verified by the launcher and probed here. Rendering
 * is a compact NES-framebuffer adaptation of Sonic's S3&K standing/running/
 * rolling silhouettes, using the same post-PPU replacement path as Link/Samus.
 */
#include "game_sonic.h"

#include "game_smash64.h"
#include "game_sonic_audio.h"
#include "mods/s3k/sonic_controller.h"

#include "foreign_controller.h"
#include "nes_runtime.h"
#include "generated/super-mario-bros_full_decls.h"

#include <SDL.h>

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define S3K_ROM_BYTES 4194304L
#define S3K_SONIC_ART_OFF 0x100000u
#define S3K_SONIC_MAP_OFF 0x146620u
#define S3K_SONIC_DPLC_OFF 0x148182u
#define S3K_SONIC_PALETTE_OFF 0x0A8A3Cu
#define S3K_SONIC_MAP_COUNT 219u
#define S3K_FIRE_SHIELD_ART_OFF 0x18C704u
#define S3K_FIRE_SHIELD_MAP_OFF 0x19AC6u
#define S3K_FIRE_SHIELD_DPLC_OFF 0x19CE6u
#define S3K_FIRE_SHIELD_MAP_COUNT 25u
#define S3K_SONIC_TILE_BYTES 32u
#define S3K_SONIC_MAX_FRAME_TILES 96u
#define S3K_SONIC_SCALE_NUM 4
#define S3K_SONIC_SCALE_DEN 5
#define S3K_SONIC_BALL_SCALE_NUM 2
#define S3K_SONIC_BALL_SCALE_DEN 3
#define S3K_SONIC_SOURCE_FOOT_Y 20
#define S3K_SPRITE_CANVAS_SIZE 96
#define S3K_SPRITE_CANVAS_ORIGIN (S3K_SPRITE_CANVAS_SIZE / 2)

static int s_enabled;
static int s_owner_ready;
static uint64_t s_present_frame;
static int s_draw_behind_background;
static uint8_t *s_owner_rom;
static uint32_t s_genesis_palette[16];
static uint32_t s_sprite_canvas[S3K_SPRITE_CANVAS_SIZE *
                                S3K_SPRITE_CANVAS_SIZE];

static const uint32_t k_fire_shield_palette[16] = {
    0u,
    0xFF701000u, 0xFFB82000u, 0xFFE84810u, 0xFFFF7820u,
    0xFFFFA830u, 0xFFFFD860u, 0xFFFFFFA0u, 0xFFFFF0C0u,
    0xFF501000u, 0xFF902000u, 0xFFD83800u, 0xFFFF6818u,
    0xFFFF9830u, 0xFFFFC850u, 0xFFFFFFE0u
};

static const uint32_t C_OUTLINE = 0xFF101018u;
static const uint32_t C_BLUE    = 0xFF1848D8u;
static const uint32_t C_BLUE_HI = 0xFF58A0FFu;
static const uint32_t C_SKIN    = 0xFFFFB878u;
static const uint32_t C_WHITE   = 0xFFFFF8F0u;
static const uint32_t C_RED     = 0xFFE03828u;
static const uint32_t C_GOLD    = 0xFFFFD850u;

static const char *const k_idle[] = {
    "......KKK.......",
    "....KKBBBK......",
    "...KBBBBBBK.....",
    "..KBBBBBBBK.....",
    ".KBBBBBWWBBK....",
    ".KBBBBBWWTBBK...",
    ".KBBBBTTTTTBK...",
    "..KBBTTTTTTK....",
    "...KTTTTTTK.....",
    "...KWWKBBK......",
    "..KWWKBBBK......",
    ".KBBBKBBBK......",
    "..KBBK.RRK......",
    "...KK.RRYYK.....",
    "....KRRRYYK.....",
    ".....KKKKK......",
};

static const char *const k_run1[] = {
    ".....KKK........",
    "...KKBBBK.......",
    "..KBBBBBBK......",
    ".KBBBBBBBBK.....",
    ".KBBBBWWBBK.....",
    "KBBBBBWWTBBK....",
    "KBBBBTTTTTBK....",
    ".KBBTTTTTTK.....",
    "..KKTTTTK.......",
    ".KWWKBBBK.......",
    "KWWKBBBBK.......",
    ".KKKBBBBK.......",
    "...KBBKRRK......",
    "..KRRK..YYK.....",
    ".KRRYYK.........",
    "..KKKK..........",
};

static const char *const k_run2[] = {
    "......KKK.......",
    "....KKBBBK......",
    "...KBBBBBBK.....",
    "..KBBBBBBBBK....",
    "..KBBBBWWBBK....",
    ".KBBBBBWWTBBK...",
    ".KBBBBTTTTTBK...",
    "..KBBTTTTTTK....",
    "...KKTTTTK......",
    "....KBBKWWK.....",
    "...KBBBKWWK.....",
    "...KBBBBKK......",
    "..KRRKBBK.......",
    ".KYY..KRRK......",
    ".....KYYRRK.....",
    "......KKKK......",
};

static const char *const k_ball1[] = {
    ".....KKKKK......",
    "...KKBBBBBKK....",
    "..KBBBBBBBBK....",
    ".KBBBLLBBBBBK...",
    ".KBBLBBBBLBBK...",
    "KBBLBBBBBBLBBK..",
    "KBBBBBKKBBBBK...",
    "KBBBBKTTKBBBK...",
    "KBBBKTTTTKBBK...",
    ".KBBBKTTKBBK....",
    ".KBBBBKKBBBK....",
    "..KBBBBBBBK.....",
    "...KBBBBBK......",
    "....KKBBK.......",
    "......KK........",
    "................",
};

static const char *const k_ball2[] = {
    "......KK........",
    "....KKBBK.......",
    "...KBBBBBK......",
    "..KBBBBBBBK.....",
    ".KBBBBKKBBBK....",
    ".KBBBKTTKBBK....",
    "KBBBKTTTTKBBK...",
    "KBBBBKTTKBBBK...",
    "KBBBBBKKBBBBK...",
    "KBBLBBBBBBLBBK..",
    ".KBBLBBBBLBBK...",
    ".KBBBLLBBBBBK...",
    "..KBBBBBBBBK....",
    "...KKBBBBBKK....",
    ".....KKKKK......",
    "................",
};

static int probe_owner_rom(const char *rom_path)
{
    SDL_RWops *file;
    uint8_t *data;
    Sint64 size;
    if (!rom_path || !*rom_path) return 0;
    file = SDL_RWFromFile(rom_path, "rb");
    if (!file) return 0;
    size = SDL_RWsize(file);
    if (size != S3K_ROM_BYTES) {
        SDL_RWclose(file);
        return 0;
    }
    data = (uint8_t *)malloc((size_t)S3K_ROM_BYTES);
    if (!data) {
        SDL_RWclose(file);
        return 0;
    }
    if (SDL_RWread(file, data, 1, (size_t)S3K_ROM_BYTES) !=
        (size_t)S3K_ROM_BYTES) {
        SDL_RWclose(file);
        free(data);
        return 0;
    }
    SDL_RWclose(file);
    free(s_owner_rom);
    s_owner_rom = data;
    return 1;
}

static void put_pixel(uint32_t *fb, int x, int y, uint32_t color)
{
    if (x >= 0 && x < g_render_width && y >= 0 && y < 240 &&
        !(s_draw_behind_background &&
          ppu_renderer_background_opaque(x, y)))
        fb[y * g_render_width + x] = color;
}

static int floor_ratio(int value, int num, int den)
{
    if (value >= 0) return (value * num) / den;
    return -(((-value) * num + den - 1) / den);
}

static int ceil_ratio(int value, int num, int den)
{
    return -floor_ratio(-value, num, den);
}

static uint32_t color_for(char c)
{
    switch (c) {
    case 'K': return C_OUTLINE;
    case 'B': return C_BLUE;
    case 'L': return C_BLUE_HI;
    case 'T': return C_SKIN;
    case 'W': return C_WHITE;
    case 'R': return C_RED;
    case 'Y': return C_GOLD;
    default: return 0;
    }
}

static void draw_pattern(uint32_t *fb, const char *const rows[16],
                         int x, int y, int mirror)
{
    for (int py = 0; py < 16; ++py) {
        for (int px = 0; px < 16; ++px) {
            char c = rows[py][mirror ? 15 - px : px];
            uint32_t color = color_for(c);
            if (!color) continue;
            put_pixel(fb, x + px * 2,     y + py * 2,     color);
            put_pixel(fb, x + px * 2 + 1, y + py * 2,     color);
            put_pixel(fb, x + px * 2,     y + py * 2 + 1, color);
            put_pixel(fb, x + px * 2 + 1, y + py * 2 + 1, color);
        }
    }
}

static uint16_t be16_at(uint32_t off)
{
    if (!s_owner_rom || off + 1u >= (uint32_t)S3K_ROM_BYTES) return 0;
    return (uint16_t)((s_owner_rom[off] << 8) | s_owner_rom[off + 1u]);
}

static int16_t be16s_at(uint32_t off)
{
    return (int16_t)be16_at(off);
}

static uint32_t genesis_color(uint16_t cram)
{
    uint32_t r = (uint32_t)((cram >> 1) & 7u);
    uint32_t g = (uint32_t)((cram >> 5) & 7u);
    uint32_t b = (uint32_t)((cram >> 9) & 7u);
    r = (r << 5) | (r << 2) | (r >> 1);
    g = (g << 5) | (g << 2) | (g >> 1);
    b = (b << 5) | (b << 2) | (b >> 1);
    return 0xFF000000u | (r << 16) | (g << 8) | b;
}

static void load_genesis_palette(void)
{
    for (unsigned i = 0; i < 16u; ++i)
        s_genesis_palette[i] =
            i == 0 ? 0u : genesis_color(be16_at(S3K_SONIC_PALETTE_OFF + i * 2u));
}

static const char *const *sonic_pattern(const ForeignState *state)
{
    if (!state) return k_idle;
    switch (state->state) {
    case S3K_SONIC_SPINDASH:
    case S3K_SONIC_ROLL:
    case S3K_SONIC_JUMP:
    case S3K_SONIC_FALL:
    case S3K_SONIC_FIRE_DASH:
        return ((s3k_sonic_anim_frame() >> 2) & 1u) ? k_ball2 : k_ball1;
    case S3K_SONIC_WALK:
    case S3K_SONIC_RUN:
    case S3K_SONIC_SKID:
        return ((s3k_sonic_anim_frame() >> 3) & 1u) ? k_run2 : k_run1;
    case S3K_SONIC_CROUCH:
    default:
        return k_idle;
    }
}

static unsigned sequence_frame(const uint8_t *frames, unsigned count,
                               unsigned shift)
{
    if (!count) return 1u;
    return frames[(s3k_sonic_anim_frame() >> shift) % count];
}

static unsigned presentation_sequence_frame(const uint8_t *frames,
                                            unsigned count,
                                            unsigned shift)
{
    if (!count) return 1u;
    return frames[(s_present_frame >> shift) % count];
}

static unsigned fire_shield_sequence_frame(const uint8_t *frames,
                                           unsigned count,
                                           unsigned shift)
{
    uint64_t clock;
    if (!count) return 1u;
    clock = game_smash64_scripted_presentation() !=
                SMASH64_SCRIPTED_PRESENTATION_NONE
                ? s_present_frame
                : s3k_sonic_anim_frame();
    return frames[(clock >> shift) % count];
}

static unsigned sonic_map_frame(const ForeignState *state)
{
    static const uint8_t k_walk[] = { 7, 8, 1, 2, 3, 4, 5, 6 };
    static const uint8_t k_run[] = { 0x21, 0x22, 0x23, 0x24 };
    static const uint8_t k_ball[] =
        { 0x96, 0x97, 0x96, 0x98, 0x96, 0x99, 0x96, 0x9A };
    static const uint8_t k_spindash[] =
        { 0x86, 0x87, 0x86, 0x88, 0x86, 0x89, 0x86, 0x8A, 0x86, 0x8B };
    static const uint8_t k_skid[] = { 0x9D, 0x9E, 0x9F, 0xA0 };
    static const uint8_t k_death[] = { 0xA7 };
    Smash64ScriptedPresentation scripted =
        game_smash64_scripted_presentation();

    if (game_smash64_death_presentation_active())
        return presentation_sequence_frame(k_death, sizeof(k_death), 3);
    if (scripted == SMASH64_SCRIPTED_PRESENTATION_WALK)
        return presentation_sequence_frame(k_walk, sizeof(k_walk), 3);
    if (!state) return 0xBAu;
    switch (state->state) {
    case S3K_SONIC_SPINDASH:
        return sequence_frame(k_spindash, sizeof(k_spindash), 1);
    case S3K_SONIC_ROLL:
    case S3K_SONIC_JUMP:
    case S3K_SONIC_FALL:
    case S3K_SONIC_FIRE_DASH:
        return sequence_frame(k_ball, sizeof(k_ball), 2);
    case S3K_SONIC_RUN:
        return sequence_frame(k_run, sizeof(k_run), 2);
    case S3K_SONIC_WALK:
        return sequence_frame(k_walk, sizeof(k_walk), 3);
    case S3K_SONIC_SKID:
        return sequence_frame(k_skid, sizeof(k_skid), 2);
    case S3K_SONIC_CROUCH:
        return state->state_frame <= 5u ? 0x9Bu : 0x9Cu;
    case S3K_SONIC_STAND:
    default:
        return 0xBAu;
    }
}

static int build_dplc_tiles(uint32_t dplc_off, unsigned map_count,
                            unsigned frame, uint16_t *tiles, unsigned cap)
{
    uint32_t ptr;
    unsigned count, out = 0;

    if (!s_owner_rom || frame >= map_count) return 0;
    ptr = dplc_off + be16_at(dplc_off + frame * 2u);
    count = be16_at(ptr);
    ptr += 2u;
    if (count > 32u) return 0;
    for (unsigned i = 0; i < count; ++i) {
        uint16_t entry = be16_at(ptr + i * 2u);
        unsigned len = (unsigned)(entry >> 12) + 1u;
        unsigned first = entry & 0x0FFFu;
        for (unsigned j = 0; j < len && out < cap; ++j)
            tiles[out++] = (uint16_t)(first + j);
    }
    return (int)out;
}

static void draw_genesis_tile(uint32_t art_off, const uint32_t *palette,
                              uint16_t tile,
                              int source_x, int source_y,
                              int hflip, int vflip)
{
    uint32_t off = art_off + (uint32_t)tile * S3K_SONIC_TILE_BYTES;

    if (!s_owner_rom || off + S3K_SONIC_TILE_BYTES > (uint32_t)S3K_ROM_BYTES)
        return;
    for (int py = 0; py < 8; ++py) {
        int sy = vflip ? 7 - py : py;
        for (int px = 0; px < 8; ++px) {
            int sx = hflip ? 7 - px : px;
            uint8_t b = s_owner_rom[off + (uint32_t)sy * 4u +
                                    (uint32_t)sx / 2u];
            uint8_t pal = (sx & 1) ? (uint8_t)(b & 0x0F) : (uint8_t)(b >> 4);
            int canvas_x = S3K_SPRITE_CANVAS_ORIGIN + source_x + px;
            int canvas_y = S3K_SPRITE_CANVAS_ORIGIN + source_y + py;
            if (pal == 0) continue;
            if (canvas_x >= 0 && canvas_x < S3K_SPRITE_CANVAS_SIZE &&
                canvas_y >= 0 && canvas_y < S3K_SPRITE_CANVAS_SIZE)
                s_sprite_canvas[canvas_y * S3K_SPRITE_CANVAS_SIZE + canvas_x] =
                    palette[pal];
        }
    }
}

static int render_genesis_frame(uint32_t art_off, const uint32_t *palette,
                                uint32_t map_off,
                                uint32_t dplc_off, unsigned map_count,
                                unsigned frame, int mirror)
{
    uint16_t frame_tiles[S3K_SONIC_MAX_FRAME_TILES];
    int vram_tiles = build_dplc_tiles(dplc_off, map_count, frame, frame_tiles,
                                      S3K_SONIC_MAX_FRAME_TILES);
    uint32_t ptr;
    unsigned pieces;

    memset(s_sprite_canvas, 0, sizeof(s_sprite_canvas));
    if (vram_tiles <= 0 || frame >= map_count) return 0;
    ptr = map_off + be16_at(map_off + frame * 2u);
    pieces = be16_at(ptr);
    ptr += 2u;
    if (pieces > 32u) return 0;

    for (unsigned i = 0; i < pieces; ++i) {
        uint32_t p = ptr + i * 6u;
        int y = (int)(int8_t)s_owner_rom[p];
        uint8_t size = s_owner_rom[p + 1u];
        uint16_t attr = be16_at(p + 2u);
        int x = (int)be16s_at(p + 4u);
        int tile_w = ((size >> 2) & 3) + 1;
        int tile_h = (size & 3) + 1;
        int hflip = (attr & 0x0800u) != 0;
        int vflip = (attr & 0x1000u) != 0;
        int tile_base = attr & 0x07FFu;

        if (mirror) {
            x = -x - tile_w * 8;
            hflip = !hflip;
        }
        for (int ty = 0; ty < tile_h; ++ty) {
            for (int tx = 0; tx < tile_w; ++tx) {
                int source_tx = hflip ? tile_w - 1 - tx : tx;
                int source_ty = vflip ? tile_h - 1 - ty : ty;
                /* Mega Drive sprite patterns advance down each tile column. */
                int vram_index = tile_base + source_tx * tile_h + source_ty;
                if (vram_index < 0 || vram_index >= vram_tiles) continue;
                draw_genesis_tile(art_off, palette, frame_tiles[vram_index],
                                  x + tx * 8, y + ty * 8,
                                  hflip, vflip);
            }
        }
    }
    return 1;
}

static void composite_genesis_frame(uint32_t *fb, int origin_x, int origin_y,
                                    int scale_num, int scale_den)
{
    int min_x = S3K_SPRITE_CANVAS_SIZE;
    int min_y = S3K_SPRITE_CANVAS_SIZE;
    int max_x = -1;
    int max_y = -1;

    for (int y = 0; y < S3K_SPRITE_CANVAS_SIZE; ++y) {
        for (int x = 0; x < S3K_SPRITE_CANVAS_SIZE; ++x) {
            if (!s_sprite_canvas[y * S3K_SPRITE_CANVAS_SIZE + x]) continue;
            if (x < min_x) min_x = x;
            if (x > max_x) max_x = x;
            if (y < min_y) min_y = y;
            if (y > max_y) max_y = y;
        }
    }
    if (max_x < min_x || max_y < min_y) return;

    min_x -= S3K_SPRITE_CANVAS_ORIGIN;
    max_x -= S3K_SPRITE_CANVAS_ORIGIN;
    min_y -= S3K_SPRITE_CANVAS_ORIGIN;
    max_y -= S3K_SPRITE_CANVAS_ORIGIN;
    {
        int dst_min_x = floor_ratio(min_x, scale_num, scale_den);
        int dst_max_x = ceil_ratio(max_x + 1, scale_num, scale_den);
        int dst_min_y = floor_ratio(min_y, scale_num, scale_den);
        int dst_max_y = ceil_ratio(max_y + 1, scale_num, scale_den);

        for (int y = dst_min_y; y < dst_max_y; ++y) {
            int source_y = floor_ratio(y * scale_den, 1, scale_num);
            for (int x = dst_min_x; x < dst_max_x; ++x) {
                int source_x = floor_ratio(x * scale_den, 1, scale_num);
                uint32_t color;
                if (source_x < min_x || source_x > max_x ||
                    source_y < min_y || source_y > max_y)
                    continue;
                color = s_sprite_canvas[
                    (source_y + S3K_SPRITE_CANVAS_ORIGIN) *
                        S3K_SPRITE_CANVAS_SIZE +
                    source_x + S3K_SPRITE_CANVAS_ORIGIN];
                if (color) put_pixel(fb, origin_x + x, origin_y + y, color);
            }
        }
    }
}

static unsigned fire_shield_map_frame(const ForeignState *state)
{
    static const uint8_t k_regular[] = {
        0, 0x0F, 1, 0x10, 2, 0x11, 3, 0x12, 4,
        0x13, 5, 0x14, 6, 0x15, 7, 0x16, 8, 0x17
    };
    static const uint8_t k_dash[] = { 9, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E };

    if (state && state->state == S3K_SONIC_FIRE_DASH)
        return fire_shield_sequence_frame(k_dash, sizeof(k_dash), 0);
    return fire_shield_sequence_frame(k_regular, sizeof(k_regular), 1);
}

static void draw_fire_shield(uint32_t *fb, const ForeignState *state,
                             int origin_x, int origin_y, int mirror,
                             unsigned shield_frame)
{
    if (render_genesis_frame(S3K_FIRE_SHIELD_ART_OFF,
                             k_fire_shield_palette,
                             S3K_FIRE_SHIELD_MAP_OFF,
                             S3K_FIRE_SHIELD_DPLC_OFF,
                             S3K_FIRE_SHIELD_MAP_COUNT,
                             shield_frame, mirror))
        composite_genesis_frame(fb, origin_x, origin_y,
                                S3K_SONIC_SCALE_NUM,
                                S3K_SONIC_SCALE_DEN);
}

static void draw_genesis_sonic(uint32_t *fb, const ForeignState *state,
                               int origin_x, int origin_y, int mirror)
{
    int death = game_smash64_death_presentation_active();
    Smash64ScriptedPresentation scripted =
        game_smash64_scripted_presentation();
    int ball = !death &&
               scripted == SMASH64_SCRIPTED_PRESENTATION_NONE &&
               state && (state->state == S3K_SONIC_SPINDASH ||
                         state->state == S3K_SONIC_ROLL ||
                         state->state == S3K_SONIC_JUMP ||
                         state->state == S3K_SONIC_FALL ||
                         state->state == S3K_SONIC_FIRE_DASH);
    int scale_num = ball ? S3K_SONIC_BALL_SCALE_NUM : S3K_SONIC_SCALE_NUM;
    int scale_den = ball ? S3K_SONIC_BALL_SCALE_DEN : S3K_SONIC_SCALE_DEN;
    int has_shield = !death && s3k_sonic_has_fire_shield();
    unsigned shield_frame = fire_shield_map_frame(state);

    if (has_shield && shield_frame >= 0x0Fu)
        draw_fire_shield(fb, state, origin_x, origin_y, mirror, shield_frame);
    if (render_genesis_frame(S3K_SONIC_ART_OFF, s_genesis_palette,
                             S3K_SONIC_MAP_OFF,
                             S3K_SONIC_DPLC_OFF, S3K_SONIC_MAP_COUNT,
                             sonic_map_frame(state), mirror))
        composite_genesis_frame(fb, origin_x, origin_y, scale_num, scale_den);
    if (has_shield && shield_frame < 0x0Fu)
        draw_fire_shield(fb, state, origin_x, origin_y, mirror, shield_frame);
}

static void draw_sonic(uint32_t *fb)
{
    const ForeignState *state = nes_foreign_state();
    int x = g_ram[Player_Rel_XPos] + g_widescreen_left + 8;
    int y = g_ram[Player_Rel_YPos] +
            (((int)(int8_t)g_ram[Player_Y_HighPos] - 1) * 256);
    int mirror = state && state->facing < 0.0f;
    int death = game_smash64_death_presentation_active();
    Smash64ScriptedPresentation scripted =
        game_smash64_scripted_presentation();
    int ball = !death &&
               scripted == SMASH64_SCRIPTED_PRESENTATION_NONE &&
               state && (state->state == S3K_SONIC_SPINDASH ||
                         state->state == S3K_SONIC_ROLL ||
                         state->state == S3K_SONIC_JUMP ||
                         state->state == S3K_SONIC_FALL ||
                         state->state == S3K_SONIC_FIRE_DASH);
    int scale_num = ball ? S3K_SONIC_BALL_SCALE_NUM : S3K_SONIC_SCALE_NUM;
    int scale_den = ball ? S3K_SONIC_BALL_SCALE_DEN : S3K_SONIC_SCALE_DEN;
    const char *const *pattern;

    if (s_owner_rom) {
        int origin_y = y + 32 -
                       floor_ratio(S3K_SONIC_SOURCE_FOOT_Y,
                                   scale_num, scale_den);
        draw_genesis_sonic(fb, state, x, origin_y, mirror);
        return;
    }

    pattern = sonic_pattern(state);
    if (game_smash64_scripted_presentation() ==
        SMASH64_SCRIPTED_PRESENTATION_WALK)
        pattern = ((s_present_frame >> 3) & 1u) ? k_run2 : k_run1;
    if (game_smash64_swim_presentation_active())
        pattern = ((s_present_frame >> 2) & 1u) ? k_ball2 : k_ball1;

    draw_pattern(fb, pattern, x, y, mirror);
}

int game_sonic_set_enabled(int enabled, const char *owner_rom_path)
{
    s_enabled = 0;
    s_owner_ready = 0;
    s_present_frame = 0;
    if (!enabled) {
        game_sonic_audio_shutdown();
        return 1;
    }
    if (!probe_owner_rom(owner_rom_path)) {
        fprintf(stderr, "[S3&K] Could not verify the selected Sonic 3 & "
                        "Knuckles ROM for Sonic.\n");
        return 0;
    }
    load_genesis_palette();
    if (!game_smash64_set_mod_enabled(1, S3K_SONIC_CONTROLLER_ID)) {
        game_smash64_set_mod_enabled(0, NULL);
        game_sonic_audio_shutdown();
        return 0;
    }
    if (!game_sonic_audio_prepare(owner_rom_path)) {
        fprintf(stderr, "[S3&K] Could not build Sonic movement audio from "
                        "the selected Sonic 3 & Knuckles ROM.\n");
        game_smash64_set_mod_enabled(0, NULL);
        return 0;
    }
    s_owner_ready = 1;
    s_enabled = 1;
    printf("[S3&K] Sonic armed: A jumps, Down+B charges a spindash, "
           "spin attacks hurt enemies; spindash rolls break side bricks.\n");
    return 1;
}

int game_sonic_active(void)
{
    return s_enabled && game_smash64_sonic_selected();
}

int game_sonic_register_hooks(void)
{
    return 1;
}

void game_sonic_update_input(uint64_t frame_count)
{
    (void)frame_count;
}

void game_sonic_update(uint64_t frame_count)
{
    (void)frame_count;
    if (game_sonic_active()) {
        s3k_sonic_set_fire_shield(g_ram[PlayerStatus] >= 2);
        s_present_frame++;
    } else {
        s3k_sonic_set_fire_shield(0);
    }
}

void game_sonic_render_post_render(uint32_t *framebuffer)
{
    Smash64ScriptedPresentation scripted_presentation;
    if (!framebuffer || !game_sonic_active() || !s_owner_ready ||
        g_ram[OperMode] != 1) return;
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
    draw_sonic(framebuffer);
    s_draw_behind_background = 0;
}
