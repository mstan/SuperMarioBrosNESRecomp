/*
 * game_smash64.c -- SMB1 host adapter for the Smash 64 player replacement mod.
 *
 * Answers "where is the player allowed to go" and owns everything the fighter
 * controller must not see: NES RAM layout, SMB1's fixed-point velocity
 * representation, and its scripted player states.
 *
 * SCOPE (M2 + M3): Falcon supplies the horizontal velocity AND the vertical
 * motion -- jump velocity, gravity, terminal velocity, fast fall and air drift.
 * SMB1 keeps everything else: it decides WHEN you jump and when you have landed,
 * it owns horizontal and vertical collision, and every scripted player sequence
 * stays native. See docs/smb1_player_adapter.md.
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
#include "game_smash64_attack_policy.h"
#include "game_smash64_assets.h"
#include "game_smash64_actions.h"
#include "game_smash64_audio.h"
#include "game_smash64_fighter_profile.h"

#include "mods/smash64/characters/pikachu.h"

#include "foreign_controller.h"
#include "mod_function_hooks.h"
#include "mod_savestate.h"
#include "nes_runtime.h"

/* Brings in the RAM/const symbol defines (Player_X_Speed, GameEngineSubroutine,
 * ...) so nothing below is a bare literal. */
#include "generated/super-mario-bros_full_decls.h"

#include <float.h>

_Static_assert(SMASH64_ENEMY_BULLET_BILL_FRENZY == BulletBill_FrenzyVar,
               "Falcon target policy Bullet Bill ID drifted from SMB symbols");
_Static_assert(SMASH64_ENEMY_PODOBOO == Podoboo,
               "Falcon target policy Podoboo ID drifted from SMB symbols");
_Static_assert(SMASH64_ENEMY_FIRST_SPECIAL == BowserFlame,
               "Falcon target policy special-object boundary drifted");

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

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
#define SMB1_XSPEED_PER_PX    16.0

/* SMB1's own caps, for scale: MaxRightXSpdData $B443 = {40,24,16,12}, so
 * Mario's top run is 40/16 = 2.5 px/frame. Falcon's authored run would map to
 * 75 * 1.28 = 96, or 6 px/frame, but the world streamer cannot sustain that.
 *
 * UpdScrollVar ($AF6F) advances exactly one AreaParserTaskHandler task per
 * frame. One complete job is eight tasks and advances two 16px columns, so
 * SMB1 can prepare at most 32px / 8 frames = 4px/frame. Feeding a larger
 * Player_X_Scroll makes ScrollThirtyTwo accumulate unserviced thresholds;
 * once its byte reaches $A0, the original signed BMI test even treats the debt
 * as below $20. The camera then outruns CurrentColumnPos/BlockBufferColumnPos,
 * corrupting upcoming collision, enemy and warp-zone context.
 *
 * Clamp the PHYSICAL foreign movement here, before $BF09 integrates it, rather
 * than clamping only the camera return value. That keeps player, camera and
 * parser in one world coordinate system. $40 is the streamer's exact service
 * boundary; $7f remains the signed host-field boundary for bounded authored
 * attack motion, whose enforced recovery lets the parser repay a short burst. */
#define SMB1_STREAM_XSPEED_LIMIT 64
#define SMB1_XSPEED_FIELD_LIMIT 127

/* ------------------------------------------------------------------ */
/* SMB1 player state -- every address Ghidra-confirmed                 */
/*                                                                    */
/* GameEngineSubroutine  $000E  read at $B0E9 (PlayerCtrlRoutine) and  */
/*                              indexed at $B04A (GameRoutines)        */
/* Player_State          $001D  read at $B450, $B51C, $B0E9            */
/* Player_X_Speed        $0057  written by $B5CC (ImposeFriction) and   */
/*                              zeroed by $DF6D (ImpedePlayerMove)      */
/* Player_XSpeedAbsolute $0700  written by $B5CC, read by $B51C/$B4BB   */
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
#define SMB1_GAMEMODE_SIDE_PIPE 2
#define SMB1_GAMEMODE_VERTICAL_PIPE 3
#define SMB1_GAMEMODE_FLAGPOLE_SLIDE 4
#define SMB1_GAMEMODE_PLAYER_END_LEVEL 5
#define SMB1_GAMEMODE_PLAYER_ENTRANCE 7
#define SMB1_GAMEMODE_CHANGE_SIZE 9
#define SMB1_GAMEMODE_INJURY_BLINK 10
#define SMB1_GAMEMODE_PLAYER_DEATH 11
#define SMB1_GAMEMODE_FIRE_FLOWER 12
/* OperModeExecutionTree $8212 reads OperMode $0770 and dispatches value 0 to
 * TitleScreenMode, 1 to GameMode, 2 to VictoryMode, and 3 to GameOverMode.
 * Ghidra confirms the $8212 read of $0770.  GameEngineSubroutine can retain 8
 * in title/attract state, so it is not sufficient as the outer presentation
 * gate by itself. */
#define SMB1_OPER_MODE_GAME 1

/* ImposeFriction, the horizontal velocity integrator we take over. Called
 * only from GndMove ($B363) and LRAir ($B3B0) -- player-only by construction,
 * since it reads Player_CollisionBits/Player_X_Speed non-indexed. */
#define SMB1_IMPOSE_FRICTION_ADDR 0xB5CC
#define SMASH64_FRICTION_HOOK_ID  "super-mario-bros.smash64.impose-friction"

/*
 * MovePlayerVertically ($BF4D), the player's own vertical integrator. It loads
 * VerticalForce ($0709) as the gravity amount, sets a max Y speed of 4, and
 * tail-calls ImposeGravitySprObj -> ImposeGravity ($BFD7) with X = 0.
 *
 * We SKIP it and integrate ourselves, because that max-speed clamp is fatal to
 * Falcon: SMB1 caps the player's fall at 4 px/frame while Falcon's terminal
 * velocity is 5.28 and his fast fall is 8.00. Feeding SMB1 our numbers and
 * letting it integrate would silently discard fast fall entirely -- the clamp
 * is applied inside the routine, after the gravity add, so there is no way to
 * pre-empt it from outside.
 *
 * ImposeGravity, decoded, does exactly three things (and we reproduce the parts
 * that matter with Falcon's constants and no clamp):
 *     YMF_Dummy   += Y_MoveForce            ; sub-fraction accumulate
 *     Y_Position  += Y_Speed + carry        ; sign-extended into Y_HighPos
 *     Y_MoveForce += gravity, carry into Y_Speed, then clamp Y_Speed to max
 *
 * Vertical COLLISION is not here -- it lives in PlayerBGCollision, runs
 * separately, and still corrects our position. So this remains
 * "controller proposes, SMB1 resolves".
 */
#define SMB1_MOVE_PLAYER_VERTICALLY_ADDR 0xBF4D
#define SMASH64_VERTICAL_HOOK_ID "super-mario-bros.smash64.move-vertically"

/*
 * MovePlayerHorizontally ($BF09) -- M4, the horizontal integrator.
 *
 * WHY THIS ADDRESS AND NOT $BF0F. MoveObjectHorizontally ($BF0F) is GENERIC:
 * it indexes SprObject_X_Speed,X and enemies reach it through
 * MoveEnemyHorizontally (smb.asm:7468) and four other call sites. Hooking it
 * would freeze every enemy on screen. $BF09 is the player-only wrapper --
 * Ghidra:
 *     bf09: LDA $070E / BNE $BF4C (ExXMove)   <- jumpspring gate
 *     bf0e: TAX                               <- X = 0, the player
 *     bf0f: LDA $57,X ...                     <- generic body
 *
 * ABI THAT MUST BE PRESERVED: both callers store the routine's return A as
 * Player_X_Scroll (smb.asm:5848 GndMove, :5889 JSMove) -- A is the whole
 * pixels moved this frame and it DRIVES THE SCROLL ENGINE. The hook must
 * leave the swept per-frame delta in g_cpu.A or the screen stops following
 * the player. (Reporting the swept-actual rather than vanilla's intended
 * value is deliberate: the screen should not scroll into a wall the player
 * did not pass.)
 *
 * Horizontal COLLISION is not here -- DoPlayerSideCheck ($DD5E) runs inside
 * PlayerBGCollision, separately, and still reacts to the position we commit.
 * The sweep's job is only to never move MORE than one pixel into the first
 * tile SMB1's own side check objects to, so this remains "controller
 * proposes, SMB1 resolves" -- the exact vertical-sweep contract.
 */
#define SMB1_MOVE_PLAYER_HORIZONTALLY_ADDR 0xBF09
#define SMASH64_HORIZONTAL_HOOK_ID "super-mario-bros.smash64.move-horizontally"
#define SMB1_BOUNDING_BOX_CORE_ADDR 0xE29C
#define SMASH64_BOUNDING_BOX_HOOK_ID "super-mario-bros.smash64.player-bounds"

/* M5.5 save-state hook id -- the adapter half. See game_smash64_savestate_get
 * below for the layout and what it deliberately omits. */
#define SMASH64_ADAPTER_SAVESTATE_ID "super-mario-bros.smash64.adapter"
#define SMASH64_CONTROLLER_SAVESTATE_ID \
    "super-mario-bros.smash64.active-controller"
#define SMASH64_ACTIONS_SAVESTATE_ID \
    "super-mario-bros.smash64.persistent-actions"
#define SMASH64_ACTIONS_RECORD_HEADER 8

static int s_savestate_controller_compatible = 1;
static const Smash64FighterProfile *s_profile = NULL;
static void game_smash64_request_savestate_reseed(void);
static void game_smash64_sync_persistent_audio(void);
static int action_resolve_attachment(uint32_t source_joint,
                                     double fighter_world_x,
                                     double fighter_foot_y,
                                     double *world_x, double *screen_y);

static void save_write_u32le(uint8_t *dst, uint32_t value)
{
    dst[0] = (uint8_t)value;
    dst[1] = (uint8_t)(value >> 8);
    dst[2] = (uint8_t)(value >> 16);
    dst[3] = (uint8_t)(value >> 24);
}

static uint32_t save_read_u32le(const uint8_t *src)
{
    return (uint32_t)src[0] | ((uint32_t)src[1] << 8) |
           ((uint32_t)src[2] << 16) | ((uint32_t)src[3] << 24);
}

static int game_smash64_controller_savestate_get(uint8_t *buf, int cap)
{
    return nes_foreign_serialize_active(buf, cap);
}

static int game_smash64_controller_savestate_set(const uint8_t *buf, int len)
{
    if (len > 0 && nes_foreign_deserialize_active(buf, len)) {
        s_savestate_controller_compatible = 1;
        return 1;
    }
    /* Loading a save made with another selected fighter must not leave its
     * adapter/action records paired with the live controller. Keep the user's
     * current selection, discard incompatible transients, and force the same
     * native-position reseed used after a scripted SMB handoff. */
    s_savestate_controller_compatible = 0;
    game_smash64_request_savestate_reseed();
    fprintf(stderr,
            "[Smash64] Save has no compatible active-controller record; "
            "reseeded the currently selected fighter\n");
    return 1;
}

static int game_smash64_actions_savestate_get(uint8_t *buf, int cap)
{
    int payload;
    if (!nes_foreign_active() || !s_profile) return 0;
    if (!buf || cap < SMASH64_ACTIONS_RECORD_HEADER) return -1;
    memcpy(buf, "S64A", 4);
    save_write_u32le(buf + 4, s_profile->savestate_tag);
    payload = smash64_actions_serialize(
        buf + SMASH64_ACTIONS_RECORD_HEADER,
        cap - SMASH64_ACTIONS_RECORD_HEADER);
    return payload < 0 ? payload : payload + SMASH64_ACTIONS_RECORD_HEADER;
}

static int game_smash64_actions_savestate_set(const uint8_t *buf, int len)
{
    if (len == 0) {
        smash64_actions_clear();
        game_smash64_sync_persistent_audio();
        return 1;
    }
    if (!s_savestate_controller_compatible || !s_profile) {
        smash64_actions_clear();
        game_smash64_sync_persistent_audio();
        return 1;
    }
    if (len >= SMASH64_ACTIONS_RECORD_HEADER &&
        memcmp(buf, "S64A", 4) == 0) {
        if (save_read_u32le(buf + 4) != s_profile->savestate_tag) {
            smash64_actions_clear();
            game_smash64_sync_persistent_audio();
            return 1;
        }
        buf += SMASH64_ACTIONS_RECORD_HEADER;
        len -= SMASH64_ACTIONS_RECORD_HEADER;
    } else if (s_profile->savestate_tag != 0x504B3634u) {
        /* Headerless action records only existed on the pre-release Pikachu
         * branch. Never interpret one while another fighter is active. */
        smash64_actions_clear();
        game_smash64_sync_persistent_audio();
        return 1;
    }
    if (!smash64_actions_deserialize(buf, len)) smash64_actions_clear();
    game_smash64_sync_persistent_audio();
    return 1;
}

/*
 * PlayerPhysicsSub ($B450) -- M3.5, the jumpsquat window.
 *
 * SMB1 launches on the A button's rising edge, while Falcon's NES mapping uses
 * A for primary attack and a fresh Up-stick for KneeBend. Hide physical A from
 * SMB1 and synthesize its required edge only on the frame Falcon actually
 * leaves the ground. See ForeignJumpPhase.
 *
 * WHY THIS ADDRESS AND NOT PlayerCtrlRoutine ($B0E9). $B0E9 is the obvious
 * candidate and it does not work: SaveJoyp lives INSIDE PlayerCtrlRoutine, a
 * few instructions past entry, and rewrites A_B_Buttons from SavedJoypadBits
 * every frame --
 *     SaveJoyp: lda SavedJoypadBits / and #%11000000 / sta A_B_Buttons
 * so a mask applied at $B0E9 entry is overwritten by the game itself before
 * CheckForJumping ever reads it. $B450 is downstream of SaveJoyp and upstream
 * of CheckForJumping ($B479, 41 bytes into the same routine), and is entered
 * from exactly one site, ProcMove. Ghidra:
 *     b450: LDA $001D / CMP #3 / BNE $b479     <- entry
 *     b479: LDA $070e / BNE $b488              <- jumpspring gate
 *     b47e: LDA $000a / AND #$80 / BEQ $b488
 *     b484: AND $000d / BEQ $b48b -> InitJS $b4a0
 *
 * The hook ALWAYS RETURNS 0: it adjusts one byte and lets SMB1's own physics
 * run untouched.
 */
#define SMB1_PLAYER_PHYSICS_ADDR 0xB450
#define SMASH64_JUMPSQUAT_HOOK_ID "super-mario-bros.smash64.jumpsquat"

/* A_B_Buttons bits. Physical A/B are Falcon's primary/special attacks and are
 * masked at PlayerPhysicsSub. A is reintroduced only as SMB1's synthetic jump
 * handshake; B never reaches its run/fireball readers while Falcon owns play. */
#define SMB1_A_BUTTON_BIT 0x80
#define SMB1_B_BUTTON_BIT 0x40

/* SMB1 vertical scale differs from horizontal: Player_Y_Speed is in WHOLE
 * pixels per frame (PlayerYSpdData $B432 = -4,-4,-4,-5,-5,-2,-1) with
 * Player_Y_MoveForce as a 1/256 fraction. Horizontal was 1/16 px. */
#define SMB1_YSPEED_PER_PX 1.0

/* ------------------------------------------------------------------ */
/* Mod state                                                          */
/* ------------------------------------------------------------------ */

static int  s_enabled = 0;
static char s_controller_id[96] = {0};
static int  s_selected = 0;
static int  s_announced = 0;

static int selected_controller_is_pikachu(void)
{
    return s_profile && strcmp(s_controller_id, SMASH64_PIKACHU_ID) == 0;
}

/* A projectile's lifetime is host-owned and serializable, whereas the
 * controller's audio event is one tick at source spawn. Reconcile the loop to
 * the actual action slot so a terrain hit, a profile switch, or a save-state
 * restore cannot leave audio running after the Jolt has gone. */
static void game_smash64_sync_persistent_audio(void)
{
    game_smash64_audio_set_persistent_cue_active(
        PIKACHU_AUDIO_ELECTRIC_LOOP,
        selected_controller_is_pikachu() &&
        smash64_actions_has_active_kind(PIKACHU_PROJECTILE_JOLT));
}

static uint8_t  s_prev_buttons = 0;
/* NES keyboard/controller events can place B one VBlank ahead of the d-pad
 * direction the player intended to press with it. Defer only a directionless
 * B edge for one frame; simultaneous and direction-first specials remain
 * immediate, while neutral Falcon Punch gains one frame of latency. */
