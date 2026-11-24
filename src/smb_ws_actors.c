/* Authored enemy residents. The original five interaction slots still run in
 * the game. Residents outside those slots use its original init, graphics,
 * terrain collision and movement routines on isolated RAM, without guest time.
 * World coordinates never depend on the widened screen edge. */
#include "smb_ws_actors.h"
#include "smb_ws_world.h"
#include "game_widescreen.h"
#ifdef SMB1_CYCLE
#include "cycle_bridge.h"
#else
#include "nes_runtime.h"
#endif
#ifdef SMB1_CYCLE
#include "cycle_bridge.h"
#else
#include "mapper.h"
#endif
#ifdef SMB1_CYCLE
#include "cycle_bridge.h"
#else
#include "recomp_stack.h"
#endif
#include "mod_runtime.h"
#include "mod_function_hooks.h"
#include "mod_savestate.h"
#include "debug_server.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern void func_C26C(void), func_E87D(void), func_DFC1(void), func_C905(void);
extern void func_F1AF(void), func_F152(void), func_CD3C(void);
extern void func_E243(void), func_DA33(void);
extern void func_E54B(void);
extern void func_C787(void);
extern void func_E5C8(void), func_ED66(void), func_C982(void), func_D65B(void);
extern uint16_t g_rts_target;

enum { MAX_ACTORS=384, SPRITES=6, PAD=48, FRENZY_SWIM_SLOTS=3, FRENZY_SLOTS=4,
       BOWSER_PACKET_OFFSET=FRENZY_SLOTS+5*2, CLIPPED_PACKET_OFFSET=BOWSER_PACKET_OFFSET+2,
       TRANSIENT_PACKETS=CLIPPED_PACKET_OFFSET+6, ACTORS_STATE_VERSION=14 };
/* Every independently indexed normal-enemy field, including aliases used by
 * plants, flying koopas, squids, hammers and score popups. Slot zero is the
 * workspace; a transfer copies fields, never the surrounding shared RAM. */
static const uint16_t fields[] = {
    0x0f,0x16,0x1e,0x46,0x58,0x6e,0x87,0xa0,0xb6,0xcf,
    0x3c5,0x401,0x417,0x434,0x491,0x49a,0x3d8,0x78a,0x796,
    0x3c,0x3a2,0x110,0x12c,0x117,0x11e,0x125
};
enum { F_FLAG,F_ID,F_STATE,F_DIR,F_XS,F_PAGE,F_X,F_YS,F_YH,F_Y,
       F_ATTR,F_XF,F_YD,F_YF,F_COLL,F_BBOX,F_OFF,F_TIMER,F_INTERVAL,
       FIELD_COUNT=sizeof fields/sizeof fields[0] };
typedef struct { int16_t x,y; uint8_t tile,attr; } Sprite;
typedef struct { uint8_t count,native,oam_base,oam_span; Sprite sprite[SPRITES]; } Packet;
typedef struct {
    uint16_t spawn_x;
    uint8_t offset,member,spawn_y,kind,loaded,active,dead;
    int16_t native_slot;
    uint8_t state[FIELD_COUNT];
} Actor;
typedef struct {
    uint32_t version;
    uint16_t area,enemy_data,count;
    uint8_t world;
    int16_t owner[5];
    Actor actor[MAX_ACTORS];
    Packet display[MAX_ACTORS],next[MAX_ACTORS];
    Packet flag_display,flag_next;
    uint8_t contacts[MAX_ACTORS][MAX_ACTORS/8];
    int camera;
    uint64_t updates,loads,transfers;
    uint64_t score_display,score_next;
    Packet transient_display[TRANSIENT_PACKETS],transient_next[TRANSIENT_PACKETS];
    uint8_t swim_slots,swim_births;
} Actors;
static Actors s;
static int s_enabled,s_virtual,s_render_wide;
static SmbEnemyMode s_mode=SMB_ENEMIES_VIEWPORT;
typedef struct {
    uint8_t ram[0x800],runtime[1024];
    int runtime_len,bail,stack;
    CPU6502State cpu;
    uint16_t rts;
} Guest;

static int camera(void) { return (int16_t)((g_ram[0x71a]<<8)|g_ram[0x71c]); }
static int actor_x(const Actor *a) { return (a->state[F_PAGE]<<8)|a->state[F_X]; }
static int live_x(int slot) { return (g_ram[0x6e + slot]<<8)|g_ram[0x87+slot]; }
static int gameplay(void) { return g_ram[0x770]==1 && g_ram[0x772]==3; }
/* Balance platforms ($24) reference another native slot and need paired
 * ownership. Independent platforms retain all movement state in one actor. */
