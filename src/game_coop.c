/* Native SMB co-op adapter. Addresses are extracted from the pinned assembly.
 * Each actor owns an explicit subset of guest RAM. The original GameCoreRoutine
 * still advances the world exactly once; hooks fan out only player work.
 */
#include "game_coop.h"
#include "coop/smb_symbols.h"
#include "nes_runtime.h"
#include "logical_input.h"
#include "mod_function_hooks.h"
#include "mod_savestate.h"
#include "mod_runtime.h"
#include "debug_server.h"
#include "config.h"
#include "nes_session_config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { ALIVE, DYING, OUT, MAX_PLAYERS=4, PIECES=20 };
typedef struct { uint16_t address, count; } Field;
#define FIELD(name,n) {S_##name,n}
static const Field fields[] = {
    FIELD(A_B_Buttons,5), FIELD(Player_State,1), FIELD(PlayerFacingDir,1),
    FIELD(Player_MovingDir,1), FIELD(Player_X_Speed,1), FIELD(Player_PageLoc,1),
    FIELD(Player_X_Position,1), FIELD(Player_Y_Speed,1), FIELD(Player_Y_HighPos,1),
    FIELD(Player_Y_Position,1), FIELD(Player_Rel_XPos,1), FIELD(Player_Rel_YPos,1),
    FIELD(Player_SprAttrib,1), FIELD(Player_OffscreenBits,1),
    FIELD(SprObject_X_MoveForce,1), FIELD(Player_YMF_Dummy,1), FIELD(Player_Y_MoveForce,1),
    FIELD(MaximumLeftSpeed,1), FIELD(MaximumRightSpeed,1), FIELD(StompChainCounter,1),
    FIELD(Player_CollisionBits,1), FIELD(Player_BoundBoxCtrl,1), FIELD(BoundingBox_UL_XPos,4),
    FIELD(PlayerGfxOffset,1), FIELD(SavedJoypadBits,1), FIELD(Player_X_Scroll,15),
    FIELD(FireballThrowingTimer,4), FIELD(DisableCollisionDet,1),
    FIELD(Platform_X_Scroll,1), FIELD(JumpspringAnimCtrl,1), FIELD(JumpspringForce,1), FIELD(JumpspringTimer,1),
    FIELD(Whirlpool_Flag,1),
    FIELD(PlayerSize,1), FIELD(Player_Pos_ForScroll,2),
    FIELD(PlayerAnimTimer,3), FIELD(SideCollisionTimer,1), FIELD(ClimbSideTimer,1),
    FIELD(StompTimer,2), FIELD(InjuryTimer,2),
    FIELD(Fireball_State,2), FIELD(FireballBouncingFlag,2), FIELD(FireballCounter,1),
    FIELD(Fireball_X_Speed,2), FIELD(Fireball_PageLoc,2), FIELD(Fireball_X_Position,2),
    FIELD(Fireball_Y_Speed,2), FIELD(Fireball_Y_HighPos,2), FIELD(Fireball_Y_Position,2),
    {S_SprObject_X_MoveForce+7,2}, {S_SprObject_YMF_Dummy+7,2},
    {S_SprObject_Y_MoveForce+7,2}, FIELD(Fireball_BoundBoxCtrl,2),
    {S_BoundingBox_UL_XPos+28,8}
};
#undef FIELD
typedef struct {
    uint8_t ram[0x800];
    uint8_t life, timer, contacts[6];
    uint8_t pieces[PIECES][4], visible[PIECES][4];
    uint8_t piece_count, visible_count;
} Actor;
typedef struct {
    Actor actor[MAX_PLAYERS];
    uint8_t ready, existed, active, transition, wipe, world, level, checkpoint, area;
    uint32_t frames, world_ticks;
    uint8_t input[MAX_PLAYERS];
} Session;
static Session s;
static int s_count, s_shared_pause, s_actor, s_world, s_routing, s_scrolling;
static int s_shared_frozen;
static uint8_t s_bypass[0x10000];
/* Frame-local native exits wait for collision/timeout resolution. Saves are
 * taken between frames, after these intents have been consumed. */
typedef struct { uint16_t address; CPU6502State cpu; uint8_t scratch[9]; } ExitIntent;
static ExitIntent s_exits[MAX_PLAYERS];
static int s_platform, s_platform_driver, s_riders[MAX_PLAYERS];
static int hook(uint16_t address);
static char hook_ids[48][48];
static const uint16_t hooks[] = {
    S_GameCoreRoutine, S_GameRoutines, S_ScrollHandler, S_PlayerGfxHandler,
    S_ProcFireball_Bubble, S_EnemiesAndLoopsCore, S_PlayerEnemyCollision,
    S_PlayerHammerCollision, S_FirebarCollision, S_ProcessWhirlpools,
    S_InitializeArea, S_GameMenuRoutine, S_DrawTitleScreen, S_RunGameTimer, S_KillPlayer,
    S_RunLargePlatform, S_RunSmallPlatform, S_LargePlatformCollision, S_SmallPlatformCollision,
    S_FlagpoleCollision, S_HandleAxeMetatile, S_HandlePipeEntry, S_PipeDwnS,
    S_VineCollision, S_CloudExit, S_VictoryMode, S_ExecGameLoopback,
    S_JumpspringHandler, S_ChkForLandJumpSpring, S_GetAreaMusic,
    S_BulletBillHandler, S_ProcLoopCommand
};

