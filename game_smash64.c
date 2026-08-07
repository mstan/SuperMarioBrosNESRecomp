/*
 * game_smash64.c -- SMB1 host adapter for the Smash 64 player replacement mod.
 *
 * Answers "where is the player allowed to go" and owns everything the fighter
 * controller must not see: NES RAM layout, SMB1's fixed-point velocity
 * representation, and its scripted player states.
 *
 * M2 SCOPE: horizontal ground movement only. SMB1 keeps its jump, gravity,
 * vertical collision, horizontal collision and position integration. We supply
 * the horizontal velocity and nothing else. See docs/smb1_player_adapter.md.
 *
 * Every address below was confirmed in Ghidra (nes/SuperMarioBrosNES) before
 * being read or written -- framework RULE 0 -- and the confirming instruction
 * is cited. Names come from symbols.sym, generated into the decls header.
 *
 * ONE FIGHTER. The fighter instance lives behind the ForeignController ABI, in
 * mods/smash64/characters/captain_falcon.c, and is driven only through
 * nes_foreign_tick/nes_foreign_resolve. An earlier version kept a private
 * FalconFighter here as well, which meant two independent Falcons: the private
 * one drove SMB1 while the registry's -- whose `grounded` nobody maintained --
 * fell forever and was what the trace ring recorded. The ring is the primary
 * observability tool, so a ring reporting a different fighter than the one
 * moving the player is worse than no ring. Do not reintroduce a second
 * instance.
 */
#include "game_smash64.h"

#include "foreign_controller.h"
#include "mod_function_hooks.h"
#include "nes_runtime.h"

/* Brings in the RAM/const symbol defines (Player_X_Speed, GameEngineSubroutine,
 * ...) so nothing below is a bare literal. */
#include "generated/super-mario-bros_full_decls.h"

#include <stdio.h>
#include <string.h>

/* ------------------------------------------------------------------ */
/* Scale -- ONE conversion, applied here and nowhere else              */
/*                                                                    */
/* Derived in docs/falcon_movement_dependency.md section 8 from        */
/* Falcon's 400-unit collision diamond against SMB1's 16px metatile    */
/* grid.                                                              */
/*                                                                    */
/* SMB1 stores horizontal velocity as a signed 8-bit value in units of */
/* 1/16 pixel per frame: MoveObjectHorizontally ($BF0F) shifts the low */
/* nibble into the subpixel accumulator and the sign-extended high     */
/* nibble into the position. So a Smash unit converts as               */
/*     smash_units * 0.08 px/unit * 16 = smash_units * 1.28            */
/* ------------------------------------------------------------------ */
#define FALCON_TO_SMB1_PX     0.08
#define SMB1_XSPEED_PER_PX    16.0
#define FALCON_TO_SMB1_XSPEED (FALCON_TO_SMB1_PX * SMB1_XSPEED_PER_PX)

/* SMB1's own caps, for scale: MaxRightXSpdData $B443 = {40,24,16,12}, so
 * Mario's top run is 40/16 = 2.5 px/frame. Falcon's run is 75 * 1.28 = 96,
 * which is 2.4x Mario and still inside the signed 8-bit field. */
#define SMB1_XSPEED_LIMIT 127

/* ------------------------------------------------------------------ */
/* SMB1 player state -- every address Ghidra-confirmed                 */
/*                                                                    */
/* GameEngineSubroutine  $000E  read at $B0E9 (PlayerCtrlRoutine) and  */
/*                              indexed at $B04A (GameRoutines)        */
/* Player_State          $001D  read at $B450, $B51C, $B0E9            */
/* Player_X_Speed        $0057  written by $B5CC (ImposeFriction) and   */
/*                              zeroed by $DF6D (ImpedePlayerMove)      */
/* Player_XSpeedAbsolute $0700  written by $B5CC, read by $B51C/$B4BB   */
/* SideCollisionTimer    $0785  set to 16 by $DF68 (ImpedePlayerMove)   */
/*                                                                     */
/* The GameRoutines jump table at $B04F was decoded straight out of     */
/* the ROM and gives the complete ownership map:                        */
/*   0 Entrance_GameTimerSetup   7 PlayerEntrance                       */
/*   1 Vine_AutoClimb            8 PlayerCtrlRoutine  <-- ordinary play */
/*   2 SideExitPipeEntry         9 PlayerChangeSize                     */
/*   3 VerticalPipeEntry        10 PlayerInjuryBlink                    */
/*   4 FlagpoleSlide            11 PlayerDeath                          */
/*   5 PlayerEndLevel           12 PlayerFireFlower                     */
/*   6 PlayerLoseLife                                                   */
/* So == 8 is exactly "ordinary controllable gameplay", and every other */
/* value is a scripted sequence that must stay native.                  */
/* ------------------------------------------------------------------ */
#define SMB1_GAMEMODE_PLAYER_CTRL 8

