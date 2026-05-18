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

// ---- Phase 11 ports (reduced scope) ---------------------------------------
//
// Each method is a literal port of the recompiler's generated body for the
// corresponding 6502 routine. Sub-callees stay natural-generated and are
// invoked via call_by_address (which dispatches through the recompiler's
// table — every emitted func_XXXX_b0 has a case).
//
// JumpSwimSub / ClimbingSub / PhysicsSub deferred to dedicated phases due
// to scale + branch density.

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

}  // namespace smb::semcomp
