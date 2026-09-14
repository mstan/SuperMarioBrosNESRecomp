/*
 * Sonic 3 & Knuckles Sonic presentation for SMB1.
 *
 * Every visible frame comes from the owner ROM through S3K's own sprite
 * pipeline: Map_Sonic pieces, DPLC_Sonic tile lists, ArtUnc_Sonic tiles and
 * Pal_SonicTails (palette line 0). The mapping frame and flip are exactly
 * what Animate_Sonic produced for this frame (mods/s3k/s3k_player.c), drawn
 * around S3K's object origin: the body centre, y_radius above the floor the
 * feet touch. The Insta-Shield, Fire Shield, standard shield, invincibility
 * stars, dash dust and rings are drawn from their own mappings with S3K's
 * layering and blink.
 *
 * Everything is composited at SONIC_SCALE_NUM/SONIC_SCALE_DEN of S3K's pixel
 * size so Sonic stands about as tall as Big Mario. Each source mapping is
 * first rendered 1:1 into a canvas, then resampled on a grid anchored to the
 * object origin (so a frame always resamples identically, and mirrored
 * frames stay mirror images), keeping each destination pixel's dominant
 * colour but letting a clearly darker outline pixel win its share.
 *
 * The picture a frame presents is SMB1's previous frame: that frame's NMI
 * wrote the scroll, OAM and nametable updates the PPU then rendered. So the
 * post-render pass draws Sonic into a layer built from the frame's state
 * and shows that layer with the next picture, the one made from the same
 * state; a frame early, Sonic would slide against lifts, enemies and the
 * background whenever his screen position changes.
 */
#include "game_sonic.h"

#include "game_smash64.h"
#include "game_sonic_adapter.h"
#include "game_sonic_audio.h"
#include "game_sonic_items.h"
#include "mods/s3k/s3k_rings.h"
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
#define S2_ROM_BYTES  1048576L

/* Offsets in the verified S3&K lock-on image (the S&K half). */
#define S3K_SONIC_ART_OFF          0x100000u  /* ArtUnc_Sonic      */
#define S3K_SONIC_MAP_OFF          0x146620u  /* Map_Sonic         */
#define S3K_SONIC_DPLC_OFF         0x148182u  /* PLC_Sonic         */
#define S3K_SONIC_PALETTE_OFF      0x0A8A3Cu  /* Pal_SonicTails    */
#define S3K_SONIC_MAP_COUNT        0xDAu
#define S3K_INSTA_SHIELD_ART_OFF   0x18C084u  /* ArtUnc_InstaShield */
#define S3K_INSTA_SHIELD_MAP_OFF   0x01A0D0u  /* Map_InstaShield    */
#define S3K_INSTA_SHIELD_DPLC_OFF  0x01A154u  /* DPLC_InstaShield   */
#define S3K_INSTA_SHIELD_MAP_COUNT 8u
#define S3K_FIRE_SHIELD_ART_OFF    0x18C704u  /* ArtUnc_FireShield  */
#define S3K_FIRE_SHIELD_MAP_OFF    0x019AC6u  /* Map_FireShield     */
#define S3K_FIRE_SHIELD_DPLC_OFF   0x019CE6u  /* DPLC_FireShield    */
#define S3K_FIRE_SHIELD_MAP_COUNT  25u
#define S3K_BUBBLE_SHIELD_ART_OFF  0x18F984u  /* ArtUnc_BubbleShield */
#define S3K_BUBBLE_SHIELD_MAP_OFF  0x019F82u  /* Map_BubbleShield    */
#define S3K_BUBBLE_SHIELD_DPLC_OFF 0x01A076u  /* DPLC_BubbleShield   */
#define S3K_BUBBLE_SHIELD_MAP_COUNT 13u
#define S3K_S2_SHIELD_MAP_OFF      0x018A42u  /* Map_S2Shield        */
#define S3K_S2_SHIELD_MAP_COUNT    6u
#define S3K_DASH_DUST_ART_OFF      0x18A604u  /* ArtUnc_DashDust     */
#define S3K_DASH_DUST_MAP_OFF      0x018DF4u  /* Map_DashDust        */
#define S3K_DASH_DUST_DPLC_OFF     0x018EE2u  /* DPLC_DashSplashDrown */
#define S3K_DASH_DUST_MAP_COUNT    30u
#define S3K_INVINCIBILITY_ART_OFF  0x18A204u  /* ArtUnc_Invincibility (no DPLC) */
#define S3K_INVINCIBILITY_MAP_OFF  0x018AEAu  /* Map_Invincibility   */
#define S3K_INVINCIBILITY_TILES    32u

/* Offsets in the verified Sonic 2 (World) (Rev A) image. */
#define S2_SHIELD_NEM_OFF          0x071D8Eu  /* ArtNem_Shield       */
#define S2_PALETTE_OFF             0x002902u  /* Pal_BGND line 0     */
#define S2_SHIELD_TILES            32u

#define S3K_TILE_BYTES 32u
#define S3K_MAX_FRAME_TILES 96u
#define S3K_CANVAS_SIZE 128
#define S3K_CANVAS_ORIGIN (S3K_CANVAS_SIZE / 2)
#define S3K_POS_TABLE 64

static int s_enabled;
static int s_owner_ready;
static uint64_t s_present_frame;
static int s_draw_behind_background;

/* Sonic's layer: framebuffer-sized colours plus, per pixel, whether it is
 * drawn and whether it goes behind opaque background (a pipe presentation),
 * which is decided against the picture it is finally shown over. */
#define LAYER_EMPTY 0
#define LAYER_FRONT 1
#define LAYER_BEHIND_BACKGROUND 2
static struct {
    uint32_t *color;
    uint8_t *kind;
    int width;
    int min_x, min_y, max_x, max_y;   /* bounds of the drawn pixels */
    int restart;                      /* a savestate replaced the frame */
} s_layer;
static uint8_t *s_owner_rom;
static uint32_t s_genesis_palette[16];
static uint32_t s_canvas[S3K_CANVAS_SIZE * S3K_CANVAS_SIZE];
static int s_canvas_min_x, s_canvas_min_y, s_canvas_max_x, s_canvas_max_y;

/* Sonic 2's standard shield: ArtNem_Shield and its palette line. */
static char *s_sonic2_rom_path;
static uint8_t s_s2_shield_art[S2_SHIELD_TILES * S3K_TILE_BYTES];
static uint32_t s_s2_palette[16];
static int s_s2_shield_ready;

/* Pos_table: Sonic's centre (world x, screen y) for the invincibility trail. */
static struct { int16_t x, y; } s_pos_table[S3K_POS_TABLE];
static unsigned s_pos_index;

/* Obj_DashDust: the spindash cloud (anim 2) and skid puffs (anim 3). */
typedef struct SonicDustPuff {
    uint8_t active;
    uint8_t expiring;     /* Animate_Sprite hit $FC: drawn once more */
    uint8_t anim_frame;
    uint8_t anim_timer;
    uint8_t mapping_frame;
    int32_t world_x;
    int32_t y;
} SonicDustPuff;
static SonicDustPuff s_puffs[8];
static uint8_t s_skid_timer;
static uint8_t s_spindash_dust_frame;
static uint8_t s_spindash_dust_timer;
static uint8_t s_spindash_dust_mapping;
static uint8_t s_spindash_dust_live;

/* Obj_Invincibility: one parent and three trailing children. */
static struct {
    uint8_t angle;       /* $34 */
    uint16_t seq_index;  /* $38 */
} s_stars[4];
static int s_stars_live;

