#include "game_widescreen.h"
#include "smb_ws_world.h"
#include "smb_ws_actors.h"
#ifdef SMB1_CYCLE
#include "cycle_bridge.h"
#else
#include "nes_runtime.h"
#endif
#include "nes_video.h"
#include "mod_runtime.h"
#include "mod_function_hooks.h"
#include "mod_savestate.h"
#include "debug_server.h"
#include <stdio.h>
#include <string.h>
#if defined(SMB1_CYCLE) && defined(NESRECOMP_NET)
#include "cyc_net.h"
#include <stdlib.h>
#endif

static int s_enabled, s_ready, s_edges = 1;
static int s_backtracking;
typedef struct {
    uint32_t version;
    int32_t high_water;
    uint16_t area;
    uint8_t world, initialized, scroll_before, pending;
} BacktrackState;
static BacktrackState s_backtrack;
static int s_room_edges = 1;
static NesAspectMode s_aspect = NES_ASPECT_FIT;
static uint64_t s_wide_frames, s_native_frames;
static SmbEnemyMode s_enemies=SMB_ENEMIES_VIEWPORT;
static uint8_t s_opaque[NES_MAX_RENDER_WIDTH*240];
#if defined(SMB1_CYCLE) && defined(NESRECOMP_NET)
/* Compact, complete simulation settings for the room's 64-byte caps field.
 * Fit settles at 16:9 online; local windows can resize without changing it. */
static int ws_session_get(char *out,int cap) {
    return snprintf(out,(size_t)cap,"%d:%d:%d:%d",s_enabled,s_edges,(int)s_enemies,s_room_edges);
}
static int ws_session_offer(char *out,int cap) {
    const char *p="super-mario-bros.enhancement.widescreen";
    char hud[32]="edges",enemies[32]="viewport",camera[32]="edges";
    int enabled=nes_mod_feature_selected(p,"widescreen");
    if(nes_mod_feature_selected("super-mario-bros.gameplay.simultaneous-coop","coop"))enabled=0;
    nes_mod_option_value(p,"widescreen","hud",hud,sizeof hud);
    nes_mod_option_value(p,"widescreen","enemy_activation",enemies,sizeof enemies);
    nes_mod_option_value(p,"widescreen","camera",camera,sizeof camera);
    return snprintf(out,(size_t)cap,"%d:%d:%d:%d",enabled,strcmp(hud,"center")!=0,!strcmp(enemies,"classic")?SMB_ENEMIES_CLASSIC:SMB_ENEMIES_VIEWPORT,strcmp(camera,"centered")!=0);
}
static int ws_width_offer(char *out,int cap) {
    const char *p="super-mario-bros.enhancement.widescreen";char aspect[32]="fit";
    if(!nes_mod_feature_selected(p,"widescreen")||nes_mod_feature_selected("super-mario-bros.gameplay.simultaneous-coop","coop"))return snprintf(out,(size_t)cap,"256");
    nes_mod_option_value(p,"widescreen","aspect",aspect,sizeof aspect);
    NesAspectMode m=NES_ASPECT_16_9;nes_video_aspect_from_name(aspect,&m);
    return snprintf(out,(size_t)cap,"%d",m==NES_ASPECT_32_9?854:m==NES_ASPECT_21_9?560:426);
}
static int ws_session_apply(const char *v) {
    int on=-1,hud=-1,enemies=-1,camera=-1;char tail;
    if(sscanf(v,"%d:%d:%d:%d%c",&on,&hud,&enemies,&camera,&tail)!=4||on<0||on>1||hud<0||hud>1||enemies<0||enemies>2||camera<0||camera>1)return 0;
    game_widescreen_configure("16:9",hud?"edges":"center",enemies==SMB_ENEMIES_CLASSIC?"classic":"viewport");
    s_enemies=(SmbEnemyMode)enemies;game_widescreen_set_camera(camera?"edges":"centered");game_widescreen_set_mod_enabled(on);return 1;
}
static void ws_session_restore(void){game_widescreen_set_mod_enabled(0);}
static int bt_session_get(char *out,int cap) { return snprintf(out,(size_t)cap,"%d",s_backtracking); }
static int bt_session_offer(char *out,int cap) {
    int on=nes_mod_feature_selected("super-mario-bros.gameplay.free-backtracking","backtracking");
    if(nes_mod_feature_selected("super-mario-bros.gameplay.simultaneous-coop","coop"))on=0;
    return snprintf(out,(size_t)cap,"%d",on);
}
static int bt_session_apply(const char *v) {
    if (strcmp(v,"0") && strcmp(v,"1")) return 0;
    game_backtracking_set_enabled(*v=='1'); return 1;
}
static void bt_session_restore(void) { game_backtracking_set_enabled(0); }
NES_MOD_CONSTRUCTOR(register_cycle_ws_session) {
    nes_runner_register_session_keys();
    nes_netplay_session_register("ws",ws_session_get,ws_session_apply,ws_session_restore);
    nes_netplay_session_set_offer("ws",ws_session_offer);nes_netplay_session_set_offer("vw",ws_width_offer);
    nes_netplay_session_register("bk",bt_session_get,bt_session_apply,bt_session_restore);
    nes_netplay_session_set_offer("bk",bt_session_offer);
}
#endif
static int s_render_camera, s_render_native_x0, s_view_left;
static int gameplay(void) {
    return (g_ram[0x770] == 1 && g_ram[0x772] == 3) || g_ram[0x770] == 2;
}
static int camera_x(void) { return (g_ram[0x71a] << 8) | g_ram[0x71c]; }
int game_backtracking_active(void) {
    return s_backtracking && gameplay() && g_smb_ws_world.valid &&
        !g_smb_ws_world.fixed_rooms && !smb_ws_world_busy();
}
static int anchor_camera(int width) {
    return (s_enabled || s_backtracking) && s_room_edges && width > 256 &&
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
    int cam=camera_x();
#ifdef SMB1_CYCLE
    /* The captured rendering address owns the nametable phase. PPUCTRL
     * describes the base table, which can disagree after wrapping/splitting;
     * combining that bit with an eight-bit scroll misplaces terrain by 256. */
    int ppu=cyc_render_line_scroll_x(32);
#else
    uint8_t ctrl=g_ppuctrl,sx=g_ppuscroll_x;
    runtime_get_visible_frame_start(&ctrl,&sx,NULL,NULL,NULL);
    int ppu=((ctrl&1)<<8)|sx;
#endif
    return cam+((ppu-cam+256)&511)-256;
}

