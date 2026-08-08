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
 * PlayerPhysicsSub ($B450) -- M3.5, the jumpsquat window.
 *
 * SMB1 launches on the A button's RISING EDGE, which leaves Falcon's 4-frame
 * KneeBend nowhere to live, so his short hop was unreachable. We make SMB1 see
 * the press LATE: withhold the A bit for the squat, then present it on the
 * frame Falcon actually leaves the ground. See ForeignJumpPhase.
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

/* A_B_Buttons bit for A. B ($40) is never touched, which is what keeps the
 * run-speed check at $B53A and the fireball check at $B62B out of scope. */
#define SMB1_A_BUTTON_BIT 0x80

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

static uint8_t  s_prev_buttons = 0;
static uint64_t s_frame = 0;
static int8_t   s_xspeed = 0;            /* this frame's velocity, computed in
                                          * update_input, written by the hook */
static int8_t   s_wrote_xspeed = 0;      /* what the hook wrote last frame, so a
                                          * zeroed readback is detectable as
                                          * SMB1 refusing the motion */
static unsigned long s_owned_frames = 0;
static unsigned long s_wall_frames = 0;
static unsigned long s_air_frames = 0;
static unsigned long s_squat_frames = 0;   /* frames SMB1's A bit was withheld */
static unsigned long s_launch_frames = 0;  /* frames it was presented */
static int s_friction_ran = 0;           /* did ImposeFriction fire this frame */
static double s_y_sub = 0.0;             /* vertical subpixel remainder, kept
                                          * host-side rather than contending
                                          * for SMB1's fraction bytes */
static int s_wrote_y = 0;                /* 16-bit player Y the vertical hook
                                          * last wrote, so a corrected readback
                                          * is detectable as SMB1 refusing the
                                          * motion -- the vertical twin of
                                          * s_wrote_xspeed */
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

static ForeignOwnership decide_ownership(void)
{
    if (!s_enabled || !s_selected) return FOREIGN_OWNERSHIP_NATIVE;

    /* Anything but ordinary play is a scripted sequence -- pipes, flagpole,
     * death, entrance autowalk, powerup transitions. Hand control back
     * rather than blanket-suppressing SMB1's player update. */
    if (g_ram[GameEngineSubroutine] != SMB1_GAMEMODE_PLAYER_CTRL)
        return FOREIGN_OWNERSHIP_SCRIPTED;

    /*
     * M3: Falcon owns the air too. The state encoding is from the disassembly
     * (PlayerPhysicsSub $B450 compares #$03 for climbing; PlayerBGCollision's
     * SetFallS path stores #$02; InitJS stores #$01):
     *     0 on ground   1 jumping/swimming   2 falling   3 climbing   4 killed
     * 0..2 are ordinary locomotion and ours. 3 is a vine, 4 is death, and both
     * are native modes we do not model.
     *
     * Note 1 doubles as swimming. SwimmingFlag distinguishes them and water
     * levels are out of scope for M3, so a swim would currently be driven as a
     * jump; that is tracked with the scripted-state handoffs in M5.
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
    nes_foreign_set_ownership(decide_ownership());

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

        fs->grounded = (pstate == 0);
        fs->air_cause = (pstate == 1) ? FOREIGN_AIR_LAUNCHED
                      : (pstate == 2) ? FOREIGN_AIR_FELL
                                      : FOREIGN_AIR_NONE;
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

    /*
     * M2: SMB1 integrates and collides, so the granted motion is what we
     * proposed minus anything the wall check just removed. That is honest for
     * horizontal ground movement; M4 replaces it with a real swept query
     * against SMB1's block buffer.
     */
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
            hit.imposed_vy = -(double)now_ys / FALCON_TO_SMB1_PX;
            s_imposed_frames++;

            /* Downward impulse while we were rising is SMB1 stopping the jump
             * against something solid; report it as a ceiling too so the ring
             * and the controller both see the collision, not just the number. */
            if (now_ys > 0 && s_wrote_dy_px < 0.0) hit.hit_ceiling = 1;

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
        hit.actual_dy = -(double)(now_y - s_y_before) / FALCON_TO_SMB1_PX;
        s_wrote_y_valid = 0;
    }

    nes_foreign_resolve(&hit);
}