/* ImposeFriction, the horizontal velocity integrator we take over. Called
 * only from GndMove ($B363) and LRAir ($B3B0) -- player-only by construction,
 * since it reads Player_CollisionBits/Player_X_Speed non-indexed. */
#define SMB1_IMPOSE_FRICTION_ADDR 0xB5CC
#define SMASH64_FRICTION_HOOK_ID  "super-mario-bros.smash64.impose-friction"

/* ------------------------------------------------------------------ */
/* Mod state                                                          */
/* ------------------------------------------------------------------ */

static int  s_enabled = 0;
static char s_controller_id[96] = {0};
static int  s_selected = 0;
static int  s_announced = 0;

static uint8_t  s_prev_buttons = 0;
static uint64_t s_frame = 0;
static int8_t   s_xspeed = 0;            /* this frame's velocity, computed in
                                          * update_input, written by the hook */
static int8_t   s_wrote_xspeed = 0;      /* what the hook wrote last frame, so a
                                          * zeroed readback is detectable as
                                          * SMB1 refusing the motion */
static unsigned long s_owned_frames = 0;
static unsigned long s_wall_frames = 0;

/* NES pad bits: bit7=A bit6=B bit5=Select bit4=Start
 *               bit3=Up bit2=Down bit1=Left bit0=Right */
#define PAD_A      0x80
#define PAD_B      0x40
#define PAD_UP     0x08
#define PAD_DOWN   0x04
#define PAD_LEFT   0x02
#define PAD_RIGHT  0x01

/* ------------------------------------------------------------------ */
/* Ownership                                                          */
/* ------------------------------------------------------------------ */

static ForeignOwnership decide_ownership(void)
{
    if (!s_enabled || !s_selected) return FOREIGN_OWNERSHIP_NATIVE;

    /* Anything but ordinary play is a scripted sequence -- pipes, flagpole,
     * death, entrance autowalk, powerup transitions. Hand control back
     * rather than blanket-suppressing SMB1's player update. */
    if (g_ram[GameEngineSubroutine] != SMB1_GAMEMODE_PLAYER_CTRL)
        return FOREIGN_OWNERSHIP_SCRIPTED;

    /* M2 SIMPLIFICATION: Falcon owns the ground, SMB1 owns the air. While
     * Player_State is nonzero the player is jumping/falling and SMB1's own air
     * physics run untouched. M3 takes the air properly. */
    if (g_ram[Player_State] != 0) return FOREIGN_OWNERSHIP_NATIVE;

    return FOREIGN_OWNERSHIP_FOREIGN;
}

/* ------------------------------------------------------------------ */
/* Input -- digital pad to synthetic analog stick                      */
/* ------------------------------------------------------------------ */

/*
 * A d-pad press moves the synthetic stick 0 -> +/-1.0 in one frame, which the
 * controller reads as a full-deflection fresh stick tap. That makes dash,
 * dash->run, turn, brake, short hop, full hop and fast fall all reachable.
 * Walk is not reachable from neutral -- see
 * docs/smb1_player_adapter.md section 5.
 */
static void sample_input(ForeignInput *out)
{
    const uint8_t b = g_controller1_buttons;
    const uint8_t pressed = (uint8_t)(b & ~s_prev_buttons);

    const int left  = (b & PAD_LEFT)  != 0;
    const int right = (b & PAD_RIGHT) != 0;
    const int up    = (b & PAD_UP)    != 0;
    const int down  = (b & PAD_DOWN)  != 0;

    memset(out, 0, sizeof(*out));

    /* Opposing directions cancel, matching how the pad is read. */
    out->stick_x = (float)((right ? 1 : 0) - (left ? 1 : 0));
    out->stick_y = (float)((up ? 1 : 0) - (down ? 1 : 0));

    out->jump_held    = (b & PAD_A) != 0;
    out->jump_pressed = (pressed & PAD_A) != 0;
    out->raw_buttons  = b;

    s_prev_buttons = b;
}