static uint8_t *read_rom_file(const char *rom_path, long expected_size)
{
    SDL_RWops *file;
    uint8_t *data;
    if (!rom_path || !*rom_path) return NULL;
    file = SDL_RWFromFile(rom_path, "rb");
    if (!file) return NULL;
    if (SDL_RWsize(file) != expected_size) {
        SDL_RWclose(file);
        return NULL;
    }
    data = (uint8_t *)malloc((size_t)expected_size);
    if (!data) {
        SDL_RWclose(file);
        return NULL;
    }
    if (SDL_RWread(file, data, 1, (size_t)expected_size) !=
        (size_t)expected_size) {
        SDL_RWclose(file);
        free(data);
        return NULL;
    }
    SDL_RWclose(file);
    return data;
}

static int probe_owner_rom(const char *rom_path)
{
    uint8_t *data = read_rom_file(rom_path, S3K_ROM_BYTES);
    if (!data) return 0;
    free(s_owner_rom);
    s_owner_rom = data;
    return 1;
}

static uint16_t be16_in(const uint8_t *rom, long size, uint32_t off)
{
    if (!rom || (long)off + 1 >= size) return 0;
    return (uint16_t)((rom[off] << 8) | rom[off + 1u]);
}

static uint16_t be16_at(uint32_t off)
{
    return be16_in(s_owner_rom, S3K_ROM_BYTES, off);
}

/* Genesis CRAM 0BGR (3 bits each) through the VDP's linear DAC levels. */
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

/* Nem_Decomp_Main / Nem_Build_Code_Table / Nem_Process_Compressed_Data,
 * decompressing to RAM. Returns the number of 8x8 patterns produced. */
static unsigned nemesis_decompress(const uint8_t *src, size_t avail,
                                   uint8_t *dst, size_t cap_tiles)
{
    uint16_t table[256];
    size_t p = 0;
    uint16_t header, patterns, rows_left;
    int xor_mode;
    uint16_t d5, d6;
    uint32_t d2 = 0, d4 = 0;
    unsigned d3 = 8;
    size_t out = 0;

#define NEM_BYTE() (p < avail ? src[p++] : 0)
    if (avail < 4) return 0;
    header = (uint16_t)((NEM_BYTE() << 8) | NEM_BYTE());
    xor_mode = (header & 0x8000u) != 0;
    patterns = (uint16_t)(header & 0x7FFFu);
    if (patterns == 0 || patterns > cap_tiles) return 0;
    rows_left = (uint16_t)(patterns * 8u);

    memset(table, 0, sizeof(table));
    {
        uint8_t d0 = NEM_BYTE();
        uint16_t d7 = 0;
        while (d0 != 0xFF) {
            d7 = d0;
            for (;;) {
                uint8_t len, rep;
                d0 = NEM_BYTE();
                if (d0 >= 0x80) break;
                rep = (uint8_t)(d0 & 0x70);
                len = (uint8_t)(d0 & 0x0F);
                d7 = (uint16_t)((len << 8) | rep | (d7 & 0x0F));
                if (len == 8 || len == 0) {
                    table[NEM_BYTE()] = d7;
                } else if (len < 8) {
                    const unsigned shift = 8u - len;
                    unsigned code = (unsigned)NEM_BYTE() << shift;
                    for (unsigned n = 0; n < (1u << shift) && code < 256u; ++n)
                        table[code++] = d7;
                }
            }
            if (p >= avail) return 0;
        }
    }

    d5 = (uint16_t)((NEM_BYTE() << 8) | NEM_BYTE());
    d6 = 0x10;
    while (rows_left) {
        const uint16_t d1 = (uint16_t)((d5 >> (d6 - 8)) & 0xFF);
        uint16_t repeat;
        uint8_t pixel;
        if (d1 >= 0xFC) {
            uint16_t v;
            d6 = (uint16_t)(d6 - 6);
            if (d6 < 9) { d6 = (uint16_t)(d6 + 8); d5 = (uint16_t)((d5 << 8) | NEM_BYTE()); }
            d6 = (uint16_t)(d6 - 7);
            v = (uint16_t)(d5 >> d6);
            pixel = (uint8_t)(v & 0x0F);
            repeat = (uint16_t)((v & 0x70) >> 4);
            if (d6 < 9) { d6 = (uint16_t)(d6 + 8); d5 = (uint16_t)((d5 << 8) | NEM_BYTE()); }
        } else {
            const uint16_t entry = table[d1];
            d6 = (uint16_t)(d6 - (entry >> 8));
            if (d6 < 9) { d6 = (uint16_t)(d6 + 8); d5 = (uint16_t)((d5 << 8) | NEM_BYTE()); }
            pixel = (uint8_t)(entry & 0x0F);
            repeat = (uint16_t)((entry & 0xF0) >> 4);
        }
        for (int n = 0; n <= (int)repeat && rows_left; ++n) {
            d4 = (d4 << 4) | pixel;
            if (--d3 == 0) {
                uint32_t row = d4;
                if (xor_mode) {
                    d2 ^= d4;
                    row = d2;
                }
                if (out + 4 <= cap_tiles * S3K_TILE_BYTES) {
                    dst[out++] = (uint8_t)(row >> 24);
                    dst[out++] = (uint8_t)(row >> 16);
                    dst[out++] = (uint8_t)(row >> 8);
                    dst[out++] = (uint8_t)row;
                }
                rows_left--;
                d4 = 0;
                d3 = 8;
            }
        }
    }
#undef NEM_BYTE
    return patterns;
}

/* Sonic 2's shield: the Nemesis art at ArtNem_Shield and palette line 0,
 * whose colour order differs from S3K's Pal_SonicTails. */
static void load_sonic2_shield(void)
{
    uint8_t *rom;

    s_s2_shield_ready = 0;
    rom = read_rom_file(s_sonic2_rom_path, S2_ROM_BYTES);
    if (!rom) return;
    if (nemesis_decompress(rom + S2_SHIELD_NEM_OFF,
                           (size_t)(S2_ROM_BYTES - S2_SHIELD_NEM_OFF),
                           s_s2_shield_art, S2_SHIELD_TILES) ==
        S2_SHIELD_TILES) {
        for (unsigned i = 0; i < 16u; ++i)
            s_s2_palette[i] = i == 0 ? 0u : genesis_color(
                be16_in(rom, S2_ROM_BYTES, S2_PALETTE_OFF + i * 2u));
        s_s2_shield_ready = 1;
    }
    free(rom);
    if (!s_s2_shield_ready)
        fprintf(stderr, "[S3&K] Could not read Sonic 2's shield art; the "
                        "standard shield keeps its Bubble stand-in.\n");
}

void game_sonic_set_sonic2_rom(const char *path)
{
    free(s_sonic2_rom_path);
    s_sonic2_rom_path = NULL;
    if (path && *path) {
        const size_t n = strlen(path) + 1u;
        s_sonic2_rom_path = (char *)malloc(n);
        if (s_sonic2_rom_path) memcpy(s_sonic2_rom_path, path, n);
    }
}

static void layer_clear(void)
{
    if (s_layer.kind && s_layer.max_x >= 0) {
        for (int y = s_layer.min_y; y <= s_layer.max_y; ++y)
            memset(s_layer.kind + y * s_layer.width + s_layer.min_x, LAYER_EMPTY,
                   (size_t)(s_layer.max_x - s_layer.min_x + 1));
    }
    s_layer.min_x = s_layer.min_y = INT32_MAX;
    s_layer.max_x = s_layer.max_y = -1;
}

/* Size the layer to the framebuffer; a new width discards its contents. */
static int layer_prepare(void)
{
    if (s_layer.color && s_layer.width == g_render_width) return 1;
    free(s_layer.color);
    free(s_layer.kind);
    s_layer.width = g_render_width;
    s_layer.color = (uint32_t *)malloc((size_t)g_render_width * 240u *
                                       sizeof(uint32_t));
    s_layer.kind = (uint8_t *)calloc((size_t)g_render_width * 240u, 1u);
    s_layer.max_x = -1;
    if (!s_layer.color || !s_layer.kind) {
        free(s_layer.color);
        free(s_layer.kind);
        s_layer.color = NULL;
        s_layer.kind = NULL;
        s_layer.width = 0;
        return 0;
    }
    layer_clear();
    return 1;
}

