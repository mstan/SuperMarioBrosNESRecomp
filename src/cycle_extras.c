#include "cycle_bridge.h"
#include "cyc_host_extras.h"
#include "cyc_tcp.h"
#include "cyc_ring.h"
#include "game_coop.h"
#include "game_widescreen.h"
#include "game_voxel.h"
#include "game_smash64.h"
#include "game_smash64_render.h"
#include "game_link.h"
#include "game_samus.h"
#include "game_sonic.h"
#include "smb_ws_actors.h"
#include "mod_audio.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
uint64_t g_frame_count;
static uint32_t picture[NES_MAX_RENDER_WIDTH*240];
static int suppress(int slot,int x,int y,void *user) {(void)user;return game_coop_suppress_sprite(slot)||game_smash64_render_suppress_sprite(slot,x,y)||smb_ws_actors_suppress_sprite(slot);}
static void power_on(void *ctx) {
    (void)ctx;smb1_cycle_init();cyc_render_capture_background(true);g_frame_count=0;
    if(game_coop_enabled()){game_widescreen_set_mod_enabled(0);game_voxel_set_mod_enabled(0);game_smash64_set_mod_enabled(0,NULL);game_link_set_enabled(0,NULL);game_samus_set_enabled(0,NULL);game_sonic_set_enabled(0,NULL);}
    game_widescreen_init();game_voxel_init();game_smash64_init();game_smash64_render_init();ppu_renderer_set_sprite_suppress(suppress,NULL);
}
static void input(void *ctx,uint8_t buttons[2]) {
    (void)ctx;smb1_cycle_sync();g_frame_count=cyc_ring_frame;g_controller1_buttons=buttons[0];game_voxel_update_input();buttons[0]=g_controller1_buttons;
    game_smash64_update_input(g_frame_count);game_link_update_input(g_frame_count);game_samus_update_input(g_frame_count);game_sonic_update_input(g_frame_count);
}
static void frame_begin(void *ctx) {(void)ctx;smb1_cycle_sync();g_frame_count=cyc_ring_frame;}
static void frame_end(void *ctx) {
    (void)ctx;smb1_cycle_sync();g_frame_count=cyc_ring_frame;
    game_widescreen_update();game_voxel_update();game_smash64_update(g_frame_count);game_link_update(g_frame_count);game_samus_update(g_frame_count);game_sonic_update(g_frame_count);
}
static const uint32_t *present(void *ctx,int *width,int *height) {
    (void)ctx;smb1_cycle_sync();const uint32_t *source=cyc_render_present(width,height);
    if(*width==256)source=smb1_cycle_native_picture();
    memcpy(picture,source,(size_t)*width**height*sizeof(*picture));
    game_voxel_post_render(picture);game_smash64_render_post_render(picture);game_link_render_post_render(picture);game_samus_render_post_render(picture);game_sonic_render_post_render(picture);game_coop_render(picture);return picture;
}
static bool option(void *ctx,const char *key,const char *value) {
    (void)ctx;
    if(!strcmp(key,"--coop")){if(strcmp(value,"0")&&strcmp(value,"2")&&strcmp(value,"3")&&strcmp(value,"4"))return false;game_coop_configure(atoi(value),0);return true;}
    if(!strcmp(key,"--coop-pause")){if(strcmp(value,"player")&&strcmp(value,"shared"))return false;return game_coop_arg(key,value)!=0;}
    if(!strcmp(key,"--widescreen-hud")&&strcmp(value,"edges")&&strcmp(value,"center"))return false;
    if(!strcmp(key,"--widescreen-camera")&&strcmp(value,"edges")&&strcmp(value,"centered"))return false;
    if(!strcmp(key,"--widescreen-enemies")&&strcmp(value,"viewport")&&strcmp(value,"classic")&&strcmp(value,"native"))return false;
    if(!strcmp(key,"--widescreen")){NesAspectMode mode;if(strcmp(value,"off")&&(!nes_video_aspect_from_name(value,&mode)||mode==NES_ASPECT_STOCK))return false;}
    return game_widescreen_arg(key,value)!=0;
}
void debug_server_send_fmt(const char *format,...) {
    char raw[4096];va_list args;va_start(args,format);vsnprintf(raw,sizeof raw,format,args);va_end(args);
    int id=0;if(sscanf(raw,"{\"id\":%d",&id)!=1)return;char *fields=strchr(raw,','),*end=strrchr(raw,'}');if(!fields||!end)return;*end=0;cyc_tcp_ok(id,fields+1);
}
static void tcp_coop(int id,const char *line) {smb1_cycle_sync();game_coop_debug("coop_state",id,line);}
#define WS_CMD(name) static void tcp_##name(int id,const char *line){(void)line;smb1_cycle_sync();int w,h;cyc_render_present(&w,&h);game_widescreen_debug(#name,id);}
WS_CMD(smb_ws_state) WS_CMD(smb_ws_seam) WS_CMD(smb_ws_actors)
static void tcp_setup(void *ctx) {(void)ctx;cyc_tcp_register("coop_state","logical player and shared-world state",tcp_coop);cyc_tcp_register("smb_ws_state","terrain state",tcp_smb_ws_state);cyc_tcp_register("smb_ws_seam","terrain comparison",tcp_smb_ws_seam);cyc_tcp_register("smb_ws_actors","resident state",tcp_smb_ws_actors);}
static void event(void *ctx,const void *raw,int player) {(void)ctx;cyc_presentation_event(raw,player);game_voxel_handle_event(raw);}
static void audio_mix(void *ctx,int16_t *samples,size_t count) {(void)ctx;nes_mod_audio_mix(samples,(int)count);}
static void state_loaded(void *ctx) {(void)ctx;smb1_cycle_sync();nes_mod_audio_stop_all();}
const CycHostExtras *cyc_host_extras(void) {
    static const CycHostOption options[]={
        {"--widescreen",true,"fit|16:9|21:9|32:9|off"},{"--widescreen-hud",true,"edges|center"},{"--widescreen-enemies",true,"viewport|classic|native"},{"--widescreen-camera",true,"edges|centered"},
        {"--coop",true,"0|2|3|4 logical simultaneous players"},{"--coop-pause",true,"player|shared"}
    };
    static const CycHostExtras x={.present=present,.power_on=power_on,.input=input,.frame_begin=frame_begin,.frame_end=frame_end,.event=event,.options=options,.option_count=sizeof options/sizeof options[0],.option=option,.tcp_setup=tcp_setup,.audio_rate=NES_MOD_AUDIO_SAMPLE_RATE,.audio_mix=audio_mix,.state_loaded=state_loaded};return &x;
}