static int s_special_grace_pending;
static uint64_t s_frame = 0;
static int8_t   s_xspeed = 0;            /* this frame's velocity, computed in
                                          * update_input, written by the hook */
static ForeignAttackHitbox s_attack;     /* emitted before NMI, consumed once
                                          * inside PlayerPhysicsSub */
static int s_contact_pending;            /* one target connected; drained into
                                          * the next collision resolve */
static int s_forced_airborne_pending;    /* bridges a controller's one-tick
                                          * departure edge across SMB1's
                                          * integer floor quantization */
static unsigned s_forced_airborne_frames;
static unsigned long s_owned_frames = 0;
static unsigned long s_wall_frames = 0;
static unsigned long s_air_frames = 0;
static unsigned long s_squat_frames = 0;   /* frames SMB1's A bit was withheld */
static unsigned long s_launch_frames = 0;  /* frames it was presented */
static int s_friction_ran = 0;           /* did ImposeFriction fire this frame */
static double s_y_sub = 0.0;             /* vertical subpixel remainder, kept
                                          * host-side rather than contending
                                          * for SMB1's fraction bytes */
static double s_pending_external_dy = 0.0; /* controller-space Y displacement
                                            * applied by a host-side atomic
                                            * clearance adaptation */
static int s_wrote_y = 0;                /* 16-bit player Y the vertical hook
                                          * last wrote, so a corrected readback
                                          * is detectable as SMB1 refusing the
                                          * motion */
static int s_wrote_y_valid = 0;
static int8_t s_wrote_yspeed = 0;        /* Player_Y_Speed the vertical hook
                                          * last wrote, so SMB1 overwriting it
                                          * is detectable as a vertical EVENT
                                          * (bounce / spring / killed jump)
                                          * rather than lost silently */
static int s_wrote_yspeed_valid = 0;
static unsigned long s_imposed_frames = 0;
static int s_y_before = 0;               /* 16-bit player Y at hook entry */
static double s_wrote_dy_px = 0.0;       /* sign of that motion: SMB1's Y grows
                                          * downward, so < 0 was rising */

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

/*
 * The player's WORLD x, for the trace ring's native_x column.
 *
 * This used to be handed the frame's x-SPEED, which made the column a
 * duplicate of vx under a name that says position -- so a trace could not
 * answer "where was he when that happened", which is the first question any
 * geometry bug asks. Player_X_Position ($0086) is only the low byte and wraps
 * every 256 px, so combine it with Player_PageLoc ($006D) to get something
 * monotonic across a level.
 */
static int32_t player_native_x(void)
{
    return ((int32_t)g_ram[Player_PageLoc] * 256) +
           (int32_t)g_ram[Player_X_Position];
}

/* ------------------------------------------------------------------ */
/* M4 -- asking SMB1's own tiles where the player may go               */
/* ------------------------------------------------------------------ */

/*
 * Host-defined bits in ForeignCollisionResult.flags, recorded in the ring's
 * collision_flags column. These say what SMB1's OWN block buffer thinks about
 * where the controller has actually put the player, which is a different
 * question from whether SMB1 bothered to act on it.
 */
#define SMASH64_CF_HEAD_IN_SOLID 0x0001u
#define SMASH64_CF_FEET_IN_SOLID 0x0002u
#define SMASH64_CF_SWEPT_CEILING 0x0004u
#define SMASH64_CF_SWEPT_FLOOR   0x0008u
/* The sweep actually stepped and probed this frame. Without this, "no sweep
 * block" is ambiguous between "nothing was in the way" and "the sweep never
 * got a chance to look", and those need completely different fixes. */
#define SMASH64_CF_SWEPT_RAN     0x0010u
/* Horizontal twins. SIDE_SWEPT_RAN exists for the identical ambiguity. */
#define SMASH64_CF_SWEPT_WALL     0x0020u
#define SMASH64_CF_SIDE_SWEPT_RAN 0x0040u
#define SMASH64_CF_ATTACK_ACTIVE  0x0100u
#define SMASH64_CF_ENEMY_DEFEATED 0x0200u
#define SMASH64_CF_BLOCK_BROKEN   0x0400u
#define SMASH64_CF_CONTACT_CAUGHT 0x0800u
#define SMASH64_CF_FORCE_AIRBORNE 0x1000u

/* What the per-pixel sweep stopped on last frame, if anything. Consumed by the
 * next update_input, which is the next time a ForeignCollisionResult is built. */
#define SMASH64_SWEEP_NONE    0
#define SMASH64_SWEEP_CEILING 1
#define SMASH64_SWEEP_FLOOR   2
static int s_swept_block = SMASH64_SWEEP_NONE;
static int s_swept_ran = 0;
/* Diagnostic: NESRECOMP_SMASH64_SWEEP_NOBLOCK=1 keeps the sweep's probes and
 * ring flags but never stops the motion. This exists to answer the question
 * the sweep otherwise masks: does the raw per-frame delta tunnel through
 * SMB1's own collision? Announced on stderr at mod enable, so a run with it
 * on can never be mistaken for a normal one. Governs BOTH axes. */
static int s_sweep_noblock = 0;

/* Horizontal sweep results, produced inside the horizontal hook and drained
 * by the next update_input -- the exact pattern of s_swept_block above. */
static int s_x_swept_wall = 0;
static int s_x_swept_ran = 0;
/* Coupled root-burst projection lives one host tick. It cannot be recovered
 * from ForeignState after the controller resolves, because that state retains
 * source-space velocity for source action timing and savestates. */
static double s_coupled_dx = 0.0;
static double s_coupled_dy = 0.0;
static int s_coupled_motion_valid = 0;
/* A profile-produced burst plan lives entirely on the host side. It preserves
 * the source fighter's velocity for source timing/save semantics while giving
 * the SMB mover one stable vector cap for this exact phase. */
static unsigned s_coupled_plan_state = UINT_MAX;
static double s_coupled_plan_component_px_limit = 0.0;
static int s_coupled_plan_active = 0;
/* Older adapter records did not carry a plan. They may resume a zip only at
 * conservative streamer service, never by re-deciding a fast plan mid-zip. */
static int s_coupled_plan_conservative_chain = 0;
static double s_x_sub = 0.0;   /* horizontal subpixel remainder, host-side --
                                * replaces SprObject_X_MoveForce ($0400), which
                                * the skipped integrator owned */
static int s_wrote_x = 0;      /* native (page*256+pos) X the horizontal hook
                                * last wrote, so an ImpedePlayerMove 1px eject
                                * is detectable as SMB1 refusing the motion */
static int s_wrote_x_valid = 0;
static int s_x_before = 0;     /* native X at horizontal hook entry */

/* Last frame's ownership, for the SCRIPTED->FOREIGN edge (M5). */
static ForeignOwnership s_prev_ownership = FOREIGN_OWNERSHIP_NATIVE;
static int s_reseed_this_frame = 0;   /* marks the ring row after the tick
                                       * pushes it -- the note functions edit
                                       * the LAST row, so ordering matters */
/* Collision-flag bits accumulated inside the vertical hook, where the sweep
 * runs, and drained by the next update_input when the ForeignCollisionResult
 * is assembled. Sampling them at the later point read a different instant of
 * the frame -- see the drain site. */
static uint32_t s_pending_flags = 0;

static void game_smash64_request_savestate_reseed(void)
{
    s_xspeed = 0;
    s_y_sub = 0.0;
    s_x_sub = 0.0;
    s_pending_external_dy = 0.0;
    s_wrote_y = 0;
    s_wrote_y_valid = 0;
    s_wrote_yspeed = 0;
    s_wrote_yspeed_valid = 0;
    s_y_before = 0;
    s_wrote_dy_px = 0.0;
    s_wrote_x = 0;
    s_wrote_x_valid = 0;
    s_x_before = 0;
    s_coupled_dx = s_coupled_dy = 0.0;
    s_coupled_motion_valid = 0;
    s_coupled_plan_state = UINT_MAX;
    s_coupled_plan_component_px_limit = 0.0;
    s_coupled_plan_active = 0;
    s_coupled_plan_conservative_chain = 0;
    s_prev_buttons = 0;
    s_special_grace_pending = 0;
    s_swept_block = SMASH64_SWEEP_NONE;
    s_swept_ran = 0;
    s_x_swept_wall = 0;
    s_x_swept_ran = 0;
    s_pending_flags = 0;
    s_contact_pending = 0;
    s_forced_airborne_pending = 0;
    s_forced_airborne_frames = 0;
    memset(&s_attack, 0, sizeof(s_attack));
    smash64_actions_clear();
    game_smash64_sync_persistent_audio();
    /* The next ordinary-control update takes the existing, well-tested
     * SCRIPTED->FOREIGN reseed path and reanchors the selected fighter to the
     * guest RAM that the save loader just restored. */
    s_prev_ownership = FOREIGN_OWNERSHIP_SCRIPTED;
    s_reseed_this_frame = 0;
}

/*
 * Index into BlockBuffer_X_Adder / BlockBuffer_Y_Adder for the player's
 * current size and posture. Mirrors ChkCollSize ($DBB1 region, smb.asm:11867)
 * exactly, including the order of the tests: BlockBufferAdderData ($E3AD) is
 * {$00, $07, $0e} and SMB1 walks Y down from 2.
 */
static uint8_t block_adder_index(void)
{
    return s_profile ? s_profile->block_adder_index : 0x00;
}

static double source_units_to_px(double units)
{
    return units * (s_profile ? s_profile->units_to_smb_px : 0.08);
}

static double smb_px_to_source_units(double pixels)
{
    const double scale = s_profile ? s_profile->units_to_smb_px : 0.08;
    return pixels / scale;
}

static int state_has_trait(unsigned state, uint32_t trait)
{
    return (smash64_fighter_profile_state_traits(s_profile, state) & trait)
           != 0;
}

/* PlayerHeadCollision writes $23 as a temporary blank while one of SMB1's
 * two block-object slots owns the replacement animation. Falcon's formerly
 * unbounded multi-brick pass could overwrite both slots before the updater
 * consumed them, leaving a visually blank but collision-solid $23 in old
 * saves. Repair only an ORPHAN: a live block state or replacement flag with
 * the same BlockBufferColli scratch address still owns a legitimate $23. */
static uint8_t settle_orphaned_blank_metatile(uint8_t tile)
{
    uint8_t ptr_lo;
    uint8_t row;
    uint16_t addr;

    if (tile != 0x23) return tile;

    ptr_lo = g_ram[0x06];
    row = g_ram[0x02];
    for (int i = 0; i < 2; ++i) {
        if ((g_ram[Block_State + i] != 0 ||
             g_ram[Block_RepFlag + i] != 0) &&
            g_ram[Block_BBuf_Low + i] == ptr_lo &&
            g_ram[Block_Orig_YPos + i] == row)
            return tile;
    }

    addr = (uint16_t)(((uint16_t)g_ram[0x07] << 8) | ptr_lo);
    addr = (uint16_t)(addr + row);
    if (addr < sizeof g_ram) g_ram[addr] = 0;
    return 0;
}

/*
 * Ask SMB1 whether the metatile at the player's head (or feet) is solid, for a
 * CANDIDATE vertical position.
 *
 * This calls the game's own lookup rather than reimplementing its address
 * math. BlockBufferCollision ($E3F0) reads SprObject_X_Position / PageLoc /
 * Y_Position for the object in X (0 = player), converts to a block-buffer
 * index and returns the metatile in A. It touches only scratch $02-$07, so it
 * is safe as a query provided we restore that scratch, the position byte we
 * moved, and the CPU registers.
 *
 * Deliberately NOT calling CheckForCoinMTiles, which HeadChk and DoFootCheck
 * both use here: despite the name it is not a predicate, it queues the
 * coin-grab sound as a side effect. CheckForSolidMTiles ($DF8F) is a genuine
 * predicate -- GetMTileAttrib plus a compare, registers only -- and returns
 * its answer in carry.
 *
 * Reimplementing any of this in C would be a second copy of ROM logic that
 * silently drifts; the game's tiles stay the only source of truth.
 */
static int smb1_solid_at(int y_pos, int feet,
                         int head_bumpables_are_barriers)
{
    CPU6502State save_cpu = g_cpu;
    uint8_t save_scratch[6];
    uint8_t save_y = g_ram[Player_Y_Position];
    uint8_t tile;
    int solid = 0;

    memcpy(save_scratch, &g_ram[0x02], sizeof save_scratch); /* $02..$07 */

    g_ram[Player_Y_Position] = (uint8_t)(y_pos & 0xFF);

    /* BlockBufferColli_Head does not set X (only _Side does), so the caller
     * owns it. Y selects the adder pair; _Feet increments it on entry. */
    g_cpu.X = 0;
    g_cpu.Y = block_adder_index();
    if (feet) BlockBufferColli_Feet();
    else      BlockBufferColli_Head();
    tile = settle_orphaned_blank_metatile(g_cpu.A);
    g_cpu.A = tile;

    /*
     * The predicate is NOT the same for the two edges, and getting this wrong
     * silently disabled the whole downward sweep once already.
     *
     * HEAD: HeadChk asks CheckForSolidMTiles ($DF8F), which answers "is this
     * the kind of thing you BUMP" -- SolidMTileUpperExt is {$10,$61,$88,$c4}
     * indexed by the metatile's 2 MSB, and carry is set only at or above that
     * base.
     *
     * FEET: DoFootCheck never calls it. It treats ANY NONZERO metatile as
     * floor (smb.asm:11926 `bne ChkFootMTile`) and then excludes climbables.
     * That distinction is not cosmetic: 1-1's ground metatile is $54, whose
     * 2 MSB select threshold $61, so $54 < $61 and CheckForSolidMTiles calls
     * ordinary ground NOT SOLID. Using it for the feet meant the probe
     * answered "no floor" while standing on the floor, and the downward sweep
     * could never fire. Measured: the sweep stepped through the landing row at
     * ny=176 without blocking.
     */
    if (tile != 0) {
        if (feet) {
            g_cpu.A = tile;
            CheckForClimbMTiles();
            solid = g_cpu.C ? 0 : 1;   /* climbable is not floor */
        } else if (head_bumpables_are_barriers &&
                   tile != 0xC2 && tile != 0xC3) {
            /* Native HeadChk deliberately classifies bricks and item blocks
             * below SolidMTileUpperExt as BUMPABLE, then lets
             * PlayerHeadCollision animate or shatter them. Falcon Dive is a
             * recovery move, not a head-bump attack: for its upward sweep
             * only, those same non-coin metatiles are physical barriers.
             * Coins remain pass-through so SMB1 can collect them normally. */
            solid = 1;
        } else {
            g_cpu.A = tile;
            CheckForSolidMTiles();
            solid = g_cpu.C ? 1 : 0;   /* cmp: carry set = at or above base */
        }
    }

    memcpy(&g_ram[0x02], save_scratch, sizeof save_scratch);
    g_ram[Player_Y_Position] = save_y;
    g_cpu = save_cpu;
    return solid;
}

/*
 * The side-contact predicate is neither of the vertical ones. CheckSideMTiles
 * ($DD9C) is its own chain, reproduced here in its own order:
 *   ChkInvisibleMTiles $DEBD: $5F/$60 are not walls
 *   CheckForClimbMTiles $DF9A: vine/ladder edges climb instead of stopping
 *   coins $C2/$C3 collect instead of stopping (CheckForCoinMTiles is NOT
 *     called for the same reason smb1_solid_at avoids it -- side effects)
 *   jumpsprings $67/$68 stop the player UNLESS one is already animating
 *   ChkPBtm: past this point everything is a wall except a sideways-pipe
 *     bottom ($6C/$1F) approached grounded and facing left, which enters it
 * DoPlayerSideCheck additionally excuses pipe tops $1C/$6B -- but only for
 * the UPPER body probe (smb.asm:11981-11984); the lower probe hands ANY
 * nonzero tile to CheckSideMTiles (smb.asm:11997).
 */
static int side_tile_is_wall(uint8_t tile, int upper)
{
    if (tile == 0) return 0;
    if (upper && (tile == 0x1C || tile == 0x6B)) return 0;
    if (tile == 0x5F || tile == 0x60) return 0;
    g_cpu.A = tile;
    CheckForClimbMTiles();
    if (g_cpu.C) return 0;
    if (tile == 0xC2 || tile == 0xC3) return 0;
    if (tile == 0x67 || tile == 0x68)
        return g_ram[JumpspringAnimCtrl] ? 0 : 1;
    if (g_ram[Player_State] != 0) return 1;
    if (g_ram[PlayerFacingDir] != 1) return 1;
    return (tile == 0x6C || tile == 0x1F) ? 0 : 1;
}

