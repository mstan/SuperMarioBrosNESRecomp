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