static int platform(int id) { return id>=0x25 && id<=0x2c; }
static int managed(int id) { return (id<=0x10 && id!=4 && id!=9) || platform(id); }
static int swim_scope(int slot) {
    if (!s_enabled || s_virtual || !gameplay() || slot>=FRENZY_SWIM_SLOTS ||
        g_render_width<=256 || g_ram[0x74e]!=0) return 0;
    int id=g_ram[0x16+slot];
    return id==0x0a || id==0x0b;
}
static uint8_t rom(int addr) { return mapper_peek_prg((uint16_t)addr); }
static void pull(Actor *a,int slot) {
    for (int i=0;i<FIELD_COUNT;i++) a->state[i]=g_ram[fields[i]+slot];
}
static void push(const Actor *a,int slot) {
    for (int i=0;i<FIELD_COUNT;i++) g_ram[fields[i]+slot]=a->state[i];
}
void smb_ws_actors_reset(void) {
    memset(&s,0,sizeof s); s.version=ACTORS_STATE_VERSION;
    for (int i=0;i<5;i++) s.owner[i]=-1;
}
static int begin(Guest *g,const Actor *a) {
#ifdef SMB1_CYCLE
    if(!cyc_mod_isolate_begin()) return 0;
    g->cpu=g_cpu;
#else
    g->runtime_len=runtime_get_state_blob(g->runtime,sizeof g->runtime);
    if (g->runtime_len<=0) return 0;
    memcpy(g->ram,g_ram,sizeof g->ram); g->cpu=g_cpu;
    g->bail=g_bail_active; g->stack=g_recomp_stack_top; g->rts=g_rts_target;
#endif
    runtime_begin_unclocked(); s_virtual=1;
    memset(g_ram+0x0f,0,6);
    push(a,0); g_ram[8]=0; g_cpu.X=0; g_cpu.S=0xfd;
#ifndef SMB1_CYCLE
    g_bail_active=0;
#endif
    /* Local screen projection serves only private graphics/bounding-box work.
     * Player/world coordinates and authored spawn positions remain absolute. */
    int cam=actor_x(a)-128;
    g_ram[0x71a]=(uint8_t)(cam>>8); g_ram[0x71c]=(uint8_t)cam;
    g_ram[0x71b]=(uint8_t)((cam+255)>>8); g_ram[0x71d]=(uint8_t)(cam+255);
    memset(g_ram+0x500,0,0x1a0);
    int first=actor_x(a)/16-16;
    for (int c=first;c<first+32;c++) {
        if (c<0 || c>=SMB_WS_META_COLUMNS) continue;
        int address=0x500+((c&16)?0xd0:0)+(c&15);
        for (int y=0;y<13;y++) g_ram[address+y*16]=g_smb_ws_world.collision[c][y];
    }
    g_ram[0x6e5]=0x40; g_ram[0x36a]=0;
    for (int i=0;i<64;i++) g_ram[0x200+i*4]=0xf8;
    return 1;
}
static void end(const Guest *g) {
#ifdef SMB1_CYCLE
    (void)g;cyc_mod_isolate_end();smb1_cycle_sync();
#else
    memcpy(g_ram,g->ram,sizeof g->ram); g_cpu=g->cpu;
    g_bail_active=g->bail; g_recomp_stack_top=g->stack; g_rts_target=g->rts;
    runtime_end_unclocked(); runtime_set_state_blob(g->runtime,g->runtime_len);
#endif
    s_virtual=0;
}
static void capture_packet(Packet *p,int native,int oam_base,int offset) {
    int wx=live_x(0);
    p->count=0; p->native=(uint8_t)native; p->oam_base=(uint8_t)oam_base;
    for (int i=0;i<SPRITES;i++) {
        const uint8_t *o=g_ram+0x200+offset+i*4;
        if (o[0]>=0xef) continue;
        Sprite *v=&p->sprite[p->count++];
        v->x=(int16_t)(wx+(int)o[3]-128); v->y=o[0]+1;
        v->tile=o[1]; v->attr=o[2];
    }
}
static void graphics(Packet *p,int native,int oam_base) {
    g_cpu.X=0; func_F1AF(); g_cpu.X=0; func_F152();
    g_cpu.X=0;
    if (platform(g_ram[0x16])) {
        if (g_ram[0x16]>=0x2b) func_ED66();
        else func_E5C8();
    } else func_E87D();
    capture_packet(p,native,oam_base,0x40);
}
static void capture_live_packet(Packet *p,int slot) {
    Actor current={0};
    pull(&current,slot);
    int oam_base=g_ram[0x6e5+slot]/4;
    Guest g;
    if (begin(&g,&current)) { graphics(p,1,oam_base); end(&g); }
}
static void flag_graphics(Packet *p,const Actor *a,int native,int oam_base) {
    Guest g;
    if (!begin(&g,a)) return;
    if (!native) { g_ram[0x70f]=0; g_ram[0x10d]=0xb0; }
    g_cpu.X=0; func_F1AF(); g_cpu.X=0; func_F152();
    g_cpu.X=0; func_E54B(); capture_packet(p,native,oam_base,0x40); end(&g);
}
static void add(int ofs,int member,int wx,int y,int kind) {
    if (s.count>=MAX_ACTORS) return;
    Actor *a=&s.actor[s.count++];
    a->offset=(uint8_t)ofs; a->member=(uint8_t)member; a->spawn_x=(uint16_t)wx;
    a->spawn_y=(uint8_t)y; a->kind=(uint8_t)kind; a->native_slot=-1;
}
static int ensure(void) {
    if (!s_enabled || s_virtual || !g_smb_ws_world.valid) return 0;
    unsigned enemy=g_ram[0xe9]|(g_ram[0xea]<<8);
    if (enemy<0x8000) return 0;
    if (s.area==g_smb_ws_world.area_data && s.enemy_data==enemy && s.world==g_ram[0x75f]) return 1;
    smb_ws_actors_reset(); s.area=g_smb_ws_world.area_data; s.enemy_data=(uint16_t)enemy; s.world=g_ram[0x75f];
    /* Native enemy parsing retires records behind the initial right edge.
     * A midpoint/pipe reload must not revive those bodies beside Mario before
     * he receives control. Keep viewport activation for the remaining records. */
    const int entrance_right=camera()+255;
    int page=0,selected=0;
    for (int ofs=0;ofs<255;) {
        int b0=rom(enemy+ofs),b1=rom(enemy+ofs+1),row=b0&15;
        if (b0==0xff) break;
        if ((b1&128) && !selected) { page++; selected=1; }
        if (row==15 && !selected) { page=b1&63; selected=1; ofs+=2; continue; }
        int wx=page*256+(b0&0xf0);
        if (row<14 && wx>=entrance_right && (!(b1&64) || g_ram[0x6cc])) {
            int id=b1&63;
            if (managed(id)) add(ofs,0,wx,row*16,(id==6 && g_ram[0x76a])?2:id);
            else if (id>=0x37 && id<=0x3e) {
                int group=id-0x37,kind=group<4?(g_ram[0x76a]?2:6):0;
                /* A group record marks its activation boundary, not its first
                 * body. CheckRightBounds admits it at native right+48, and
                 * HandleGroupEnemies places bodies from that native edge. */
                for (int n=0;n<2+(group&1);n++) add(ofs,n,wx-48+n*24,(group&2)?0x70:0xb0,kind);
            }
        }
        ofs+=row==14?3:2; selected=0;
    }
    for (int i=0;i<g_smb_ws_world.plant_count;i++) {
        const SmbWsPlant *p=&g_smb_ws_world.plants[i];
        add(255,0,p->x,p->y,0x0d);
    }
    return 1;
}
static void initialize(Actor *a) {
    memset(a->state,0,sizeof a->state);
    a->state[F_FLAG]=1; a->state[F_ID]=a->kind;
    a->state[F_PAGE]=(uint8_t)(a->spawn_x>>8); a->state[F_X]=(uint8_t)a->spawn_x;
    a->state[F_YH]=1; a->state[F_Y]=a->spawn_y;
    Guest g;
    if (!begin(&g,a)) return;
    if (a->offset==255 && a->kind==0x0d) func_C787();
    else func_C26C();
    pull(a,0); end(&g);
    a->loaded=1; s.loads++;
}
static void detach(int slot) {
    int n=s.owner[slot];
    if (n>=0) { pull(&s.actor[n],slot); s.actor[n].native_slot=-1; }
    s.owner[slot]=-1; g_ram[0x0f+slot]=0;
}
static void promote(int n) {
    Actor *a=&s.actor[n]; int slot=-1;
    for (int j=0;j<5;j++) if (!g_ram[0x0f+j] && s.owner[j]!=-2) { slot=j; break; }
    /* Keep the scarce original interaction slots closest to Mario. */
    if (slot<0) {
        int px=(g_ram[0x6d]<<8)|g_ram[0x86],far=abs(actor_x(a)-px)+32;
        for (int j=0;j<5;j++) if (s.owner[j]>=0) {
            int distance=abs(live_x(j)-px);
            if (distance>far && distance>80) { slot=j; far=distance; }
        }
        if (slot>=0) detach(slot);
    }
    if (slot<0) return;
    a->state[F_COLL]=0;
    for (int j=0;j<5;j++) g_ram[0x491+j]&=(uint8_t)~(0x80u>>slot);
    push(a,slot); s.owner[slot]=(int16_t)n; a->native_slot=(int16_t)slot; s.transfers++;
}
static void collide_residents(void) {
    if (!(g_ram[9]&1) || g_ram[0x747] || (g_ram[0x776]&1) || !g_ram[0x74e]) return;
    for (int n=0;n<s.count;n++) for (int m=n+1;m<s.count;m++) {
        Actor *a=&s.actor[n],*b=&s.actor[m];
        uint8_t *contact=&s.contacts[n][m/8],mask=(uint8_t)(1u<<(m&7));
        int ay=a->state[F_Y]+a->state[F_YH]*256,by=b->state[F_Y]+b->state[F_YH]*256;
        if (platform(a->kind) || platform(b->kind) ||
            !a->loaded || !b->loaded || a->active!=1 || b->active!=1 || a->dead || b->dead ||
            abs(actor_x(a)-actor_x(b))>48 || abs(ay-by)>48) { *contact&=(uint8_t)~mask; continue; }
        if (a->native_slot>=0 && b->native_slot>=0) continue; /* native game handled this pair */
        Guest g;
        if (!begin(&g,a)) continue;
        push(b,1);
        /* A pair has a persistent latch of its own. Native collision bits are
         * indexed by the five transient slots and cannot identify residents. */
        g_ram[0x491]=(*contact&mask)?0x40:0;
        for (int slot=0;slot<2;slot++) {
            g_ram[8]=(uint8_t)slot; g_cpu.X=(uint8_t)slot; func_F1AF();
            g_cpu.X=(uint8_t)slot; func_F152(); g_cpu.X=(uint8_t)slot; func_E243();
        }
        g_ram[8]=1; g_cpu.X=1; func_DA33();
        if (g_ram[0x491]&0x40) *contact|=mask; else *contact&=(uint8_t)~mask;
        uint8_t ac=a->state[F_COLL],bc=b->state[F_COLL];
        pull(a,0); pull(b,1); a->state[F_COLL]=ac; b->state[F_COLL]=bc;
        end(&g);
        if (a->native_slot>=0) push(a,a->native_slot);
        if (b->native_slot>=0) push(b,b->native_slot);
    }
}
/* Hooks execute with SMB's ordinary C-call ABI (push_all_jsr is disabled).
 * Returning 1 replaces the original C function; there is no guest RTS to pop. */