/*
 * Ask SMB1 whether a CANDIDATE horizontal position touches a wall on the
 * leading side. dir < 0 probes the left-edge adder pair (base+3/base+4,
 * X_Adder $02), dir > 0 the right-edge pair (base+5/base+6, X_Adder $0D) --
 * only the leading edge, because that is the only side ImpedePlayerMove
 * ($DF4B) itself acts on: a left-edge hit reacts only while X speed <= 0
 * ($DF60 CPY #1 / BPL exit) and a right-edge hit only while >= 0 ($DF55).
 *
 * BlockBufferColli_Side ($E3EC) sets X = 0 itself, unlike _Head/_Feet, and
 * touches the same scratch $02-$07, so the save/restore mirrors
 * smb1_solid_at exactly, with the position byte swapped for X and PageLoc.
 */
static int smb1_side_solid_at(int x_pos, int page, int dir)
{
    CPU6502State save_cpu = g_cpu;
    uint8_t save_scratch[6];
    uint8_t save_x = g_ram[Player_X_Position];
    uint8_t save_page = g_ram[Player_PageLoc];
    uint8_t base = block_adder_index();
    uint8_t py = g_ram[Player_Y_Position];
    int solid = 0;

    memcpy(save_scratch, &g_ram[0x02], sizeof save_scratch);

    g_ram[Player_X_Position] = (uint8_t)(x_pos & 0xFF);
    g_ram[Player_PageLoc]    = (uint8_t)page;

    /* DoPlayerSideCheck's own screen-margin guards: the upper-body probe only
     * runs for Y in [$20,$E4) (smb.asm:11976-11979), the lower-body probe for
     * [$08,$D0) (smb.asm:11988-11991). Probing outside them would invent
     * walls in the status bar and below the pit line. */
    if (py >= 0x20 && py < 0xE4) {
        uint8_t tile;
        g_cpu.Y = (uint8_t)(base + (dir < 0 ? 3 : 5));
        BlockBufferColli_Side();
        tile = settle_orphaned_blank_metatile(g_cpu.A);
        g_cpu.A = tile;
        if (side_tile_is_wall(tile, 1)) solid = 1;
    }
    if (!solid && py >= 0x08 && py < 0xD0) {
        uint8_t tile;
        g_cpu.Y = (uint8_t)(base + (dir < 0 ? 4 : 6));
        BlockBufferColli_Side();
        tile = settle_orphaned_blank_metatile(g_cpu.A);
        g_cpu.A = tile;
        if (side_tile_is_wall(tile, 0)) solid = 1;
    }

    memcpy(&g_ram[0x02], save_scratch, sizeof save_scratch);
    g_ram[Player_X_Position] = save_x;
    g_ram[Player_PageLoc]    = save_page;
    g_cpu = save_cpu;
    return solid;
}

/* A two-tile-high tunnel can begin one tile below the platform Falcon is
 * standing on. At the lip, a purely horizontal Big-Mario probe sees the roof
 * before SMB1 has had a frame to discover the lower floor, so movement locks
 * even though the adjacent cavity has a valid 32px opening. Admit only the
 * exact one-tile controlled descent: the lowered Big profile must have clear
 * head and side probes and at least one solid foot probe. SMB1 may put Falcon
 * into Fall on the next frame if the other foot is unsupported; that is the
 * intended step-down, not an invented standing platform. This never grants
 * passage through a 16px tunnel. */
static int smb1_can_step_down_one_tile(int x_pos, int page, int dir)
{
    uint8_t save_y = g_ram[Player_Y_Position];
    int down_y;
    int clear;

    if (!s_profile || !s_profile->allow_one_tile_step_down ||
        g_ram[Player_State] != 0 || g_ram[Player_Y_HighPos] != 1 ||
        save_y >= 0xBF)
        return 0;

    down_y = (int)save_y + 16;
    g_ram[Player_Y_Position] = (uint8_t)down_y;
    clear = !smb1_side_solid_at(x_pos, page, dir) &&
            !smb1_solid_at(down_y, 0, 0) &&
             smb1_solid_at(down_y, 1, 0);
    g_ram[Player_Y_Position] = save_y;
    return clear;
}

static ForeignOwnership decide_ownership(void)
{
    if (!s_enabled || !s_selected) return FOREIGN_OWNERSHIP_NATIVE;

    if (g_ram[OperMode] != SMB1_OPER_MODE_GAME)
        return FOREIGN_OWNERSHIP_SCRIPTED;

    /* Anything but ordinary play is a scripted sequence -- pipes, flagpole,
     * death, entrance autowalk, powerup transitions. Hand control back
     * rather than blanket-suppressing SMB1's player update. */
    if (g_ram[GameEngineSubroutine] != SMB1_GAMEMODE_PLAYER_CTRL)
        return FOREIGN_OWNERSHIP_SCRIPTED;

    /*
     * M5: swimming stays native. SSB64 has no swim model, and Player_State 1
     * doubles as jumping AND swimming, so without this gate a water level
     * would be driven as an endless Falcon jump. SwimmingFlag is LEVEL-
     * scoped: its one write site in the whole ROM is Entrance_GameTimerSetup
     * ($9153 STY $0704 = AreaType==0, smb.asm:2794-2797; Ghidra byte-search
     * found no other absolute store), so gating the whole level is exact,
     * not an approximation.
     */
    if (g_ram[SwimmingFlag])
        return FOREIGN_OWNERSHIP_SCRIPTED;

    /*
     * M3: Falcon owns the air too. The state encoding is from the disassembly
     * (PlayerPhysicsSub $B450 compares #$03 for climbing; PlayerBGCollision's
     * SetFallS path stores #$02; InitJS stores #$01):
     *     0 on ground   1 jumping/swimming   2 falling   3 climbing
     * 0..2 are ordinary locomotion and ours; 3 is a vine, a native mode we do
     * not model. An earlier revision asserted 4 = killed; no store of #$04
     * exists in smb.asm (all seven sta Player_State sites checked -- death
     * goes through SetKRout, which stores #$01), and ownership safety never
     * depended on it: GameEngineSubroutine leaves 8 for the whole death
     * sequence and gates first, above.
     */
    if (g_ram[Player_State] > 2) return FOREIGN_OWNERSHIP_SCRIPTED;

    return FOREIGN_OWNERSHIP_FOREIGN;
}

/* ------------------------------------------------------------------ */
/* Input -- digital pad to synthetic analog stick                      */
/* ------------------------------------------------------------------ */

/*
 * A d-pad press moves the synthetic stick 0 -> +/-1.0 in one frame, which the
 * controller reads as a full-deflection fresh stick tap. That makes dash,
 * dash->run, turn, brake, stick-jump and fast fall reachable. Walk is not
 * reachable from neutral -- see
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

    /* Smash's primary attack and special are distinct inputs. On the NES pad,
     * A is the primary attack and B is the special. Jump remains available
     * through Smash's fresh Up-stick path; the jumpsquat hook below masks A
     * from SMB1 so an A normal cannot also trigger Mario's native jump. */
    out->attack_pressed = (pressed & PAD_A) != 0;
    out->jump_pressed = (pressed & PAD_UP) != 0;
    out->jump_held = up;
    out->down_pressed = (pressed & PAD_DOWN) != 0;
    if (pressed & PAD_B) {
        if (left || right || up || down) {
            out->special_pressed = 1;
            s_special_grace_pending = 0;
        } else {
            s_special_grace_pending = 1;
        }
    } else if (s_special_grace_pending) {
        /* The current-frame stick is deliberately sampled here: this is the
         * one-frame grace that turns B->Up/Down into the intended special. */
        out->special_pressed = 1;
        s_special_grace_pending = 0;
    }
    out->raw_buttons  = b;

    s_prev_buttons = b;
}

/* ------------------------------------------------------------------ */
/* Per frame                                                          */
/* ------------------------------------------------------------------ */

/* These ordinary locomotion states can hold or inherit player-controlled speed
 * long enough to outrun the area parser, so their physical movement must stay
 * within the streamer's steady capacity on the ground and in the air. Attack
 * and special root tracks are finite bursts with mandatory recovery; clipping
 * those here breaks their authored terrain reach (notably Falcon Kick) while
 * providing no additional sustained-rate safety. */
static int8_t clamp_xspeed(double smash_units, unsigned state)
{
    double v = source_units_to_px(smash_units) * SMB1_XSPEED_PER_PX;
    const double limit = state_has_trait(
                             state, SMASH64_STATE_TRAIT_STREAM_LIMIT)
                             ? (s_profile
                                    ? s_profile->ordinary_stream_xspeed_limit
                                    : SMB1_STREAM_XSPEED_LIMIT)
                             : SMB1_XSPEED_FIELD_LIMIT;

    if (v >  limit) v =  limit;
    if (v < -limit) v = -limit;
    return (int8_t)((v >= 0.0) ? (v + 0.5) : (v - 0.5));
}

/* Quick Attack is a 330-source-unit/tick source zip (26.4 SMB px/tick) and
 * its second point is 0.9x that. SMB1's area parser can prepare only 4 px of
 * new horizontal world per tick, but its authored 20f aim plus 9f re-aim
 * window gives bounded parser-service credit. A 16px first zip adds 60px of
 * debt across five frames; the window repays 36px, then the 14.4px 0.9x
 * second zip adds 52px. From the required <32px starting debt this remains
 * below ScrollThirtyTwo's $A0 signed hazard and recovery keeps repaying.
 * The 26.4px source value does not satisfy that proof and corrupts columns.
 *
 * Project the whole vector ONCE to the profile's component limit. This retains
 * its exact chosen heading -- cardinal remains cardinal and a 90-degree second
 * point remains a true corner -- unlike independent X/Y clipping. A cardinal
 * point becomes a visibly teleport-like 80px first and 72px second path, not
 * the unsafe source 132/118.8px distance. Effects/presentation may sell the
 * teleport but must never move the collision body farther. */
static void adapt_coupled_burst_to_host(ForeignMoveResult *move,
                                        ForeignState *state)
{
    double max_component_px, scale;
    double limit;

    if (!move || !state)
        return;
    if (!state_has_trait(move->state, SMASH64_STATE_TRAIT_COUPLED_2D_SWEEP)) {
        s_coupled_plan_state = UINT_MAX;
        s_coupled_plan_component_px_limit = 0.0;
        s_coupled_plan_active = 0;
        s_coupled_plan_conservative_chain = 0;
        return;
    }
    if (!s_profile || !s_profile->coupled_burst_plan) return;
    /* The callback is run only on a phase edge. Thus a diagonal's full vector
     * is projected once and remains exactly that heading for every ZIP tick.
     * A migrated old save has conservative_chain set and receives 4px rather
     * than re-evaluating live parser RAM halfway through its source action. */
    if (!s_coupled_plan_active || s_coupled_plan_state != move->state) {
        s_coupled_plan_state = move->state;
        s_coupled_plan_component_px_limit =
            s_coupled_plan_conservative_chain ? 4.0 :
            smash64_fighter_profile_coupled_burst_component_px_limit(
                s_profile, move->state, g_ram[ScrollThirtyTwo]);
        s_coupled_plan_active = 1;
    }
    limit = s_coupled_plan_component_px_limit;
    if (limit <= 0.0) return;
    max_component_px = fabs(source_units_to_px(move->requested_dx));
    if (fabs(source_units_to_px(move->requested_dy)) > max_component_px)
        max_component_px = fabs(source_units_to_px(move->requested_dy));
    if (max_component_px > limit && max_component_px != 0.0) {
        scale = limit / max_component_px;
        /* Do not edit move/state source velocity: controller trace, source
         * action timing, and fighter serializer must all retain 330/297.
         * Only this one-tick host shadow feeds the collision DDA. */
        s_coupled_dx = move->requested_dx * scale;
        s_coupled_dy = move->requested_dy * scale;
    } else {
        s_coupled_dx = move->requested_dx;
        s_coupled_dy = move->requested_dy;
    }
    s_coupled_motion_valid = 1;
}