/*
 * Replaces ImposeFriction ($B5CC) while Falcon owns the player.
 *
 * Returning 1 skips SMB1's own horizontal integrator, so the velocity we write
 * survives to MoveObjectHorizontally ($BF0F), which applies it with SMB1's own
 * collision. Returning 0 runs the original unchanged.
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
    s_wrote_xspeed = xspeed;
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
    dy_px = -(fs->vy) * FALCON_TO_SMB1_PX;

    s_y_sub += dy_px;
    whole = (int)s_y_sub;          /* truncate toward zero, either sign */
    s_y_sub -= (double)whole;

    pos  = (int)g_ram[Player_Y_Position];
    high = (int8_t)g_ram[Player_Y_HighPos];
    s_y_before = (high * 256) + pos;

    pos += whole;
    while (pos < 0)    { pos += 256; high -= 1; }
    while (pos > 255)  { pos -= 256; high += 1; }

    g_ram[Player_Y_Position] = (uint8_t)pos;
    g_ram[Player_Y_HighPos]  = (uint8_t)(int8_t)high;

    /* Remember what we wrote so next frame can tell whether SMB1 kept it. */
    s_wrote_y = (high * 256) + pos;
    s_wrote_y_valid = 1;
    s_wrote_dy_px = dy_px;

    /* Keep SMB1's own view of vertical velocity consistent: collision bias,
     * the landing/heavy-landing check and the player graphics handler all read
     * Player_Y_Speed, and a stale value makes them disagree with the motion. */
    {
        int ys = (int)((dy_px >= 0.0) ? (dy_px + 0.5) : (dy_px - 0.5));
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

/*
 * Runs at PlayerPhysicsSub ($B450) entry, before CheckForJumping ($B479).
 *
 * Withholds or presents SMB1's A bit so Falcon's KneeBend decides jump height.
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
 *   $B53A, $B62B            read B_Button ($40) only. Untouched.
 */
static int jumpsquat_hook(uint16_t addr)
{
    const ForeignState *fs;

    (void)addr;

    if (decide_ownership() != FOREIGN_OWNERSHIP_FOREIGN) return 0;

    fs = nes_foreign_state();
    if (!fs) return 0;

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

    switch (fs->jump_phase) {
    case FOREIGN_JUMP_CHARGING:
        /* Falcon is in KneeBend. Withhold the press -- do not consume it: the
         * bit is only cleared for this frame, so SMB1's own edge detection
         * stays intact and sees a clean edge when we present it. */
        g_ram[A_B_Buttons] &= (uint8_t)~SMB1_A_BUTTON_BIT;
        s_squat_frames++;
        break;

    case FOREIGN_JUMP_LAUNCH:
        /*
         * Falcon left the ground this tick. FORCE the bit rather than merely
         * stopping the mask: a short hop means the player released A during the
         * squat, so SavedJoypadBits no longer carries it and SaveJoyp already
         * wrote $000A without it. Without this, a short hop produces no jump at
         * all -- silently, and it reads as the physics being wrong.
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
    nes_mod_set_function_hook_enabled(SMASH64_VERTICAL_HOOK_ID, 0);
    nes_mod_set_function_hook_enabled(SMASH64_JUMPSQUAT_HOOK_ID, 0);

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

    if (!nes_mod_set_function_hook_enabled(SMASH64_FRICTION_HOOK_ID, 1)) {
        fprintf(stderr,
                "[Smash64] ImposeFriction hook is not registered; SMB1 keeps "
                "its own horizontal physics\n");
        return;
    }
    if (!nes_mod_set_function_hook_enabled(SMASH64_VERTICAL_HOOK_ID, 1)) {
        fprintf(stderr,
                "[Smash64] MovePlayerVertically hook is not registered; SMB1 "
                "keeps its own gravity\n");
        return;
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
    printf("[Smash64] Falcon owns ground movement, air physics, and jump "
           "timing (4-frame jumpsquat: tap A for a short hop). SMB1 keeps all "
           "collision and every scripted sequence.\n");
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
    return ok;
}