static int spawn_hook(uint16_t addr) {
    (void)addr;
    if (!s_enabled || s_virtual || !gameplay() || !ensure()) return 0;
    int slot=g_cpu.X;
    if (slot>=5) return 0;
    if (slot<FRENZY_SWIM_SLOTS) {
        unsigned bit=1u<<slot;
        s.swim_slots&=(uint8_t)~bit;
        if (s.swim_births&bit) {
            s.swim_births&=(uint8_t)~bit;
            s.swim_slots|=(uint8_t)bit;
            int old=s.owner[slot];
            if (old>=0) {
                s.actor[old].dead=1;
                s.actor[old].native_slot=-1;
            }
            s.owner[slot]=-1;
            return 0; /* The native frenzy owns the slot and swimmer motion. */
        }
    }
    if (!managed(g_ram[0x16+slot])) return 0;
    int ofs=g_ram[0x739],n=-1;
    /* Group initialization calls this repeatedly at the same data offset. */
    int code=rom(s.enemy_data+ofs+1)&63,grouped=code>=0x37 && code<=0x3e;
    int member=grouped?(live_x(slot)-((g_ram[0x71b]<<8)|g_ram[0x71d]))/24:0;
    for (int i=0;i<s.count;i++) if (s.actor[i].offset==ofs &&
        s.actor[i].kind==g_ram[0x16+slot] && s.actor[i].member==member &&
        (grouped || abs((int)s.actor[i].spawn_x-live_x(slot))<=48)) { n=i; break; }
    if (n<0) return 0;
    Actor *a=&s.actor[n];
    if (s_mode==SMB_ENEMIES_CLASSIC && !a->active && !a->dead) {
        s.owner[slot]=(int16_t)n; a->native_slot=(int16_t)slot; a->active=a->loaded=1;
        return 0; /* original activation/initialization, including its cycles */
    }
    if (!a->loaded && !a->dead) initialize(a);
    a->active=1;
    if (!a->dead && a->native_slot<0 && actor_x(a)>=camera()-24 && actor_x(a)<=camera()+304) {
        a->state[F_COLL]=0;
        for (int j=0;j<5;j++) g_ram[0x491+j]&=(uint8_t)~(0x80u>>slot);
        push(a,slot); s.owner[slot]=(int16_t)n; a->native_slot=(int16_t)slot; s.transfers++;
    } else {
        /* The parser must consume a resident/dead record, without creating a
         * second object. Its success flag is retired before another game tick. */
        g_ram[0x0f+slot]=1; s.owner[slot]=-2;
    }
    return 1;
}
/* Area construction can leave a live plant before its graphics hook runs.
 * Claim that original object before any resident preview can create a twin. */