void game_smash64_update_input(uint64_t frame_count)
{
    ForeignInput fin;
    ForeignMoveResult move;
    ForeignCollisionResult hit;
    ForeignState *fs;
    int wall;

    s_frame = frame_count;
    s_friction_ran = 0;
    if (!s_enabled || !s_selected) return;

    sample_input(&fin);

    /*
     * Publish ownership and tick ONCE per frame, here rather than in the hook,
     * so the trace ring gets a row every frame including while SMB1 owns the
     * player. Handoffs must appear as transitions, not as gaps -- and gaps are
     * what the ring showed before, because the hook only fires from SMB1's own
     * movement path and scripted sequences never reach it.
     */
    {
        ForeignOwnership now = decide_ownership();
        int reseed = 0;

        /*
         * M5: a scripted sequence handing back is a fresh start for the
         * FIGHTER, not just for SMB1. Nothing ticks the controller while
         * ownership is SCRIPTED, so vel_ground_x, the move state and every
         * mid-gesture buffer (kneebend, turn, stick-tap) freeze at whatever
         * they held when ownership left -- a dash frozen into a pipe would
         * come out of the far end as a full-speed phantom dash SMB1 never
         * asked for. (The death edge happens to self-heal because resolve
         * keeps running during the animation and routes through a landing
         * that zeroes velocity -- measured, frame 649 of the death-edge
         * trace -- but that is an accident of that one sequence, not a
         * contract.) nes_foreign_select's own contract is a full reset, so
         * re-selecting is the reseed; the adapter's own accumulators
         * describe trajectories from before the sequence and go with it.
         * SMB1 normalizes facing itself on every re-entry (PlayerRdy,
         * smb.asm:5480-5483, forces PlayerFacingDir = 1), matching the
         * reset's facing default.
         */
        if (s_prev_ownership == FOREIGN_OWNERSHIP_SCRIPTED &&
            now == FOREIGN_OWNERSHIP_FOREIGN) {
            nes_foreign_select(s_controller_id);
            s_y_sub = 0.0;
            s_x_sub = 0.0;
            s_wrote_x_valid = 0;
            s_wrote_y_valid = 0;
            s_wrote_yspeed_valid = 0;
            s_pending_external_dy = 0.0;
            s_contact_pending = 0;
            s_special_grace_pending = 0;
            s_forced_airborne_pending = 0;
            s_forced_airborne_frames = 0;
            reseed = 1;
        }
        s_prev_ownership = now;
        nes_foreign_set_ownership(now);
        if (now != FOREIGN_OWNERSHIP_FOREIGN) {
            /* Never let a pending foreign departure mutate a pipe, flagpole,
             * death, or other native/scripted handoff even for one frame. */
            s_forced_airborne_pending = 0;
            s_forced_airborne_frames = 0;
            s_special_grace_pending = 0;
            s_pending_external_dy = 0.0;
            smash64_actions_clear();
            game_smash64_sync_persistent_audio();
        }
        s_reseed_this_frame = reseed;
    }

    fs = nes_foreign_state();
    if (fs) {
        /*
         * SMB1 is the authority on standing on ground, and on how we left it.
         * InitJS ($B4A0) stores Player_State = 1 only after an A-press check,
         * so 1 is a deliberate launch; PlayerBGCollision's SetFallS path stores
         * 2 when the floor stops being there. That distinction cannot be
         * recovered from `grounded`, and it cannot be guessed from the pad
         * either -- we sample input at VBlank, one frame before SMB1 acts on it.
         */
        uint8_t pstate = g_ram[Player_State];

        /*
         * A foreign move's departure request is an EDGE, but SMB1 cannot
         * represent the source animation's subpixel lift-off: until at least
         * one whole NES pixel has accumulated, PlayerBGCollision sees the
         * fighter's feet on the floor and writes Player_State=0 again. Keep
         * presenting the already-authorized falling state to the host until
         * move_player_vertically_hook actually integrates that first pixel.
         * This is adapter-side quantization bridging, not a repeated
         * controller request; the trace therefore still exposes one edge.
         */
        if (s_forced_airborne_pending && pstate == 0) {
            pstate = 2;
            g_ram[Player_State] = 2;
        }

        /* A wall-bound Falcon Kick can press against the adapter's gameplay-
         * top ceiling with its feet aligned to the underside roof row. SMB1
         * mistakes that alignment for a floor and reports grounded, which
         * would cancel Bound before its authentic root track turns downward.
         * Keep only this screen-edge frame airborne; once Y moves below $20,
         * ordinary host grounding regains authority immediately. */
        if (state_has_trait(fs->state,
                            SMASH64_STATE_TRAIT_KEEP_AIRBORNE_AT_TOP) &&
            g_ram[Player_Y_HighPos] == 1 &&
            g_ram[Player_Y_Position] <= 0x20 && pstate == 0) {
            pstate = 2;
            g_ram[Player_State] = 2;
        }

        fs->grounded = (pstate == 0);
        fs->air_cause = (pstate == 1) ? FOREIGN_AIR_LAUNCHED
                      : (pstate == 2) ? FOREIGN_AIR_FELL
                                      : FOREIGN_AIR_NONE;
    }

    /* The per-pixel horizontal sweep is the wall authority. The former
     * X-speed/SideCollisionTimer inference was deliberately removed after
     * sustained agreement coverage: it was one frame late and could keep a
     * stale timer classified as a fresh wall. The exact position readback
     * below remains, because it reconciles any native ejection SMB1 performs
     * after the hook (notably inside a one-tile concavity). */
    wall = s_x_swept_wall;

    memset(&move, 0, sizeof(move));
    s_coupled_motion_valid = 0;
    if (nes_foreign_tick(frame_count, &fin, &move)) {
        adapt_coupled_burst_to_host(&move, fs);
        game_smash64_audio_play_events(&move.audio, frame_count);
        s_attack = move.attack;
        {
            double action_facing = (fs && fs->facing < 0.0f) ? -1.0 : 1.0;
            /* Pikachu's rendered LR is mirrored at the SMB seam. Ordinary
             * action offsets/velocities use that screen-space convention;
             * source-preoriented projectiles opt out per event flag. */
            if (selected_controller_is_pikachu()) action_facing = -action_facing;
            smash64_actions_apply_commands(
                &move.actions, (double)player_native_x() + 8.0,
                (double)g_ram[Player_Y_Position] + 32.0, action_facing,
                s_profile ? s_profile->units_to_smb_px : 0.08,
                action_resolve_attachment);
        }
        game_smash64_sync_persistent_audio();
        if (move.force_airborne && !s_forced_airborne_pending) {
            /* Generic controller-to-host departure handshake. SetFallS
             * ($DC82) writes Player_State=2 for SMB1's native falling state;
             * Ghidra confirms `LDA #$02; STA $001D` at $DC82-$DC84. A move
             * such as Falcon Kick's wall rebound leads for one tick, just as
             * the jumpsquat LAUNCH handshake leads SMB's jump trigger. */
            g_ram[Player_State] = 2;
            if (fs) {
                fs->grounded = 0;
                fs->air_cause = FOREIGN_AIR_NONE;
            }
            s_forced_airborne_pending = 1;
            s_forced_airborne_frames = 0;
            s_pending_flags |= SMASH64_CF_FORCE_AIRBORNE;
        }
        if (s_forced_airborne_pending &&
            ++s_forced_airborne_frames > 16) {
            /* Malformed controllers must not pin SMB1 airborne forever. */
            s_forced_airborne_pending = 0;
            s_forced_airborne_frames = 0;
        }
        if (wall) {
            move.requested_dx = 0.0;
            s_wall_frames++;
        }
        s_xspeed = clamp_xspeed(move.requested_dx, move.state);
        s_owned_frames++;
    } else {
        memset(&s_attack, 0, sizeof(s_attack));
        s_contact_pending = 0;
        s_special_grace_pending = 0;
        s_pending_external_dy = 0.0;
        s_forced_airborne_pending = 0;
        s_forced_airborne_frames = 0;
        smash64_actions_clear();
        game_smash64_sync_persistent_audio();
        /* SMB1 owns the player; keep our idea of velocity in step with it so
         * resuming control does not inject a stale speed. */
        s_xspeed = (int8_t)g_ram[Player_X_Speed];

        /*
         * And drop the pending vertical-event readback. On the frame ownership
         * hands back, SMB1's own integrator writes Player_Y_Speed for perfectly
         * ordinary reasons, which would otherwise read as an imposed impulse
         * and inject a velocity into the controller in the middle of a pipe,
         * a death or a powerup.
         */
        s_wrote_yspeed_valid = 0;
        s_wrote_y_valid = 0;
    }

    /* The tick above pushed this frame's ring row; stamp it now if this was
     * the reseed edge. */
    if (s_reseed_this_frame) {
        nes_foreign_trace_note_reseed();
        s_reseed_this_frame = 0;
    }

    /*
     * Vertical readback -- the exact twin of the horizontal wall check above,
     * and needed for the same reason. PlayerBGCollision runs after
     * MovePlayerVertically and corrects the 16-bit player Y when it hits
     * something, so comparing what we wrote last frame against what is there
     * now tells us whether SMB1 accepted the motion.
     *
     * Without this, running into the underside of the 1-1 brick row left Falcon
     * pressing upward into it for three frames at +32 units/frame while SMB1
     * silently clamped him: the pixels were right but the controller believed it
     * was still rising, which is the same class of mistake as the wall the
     * player could tunnel through before the horizontal check existed.
     */
    memset(&hit, 0, sizeof(hit));
    hit.actual_dx = move.requested_dx;
    hit.grounded = (g_ram[Player_State] == 0);
    hit.hit_wall = wall;

    /*
     * The LAUNCH frame is the mirror image of the handoff frame, and it needs
     * the opposite courtesy.
     *
     * Normally SMB1 leads and the controller follows a frame later. On the
     * frame Falcon's own jumpsquat ends, the controller LEADS: it left the
     * ground at VBlank, and SMB1 will not set Player_State = 1 until it runs
     * InitJS later in this same frame. So Player_State still reads 0 here, and
     * reporting that as `grounded` makes falcon_resolve conclude he landed --
     * enter_landing, one frame later the reconciliation branch sees a ground
     * state with the host saying airborne, and re-launches him at the FULL hop
     * velocity.
     *
     * Measured: a 2-frame tap took off at vy 65.60 (the short-hop force) and
     * was overwritten to 97.60 (the full-hop force) on the very next frame, so
     * every short hop silently became a full hop while the trace's takeoff row
     * still looked correct.
     *
     * The controller has just told us it is airborne. Believe it for this one
     * frame; SMB1 confirms on the next.
     */
    if (fs && fs->jump_phase == FOREIGN_JUMP_LAUNCH) hit.grounded = 0;

    /*
     * Vertical EVENT readback -- the velocity-level twin of the position
     * readback below, and the more important of the two.
     *
     * SMB1 does not only block vertical motion; it LAUNCHES the player, and it
     * signals every such event the same way: by storing a new Player_Y_Speed
     * and expecting ImposeGravity to pick it up next frame. Decoded from the
     * ROM, the writers are
     *
     *   $01  head hit a block, "kill jump"      ($DBD1 area, and NYSpd $DE87)
     *   $FD  stomped an enemy -- bounce         (EnemyStomped)
     *   $FC  bounce off a stomped enemy / death (SBnce)
     *   $FE  shattered a brick                  (BrickShatter)
     *        jumpspring force                   (JumpspringHandler)
     *
     * We skip MovePlayerVertically, so nothing ever consumed any of them. That
     * one omission is why Falcon sailed straight through the underside of a
     * question block and why stomping an enemy produced no bounce -- both
     * reported by the owner in the first playtest, and both the same bug.
     *
     * The position readback below cannot substitute. A killed jump changes only
     * the velocity: SMB1 leaves the position exactly where we put it, so the
     * position diff sees nothing at all.
     *
     * Rule: if Player_Y_Speed is not the value the hook wrote, SMB1 overruled
     * us. Adopt it. One rule covers bounce, spring, brick and ceiling, because
     * SMB1 expresses all four in the same byte.
     */
    if (s_wrote_yspeed_valid) {
        int8_t now_ys = (int8_t)g_ram[Player_Y_Speed];

        if (now_ys != s_wrote_yspeed) {
            /* SMB1's Y grows downward and is in whole px/frame; Falcon's is
             * +up in his own units. The one scale constant undoes both. */
            hit.has_imposed_vy = 1;
            hit.imposed_vy = smb_px_to_source_units(-(double)now_ys);
            s_imposed_frames++;

            /*
             * We were rising and SMB1 replaced our upward speed with something
             * that is not upward: it stopped the jump against something solid.
             * Report a ceiling so the ring and the controller see the
             * COLLISION and not merely a number.
             *
             * The test is >= 0, not > 0, because SMB1 expresses a block bump as
             * Player_Y_Speed = 0 (PlayerHeadCollision, smb.asm:7252) and only
             * a solid-tile stop as $01. Testing > 0 missed the commonest case
             * of all -- measured: bumping a ? block gave imposed 0.00 with
             * hit_ceiling 0, which read as "nothing happened" in the ring even
             * though the bump had been applied correctly.
             */
            if (now_ys >= 0 && s_wrote_dy_px < 0.0) hit.hit_ceiling = 1;

            /* Our subpixel remainder describes a trajectory SMB1 has replaced. */
            s_y_sub = 0.0;
        }
        s_wrote_yspeed_valid = 0;
    }

    if (s_wrote_y_valid) {
        int now_y = ((int)(int8_t)g_ram[Player_Y_HighPos] * 256) +
                    (int)g_ram[Player_Y_Position];

        if (now_y != s_wrote_y) {
            if (s_wrote_dy_px < 0.0)      hit.hit_ceiling = 1;
            else if (s_wrote_dy_px > 0.0) hit.hit_floor = 1;
            /* Our subpixel remainder describes a position SMB1 has overruled. */
            s_y_sub = 0.0;
        }

        /* Back into the controller's units and sign: SMB1's Y grows downward,
         * Falcon's grows upward, and the one scale constant undoes the
         * projection the hook applied. */
        hit.actual_dy = smb_px_to_source_units(
            -(double)(now_y - s_y_before));
        s_wrote_y_valid = 0;
    }

    /*
     * Horizontal position readback -- the X twin of the block above. SMB1's
     * DoPlayerSideCheck runs after the horizontal hook and ejects the player
     * one pixel off a wall it objects to (ImpedePlayerMove $DF77), so a
     * position that moved under us is SMB1 refusing the parked contact.
     * Same sign both sides, so no negation: SMB1's X and Falcon's X both
     * grow rightward.
     */
    if (s_wrote_x_valid) {
        int now_x = (int)player_native_x();

        if (now_x != s_wrote_x) {
            hit.hit_wall = 1;
            s_x_sub = 0.0;
        }
        hit.actual_dx = smb_px_to_source_units(
            (double)(now_x - s_x_before));
        s_wrote_x_valid = 0;
    }

    /* The horizontal step-down adapter changes native Y after this frame's
     * controller tick. Reconcile that host-authored displacement on the next
     * resolve so Falcon's portable position cannot remain one tile above his
     * rendered/native body. This is additive to any ordinary vertical
     * readback that happened on the same frame. */
    if (s_pending_external_dy != 0.0) {
        hit.actual_dy += s_pending_external_dy;
        s_pending_external_dy = 0.0;
    }

    /*
     * M4 step 1 -- OBSERVE before changing the movement path.
     *
     * Ask SMB1's own block buffer whether the position we just wrote is inside
     * solid geometry. This changes nothing; it only records a verdict in the
     * ring, and it answers a question the existing columns cannot: hit_ceiling
     * says "SMB1 pushed back", which is silent both when SMB1 never noticed and
     * when it noticed in a way we failed to read. HEAD_IN_SOLID says "he is in
     * the wall right now", which is the actual clipping symptom.
     *
     * Cheap enough to run unconditionally: two block-buffer lookups per frame,
     * only while Falcon owns the player.
     */
    /*
     * Overlap verdict, measured INSIDE the hook rather than here.
     *
     * It used to be sampled at this point, which is a different instant in the
     * frame from the sweep: the screen scrolls between the two, and the block
     * buffer is indexed off the player's screen position, so the same Y could
     * answer differently in the two places. That produced a genuinely
     * contradictory trace -- a frame flagged both SWEPT_RAN and HEAD_IN_SOLID,
     * i.e. "the sweep stepped and found nothing solid, and the position it
     * chose is solid". Both readings were honest; they were of different
     * moments. Now the sweep and the overlap check see one instant.
     */
    hit.flags |= s_pending_flags;
    s_pending_flags = 0;
    hit.attack_connected = s_contact_pending;
    s_contact_pending = 0;
    smash64_actions_drain_feedback(&hit.action_feedback);

    /*
     * The sweep's own verdict, independent of whether SMB1 chose to react.
     *
     * This is the part that does not depend on the game noticing: the position
     * we wrote is never inside geometry, whatever SMB1's once-per-frame gates
     * decide. If SMB1 also reacts, its Player_Y_Speed lands via the imposed_vy
     * path above and is the more specific answer; this only ensures the
     * controller is told it stopped.
     */
    if (s_swept_block == SMASH64_SWEEP_CEILING) {
        hit.hit_ceiling = 1;
        hit.flags |= SMASH64_CF_SWEPT_CEILING;
    } else if (s_swept_block == SMASH64_SWEEP_FLOOR) {
        hit.hit_floor = 1;
        hit.flags |= SMASH64_CF_SWEPT_FLOOR;
    }
    if (s_swept_ran) hit.flags |= SMASH64_CF_SWEPT_RAN;
    s_swept_block = SMASH64_SWEEP_NONE;
    s_swept_ran = 0;
    s_pending_flags = 0;

    /* Horizontal drain -- same lifecycle as the vertical bits above. */
    if (s_x_swept_wall) {
        hit.hit_wall = 1;
        hit.flags |= SMASH64_CF_SWEPT_WALL;
    }
    if (s_x_swept_ran) hit.flags |= SMASH64_CF_SIDE_SWEPT_RAN;
    s_x_swept_wall = 0;
    s_x_swept_ran = 0;

    nes_foreign_resolve(&hit);
    if (hit.attack_connected) {
        /* Tick runs before resolve, so its move result still describes the
         * launch state on the frame resolve enters Catch. Do not let that
         * pre-resolve catch volume survive into the following guest hook. */
        memset(&s_attack, 0, sizeof(s_attack));
    }
}

/*
 * Replaces ImposeFriction ($B5CC) while Falcon owns the player.
 *
 * Returning 1 skips SMB1's own friction/acceleration, so the velocity we
 * write survives to the horizontal hook at $BF09, which integrates it with
 * the per-pixel sweep (M4). Returning 0 runs the original unchanged.
 */
static void write_xspeed(int8_t xspeed)
{
    /* The two bytes ImposeFriction itself writes. Player_XSpeedAbsolute is not
     * decoration: $B51C reads it to pick the speed tier and $B4BB reads it to
     * scale jump height, so leaving it stale would make Falcon jump like a
     * walking Mario. */
    g_ram[Player_X_Speed] = (uint8_t)xspeed;
    g_ram[Player_XSpeedAbsolute] =
        (uint8_t)((xspeed < 0) ? -(int)xspeed : (int)xspeed);
}

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

    write_xspeed(xspeed);
    s_friction_ran = 1;

    nes_foreign_trace_note_native(player_native_x(),
                                  (int32_t)g_ram[Player_Y_Position]);
    return 1;
}

/*
 * Replaces MovePlayerVertically ($BF4D) while Falcon owns the player.
 *
 * Integrates Falcon's vertical velocity into SMB1's 16-bit player Y
 * (Player_Y_HighPos:Player_Y_Position) with no speed clamp, keeping the
 * subpixel remainder host-side rather than contending for SMB1's fraction
 * bytes. Returns 1 to skip SMB1's own integrator and its 4px/frame cap.
 */