static void layer_composite(uint32_t *fb)
{
    if (!s_layer.color || s_layer.width != g_render_width) return;
    for (int y = s_layer.min_y; y <= s_layer.max_y; ++y) {
        for (int x = s_layer.min_x; x <= s_layer.max_x; ++x) {
            const int i = y * s_layer.width + x;
            if (s_layer.kind[i] == LAYER_EMPTY ||
                (s_layer.kind[i] == LAYER_BEHIND_BACKGROUND &&
                 ppu_renderer_background_opaque(x, y)))
                continue;
            fb[i] = s_layer.color[i];
        }
    }
}

static void layer_plot(int x, int y, uint32_t color, uint8_t kind)
{
    const int i = y * s_layer.width + x;
    s_layer.color[i] = color;
    s_layer.kind[i] = kind;
    if (x < s_layer.min_x) s_layer.min_x = x;
    if (x > s_layer.max_x) s_layer.max_x = x;
    if (y < s_layer.min_y) s_layer.min_y = y;
    if (y > s_layer.max_y) s_layer.max_y = y;
}

static void put_pixel(int x, int y, uint32_t color)
{
    if (x >= 0 && x < g_render_width && y >= 0 && y < 240)
        layer_plot(x, y, color, s_draw_behind_background
                                    ? LAYER_BEHIND_BACKGROUND : LAYER_FRONT);
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

static void canvas_clear(void)
{
    memset(s_canvas, 0, sizeof(s_canvas));
    s_canvas_min_x = s_canvas_min_y = S3K_CANVAS_SIZE;
    s_canvas_max_x = s_canvas_max_y = -1;
}

static void draw_tile_data(const uint8_t *tile, const uint32_t *palette,
                           int source_x, int source_y, int hflip, int vflip)
{
    for (int py = 0; py < 8; ++py) {
        const int sy = vflip ? 7 - py : py;
        for (int px = 0; px < 8; ++px) {
            const int sx = hflip ? 7 - px : px;
            const uint8_t b = tile[(unsigned)sy * 4u + (unsigned)sx / 2u];
            const uint8_t pal = (sx & 1) ? (uint8_t)(b & 0x0F) : (uint8_t)(b >> 4);
            const int cx = S3K_CANVAS_ORIGIN + source_x + px;
            const int cy = S3K_CANVAS_ORIGIN + source_y + py;
            if (pal == 0) continue;
            if (cx < 0 || cx >= S3K_CANVAS_SIZE || cy < 0 || cy >= S3K_CANVAS_SIZE)
                continue;
            s_canvas[cy * S3K_CANVAS_SIZE + cx] = palette[pal];
            if (cx < s_canvas_min_x) s_canvas_min_x = cx;
            if (cx > s_canvas_max_x) s_canvas_max_x = cx;
            if (cy < s_canvas_min_y) s_canvas_min_y = cy;
            if (cy > s_canvas_max_y) s_canvas_max_y = cy;
        }
    }
}

/* Where a mapping's VRAM-relative tile index comes from. */
typedef struct TileSource {
    const uint8_t *base;      /* 32-byte 4bpp patterns */
    size_t pattern_count;
    const uint16_t *dplc;     /* NULL: tile index addresses `base` directly */
    int dplc_count;
    const uint32_t *palette;
} TileSource;

static void render_pieces(uint32_t map_off, unsigned map_count, unsigned frame,
                          int mirror, const TileSource *src)
{
    uint32_t ptr;
    unsigned pieces;

    if (!s_owner_rom || frame >= map_count) return;
    ptr = map_off + be16_at(map_off + frame * 2u);
    pieces = be16_at(ptr);
    ptr += 2u;
    if (pieces > 32u) return;

    for (unsigned i = 0; i < pieces; ++i) {
        const uint32_t p = ptr + i * 6u;
        const int y = (int)(int8_t)s_owner_rom[p];
        const uint8_t size = s_owner_rom[p + 1u];
        const uint16_t attr = be16_at(p + 2u);
        int x = (int)(int16_t)be16_at(p + 4u);
        const int tile_w = ((size >> 2) & 3) + 1;
        const int tile_h = (size & 3) + 1;
        int hflip = (attr & 0x0800u) != 0;
        const int vflip = (attr & 0x1000u) != 0;
        const int tile_base = attr & 0x07FF;

        if (mirror) {
            x = -x - tile_w * 8;
            hflip = !hflip;
        }
        for (int ty = 0; ty < tile_h; ++ty) {
            for (int tx = 0; tx < tile_w; ++tx) {
                const int stx = hflip ? tile_w - 1 - tx : tx;
                const int sty = vflip ? tile_h - 1 - ty : ty;
                /* Mega Drive pattern blocks advance down each column. */
                const int index = tile_base + stx * tile_h + sty;
                size_t pattern;
                if (index < 0) continue;
                if (src->dplc) {
                    if (index >= src->dplc_count) continue;
                    pattern = src->dplc[index];
                } else {
                    pattern = (size_t)index;
                }
                if (pattern >= src->pattern_count) continue;
                draw_tile_data(src->base + pattern * S3K_TILE_BYTES,
                               src->palette, x + tx * 8, y + ty * 8,
                               hflip, vflip);
            }
        }
    }
}

/* Render one S3K mapping frame into the canvas around the object origin,
 * applying render_flags bit 0 the way the VDP sprite builder does. The VRAM
 * patterns are the ones DPLC entry `dplc_frame` loaded, which is the mapping
 * frame itself except for objects that reuse another frame's upload. */
static int render_frame_dplc(uint32_t art_off, uint32_t map_off,
                             uint32_t dplc_off, unsigned map_count,
                             unsigned frame, unsigned dplc_frame, int mirror)
{
    uint16_t tiles[S3K_MAX_FRAME_TILES];
    const int vram_tiles = build_dplc_tiles(dplc_off, map_count, dplc_frame,
                                            tiles, S3K_MAX_FRAME_TILES);
    TileSource src;

    canvas_clear();
    if (vram_tiles <= 0 || frame >= map_count || !s_owner_rom) return 0;
    src.base = s_owner_rom + art_off;
    src.pattern_count = ((size_t)S3K_ROM_BYTES - art_off) / S3K_TILE_BYTES;
    src.dplc = tiles;
    src.dplc_count = vram_tiles;
    src.palette = s_genesis_palette;
    render_pieces(map_off, map_count, frame, mirror, &src);
    return 1;
}

static int render_frame(uint32_t art_off, uint32_t map_off, uint32_t dplc_off,
                        unsigned map_count, unsigned frame, int mirror)
{
    return render_frame_dplc(art_off, map_off, dplc_off, map_count, frame,
                             frame, mirror);
}

static int floor_div(int a, int b)
{
    return a >= 0 ? a / b : -((-a + b - 1) / b);
}

/* Destination offset i (from the origin) covers source span
 * [i*DEN/NUM, (i+1)*DEN/NUM). At 4/5 that is 5/4 of a source pixel, which
 * always overlaps exactly two source pixels; weights are in NUM-ths. */
static void scale_axis(int i, int *k0, int *w0, int *w1)
{
    const int start = i * SONIC_SCALE_DEN;
    *k0 = floor_div(start, SONIC_SCALE_NUM);
    *w0 = (*k0 + 1) * SONIC_SCALE_NUM - start;
    *w1 = SONIC_SCALE_DEN - *w0;
}

static uint32_t canvas_at(int x, int y)
{
    if (x < 0 || x >= S3K_CANVAS_SIZE || y < 0 || y >= S3K_CANVAS_SIZE)
        return 0;
    return s_canvas[y * S3K_CANVAS_SIZE + x];
}

static int color_luma(uint32_t c)
{
    return (int)((((c >> 16) & 0xFF) * 299 + ((c >> 8) & 0xFF) * 587 +
                  (c & 0xFF) * 114) / 1000);
}

/* Composite the canvas with its origin at (origin_x, origin_y). */
static void composite(int origin_x, int origin_y)
{
    const int total = SONIC_SCALE_DEN * SONIC_SCALE_DEN;
    int i0, i1, j0, j1;

    if (s_canvas_max_x < 0) return;
    i0 = floor_div((s_canvas_min_x - S3K_CANVAS_ORIGIN) * SONIC_SCALE_NUM,
                   SONIC_SCALE_DEN) - 1;
    i1 = floor_div((s_canvas_max_x + 1 - S3K_CANVAS_ORIGIN) * SONIC_SCALE_NUM,
                   SONIC_SCALE_DEN) + 1;
    j0 = floor_div((s_canvas_min_y - S3K_CANVAS_ORIGIN) * SONIC_SCALE_NUM,
                   SONIC_SCALE_DEN) - 1;
    j1 = floor_div((s_canvas_max_y + 1 - S3K_CANVAS_ORIGIN) * SONIC_SCALE_NUM,
                   SONIC_SCALE_DEN) + 1;

    for (int j = j0; j <= j1; ++j) {
        const int dy = origin_y + j;
        int ky, wy0, wy1;
        if (dy < 0 || dy >= 240) continue;
        scale_axis(j, &ky, &wy0, &wy1);
        ky += S3K_CANVAS_ORIGIN;
        for (int i = i0; i <= i1; ++i) {
            const int dx = origin_x + i;
            uint32_t c[4];
            int w[4], opaque = 0, best = -1, dark = -1;
            int kx, wx0, wx1;
            if (dx < 0 || dx >= g_render_width) continue;
            scale_axis(i, &kx, &wx0, &wx1);
            kx += S3K_CANVAS_ORIGIN;
            c[0] = canvas_at(kx, ky);         w[0] = wx0 * wy0;
            c[1] = canvas_at(kx + 1, ky);     w[1] = wx1 * wy0;
            c[2] = canvas_at(kx, ky + 1);     w[2] = wx0 * wy1;
            c[3] = canvas_at(kx + 1, ky + 1); w[3] = wx1 * wy1;
            if (!(c[0] | c[1] | c[2] | c[3])) continue;
            /* Merge equal colours into their first occurrence. */
            for (int a = 0; a < 4; ++a) {
                if (!c[a] || !w[a]) continue;
                for (int b = a + 1; b < 4; ++b) {
                    if (c[b] == c[a]) {
                        w[a] += w[b];
                        w[b] = 0;
                    }
                }
                opaque += w[a];
            }
            if (opaque * 2 < total) continue;
            for (int a = 0; a < 4; ++a) {
                if (!c[a] || !w[a]) continue;
                if (best < 0 || w[a] > w[best] ||
                    (w[a] == w[best] && color_luma(c[a]) < color_luma(c[best])))
                    best = a;
                if (dark < 0 || color_luma(c[a]) < color_luma(c[dark]))
                    dark = a;
            }
            if (dark != best && w[dark] * 5 >= total &&
                color_luma(c[dark]) + 40 < color_luma(c[best]))
                best = dark;
            put_pixel(dx, dy, c[best]);
        }
    }
}

/* ------------------------------------------------------------- shields -- */

/* Ani_BubbleShield anim 0: the stand-in for Obj_S2Shield without Sonic 2's
 * art (S3K itself has none). */
static const uint8_t k_bubble_idle[] = {
    0x00, 0x09, 0x00, 0x09, 0x00, 0x09, 0x01, 0x0A, 0x01, 0x0A, 0x01, 0x0A,
    0x02, 0x09, 0x02, 0x09, 0x02, 0x09, 0x03, 0x0A, 0x03, 0x0A, 0x03, 0x0A,
    0x04, 0x09, 0x04, 0x09, 0x04, 0x09, 0x05, 0x0A, 0x05, 0x0A, 0x05, 0x0A,
    0x06, 0x09, 0x06, 0x09, 0x06, 0x09, 0x07, 0x0A, 0x07, 0x0A, 0x07, 0x0A,
    0x08, 0x09, 0x08, 0x09, 0x08, 0x09
};

static void draw_shield(const S3KPlayer *p, int ox, int oy)
{
    if (p->status_secondary & S3K_STATUS2_FIRE) {
        if (render_frame(S3K_FIRE_SHIELD_ART_OFF, S3K_FIRE_SHIELD_MAP_OFF,
                         S3K_FIRE_SHIELD_DPLC_OFF, S3K_FIRE_SHIELD_MAP_COUNT,
                         p->shield_mapping_frame, p->shield_hflip))
            composite(ox, oy);
        return;
    }
    if ((p->status_secondary & S3K_STATUS2_SHIELD) &&
        !(p->status_secondary & S3K_STATUS2_INVINCIBLE)) {
        /* While an Insta-Shield plays under it (shield anim 1 owns the
         * mapping frame), the shield keeps cycling Ani_S2Shield's ten
         * one-frame steps underneath the attack. */
        static const uint8_t k_s2shield_steps[] = {
            0x05, 0x00, 0x05, 0x01, 0x05, 0x02, 0x05, 0x03, 0x05, 0x04
        };
        const int insta = p->shield_anim == 1;
        const uint8_t frame = insta
            ? k_s2shield_steps[s_present_frame % sizeof(k_s2shield_steps)]
            : p->shield_mapping_frame;
        if (s_s2_shield_ready) {
            /* Obj_S2Shield: Map_S2Shield with Sonic 2's ArtNem_Shield. */
            TileSource src;
            src.base = s_s2_shield_art;
            src.pattern_count = S2_SHIELD_TILES;
            src.dplc = NULL;
            src.dplc_count = 0;
            src.palette = s_s2_palette;
            canvas_clear();
            render_pieces(S3K_S2_SHIELD_MAP_OFF, S3K_S2_SHIELD_MAP_COUNT,
                          frame, p->shield_hflip, &src);
            composite(ox, oy);
        } else if (render_frame(S3K_BUBBLE_SHIELD_ART_OFF,
                                S3K_BUBBLE_SHIELD_MAP_OFF,
                                S3K_BUBBLE_SHIELD_DPLC_OFF,
                                S3K_BUBBLE_SHIELD_MAP_COUNT,
                                k_bubble_idle[(s_present_frame / 2u) %
                                              sizeof(k_bubble_idle)],
                                p->shield_hflip)) {
            composite(ox, oy);
        }
        if (!insta) return;
    }
    if (render_frame(S3K_INSTA_SHIELD_ART_OFF, S3K_INSTA_SHIELD_MAP_OFF,
                     S3K_INSTA_SHIELD_DPLC_OFF, S3K_INSTA_SHIELD_MAP_COUNT,
                     p->shield_mapping_frame, p->shield_hflip))
        composite(ox, oy);
}

/* ---------------------------------------------------------- dash dust -- */

/* Animate_Sprite over Ani_DashSplashDrown's anim 2 (spindash) and 3 (puff). */
static const uint8_t k_dust_spindash[] = { 0x01, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0xFF };
static const uint8_t k_dust_puff[] = { 0x03, 0x11, 0x12, 0x13, 0x14, 0xFC };
/* The skid routine leaves mapping_frame $15 on the parent dust object, whose
 * DPLC upload the puffs' own frames ($11-$14, empty DPLC entries) draw from. */
#define S3K_SKID_PUFF_DPLC_FRAME 0x15u

static int world_to_screen_x(int world_x)
{
    const int left = ((int)g_ram[ScreenLeft_PageLoc] << 8) |
                     (int)g_ram[ScreenLeft_X_Pos];
    /* World x is modulo 65536: Player_PageLoc wraps through $FF/$00. */
    return (int)(int16_t)(uint16_t)(world_x - left) + g_widescreen_left;
}

/* Obj_DashDust anim 1 (loc_18BC8): the splash, at the water line under the
 * x the player had when it started, Ani_DashSplashDrown frames 1-9 at
 * delay 3, then anim 0's empty frame. */
static const uint8_t k_dust_splash[] = { 0x03, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0xFD };
#define SONIC_WATER_LINE_Y 0x24   /* Player_Y $14 + the 32px body's centre */
static struct {
    uint8_t live;
    uint8_t anim_frame;
    uint8_t anim_timer;
    uint8_t mapping_frame;
    int32_t world_x;
} s_splash;

static void update_splash(int world_x)
{
    if (s3k_sonic_take_splash()) {
        memset(&s_splash, 0, sizeof(s_splash));
        s_splash.live = 1;
        s_splash.world_x = world_x;
    }
    if (!s_splash.live) return;
    if (s_splash.anim_timer) {
        s_splash.anim_timer--;
        return;
    }
    s_splash.anim_timer = k_dust_splash[0];
    if (k_dust_splash[1u + s_splash.anim_frame] == 0xFD) {
        s_splash.live = 0;
        return;
    }
    s_splash.mapping_frame = k_dust_splash[1u + s_splash.anim_frame];
    s_splash.anim_frame++;
}

static void update_dust(const S3KPlayer *p, int world_x, int center_y)
{
    /* Obj_DashDust anim 2 (loc_18C20): follows the player while the
     * spindash is charging. A roll held in a tunnel also carries
     * spin_dash_flag but never started the dust. */
    if (p->spin_dash_flag && p->dust_state == S3K_DUST_SPINDASH &&
        p->routine == S3K_ROUTINE_CONTROL) {
        if (!s_spindash_dust_live) {
            s_spindash_dust_live = 1;
            s_spindash_dust_frame = 0;
            s_spindash_dust_timer = 0;
        }
        if (s_spindash_dust_timer) {
            s_spindash_dust_timer--;
        } else {
            uint8_t f;
            s_spindash_dust_timer = k_dust_spindash[0];
            f = k_dust_spindash[1u + s_spindash_dust_frame];
            if (f == 0xFF) {
                s_spindash_dust_frame = 0;
                f = k_dust_spindash[1];
            }
            s_spindash_dust_mapping = f;
            s_spindash_dust_frame++;
        }
    } else {
        s_spindash_dust_live = 0;
    }

    /* Puffs whose script reached $FC were drawn one last time; delete. */
    for (int i = 0; i < (int)(sizeof(s_puffs) / sizeof(s_puffs[0])); ++i)
        if (s_puffs[i].expiring) s_puffs[i].active = s_puffs[i].expiring = 0;

    /* Routine 6 (loc_18CB6): a puff every fourth frame of the skid, at the
     * player's feet ($10 below the centre); puffs stay where they spawned. */
    if (p->anim == S3K_ANIM_SKID && !(p->status & S3K_STATUS_UNDERWATER)) {
        if (s_skid_timer == 0 || --s_skid_timer == 0xFF) {
            s_skid_timer = 3;
            for (int i = 0; i < (int)(sizeof(s_puffs) / sizeof(s_puffs[0])); ++i) {
                if (s_puffs[i].active) continue;
                memset(&s_puffs[i], 0, sizeof(s_puffs[i]));
                s_puffs[i].active = 1;
                s_puffs[i].mapping_frame = 0x11;
                s_puffs[i].world_x = world_x;
                s_puffs[i].y = center_y + sonic_scale_px(0x10);
                break;
            }
        }
    } else {
        s_skid_timer = 0;
    }
    for (int i = 0; i < (int)(sizeof(s_puffs) / sizeof(s_puffs[0])); ++i) {
        SonicDustPuff *puff = &s_puffs[i];
        if (!puff->active) continue;
        if (puff->anim_timer) {
            puff->anim_timer--;
            continue;
        }
        puff->anim_timer = k_dust_puff[0];
        if (k_dust_puff[1u + puff->anim_frame] == 0xFC) {
            /* $FC advances the routine; Draw_Sprite still runs this frame
             * and Delete_Current_Sprite runs on the next. */
            puff->expiring = 1;
            continue;
        }
        puff->mapping_frame = k_dust_puff[1u + puff->anim_frame];
        puff->anim_frame++;
    }
}

static void draw_dust(const S3KPlayer *p, int ox, int oy)
{
    if (s_spindash_dust_live &&
        render_frame(S3K_DASH_DUST_ART_OFF, S3K_DASH_DUST_MAP_OFF,
                     S3K_DASH_DUST_DPLC_OFF, S3K_DASH_DUST_MAP_COUNT,
                     s_spindash_dust_mapping, p->render_hflip))
        composite(ox, oy);
    for (int i = 0; i < (int)(sizeof(s_puffs) / sizeof(s_puffs[0])); ++i) {
        if (!s_puffs[i].active) continue;
        if (render_frame_dplc(S3K_DASH_DUST_ART_OFF, S3K_DASH_DUST_MAP_OFF,
                              S3K_DASH_DUST_DPLC_OFF, S3K_DASH_DUST_MAP_COUNT,
                              s_puffs[i].mapping_frame,
                              S3K_SKID_PUFF_DPLC_FRAME, 0))
            composite(world_to_screen_x(s_puffs[i].world_x), s_puffs[i].y);
    }
    if (s_splash.live && s_splash.mapping_frame &&
        render_frame(S3K_DASH_DUST_ART_OFF, S3K_DASH_DUST_MAP_OFF,
                     S3K_DASH_DUST_DPLC_OFF, S3K_DASH_DUST_MAP_COUNT,
                     s_splash.mapping_frame, 0))
        composite(world_to_screen_x(s_splash.world_x), SONIC_WATER_LINE_Y);
}

/* ------------------------------------------------------- invincibility -- */

/* byte_189A0: 32 orbit offsets. */
static const int8_t k_star_orbit[64] = {
    0x0F, 0x00, 0x0F, 0x03, 0x0E, 0x06, 0x0D, 0x08, 0x0B, 0x0B, 0x08, 0x0D, 0x06, 0x0E, 0x03, 0x0F,
    0x00, 0x10, -4, 0x0F, -7, 0x0E, -9, 0x0D, -0x0C, 0x0B, -0x0E, 0x08, -0x0F, 0x06, -0x10, 0x03,
    -0x10, 0x00, -0x10, -4, -0x0F, -7, -0x0E, -9, -0x0C, -0x0C, -9, -0x0E, -7, -0x0F, -4, -0x10,
    -1, -0x10, 0x03, -0x10, 0x06, -0x0F, 0x08, -0x0E, 0x0B, -0x0C, 0x0D, -9, 0x0E, -7, 0x0F, -4
};
static const uint8_t k_star_seq_parent[] = { 8, 5, 7, 6, 6, 7, 5, 8, 6, 7, 7, 6, 0xFF };
static const uint8_t k_star_seq_1[] = { 8, 7, 6, 5, 4, 3, 4, 5, 6, 7, 0xFF, 3, 4, 5, 6, 7, 8, 7, 6, 5, 4 };
static const uint8_t k_star_seq_2[] = { 8, 7, 6, 5, 4, 3, 2, 3, 4, 5, 6, 7, 0xFF, 2, 3, 4, 5, 6, 7, 8, 7, 6, 5, 4, 3 };
static const uint8_t k_star_seq_3[] = { 7, 6, 5, 4, 3, 2, 1, 2, 3, 4, 5, 6, 0xFF, 1, 2, 3, 4, 5, 6, 7, 6, 5, 4, 3, 2 };

typedef struct StarSprite { int16_t x, y; uint8_t frame; } StarSprite;
static StarSprite s_star_sprites[8];
static int s_star_sprite_count;

static void update_stars(const S3KPlayer *p)
{
    static const struct { const uint8_t *seq; uint8_t len; uint8_t second; uint8_t start_angle; } k_child[3] = {
        { k_star_seq_1, sizeof(k_star_seq_1), 0x0B, 0x00 },
        { k_star_seq_2, sizeof(k_star_seq_2), 0x0D, 0x16 },
        { k_star_seq_3, sizeof(k_star_seq_3), 0x0D, 0x2C },
    };
    const int left = (p->status & S3K_STATUS_FACING_LEFT) != 0;

    s_star_sprite_count = 0;
    if (!(p->status_secondary & S3K_STATUS2_INVINCIBLE)) {
        s_stars_live = 0;
        return;
    }
    if (!s_stars_live) {
        s_stars_live = 1;
        memset(s_stars, 0, sizeof(s_stars));
        s_stars[0].angle = 4;
        for (int i = 0; i < 3; ++i) s_stars[1 + i].angle = k_child[i].start_angle;
    }
    for (int obj = 0; obj < 4; ++obj) {
        int16_t cx, cy;
        uint8_t f1, f2;
        if (obj == 0) {
            const unsigned idx = s_pos_index;
            cx = s_pos_table[idx].x;
            cy = s_pos_table[idx].y;
            if (k_star_seq_parent[s_stars[0].seq_index] == 0xFF) s_stars[0].seq_index = 0;
            f1 = f2 = k_star_seq_parent[s_stars[0].seq_index];
            s_stars[0].seq_index++;
        } else {
            /* Obj_188E8 reads Pos_table_index - 12*n; the index names the
             * next write slot, so that is 3n-1 entries before the latest. */
            const unsigned back = (unsigned)obj * 3u - 1u;
            const unsigned idx = (s_pos_index + S3K_POS_TABLE - back) % S3K_POS_TABLE;
            const uint8_t *seq = k_child[obj - 1].seq;
            uint16_t si;
            cx = s_pos_table[idx].x;
            cy = s_pos_table[idx].y;
            if (seq[s_stars[obj].seq_index] == 0xFF) s_stars[obj].seq_index = 0;
            si = s_stars[obj].seq_index;
            f1 = seq[si];
            f2 = seq[(unsigned)si + k_child[obj - 1].second < k_child[obj - 1].len
                         ? (unsigned)si + k_child[obj - 1].second : 0u];
            s_stars[obj].seq_index++;
        }
        for (int sub = 0; sub < 2; ++sub) {
            const uint8_t angle = (uint8_t)(s_stars[obj].angle + (sub ? 0x20 : 0));
            const unsigned o = angle & 0x3Eu;
            if (s_star_sprite_count < 8) {
                s_star_sprites[s_star_sprite_count].x =
                    (int16_t)(cx + sonic_scale_px(k_star_orbit[o]));
                s_star_sprites[s_star_sprite_count].y =
                    (int16_t)(cy + sonic_scale_px(k_star_orbit[o + 1u]));
                s_star_sprites[s_star_sprite_count].frame = sub ? f2 : f1;
                s_star_sprite_count++;
            }
        }
        s_stars[obj].angle = (uint8_t)(s_stars[obj].angle +
            (obj == 0 ? (left ? -0x12 : 0x12) : (left ? -2 : 2)));
    }
}

static void draw_stars(void)
{
    TileSource src;
    if (!s_owner_rom) return;
    src.base = s_owner_rom + S3K_INVINCIBILITY_ART_OFF;
    src.pattern_count = S3K_INVINCIBILITY_TILES;
    src.dplc = NULL;
    src.dplc_count = 0;
    src.palette = s_genesis_palette;
    for (int i = 0; i < s_star_sprite_count; ++i) {
        canvas_clear();
        render_pieces(S3K_INVINCIBILITY_MAP_OFF, 9u, s_star_sprites[i].frame, 0, &src);
        composite(world_to_screen_x(s_star_sprites[i].x), s_star_sprites[i].y);
    }
}

/* ---------------------------------------------------------------- rings -- */

static void draw_nes_sprite_tile(uint8_t tile, uint8_t attr, int x, int y);

/* Scattered rings are SMB1's own coins on screen, drawn as JCoinGfxHandler
 * draws a coin jumping out of a block: JumpingCoinTiles over two sprites,
 * the lower one flipped vertically, sprite palette 2. Obj_Bouncing_Ring's
 * spill animation frame (which slows as the rings age) picks the tile, so
 * the coins spin down the way the rings would. A collected ring simply
 * disappears, as a coin does. */
static void draw_rings(void)
{
    static const uint8_t k_coin_tiles[4] = { 0x60, 0x61, 0x62, 0x63 };
    const S3KRingSpill *rings = game_sonic_adapter_rings();

    if (!rings || !(g_ppumask & 0x10)) return;
    for (int i = 0; i < S3K_RING_SPILL_MAX; ++i) {
        const S3KRing *r = &rings->rings[i];
        const int x = world_to_screen_x(r->x >> 8) - 4;
        const int y = (r->y >> 8) - 8;
        uint8_t tile;
        if (r->state != S3K_RING_BOUNCING) continue;
        tile = k_coin_tiles[r->mapping_frame & 3u];
        /* OAM Y is one line above the picture line it starts on. */
        draw_nes_sprite_tile(tile, 0x02, x, y + 1);
        draw_nes_sprite_tile(tile, 0x82, x, y + 9);
    }
}

/* -------------------------------------------------------- brick debris -- */

/* DrawBrickChunks for the adapter's chunk pairs: tile $84 with sprite
 * palette 3, flipped by FrameCounter d3/d2, and each pair's mirror image
 * placed 2*Orig-X+7 (the carry-in of its sbc/adc). These are SMB1 objects,
 * so they keep the NES pixel scale. */
static void draw_nes_sprite_tile(uint8_t tile, uint8_t attr, int x, int y)
{
    const int pattern = (g_ppuctrl & 0x08) ? 0x1000 : 0x0000;
    for (int ty = 0; ty < 8; ++ty) {
        const int dy = y + ty;
        const int off = pattern + tile * 16 + ((attr & 0x80) ? 7 - ty : ty);
        if (dy < 0 || dy >= 240) continue;
        for (int tx = 0; tx < 8; ++tx) {
            const int dx = x + tx;
            const int bit = (attr & 0x40) ? tx : 7 - tx;
            const int color = ((g_chr_ram[off] >> bit) & 1) |
                              (((g_chr_ram[off + 8] >> bit) & 1) << 1);
            if (!color || dx < 0 || dx >= g_render_width) continue;
            if (dx - g_widescreen_left < 8 && dx >= g_widescreen_left &&
                !(g_ppumask & 0x04))
                continue;
            /* OAM attribute d5 puts the sprite behind the background. */
            layer_plot(dx, dy,
                       g_nes_palette[g_ppu_pal[16 + (attr & 3) * 4 + color] & 0x3F],
                       (attr & 0x20) ? LAYER_BEHIND_BACKGROUND : LAYER_FRONT);
        }
    }
}

static void draw_brick_debris(void)
{
    const SonicBrickDebris *debris = game_sonic_adapter_brick_debris();
    const uint8_t attr = (uint8_t)((((unsigned)g_ram[FrameCounter] << 4) & 0xC0u) | 0x03u);

    if (!debris || !(g_ppumask & 0x10)) return;
    for (int i = 0; i < SONIC_BRICK_DEBRIS_MAX; ++i) {
        const SonicBrickDebris *d = &debris[i];
        const int left_x = world_to_screen_x(d->x);
        const int right_x = world_to_screen_x(2 * d->orig_x - d->x + 7);
        if (!d->active) continue;
        for (int r = 0; r < 2; ++r) {
            /* OAM Y $EF and beyond is below the visible picture. */
            if (d->row[r].y_high != 1 || d->row[r].y_pos >= 0xEF) continue;
            draw_nes_sprite_tile(0x84, attr, left_x, d->row[r].y_pos + 1);
            draw_nes_sprite_tile(0x84, attr, right_x, d->row[r].y_pos + 1);
        }
    }
}

/* ------------------------------------------------ pooled SMB1 objects -- */

/* The blocks, jumping coins and power-ups game_sonic_items.c keeps beyond
 * SMB1's own slots, drawn as SMB1's handlers draw them. */
static void draw_items(void)
{
    static const uint8_t k_coin_tiles[4] = { 0x60, 0x61, 0x62, 0x63 };
    const SonicItems *items = game_sonic_items();
    const int ground = g_ram[AreaType] == 1;

    /* Sonic's sprite across (centre +-12 at his scale) and his feet. */
    const int sonic_x = world_to_screen_x(((int)g_ram[Player_PageLoc] << 8) |
                                          (int)g_ram[Player_X_Position]) + 8;
    const int sonic_feet = g_ram[Player_Y_HighPos] == 1
                               ? (int)g_ram[Player_Y_Position] + 32 : -1;

    if (!items || !(g_ppumask & 0x10)) return;
    for (int i = 0; i < SONIC_BUMP_BLOCK_MAX; ++i) {
        /* DrawBlock: brick tiles $85/$86 (lineless $86 on top outside
         * ground areas), or a used block's $87 mirrored four ways. */
        const SonicBumpBlock *b = &items->blocks[i];
        const int x = world_to_screen_x(b->x);
        int y = b->row.y_pos + 1;
        if ((b->active != 1 && b->active != 2) || b->row.y_high != 1 ||
            b->row.y_pos >= 0xEF)
            continue;
        /* Sonic's Insta-Shield bumps blocks beside his feet, and he can land
         * on one mid-bounce, which no head-bumped block in SMB1 ever carries.
         * The block does not rise through the feet of a Sonic standing on it
         * or coming down onto it: it bounced up through his legs and he
         * looked to be walking inside it. */
        if (sonic_feet >= 0 && sonic_feet <= 0x20 + b->orig_ypos &&
            sonic_x + 12 > x && sonic_x - 12 < x + 16 &&
            b->row.y_pos < sonic_feet)
            y = sonic_feet + 1;
        if (b->metatile == 0xC4) {
            const uint8_t attr = ground ? 0x03 : 0x01;
            draw_nes_sprite_tile(0x87, attr, x, y);
            draw_nes_sprite_tile(0x87, attr | 0x40, x + 8, y);
            draw_nes_sprite_tile(0x87, attr | 0x80, x, y + 8);
            draw_nes_sprite_tile(0x87, attr | 0xC0, x + 8, y + 8);
        } else {
            const uint8_t top = ground ? 0x85 : 0x86;
            draw_nes_sprite_tile(top, 0x03, x, y);
            draw_nes_sprite_tile(top, 0x03, x + 8, y);
            draw_nes_sprite_tile(0x86, 0x03, x, y + 8);
            draw_nes_sprite_tile(0x86, 0x03, x + 8, y + 8);
        }
    }
    for (int i = 0; i < SONIC_JUMP_COIN_MAX; ++i) {
        /* JCoinGfxHandler: the coin over two sprites (the lower flipped),
         * then DrawFloateyNumber_Coin's "200". */
        const SonicJumpCoin *c = &items->coins[i];
        const int x = world_to_screen_x(c->x);
        const int y = c->row.y_pos + 1;
        if (!c->state || c->row.y_high != 1) continue;
        if (c->state == 1) {
            const uint8_t tile = k_coin_tiles[(g_ram[FrameCounter] >> 1) & 3];
            draw_nes_sprite_tile(tile, 0x02, x, y);
            draw_nes_sprite_tile(tile, 0x82, x, y + 8);
        } else {
            draw_nes_sprite_tile(0xF7, 0x02, x, y);
            draw_nes_sprite_tile(0xFB, 0x02, x + 8, y);
        }
    }
    for (int i = 0; i < SONIC_POWERUP_MAX; ++i) {
        /* The sprites DrawPowerUp wrote when the item last ran. */
        const SonicPowerUp *p = &items->powerups[i];
        if (!p->active) continue;
        for (int s = 0; s < 16; s += 4) {
            if (p->oam[s] >= 0xEF) continue;
            draw_nes_sprite_tile(p->oam[s + 1], p->oam[s + 2],
                                 p->oam[s + 3] + g_widescreen_left,
                                 p->oam[s] + 1);
        }
    }
}

/* ---------------------------------------------------------------- Sonic -- */

/* Kill_Character's arc: y_vel -$700 then MoveSprite_TestGravity ($38) with
 * no collision, drawn over SMB1's own death timing (the freeze included)
 * and music. */
static int s_death_live;
static int32_t s_death_y;      /* screen y of the body centre, 16.8 */
static int16_t s_death_y_vel;
static int s_death_screen_x;

/* Scripted SMB sequences (pipes, flagpole, autowalk, death) are native, so
 * the S3K object is not ticking; present them with S3K's own scripts. */
static unsigned scripted_frame(Smash64ScriptedPresentation scripted,
                               int *mirror)
{
    static const uint8_t k_walk[] = { 0x07, 0x08, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06 };
    static const uint8_t k_hang[] = { 0x90, 0x91, 0x92, 0x91 };           /* AniSonic22, delay $B */
    static const uint8_t k_ball[] = { 0x96, 0x97, 0x96, 0x98, 0x96, 0x99, 0x96, 0x9A };
    if (game_smash64_death_presentation_active()) {
        *mirror = 0;
        return 0xA7;                          /* AniSonic18 */
    }
    switch (scripted) {
    case SMASH64_SCRIPTED_PRESENTATION_WALK:
    case SMASH64_SCRIPTED_PRESENTATION_PIPE_SIDE:
        *mirror = 0;
        return k_walk[(s_present_frame / 8u) % sizeof(k_walk)];
    case SMASH64_SCRIPTED_PRESENTATION_FLAGPOLE:
        *mirror = 0;
        return k_hang[(s_present_frame / 12u) % sizeof(k_hang)];
    case SMASH64_SCRIPTED_PRESENTATION_PIPE_VERTICAL:
        return k_ball[(s_present_frame / 2u) % sizeof(k_ball)];
    default:
        return 0x100;
    }
}

/* Sonic's body centre on screen. Player_Rel_XPos is a byte, so a player just
 * left of the screen (a lift can carry him there after ChkPOffscr has kept
 * him on it) would wrap to the right edge. */
static int sonic_screen_center_x(void)
{
    return world_to_screen_x(((int)g_ram[Player_PageLoc] << 8) |
                             (int)g_ram[Player_X_Position]) + 8;
}

static void draw_sonic(void)
{
    const S3KPlayer *p = s3k_sonic_player();
    const Smash64ScriptedPresentation scripted =
        game_smash64_scripted_presentation();
    const int base_x = sonic_screen_center_x();
    const int feet_y = (int)g_ram[Player_Rel_YPos] + 32 +
                       (((int)(int8_t)g_ram[Player_Y_HighPos] - 1) * 256);
    int mirror = p->render_hflip != 0;
    unsigned frame = scripted_frame(scripted, &mirror);
    const int scripted_pose = frame != 0x100;
    const int death = game_smash64_death_presentation_active();
    const int origin_y = death && s_death_live ? (s_death_y >> 8)
                         : feet_y - sonic_scale_px(scripted_pose ? 0x13
                                                   : (int)p->y_radius);
    /* Shields hide under invincibility, except for an attack started there
     * (see run_shield_object), which draws without the idle shield. */
    const int invincible = (p->status_secondary & S3K_STATUS2_INVINCIBLE) != 0;
    const int shield_live = !scripted_pose &&
        (!invincible || p->shield_anim == 1);
    const int shield_front =
        (p->status_secondary & S3K_STATUS2_FIRE)
            ? p->shield_mapping_frame < 0x0F
            : 1;   /* Obj_InstaShield / Obj_S2Shield priority $80: over Sonic */

    if (!scripted_pose) frame = p->mapping_frame;
    if (frame >= S3K_SONIC_MAP_COUNT) frame = 0xBA;

    /* S3K priority order, back to front: fire shield rear frames ($200),
     * bouncing rings ($180), Sonic ($100), then shields, stars and dust
     * ($80). SMB1's brick chunks and pooled objects are ordinary NES sprites
     * behind all of them. */
    draw_brick_debris();
    draw_items();
    if (shield_live && !shield_front) draw_shield(p, base_x, origin_y);
    draw_rings();
    if (scripted_pose || !p->display_hidden) {
        if (render_frame(S3K_SONIC_ART_OFF, S3K_SONIC_MAP_OFF,
                         S3K_SONIC_DPLC_OFF, S3K_SONIC_MAP_COUNT, frame, mirror))
            composite(death && s_death_live ? s_death_screen_x : base_x,
                      origin_y);
    }
    if (shield_live && shield_front) draw_shield(p, base_x, origin_y);
    if (!scripted_pose) {
        draw_stars();
        draw_dust(p, base_x, origin_y);
    }
}

int game_sonic_set_enabled(int enabled, const char *owner_rom_path)
{
    s_enabled = 0;
    s_owner_ready = 0;
    s_present_frame = 0;
    /* The sound board reads the ROM buffer that probe_owner_rom replaces. */
    game_sonic_audio_shutdown();
    if (!enabled) return 1;
    if (!probe_owner_rom(owner_rom_path)) {
        fprintf(stderr, "[S3&K] Could not verify the selected Sonic 3 & "
                        "Knuckles ROM for Sonic.\n");
        return 0;
    }
    load_genesis_palette();
    load_sonic2_shield();
    memset(s_puffs, 0, sizeof(s_puffs));
    memset(&s_splash, 0, sizeof(s_splash));
    s_stars_live = 0;
    s_spindash_dust_live = 0;
    if (!game_smash64_set_mod_enabled(1, S3K_SONIC_CONTROLLER_ID)) {
        game_smash64_set_mod_enabled(0, NULL);
        game_sonic_audio_shutdown();
        return 0;
    }
    if (!game_sonic_audio_prepare(s_owner_rom, (size_t)S3K_ROM_BYTES)) {
        fprintf(stderr, "[S3&K] Could not start the Sonic 3 & Knuckles sound "
                        "driver from the selected ROM.\n");
        game_smash64_set_mod_enabled(0, NULL);
        return 0;
    }
    game_sonic_adapter_load_owner_data(s_owner_rom, (size_t)S3K_ROM_BYTES);
    s_owner_ready = 1;
    s_enabled = 1;
    s_layer.restart = 1;
    printf("[S3&K] Sonic armed with S3&K player physics: A/B jump, "
           "Down+jump spindash, jump again for the Insta-Shield%s.\n",
           s_s2_shield_ready ? " (standard shield art from Sonic 2)" : "");
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
    const S3KPlayer *p;
    int world_x, center_y;

    (void)frame_count;
    if (!game_sonic_active()) return;
    s_present_frame++;

    if (game_smash64_death_presentation_active()) {
        if (!s_death_live) {
            const S3KPlayer *dp = s3k_sonic_player();
            s_death_live = 1;
            s_death_y = ((int32_t)g_ram[Player_Y_Position] + 32 -
                         (int32_t)sonic_scale_px((int)dp->y_radius) +
                         (((int)(int8_t)g_ram[Player_Y_HighPos] - 1) * 256)) * 256;
            s_death_y_vel = -0x700;
            s_death_screen_x = sonic_screen_center_x();
        } else if (g_ram[TimerControl] < 0xF0 && (s_death_y >> 8) < 0x200) {
            /* PlayerDeath holds the player until KillPlayer's TimerControl
             * $FF has counted below $F0; the arc starts with Mario's. */
            s_death_y += s_death_y_vel;
            s_death_y_vel = (int16_t)(s_death_y_vel + 0x38);
        }
    } else {
        s_death_live = 0;
    }

    if (g_ram[OperMode] != 1 || !game_smash64_active()) {
        s_stars_live = 0;
        s_spindash_dust_live = 0;
        memset(&s_splash, 0, sizeof(s_splash));
        return;
    }
    /* Dust, splash and the invincibility stars are objects too: a paused
     * game holds them where they are. */
    if (g_ram[GamePauseStatus] & 0x01) return;
    p = s3k_sonic_player();
    world_x = (((int)g_ram[Player_PageLoc] << 8) |
               (int)g_ram[Player_X_Position]) + 8;
    center_y = (int)g_ram[Player_Y_Position] + 32 -
               sonic_scale_px((int)p->y_radius) +
               (((int)(int8_t)g_ram[Player_Y_HighPos] - 1) * 256);
    /* Sonic_RecordPos */
    s_pos_index = (s_pos_index + 1u) % S3K_POS_TABLE;
    s_pos_table[s_pos_index].x = (int16_t)world_x;
    s_pos_table[s_pos_index].y = (int16_t)center_y;
    update_dust(p, world_x, center_y);
    update_splash(world_x);
    update_stars(p);
}

void game_sonic_shift_world_x(int dx)
{
    for (int i = 0; i < (int)(sizeof(s_puffs) / sizeof(s_puffs[0])); ++i)
        s_puffs[i].world_x += dx;
    for (int i = 0; i < S3K_POS_TABLE; ++i)
        s_pos_table[i].x = (int16_t)(s_pos_table[i].x + dx);
    s_splash.world_x += dx;
}

/* Draw this frame's presentation into the layer. */
static void build_layer(void)
{
    Smash64ScriptedPresentation scripted;

    layer_clear();
    if (!game_sonic_active() || !s_owner_ready || g_ram[OperMode] != 1 ||
        !layer_prepare())
        return;
    scripted = game_smash64_scripted_presentation();
    if (!game_smash64_active() &&
        !game_smash64_death_presentation_active() &&
        !game_smash64_still_presentation_active() &&
        scripted == SMASH64_SCRIPTED_PRESENTATION_NONE) {
        /* Brick chunks and pooled objects outlive the hand-off into a pipe. */
        draw_brick_debris();
        draw_items();
        return;
    }

    s_draw_behind_background =
        (scripted == SMASH64_SCRIPTED_PRESENTATION_PIPE_SIDE ||
         scripted == SMASH64_SCRIPTED_PRESENTATION_PIPE_VERTICAL) &&
        (g_ram[Player_SprAttrib] & 0x20) != 0;
    draw_sonic();
    s_draw_behind_background = 0;
}

void game_sonic_note_state_loaded(void)
{
    s_layer.restart = 1;
}

void game_sonic_render_post_render(uint32_t *framebuffer)
{
    /* Nothing was built for the frame a savestate's picture shows; that one
     * picture gets the loaded frame's own layer. */
    if (s_layer.restart) {
        s_layer.restart = 0;
        build_layer();
    }
    if (framebuffer && game_sonic_active() && s_owner_ready)
        layer_composite(framebuffer);
    build_layer();
}
