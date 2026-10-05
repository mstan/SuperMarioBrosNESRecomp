#pragma once
#include "cyc_presentation.h"
#include "cyc_mod.h"
#include "cyc_render.h"
#include "cyc_video.h"
#include "mod_function_hooks.h"
#include "logical_input.h"
#include "smb_cycle_symbols.h"
typedef struct { uint8_t A,X,Y,S,P,N,V,D,I,Z,C; } CPU6502State;
extern CPU6502State smb1_cycle_cpu;
#define g_cpu smb1_cycle_cpu
#define g_ppuscroll_x (cyc_render_line_scroll_x(32)&255)
#define g_ppuscroll_y (cyc_render_line_scroll_y(32)%240)
void smb1_cycle_sync(void);
void smb1_cycle_init(void);
void smb1_cycle_call(uint16_t address);
int call_by_address(uint16_t address);
uint8_t nes_read(uint16_t address);
uint8_t mapper_peek_prg(uint16_t address);
int mapper_get_mirroring(void);
int smb1_cycle_register_hook(const char *id,uint16_t address,NESModFunctionEntryCallback callback);
#define nes_mod_register_function_entry_plugin smb1_cycle_register_hook
void runtime_begin_unclocked(void);
void runtime_end_unclocked(void);
int runtime_get_vblank_depth(void);
int ppu_renderer_set_custom_render(CycCompositorFn fn,void *user);
int ppu_renderer_custom_render_active(void);
int ppu_renderer_background_opaque(int x,int y);
void ppu_renderer_set_background_opaque_frame(const uint8_t *pixels,int width,int height);
typedef int (*SmbSpriteSuppress)(int slot,int x,int y,void *user);
void ppu_renderer_set_sprite_suppress(SmbSpriteSuppress fn,void *user);
int ppu_renderer_sprite_suppressed(int slot,int x,int y);
const uint32_t *smb1_cycle_native_picture(void);
void runtime_get_visible_frame_start(uint8_t *ctrl,uint8_t *x,uint8_t *y,void *a,void *b);
void game_coop_cycle_title_ready(void);
extern uint64_t g_frame_count;
extern int g_ws_oam_sidecar,g_ws_obj_ctx_valid;