static int move_player_vertically_hook(uint16_t addr)
{
    const ForeignState *fs;
    double dy_px;
    int whole;
    int pos, high;

    (void)addr;

    if (decide_ownership() != FOREIGN_OWNERSHIP_FOREIGN) return 0;

    fs = nes_foreign_state();
    if (!fs) return 0;

    /* Quick Attack's horizontal hook has already advanced both axes through
     * one coupled <=1px DDA. Do not integrate Y a second time here. We still
     * publish the corresponding native Y speed because PlayerBGCollision and
     * the next-frame imposed-velocity readback consume that byte. */
    if (state_has_trait(fs->state,
                        SMASH64_STATE_TRAIT_COUPLED_2D_SWEEP) &&
        s_wrote_y_valid) {
        double coupled_dy_px = s_coupled_motion_valid
            ? source_units_to_px(-s_coupled_dy)
            : source_units_to_px(-(fs->vy));
        int ys = (int)((coupled_dy_px >= 0.0)
                           ? (coupled_dy_px + 0.5)
                           : (coupled_dy_px - 0.5));
        if (s_swept_block == SMASH64_SWEEP_CEILING &&
            state_has_trait(
                fs->state,
                SMASH64_STATE_TRAIT_SUPPRESS_UPWARD_SPEED_ON_CEILING))
            ys = 1;
        if (ys > 127) ys = 127;
        if (ys < -128) ys = -128;
        g_ram[Player_Y_Speed] = (uint8_t)(int8_t)ys;
        s_wrote_yspeed = (int8_t)ys;
        s_wrote_yspeed_valid = 1;
        if (!s_friction_ran) write_xspeed(s_xspeed);
        nes_foreign_trace_note_native(player_native_x(),
                                      (int32_t)g_ram[Player_Y_Position]);
        s_air_frames++;
        return 1;
    }

    /*
     * The handoff frame belongs to SMB1.
     *
     * SMB1 decides to jump DURING the frame -- InitJS ($B4A0), inside
     * PlayerPhysicsSub -- but the controller ticks at VBlank, BEFORE the frame.
     * So on the very frame the host launches, Falcon is still in jumpsquat with
     * vel_air_y = 0. Integrating that moves the player zero pixels, and SMB1's
     * foot check lands him again on the spot: measured, the jump simply did not
     * happen, and the trace showed one JUMP_F frame followed straight by
     * LANDING_LIGHT.
     *
     * Running the original for that one frame costs the difference between
     * SMB1's -5 px and Falcon's -6.7 px, once. By the next VBlank Player_State
     * is 1, the controller reconciles into a real jump, and every frame after
     * this one is ours. The same guard covers walking off a ledge.
     */
    if (fs->grounded) return 0;

    /* Falcon's vel_air_y is +UP in his own units; SMB1's Y grows DOWNWARD. */
    dy_px = source_units_to_px(-(fs->vy));

    s_y_sub += dy_px;
    whole = (int)s_y_sub;          /* truncate toward zero, either sign */
    s_y_sub -= (double)whole;

    pos  = (int)g_ram[Player_Y_Position];
    high = (int8_t)g_ram[Player_Y_HighPos];
    s_y_before = (high * 256) + pos;

    /*
     * M4 step 2 -- walk the motion one pixel at a time against SMB1's own
     * tiles instead of teleporting the whole delta.
     *
     * WHY ONE PIXEL, AND WHY STOP *AT* THE BLOCKED POSITION RATHER THAN
     * BEFORE IT. SMB1 resolves its own vertical collisions, and both of its
     * checks are gated on how far INTO a metatile the player is:
     *
     *   DoFootCheck  ldy $04 / cpy #$05 / bcc LandPlyr   -- lands only when
     *                the coordinate's low nybble is < 5
     *   HeadChk      ldy $04 / cpy #$04 / bcc DoFootCheck -- bumps only when
     *                it is >= 4
     *
     * The adders (BlockBuffer_Y_Adder $E3D1) are +32 for the feet and +4 for
     * the head, so the feet cross into a new tile row exactly when
     * Y = 0 (mod 16) and the head when Y = 12 (mod 16). Those are precisely
     * the coordinates at which the two gates above fire. Stepping one pixel
     * and stopping on the first solid probe therefore parks the player on the
     * coordinate SMB1 is looking for -- the sweep FEEDS the game's own
     * collision rather than replacing it.
     *
     * Stopping one pixel SHORT instead would be worse than doing nothing: the
     * feet would never enter the floor tile, LandPlyr would never run, and the
     * player would hover a pixel above the ground forever.
     *
     * Only the leading edge is probed -- feet when descending, head when
     * rising -- because that is the edge SMB1 itself tests for that direction.
     */
    {
        int step = (whole > 0) ? 1 : -1;
        int left = (whole >= 0) ? whole : -whole;
        int feet = (whole > 0);

        while (left-- > 0) {
            int cand = pos + step;
            int cand_hi = high;

            s_swept_ran = 1;

            while (cand < 0)   { cand += 256; cand_hi -= 1; }
            while (cand > 255) { cand -= 256; cand_hi += 1; }

            /* Wall-bound Falcon Kick has very large upward authored root
             * deltas and previously wrapped through the HUD forever. Contain
             * that hazardous special only. Ordinary jumps and Dive must keep
             * SMB1's native high-byte-0 representation: World 1-2 deliberately
             * routes the player above the ceiling to its hidden warp zone. */
            if (!feet && state_has_trait(
                             fs->state,
                             SMASH64_STATE_TRAIT_CLAMP_AT_GAMEPLAY_TOP) &&
                (cand_hi < 1 || (cand_hi == 1 && cand < 0x20))) {
                pos = 0x20;
                high = 1;
                s_swept_block = SMASH64_SWEEP_CEILING;
                if (!s_sweep_noblock) break;
            }

            /*
             * Mirror SMB1's own "don't even look" guards, so we never invent a
             * collision where the game has none. Getting this wrong would be
             * catastrophic in the obvious way: a pit must stay fatal.
             *   DoFootCheck skips entirely at Y >= $CF (smb.asm:11916)
             *   HeadChk skips below PlayerBGUpperExtent, $20 big / $10 small.
             * Falcon's stable profile is always the Big $20 extent.
             */
            {
                int dive_head_barrier = !feet && state_has_trait(
                    fs->state, SMASH64_STATE_TRAIT_HEAD_BUMP_BARRIER);
                if (cand_hi == 1 &&
                    (feet ? (cand < 0xCF)
                          : (cand >= (s_profile
                                         ? s_profile->head_upper_extent
                                         : 0x20))) &&
                    smb1_solid_at(cand, feet, dive_head_barrier)) {
                    /* Ordinary contact parks at the first blocked coordinate
                     * so SMB1's alignment-gated collision can resolve it.
                     * Dive deliberately suppresses native HeadChk to avoid a
                     * bump/shatter transaction, so it must stay one pixel
                     * BEFORE the barrier or repeated root deltas creep through
                     * it one pixel per frame. */
                    if (!dive_head_barrier) {
                        pos = cand;
                        high = cand_hi;
                    }
                    s_swept_block = feet ? SMASH64_SWEEP_FLOOR
                                         : SMASH64_SWEEP_CEILING;
                    /* Diagnostic mode records the would-have-blocked position
                     * in the ring but lets the motion run to the full delta. */
                    if (!s_sweep_noblock) break;
                }
            }

            pos = cand;
            high = cand_hi;
        }
    }

    g_ram[Player_Y_Position] = (uint8_t)pos;
    g_ram[Player_Y_HighPos]  = (uint8_t)(int8_t)high;

    /* The first successful representable UPWARD step completes the adapter
     * bridge. Do this after the sweep: a downward pixel or an upward request
     * parked against a ceiling is not a departure. The state already written
     * for this guest frame remains airborne; next VBlank samples the genuinely
     * separated position, allowing a later real landing to win normally. */
    if (s_forced_airborne_pending && whole < 0 &&
        ((high * 256) + pos) < s_y_before &&
        s_swept_block != SMASH64_SWEEP_CEILING) {
        s_forced_airborne_pending = 0;
        s_forced_airborne_frames = 0;
    }

    /* Did we end the frame inside geometry? Measured here, at the same instant
     * as the sweep above, so the two can never contradict each other. */
    if (high == 1) {
        if (smb1_solid_at(pos, 0, 0))
            s_pending_flags |= SMASH64_CF_HEAD_IN_SOLID;
        if (smb1_solid_at(pos, 1, 0))
            s_pending_flags |= SMASH64_CF_FEET_IN_SOLID;
    }

    /* Remember what we wrote so next frame can tell whether SMB1 kept it. */
    s_wrote_y = (high * 256) + pos;
    s_wrote_y_valid = 1;
    s_wrote_dy_px = dy_px;

    /* Keep SMB1's own view of vertical velocity consistent: collision bias,
     * the landing/heavy-landing check and the player graphics handler all read
     * Player_Y_Speed, and a stale value makes them disagree with the motion. */
    {
        int ys = (int)((dy_px >= 0.0) ? (dy_px + 0.5) : (dy_px - 0.5));
        /* The sweep already stopped Falcon Dive at this ceiling. Publishing
         * its still-negative authored speed would make native HeadChk enter
         * PlayerHeadCollision, bumping or shattering $51/$52 according to the
         * hidden Mario size and creating the illusion that Up-B phases through
         * blocks. A small non-upward value preserves the solid tile while
         * resolve receives hit_ceiling. */
        if (s_swept_block == SMASH64_SWEEP_CEILING &&
            state_has_trait(
                fs->state,
                SMASH64_STATE_TRAIT_SUPPRESS_UPWARD_SPEED_ON_CEILING))
            ys = 1;
        if (ys >  127) ys =  127;
        if (ys < -128) ys = -128;
        g_ram[Player_Y_Speed] = (uint8_t)(int8_t)ys;
        /* Remember it, so next frame can tell OUR value apart from one SMB1
         * stored to signal a bounce, a spring or a killed jump. */
        s_wrote_yspeed = (int8_t)ys;
        s_wrote_yspeed_valid = 1;
    }

    /*
     * SMB1 only calls ImposeFriction from LRAir when a direction is held
     * (Left_Right_Buttons != 0), so on a neutral airborne frame our horizontal
     * velocity would never reach the guest. That matters because Falcon's jump
     * sets vel_air_x from the stick -- a neutral jump is supposed to drop your
     * running momentum -- and without this the guest would keep the run speed
     * until the next frame the stick was touched, then snap.
     *
     * MovePlayerVertically is the tail of the airborne path, so this lands one
     * frame after MovePlayerHorizontally read the byte. One frame of lag on
     * neutral air drift; the alternative is writing outside the game's own
     * player-movement window, which is the thing we do not do.
     */
    if (!s_friction_ran) write_xspeed(s_xspeed);

    /*
     * Record the native coordinates here too, not only from the friction hook.
     * SMB1 calls ImposeFriction from LRAir only when a direction is held, so on
     * a neutral airborne frame nothing noted them and native_y stayed 0 for the
     * whole flight -- which is exactly the column you need to compare a short
     * hop's peak against a full hop's. Post-write, so the row carries the Y the
     * game actually ended up with.
     */
    nes_foreign_trace_note_native(player_native_x(),
                                  (int32_t)g_ram[Player_Y_Position]);

    s_air_frames++;
    return 1;
}

/* Integrate a diagonal root burst as one path, not as a horizontal move
 * followed by a vertical move. The latter is individually swept but traces an
 * L shape and can cut around a one-pixel tile corner. This DDA advances at
 * most one native pixel on either axis per probe, asks the same SMB1 side and
 * head/foot predicates as the ordinary hooks at the COMBINED candidate, and
 * stops before the first rejected candidate. */
static int move_player_coupled_2d(const ForeignState *fs)
{
    double dx_px, dy_px;
    int whole_x, whole_y, steps, i;
    int done_x = 0, done_y = 0;
    int pos, page, y_pos, y_high;

    if (!fs) return 0;

    dx_px = s_coupled_motion_valid
        ? source_units_to_px(s_coupled_dx)
        : (double)(int8_t)g_ram[Player_X_Speed] / SMB1_XSPEED_PER_PX;
    dy_px = s_coupled_motion_valid
        ? source_units_to_px(-s_coupled_dy)
        : source_units_to_px(-(fs->vy));
    s_x_before = (int)player_native_x();
    s_y_before = ((int)(int8_t)g_ram[Player_Y_HighPos] * 256) +
                 (int)g_ram[Player_Y_Position];

    s_x_sub += dx_px;
    whole_x = (int)s_x_sub;
    s_x_sub -= (double)whole_x;
    s_y_sub += dy_px;
    whole_y = (int)s_y_sub;
    s_y_sub -= (double)whole_y;

    steps = abs(whole_x);
    if (abs(whole_y) > steps) steps = abs(whole_y);
    pos = (int)g_ram[Player_X_Position];
    page = (int)g_ram[Player_PageLoc];
    y_pos = (int)g_ram[Player_Y_Position];
    y_high = (int8_t)g_ram[Player_Y_HighPos];

    for (i = 1; i <= steps; ++i) {
        const int want_x = (whole_x * i) / steps;
        const int want_y = (whole_y * i) / steps;
        const int step_x = want_x - done_x;
        const int step_y = want_y - done_y;
        int cand_x = pos + step_x;
        int cand_page = page;
        int cand_y = y_pos + step_y;
        int cand_high = y_high;
        int wall = 0, vertical = 0;

        while (cand_x < 0) { cand_x += 256; cand_page -= 1; }
        while (cand_x > 255) { cand_x -= 256; cand_page += 1; }
        while (cand_y < 0) { cand_y += 256; cand_high -= 1; }
        while (cand_y > 255) { cand_y -= 256; cand_high += 1; }

        /* Both predicates read the other axis from player RAM. Present the
         * combined candidate for the duration of the read-only queries. */
        g_ram[Player_X_Position] = (uint8_t)cand_x;
        g_ram[Player_PageLoc] = (uint8_t)cand_page;
        g_ram[Player_Y_Position] = (uint8_t)cand_y;
        g_ram[Player_Y_HighPos] = (uint8_t)(int8_t)cand_high;

        if (step_x != 0 && cand_page >= 0 && cand_high == 1) {
            s_x_swept_ran = 1;
            wall = smb1_side_solid_at(cand_x, cand_page, step_x);
        }
        if (step_y != 0 && cand_high == 1) {
            const int feet = step_y > 0;
            const int within_native_extent = feet
                ? cand_y < 0xCF
                : cand_y >= (s_profile ? s_profile->head_upper_extent
                                       : 0x20);
            s_swept_ran = 1;
            if (within_native_extent)
                vertical = smb1_solid_at(
                    cand_y, feet,
                    !feet && state_has_trait(
                        fs->state,
                        SMASH64_STATE_TRAIT_HEAD_BUMP_BARRIER));
        }

        /* Queries restore only the coordinate they temporarily own. Restore
         * the last accepted full position before deciding this candidate. */
        g_ram[Player_X_Position] = (uint8_t)pos;
        g_ram[Player_PageLoc] = (uint8_t)page;
        g_ram[Player_Y_Position] = (uint8_t)y_pos;
        g_ram[Player_Y_HighPos] = (uint8_t)(int8_t)y_high;

        if (wall || vertical) {
            if (wall) s_x_swept_wall = 1;
            if (vertical)
                s_swept_block = step_y > 0 ? SMASH64_SWEEP_FLOOR
                                           : SMASH64_SWEEP_CEILING;
            if (!s_sweep_noblock) {
                s_x_sub = 0.0;
                s_y_sub = 0.0;
                break;
            }
        }

        pos = cand_x;
        page = cand_page;
        y_pos = cand_y;
        y_high = cand_high;
        done_x = want_x;
        done_y = want_y;
    }

    g_ram[Player_X_Position] = (uint8_t)pos;
    g_ram[Player_PageLoc] = (uint8_t)page;
    g_ram[Player_Y_Position] = (uint8_t)y_pos;
    g_ram[Player_Y_HighPos] = (uint8_t)(int8_t)y_high;

    s_wrote_x = page * 256 + pos;
    s_wrote_x_valid = 1;
    s_wrote_y = y_high * 256 + y_pos;
    s_wrote_y_valid = 1;
    s_wrote_dy_px = dy_px;

    if (s_forced_airborne_pending && s_wrote_y < s_y_before &&
        s_swept_block != SMASH64_SWEEP_CEILING) {
        s_forced_airborne_pending = 0;
        s_forced_airborne_frames = 0;
    }
    if (y_high == 1) {
        if (smb1_solid_at(y_pos, 0, 0))
            s_pending_flags |= SMASH64_CF_HEAD_IN_SOLID;
        if (smb1_solid_at(y_pos, 1, 0))
            s_pending_flags |= SMASH64_CF_FEET_IN_SOLID;
    }

    g_cpu.A = (uint8_t)(int8_t)(s_wrote_x - s_x_before);
    return 1;
}

/*
 * Replaces MovePlayerHorizontally ($BF09) while Falcon owns the player.
 *
 * M4 -- walk the horizontal motion one pixel at a time against SMB1's own
 * tiles instead of letting the skipped integrator teleport the whole delta.
 * Unlike vertical there is NO alignment gate to satisfy: DoPlayerSideCheck
 * reacts the instant the probe pixel enters a solid tile column, so parking
 * AT the first solid candidate is exactly the pixel SMB1's own check fires
 * on -- it sets SideCollisionTimer and ejects one pixel from there, the same
 * dance vanilla performs every frame Mario pushes a wall.
 *
 * Consumes Player_X_Speed (1/16 px/frame), which the friction hook wrote
 * earlier this same frame, so the two hooks stay a pipeline, not rivals.
 */