static void original(uint16_t address) {
    ++s_bypass[address];
    if (!call_by_address(address)) {
        fprintf(stderr,"[Co-op] Missing native entry %04x\n",address);
        abort();
    }
    --s_bypass[address];
}
static int xpos(const Actor *a) {
    return a->ram[S_Player_PageLoc]*256+a->ram[S_Player_X_Position];
}
static int camera(void) { return g_ram[S_ScreenLeft_PageLoc]*256+g_ram[S_ScreenLeft_X_Pos]; }
static int living(void) {
    int n=0; for (int i=0;i<s_count;++i) n+=s.actor[i].life==ALIVE; return n;
}
static int first_alive(void) {
    for(int i=0;i<s_count;++i) if(s.actor[i].life==ALIVE) return i;
    return 0;
}
static void capture(void) {
    Actor *a=&s.actor[s_actor];
    uint8_t old_sub=a->ram[S_GameEngineSubroutine];
    for(size_t i=0;i<sizeof fields/sizeof *fields;++i)
        memcpy(a->ram+fields[i].address,g_ram+fields[i].address,fields[i].count);
    if(!s_world || g_ram[S_TimerControl]!=(s_shared_frozen?1:0) || old_sub!=g_ram[S_GameEngineSubroutine])
        a->timer=g_ram[S_TimerControl];
}
static void bind(int index) {
    s_actor=index;
    const Actor *a=&s.actor[index];
    for(size_t i=0;i<sizeof fields/sizeof *fields;++i)
        memcpy(g_ram+fields[i].address,a->ram+fields[i].address,fields[i].count);
    g_ram[S_TimerControl]=s_world ? (s_shared_frozen ? 1:0) : a->timer;
    g_ram[S_CurrentPlayer]=0; /* Team score, coins and attempts use native P1. */
    g_ram[S_NumberOfPlayers]=0;
}
static void geometry(void) {
    CPU6502State cpu=g_cpu;
    uint8_t scratch[9]; memcpy(scratch,g_ram,sizeof scratch);
    original(S_GetPlayerOffscreenBits); original(S_RelativePlayerPosition);
    g_cpu.X=0; original(S_BoundingBoxCore);
    memcpy(g_ram,scratch,sizeof scratch); g_cpu=cpu;
}
static int nearest(int x,int y,int horizontal) {
    int best=first_alive(); int64_t distance=INT64_MAX;
    for(int i=0;i<s_count;++i) if(s.actor[i].life==ALIVE) {
        int64_t dx=xpos(&s.actor[i])-x;
        int64_t dy=(int)s.actor[i].ram[S_Player_Y_Position]+16-y;
        int64_t d=dx*dx+(horizontal?0:dy*dy);
        if(d<distance) { distance=d; best=i; }
    }
    return best;
}
static void dead(int i) {
    Actor *a=&s.actor[i];
    if(a->life!=ALIVE) return;
    a->life=DYING;
    a->ram[S_PlayerStatus]=0;
    a->ram[S_StarInvincibleTimer]=0;
    a->ram[S_InjuryTimer]=0;
    a->ram[S_Fireball_State]=a->ram[S_Fireball_State+1]=0;
}
static void inspect_actor(int i) {
    Actor *a=&s.actor[i];
    if(a->ram[S_GameEngineSubroutine]==11) dead(i);
    if(a->ram[S_Player_Y_HighPos]>=2 && a->ram[S_Player_Y_HighPos]<0x80 &&
       (!g_ram[S_CloudTypeOverride] || a->life==DYING)) {
        dead(i); a->life=OUT;
    }
    if(g_ram[S_EventMusicQueue]==1 && living()) g_ram[S_EventMusicQueue]=0;
}
static void initialize_actors(void) {
    Actor seed; memset(&seed,0,sizeof seed);
    memcpy(seed.ram,g_ram,sizeof seed.ram);
    int next_level=s.existed && (s.world!=g_ram[S_WorldNumber] || s.level!=g_ram[S_LevelNumber]);
    for(int i=0;i<s_count;++i) {
        uint8_t status=s.actor[i].ram[S_PlayerStatus], size=s.actor[i].ram[S_PlayerSize];
        uint8_t life=s.actor[i].life;
        s.actor[i]=seed;
        if(s.existed && !s.wipe && life==ALIVE) {
            s.actor[i].ram[S_PlayerStatus]=status;
            s.actor[i].ram[S_PlayerSize]=size;
        } else {
            s.actor[i].ram[S_PlayerStatus]=0; s.actor[i].ram[S_PlayerSize]=1;
        }
        s.actor[i].life=(!s.existed || s.wipe || next_level || life==ALIVE) ? ALIVE:OUT;
        int x=camera()+g_ram[S_Player_Rel_XPos];
        /* Initial spawn is shared; nearby offsets only on ordinary ground entry. */
        if(!g_ram[S_AltEntranceControl] && x-camera()>=24) x-=i*8;
        s.actor[i].ram[S_Player_X_Position]=(uint8_t)x;
        s.actor[i].ram[S_Player_PageLoc]=(uint8_t)(x>>8);
        s.actor[i].ram[S_Fireball_State]=s.actor[i].ram[S_Fireball_State+1]=0;
    }
    if(!s.existed || next_level) s.checkpoint=0;
    s.world=g_ram[S_WorldNumber]; s.level=g_ram[S_LevelNumber];
    s.ready=s.existed=1; s.transition=s.wipe=0; s.active=(uint8_t)first_alive();
    bind(s.active);
}
static void tick_actor(Actor *a) {
    if(a->timer) { --a->timer; if(a->timer) return; }
    const uint16_t timers[]={S_PlayerAnimTimer,S_JumpSwimTimer,S_RunningTimer,
        S_SideCollisionTimer,S_ClimbSideTimer,S_StompTimer,S_AirBubbleTimer,S_JumpspringTimer};
    for(size_t j=0;j<sizeof timers/sizeof *timers;++j) if(a->ram[timers[j]]) --a->ram[timers[j]];
    if(g_ram[S_IntervalTimerControl]==0x14) {
        if(a->ram[S_InjuryTimer]) --a->ram[S_InjuryTimer];
        if(a->ram[S_StarInvincibleTimer]) --a->ram[S_StarInvincibleTimer];
    }
}
static void scroll_party(void) {
    int front=first_alive(), rear=xpos(&s.actor[front]), left=camera();
    for(int i=0;i<s_count;++i) if(s.actor[i].life==ALIVE) {
        if(xpos(&s.actor[i])>xpos(&s.actor[front])) front=i;
        if(xpos(&s.actor[i])<rear) rear=xpos(&s.actor[i]);
    }
    bind(front); s_scrolling=1;
    /* Native camera acceleration/streaming remain authoritative. Clamp its
       proposed movement to the room remaining behind the trailing player. */
    int margin=rear-left;
    if(margin<0) margin=0;
    /* MovePlayerHoriz supplies a signed displacement. Clamping its unsigned
       byte would turn -1 into a large forward scroll, even with one survivor. */
    if((int8_t)g_ram[S_Player_X_Scroll]>margin) g_ram[S_Player_X_Scroll]=(uint8_t)margin;
    /* Platform displacement was applied once during the preceding world tick. */
    g_ram[S_Platform_X_Scroll]=0;
    original(S_ScrollHandler);
    s_scrolling=0; capture();
    left=camera();
    for(int i=0;i<s_count;++i) if(s.actor[i].life==ALIVE) {
        Actor *a=&s.actor[i]; int x=xpos(a), clipped=x;
        if(clipped<left) clipped=left;
        if(clipped>left+240) clipped=left+240;
        if(clipped!=x) { a->ram[S_Player_X_Position]=(uint8_t)clipped;
            a->ram[S_Player_PageLoc]=(uint8_t)(clipped>>8); a->ram[S_Player_X_Speed]=0; }
    }
    bind(s.active); geometry(); capture();
}
static int star_music(void) {
    for(int i=0;i<s_count;++i) if(s.actor[i].life==ALIVE && s.actor[i].ram[S_StarInvincibleTimer]>4) return 1;
    return 0;
}
static void stage_party(void) {
    const Actor *lead=&s.actor[s.active];
    int rank=0, routine=lead->ram[S_GameEngineSubroutine];
    const uint16_t pose[]={S_Player_Y_Position,S_Player_Y_HighPos,S_Player_State,
        S_PlayerFacingDir,S_Player_MovingDir,S_Player_X_Speed,S_Player_Y_Speed,
        S_Player_SprAttrib,S_PlayerAnimCtrl,S_PlayerAnimTimer,S_PlayerGfxOffset};
    for(int i=0;i<s_count;++i) if(i!=s.active && s.actor[i].life==ALIVE) {
        Actor *a=&s.actor[i]; ++rank;
        for(size_t j=0;j<sizeof pose/sizeof *pose;++j) a->ram[pose[j]]=lead->ram[pose[j]];
        int x=xpos(lead);
        if(routine==4 || routine==5 || g_ram[S_OperMode]==2 || routine==2) x-=rank*12;
        if(x<camera()) x=camera();
        a->ram[S_Player_X_Position]=(uint8_t)x;a->ram[S_Player_PageLoc]=(uint8_t)(x>>8);
        a->ram[S_GameEngineSubroutine]=(uint8_t)routine;
        a->ram[S_PlayerSize]=a->ram[S_PlayerStatus]?0:1;
        a->ram[S_PlayerChangeSizeFlag]=0;a->ram[S_InjuryTimer]=0;a->timer=0;
        a->ram[S_Fireball_State]=a->ram[S_Fireball_State+1]=0;
    }
}
static void accept_exit(void) {
    CPU6502State cpu=g_cpu;
    uint8_t scratch[9];memcpy(scratch,g_ram,9);
    for(int i=0;i<s_count;++i) if(s_exits[i].address && s.actor[i].life==ALIVE) {
        bind(i);g_cpu=s_exits[i].cpu;memcpy(g_ram,s_exits[i].scratch,9);
        original(s_exits[i].address);capture();
        if(g_ram[S_GameEngineSubroutine]<6 || g_ram[S_OperMode]!=1 || g_ram[S_OperMode_Task]!=3) {
            s.transition=1;s.active=(uint8_t)i;
            s.actor[i].timer=0;s.actor[i].ram[S_PlayerChangeSizeFlag]=0;
            s.actor[i].ram[S_PlayerSize]=s.actor[i].ram[S_PlayerStatus]?0:1;
            stage_party();break;
        }
    }
    bind(s.active);g_cpu=cpu;memcpy(g_ram,scratch,9);
}
static void track_checkpoint(void) {
    if(g_ram[S_CloudTypeOverride] || g_ram[S_AltEntranceControl] ||
       g_ram[S_WorldNumber]>=8 || g_ram[S_LevelNumber]>=4) return;
    uint8_t main_area=nes_read(S_AreaAddrOffsets+nes_read(S_WorldAddrOffsets+g_ram[S_WorldNumber])+g_ram[S_AreaNumber]);
    if((main_area&0x7f)!=(s.area&0x7f)) return;
    /* Same native per-level table; any living player can establish it. Bonus
       rooms cannot establish a checkpoint in the main level's coordinates. */
    uint8_t packed=nes_read(S_HalfwayPageNybbles+g_ram[S_WorldNumber]*2+(g_ram[S_LevelNumber]>>1));
    uint8_t page=(g_ram[S_LevelNumber]&1)?packed&15:packed>>4;
    for(int i=0;i<s_count;++i) if(s.actor[i].life==ALIVE && s.actor[i].ram[S_Player_PageLoc]>=page)
        s.checkpoint=page;
}
static void run_players(void) {
    if(s.wipe) { s_shared_frozen=1; return; }
    if(s.transition) {
        tick_actor(&s.actor[s.active]); bind(s.active);
        original(S_GameRoutines); capture(); stage_party(); return;
    }
    s_shared_frozen=0;
    if(s_shared_pause) for(int i=0;i<s_count;++i)
        if(s.actor[i].life==ALIVE && s.actor[i].timer) s_shared_frozen=1;
    CPU6502State cpu=g_cpu;
    for(int i=0;i<s_count;++i) {
        Actor *a=&s.actor[i]; a->piece_count=0;
        if(a->life==OUT) continue;
        if(s_shared_frozen && !a->timer && a->life==ALIVE) continue;
        tick_actor(a); bind(i); g_cpu=cpu;
        g_ram[S_SavedJoypadBits]=nes_input_seat(i+1)&0xcf;
        uint8_t scroll_lock=g_ram[S_ScrollLock];
        original(S_GameRoutines); capture(); inspect_actor(i);
        if(a->life!=ALIVE || g_ram[S_CloudTypeOverride]) g_ram[S_ScrollLock]=scroll_lock;
    }
    s.active=(uint8_t)first_alive();
    if(!s.transition && living() && !s_shared_frozen) scroll_party();
    bind(s.active); g_cpu=cpu;
}
static void collision_all(uint16_t address) {
    int owner=s_actor; capture();
    CPU6502State cpu=g_cpu, result=cpu;
    uint8_t scratch[9]; memcpy(scratch,g_ram,sizeof scratch);
    int slot=g_ram[S_ObjectOffset];
    uint8_t original_bits=slot<6?g_ram[S_Enemy_CollisionBits+slot]:0;
    uint8_t sprite_x=g_ram[S_Sprite_X_Position+4];
    uint8_t hammer_contact=slot<9?g_ram[S_Misc_Collision_Flag+slot]:0;
    if(address==S_FirebarCollision) {
        /* This native routine also draws one segment and advances OAM Y.
           Preserve that return even when all nearby actors are frozen/out. */
        uint8_t timer=g_ram[S_TimerControl];g_ram[S_TimerControl]=1;
        original(address);result=g_cpu;g_cpu=cpu;
        g_ram[S_TimerControl]=timer;memcpy(g_ram,scratch,sizeof scratch);
    }
    for(int i=0;i<s_count;++i) {
        Actor *a=&s.actor[i];
        if(a->life!=ALIVE || a->timer || s.transition) continue;
        bind(i); geometry(); memcpy(g_ram,scratch,sizeof scratch); g_cpu=cpu;
        /* FirebarCollision reads sprite 1's X instead of the player bbox.
           The native player sprites are hidden/recolored by this adapter. */
        if(address==S_FirebarCollision) g_ram[S_Sprite_X_Position+4]=(uint8_t)(g_ram[S_Player_Rel_XPos]+8);
        if(address==S_PlayerHammerCollision && slot<9) g_ram[S_Misc_Collision_Flag+slot]=hammer_contact;
        if(address==S_PlayerEnemyCollision && slot<6)
            g_ram[S_Enemy_CollisionBits+slot]=(original_bits&0xfe)|a->contacts[slot];
        uint8_t state=slot<6?g_ram[S_Enemy_State+slot]:0;
        uint8_t kind=slot<6?g_ram[S_Enemy_ID+slot]:0;
        original(address);
        if(address==S_PlayerEnemyCollision && slot<6)
            a->contacts[slot]=g_ram[S_Enemy_CollisionBits+slot]&1;
        capture(); inspect_actor(i);
        if(i==owner && address!=S_FirebarCollision) result=g_cpu;
        /* One collectible, stomp, or shell kick is resolved once in port
           order. A moving shell can still injure multiple teammates. */
        if(address==S_PlayerEnemyCollision && slot<6 &&
            (!g_ram[S_Enemy_Flag+slot] || g_ram[S_Enemy_State+slot]!=state || g_ram[S_Enemy_ID+slot]!=kind)) break;
        /* A hammer reverses on contact once. First touching port owns that
           native interaction, including a star deflection. */
        if(address==S_PlayerHammerCollision && slot<9 && g_ram[S_Misc_Collision_Flag+slot]) break;
    }
    g_ram[S_Sprite_X_Position+4]=sprite_x;
    if(slot<6) g_ram[S_Enemy_CollisionBits+slot]=original_bits;
    bind(owner); geometry(); memcpy(g_ram,scratch,sizeof scratch); g_cpu=result;
}
static void platform_collisions(uint16_t address) {
    int owner=s_actor,slot=g_ram[S_ObjectOffset],small=address==S_SmallPlatformCollision;
    capture();CPU6502State cpu=g_cpu;
    uint8_t scratch[9],boxes[24];memcpy(scratch,g_ram,9);
    memcpy(boxes,g_ram+S_BoundingBox_UL_XPos+4,sizeof boxes);
    s_platform_driver=-1;
    for(int i=0;i<s_count;++i) {
        s_riders[i]=-1;
        if(s.actor[i].life!=ALIVE || s.actor[i].timer || s.transition || s_shared_frozen) continue;
        bind(i);geometry();g_cpu=cpu;memcpy(g_ram,scratch,9);
        memcpy(g_ram+S_BoundingBox_UL_XPos+4,boxes,sizeof boxes);
        original(address);capture();
        int flag=g_ram[S_PlatformCollisionFlag+slot];
        if((small && flag>0 && flag<=2) || (!small && flag<6)) {
            s_riders[i]=flag;
            if(s_platform_driver<0) s_platform_driver=i;
        }
    }
    int driver=s_platform_driver<0?owner:s_platform_driver;
    bind(driver);geometry();g_cpu=cpu;g_cpu.X=(uint8_t)slot;
    memcpy(g_ram,scratch,9);memcpy(g_ram+S_BoundingBox_UL_XPos+4,boxes,sizeof boxes);
    g_ram[S_PlatformCollisionFlag+slot]=s_platform_driver<0?(small?0:255):(uint8_t)s_riders[driver];
}
static void run_platform(uint16_t address) {
    int owner=s_actor,slot=g_ram[S_ObjectOffset];
    int oldx=g_ram[S_Enemy_PageLoc+slot]*256+g_ram[S_Enemy_X_Position+slot];
    int kind=g_ram[S_Enemy_ID+slot];
    s_platform=1; s_platform_driver=-1;
    original(address);capture();
    s_platform=0;
    CPU6502State cpu=g_cpu;uint8_t scratch[9];memcpy(scratch,g_ram,9);
    int dx=g_ram[S_Enemy_PageLoc+slot]*256+g_ram[S_Enemy_X_Position+slot]-oldx;
    if(!s_shared_frozen && !s.transition) for(int i=0;i<s_count;++i) {
        if(i==s_platform_driver || s_riders[i]<0) continue;
        bind(i);
        if(address==S_RunSmallPlatform) {
            g_cpu.X=(uint8_t)slot;g_cpu.A=(uint8_t)s_riders[i];original(S_PositionPlayerOnS_Plat);
        } else {
            g_cpu.X=(uint8_t)s_riders[i];
            if(kind==0x28 || kind==0x2a) { g_ram[0]=(uint8_t)dx;original(S_PositionPlayerOnHPlat); }
            else original(S_PositionPlayerOnVPlat);
        }
        capture();
    }
    bind(owner);geometry();g_cpu=cpu;memcpy(g_ram,scratch,9);
}
static void add_pieces(Actor *a,int offset,int count,int projectile) {
    for(int j=0;j<count && a->piece_count<PIECES;++j) {
        int k=(offset+4*j)&255;
        if(g_ram[S_Sprite_Data+k]>=0xf0) continue;
        uint8_t *piece=a->pieces[a->piece_count++];
        memcpy(piece,g_ram+S_Sprite_Data+k,4);
        /* OAM attribute bit 2 is unused by the NES. In our private copy it
           marks projectiles without guessing from overlapping tile IDs. */
        if(projectile) piece[2]|=4;
    }
}
static void graphics_all(void) {
    int owner=s_actor; capture(); CPU6502State cpu=g_cpu;
    uint8_t oam[256]; memcpy(oam,g_ram+S_Sprite_Data,256);
    for(int i=0;i<s_count;++i) {
        if(s.actor[i].life==OUT) continue;
        bind(i); geometry();
        int offset=g_ram[S_Player_SprDataOffset];
        for(int j=0;j<8;++j) g_ram[S_Sprite_Data+((offset+j*4)&255)]=0xf8;
        g_cpu=cpu; original(S_PlayerGfxHandler); capture();
        add_pieces(&s.actor[i],offset,8,0);
        memcpy(g_ram+S_Sprite_Data,oam,256);
    }
    bind(owner); g_cpu=cpu;
    for(int j=0;j<8;++j) g_ram[S_Sprite_Data+((g_ram[S_Player_SprDataOffset]+j*4)&255)]=0xf8;
}
static void fireballs_all(void) {
    int owner=s_actor; capture(); CPU6502State cpu=g_cpu;
    uint8_t oam[256]; memcpy(oam,g_ram+S_Sprite_Data,256);
    for(int i=0;i<s_count;++i) {
        if(s.actor[i].life!=ALIVE) continue;
        bind(i); g_cpu=cpu;
        if(s.actor[i].timer || s.transition || s_shared_frozen) g_ram[S_A_B_Buttons]&=~0x40;
        /* Native bubble routine is shared; it is dispatched once below. */
        uint8_t area=g_ram[S_AreaType]; g_ram[S_AreaType]=1;
        if(!s_shared_frozen && !s.transition) original(S_ProcFireball_Bubble);
        g_ram[S_AreaType]=area;
        for(int j=0;j<2;++j) if(g_ram[S_Fireball_State+j]) {
            int offset=g_ram[(g_ram[S_Fireball_State+j]&0x80)?S_Alt_SprDataOffset+j:S_FBall_SprDataOffset+j];
            add_pieces(&s.actor[i],offset,(g_ram[S_Fireball_State+j]&0x80)?4:1,1);
        }
        capture(); memcpy(g_ram+S_Sprite_Data,oam,256);
    }
    bind(owner); g_cpu=cpu;
    original(S_ProcAirBubbles);
}
static int hook(uint16_t address) {
    if(!s_count || s_bypass[address]) return 0;
    if(address==S_DrawTitleScreen) {
        original(address);
        if(g_ram[S_OperMode]==0) {
            /* DrawTitleScreen copies the native CHR title transfer stream to
               $0300-$0439. Change its two menu records before the next NMI
               uploads them. The native mushroom at $2249 is left intact,
               and these tiles persist throughout the Start transition. */
            for(int p=0x300;p+3<=0x43a && g_ram[p];) {
                int dest=g_ram[p]*256+g_ram[p+1], control=g_ram[p+2];
                int size=(control&0x40)?1:(control&0x3f);
                p+=3;
                if(p+size>0x43a) break;
                if(control==13 && (dest==0x224b || dest==0x228b)) {
                    memset(g_ram+p,0x24,13);
                    if(dest==0x224b) {
                        const char *label="CO-OP PLAY";
                        for(int j=0;label[j];++j)
                            g_ram[p+j]=(uint8_t)(label[j]==' '?0x24:label[j]=='-'?0x28:label[j]-'A'+10);
                    }
                }
                p+=size;
            }
        }
        return 1;
    }
    if(address==S_GameMenuRoutine) {
        g_ram[S_NumberOfPlayers]=0;
        g_ram[S_SavedJoypadBits]&=~0x20;
        g_ram[S_SavedJoypad2Bits]=0;
        original(address); g_ram[S_NumberOfPlayers]=0;
        if(g_ram[S_OperMode]==1) { memset(&s,0,sizeof s); g_ram[S_NumberofLives]=2; }
        return 1;
    }
    if(address==S_InitializeArea) { s.ready=0; s.area=g_ram[S_AreaPointer]; return 0; }
    if(address==S_VictoryMode && s.ready) {
        tick_actor(&s.actor[s.active]);
        bind(s.active);s_routing=1;s_world=1;
        for(int i=0;i<s_count;++i) s.actor[i].piece_count=0;
        original(address);capture();stage_party();
        s_routing=s_world=0;return 1;
    }
    if(address==S_GameCoreRoutine) {
        if(g_ram[S_OperMode]!=1) return 0;
        ++s.frames;
        if(!s.ready) {
            original(address);
            if(g_ram[S_GameEngineSubroutine]==8 && g_ram[S_OperMode_Task]==3) initialize_actors();
            return 1;
        }
        memset(s_exits,0,sizeof s_exits);
        for(int i=0;i<s_count;++i) s.actor[i].piece_count=0;
        int had_star_music=star_music();
        bind(s.active); s_routing=1;
        original(address); capture();
        s_routing=0; s_world=0;
        if(!s.transition) accept_exit();
        if(!s.transition) track_checkpoint();
        if(had_star_music && !star_music() && !s.transition && living()) original(S_GetAreaMusic);
        ++s.world_ticks;
        if(!living() && !s.transition) {
            if(!s.wipe) { s.wipe=1; g_ram[S_EventMusicQueue]=1; }
            else if(s.wipe<100) ++s.wipe;
            else {
                g_ram[S_PlayerStatus]=0; g_ram[S_PlayerSize]=1;
                /* PlayerLoseLife derives HalfwayPage from ScreenLeft_PageLoc.
                   Supply the team's established page just for that native
                   decision; InitializeArea rebuilds the camera on retry. */
                g_ram[S_ScreenLeft_PageLoc]=s.checkpoint;
                original(S_PlayerLoseLife); s.ready=0;
            }
        }
        for(int i=0;i<s_count;++i) s.actor[i].ram[S_PreviousA_B_Buttons]=s.actor[i].ram[S_A_B_Buttons];
        if(!s.transition && living()) s.active=(uint8_t)first_alive();
        bind(s.active);
        /* Native NMI decrements world timers once. Private timers tick in
           run_players, so their copies in RAM are overwritten on binding. */
        g_ram[S_TimerControl]=s_shared_frozen?1:0;
        return 1;
    }
    if(!s.ready || !s_routing) return 0;
    if(address==S_GetAreaMusic && s_world && !s.transition && star_music()) return 1;
    if(!s.transition && !s_world && (address==S_FlagpoleCollision || address==S_HandleAxeMetatile ||
        address==S_PipeDwnS || address==S_CloudExit ||
        (address==S_HandlePipeEntry && (g_ram[S_Up_Down_Buttons]&4) && g_ram[0]==0x11 && g_ram[1]==0x10) ||
        (address==S_VineCollision && g_cpu.A==0x26 && g_ram[S_Player_Y_Position]<0x20))) {
        ExitIntent *e=&s_exits[s_actor];
        if(!e->address) { e->address=address;e->cpu=g_cpu;memcpy(e->scratch,g_ram,9); }
        return 1;
    }
    if(address==S_GameRoutines) {
        run_players(); s_world=1; g_ram[S_TimerControl]=s_shared_frozen?1:0; return 1;
    }
    if(address==S_ScrollHandler && !s_scrolling && !s.transition) return 1;
    if(address==S_PlayerGfxHandler) { graphics_all(); return 1; }
    if(address==S_ProcFireball_Bubble) { fireballs_all(); return 1; }
    if(address==S_EnemiesAndLoopsCore) {
        int owner=s_actor, slot=g_cpu.X; capture();
        int target=slot<6 ? nearest(g_ram[S_Enemy_PageLoc+slot]*256+g_ram[S_Enemy_X_Position+slot],g_ram[S_Enemy_Y_Position+slot],g_ram[S_Enemy_ID+slot]==S_PiranhaPlant):owner;
        if(s.transition) target=s.active;
        bind(target); geometry(); original(address); capture(); inspect_actor(target);
        bind(owner); geometry(); return 1;
    }
    if(address==S_RunLargePlatform || address==S_RunSmallPlatform) { run_platform(address);return 1; }
    if(address==S_BulletBillHandler) {
        int owner=s_actor,slot=g_cpu.X;capture();
        if(slot<6 && !s.transition) bind(nearest(g_ram[S_Enemy_PageLoc+slot]*256+g_ram[S_Enemy_X_Position+slot],g_ram[S_Enemy_Y_Position+slot],0));
        geometry();original(address);capture();bind(owner);geometry();return 1;
    }
    if(address==S_ProcLoopCommand && g_ram[S_LoopCommand] && !g_ram[S_CurrentColumnPos]) {
        int owner=s_actor;capture();
        for(int j=10;j>=0;--j) if(nes_read(S_LoopCmdWorldNumber+j)==g_ram[S_WorldNumber] &&
            nes_read(S_LoopCmdPageNumber+j)==g_ram[S_CurrentPageLoc]) {
            for(int i=0;i<s_count;++i) if(s.actor[i].life==ALIVE && !s.actor[i].ram[S_Player_State] &&
                s.actor[i].ram[S_Player_Y_Position]==nes_read(S_LoopCmdYPosition+j)) { bind(i);break; }
            break;
        }
        original(address);capture();bind(owner);geometry();return 1;
    }
    if(s_platform && (address==S_LargePlatformCollision || address==S_SmallPlatformCollision)) {
        platform_collisions(address);return 1;
    }
    if(address==S_ExecGameLoopback) {
        int owner=s_actor;capture();original(address);capture();
        for(int i=0;i<s_count;++i) if(i!=owner) s.actor[i].ram[S_Player_PageLoc]-=4;
        return 1;
    }
    if(address==S_ChkForLandJumpSpring) {
        /* One native spring animation; first contacting port owns its jump. */
        for(int i=0;i<s_count;++i) if(i!=s_actor && s.actor[i].ram[S_JumpspringAnimCtrl]) return 1;
        return 0;
    }
    if(address==S_JumpspringHandler) {
        int owner=s_actor;capture();
        for(int i=0;i<s_count;++i) if(s.actor[i].life==ALIVE && s.actor[i].ram[S_JumpspringAnimCtrl]) { bind(i);break; }
        original(address);capture();bind(owner);return 1;
    }
    if(address==S_PlayerEnemyCollision || address==S_PlayerHammerCollision || address==S_FirebarCollision) {
        collision_all(address); return 1;
    }
    if(address==S_ProcessWhirlpools) { collision_all(address); return 1; }
    if(address==S_RunGameTimer) {
        int owner=s_actor;capture();
        if(!s.transition && living()) bind(first_alive());
        original(address);capture();
        if(g_ram[S_GameTimerExpiredFlag]) {
            for(int i=0;i<s_count;++i) { dead(i); s.actor[i].life=OUT; }
        }
        bind(owner);
        return 1;
    }
    if(address==S_KillPlayer && s.transition) return 1;
    return 0;
}

