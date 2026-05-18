// semcomp/PlayerPhysics.cpp — replacement bodies for $B0E6 + $B329.
#include "semcomp/PlayerPhysics.h"

#include "semcomp/GameState.h"
#include "semcomp/SmbRamMap.h"

extern "C" {
#include "nes_runtime.h"
}

namespace smb::semcomp {

namespace {
// Delegated callees. All separately-emitted, not owned by us.
constexpr std::uint16_t kPC_PlayerCtrlRoutine = 0xB0E9;
constexpr std::uint16_t kPC_MovePlayer        = 0xB450;
constexpr std::uint16_t kPC_OnGroundStateSub  = 0xB35A;
constexpr std::uint16_t kPC_JumpSwimSub       = 0xB376;
constexpr std::uint16_t kPC_FallingSub        = 0xB36D;
constexpr std::uint16_t kPC_ClimbingSub       = 0xB3CF;
}  // namespace

void PlayerPhysics::auto_control() {
    // $B0E6: STA $06FC — stash A as the controller-pressed override.
    state_.write8(ram::Controller1_NewlyPressed, g_cpu.A);
    // $B0E9 fall-through: call into PlayerCtrlRoutine which we don't own.
    call_by_address(kPC_PlayerCtrlRoutine);
}

// ---- PlayerMovementSubs dispatch targets (Phases 11-13) -------------------
//
// Each method is a literal port of the recompiler's generated body for the
// corresponding 6502 routine. Sub-callees stay natural-generated and are
// invoked via call_by_address (which dispatches through the recompiler's
// table — every emitted func_XXXX_b0 has a case).
//
// PhysicsSub ($B450) intentionally deferred — ~300-line body with heavy
// ROM-table lookups, dedicated future phase.

void PlayerPhysics::on_ground_state_sub() {
    // $B35A: JSR $B58F GetPlayerAnimSpeed
    call_by_address(0xB58F);
    // $B35D-$B361: A = $0C; if A != 0, $33 = A (write Player_MovingDir).
    {
        const std::uint8_t a = state_.read8(0x000C);
        if (a != 0) state_.write8(0x0033, a);
        g_cpu.A = a;
    }
    // $B363 GndMove: JSR $B5CC ImposeFriction
    call_by_address(0xB5CC);
    // $B366: JSR $BF09 MovePlayerHorizontally — leaves A set with the
    // horizontal displacement byte.
    call_by_address(0xBF09);
    // $B369: STA $06FF (BG-scroll-pending byte? — copy A returned by
    // MovePlayerHorizontally).
    state_.write8(0x06FF, g_cpu.A);
    // $B36C: RTS
}

void PlayerPhysics::falling_sub() {
    // $B36D: A = $070A (terminal y-velocity?); $0709 = A.
    {
        const std::uint8_t v = state_.read8(0x070A);
        state_.write8(0x0709, v);
        g_cpu.A = v;
    }
    // $B373: JMP $B3AC LRAir (tail-call, leaves A live for the rest of
    // LRAir's chain). $B3AC is emitted as standalone func_B3AC_b0.
    call_by_address(0xB3AC);
}

// Phase 12 — $B376 JumpSwimSub. Air/swim per-frame physics. Tail-flows
// through $B3AC LRAir; we dispatch the LRAir tail via call_by_address since
// it's emitted standalone.
//
// Branch polarity notes:
//   $B378 BPL DumpFall    -> "if !N goto DumpFall"  (positive/zero jumpspring counter)
//   $B380 BNE ProcSwim    -> "if !Z goto ProcSwim"  (sign-bit overlap of $0A & $0D)
//   $B38B BCC ProcSwim    -> "if !C goto ProcSwim"  (A < $0706 after subtract)
//   $B396 BEQ LRAir       -> "if Z goto LRAir"      (SwimmingFlag == 0)
//   $B39F BCS LRWater     -> "if C goto LRWater"    (CE >= $14)
//   $B3A8 BEQ LRAir       -> "if Z goto LRAir"      ($0C == 0)
void PlayerPhysics::jump_swim_sub() {
    // $B376: Y = $9F (JumpspringAnimCtrl).
    g_cpu.Y = state_.read8(0x009F);
    // $B378: BPL DumpFall — if Y positive/zero, skip the swim-tier check.
    if ((g_cpu.Y & 0x80) == 0) goto DumpFall;

    // $B37A: A = $0A; $B37C: A &= 0x80; $B37E: A &= $0D.
    g_cpu.A = state_.read8(0x000A);
    g_cpu.A &= 0x80;
    g_cpu.A &= state_.read8(0x000D);
    // $B380: BNE ProcSwim.
    if (g_cpu.A != 0) goto ProcSwim;

    {
        // $B382: A = $0708; $B385: SEC; $B386: SBC $CE.
        g_cpu.A = state_.read8(0x0708);
        g_cpu.C = 1;
        const std::uint8_t m1 = state_.read8(0x00CE);
        const std::int16_t r1 = static_cast<std::int16_t>(g_cpu.A)
                              - static_cast<std::int16_t>(m1)
                              - static_cast<std::int16_t>(1 - g_cpu.C);
        g_cpu.C = (r1 >= 0) ? 1 : 0;
        g_cpu.A = static_cast<std::uint8_t>(r1 & 0xFF);
        // $B388: CMP $0706.
        const std::uint8_t m2 = state_.read8(0x0706);
        g_cpu.C = (g_cpu.A >= m2) ? 1 : 0;
        // $B38B: BCC ProcSwim.
        if (!g_cpu.C) goto ProcSwim;
    }

DumpFall: {
        // $B38D: A = $070A; $B390: STA $0709.
        const std::uint8_t v = state_.read8(0x070A);
        state_.write8(0x0709, v);
        g_cpu.A = v;
    }

ProcSwim: {
        // $B393: A = $0704 (SwimmingFlag). $B396: BEQ LRAir.
        const std::uint8_t swim = state_.read8(0x0704);
        g_cpu.A = swim;
        if (swim == 0) {
            call_by_address(0xB3AC);  // LRAir
            return;
        }
    }
    // $B398: JSR $B58F GetPlayerAnimSpeed.
    call_by_address(0xB58F);
    {
        // $B39B: A = $CE. $B39D: CMP #$14. $B39F: BCS LRWater.
        const std::uint8_t ce = state_.read8(0x00CE);
        g_cpu.A = ce;
        g_cpu.C = (ce >= 0x14) ? 1 : 0;
        if (!g_cpu.C) {
            // $B3A1: A = #$18; $B3A3: STA $0709.
            g_cpu.A = 0x18;
            state_.write8(0x0709, 0x18);
        }
    }
    // $B3A6 LRWater: A = $0C; BEQ LRAir; STA $33; fall through to LRAir.
    {
        const std::uint8_t a0c = state_.read8(0x000C);
        g_cpu.A = a0c;
        if (a0c != 0) {
            state_.write8(0x0033, a0c);
        }
    }
    // $B3AC LRAir tail — separately-emitted func_B3AC_b0 finishes the chain
    // (ImposeFriction conditionally + MovePlayerHorizontally + crouch tweak +
    // JMP $BF4D).
    call_by_address(0xB3AC);
}

// Phase 13 — $B3CF ClimbingSub. Vine/flagpole climb. The body has two RTS
// exits ($B41F ExitCSub, $B423 InitCSTimer). Two ROM table lookups at
// $B3C7/$B3CB drive the X/Y delta selection (4-way climb direction).
//
// Inner labels ($B3DF MoveOnVine, $B40A CSetFDir, $B406 ClimbFD) ARE
// emitted as standalone _b1 functions, but those callers live entirely in
// the sound-bank context (different physical bank). Within _b0 nothing
// reaches into the interior, so replacing $B3CF is safe.
//
// Carry propagates across the two 16-bit adds:
//   $B3D3 ADC $0433     (low-byte fract add)  → C may set
//   $B3E2 ADC $CE       uses C from above
//   $B3E8 ADC $00       uses C from $B3E2
// Don't reset C between them.
void PlayerPhysics::climbing_sub() {
    // $B3CF: A = $0416 (low fract). $B3D2: CLC. $B3D3: ADC $0433.
    g_cpu.A = state_.read8(0x0416);
    g_cpu.C = 0;
    {
        const std::uint8_t m = state_.read8(0x0433);
        const std::uint16_t r = static_cast<std::uint16_t>(g_cpu.A) + m + g_cpu.C;
        g_cpu.C = (r > 0xFF) ? 1 : 0;
        g_cpu.A = static_cast<std::uint8_t>(r & 0xFF);
    }
    // $B3D6: STA $0416.
    state_.write8(0x0416, g_cpu.A);

    // $B3D9: Y = 0. $B3DB: A = $9F. $B3DD: BPL MoveOnVine (skip DEY).
    g_cpu.Y = 0x00;
    g_cpu.A = state_.read8(0x009F);
    if ((g_cpu.A & 0x80) != 0) {
        // $B3DF: DEY  -> Y = $FF (sign-extension of negative $9F).
        g_cpu.Y = static_cast<std::uint8_t>((g_cpu.Y - 1) & 0xFF);
    }
    // $B3E0 MoveOnVine: STY $00.
    state_.write8(0x0000, g_cpu.Y);
    // $B3E2: ADC $CE (carry from $B3D3 is intentional — fractional overflow
    // propagates into the integer-Y high byte).
    {
        const std::uint8_t m = state_.read8(0x00CE);
        const std::uint16_t r = static_cast<std::uint16_t>(g_cpu.A) + m + g_cpu.C;
        g_cpu.C = (r > 0xFF) ? 1 : 0;
        g_cpu.A = static_cast<std::uint8_t>(r & 0xFF);
    }
    // $B3E4: STA $CE.
    state_.write8(0x00CE, g_cpu.A);
    // $B3E6: A = $B5. $B3E8: ADC $00 (sign-extension byte).
    g_cpu.A = state_.read8(0x00B5);
    {
        const std::uint8_t m = state_.read8(0x0000);
        const std::uint16_t r = static_cast<std::uint16_t>(g_cpu.A) + m + g_cpu.C;
        g_cpu.C = (r > 0xFF) ? 1 : 0;
        g_cpu.A = static_cast<std::uint8_t>(r & 0xFF);
    }
    // $B3EA: STA $B5.
    state_.write8(0x00B5, g_cpu.A);

    // $B3EC: A = $0C. $B3EE: AND $0490. $B3F1: BEQ InitCSTimer.
    g_cpu.A = state_.read8(0x000C);
    g_cpu.A &= state_.read8(0x0490);
    if (g_cpu.A == 0) {
        // $B420 InitCSTimer: STA $0789 (A = 0 here); $B423: RTS.
        state_.write8(0x0789, 0x00);
        return;
    }
    // $B3F3: Y = $0789. $B3F6: BNE ExitCSub.
    g_cpu.Y = state_.read8(0x0789);
    if (g_cpu.Y != 0) {
        return;
    }
    // $B3F8: Y = $18. $B3FA: STY $0789.
    g_cpu.Y = 0x18;
    state_.write8(0x0789, 0x18);
    // $B3FD: X = 0. $B3FF: Y = $33. $B401: LSR A. $B402: BCS ClimbFD.
    g_cpu.X = 0x00;
    g_cpu.Y = state_.read8(0x0033);
    g_cpu.C = static_cast<std::uint8_t>(g_cpu.A & 1);
    g_cpu.A = static_cast<std::uint8_t>(g_cpu.A >> 1);
    if (g_cpu.C == 0) {
        // $B404: INX. $B405: INX.
        g_cpu.X = static_cast<std::uint8_t>((g_cpu.X + 1) & 0xFF);
        g_cpu.X = static_cast<std::uint8_t>((g_cpu.X + 1) & 0xFF);
    }
    // $B406 ClimbFD: DEY. $B407: BEQ CSetFDir.
    g_cpu.Y = static_cast<std::uint8_t>((g_cpu.Y - 1) & 0xFF);
    if (g_cpu.Y != 0) {
        // $B409: INX.
        g_cpu.X = static_cast<std::uint8_t>((g_cpu.X + 1) & 0xFF);
    }
    // $B40A CSetFDir: A = $86. $B40C: CLC. $B40D: ADC $B3C7,X (ROM table).
    g_cpu.A = state_.read8(0x0086);
    g_cpu.C = 0;
    {
        const std::uint16_t addr = static_cast<std::uint16_t>(0xB3C7 + g_cpu.X);
        const std::uint8_t m = nes_read(addr);
        const std::uint16_t r = static_cast<std::uint16_t>(g_cpu.A) + m + g_cpu.C;
        g_cpu.C = (r > 0xFF) ? 1 : 0;
        g_cpu.A = static_cast<std::uint8_t>(r & 0xFF);
    }
    // $B410: STA $86.
    state_.write8(0x0086, g_cpu.A);
    // $B412: A = $6D. $B414: ADC $B3CB,X (ROM table). 16-bit carry propagation.
    g_cpu.A = state_.read8(0x006D);
    {
        const std::uint16_t addr = static_cast<std::uint16_t>(0xB3CB + g_cpu.X);
        const std::uint8_t m = nes_read(addr);
        const std::uint16_t r = static_cast<std::uint16_t>(g_cpu.A) + m + g_cpu.C;
        g_cpu.C = (r > 0xFF) ? 1 : 0;
        g_cpu.A = static_cast<std::uint8_t>(r & 0xFF);
    }
    // $B417: STA $6D.
    state_.write8(0x006D, g_cpu.A);
    // $B419: A = $0C. $B41B: EOR #$03. $B41D: STA $33. $B41F: RTS.
    g_cpu.A = state_.read8(0x000C);
    g_cpu.A ^= 0x03;
    state_.write8(0x0033, g_cpu.A);
}

void PlayerPhysics::movement_subs() {
    // $B329-$B32E: A = 0; Y = $0754 (PlayerSize). If Y != 0 (Small),
    // skip the joypad-down check and go straight to SetCrouch with A=0
    // (no crouch — Small Mario can't crouch).
    g_cpu.A = 0x00;
    g_cpu.Y = state_.read8(ram::PlayerSize);

    if (g_cpu.Y == 0) {
        // $B330-$B332: tall Mario; A = $001D (Player_State).
        // If non-zero (airborne), skip down-button read; A stays = state byte.
        // Wait — the original then writes A (the state byte) to $0714?!
        // Let me re-read: at $B332 BNE jumps to ProcMove (skipping the
        // crouch-set entirely). So airborne state -> no crouch-flag write.
        const std::uint8_t state = state_.read8(ram::Player_State);
        if (state != 0) {
            // Airborne — jump past SetCrouch directly to ProcMove.
            goto ProcMove;
        }
        // $B334-$B336: A = $000B (Joypad) & $04 (Down).
        g_cpu.A = static_cast<std::uint8_t>(state_.read8(0x000B) & 0x04);
        // Fall through to SetCrouch.
    }
    // $B338 SetCrouch: $0714 = A. This is the CrouchingFlag.
    state_.write8(0x0714, g_cpu.A);

ProcMove:
    // $B33B: JSR $B450 (MovePlayer — apply velocity to position).
    call_by_address(kPC_MovePlayer);

    // $B33E: A = $070B (PlayerChangeSizeFlag). If non-zero, exit
    // (don't run state-dispatch during grow/shrink anim).
    if (state_.read8(ram::PlayerChangeSizeFlag) != 0) {
        return;
    }

    // $B343-$B347: A = $001D Player_State. If A == 3, skip the $0789
    // = $18 stage (climbing leaves $0789 alone).
    const std::uint8_t state = state_.read8(ram::Player_State);
    g_cpu.A = state;
    if (state != 0x03) {
        // $B349-$B34B: Y = $18, $0789 = Y. Then fall to MoveSubs.
        g_cpu.Y = 0x18;
        state_.write8(0x0789, 0x18);
    }

    // $B34E MoveSubs: inline_dispatch $8E04 with 4 cases on A.
    switch (g_cpu.A) {
        case 0: call_by_address(kPC_OnGroundStateSub); return;
        case 1: call_by_address(kPC_JumpSwimSub);      return;
        case 2: call_by_address(kPC_FallingSub);       return;
        case 3: call_by_address(kPC_ClimbingSub);      return;
        default: return;  // matches the original's nes_log_inline_miss fallback
    }
    // $B359 NoMoveSub: RTS — unreachable here (each case returns).
}

// Phase 14 — $B450 PlayerPhysicsSub. Literal port of the per-frame physics
// dispatcher. Three branches off $1D Player_State: climbing → ProcClimb;
// not-climbing → CheckForJumping → (NoJump tail-call to $B51C X_Physics
// standalone, or InitJS to set up a fresh jump). InitJS picks the Y-physics
// tier from ROM tables at $B424/$B42B/$B439/$B432, indexed by $0700
// PlayerXSpeedAbsolute (categorical 0..4) and $0704 SwimmingFlag (extra +5).
//
// Branch polarity notes:
//   $B454 BNE CheckForJumping  -> if A != 3 (not climbing)
//   $B45D BEQ ProcClimb        -> if (Joypad & $0490) == 0
//   $B462 BNE ProcClimb        -> if (A & $08) != 0  (Up button)
//   $B47C BNE NoJump           -> if $070E != 0 (PlayerCtrlRoutine_Sel busy)
//   $B482 BEQ NoJump           -> if (Joypad_held & $80) == 0
//   $B486 BEQ ProcJumping      -> if (A & $0D) == 0
//   $B48D BEQ InitJS           -> if $1D == 0 (was on ground)
//   $B492 BEQ NoJump           -> if $0704 == 0 (not swimming)
//   $B497 BNE InitJS           -> if $0782 != 0
//   $B49B BPL InitJS           -> if $9F sign bit clear
//   $B4C0/$B4C5/$B4CA/$B4CF BCC ChkWtr -> if A < threshold
//   $B4DA BEQ GetYPhy          -> if $0704 == 0
//   $B4E1 BEQ GetYPhy          -> if $047D == 0
//   $B4FE BEQ PJumpSnd         -> if $0704 == 0
//   $B508 BCS X_Physics        -> if $CE >= $14
//   $B516 BEQ SJumpSnd         -> if Y == 0 (PlayerSize 0 = tall)
void PlayerPhysics::physics_sub() {
    // $B450: A = $1D (Player_State).
    g_cpu.A = state_.read8(0x001D);
    // $B452: CMP #$03. $B454: BNE CheckForJumping.
    g_cpu.C = (g_cpu.A >= 0x03) ? 1 : 0;
    if (g_cpu.A != 0x03) goto CheckForJumping;

    // ProcClimb path — choose climbing-state animation tier.
    g_cpu.Y = 0x00;
    // $B458: A = $0B. $B45A: A &= $0490.
    g_cpu.A = state_.read8(0x000B);
    g_cpu.A &= state_.read8(0x0490);
    // $B45D: BEQ ProcClimb.
    if (g_cpu.A == 0) goto ProcClimb;
    g_cpu.Y = static_cast<std::uint8_t>((g_cpu.Y + 1) & 0xFF);
    // $B460: A &= #$08 (Up button).
    g_cpu.A &= 0x08;
    // $B462: BNE ProcClimb.
    if (g_cpu.A != 0) goto ProcClimb;
    g_cpu.Y = static_cast<std::uint8_t>((g_cpu.Y + 1) & 0xFF);

ProcClimb:
    // $B465: X = ROM[$B44D + Y]. $B468: STX $0433.
    g_cpu.X = nes_read(static_cast<std::uint16_t>(0xB44D + g_cpu.Y));
    state_.write8(0x0433, g_cpu.X);
    // $B46B: A = #$08.
    g_cpu.A = 0x08;
    // $B46D: X = ROM[$B44A + Y]. $B470: STX $9F. N=X[7].
    g_cpu.X = nes_read(static_cast<std::uint16_t>(0xB44A + g_cpu.Y));
    state_.write8(0x009F, g_cpu.X);
    // $B472: BMI SetCAnim — skip LSR if X (last LDX result) has bit 7 set.
    if ((g_cpu.X & 0x80) == 0) {
        // $B474: LSR A.
        g_cpu.C = static_cast<std::uint8_t>(g_cpu.A & 1);
        g_cpu.A = static_cast<std::uint8_t>((g_cpu.A >> 1) & 0xFF);
    }
    // $B475 SetCAnim: STA $070C. $B478: RTS.
    state_.write8(0x070C, g_cpu.A);
    return;

CheckForJumping:
    // $B479: A = $070E (PlayerCtrlRoutine_Sel).
    g_cpu.A = state_.read8(0x070E);
    // $B47C: BNE NoJump.
    if (g_cpu.A != 0) goto NoJump;
    // $B47E: A = $0A. $B480: A &= #$80.
    g_cpu.A = state_.read8(0x000A);
    g_cpu.A &= 0x80;
    // $B482: BEQ NoJump.
    if (g_cpu.A == 0) goto NoJump;
    // $B484: A &= $0D.
    g_cpu.A &= state_.read8(0x000D);
    // $B486: BEQ ProcJumping.
    if (g_cpu.A == 0) goto ProcJumping;
    // fall through to NoJump

NoJump:
    // $B488: JMP $B51C X_Physics (standalone tail-call).
    call_by_address(0xB51C);
    return;

ProcJumping:
    // $B48B: A = $1D. $B48D: BEQ InitJS.
    g_cpu.A = state_.read8(0x001D);
    if (g_cpu.A == 0) goto InitJS;
    // $B48F: A = $0704. $B492: BEQ NoJump.
    g_cpu.A = state_.read8(0x0704);
    if (g_cpu.A == 0) goto NoJump;
    // $B494: A = $0782. $B497: BNE InitJS.
    g_cpu.A = state_.read8(0x0782);
    if (g_cpu.A != 0) goto InitJS;
    // $B499: A = $9F. $B49B: BPL InitJS.
    g_cpu.A = state_.read8(0x009F);
    if ((g_cpu.A & 0x80) == 0) goto InitJS;
    // $B49D: JMP X_Physics.
    call_by_address(0xB51C);
    return;

InitJS:
    // $B4A0: A = #$20. $B4A2: STA $0782.
    g_cpu.A = 0x20;
    state_.write8(0x0782, 0x20);
    // $B4A5: Y = 0. $B4A7: STY $0416. $B4AA: STY $0433.
    g_cpu.Y = 0x00;
    state_.write8(0x0416, 0x00);
    state_.write8(0x0433, 0x00);
    // $B4AD: A = $B5. $B4AF: STA $0707.
    g_cpu.A = state_.read8(0x00B5);
    state_.write8(0x0707, g_cpu.A);
    // $B4B2: A = $CE. $B4B4: STA $0708.
    g_cpu.A = state_.read8(0x00CE);
    state_.write8(0x0708, g_cpu.A);
    // $B4B7: A = #$01. $B4B9: STA $1D.
    g_cpu.A = 0x01;
    state_.write8(0x001D, 0x01);
    // $B4BB: A = $0700 (PlayerXSpeedAbsolute).
    g_cpu.A = state_.read8(0x0700);
    // $B4BE: CMP #$09. $B4C0: BCC ChkWtr.
    g_cpu.C = (g_cpu.A >= 0x09) ? 1 : 0;
    if (!g_cpu.C) goto ChkWtr;
    g_cpu.Y = static_cast<std::uint8_t>((g_cpu.Y + 1) & 0xFF);
    // $B4C3: CMP #$10. $B4C5: BCC ChkWtr.
    g_cpu.C = (g_cpu.A >= 0x10) ? 1 : 0;
    if (!g_cpu.C) goto ChkWtr;
    g_cpu.Y = static_cast<std::uint8_t>((g_cpu.Y + 1) & 0xFF);
    // $B4C8: CMP #$19. $B4CA: BCC ChkWtr.
    g_cpu.C = (g_cpu.A >= 0x19) ? 1 : 0;
    if (!g_cpu.C) goto ChkWtr;
    g_cpu.Y = static_cast<std::uint8_t>((g_cpu.Y + 1) & 0xFF);
    // $B4CD: CMP #$1C. $B4CF: BCC ChkWtr.
    g_cpu.C = (g_cpu.A >= 0x1C) ? 1 : 0;
    if (!g_cpu.C) goto ChkWtr;
    // $B4D1: INY.
    g_cpu.Y = static_cast<std::uint8_t>((g_cpu.Y + 1) & 0xFF);

ChkWtr:
    // $B4D2: A = #$01. $B4D4: STA $0706.
    g_cpu.A = 0x01;
    state_.write8(0x0706, 0x01);
    // $B4D7: A = $0704. $B4DA: BEQ GetYPhy.
    g_cpu.A = state_.read8(0x0704);
    if (g_cpu.A == 0) goto GetYPhy;
    // $B4DC: Y = #$05.
    g_cpu.Y = 0x05;
    // $B4DE: A = $047D. $B4E1: BEQ GetYPhy.
    g_cpu.A = state_.read8(0x047D);
    if (g_cpu.A == 0) goto GetYPhy;
    // $B4E3: INY.
    g_cpu.Y = static_cast<std::uint8_t>((g_cpu.Y + 1) & 0xFF);

GetYPhy:
    // $B4E4: A = ROM[$B424 + Y]. $B4E7: STA $0709.
    g_cpu.A = nes_read(static_cast<std::uint16_t>(0xB424 + g_cpu.Y));
    state_.write8(0x0709, g_cpu.A);
    // $B4EA: A = ROM[$B42B + Y]. $B4ED: STA $070A.
    g_cpu.A = nes_read(static_cast<std::uint16_t>(0xB42B + g_cpu.Y));
    state_.write8(0x070A, g_cpu.A);
    // $B4F0: A = ROM[$B439 + Y]. $B4F3: STA $0433.
    g_cpu.A = nes_read(static_cast<std::uint16_t>(0xB439 + g_cpu.Y));
    state_.write8(0x0433, g_cpu.A);
    // $B4F6: A = ROM[$B432 + Y]. $B4F9: STA $9F.
    g_cpu.A = nes_read(static_cast<std::uint16_t>(0xB432 + g_cpu.Y));
    state_.write8(0x009F, g_cpu.A);
    // $B4FB: A = $0704. $B4FE: BEQ PJumpSnd.
    g_cpu.A = state_.read8(0x0704);
    if (g_cpu.A == 0) goto PJumpSnd;
    // $B500: A = #$04. $B502: STA $FF (queue Square1 SFX channel).
    g_cpu.A = 0x04;
    state_.write8(0x00FF, 0x04);
    // $B504: A = $CE. $B506: CMP #$14. $B508: BCS X_Physics.
    g_cpu.A = state_.read8(0x00CE);
    g_cpu.C = (g_cpu.A >= 0x14) ? 1 : 0;
    if (g_cpu.C) {
        call_by_address(0xB51C);
        return;
    }
    // $B50A: A = #$00. $B50C: STA $9F.
    g_cpu.A = 0x00;
    state_.write8(0x009F, 0x00);
    // $B50E: JMP X_Physics.
    call_by_address(0xB51C);
    return;

PJumpSnd:
    // $B511: A = #$01. $B513: Y = $0754 (PlayerSize). $B516: BEQ SJumpSnd.
    g_cpu.A = 0x01;
    g_cpu.Y = state_.read8(0x0754);
    if (g_cpu.Y == 0) goto SJumpSnd;
    // $B518: A = #$80.
    g_cpu.A = 0x80;

SJumpSnd:
    // $B51A: STA $FF. Fall through to X_Physics.
    state_.write8(0x00FF, g_cpu.A);
    call_by_address(0xB51C);
}

// Phase 15 — MovePlayer family.

void PlayerPhysics::move_player_y_axis() {
    // $B200: CLC; ADC $CE; STA $CE; RTS.
    g_cpu.C = 0;
    {
        const std::uint8_t m = state_.read8(0x00CE);
        const std::uint16_t r = static_cast<std::uint16_t>(g_cpu.A) + m + g_cpu.C;
        g_cpu.C = (r > 0xFF) ? 1 : 0;
        g_cpu.A = static_cast<std::uint8_t>(r & 0xFF);
    }
    state_.write8(0x00CE, g_cpu.A);
}

void PlayerPhysics::ex_x_move() {
    // $BF4C: RTS (early-exit point of $BF09; also separately callable).
}

void PlayerPhysics::move_player_horizontally() {
    // $BF09: A = $070E (PlayerCtrlRoutine_Sel).
    g_cpu.A = state_.read8(0x070E);
    // $BF0C: BNE ExXMove.
    if (g_cpu.A != 0) return;
    // $BF0E: TAX (A==0, so X=0). FLAG_NZ(X)
    g_cpu.X = g_cpu.A;
    // MoveObjectHorizontally at $BF0F — runs with the just-set X.
    // $BF0F: A = $57+X (player obj velocity).
    g_cpu.A = state_.read8(static_cast<std::uint16_t>((0x57 + g_cpu.X) & 0xFF));
    // $BF11-$BF14: 4x ASL — extract top 4 bits as low nibble of $01.
    for (int i = 0; i < 4; ++i) {
        g_cpu.C = static_cast<std::uint8_t>((g_cpu.A >> 7) & 1);
        g_cpu.A = static_cast<std::uint8_t>((g_cpu.A << 1) & 0xFF);
    }
    // $BF15: STA $01.
    state_.write8(0x0001, g_cpu.A);
    // $BF17: A = $57+X again.
    g_cpu.A = state_.read8(static_cast<std::uint16_t>((0x57 + g_cpu.X) & 0xFF));
    // $BF19-$BF1C: 4x LSR — extract high 4 bits as low nibble.
    for (int i = 0; i < 4; ++i) {
        g_cpu.C = static_cast<std::uint8_t>(g_cpu.A & 1);
        g_cpu.A = static_cast<std::uint8_t>((g_cpu.A >> 1) & 0xFF);
    }
    // $BF1D: CMP #$08.
    g_cpu.C = (g_cpu.A >= 0x08) ? 1 : 0;
    // $BF1F: BCC SaveXSpd.
    if (g_cpu.C) {
        // $BF21: A |= #$F0 (sign-extend nibble to signed 8-bit negative).
        g_cpu.A |= 0xF0;
    }
    // $BF23 SaveXSpd: STA $00.
    state_.write8(0x0000, g_cpu.A);
    // $BF25: Y = 0. $BF27: CMP #$00. $BF29: BPL UseAdder.
    g_cpu.Y = 0x00;
    g_cpu.C = (g_cpu.A >= 0x00) ? 1 : 0;  // always true since A is 8-bit
    // BPL is "branch if N=0" — N = A bit 7. So if A >= 0x80, signed-negative.
    if ((g_cpu.A & 0x80) != 0) {
        // $BF2B: DEY -> Y = $FF (sign extension).
        g_cpu.Y = static_cast<std::uint8_t>((g_cpu.Y - 1) & 0xFF);
    }
    // $BF2C UseAdder: STY $02.
    state_.write8(0x0002, g_cpu.Y);
    // $BF2E: A = $0400+X. $BF31: CLC. $BF32: ADC $01.
    g_cpu.A = state_.read8(static_cast<std::uint16_t>(0x0400 + g_cpu.X));
    g_cpu.C = 0;
    {
        const std::uint8_t m = state_.read8(0x0001);
        const std::uint16_t r = static_cast<std::uint16_t>(g_cpu.A) + m + g_cpu.C;
        g_cpu.C = (r > 0xFF) ? 1 : 0;
        g_cpu.A = static_cast<std::uint8_t>(r & 0xFF);
    }
    // $BF34: STA $0400+X.
    state_.write8(static_cast<std::uint16_t>(0x0400 + g_cpu.X), g_cpu.A);
    // $BF37: A = #$00. $BF39: ROL A (pulls carry into bit 0).
    g_cpu.A = 0x00;
    {
        const std::uint8_t c = g_cpu.C;
        g_cpu.C = static_cast<std::uint8_t>((g_cpu.A >> 7) & 1);
        g_cpu.A = static_cast<std::uint8_t>(((g_cpu.A << 1) | c) & 0xFF);
    }
    // $BF3A: PHA — push carry-extended adder. We use a local instead.
    const std::uint8_t carry_high = g_cpu.A;
    // $BF3B: ROR A — restore carry.
    {
        const std::uint8_t c = g_cpu.C;
        g_cpu.C = static_cast<std::uint8_t>(g_cpu.A & 1);
        g_cpu.A = static_cast<std::uint8_t>(((g_cpu.A >> 1) | (c << 7)) & 0xFF);
    }
    // $BF3C: A = $86+X (X position low). $BF3E: ADC $00.
    g_cpu.A = state_.read8(static_cast<std::uint16_t>((0x86 + g_cpu.X) & 0xFF));
    {
        const std::uint8_t m = state_.read8(0x0000);
        const std::uint16_t r = static_cast<std::uint16_t>(g_cpu.A) + m + g_cpu.C;
        g_cpu.C = (r > 0xFF) ? 1 : 0;
        g_cpu.A = static_cast<std::uint8_t>(r & 0xFF);
    }
    // $BF40: STA $86+X.
    state_.write8(static_cast<std::uint16_t>((0x86 + g_cpu.X) & 0xFF), g_cpu.A);
    // $BF42: A = $6D+X (X position high). $BF44: ADC $02.
    g_cpu.A = state_.read8(static_cast<std::uint16_t>((0x6D + g_cpu.X) & 0xFF));
    {
        const std::uint8_t m = state_.read8(0x0002);
        const std::uint16_t r = static_cast<std::uint16_t>(g_cpu.A) + m + g_cpu.C;
        g_cpu.C = (r > 0xFF) ? 1 : 0;
        g_cpu.A = static_cast<std::uint8_t>(r & 0xFF);
    }
    // $BF46: STA $6D+X.
    state_.write8(static_cast<std::uint16_t>((0x6D + g_cpu.X) & 0xFF), g_cpu.A);
    // $BF48: PLA (restore carry-extended adder).
    g_cpu.A = carry_high;
    // $BF49: CLC. $BF4A: ADC $00 (return-value calculation, A holds final result).
    g_cpu.C = 0;
    {
        const std::uint8_t m = state_.read8(0x0000);
        const std::uint16_t r = static_cast<std::uint16_t>(g_cpu.A) + m + g_cpu.C;
        g_cpu.C = (r > 0xFF) ? 1 : 0;
        g_cpu.A = static_cast<std::uint8_t>(r & 0xFF);
    }
    // $BF4C: RTS (leaves A as the carry-extended displacement for caller).
}

void PlayerPhysics::move_player_vertically() {
    // $BF4D: X = 0. $BF4F: A = $0747. $BF52: BNE NoJSChk.
    g_cpu.X = 0x00;
    g_cpu.A = state_.read8(0x0747);
    if (g_cpu.A != 0) goto NoJSChk;
    // $BF54: A = $070E. $BF57: BNE -> ExXMove ($BF4C).
    g_cpu.A = state_.read8(0x070E);
    if (g_cpu.A != 0) return;  // Equivalent to call_by_address(0xBF4C) which is RTS.
NoJSChk:
    // $BF59: A = $0709. $BF5C: STA $00.
    g_cpu.A = state_.read8(0x0709);
    state_.write8(0x0000, g_cpu.A);
    // $BF5E: A = #$04. $BF60: JMP $BFAD ImposeGravitySprObj.
    g_cpu.A = 0x04;
    call_by_address(0xBFAD);
}

}  // namespace smb::semcomp
