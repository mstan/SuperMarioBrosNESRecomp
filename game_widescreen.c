#include "game_widescreen.h"
#include "smb_ws_world.h"
#include "smb_ws_actors.h"
#include "nes_runtime.h"
#include "nes_video.h"
#include "mod_runtime.h"
#include "mod_function_hooks.h"
#include "mod_savestate.h"
#include "debug_server.h"
#include <stdio.h>
#include <string.h>

static int s_enabled, s_ready, s_edges = 1;
static int s_room_edges = 1;
static NesAspectMode s_aspect = NES_ASPECT_FIT;
static uint64_t s_wide_frames, s_native_frames;
static SmbEnemyMode s_enemies=SMB_ENEMIES_VIEWPORT;
static uint8_t s_opaque[NES_MAX_RENDER_WIDTH*240];
static int s_render_camera, s_render_native_x0, s_view_left;
static int gameplay(void) {
    return (g_ram[0x770] == 1 && g_ram[0x772] == 3) || g_ram[0x770] == 2;
}
static int camera_x(void) { return (g_ram[0x71a] << 8) | g_ram[0x71c]; }
static int anchor_camera(int width) {
    return s_enabled && s_room_edges && width > 256 &&
        s_enemies != SMB_ENEMIES_NATIVE && gameplay() && g_smb_ws_world.valid;
}
int game_widescreen_view_left(int native_camera, int width) {
    int view = native_camera - (width - 256) / 2;
    if (!anchor_camera(width)) return view;
    int left, right;
    smb_ws_world_bounds(native_camera, &left, &right);
    if (right - left <= width) return left - (width - (right - left)) / 2;
    if (view < left) view = left;
    if (view > right - width) view = right - width;
    return view;
}
void game_widescreen_actor_range(int native_camera, int width, int pad, int *left, int *right) {
    *left = game_widescreen_view_left(native_camera, width) - pad;
    *right = *left + width + pad * 2;
    if (anchor_camera(width)) {
        int start, end;
        smb_ws_world_bounds(native_camera, &start, &end);
        if (*left < start - pad) *left = start - pad;
        if (*right > end + pad) *right = end + pad;
    }
}
static int render_camera(void) {
    /* Game logic has already advanced the camera for the next frame. Match
     * the stock pass's captured PPU scroll, then unwrap its two nametables
     * against the absolute level camera. This also survives page crossings. */
    uint8_t ctrl=g_ppuctrl,sx=g_ppuscroll_x;
    runtime_get_visible_frame_start(&ctrl,&sx,NULL,NULL,NULL);
    int cam=camera_x(),ppu=((ctrl&1)<<8)|sx;
    return cam+((ppu-cam+256)&511)-256;
}

static int render(uint32_t *out, int width, int height, int native_x0,
                  const uint32_t *native, void *user) {
    (void)user;
    if (!s_enabled || !gameplay() || !g_smb_ws_world.valid || !(g_ppumask & 8)) {
        s_native_frames++; return 0;
    }
    int cam = render_camera();
    s_render_camera=cam;
    s_view_left = game_widescreen_view_left(cam, width);
    int play_x0 = cam - s_view_left;
    s_render_native_x0 = play_x0;
    int room_left = 0, room_right = SMB_WS_META_COLUMNS * 16;
    if (anchor_camera(width)) smb_ws_world_bounds(cam, &room_left, &room_right);
    uint32_t backdrop = g_nes_palette[g_ppu_pal[0] & 63];
    int pattern = (g_ppuctrl & 0x10) ? 0x1000 : 0;
    for (int y = 0; y < height; y++) for (int x = 0; x < width; x++) {
        uint8_t tile, palette;
        int wx = s_view_left + x;
        uint32_t color = backdrop;
        s_opaque[y*width+x]=0;
        if (wx >= room_left && wx < room_right && smb_ws_world_pixel(wx, y, &palette, &tile)) {
            int offset = pattern + tile * 16 + (y & 7), shift = 7 - (wx & 7);
            int pixel = ((g_chr_ram[offset] >> shift) & 1) |
                        (((g_chr_ram[offset+8] >> shift) & 1) << 1);
            if (pixel) { color = g_nes_palette[g_ppu_pal[palette*4 + pixel] & 63]; s_opaque[y*width+x]=1; }
        }
        out[y * width + x] = color;
    }
    /* The stock pass remains authoritative for native sprites, priority,
     * sprite-zero timing, transient tiles and the original play area. */
    int first = play_x0 < 0 ? -play_x0 : 0;
    int last = play_x0 + 256 > width ? width - play_x0 : 256;
    for (int y = 32; y < height; y++) for (int x = first; x < last; x++) {
        out[y*width+x+play_x0] = native[y*256+x];
        s_opaque[y*width+x+play_x0]=(uint8_t)ppu_renderer_background_opaque(x,y);
    }
    smb_ws_actors_draw(out,width,play_x0,cam,s_opaque);
    ppu_renderer_set_background_opaque_frame(s_opaque,width,height);
    for (int y = 0; y < 32; y++) {
        if (s_edges) {
            memcpy(out+y*width, native+y*256, 128*sizeof(uint32_t));
            memcpy(out+y*width+width-128, native+y*256+128, 128*sizeof(uint32_t));
        } else memcpy(out+y*width+native_x0, native+y*256, 256*sizeof(uint32_t));
    }
    s_wide_frames++;
    return 1;
}