void game_coop_configure(int players,int shared_pause) {
    s_count=players>=2 && players<=4?players:0;
    /* Co-op is online-capable: a netplay match runs the HOST's co-op mode on
     * every peer through the session configuration seal below, and every
     * seat's input comes from the published rows (docs/NETPLAY.md). */
    s_shared_pause=shared_pause!=0;
    memset(&s,0,sizeof s); s_actor=s_world=s_routing=s_scrolling=s_shared_frozen=0;
    for(size_t i=0;i<sizeof hooks/sizeof *hooks;++i) {
        char id[48]; snprintf(id,sizeof id,"smb.coop.%04x",hooks[i]);
        nes_mod_set_function_hook_enabled(id,s_count!=0);
    }
    if(s_count) g_nes_config.widescreen=0;
}
int game_coop_enabled(void) { return s_count!=0; }
void game_coop_before_frame(void) {
    if(!s_count) return;
    for(int i=0;i<s_count;++i) {
        Actor *a=&s.actor[i];
        a->visible_count=a->piece_count;
        memcpy(a->visible,a->pieces,sizeof a->visible);
    }
}
int game_coop_suppress_sprite(int slot) {
    if(!s_count || !s.ready) return 0;
    int offset=g_ram[S_Player_SprDataOffset]/4;
    return slot>=offset && slot<offset+8;
}