static int move_player_horizontally_hook(uint16_t addr)
{
    const ForeignState *fs;
    double dx_px;
    int whole, pos, page;

    (void)addr;

    if (decide_ownership() != FOREIGN_OWNERSHIP_FOREIGN) return 0;

    /* MovePlayerHorizontally's own first act is to leave while a jumpspring
     * animates ($BF09: LDA $070E / BNE ExXMove); declining preserves it. */
    if (g_ram[JumpspringAnimCtrl] != 0) return 0;

    fs = nes_foreign_state();
    if (fs && state_has_trait(fs->state,
                              SMASH64_STATE_TRAIT_COUPLED_2D_SWEEP))
        return move_player_coupled_2d(fs);

    dx_px = (double)(int8_t)g_ram[Player_X_Speed] / SMB1_XSPEED_PER_PX;

    s_x_before = (int)player_native_x();
    s_x_sub += dx_px;
    whole = (int)s_x_sub;
    s_x_sub -= (double)whole;

    pos  = (int)g_ram[Player_X_Position];
    page = (int)g_ram[Player_PageLoc];

    {
        int step = (whole > 0) ? 1 : -1;
        int left = (whole >= 0) ? whole : -whole;

        while (left-- > 0) {
            int cand = pos + step;
            int cand_page = page;

            s_x_swept_ran = 1;

            while (cand < 0)   { cand += 256; cand_page -= 1; }
            while (cand > 255) { cand -= 256; cand_page += 1; }

            pos = cand;
            page = cand_page;

            if (cand_page >= 0 &&
                smb1_side_solid_at(cand, cand_page, step)) {
                if (!s_sweep_noblock &&
                    smb1_can_step_down_one_tile(cand, cand_page, step)) {
                    g_ram[Player_Y_Position] =
                        (uint8_t)(g_ram[Player_Y_Position] + 16);
                    s_y_sub = 0.0;
                    s_pending_external_dy +=
                        smb_px_to_source_units(-16.0);
                } else {
                    s_x_swept_wall = 1;
                    if (!s_sweep_noblock) break;
                }
            }
        }
    }

    g_ram[Player_X_Position] = (uint8_t)pos;
    g_ram[Player_PageLoc]    = (uint8_t)page;

    s_wrote_x = (page * 256) + pos;
    s_wrote_x_valid = 1;

    /* ABI: both callers store A as Player_X_Scroll (smb.asm:5848, :5889) --
     * the whole pixels moved this frame, driving the scroll engine. Report
     * the SWEPT distance, so the camera never advances into a wall. */
    g_cpu.A = (uint8_t)(int8_t)(s_wrote_x - s_x_before);

    return 1;
}

/* ------------------------------------------------------------------ */
/* M7 combat -- portable hitbox to native SMB1 consequences           */
/*                                                                    */
/* The native entry points used here were confirmed headlessly in     */
/* nes/SuperMarioBrosNES: PlayerHeadCollision $BCED, BrickShatter     */
/* $BE02, and ShellOrBlockDefeat $D795.                                */
/* ------------------------------------------------------------------ */

static int ranges_overlap(double a0, double a1, double b0, double b1)
{
    return a0 < b1 && b0 < a1;
}

static int defeat_enemies_in_attack(double left, double right,
                                    double top, double bottom, int max_hits)
{
    CPU6502State save_cpu = g_cpu;
    int hits = 0;

    for (int slot = 0; slot < 5; ++slot) {
        uint8_t id, state;
        int ex, ey;

        if (!g_ram[Enemy_Flag + slot]) continue;
        if (g_ram[Enemy_Y_HighPos + slot] != 1) continue;
        id = g_ram[Enemy_ID + slot];
        state = g_ram[Enemy_State + slot];
        if (!smash64_enemy_accepts_attack(id, state)) continue;

        ex = ((int)g_ram[Enemy_PageLoc + slot] << 8) |
             (int)g_ram[Enemy_X_Position + slot];
        ey = (int)g_ram[Enemy_Y_Position + slot];
        if (!ranges_overlap(left, right, (double)ex, (double)(ex + 16)) ||
            !ranges_overlap(top, bottom, (double)ey, (double)(ey + 24)))
            continue;

        /* RelativeEnemyPosition refreshes the coordinates consumed by the
         * native floatey-number path; ShellOrBlockDefeat then owns state,
         * score, stun direction, and the enemy-smack sound. */
        g_cpu.X = (uint8_t)slot;
        RelativeEnemyPosition();
        g_cpu.X = (uint8_t)slot;
        ShellOrBlockDefeat();
        hits++;
        if (max_hits > 0 && hits >= max_hits) break;
    }
    g_cpu = save_cpu;
    return hits;
}

static int action_solid_at(double world_x, double screen_y)
{
    int col, tile_top, row;
    uint16_t base, addr;
    uint8_t tile;

    /* The status-bar boundary and bottom edge are host solids for persistent
     * actions. This prevents a bolt/jolt from wrapping through the HUD or the
     * 8-bit bottom of the gameplay field. */
    if (screen_y < 32.0 || screen_y >= 240.0 || world_x < 0.0) return 1;
    col = (int)floor(world_x / 16.0);
    tile_top = (int)floor(screen_y / 16.0) * 16;
    row = tile_top - 0x20;
    if (row < 0 || row > 0xC0) return 1;
    base = (col & 0x10) ? Block_Buffer_2 : Block_Buffer_1;
    addr = (uint16_t)(base + (col & 0x0F) + row);
    tile = g_ram[addr];
    if (tile == 0x23) {
        CPU6502State save_cpu = g_cpu;
        uint8_t save_scratch[6];
        memcpy(save_scratch, &g_ram[0x02], sizeof(save_scratch));
        g_ram[0x02] = (uint8_t)row;
        g_ram[0x06] = (uint8_t)(base + (col & 0x0F));
        g_ram[0x07] = (uint8_t)(base >> 8);
        tile = settle_orphaned_blank_metatile(tile);
        memcpy(&g_ram[0x02], save_scratch, sizeof(save_scratch));
        g_cpu = save_cpu;
    }
    /* Coins are collectible/pass-through, not projectile walls. */
    return tile != 0 && tile != 0xC2 && tile != 0xC3;
}

static int action_defeat_target(double left, double right,
                                double top, double bottom)
{
    return defeat_enemies_in_attack(left, right, top, bottom, 1) > 0;
}

static int action_self_contact(uint32_t kind, double action_x,
                               double action_y, double fighter_left,
                               double fighter_right, double fighter_top,
                               double fighter_bottom)
{
    (void)fighter_top;
    if (!s_profile || s_profile->savestate_tag != 0x504B3634u ||
        kind != PIKACHU_PROJECTILE_THUNDER)
        return -1;
    /* Keep source self-contact independent of the smaller weapon body used
     * for terrain/enemy contact. */
    return smash64_pikachu_thunder_source_contact(
        action_x, action_y, fighter_left, fighter_right, fighter_bottom);
}

static int action_resolve_attachment(uint32_t source_joint,
                                     double fighter_world_x,
                                     double fighter_foot_y,
                                     double *world_x, double *screen_y)
{
    float resolved_x, resolved_y;

    if (!world_x || !screen_y || !isfinite(fighter_world_x) ||
        !isfinite(fighter_foot_y) || fabs(fighter_world_x) > FLT_MAX ||
        fabs(fighter_foot_y) > FLT_MAX)
        return 0;
    /* This validates joint < joint_count before indexing and evaluates the
     * controller's current logical pose without depending on a prior render.
     * Missing owner-only source data fails the spawn closed instead of
     * silently moving authored collision to the fighter root. */
    if (!game_smash64_assets_pikachu_joint_native(
            source_joint, (float)fighter_world_x, (float)fighter_foot_y,
            &resolved_x, &resolved_y))
        return 0;
    *world_x = (double)resolved_x;
    *screen_y = (double)resolved_y;
    return isfinite(*world_x) && isfinite(*screen_y);
}

static void apply_pending_actions(void)
{
    Smash64ActionHost host;
    double x = (double)player_native_x();
    double foot = (double)g_ram[Player_Y_Position] + 32.0;
    double body_height = (s_profile && s_profile->block_adder_index != 0)
                             ? 16.0 : 24.0;
    memset(&host, 0, sizeof(host));
    host.solid_at = action_solid_at;
    host.defeat_target = action_defeat_target;
    host.fighter_left = x;
    host.fighter_right = x + 16.0;
    host.fighter_top = foot - body_height;
    host.fighter_bottom = foot;
    host.self_contact = action_self_contact;
    smash64_actions_step(&host);
    game_smash64_sync_persistent_audio();
}

static int break_smb1_brick(int world_col, int tile_top)
{
    CPU6502State save_cpu = g_cpu;
    uint8_t save_scratch[8];
    uint8_t save_size = g_ram[PlayerSize];
    uint8_t save_crouch = g_ram[CrouchingFlag];
    uint8_t save_x = g_ram[Player_X_Position];
    uint8_t save_page = g_ram[Player_PageLoc];
    uint8_t save_y = g_ram[Player_Y_Position];
    uint8_t save_yhi = g_ram[Player_Y_HighPos];
    uint8_t save_yspeed = g_ram[Player_Y_Speed];
    int row = tile_top - 0x20;
    int anchor_x = world_col * 16 - 8;
    uint16_t base;
    uint16_t addr;
    uint8_t tile;
    int broke;

    if (world_col < 0 || anchor_x < 0 ||
        tile_top < 0x20 || tile_top > 0xE0) return 0;
    base = (world_col & 0x10) ? Block_Buffer_2 : Block_Buffer_1;
    addr = (uint16_t)(base + (world_col & 0x0F) + row);
    tile = g_ram[addr];
    /* $51/$52 are the ordinary breakable bricks. Question, coin, invisible,
     * scenery, pipe, and castle metatiles never enter the native shatter path. */
    if (tile != 0x51 && tile != 0x52) return 0;

    memcpy(save_scratch, &g_ram[0x00], sizeof save_scratch);
    g_ram[0x02] = (uint8_t)row;
    g_ram[0x06] = (uint8_t)(base + (world_col & 0x0F));
    g_ram[0x07] = (uint8_t)(base >> 8);

    /* Present the target as the same head contact Big Mario would have made.
     * PlayerHeadCollision then performs the real buffer/VRAM update, block
     * object spawn, brick chunks, 50 points, and Sfx_BrickShatter. */
    g_ram[PlayerSize] = 0;
    g_ram[CrouchingFlag] = 0;
    g_ram[Player_PageLoc] = (uint8_t)(anchor_x >> 8);
    g_ram[Player_X_Position] = (uint8_t)anchor_x;
    g_ram[Player_Y_HighPos] = 1;
    g_ram[Player_Y_Position] = (uint8_t)(tile_top - 4);
    g_cpu.A = tile;
    PlayerHeadCollision();
    broke = (g_ram[addr] == 0x23);
    if (broke) {
        /* An ordinary Big-Mario $51/$52 shatter ultimately restores zero.
         * Commit that collision value now: Falcon's broad attack must not
         * depend on one of only two asynchronous block slots to make an
         * already-blank cell traversable. The live slot still owns debris,
         * score, sound, and its redundant later zero/VRAM replacement. */
        g_ram[addr] = 0;
    }

    memcpy(&g_ram[0x00], save_scratch, sizeof save_scratch);
    g_ram[PlayerSize] = save_size;
    g_ram[CrouchingFlag] = save_crouch;
    g_ram[Player_X_Position] = save_x;
    g_ram[Player_PageLoc] = save_page;
    g_ram[Player_Y_Position] = save_y;
    g_ram[Player_Y_HighPos] = save_yhi;
    /* Falcon's attack is not a head-bounce. Preserve every native shatter
     * consequence except BrickShatter's imposed Mario Y speed. */
    g_ram[Player_Y_Speed] = save_yspeed;
    g_cpu = save_cpu;
    return broke;
}

static int break_bricks_in_attack(double left, double right,
                                  double top, double bottom)
{
    int first_col = (int)(left / 16.0);
    int last_col = (int)((right - 0.001) / 16.0);
    int first_row = (int)(top / 16.0);
    int last_row = (int)((bottom - 0.001) / 16.0);
    int broken = 0;

    for (int row = first_row; row <= last_row; ++row) {
        int tile_top = row * 16;
        for (int col = first_col; col <= last_col; ++col) {
            broken += break_smb1_brick(col, tile_top);
            /* SMB1 has exactly two block-object slots. Do not overwrite one
             * before BlockObjMT_Updater consumes it later this frame; an
             * active multi-frame attack can take the next pair next frame. */
            if (broken >= 2) return broken;
        }
    }
    return broken;
}

static void apply_pending_attack(void)
{
    const ForeignState *fs = nes_foreign_state();
    const ForeignController *ctl = nes_foreign_active();
    double facing, center_x, foot_y, center_y, half_w, half_h;
    double left, right, top, bottom;
    int enemies, blocks = 0;

    if (!s_attack.active || !fs) return;
    facing = fs->facing < 0.0f ? -1.0 : 1.0;
    center_x = (double)player_native_x() + 8.0 +
               facing * source_units_to_px(s_attack.offset_x);
    foot_y = (double)g_ram[Player_Y_Position] + 32.0;
    center_y = foot_y - source_units_to_px(s_attack.offset_y);
    half_w = source_units_to_px(s_attack.width) * 0.5;
    half_h = source_units_to_px(s_attack.height) * 0.5;
    left = center_x - half_w;
    right = center_x + half_w;
    top = center_y - half_h;
    bottom = center_y + half_h;

    nes_foreign_trace_note_flags(SMASH64_CF_ATTACK_ACTIVE);
    enemies = defeat_enemies_in_attack(
        left, right, top, bottom,
        (s_attack.flags & FOREIGN_ATTACK_CONTACT_ONLY) ? 1 : 0);
    if (!(s_attack.flags & FOREIGN_ATTACK_CONTACT_ONLY) &&
        (s_attack.flags & FOREIGN_ATTACK_BREAK_BLOCKS))
        blocks = break_bricks_in_attack(left, right, top, bottom);
    if (enemies) nes_foreign_trace_note_flags(SMASH64_CF_ENEMY_DEFEATED);
    if (blocks) nes_foreign_trace_note_flags(SMASH64_CF_BLOCK_BROKEN);
    if (enemies || blocks) {
        const char *name = (ctl && ctl->state_name)
                               ? ctl->state_name(fs->state) : "?";
        printf("[Smash64Combat] %s: %d enemy hit(s), %d brick(s) broken\n",
               name ? name : "?", enemies, blocks);
    }
    if (enemies && (s_attack.flags & FOREIGN_ATTACK_CONTACT_ONLY)) {
        /* SMB has no fighter capture graph. Apply the eventual 20-damage
         * throw through its native enemy-defeat path immediately, then report
         * one connection so Falcon owns the 16f Catch + 60f Throw sequence.
         * Limiting the search above to one slot prevents a grab volume from
         * sweeping up a crowd before that state transition reaches us. */
        s_contact_pending = 1;
        s_pending_flags |= SMASH64_CF_CONTACT_CAUGHT;
        /* apply_pending_attack runs in guest context before the next host
         * controller tick can replace this move result. Retire the one-shot
         * catch volume here or that stale frame can defeat a second target
         * after Falcon has already entered Catch. */
        s_attack.active = 0;
    }
}