static void apply(void) {
    if (!s_ready) return;
    g_ws_oam_sidecar = 0;
    g_ws_obj_ctx_valid = 0;
    g_ws_eff_left = g_ws_eff_right = -1;
    if (s_enabled) {
        if (!ppu_renderer_set_custom_render(render, NULL)) {
            s_enabled = 0;
            nes_video_set_aspect_mode(NES_ASPECT_STOCK);
        } else nes_video_set_aspect_mode(s_aspect);
    } else {
        ppu_renderer_set_custom_render(NULL, NULL);
        nes_video_set_aspect_mode(NES_ASPECT_STOCK);
    }
    nes_mod_set_function_hook_enabled("super-mario-bros.widescreen.column", s_enabled);
    nes_mod_set_function_hook_enabled("super-mario-bros.widescreen.area", s_enabled);
    nes_mod_set_function_hook_enabled("super-mario-bros.widescreen.collision-column", s_enabled);
    smb_ws_actors_configure(s_enabled,s_enemies);
}
void game_widescreen_set_mod_enabled(int enabled) {
    s_enabled = enabled != 0;
    if (!s_enabled) { s_aspect = NES_ASPECT_FIT; s_edges = s_room_edges = 1; s_enemies=SMB_ENEMIES_VIEWPORT; }
    apply();
}
void game_widescreen_configure(const char *aspect, const char *hud, const char *enemies) {
    NesAspectMode value;
    if (nes_video_aspect_from_name(aspect, &value) && value != NES_ASPECT_STOCK) s_aspect = value;
    s_edges = !hud || strcmp(hud, "center") != 0;
    s_enemies=enemies && !strcmp(enemies,"classic")?SMB_ENEMIES_CLASSIC:SMB_ENEMIES_VIEWPORT;
    apply();
}
void game_widescreen_set_camera(const char *camera) {
    s_room_edges = !camera || strcmp(camera, "centered") != 0;
}
void game_widescreen_init(void) {
    smb_ws_world_reset(); smb_ws_actors_reset(); s_wide_frames = s_native_frames = 0;
    s_ready = 1; apply();
}
void game_widescreen_update(void) {
    if (s_enabled && gameplay()) { smb_ws_world_update(); smb_ws_actors_update(); }
}
void game_widescreen_begin_frame(void) { if (s_enabled) smb_ws_actors_begin_frame(); }
int game_widescreen_column_hook(uint16_t addr) {
    (void)addr;
    if (s_enabled && !smb_ws_world_busy() && g_ram[0x770] != 0)
        smb_ws_world_observe_column();
    return 0; /* Observe only; the original routine always executes. */
}
static int area_hook(uint16_t addr) {
    (void)addr;
    if (s_enabled && !smb_ws_world_busy()) { smb_ws_world_reset(); smb_ws_actors_reset(); }
    return 0;
}
static int collision_column_hook(uint16_t addr) {
    (void)addr;
    if (s_enabled) smb_ws_world_begin_column();
    return 0;
}
int game_widescreen_arg(const char *key, const char *value) {
    if (!strcmp(key, "--widescreen-camera") && value) {
        if (!strcmp(value, "edges") || !strcmp(value, "centered")) game_widescreen_set_camera(value);
        else fprintf(stderr, "[Widescreen] camera must be edges or centered\n");
        return 1;
    }
    if (!strcmp(key,"--widescreen-enemies") && value) {
        if (!strcmp(value,"classic")) s_enemies=SMB_ENEMIES_CLASSIC;
        else if (!strcmp(value,"viewport")) s_enemies=SMB_ENEMIES_VIEWPORT;
        else if (!strcmp(value,"native")) s_enemies=SMB_ENEMIES_NATIVE;
        else { fprintf(stderr,"[Widescreen] enemy policy must be classic or viewport (native for renderer diagnostics)\n"); return 1; }
        apply(); return 1;
    }
    if (strcmp(key, "--widescreen") || !value) return 0;
    NesAspectMode aspect;
    if (!strcmp(value, "off")) game_widescreen_set_mod_enabled(0);
    else if (nes_video_aspect_from_name(value, &aspect) && aspect != NES_ASPECT_STOCK) {
        s_aspect = aspect; game_widescreen_set_mod_enabled(1);
    } else {
        fprintf(stderr, "[Widescreen] invalid aspect: %s (fit,16:9,21:9,32:9,off)\n", value);
        game_widescreen_set_mod_enabled(0);
    }
    return 1;
}
int game_widescreen_debug(const char *cmd, int id) {
    if (smb_ws_actors_debug(cmd,id)) return 1;
    if (!strcmp(cmd,"smb_ws_seam")) {
        /* Compare terrain against the native background, without sprites.
         * Nearby offsets expose a scroll-phase error at either join. This
         * diagnostic runs only when explicitly requested over TCP. */
        int errors[9]={0},samples=0;
        if (s_enabled && g_smb_ws_world.valid && gameplay()) {
            int x0=s_render_native_x0;
            for (int y=32;y<240;y++) for (int side=0;side<2;side++)
                for (int x=8+side*224;x<24+side*224;x++) {
                    if (x0+x < 0 || x0+x >= g_render_width) continue;
                    int actual=s_opaque[y*g_render_width+x0+x];
                    samples++;
                    for (int d=-4;d<=4;d++) {
                        uint8_t pal,tile; int wx=s_render_camera+x+d,pixel=0;
                        if (smb_ws_world_pixel(wx,y,&pal,&tile)) {
                            int off=((g_ppuctrl&16)?0x1000:0)+tile*16+(y&7),bit=7-(wx&7);
                            pixel=((g_chr_ram[off]>>bit)&1)|(((g_chr_ram[off+8]>>bit)&1)<<1);
                        }
                        errors[d+4]+=(pixel!=0)!=actual;
                    }
                }
        }
        debug_server_send_fmt("{\"id\":%d,\"render_camera\":%d,\"game_camera\":%d,\"ppu_scroll_x\":%d,\"samples\":%d,\"offset_errors\":[%d,%d,%d,%d,%d,%d,%d,%d,%d]}",
            id,s_render_camera,camera_x(),g_ppuscroll_x,samples,
            errors[0],errors[1],errors[2],errors[3],errors[4],errors[5],errors[6],errors[7],errors[8]);
        return 1;
    }
    if (strcmp(cmd, "smb_ws_state")) return 0;
    const SmbWsWorld *w = &g_smb_ws_world;
    debug_server_send_fmt("{\"id\":%d,\"enabled\":%d,\"custom_renderer\":%d,"
        "\"render_width\":%d,\"camera_x\":%d,\"area_data\":%u,"
        "\"view_left\":%d,\"native_x0\":%d,\"room_edges\":%d,\"area_end\":%u,\"fixed_rooms\":%u,"
        "\"decoded_columns\":%u,\"verified_columns\":%u,\"mismatched_columns\":%u,"
        "\"first_mismatch_column\":%d,\"first_mismatch_row\":%d,"
        "\"expected\":%u,\"actual\":%u,\"wide_frames\":%llu,\"native_frames\":%llu}",
        id,s_enabled,ppu_renderer_custom_render_active(),g_render_width,camera_x(),w->area_data,
        s_view_left,s_render_native_x0,s_room_edges,w->area_end,w->fixed_rooms,
        w->decoded_columns,w->verified_columns,w->mismatched_columns,w->first_mismatch_column,
        w->first_mismatch_row,w->first_expected,w->first_actual,
        (unsigned long long)s_wide_frames,(unsigned long long)s_native_frames);
    return 1;
}
static int save_world(uint8_t *data, int cap) {
    if (cap < (int)sizeof g_smb_ws_world) return -1;
    memcpy(data,&g_smb_ws_world,sizeof g_smb_ws_world);
    return sizeof g_smb_ws_world;
}
static int load_world(const uint8_t *data, int len) {
    uint32_t version;
    if (!len) { smb_ws_world_reset(); return 1; }
    if (len != sizeof g_smb_ws_world) return 0;
    memcpy(&version,data,sizeof version);
    if (version != 4) return 0;
    memcpy(&g_smb_ws_world,data,sizeof g_smb_ws_world);
    /* The previous compositor could save attributes from a reused physical
     * nametable. Palette ownership comes from the area's metatiles. */
    for (int c=0;c<SMB_WS_TILE_COLUMNS;c++) for (int row=0;row<SMB_WS_ROWS;row++)
        g_smb_ws_world.palettes[c][row]=g_smb_ws_world.metatiles[c/2][row/2]>>6;
    /* Settings belong to Mods, never to the save being loaded. */
    return 1;
}
NES_MOD_CONSTRUCTOR(register_custom_widescreen) {
    if (!nes_mod_register_function_entry_plugin("super-mario-bros.widescreen.column",0x88ae,game_widescreen_column_hook) ||
        !nes_mod_register_function_entry_plugin("super-mario-bros.widescreen.area",0x8fe4,area_hook) ||
        !nes_mod_register_function_entry_plugin("super-mario-bros.widescreen.collision-column",0x93fc,collision_column_hook) ||
        !nes_mod_register_savestate_hook("super-mario-bros.widescreen.world",save_world,load_world))
        fprintf(stderr, "[Widescreen] Failed to register custom renderer hooks\n");
}