static const uint8_t palettes[4][3]={{0x16,0x27,0x18},{0x30,0x27,0x19},{0x28,0x27,0x14},{0x14,0x27,0x04}};
static void text_at(uint32_t *fb,int x,int y,const char *text,uint32_t color) {
    for(;*text;++text,x+=8) {
        int tile=*text>='0'&&*text<='9'?*text-'0':*text>='A'&&*text<='Z'?*text-'A'+10:*text=='-'?0x28:0x24;
        for(int yy=0;yy<8;++yy) {
            uint8_t bits=g_chr_ram[0x1000+tile*16+yy]|g_chr_ram[0x1000+tile*16+yy+8];
            for(int xx=0;xx<8;++xx) if((bits&(0x80>>xx)) && x+xx>=0 && x+xx<256 && y+yy>=0 && y+yy<240)
                fb[(y+yy)*g_render_width+x+xx]=color;
        }
    }
}
void game_coop_render(uint32_t *fb) {
    if(!s_count || g_render_width!=256) return;
    if(g_ram[S_OperMode]==0) return;
    if(!s.ready) return;
    uint32_t background=g_nes_palette[g_ppu_pal[0]&63];
    for(int y=16;y<24;++y) for(int x=24;x<64;++x) fb[y*256+x]=background;
    text_at(fb,24,16,"TEAM",g_nes_palette[0x30]);
    char lives[8];snprintf(lives,sizeof lives,"L%u",(unsigned)((g_ram[S_NumberofLives]+1)&255));
    text_at(fb,96,16,lives,g_nes_palette[0x30]);
    for(int i=s_count-1;i>=0;--i) {
        const Actor *a=&s.actor[i];
        for(int j=0;j<a->visible_count;++j) {
            const uint8_t *o=a->visible[j]; int y=o[0]+1,x=o[3];
            int projectile=(o[2]&4)!=0;
            for(int yy=0;yy<8;++yy) {
                int row=(o[2]&0x80)?7-yy:yy;
                uint8_t lo=g_chr_ram[o[1]*16+row],hi=g_chr_ram[o[1]*16+row+8];
                for(int xx=0;xx<8;++xx) {
                    int bit=(o[2]&0x40)?xx:7-xx;
                    int pixel=((lo>>bit)&1)|(((hi>>bit)&1)<<1);
                    int px=x+xx,py=y+yy;
                    if(!pixel || px>=256 || py>=240 || py<32) continue;
                    if((o[2]&0x20) && ppu_renderer_background_opaque(px,py)) continue;
                    uint8_t color=projectile?g_ppu_pal[0x10+(o[2]&3)*4+pixel]:palettes[i][pixel-1];
                    if(!projectile && a->ram[S_PlayerStatus]==2 && pixel==1) color=0x30;
                    if(!projectile && a->ram[S_StarInvincibleTimer]) color=(uint8_t)((color+(g_ram[S_FrameCounter]/4)%4*0x10)&63);
                    uint32_t rgb=g_nes_palette[color&63];
                    /* NES $28 is olive in the stock display palette. These
                       host-drawn sprites can use Wario's warm yellow directly;
                       keep the native fire/star color changes above. */
                    if(!projectile && i==2 && pixel==1 && a->ram[S_PlayerStatus]!=2 && !a->ram[S_StarInvincibleTimer])
                        rgb=0xffffd43b;
                    fb[py*256+px]=rgb;
                }
            }
        }
    }
}