#ifdef SMB1_CYCLE
typedef struct { int play_x0, hud_x0, width; } HudSpritePlacement;
static int place_hud_sprite(int slot, int x, int y, int *out_x, void *user) {
    const HudSpritePlacement *p = user;
    if (ppu_renderer_sprite_suppressed(slot,x,y)) return 0;
    /* Only sprite zero is part of SMB's fixed status-bar split. All other
     * sprites, including Mario jumping above the bar, keep world placement. */
    *out_x = x + p->play_x0;
    if (slot == 0) *out_x = s_edges ? x + (x >= 128 ? p->width-256 : 0) : x + p->hud_x0;
    return 1;
}
#endif

static int render(uint32_t *out, int width, int height, int native_x0,
                  const uint32_t *native, void *user) {
    (void)user;
    int cached = game_backtracking_active() && g_ram[0x0e]>=7;
    if ((!s_enabled && !cached) || !gameplay() || !g_smb_ws_world.valid || !(g_ppumask & 8)) {
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
    for (int y = 32; !cached && y < height; y++) for (int x = first; x < last; x++) {
        out[y*width+x+play_x0] = native[y*256+x];
        s_opaque[y*width+x+play_x0]=(uint8_t)ppu_renderer_background_opaque(x,y);
    }
    const uint32_t *hud = native;
#ifdef SMB1_CYCLE
    static uint32_t hud_background[256*240];
    int separate_sprites = cyc_render_background(hud_background);
    if (separate_sprites) hud = hud_background;
#endif
    /* Position the status background independently of world sprites. Copying
     * the combined native picture here used to move Mario with the HUD. */
    for (int y = 0; y < 32; y++) {
        if (s_edges) {
            memcpy(out+y*width, hud+y*256, 128*sizeof(uint32_t));
            memcpy(out+y*width+width-128, hud+y*256+128, 128*sizeof(uint32_t));
        } else memcpy(out+y*width+native_x0, hud+y*256, 256*sizeof(uint32_t));
        for (int x = 0; x < 256; x++) {
            int dx = s_edges ? x + (x >= 128 ? width-256 : 0) : x + native_x0;
            s_opaque[y*width+dx] = (uint8_t)ppu_renderer_background_opaque(x,y);
        }
    }
#ifdef SMB1_CYCLE
    if (separate_sprites) {
        HudSpritePlacement p = {play_x0,native_x0,width};
        cyc_render_sprites(out,width,cached?height:32,play_x0,s_opaque,place_hud_sprite,&p);
    }
#endif
    smb_ws_actors_draw(out,width,play_x0,cam,s_opaque);
    ppu_renderer_set_background_opaque_frame(s_opaque,width,height);
    s_wide_frames++;
    return 1;
}

static void apply(void) {
    if (!s_ready) return;
    g_ws_oam_sidecar = 0;
    g_ws_obj_ctx_valid = 0;
    g_ws_eff_left = g_ws_eff_right = -1;
    int infrastructure=s_enabled || s_backtracking;
    if (infrastructure) {
        if (!ppu_renderer_set_custom_render(render, NULL)) {
            s_enabled = 0;
            nes_video_set_aspect_mode(NES_ASPECT_STOCK);
        } else nes_video_set_aspect_mode(s_enabled?s_aspect:NES_ASPECT_STOCK);
    } else {
        ppu_renderer_set_custom_render(NULL, NULL);
        nes_video_set_aspect_mode(NES_ASPECT_STOCK);
    }
    nes_mod_set_function_hook_enabled("super-mario-bros.widescreen.column", infrastructure);
    nes_mod_set_function_hook_enabled("super-mario-bros.widescreen.area", infrastructure);
    nes_mod_set_function_hook_enabled("super-mario-bros.widescreen.collision-column", infrastructure);
    nes_mod_set_function_hook_enabled("super-mario-bros.backtracking.scroll",s_backtracking);
    nes_mod_set_function_hook_enabled("super-mario-bros.backtracking.parser",s_backtracking);
    nes_mod_set_function_hook_enabled("super-mario-bros.backtracking.block",s_backtracking);
    nes_mod_set_function_hook_enabled("super-mario-bros.backtracking.destroy",s_backtracking);
    nes_mod_set_function_hook_enabled("super-mario-bros.backtracking.loopback",s_backtracking);
    /* Native diagnostics normally bypass residents. Backtracking still needs
     * their retirement/sleep ledger; Classic keeps original activation timing
     * without changing the stored enemy policy. */
    SmbEnemyMode effective=s_backtracking && s_enemies==SMB_ENEMIES_NATIVE
        ? SMB_ENEMIES_CLASSIC : s_enemies;
    smb_ws_actors_configure(infrastructure,effective);
}
void game_backtracking_set_enabled(int enabled) {
#ifdef SMB1_CYCLE
    s_backtracking=enabled!=0;
#else
    (void)enabled; s_backtracking=0;
#endif
    memset(&s_backtrack,0,sizeof s_backtrack);s_backtrack.version=1;
    apply();
}
int game_backtracking_compose_native(uint32_t *out,const uint32_t *native) {
    return game_backtracking_active()?render(out,256,240,0,native,NULL):0;
}
uint8_t game_backtracking_ram_read_hook(uint16_t pc,uint16_t addr,uint8_t value) {
#ifdef SMB1_CYCLE
    /* PlayerLoseLife's CMP ScreenLeft_PageLoc at $9206 decides midpoint
     * eligibility. The stock camera only advances, so this operand represented
     * furthest progress. Give only that comparison the retained parser view;
     * the real camera and the remaining native death/retry routine stay intact. */
    if (pc==0x9206 && addr==0x071a && s_backtracking &&
        s_backtrack.initialized && !cyc_mod_isolated() &&
        s_backtrack.area==((g_ram[0xe8]<<8)|g_ram[0xe7]) &&
        s_backtrack.world==g_ram[0x75f]) {
        int page=s_backtrack.high_water>>8;
        if (page>value) return (uint8_t)page;
    }
#else
    (void)pc;(void)addr;
#endif
    return value;
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
    memset(&s_backtrack,0,sizeof s_backtrack);s_backtrack.version=1;
    s_ready = 1; apply();
}
void game_widescreen_update(void) {
    if ((s_enabled || s_backtracking) && gameplay()) { smb_ws_world_update(); smb_ws_actors_update(); }
}
void game_widescreen_begin_frame(void) {
    if (s_enabled || s_backtracking) {
        if (game_backtracking_active()) smb_ws_world_bind_collision(camera_x());
        smb_ws_actors_begin_frame();
    }
}
int game_widescreen_column_hook(uint16_t addr) {
    (void)addr;
    if ((s_enabled || s_backtracking) && !smb_ws_world_busy() && g_ram[0x770] != 0)
        smb_ws_world_observe_column();
    return 0; /* Observe only; the original routine always executes. */
}
static int area_hook(uint16_t addr) {
    (void)addr;
    if ((s_enabled || s_backtracking) && !smb_ws_world_busy()) {
        smb_ws_world_reset(); smb_ws_actors_reset();
        memset(&s_backtrack,0,sizeof s_backtrack);s_backtrack.version=1;
    }
    return 0;
}
static int collision_column_hook(uint16_t addr) {
    (void)addr;
    if (s_enabled || s_backtracking) smb_ws_world_begin_column();
    return 0;
}
static int backtracking_scroll(uint16_t addr) {
    (void)addr;
    if (!game_backtracking_active() || g_ram[0x0e]!=8) return 0;
#ifdef SMB1_CYCLE
    if (cyc_mod_isolated()) return 0;
#endif
    int cam=camera_x();
    if (!s_backtrack.initialized || s_backtrack.area!=g_smb_ws_world.area_data || s_backtrack.world!=g_ram[0x75f]) {
        s_backtrack.high_water=cam;s_backtrack.area=g_smb_ws_world.area_data;
        s_backtrack.world=g_ram[0x75f];s_backtrack.initialized=1;
    }
    s_backtrack.scroll_before=g_ram[0x73d];s_backtrack.pending=1;
    int dx=(int8_t)(g_ram[0x6ff]+g_ram[0x3a1]);
    int player=(g_ram[0x6d]<<8)|g_ram[0x86];
    if (dx<0 && player-cam<=80 && !g_ram[0x723] && !g_ram[0x785]) {
        int left,right;smb_ws_world_bounds(cam,&left,&right);
        int next=cam+dx;if(next<left)next=left;
        g_ram[ScreenLeft_PageLoc]=(uint8_t)(next>>8);
        g_ram[ScreenLeft_X_Pos]=g_ram[HorizontalScroll]=(uint8_t)next;
        g_ram[ScreenRight_PageLoc]=(uint8_t)((next+255)>>8);
        g_ram[ScreenRight_X_Pos]=(uint8_t)(next+255);
        g_ram[Mirror_PPU_CTRL_REG1]=(uint8_t)((g_ram[Mirror_PPU_CTRL_REG1]&~1)|((next>>8)&1));
    }
    /* The native routine still owns screen clamping, platform-force clearing,
     * rightward camera movement, and its normal register/cycle contract. */
    return 0;
}
static int backtracking_parser(uint16_t addr) {
    (void)addr;
    if (!s_backtracking || !s_backtrack.pending || smb_ws_world_busy()) return 0;
#ifdef SMB1_CYCLE
    if (cyc_mod_isolated()) return 0;
#endif
    int cam=camera_x(),new_distance=cam>s_backtrack.high_water?cam-s_backtrack.high_water:0;
    g_ram[0x73d]=(uint8_t)(s_backtrack.scroll_before+new_distance);
    if (cam>s_backtrack.high_water) s_backtrack.high_water=cam;
    s_backtrack.pending=0;
    return 0; /* Pending native parser tasks still finish in the normal way. */
}
static int backtracking_block(uint16_t addr) {
    if (!game_backtracking_active()) return 0;
#ifdef SMB1_CYCLE
    if (cyc_mod_isolated()) return 0;
#endif
    smb_ws_world_write_block(addr==0x8a6b?0:g_cpu.A);
    return 0;
}
static int backtracking_loopback(uint16_t addr) {
    (void)addr;
    if (!s_backtracking || smb_ws_world_busy()) return 0;
#ifdef SMB1_CYCLE
    if (cyc_mod_isolated()) return 0;
#endif
    /* The native castle maze deliberately moves both parser and camera back
     * four pages. That is a new native area pass, not a player revisit: retain
     * the factory reset/reparse behavior and adopt its new high-water mark. */
    smb_ws_world_reset();smb_ws_actors_reset();
    memset(&s_backtrack,0,sizeof s_backtrack);s_backtrack.version=1;
    return 0;
}
int game_widescreen_arg(const char *key, const char *value) {
    if (!strcmp(key,"--widescreen-hud") && value) {
        if (strcmp(value,"edges") && strcmp(value,"center")) return 0;
        s_edges = strcmp(value,"center") != 0;
        apply(); return 1;
    }
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
        "\"render_width\":%d,\"camera_x\":%d,\"area_data\":%u,\"backtracking\":%d,\"parser_high_water\":%d,"
        "\"view_left\":%d,\"native_x0\":%d,\"room_edges\":%d,\"area_end\":%u,\"fixed_rooms\":%u,"
        "\"decoded_columns\":%u,\"verified_columns\":%u,\"mismatched_columns\":%u,"
        "\"first_mismatch_column\":%d,\"first_mismatch_row\":%d,"
        "\"expected\":%u,\"actual\":%u,\"wide_frames\":%llu,\"native_frames\":%llu}",
        id,s_enabled,ppu_renderer_custom_render_active(),g_render_width,camera_x(),w->area_data,s_backtracking,s_backtrack.high_water,
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
static int save_backtrack(uint8_t *data,int cap) {
    if (cap<(int)sizeof s_backtrack) return -1;
    memcpy(data,&s_backtrack,sizeof s_backtrack);return sizeof s_backtrack;
}
static int load_backtrack(const uint8_t *data,int len) {
    if (!len) {memset(&s_backtrack,0,sizeof s_backtrack);s_backtrack.version=1;return 1;}
    if (len!=sizeof s_backtrack) return 0;
    BacktrackState candidate;memcpy(&candidate,data,sizeof candidate);
    if (candidate.version!=1 || candidate.high_water<0 || candidate.high_water>=SMB_WS_META_COLUMNS*16 || candidate.initialized>1 || candidate.pending>1) return 0;
    s_backtrack=candidate;return 1;
}
NES_MOD_CONSTRUCTOR(register_custom_widescreen) {
    if (!nes_mod_register_function_entry_plugin("super-mario-bros.widescreen.column",0x88ae,game_widescreen_column_hook) ||
        !nes_mod_register_function_entry_plugin("super-mario-bros.widescreen.area",0x8fe4,area_hook) ||
        !nes_mod_register_function_entry_plugin("super-mario-bros.widescreen.collision-column",0x93fc,collision_column_hook) ||
        !nes_mod_register_function_entry_plugin("super-mario-bros.backtracking.scroll",0xaf93,backtracking_scroll) ||
        !nes_mod_register_function_entry_plugin("super-mario-bros.backtracking.parser",0xaf6f,backtracking_parser) ||
        !nes_mod_register_function_entry_plugin("super-mario-bros.backtracking.block",0x8a6d,backtracking_block) ||
        !nes_mod_register_function_entry_plugin("super-mario-bros.backtracking.destroy",0x8a6b,backtracking_block) ||
        !nes_mod_register_function_entry_plugin("super-mario-bros.backtracking.loopback",0xc08c,backtracking_loopback) ||
        !nes_mod_register_savestate_hook("super-mario-bros.backtracking",save_backtrack,load_backtrack) ||
        !nes_mod_register_savestate_hook("super-mario-bros.widescreen.world",save_world,load_world))
        fprintf(stderr, "[Widescreen] Failed to register custom renderer hooks\n");
}