/*
 * Runs at PlayerPhysicsSub ($B450) entry, before CheckForJumping ($B479).
 *
 * Withholds or presents SMB1's A bit so Falcon's A-normal input never also
 * launches Mario, while Falcon's own Up-stick KneeBend decides jump timing.
 * Always returns 0 -- SMB1's physics runs unmodified; only one input byte moved.
 *
 * SCOPE OF THE WRITE. A_B_Buttons ($000A) is written by SMB1 itself every
 * frame at SaveJoyp, a few instructions before we get here, so this is a
 * time-scoped write to a byte the game owns and rewrites -- the sanctioned
 * pattern in nesrecomp/docs/FOREIGN_CONTROLLER.md, not a relocation and not new
 * guest state. Nothing persists across frames.
 *
 * WHO ELSE SEES IT. Every reader of $000A was enumerated from the byte-exact
 * disassembly and cross-checked against a ROM-wide search for LDA $0A (8 hits,
 * 7 real + one inside E_UndergroundArea3 level data). Downstream of us in the
 * same frame:
 *   $B47E CheckForJumping   the target.
 *   $AF67 SaveAB            copies $000A into PreviousA_B_Buttons at the end of
 *                           GameEngine. AFFECTED AND REQUIRED: that is what
 *                           manufactures a clean rising edge on the launch
 *                           frame, and what stops InitJS re-firing on the frame
 *                           after it while A is still held.
 *   $B37A JumpSwimSub       guarded by "ldy Player_Y_Speed / bpl DumpFall", so
 *                           only reached while rising. Falcon is grounded with
 *                           vy 0 for the whole squat, so it is not reached.
 *   $B8E5 JumpspringHandler gated off below.
 *   $F05D ActionSwimming    gated off below.
 *   $B53A, $B62B            read B_Button ($40). AFFECTED AND REQUIRED: B is
 *                           masked while FOREIGN so SMB1 cannot also run or
 *                           throw a fireball when Falcon starts a special.
 */
static int jumpsquat_hook(uint16_t addr)
{
    const ForeignState *fs;

    (void)addr;

    if (decide_ownership() != FOREIGN_OWNERSHIP_FOREIGN) return 0;

    fs = nes_foreign_state();
    if (!fs) return 0;

    /* B belongs to Falcon combat while the foreign controller owns the
     * player. Mask it before SMB1's run-speed and fireball readers, then apply
     * the attack once in the guest's own execution context. */
    g_ram[A_B_Buttons] &= (uint8_t)~SMB1_B_BUTTON_BIT;
    apply_pending_attack();
    apply_pending_actions();

    /*
     * Water is M5's problem, and masking A here would reach two swim readers:
     * ProcSwim's hold-check at $B37A and the stroke animation at $F05D. Decline
     * the whole mechanism rather than half-applying it -- SMB1 keeps its own
     * rising-edge jump while swimming, which is the M3 behaviour.
     */
    if (g_ram[SwimmingFlag] != 0) return 0;

    /*
     * A jumpspring bounce reads $000A at $B8E5 later in the frame to decide
     * whether to apply the boosted force, and CheckForJumping itself declines
     * while JumpspringAnimCtrl is set ($B479), so masking here would suppress
     * the boost and buy nothing in exchange.
     */
    if (g_ram[JumpspringAnimCtrl] != 0) return 0;

    /* Physical A is Falcon's primary attack. SMB1 must see it only on the
     * controller-authored jump launch frame below; otherwise an A normal also
     * enters InitJS and becomes an unintended Mario jump. */
    g_ram[A_B_Buttons] &= (uint8_t)~SMB1_A_BUTTON_BIT;

    switch (fs->jump_phase) {
    case FOREIGN_JUMP_CHARGING:
        /* Falcon is in KneeBend. SMB1 receives one clean synthetic edge only
         * when the source state machine publishes LAUNCH. */
        s_squat_frames++;
        break;

    case FOREIGN_JUMP_LAUNCH:
        /*
         * Falcon left the ground this tick. FORCE the bit; physical A is an
         * attack now, so the host jump edge is always synthetic.
         */
        g_ram[A_B_Buttons] |= (uint8_t)SMB1_A_BUTTON_BIT;
        s_launch_frames++;
        break;

    case FOREIGN_JUMP_NONE:
    default:
        break;
    }
    return 0;
}

/* BoundingBoxCore is shared, but index zero is the player entry and enemy
 * calls use later SprObj_BoundBoxCtrl elements. Reasserting only element zero
 * at each entry gives Falcon the matching Big-Mario contact box without
 * changing PlayerSize, CrouchingFlag, health, graphics, or any enemy box. */
static int bounding_box_core_hook(uint16_t addr)
{
    (void)addr;
    if (g_cpu.X == 0 && g_cpu.Y == 0 &&
        decide_ownership() == FOREIGN_OWNERSHIP_FOREIGN && s_profile)
        g_ram[Player_BoundBoxCtrl] = s_profile->player_bbox_ctrl;
    return 0;
}

uint8_t game_smash64_ram_read_hook(uint16_t pc, uint16_t addr, uint8_t val)
{
    const ForeignState *fs;

    if (decide_ownership() != FOREIGN_OWNERSHIP_FOREIGN)
        return val;

    /* ChkForPlayerInjury reads InjuryTimer at $D913 and again at $D92C
     * immediately before ForceInjury. Returning a transient nonzero verdict
     * at those two reads preserves native enemy collision/stomp processing
     * while suppressing only damage. Source Quick Attack does this for its
     * 20-frame Start/aim status; entering either zip through PRESERVE_NONE
     * restores normal hit status. No guest timer is written or extended. */
    fs = nes_foreign_state();
    if (addr == InjuryTimer && (pc == 0xD913 || pc == 0xD92C) && fs &&
        state_has_trait(fs->state, SMASH64_STATE_TRAIT_INTANGIBLE))
        return 1;

    /* PlayerBGCollision $DC64: geometry selection only.
     * $DC9A/$DC9F choose BlockBufferAdderData and $DCB1/$DCB4 choose
     * PlayerBGUpperExtent. $BD57/$BD5C choose the contacted block's Y anchor;
     * they must use the same profile or a hidden-small Falcon spawns a powerup
     * one tile too low. The earlier consequence reads in PlayerHeadCollision
     * remain native, so small Falcon still bumps a brick instead of shattering
     * it. */
    if (!s_profile) return val;
    if (addr == CrouchingFlag &&
        (pc == 0xDC9A || pc == 0xDCB4 || pc == 0xBD57))
        return s_profile->collision_crouching;
    if (addr == PlayerSize &&
        (pc == 0xDC9F || pc == 0xDCB1 || pc == 0xBD5C))
        return s_profile->collision_player_size;
    return val;
}

/* ------------------------------------------------------------------ */
/* Save state -- the adapter half (M5.5)                              */
/*                                                                    */
/* The fighter's own state travels in its own hook, registered from    */
/* captain_falcon.c (see mods/smash64/characters/captain_falcon.c).     */
/* This is everything the ADAPTER carries that the fighter never sees: */
/* in-flight subpixel accumulators and the previous-frame readback      */
/* latches that tell the difference between "SMB1 kept our write" and   */
/* "SMB1 overruled it" on the very next frame. Losing any of these on a */
/* load reproduces exactly the bugs their own comments describe above  */
/* -- e.g. a stale s_wrote_yspeed_valid reads a save's own restore as   */
/* an imposed vertical event that never happened.                      */
/*                                                                    */
/* Deliberately NOT included:                                          */
/*   s_enabled / s_selected / s_controller_id -- mod activation is the  */
/*     live user choice this session, per M5.5's design notes; a save   */
/*     must not silently re-arm or disarm the mod on load.              */
/*   s_sweep_noblock -- bound to NESRECOMP_SMASH64_SWEEP_NOBLOCK in      */
/*     *this* process's environment, not to the save file's history.    */
/*   s_frame, s_announced, s_owned_frames, s_wall_frames, s_air_frames,  */
/*     s_squat_frames, s_launch_frames, s_imposed_frames, s_friction_ran */
/*     -- run diagnostics/counters, not trajectory state; restoring     */
/*     them would make a loaded run's stats describe two sessions at    */
/*     once, which is more confusing than resetting them at zero.       */
/* ------------------------------------------------------------------ */

/* Fixed layout after the version byte. A future field addition bumps the
 * version rather than growing this silently; struct memcpy is fine here
 * (unlike a cross-process ABI) because get/set run in the same build. */
typedef struct {
    int8_t   xspeed;
    double   y_sub;
    double   pending_external_dy;
    double   x_sub;
    int32_t  wrote_y;
    int32_t  wrote_y_valid;
    int8_t   wrote_yspeed;
    int32_t  wrote_yspeed_valid;
    int32_t  y_before;
    double   wrote_dy_px;
    int32_t  wrote_x;
    int32_t  wrote_x_valid;
    int32_t  x_before;
    int32_t  prev_ownership;
    uint8_t  prev_buttons;     /* sample_input's edge-detect latch */
    int32_t  special_grace_pending;
    /* Undrained per-frame collision verdicts, set inside a movement hook
     * and consumed by the NEXT update_input. Saving mid-frame, between the
     * hook and that drain, would otherwise lose the very event a trace is
     * usually taken to inspect. */
    int32_t  swept_block;
    int32_t  swept_ran;
    int32_t  x_swept_wall;
    int32_t  x_swept_ran;
    uint32_t pending_flags;
    int32_t  contact_pending;
    int32_t  forced_airborne_pending;
    uint32_t forced_airborne_frames;
    ForeignAttackHitbox attack;
} AdapterSaveFields;

/* Kept separately after the stable v8 adapter payload so old records can be
 * read without copying a platform-padded prefix struct. This is host-only:
 * it records the already-selected projection plan, never source velocity. */
typedef struct {
    uint32_t state;
    double component_px_limit;
    int32_t active;
    int32_t conservative_chain;
} CoupledBurstPlanSave;

/* Version 6 added the B-special grace latch but predates the host-authored
 * step-down displacement. Preserve it because the owner's active slots were
 * created while that adapter was in use. */
typedef struct {
    int8_t   xspeed;
    double   y_sub;
    double   x_sub;
    int32_t  wrote_y;
    int32_t  wrote_y_valid;
    int8_t   wrote_yspeed;
    int32_t  wrote_yspeed_valid;
    int32_t  y_before;
    double   wrote_dy_px;
    int32_t  wrote_x;
    int32_t  wrote_x_valid;
    int32_t  x_before;
    int32_t  prev_ownership;
    uint8_t  prev_buttons;
    int32_t  special_grace_pending;
    int32_t  swept_block;
    int32_t  swept_ran;
    int32_t  x_swept_wall;
    int32_t  x_swept_ran;
    uint32_t pending_flags;
    int32_t  contact_pending;
    int32_t  forced_airborne_pending;
    uint32_t forced_airborne_frames;
    ForeignAttackHitbox attack;
} AdapterSaveFieldsV6;

/* Version 5 predates both the B-special grace latch and the host-authored
 * step-down displacement. Keep a reader because the owner's live slot 0/1
 * saves were made with it; both later fields initialize safely clear. */
typedef struct {
    int8_t   xspeed;
    double   y_sub;
    double   x_sub;
    int32_t  wrote_y;
    int32_t  wrote_y_valid;
    int8_t   wrote_yspeed;
    int32_t  wrote_yspeed_valid;
    int32_t  y_before;
    double   wrote_dy_px;
    int32_t  wrote_x;
    int32_t  wrote_x_valid;
    int32_t  x_before;
    int32_t  prev_ownership;
    uint8_t  prev_buttons;
    int32_t  swept_block;
    int32_t  swept_ran;
    int32_t  x_swept_wall;
    int32_t  x_swept_ran;
    uint32_t pending_flags;
    int32_t  contact_pending;
    int32_t  forced_airborne_pending;
    uint32_t forced_airborne_frames;
    ForeignAttackHitbox attack;
} AdapterSaveFieldsV5;

#define SMASH64_ADAPTER_SAVESTATE_VERSION 9
#define SMASH64_ADAPTER_SAVESTATE_HEADER 5

/*
 * Returns 0 bytes while the mod is off. There is no adapter trajectory to
 * preserve when it is not driving anything -- game_smash64_set_mod_enabled
 * already zeroes every field below the moment it disables -- and this keeps
 * a vanilla (or mod-off) save lean instead of carrying a dead record.
 */
static int game_smash64_savestate_get(uint8_t *buf, int cap)
{
    AdapterSaveFields f;
    CoupledBurstPlanSave plan;

    if (!s_enabled || !s_profile) return 0;
    if (cap < (int)(SMASH64_ADAPTER_SAVESTATE_HEADER + sizeof f +
                     sizeof plan)) return -1;

    f.xspeed              = s_xspeed;
    f.y_sub               = s_y_sub;
    f.pending_external_dy = s_pending_external_dy;
    f.x_sub               = s_x_sub;
    f.wrote_y             = s_wrote_y;
    f.wrote_y_valid       = s_wrote_y_valid;
    f.wrote_yspeed        = s_wrote_yspeed;
    f.wrote_yspeed_valid  = s_wrote_yspeed_valid;
    f.y_before            = s_y_before;
    f.wrote_dy_px         = s_wrote_dy_px;
    f.wrote_x             = s_wrote_x;
    f.wrote_x_valid       = s_wrote_x_valid;
    f.x_before            = s_x_before;
    f.prev_ownership      = (int32_t)s_prev_ownership;
    f.prev_buttons        = s_prev_buttons;
    f.special_grace_pending = s_special_grace_pending;
    f.swept_block         = s_swept_block;
    f.swept_ran           = s_swept_ran;
    f.x_swept_wall        = s_x_swept_wall;
    f.x_swept_ran         = s_x_swept_ran;
    f.pending_flags       = s_pending_flags;
    f.contact_pending     = s_contact_pending;
    f.forced_airborne_pending = s_forced_airborne_pending;
    f.forced_airborne_frames = s_forced_airborne_frames;
    f.attack              = s_attack;
    plan.state = s_coupled_plan_state;
    plan.component_px_limit = s_coupled_plan_component_px_limit;
    plan.active = s_coupled_plan_active;
    plan.conservative_chain = s_coupled_plan_conservative_chain;

    buf[0] = SMASH64_ADAPTER_SAVESTATE_VERSION;
    save_write_u32le(buf + 1, s_profile->savestate_tag);
    memcpy(buf + SMASH64_ADAPTER_SAVESTATE_HEADER, &f, sizeof f);
    memcpy(buf + SMASH64_ADAPTER_SAVESTATE_HEADER + sizeof f,
           &plan, sizeof plan);
    return (int)(SMASH64_ADAPTER_SAVESTATE_HEADER + sizeof f + sizeof plan);
}

/*
 * len == 0 is the "mod was off when this was saved" case get() produces
 * above (or an older save with no adapter record at all) -- nothing to
 * restore, and s_enabled/s_selected are the live session's choice regardless.
 */