/* Fixed-width records, no pointers/padding. All multibyte values are LE. */
static void put32(uint8_t **p,uint32_t n) { for(int j=0;j<4;++j) *(*p)++=(uint8_t)(n>>(j*8)); }
static uint32_t get32(const uint8_t **p) { uint32_t n=0;for(int j=0;j<4;++j)n|=(uint32_t)*(*p)++<<(j*8);return n; }
static int save(uint8_t *buf,int cap) {
    const int size=28+MAX_PLAYERS*(0x800+10+PIECES*8);
    if(cap<size) return -1;
    uint8_t *p=buf; memcpy(p,"SMBC",4); p+=4;
    *p++=2; *p++=(uint8_t)s_count; *p++=(uint8_t)s_shared_pause; *p++=s.ready;
    *p++=s.existed; *p++=s.active; *p++=s.transition; *p++=s.wipe;
    *p++=s.world; *p++=s.level; *p++=s.checkpoint; *p++=s.area;
    put32(&p,s.frames); put32(&p,s.world_ticks);
    for(int i=0;i<MAX_PLAYERS;++i) *p++=nes_input_seat(i+1);
    for(int i=0;i<MAX_PLAYERS;++i) {
        const Actor *a=&s.actor[i]; memcpy(p,a->ram,0x800);p+=0x800;
        *p++=a->life; *p++=a->timer; memcpy(p,a->contacts,6);p+=6;
        *p++=a->piece_count;*p++=a->visible_count;
        memcpy(p,a->pieces,PIECES*4);p+=PIECES*4;
        memcpy(p,a->visible,PIECES*4);p+=PIECES*4;
    }
    return (int)(p-buf);
}
static int decode(const uint8_t *buf,int len,int commit) {
    if(!buf || !len) return !s_count;
    if(len!=28+MAX_PLAYERS*(0x800+10+PIECES*8) || memcmp(buf,"SMBC",4) || buf[4]!=2 || buf[5]!=s_count || buf[6]!=s_shared_pause) return 0;
    Session candidate={0}; const uint8_t *p=buf+7;
    candidate.ready=*p++;candidate.existed=*p++;candidate.active=*p++;
    candidate.transition=*p++;candidate.wipe=*p++;candidate.world=*p++;candidate.level=*p++;candidate.checkpoint=*p++;candidate.area=*p++;
    candidate.frames=get32(&p);candidate.world_ticks=get32(&p);
    memcpy(candidate.input,p,MAX_PLAYERS);p+=MAX_PLAYERS;
    if(candidate.active>=MAX_PLAYERS || (candidate.ready && candidate.active>=s_count) ||
       candidate.ready>1 || candidate.existed>1 || candidate.transition>1 || candidate.wipe>100 ||
       candidate.world>=8 || candidate.level>=4 || candidate.checkpoint>15 || candidate.world_ticks>candidate.frames) return 0;
    for(int i=0;i<MAX_PLAYERS;++i) {
        Actor *a=&candidate.actor[i];memcpy(a->ram,p,0x800);p+=0x800;
        a->life=*p++;a->timer=*p++;memcpy(a->contacts,p,6);p+=6;
        a->piece_count=*p++;a->visible_count=*p++;
        if(a->life>OUT || a->piece_count>PIECES || a->visible_count>PIECES ||
           a->ram[S_GameEngineSubroutine]>12 || a->ram[S_PlayerStatus]>2 || a->ram[S_PlayerSize]>1) return 0;
        for(int j=0;j<6;++j) if(a->contacts[j]>1) return 0;
        memcpy(a->pieces,p,PIECES*4);p+=PIECES*4;memcpy(a->visible,p,PIECES*4);p+=PIECES*4;
    }
    if(commit) {
        s=candidate;s_actor=s.active;s_world=s_routing=s_scrolling=s_shared_frozen=0;
        if(s_count) for(int i=2;i<MAX_PLAYERS;++i) g_logical_input[i]=s.input[i];
    }
    return 1;
}
static int load(const uint8_t *buf,int len) { return decode(buf,len,1); }
static int validate(const uint8_t *buf,int len) { return decode(buf,len,0); }
/* Session configuration key "coop" = "<players 0|2..4>:<player|shared>".
 * A netplay launch applies the host's value before boot; the offline mode is
 * rebuilt by the mod runtime's next ordinary commit (reset_coop, then the
 * activation plugin), so restore only has to switch the session's off. */