/* ------------------------------------------------------------------ */
/* Per frame                                                          */
/* ------------------------------------------------------------------ */

static int8_t clamp_xspeed(double smash_units)
{
    double v = smash_units * FALCON_TO_SMB1_XSPEED;

    if (v >  SMB1_XSPEED_LIMIT) v =  SMB1_XSPEED_LIMIT;
    if (v < -SMB1_XSPEED_LIMIT) v = -SMB1_XSPEED_LIMIT;
    return (int8_t)((v >= 0.0) ? (v + 0.5) : (v - 0.5));
}

void game_smash64_update_input(uint64_t frame_count)
{
    ForeignInput fin;
    ForeignMoveResult move;
    ForeignCollisionResult hit;
    ForeignState *fs;
    int wall;

    s_frame = frame_count;
    if (!s_enabled || !s_selected) return;

    sample_input(&fin);

    /*
     * Publish ownership and tick ONCE per frame, here rather than in the hook,
     * so the trace ring gets a row every frame including while SMB1 owns the
     * player. Handoffs must appear as transitions, not as gaps -- and gaps are
     * what the ring showed before, because the hook only fires from SMB1's own
     * movement path and scripted sequences never reach it.
     */
    nes_foreign_set_ownership(decide_ownership());

    fs = nes_foreign_state();
    if (fs) {
        /* SMB1 is the authority on standing on ground. */
        fs->grounded = (g_ram[Player_State] == 0);
    }

    /*
     * Did SMB1 refuse last frame's motion? ImpedePlayerMove ($DF4B) is the wall
     * response: it zeroes Player_X_Speed ($DF6D), sets SideCollisionTimer
     * ($DF68) and ejects the player one pixel. Either signal means the velocity
     * we proposed was rejected, so feed that back rather than proposing it
     * again -- which is what turned a wall into a tunnel.
     */
    wall = (s_wrote_xspeed != 0 && (int8_t)g_ram[Player_X_Speed] == 0) ||
           (g_ram[SideCollisionTimer] != 0);

    memset(&move, 0, sizeof(move));
    if (nes_foreign_tick(frame_count, &fin, &move)) {
        if (wall) {
            move.requested_dx = 0.0;
            s_wall_frames++;
        }
        s_xspeed = clamp_xspeed(move.requested_dx);
        s_owned_frames++;
    } else {
        /* SMB1 owns the player; keep our idea of velocity in step with it so
         * resuming control does not inject a stale speed. */
        s_xspeed = (int8_t)g_ram[Player_X_Speed];
    }

    /*
     * M2: SMB1 integrates and collides, so the granted motion is what we
     * proposed minus anything the wall check just removed. That is honest for
     * horizontal ground movement; M4 replaces it with a real swept query
     * against SMB1's block buffer.
     */
    memset(&hit, 0, sizeof(hit));
    hit.actual_dx = move.requested_dx;
    hit.grounded = (g_ram[Player_State] == 0);
    hit.hit_wall = wall;
    nes_foreign_resolve(&hit);
}

/*
 * Replaces ImposeFriction ($B5CC) while Falcon owns the player.
 *
 * Returning 1 skips SMB1's own horizontal integrator, so the velocity we write
 * survives to MoveObjectHorizontally ($BF0F), which applies it with SMB1's own
 * collision. Returning 0 runs the original unchanged.
 */