static int adopt_plant(int slot) {
    int n=s.owner[slot];
    if (n>=0 || !g_ram[0x0f+slot] || g_ram[0x16+slot]!=0x0d) return n;
    for (int i=0;i<s.count;i++) {
        Actor *a=&s.actor[i];
        if (a->offset!=255 || a->spawn_x!=live_x(slot) || a->native_slot>=0) continue;
        a->loaded=a->active=1; a->dead=0;
        a->native_slot=(int16_t)slot; s.owner[slot]=(int16_t)i;
        pull(a,slot); return i;
    }
    return n;
}
static int gfx_hook(uint16_t addr) {
    (void)addr;
    if (!s_enabled || s_virtual || !gameplay() || g_cpu.X>=5) return 0;
    int slot=g_cpu.X,n=s.owner[slot];
    if (swim_scope(slot) && (s.swim_slots&(1u<<slot))) {
        capture_live_packet(&s.transient_next[slot],slot);
        return 0;
    }
    if (slot<FRENZY_SLOTS && g_render_width>256 &&
        g_ram[0x0f+slot] && g_ram[0x16+slot]==0x14) {
        int x=live_x(slot),cam=camera(),left,right;
        game_widescreen_actor_range(cam,g_render_width,8,&left,&right);
        /* Native flying fish already keep moving beyond the camera. Recover
         * sprite columns at its edges without changing frenzy or motion. */
        if (x+16>left && x<right && (x<cam+8 || x+24>cam+256))
            capture_live_packet(&s.transient_next[slot],slot);
        return 0;
    }
    /* Initial screen construction can create a plant before gameplay starts.
     * Adopt that live object before considering any preview of the same pipe. */
    if (n<0 && g_ram[0x16+slot]==0x0d && g_ram[0x0f+slot] && ensure()) n=adopt_plant(slot);
    /* Adopt native platforms already present when loading a machine-only
     * checkpoint. Multiple lifts may share X; claim a distinct resident for
     * each live slot, preserving its current phase instead of reinitializing. */
    if (n<0 && platform(g_ram[0x16+slot]) && g_ram[0x0f+slot] && ensure()) {
        int best=65536;
        for (int i=0;i<s.count;i++) {
            Actor *a=&s.actor[i];
            if (a->kind!=g_ram[0x16+slot] || a->native_slot>=0 || a->dead) continue;
            int shifted=(a->kind==0x26 || a->kind==0x27 || a->kind>=0x2b)?12:0;
            int dx=abs((int)a->spawn_x+shifted-live_x(slot));
            int dy=abs((int)(a->loaded?a->state[F_Y]:a->spawn_y)-g_ram[0xcf+slot]);
            if (dy>128) dy=256-dy;
            if (dx<=48 && dx*256+dy<best) { n=i; best=dx*256+dy; }
        }
        if (n>=0) {
            Actor *a=&s.actor[n]; a->loaded=a->active=1;
            a->native_slot=(int16_t)slot; s.owner[slot]=(int16_t)n; pull(a,slot);
        }
    }
    if (n>=0) capture_live_packet(&s.next[n],slot);
    return 0;
}
static void capture_preclip_packet(Packet *p,int slot,int span,int drawn,int x,int cam) {
    int oam=g_ram[0x6e5+slot];
    if (oam>256-span*4) return;
    p->count=0; p->oam_base=(uint8_t)(oam/4); p->oam_span=(uint8_t)span;
    for (int i=0;i<drawn;i++) {
        const uint8_t *o=g_ram+0x200+oam+i*4;
        if (o[0]>=0xef) continue;
        Sprite *v=&p->sprite[p->count++];
        v->x=(int16_t)(x+(int8_t)(o[3]-(uint8_t)(x-cam)));
        v->y=o[0]+1; v->tile=o[1]; v->attr=o[2];
    }
    p->native=p->count!=0;
}
static int sprite_clip_hook(uint16_t addr) {
    (void)addr;
    if (!s_enabled || s_virtual || g_render_width<=256 || !gameplay()) return 0;
    int slot=g_ram[8];
    if (slot>=6 || g_ram[0xb6+slot]!=1) return 0;
    int kind=g_ram[0x16+slot];
    int packet=CLIPPED_PACKET_OFFSET+slot,span=SPRITES;
    switch (kind) {
    case 0x2d: {
        int half=g_ram[0x36a];
        if (!half || half>2) return 0;
        packet=BOWSER_PACKET_OFFSET+half-1;
        break;
    }
    case 0x2e:
        if (slot!=5 || !g_ram[0x0f+slot]) return 0;
        span=4;
        break;
    case 0x08:
        /* Area-managed objects already have their own wide draw packet. */
        if (slot>=5 || s.owner[slot]>=0 || !g_ram[0x0f+slot]) return 0;
        break;
    case 0x11:
    case 0x12:
    case 0x32:
    case 0x35:
        if (slot>=5 || !g_ram[0x0f+slot]) return 0;
        break;
    default:
        return 0;
    }
    int offscreen=g_ram[0x3d1];
    if (offscreen&0x80) return 0;
    int x=live_x(slot),cam=camera(),left,right;
    game_widescreen_actor_range(cam,g_render_width,8,&left,&right);
    if (x+16<=left || x>=right || (x>=cam+8 && x+24<=cam+256)) return 0;

    /* The native draw has selected the tiles, palette, priority and flips.
     * Keep the rows still on screen before the original column clip. One
     * packet per native slot follows the OAM used by its current actor. */
    int drawn=span;
    if (offscreen&0x40) drawn=2;
    else if (offscreen&0x20) drawn=4;
    capture_preclip_packet(&s.transient_next[packet],slot,span,drawn,x,cam);
    return 0;
}
static int flame_clip_hook(uint16_t addr) {
    (void)addr;
    if (!s_enabled || s_virtual || g_render_width<=256 || !gameplay()) return 0;
    int slot=g_ram[8];
    if (slot>=6 || g_ram[0x16+slot]!=0x15 || g_ram[0xb6+slot]!=1) return 0;
    int x=live_x(slot),cam=camera(),left,right;
    game_widescreen_actor_range(cam,g_render_width,8,&left,&right);
    if (x+24<=left || x>=right || (x>=cam+8 && x+24<=cam+256)) return 0;
    /* The flame routine has drawn all three tiles. The original code still
     * clips them and controls motion, collision, and lifetime. */
    capture_preclip_packet(&s.transient_next[CLIPPED_PACKET_OFFSET+slot],slot,3,3,x,cam);
    return 0;
}
static int firebar_scope(int slot) {
    return s_enabled && !s_virtual && gameplay() && g_render_width>256 && slot<5 &&
           g_ram[0x0f+slot] && g_ram[0x16+slot]>=0x1b && g_ram[0x16+slot]<=0x21;
}
static int firebar_hook(uint16_t addr) {
    (void)addr;
    int slot=g_cpu.X;
    if (!firebar_scope(slot) || g_ram[0xb6+slot]!=1 || !ensure()) return 0;
    int long_bar=g_ram[0x16+slot]>=0x1f;
    int reach=long_bar?96:48;
    int x=live_x(slot),cam=camera(),left,right;
    game_widescreen_actor_range(cam,g_render_width,8,&left,&right);
    if (x+reach<left || x-reach>=right || (x-reach>=cam && x+reach<cam+256)) return 0;
    int extra=g_ram[0x6cf];
    if (long_bar && (extra>5 || g_ram[0x0f+extra]!=(0x80|slot))) return 0;
    int original_oam=g_ram[0x6e5+slot]/4;
    int second_oam=long_bar?g_ram[0x6e5+extra]/4:0;
    uint8_t speed=g_ram[0x388+slot],direction=g_ram[0x34+slot];
    uint8_t native_screen[4],projected_screen[4];
    memcpy(native_screen,g_ram+0x71a,sizeof native_screen);
    Actor current={0}; pull(&current,slot);
    Guest g;
    if (!begin(&g,&current)) return 0;
    memcpy(projected_screen,g_ram+0x71a,sizeof projected_screen);
    memcpy(g_ram+0x71a,native_screen,sizeof native_screen);
    func_F1AF();
    int native_clipped=g_ram[0x3d1]&8;
    memcpy(g_ram+0x71a,projected_screen,sizeof projected_screen);
    g_ram[0x388]=speed;
    g_ram[0x34]=direction;
    g_ram[0x79f]=1; /* The original pass owns player contact. */
    if (native_clipped && s_mode==SMB_ENEMIES_CLASSIC) g_ram[0x747]=1;
    g_ram[0x6cf]=1;
    g_ram[0x6e6]=0x58;
    g_cpu.X=0;
    func_CD3C();
    Packet *p=&s.transient_next[FRENZY_SLOTS+slot*2];
    capture_packet(p,1,original_oam,0x40);
    if (!p->count) p->native=0;
    if (long_bar) {
        capture_packet(p+1,1,second_oam,0x58);
        if (!p[1].count) p[1].native=0;
    }
    uint8_t spin_low=g_ram[0x58],spin_high=g_ram[0xa0];
    end(&g);
    /* The stock tick advances visible bars. In viewport mode the projected
     * tick owns the phase only on frames the stock screen would skip. */
    if (native_clipped && s_mode==SMB_ENEMIES_VIEWPORT) {
        g_ram[0x58+slot]=spin_low;
        g_ram[0xa0+slot]=spin_high;
    }
    return 0;
}
static int plant_hook(uint16_t addr) {
    (void)addr;
    if (!s_enabled || s_virtual || smb_ws_world_busy() || !gameplay() || g_cpu.X>=5 || !ensure()) return 0;
    int slot=g_cpu.X,n=-1;
    for (int i=0;i<s.count;i++) if (s.actor[i].offset==255 && s.actor[i].spawn_x==live_x(slot)) { n=i; break; }
    if (n<0) return 0;
    Actor *a=&s.actor[n];
    if (s_mode==SMB_ENEMIES_CLASSIC && !a->active && !a->dead) {
        s.owner[slot]=(int16_t)n; a->native_slot=(int16_t)slot; a->active=a->loaded=1;
        return 0;
    }
    if (!a->loaded && !a->dead) initialize(a);
    /* Preserve the real initializer's register/flag result before handing
     * its slot to an existing resident (or retiring a duplicate). */
    s_virtual=1; func_C787(); s_virtual=0;
    a->active=1;
    if (!a->dead && a->native_slot<0 && a->loaded) {
        push(a,slot); s.owner[slot]=(int16_t)n; a->native_slot=(int16_t)slot; s.transfers++;
    } else { g_ram[0x0f+slot]=0; s.owner[slot]=-1; }
    return 1;
}
static int flag_hook(uint16_t addr) {
    (void)addr;
    if (!s_enabled || s_virtual || smb_ws_world_busy() || !gameplay() || g_cpu.X!=5 ||
        !g_ram[0x14] || g_ram[0x1b]!=0x30 || smb_ws_world_flag_x()!=live_x(5)) return 0;
    Actor flag={0}; pull(&flag,5);
    flag_graphics(&s.flag_next,&flag,1,g_ram[0x6ea]/4);
    return 0;
}
static int cull_hook(uint16_t addr) {
    (void)addr;
    if (!s_enabled || s_virtual || !gameplay() || g_cpu.X>=5 || s.owner[g_cpu.X]<0) return 0;
    int x=live_x(g_cpu.X),cam=camera();
    return x<cam || x>cam+304;
}
static int score_gfx_hook(uint16_t addr) {
    (void)addr;
    if (!s_enabled || s_virtual || !gameplay()) return 0;
    /* SetupNumSpr writes a score glyph pair at the native OAM offset in Y. */
    unsigned slot=g_cpu.Y/4;
    if (slot<63) s.score_next|=UINT64_C(3)<<slot;
    return 0;
}
static int swim_birth_hook(uint16_t addr) {
    (void)addr;
    int slot=g_cpu.X;
    if (!swim_scope(slot) || !ensure()) return 0;
    s.swim_births|=(uint8_t)(1u<<slot);
    if (s_mode==SMB_ENEMIES_VIEWPORT) {
        int left,right;
        game_widescreen_actor_range(camera(),g_render_width,0,&left,&right);
        /* Keep the native 32-pixel lead beyond the visible rightmost pixel. */
        int x=right+31;
        g_ram[0x6e + slot]=(uint8_t)(x>>8);
        g_ram[0x87+slot]=(uint8_t)x;
    }
    return 0;
}
static int transient_cull_hook(uint16_t addr) {
    (void)addr;
    int slot=g_cpu.X;
    if (s_mode!=SMB_ENEMIES_VIEWPORT ||
        !(firebar_scope(slot) || (swim_scope(slot) && (s.swim_slots&(1u<<slot))))) return 0;
    int left,right;
    game_widescreen_actor_range(camera(),g_render_width,0,&left,&right);
    int native_right=(g_ram[0x71b]<<8)|g_ram[0x71d];
    /* Shift the native scratch bounds by the actual viewport deltas, keeping
     * their padding and all original comparison and retirement behavior. */
    left+=((g_ram[0]<<8)|g_ram[1])-camera();
    right+=((g_ram[2]<<8)|g_ram[3])-native_right-1;
    g_ram[0]=(uint8_t)(left>>8); g_ram[1]=(uint8_t)left;
    g_ram[2]=(uint8_t)(right>>8); g_ram[3]=(uint8_t)right;
    return 0;
}
void smb_ws_actors_begin_frame(void) {
    if (!s_enabled || runtime_get_vblank_depth()>1) return;
    s_render_wide=g_render_width>256 || game_backtracking_active();
    /* SMB retains OAM while native pause skips object graphics. Keep the
     * matching resident packets instead of consuming an empty next bank. */
    if (g_ram[0x776]&1) return;
    memcpy(s.display,s.next,sizeof s.display); memset(s.next,0,sizeof s.next);
    s.flag_display=s.flag_next; memset(&s.flag_next,0,sizeof s.flag_next);
    s.score_display=s.score_next; s.score_next=0;
    memcpy(s.transient_display,s.transient_next,sizeof s.transient_display);
    memset(s.transient_next,0,sizeof s.transient_next);
    s.camera=camera();
}
void smb_ws_actors_update(void) {
    if (!s_enabled || !gameplay() || (g_ram[0x776]&1) ||
        !ensure() || runtime_get_vblank_depth()>1) return;
    int cam=camera(),left,right;
    game_widescreen_actor_range(cam,g_render_width,PAD,&left,&right);
    uint8_t native_ticked[MAX_ACTORS]={0};
    for (int slot=0;slot<5;slot++) adopt_plant(slot);
    for (int slot=0;slot<5;slot++) {
        int n=s.owner[slot];
        if (n==-2) { g_ram[0x0f+slot]=0; s.owner[slot]=-1; continue; }
        if (n<0) continue;
        native_ticked[n]=1;
        Actor *a=&s.actor[n]; pull(a,slot);
        if (!a->state[F_FLAG]) { a->dead=1; a->native_slot=-1; s.owner[slot]=-1; continue; }
        int x=actor_x(a);
        if (x<cam-24 || x>cam+304) detach(slot);
    }
    for (int n=0;n<s.count;n++) {
        Actor *a=&s.actor[n];
        if (a->dead || a->native_slot>=0) continue;
        if (!a->loaded) {
            if (a->spawn_x<left || a->spawn_x>right) continue;
            initialize(a);
            if (!a->loaded) continue;
            a->active=s_mode==SMB_ENEMIES_VIEWPORT;
        }
        int x=actor_x(a);
        if (game_backtracking_active()) {
            if (a->active && (x<left-32 || x>right+32)) { a->active=2; continue; }
            if (a->active==2) a->active=1; /* sleep retains position, phase and defeat history */
        } else if (a->active && (x<left-32 || x>right+32)) { a->dead=1; continue; }
        if (native_ticked[n]) continue; /* already advanced by this frame's native routine */
        Guest g;
        if (!begin(&g,a)) continue;
        /* Cycle isolation does not populate Guest.ram; the live isolated RAM
         * retains the current game's pause flag on both backends. */
        int run=a->active && !(g_ram[0x776]&1);
        if (run && !g_ram[0x747]) {
            if (g_ram[0x78a]) g_ram[0x78a]--;
            if (g_ram[0x77f]==0x14 && g_ram[0x796]) g_ram[0x796]--;
        }
        if (!a->active) g_ram[9]=0;
        g_ram[0x3c5]=0;
        if (platform(a->kind)) {
            /* Native platform collision remains in its interaction slot.
             * A detached platform has no rider. Large platforms move before
             * drawing; small paired lifts draw before their shared movement. */
            g_ram[0x3a2]=a->kind>=0x2b?0:0xff;
            if (run && !g_ram[0x747] && a->kind<0x2b) {
                g_cpu.X=0; func_C982(); s.updates++;
            }
            graphics(&s.next[n],0,64);
            if (run && !g_ram[0x747] && a->kind>=0x2b) {
                g_cpu.X=0; func_D65B(); s.updates++;
            }
        } else {
            graphics(&s.next[n],0,64);
        }
        if (!platform(a->kind) && run && g_ram[0x0f]) {
            g_cpu.X=0; func_DFC1();
            if (!g_ram[0x747]) { g_cpu.X=0; func_C905(); s.updates++; }
        }
        pull(a,0); end(&g);
        if (!a->state[F_FLAG]) { a->dead=1; continue; }
        x=actor_x(a);
        if (a->active && x>=cam-24 && x<=cam+288) promote(n);
    }
    collide_residents();
    if (!s.flag_next.count) {
        int x=smb_ws_world_flag_x();
        if (x>=0 && x>=left-16 && x<=right) {
            Actor flag={0};
            flag.state[F_FLAG]=1; flag.state[F_ID]=0x30;
            flag.state[F_PAGE]=(uint8_t)(x>>8); flag.state[F_X]=(uint8_t)x;
            flag.state[F_YH]=1; flag.state[F_Y]=0x30;
            /* Before native loading, preview only the authored flag. Once
             * loaded, the flag hook supplies its real animation and score. */
            if (g_ram[0x1b]!=0x30 || live_x(5)!=x)
                flag_graphics(&s.flag_next,&flag,0,64);
        }
    }
}
int smb_ws_actors_suppress_sprite(int slot) {
    if (!s_enabled || !s_render_wide || !gameplay() || !g_smb_ws_world.valid) return 0;
    if ((unsigned)slot<64 && ((s.score_display>>slot)&1)) return 0;
    for (int n=0;n<s.count;n++) {
        const Packet *p=&s.display[n];
        if (p->native && slot>=p->oam_base && slot<p->oam_base+SPRITES) return 1;
    }
    for (int n=0;n<TRANSIENT_PACKETS;n++) {
        const Packet *p=&s.transient_display[n];
        if (!p->native) continue;
        int span=p->oam_span?p->oam_span:SPRITES;
        if (slot>=p->oam_base && slot<p->oam_base+span) return 1;
    }
    return s.flag_display.native && slot>=s.flag_display.oam_base && slot<s.flag_display.oam_base+SPRITES;
}
void smb_ws_actors_draw(uint32_t *out,int width,int native_x0,int render_camera,const uint8_t *opaque) {
    if (!s_enabled || !gameplay() || !(g_ppumask&16)) return;
    int pattern=(g_ppuctrl&8)?0x1000:0;
    /* Respect native sprite priority, including score glyphs that now own
     * the same OAM slot as the replaced enemy packet. */
    uint8_t native_priority[256*240]; memset(native_priority,255,sizeof native_priority);
    for (int slot=63;slot>=0;slot--) {
        const uint8_t *o=g_ppu_oam+slot*4;
        if (o[0]>=0xef || ppu_renderer_sprite_suppressed(slot,o[3],o[0]+1)) continue;
        for (int y=0;y<8;y++) for (int x=0;x<8;x++) {
            int dx=o[3]+x,dy=o[0]+1+y;
            if (dx>=256 || dy>=240 || (dx<8 && !(g_ppumask&4))) continue;
            int off=pattern+o[1]*16+((o[2]&128)?7-y:y),bit=(o[2]&64)?x:7-x;
            int color=((g_chr_ram[off]>>bit)&1)|(((g_chr_ram[off+8]>>bit)&1)<<1);
            if (color) native_priority[dy*256+dx]=(uint8_t)slot;
        }
    }
    for (int n=s.count+TRANSIENT_PACKETS;n>=0;n--) {
        const Packet *p;
        if (n<s.count) p=&s.display[n];
        else if (n==s.count) p=&s.flag_display;
        else p=&s.transient_display[n-s.count-1];
        for (int i=p->count-1;i>=0;i--) {
            const Sprite *v=&p->sprite[i];
            for (int y=0;y<8;y++) for (int x=0;x<8;x++) {
                int dx=v->x-render_camera+native_x0+x,dy=v->y+y;
                if (dx<0 || dx>=width || dy<32 || dy>=240) continue;
                uint8_t *priority=dx>=native_x0 && dx<native_x0+256 ?
                    &native_priority[dy*256+dx-native_x0] : NULL;
                if (priority && *priority<=(p->native?p->oam_base:64)) continue;
                int off=pattern+v->tile*16+((v->attr&128)?7-y:y),bit=(v->attr&64)?x:7-x;
                int color=((g_chr_ram[off]>>bit)&1)|(((g_chr_ram[off+8]>>bit)&1)<<1);
                if (!color || ((v->attr&32) && opaque[dy*width+dx])) continue;
                out[dy*width+dx]=g_nes_palette[g_ppu_pal[16+(v->attr&3)*4+color]&63];
                if (priority && n>s.count) *priority=p->oam_base;
            }
        }
    }
}
void smb_ws_actors_configure(int enabled,SmbEnemyMode mode) {
    int active=enabled && mode!=SMB_ENEMIES_NATIVE;
    if (active!=s_enabled || mode!=s_mode) smb_ws_actors_reset();
    s_enabled=active; s_mode=mode;
    nes_mod_set_function_hook_enabled("super-mario-bros.widescreen.enemy-init",active);
    nes_mod_set_function_hook_enabled("super-mario-bros.widescreen.enemy-gfx",active);
    nes_mod_set_function_hook_enabled("super-mario-bros.widescreen.enemy-cull",active);
    nes_mod_set_function_hook_enabled("super-mario-bros.widescreen.score-gfx",active);
    nes_mod_set_function_hook_enabled("super-mario-bros.widescreen.swim-birth",active);
    nes_mod_set_function_hook_enabled("super-mario-bros.widescreen.transient-cull",active);
    nes_mod_set_function_hook_enabled("super-mario-bros.widescreen.firebar-gfx",active);
    nes_mod_set_function_hook_enabled("super-mario-bros.widescreen.sprite-clip",active);
    nes_mod_set_function_hook_enabled("super-mario-bros.widescreen.flame-clip",active);
    nes_mod_set_function_hook_enabled("super-mario-bros.widescreen.flag-gfx",active);
    nes_mod_set_function_hook_enabled("super-mario-bros.widescreen.plant-init",active);
    nes_mod_set_function_hook_enabled("super-mario-bros.widescreen.large-platform-gfx",active);
    nes_mod_set_function_hook_enabled("super-mario-bros.widescreen.small-platform-gfx",active);
}
int smb_ws_actors_debug(const char *cmd,int id) {
    if (!strcmp(cmd,"smb_ws_flag")) {
        debug_server_send_fmt("{\"id\":%d,\"world_x\":%d,\"sprites\":%d,\"native\":%d,\"x\":%d,\"y\":%d}",
            id,smb_ws_world_flag_x(),s.flag_display.count,s.flag_display.native,
            s.flag_display.count?s.flag_display.sprite[0].x:-1,
            s.flag_display.count?s.flag_display.sprite[0].y:-1);
        return 1;
    }
    if (strcmp(cmd,"smb_ws_enemies") && strcmp(cmd,"smb_ws_actors")) return 0;
    char buf[7800]; int loaded=0,native=0,active=0,sprites=0;
    for (int i=0;i<s.count;i++) if (s.actor[i].loaded && !s.actor[i].dead) {
        loaded++; native+=s.actor[i].native_slot>=0; active+=s.actor[i].active==1; sprites+=s.display[i].count;
    }
    int len=snprintf(buf,sizeof buf,"{\"id\":%d,\"enabled\":%d,\"policy\":%d,\"authored\":%d,\"loaded\":%d,\"active\":%d,\"native\":%d,\"sprites\":%d,\"updates\":%llu,\"transfers\":%llu,\"camera\":%d,\"enemies\":[",id,s_enabled,s_mode,s.count,loaded,active,native,sprites,(unsigned long long)s.updates,(unsigned long long)s.transfers,s.camera);
    int comma=0;
    for (int i=0;i<s.count && len<(int)sizeof buf-220;i++) if (s.actor[i].loaded) {
        const Actor *a=&s.actor[i];
        len+=snprintf(buf+len,sizeof buf-len,"%s{\"record\":%d,\"member\":%d,\"kind\":%d,\"spawn_x\":%d,\"x\":%d,\"y\":%d,\"active\":%d,\"dead\":%d,\"slot\":%d,\"sprites\":%d}",comma++?",":"",a->offset,a->member,a->kind,a->spawn_x,actor_x(a),a->state[F_Y]+(a->state[F_YH]-1)*256,a->active,a->dead,a->native_slot,s.display[i].count);
    }
    snprintf(buf+len,sizeof buf-len,"]}"); debug_server_send_fmt("%s",buf); return 1;
}
static int save(uint8_t *data,int cap) {
    if (cap<(int)sizeof s) return -1; memcpy(data,&s,sizeof s); return sizeof s;
}
static int load(const uint8_t *data,int len) {
    uint32_t version;
    if (!len) { smb_ws_actors_reset(); return 1; }
    if (len!=sizeof s) return 0;
    memcpy(&version,data,sizeof version); if (version!=ACTORS_STATE_VERSION) return 0;
    Actors candidate; memcpy(&candidate,data,sizeof candidate);
    if (candidate.count>MAX_ACTORS) return 0;
    for (int i=0;i<5;i++) if (candidate.owner[i]<-2 || candidate.owner[i]>=candidate.count) return 0;
    for (int i=0;i<candidate.count;i++) if (candidate.display[i].count>SPRITES || candidate.next[i].count>SPRITES) return 0;
    if (candidate.flag_display.count>SPRITES || candidate.flag_next.count>SPRITES) return 0;
    for (int i=0;i<TRANSIENT_PACKETS;i++)
        if (candidate.transient_display[i].count>SPRITES || candidate.transient_next[i].count>SPRITES ||
            candidate.transient_display[i].oam_span>SPRITES || candidate.transient_next[i].oam_span>SPRITES) return 0;
    s=candidate; return 1;
}
NES_MOD_CONSTRUCTOR(register_enemies) {
    if (!nes_mod_register_function_entry_plugin("super-mario-bros.widescreen.enemy-init",0xc26c,spawn_hook) ||
        !nes_mod_register_function_entry_plugin("super-mario-bros.widescreen.enemy-gfx",0xe87d,gfx_hook) ||
        !nes_mod_register_function_entry_plugin("super-mario-bros.widescreen.enemy-cull",0xd67a,cull_hook) ||
        !nes_mod_register_function_entry_plugin("super-mario-bros.widescreen.score-gfx",0x8537,score_gfx_hook) ||
        !nes_mod_register_function_entry_plugin("super-mario-bros.widescreen.swim-birth",0xc6f5,swim_birth_hook) ||
        !nes_mod_register_function_entry_plugin("super-mario-bros.widescreen.transient-cull",0xd6a8,transient_cull_hook) ||
        !nes_mod_register_function_entry_plugin("super-mario-bros.widescreen.firebar-gfx",0xcd3c,firebar_hook) ||
        !nes_mod_register_function_entry_plugin("super-mario-bros.widescreen.sprite-clip",0xeb64,sprite_clip_hook) ||
        !nes_mod_register_function_entry_plugin("super-mario-bros.widescreen.flame-clip",0xd263,flame_clip_hook) ||
        !nes_mod_register_function_entry_plugin("super-mario-bros.widescreen.flag-gfx",0xe54b,flag_hook) ||
        !nes_mod_register_function_entry_plugin("super-mario-bros.widescreen.plant-init",0xc787,plant_hook) ||
        !nes_mod_register_function_entry_plugin("super-mario-bros.widescreen.large-platform-gfx",0xe5c8,gfx_hook) ||
        !nes_mod_register_function_entry_plugin("super-mario-bros.widescreen.small-platform-gfx",0xed66,gfx_hook) ||
        !nes_mod_register_savestate_hook("super-mario-bros.widescreen.actors",save,load))
        fprintf(stderr,"[Widescreen] Failed to register enemy residents\n");
}