static int coop_session_get(char *out,int cap) {
    return snprintf(out,(size_t)cap,"%d:%s",s_count,s_shared_pause?"shared":"player");
}
static int coop_session_apply(const char *v) {
    int n=-1; char pause[16]="";
    if(!v || sscanf(v,"%d:%15s",&n,pause)!=2) return 0;
    if(n!=0 && (n<2 || n>MAX_PLAYERS)) return 0;
    if(strcmp(pause,"player") && strcmp(pause,"shared")) return 0;
    game_coop_configure(n,!strcmp(pause,"shared"));
    return 1;
}
static void coop_session_restore(void) { game_coop_configure(0,0); }
/* The host's offer: the player's OFFLINE selection of the co-op feature (a
 * match commits no mods, so the activated state says nothing). */
static int coop_session_offer(char *out,int cap) {
    const char *package="super-mario-bros.gameplay.simultaneous-coop";
    char count[16]="2", pause[16]="player";
    if(!nes_mod_feature_selected(package,"coop")) return snprintf(out,(size_t)cap,"0:player");
    nes_mod_option_value(package,"coop","players",count,sizeof count);
    nes_mod_option_value(package,"coop","pause",pause,sizeof pause);
    return snprintf(out,(size_t)cap,"%d:%s",atoi(count),strcmp(pause,"shared")?"player":"shared");
}
/* The package excludes widescreen: whatever the text said, co-op wins. */
static void coop_session_finalize(void) { if(s_count) g_nes_config.widescreen=0; }

