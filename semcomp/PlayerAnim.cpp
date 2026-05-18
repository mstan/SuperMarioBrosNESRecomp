// semcomp/PlayerAnim.cpp — replacement bodies for $B233, $B245, $B269, $B27D.
#include "semcomp/PlayerAnim.h"

#include "semcomp/GameState.h"

extern "C" {
#include "nes_runtime.h"
}

namespace smb::semcomp {

namespace {
// Animation timer byte ($0747). Decremented each frame; thresholds
// drive the state transitions.
constexpr std::uint16_t kRam_AnimTimer = 0x0747;

// Natural-generated callees.
constexpr std::uint16_t kPC_PlayerCtrlRoutine    = 0xB0E9;
constexpr std::uint16_t kPC_InitChangeSize       = 0xB255;
constexpr std::uint16_t kPC_DonePlayerTask       = 0xB273;
constexpr std::uint16_t kPC_CyclePlayerPalette   = 0xB288;
constexpr std::uint16_t kPC_ResetPalStar         = 0xB29A;
}  // namespace

void PlayerAnim::change_size() {
    // $B233: A = $0747
    // $B238: BNE label_B23D (skip InitChangeSize unless A == $F8)
    // $B23A: JMP InitChangeSize
    // label_B23D EndChgSize: CMP #$C4 / BNE ExitChgSize / JSR DonePlayerTask
    const std::uint8_t t = state_.read8(kRam_AnimTimer);
    if (t == 0xF8) {
        call_by_address(kPC_InitChangeSize);
        return;
    }
    if (t == 0xC4) {
        call_by_address(kPC_DonePlayerTask);
    }
    // ExitChgSize: RTS
}

void PlayerAnim::injury_blink() {
    // $B245: A = $0747
    // $B248-$B24A: CMP #$F0 / BCS ExitBlink ($B253)
    // $B24C-$B24E: CMP #$C8 / BEQ DonePlayerTask ($B273)
    // $B250: JMP PlayerCtrlRoutine
    // label_B253 ExitBlink: BNE ExitBoth (only fall-through when A == $F0)
    // label_B255: InitChangeSize body inline (toggle PlayerSize)
    const std::uint8_t t = state_.read8(kRam_AnimTimer);
    if (t >= 0xF0) {
        if (t != 0xF0) return;  // ExitBoth — RTS without doing anything
        // Fall-through: $0747 == $F0 → fire InitChangeSize once.
        call_by_address(kPC_InitChangeSize);
        return;
    }
    if (t == 0xC8) {
        call_by_address(kPC_DonePlayerTask);
        return;
    }
    call_by_address(kPC_PlayerCtrlRoutine);
}

void PlayerAnim::player_death() {
    // $B269: A = $0747
    // $B26C-$B26E: CMP #$F0 / BCS ExitDeath ($B2A3)
    // $B270: JMP PlayerCtrlRoutine
    const std::uint8_t t = state_.read8(kRam_AnimTimer);
    if (t >= 0xF0) return;  // ExitDeath
    call_by_address(kPC_PlayerCtrlRoutine);
}

void PlayerAnim::fire_flower() {
    // $B27D: A = $0747
    // $B280-$B282: CMP #$C0 / BEQ ResetPalFireFlower ($B297)
    // $B284-$B287: A = $09 (frame counter) ; LSR x2
    // $B288 CyclePlayerPalette: A &= $03 ; stage palette ; write $03C4
    //
    // For the "else" branch (palette cycle), we delegate to the
    // separately-emitted $B288 CyclePlayerPalette which is itself
    // called by other parts of the engine (line 7341, 14914).
    //
    // For the "$0747 == $C0" branch (ResetPalFireFlower at $B297):
    // JSR DonePlayerTask ($B273); then fall into ResetPalStar ($B29A,
    // separately emitted) which clears the palette low bits.
    const std::uint8_t t = state_.read8(kRam_AnimTimer);
    if (t == 0xC0) {
        call_by_address(kPC_DonePlayerTask);
        call_by_address(kPC_ResetPalStar);
        return;
    }
    // CyclePlayerPalette tick. $B288 reads $09 internally (it doesn't
    // take A pre-staged for this call form — the LSRs happen inline
    // inside $B27D's body, but $B288 entry-point itself starts at
    // CyclePlayerPalette which expects the frame-counter logic done.
    // The standalone-emitted func_B288_b0 starts at $B288 with
    // AND #$03 — assumes A is already set. We need to stage A:
    {
        const std::uint8_t frame_ctr = state_.read8(0x0009);
        g_cpu.A = static_cast<std::uint8_t>(frame_ctr >> 2);
    }
    call_by_address(kPC_CyclePlayerPalette);
}

}  // namespace smb::semcomp