static int impose_friction_hook(uint16_t addr)
{
    int8_t xspeed;

    (void)addr;

    /*
     * Re-check ownership here even though update_input already decided it.
     * This runs inside the game's own movement path, so it is the authoritative
     * moment: if the mode changed since VBlank we must not write. Defence in
     * depth on top of the structural guarantee that ImposeFriction is only
     * reached during ordinary play at all.
     */
    if (decide_ownership() != FOREIGN_OWNERSHIP_FOREIGN) return 0;

    xspeed = s_xspeed;

    /* The two bytes ImposeFriction itself writes. Player_XSpeedAbsolute is not
     * decoration: $B51C reads it to pick the speed tier and $B4BB reads it to
     * scale jump height, so leaving it stale would make Falcon jump like a
     * walking Mario. */
    g_ram[Player_X_Speed] = (uint8_t)xspeed;
    g_ram[Player_XSpeedAbsolute] =
        (uint8_t)((xspeed < 0) ? -(int)xspeed : (int)xspeed);
    s_wrote_xspeed = xspeed;

    nes_foreign_trace_note_native((int32_t)xspeed,
                                  (int32_t)g_ram[Player_Y_Position]);
    return 1;
}

/* ------------------------------------------------------------------ */
/* Public                                                             */
/* ------------------------------------------------------------------ */

void game_smash64_set_mod_enabled(int enabled, const char *controller_id)
{
    s_enabled = 0;
    s_selected = 0;
    s_announced = 0;
    s_controller_id[0] = '\0';
    nes_foreign_set_ownership(FOREIGN_OWNERSHIP_NATIVE);
    nes_mod_set_function_hook_enabled(SMASH64_FRICTION_HOOK_ID, 0);

    if (!enabled || !controller_id || !controller_id[0]) {
        nes_foreign_select(NULL);
        return;
    }

    snprintf(s_controller_id, sizeof s_controller_id, "%s", controller_id);
    s_selected = nes_foreign_select(s_controller_id);
    if (!s_selected) {
        /* Fail loudly. A silently-ignored character selection is exactly the
         * kind of thing that gets mistaken for "the physics is subtle". */
        fprintf(stderr,
                "[Smash64] No controller registered for '%s' - "
                "player replacement stays OFF\n", s_controller_id);
        return;
    }

    s_xspeed = 0;
    s_wrote_xspeed = 0;
    s_owned_frames = 0;
    s_wall_frames = 0;

    if (!nes_mod_set_function_hook_enabled(SMASH64_FRICTION_HOOK_ID, 1)) {
        fprintf(stderr,
                "[Smash64] ImposeFriction hook is not registered; SMB1 keeps "
                "its own horizontal physics\n");
        return;
    }
    s_enabled = 1;
}

int game_smash64_active(void)
{
    return s_enabled && s_selected &&
           nes_foreign_ownership() == FOREIGN_OWNERSHIP_FOREIGN;
}

void game_smash64_init(void)
{
    if (!s_enabled) return;
    {
        const ForeignController *ctl = nes_foreign_active();
        printf("[Smash64] Player replacement armed: %s (%s)\n",
               ctl && ctl->name ? ctl->name : "?", s_controller_id);
    }
    /* ASCII only: the Windows console codepage mangles non-ASCII here. */
    printf("[Smash64] M2: Falcon owns horizontal GROUND movement; SMB1 keeps "
           "jump, gravity, vertical and all collision.\n");
    printf("[Smash64] Traces: TCP 'ftring', or NESRECOMP_FTRING_DUMP=<path>.\n");
}

void game_smash64_update(uint64_t frame_count)
{
    (void)frame_count;
    if (!s_enabled || !s_selected) return;

    if (!s_announced && s_owned_frames > 0) {
        const ForeignController *ctl = nes_foreign_active();
        const ForeignState *fs = nes_foreign_state();
        s_announced = 1;
        printf("[Smash64] Falcon has the wheel (state %s, X_Speed %d = %.2f "
               "px/frame; Mario's own max run is 40 = 2.50)\n",
               (ctl && ctl->state_name && fs) ? ctl->state_name(fs->state) : "?",
               (int)s_xspeed, (double)s_xspeed / SMB1_XSPEED_PER_PX);
    }
}

unsigned long game_smash64_owned_frames(void) { return s_owned_frames; }
unsigned long game_smash64_wall_frames(void)  { return s_wall_frames; }

/* Registered before main() by mods/smash64_player_plugin.c; starts disabled,
 * so registration alone cannot change behaviour. */
int game_smash64_register_hooks(void)
{
    return nes_mod_register_function_entry_plugin(
        SMASH64_FRICTION_HOOK_ID, SMB1_IMPOSE_FRICTION_ADDR,
        impose_friction_hook);
}