int game_coop_register(void) {
    int ok=nes_mod_register_savestate_hook("smb.coop",save,load);
    ok&=nes_netplay_session_register("coop",coop_session_get,coop_session_apply,coop_session_restore);
    ok&=nes_netplay_session_set_offer("coop",coop_session_offer);
    nes_netplay_session_set_finalize(coop_session_finalize);
    ok&=nes_mod_register_savestate_validator("smb.coop",validate);
    for(size_t i=0;i<sizeof hooks/sizeof *hooks;++i) {
        snprintf(hook_ids[i],sizeof hook_ids[i],"smb.coop.%04x",hooks[i]);
        ok&=nes_mod_register_function_entry_plugin(hook_ids[i],hooks[i],hook);
    }
    return ok;
}
int game_coop_arg(const char *key,const char *value) {
#if NESRECOMP_TRACE
    if(!strcmp(key,"--coop-pause")) {
        game_coop_configure(s_count,value && !strcmp(value,"shared"));return 1;
    }
    if(strcmp(key,"--coop")) return 0;
    game_coop_configure(value?atoi(value):2,0); return 1;
#else
    (void)key;(void)value;return 0;
#endif
}
int game_coop_debug(const char *command,int id,const char *json) {
    (void)json;
    if(strcmp(command,"coop_state")) return 0;
    char actors[1536]="";size_t used=0;
    for(int i=0;i<s_count;++i) {
        const Actor *a=&s.actor[i];
        used+=(size_t)snprintf(actors+used,sizeof actors-used,"%s{\"port\":%d,\"x\":%d,\"y\":%d,\"life\":%d,\"power\":%d,\"routine\":%d,\"timer\":%d,\"fireballs\":%d,\"pieces\":%d}",i?",":"",i+1,xpos(a),a->ram[S_Player_Y_HighPos]*256+a->ram[S_Player_Y_Position],a->life,a->ram[S_PlayerStatus],a->ram[S_GameEngineSubroutine],a->timer,(a->ram[S_Fireball_State]!=0)+(a->ram[S_Fireball_State+1]!=0),a->visible_count);
    }
    debug_server_send_fmt("{\"id\":%d,\"cmd\":\"coop_state\",\"players\":%d,\"ready\":%d,\"transition\":%d,\"wipe\":%d,\"frames\":%u,\"world_ticks\":%u,\"camera\":%d,\"actors\":[%s]}\n",id,s_count,s.ready,s.transition,s.wipe,s.frames,s.world_ticks,camera(),actors);
    return 1;
}