static int game_smash64_savestate_set(const uint8_t *buf, int len)
{
    AdapterSaveFields f;
    CoupledBurstPlanSave plan;
    int legacy_plan = 0;

    if (len == 0) return 1;
    memset(&f, 0, sizeof f);
    memset(&plan, 0, sizeof plan);
    if (buf[0] == SMASH64_ADAPTER_SAVESTATE_VERSION &&
        len == (int)(SMASH64_ADAPTER_SAVESTATE_HEADER + sizeof f +
                      sizeof plan)) {
        if (!s_profile || save_read_u32le(buf + 1) != s_profile->savestate_tag)
            return 1;
        memcpy(&f, buf + SMASH64_ADAPTER_SAVESTATE_HEADER, sizeof f);
        memcpy(&plan, buf + SMASH64_ADAPTER_SAVESTATE_HEADER + sizeof f,
               sizeof plan);
    } else if (buf[0] == 8 &&
               len == (int)(SMASH64_ADAPTER_SAVESTATE_HEADER + sizeof f)) {
        if (!s_profile || save_read_u32le(buf + 1) != s_profile->savestate_tag)
            return 1;
        memcpy(&f, buf + SMASH64_ADAPTER_SAVESTATE_HEADER, sizeof f);
        legacy_plan = 1;
    } else if (buf[0] == 7 && len == (int)(1 + sizeof f)) {
        /* v7 predates multi-fighter identity. The later controller record
         * still validates the exact fighter and requests a reseed on a
         * mismatch, so retaining this reader preserves Falcon saves. */
        memcpy(&f, buf + 1, sizeof f);
        legacy_plan = 1;
    } else if (buf[0] == 6 &&
               len == (int)(1 + sizeof(AdapterSaveFieldsV6))) {
        AdapterSaveFieldsV6 old;
        memcpy(&old, buf + 1, sizeof old);
        f.xspeed = old.xspeed;
        f.y_sub = old.y_sub;
        f.pending_external_dy = 0.0;
        f.x_sub = old.x_sub;
        f.wrote_y = old.wrote_y;
        f.wrote_y_valid = old.wrote_y_valid;
        f.wrote_yspeed = old.wrote_yspeed;
        f.wrote_yspeed_valid = old.wrote_yspeed_valid;
        f.y_before = old.y_before;
        f.wrote_dy_px = old.wrote_dy_px;
        f.wrote_x = old.wrote_x;
        f.wrote_x_valid = old.wrote_x_valid;
        f.x_before = old.x_before;
        f.prev_ownership = old.prev_ownership;
        f.prev_buttons = old.prev_buttons;
        f.special_grace_pending = old.special_grace_pending;
        f.swept_block = old.swept_block;
        f.swept_ran = old.swept_ran;
        f.x_swept_wall = old.x_swept_wall;
        f.x_swept_ran = old.x_swept_ran;
        f.pending_flags = old.pending_flags;
        f.contact_pending = old.contact_pending;
        f.forced_airborne_pending = old.forced_airborne_pending;
        f.forced_airborne_frames = old.forced_airborne_frames;
        f.attack = old.attack;
        legacy_plan = 1;
    } else if (buf[0] == 5 &&
               len == (int)(1 + sizeof(AdapterSaveFieldsV5))) {
        AdapterSaveFieldsV5 old;
        memcpy(&old, buf + 1, sizeof old);
        f.xspeed = old.xspeed;
        f.y_sub = old.y_sub;
        f.x_sub = old.x_sub;
        f.wrote_y = old.wrote_y;
        f.wrote_y_valid = old.wrote_y_valid;
        f.wrote_yspeed = old.wrote_yspeed;
        f.wrote_yspeed_valid = old.wrote_yspeed_valid;
        f.y_before = old.y_before;
        f.wrote_dy_px = old.wrote_dy_px;
        f.wrote_x = old.wrote_x;
        f.wrote_x_valid = old.wrote_x_valid;
        f.x_before = old.x_before;
        f.prev_ownership = old.prev_ownership;
        f.prev_buttons = old.prev_buttons;
        f.special_grace_pending = 0;
        f.swept_block = old.swept_block;
        f.swept_ran = old.swept_ran;
        f.x_swept_wall = old.x_swept_wall;
        f.x_swept_ran = old.x_swept_ran;
        f.pending_flags = old.pending_flags;
        f.contact_pending = old.contact_pending;
        f.forced_airborne_pending = old.forced_airborne_pending;
        f.forced_airborne_frames = old.forced_airborne_frames;
        f.attack = old.attack;
        legacy_plan = 1;
    } else {
        return 0;
    }

    s_xspeed              = f.xspeed;
    s_y_sub               = f.y_sub;
    s_pending_external_dy = f.pending_external_dy;
    s_x_sub               = f.x_sub;
    s_wrote_y             = f.wrote_y;
    s_wrote_y_valid       = f.wrote_y_valid;
    s_wrote_yspeed        = f.wrote_yspeed;
    s_wrote_yspeed_valid  = f.wrote_yspeed_valid;
    s_y_before            = f.y_before;
    s_wrote_dy_px         = f.wrote_dy_px;
    s_wrote_x             = f.wrote_x;
    s_wrote_x_valid       = f.wrote_x_valid;
    s_x_before            = f.x_before;
    s_prev_ownership      = (ForeignOwnership)f.prev_ownership;
    s_prev_buttons        = f.prev_buttons;
    s_special_grace_pending = f.special_grace_pending;
    s_swept_block         = f.swept_block;
    s_swept_ran           = f.swept_ran;
    s_x_swept_wall        = f.x_swept_wall;
    s_x_swept_ran         = f.x_swept_ran;
    s_pending_flags       = f.pending_flags;
    s_contact_pending     = f.contact_pending;
    s_forced_airborne_pending = f.forced_airborne_pending;
    s_forced_airborne_frames = f.forced_airborne_frames;
    s_attack              = f.attack;
    if (!legacy_plan &&
        (!isfinite(plan.component_px_limit) ||
         plan.component_px_limit < 0.0 || plan.component_px_limit > 16.0 ||
         (plan.active != 0 && plan.active != 1) ||
         (plan.conservative_chain != 0 && plan.conservative_chain != 1))) {
        /* Treat a malformed plan exactly like a pre-plan record. */
        legacy_plan = 1;
    }
    if (legacy_plan) {
        /* The old record cannot tell us whether its current source action was
         * already admitted. Keep it conservative until it exits the coupled
         * action instead of reading current parser debt and changing mid-zip. */
        s_coupled_plan_state = UINT_MAX;
        s_coupled_plan_component_px_limit = 4.0;
        s_coupled_plan_active = 1;
        s_coupled_plan_conservative_chain = 1;
    } else {
        s_coupled_plan_state = plan.state;
        s_coupled_plan_component_px_limit = plan.component_px_limit;
        s_coupled_plan_active = plan.active != 0;
        s_coupled_plan_conservative_chain = plan.conservative_chain != 0;
    }
    return 1;
}

/* ------------------------------------------------------------------ */
/* Public                                                             */
/* ------------------------------------------------------------------ */

int game_smash64_set_mod_enabled(int enabled, const char *controller_id)
{
    if (!enabled)
        game_smash64_audio_set_enabled(0);
    s_enabled = 0;
    s_selected = 0;
    s_announced = 0;
    memset(&s_attack, 0, sizeof(s_attack));
    s_contact_pending = 0;
    s_special_grace_pending = 0;
    s_pending_external_dy = 0.0;
    s_forced_airborne_pending = 0;
    s_forced_airborne_frames = 0;
    s_coupled_plan_state = UINT_MAX;
    s_coupled_plan_component_px_limit = 0.0;
    s_coupled_plan_active = 0;
    s_coupled_plan_conservative_chain = 0;
    s_savestate_controller_compatible = 1;
    s_controller_id[0] = '\0';
    s_profile = NULL;
    smash64_actions_clear();
    game_smash64_audio_set_persistent_cue_active(
        PIKACHU_AUDIO_ELECTRIC_LOOP, 0);
    nes_foreign_set_ownership(FOREIGN_OWNERSHIP_NATIVE);
    nes_mod_set_function_hook_enabled(SMASH64_FRICTION_HOOK_ID, 0);
    nes_mod_set_function_hook_enabled(SMASH64_VERTICAL_HOOK_ID, 0);
    nes_mod_set_function_hook_enabled(SMASH64_JUMPSQUAT_HOOK_ID, 0);
    nes_mod_set_function_hook_enabled(SMASH64_HORIZONTAL_HOOK_ID, 0);
    nes_mod_set_function_hook_enabled(SMASH64_BOUNDING_BOX_HOOK_ID, 0);

    if (!enabled || !controller_id || !controller_id[0]) {
        game_smash64_assets_clear();
        nes_foreign_select(NULL);
        return 1;
    }

    s_profile = smash64_fighter_profile_find(controller_id);
    if (!s_profile) {
        fprintf(stderr,
                "[Smash64] No SMB fighter profile registered for '%s' - "
                "player replacement stays OFF\n", controller_id);
        return 0;
    }

    snprintf(s_controller_id, sizeof s_controller_id, "%s", controller_id);
    s_selected = nes_foreign_select(s_controller_id);
    if (!s_selected) {
        /* Fail loudly. A silently-ignored character selection is exactly the
         * kind of thing that gets mistaken for "the physics is subtle". */
        fprintf(stderr,
                "[Smash64] No controller registered for '%s' - "
                "player replacement stays OFF\n", s_controller_id);
        s_profile = NULL;
        return 0;
    }

    s_xspeed = 0;
    memset(&s_attack, 0, sizeof(s_attack));
    s_contact_pending = 0;
    s_special_grace_pending = 0;
    s_pending_external_dy = 0.0;
    s_forced_airborne_pending = 0;
    s_forced_airborne_frames = 0;
    s_owned_frames = 0;
    s_wall_frames = 0;
    s_air_frames = 0;
    s_squat_frames = 0;
    s_launch_frames = 0;
    s_y_sub = 0.0;
    s_wrote_y = 0;
    s_wrote_y_valid = 0;
    s_y_before = 0;
    s_wrote_dy_px = 0.0;
    s_wrote_yspeed = 0;
    s_wrote_yspeed_valid = 0;
    s_imposed_frames = 0;
    s_swept_block = SMASH64_SWEEP_NONE;
    s_x_swept_wall = 0;
    s_x_swept_ran = 0;
    s_x_sub = 0.0;
    s_wrote_x = 0;
    s_wrote_x_valid = 0;
    s_x_before = 0;
    s_prev_ownership = FOREIGN_OWNERSHIP_NATIVE;
    s_reseed_this_frame = 0;

    {
        const char *e = getenv("NESRECOMP_SMASH64_SWEEP_NOBLOCK");
        s_sweep_noblock = (e && *e && *e != '0');
        if (s_sweep_noblock)
            fprintf(stderr,
                    "[Smash64] DIAGNOSTIC: vertical sweep will PROBE BUT NOT "
                    "BLOCK (NESRECOMP_SMASH64_SWEEP_NOBLOCK) - collision "
                    "behaviour in this run is not representative\n");
    }

    if (!nes_mod_set_function_hook_enabled(SMASH64_FRICTION_HOOK_ID, 1)) {
        fprintf(stderr,
                "[Smash64] ImposeFriction hook is not registered; SMB1 keeps "
                "its own horizontal physics\n");
        return 0;
    }
    if (!nes_mod_set_function_hook_enabled(SMASH64_VERTICAL_HOOK_ID, 1)) {
        fprintf(stderr,
                "[Smash64] MovePlayerVertically hook is not registered; SMB1 "
                "keeps its own gravity\n");
        return 0;
    }
    if (!nes_mod_set_function_hook_enabled(SMASH64_JUMPSQUAT_HOOK_ID, 1)) {
        /* Not fatal: without it SMB1 launches on the A rising edge and every
         * jump is a full hop, which is exactly M3's behaviour. Say so, because
         * "short hop does nothing" is otherwise indistinguishable from a
         * physics bug. */
        fprintf(stderr,
                "[Smash64] PlayerPhysicsSub hook is not registered; SMB1 keeps "
                "its own jump TIMING, so short hop is unavailable\n");
    }
    if (!nes_mod_set_function_hook_enabled(SMASH64_HORIZONTAL_HOOK_ID, 1)) {
        /* Not fatal: SMB1's own integrator applies the velocity the friction
         * hook wrote, which is M3 behaviour -- correct speeds, but wall
         * detection reverts to the one-frame-late readback and its tunnelling
         * exposure. Say so, for the same reason the jumpsquat hook does. */
        fprintf(stderr,
                "[Smash64] MovePlayerHorizontally hook is not registered; "
                "horizontal motion uses native integration with one-frame-"
                "late position reconciliation (tunnelling exposure at dash "
                "speed)\n");
    }
    if (!nes_mod_set_function_hook_enabled(SMASH64_BOUNDING_BOX_HOOK_ID, 1)) {
        fprintf(stderr,
                "[Smash64] BoundingBoxCore hook is not registered; fighter "
                "contact bounds may follow hidden Mario size\n");
    }
    s_enabled = 1;
    if (!game_smash64_audio_set_enabled(1)) {
        game_smash64_set_mod_enabled(0, NULL);
        return 0;
    }
    return 1;
}

int game_smash64_active(void)
{
    return s_enabled && s_selected &&
           nes_foreign_ownership() == FOREIGN_OWNERSHIP_FOREIGN;
}

int game_smash64_death_presentation_active(void)
{
    return s_enabled && s_selected &&
           g_ram[OperMode] == SMB1_OPER_MODE_GAME &&
           g_ram[GameEngineSubroutine] == SMB1_GAMEMODE_PLAYER_DEATH;
}

int game_smash64_still_presentation_active(void)
{
    uint8_t subroutine;
    if (!s_enabled || !s_selected ||
        g_ram[OperMode] != SMB1_OPER_MODE_GAME)
        return 0;
    subroutine = g_ram[GameEngineSubroutine];
    return subroutine == SMB1_GAMEMODE_CHANGE_SIZE ||
           subroutine == SMB1_GAMEMODE_INJURY_BLINK ||
           subroutine == SMB1_GAMEMODE_FIRE_FLOWER;
}

int game_smash64_swim_presentation_active(void)
{
    return s_enabled && s_selected &&
           g_ram[OperMode] == SMB1_OPER_MODE_GAME &&
           g_ram[GameEngineSubroutine] == SMB1_GAMEMODE_PLAYER_CTRL &&
           g_ram[SwimmingFlag] != 0;
}

Smash64ScriptedPresentation game_smash64_scripted_presentation(void)
{
    uint8_t subroutine;
    if (!s_enabled || !s_selected ||
        g_ram[OperMode] != SMB1_OPER_MODE_GAME)
        return SMASH64_SCRIPTED_PRESENTATION_NONE;

    subroutine = g_ram[GameEngineSubroutine];
    if (subroutine == SMB1_GAMEMODE_SIDE_PIPE)
        return SMASH64_SCRIPTED_PRESENTATION_PIPE_SIDE;
    if (subroutine == SMB1_GAMEMODE_VERTICAL_PIPE ||
        (subroutine == SMB1_GAMEMODE_PLAYER_ENTRANCE &&
         g_ram[AltEntranceControl] == 2))
        return SMASH64_SCRIPTED_PRESENTATION_PIPE_VERTICAL;
    if (subroutine == SMB1_GAMEMODE_FLAGPOLE_SLIDE)
        return SMASH64_SCRIPTED_PRESENTATION_FLAGPOLE;
    if (subroutine == SMB1_GAMEMODE_PLAYER_END_LEVEL ||
        subroutine == SMB1_GAMEMODE_PLAYER_ENTRANCE)
        return SMASH64_SCRIPTED_PRESENTATION_WALK;
    return SMASH64_SCRIPTED_PRESENTATION_NONE;
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
    printf("[Smash64] Controls: A normal, B special, Up jump (4-frame "
           "jumpsquat). SMB1 keeps all collision and scripted sequences.\n");
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
        printf("[Smash64] %s has the wheel (state %s, X_Speed %d = %.2f "
               "px/frame; Mario's own max run is 40 = 2.50)\n",
               s_profile && s_profile->display_name
                   ? s_profile->display_name : "Fighter",
               (ctl && ctl->state_name && fs) ? ctl->state_name(fs->state) : "?",
               (int)s_xspeed, (double)s_xspeed / SMB1_XSPEED_PER_PX);
    }
}

unsigned long game_smash64_owned_frames(void) { return s_owned_frames; }
unsigned long game_smash64_wall_frames(void)  { return s_wall_frames; }
unsigned long game_smash64_air_frames(void)   { return s_air_frames; }
unsigned long game_smash64_imposed_frames(void) { return s_imposed_frames; }
unsigned long game_smash64_squat_frames(void)  { return s_squat_frames; }
unsigned long game_smash64_launch_frames(void) { return s_launch_frames; }

/* Registered before main() by mods/smash64_player_plugin.c; starts disabled,
 * so registration alone cannot change behaviour. */
int game_smash64_register_hooks(void)
{
    int ok = nes_mod_register_function_entry_plugin(
        SMASH64_FRICTION_HOOK_ID, SMB1_IMPOSE_FRICTION_ADDR,
        impose_friction_hook);
    ok &= nes_mod_register_function_entry_plugin(
        SMASH64_VERTICAL_HOOK_ID, SMB1_MOVE_PLAYER_VERTICALLY_ADDR,
        move_player_vertically_hook);
    ok &= nes_mod_register_function_entry_plugin(
        SMASH64_JUMPSQUAT_HOOK_ID, SMB1_PLAYER_PHYSICS_ADDR,
        jumpsquat_hook);
    ok &= nes_mod_register_function_entry_plugin(
        SMASH64_HORIZONTAL_HOOK_ID, SMB1_MOVE_PLAYER_HORIZONTALLY_ADDR,
        move_player_horizontally_hook);
    ok &= nes_mod_register_function_entry_plugin(
        SMASH64_BOUNDING_BOX_HOOK_ID, SMB1_BOUNDING_BOX_CORE_ADDR,
        bounding_box_core_hook);

    /* Unconditional, like the function hooks above: registering a savestate
     * hook does not by itself change behaviour, since get() returns 0 bytes
     * whenever the mod is off (see game_smash64_savestate_get). */
    ok &= nes_mod_register_savestate_hook(SMASH64_ADAPTER_SAVESTATE_ID,
                                          game_smash64_savestate_get,
                                          game_smash64_savestate_set);
    ok &= nes_mod_register_savestate_hook(
        SMASH64_CONTROLLER_SAVESTATE_ID,
        game_smash64_controller_savestate_get,
        game_smash64_controller_savestate_set);
    ok &= nes_mod_register_savestate_hook(
        SMASH64_ACTIONS_SAVESTATE_ID,
        game_smash64_actions_savestate_get,
        game_smash64_actions_savestate_set);
    return ok;
}
