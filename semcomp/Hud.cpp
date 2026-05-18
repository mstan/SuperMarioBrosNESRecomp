// semcomp/Hud.cpp — replacement bodies for $8F06 + $BC27.
#include "semcomp/Hud.h"

#include "semcomp/GameState.h"
#include "semcomp/SmbRamMap.h"

extern "C" {
#include "nes_runtime.h"
}

namespace smb::semcomp {

namespace {
// Callees we don't own (yet). Standalone emissions.
constexpr std::uint16_t kPC_OutputNumbers     = 0x8F11;
constexpr std::uint16_t kPC_DigitsMathRoutine = 0x8F5F;
constexpr std::uint16_t kPC_PrintStatusBarNum = 0x8F06;  // self — via call_by_address from add_to_score
}  // namespace

void Hud::print_status_bar_numbers() {
    // A on entry holds the nybbles control byte. Save to $00 scratch.
    const std::uint8_t nybbles = g_cpu.A;
    state_.write8(0x0000, nybbles);

    // First pass: low nybble selects field, OutputNumbers stages tiles.
    g_cpu.A = nybbles;  // OutputNumbers will mask with AND #$0F internally
    call_by_address(kPC_OutputNumbers);

    // Reload + shift right 4 (the natural code does LSR x4). The
    // following ADC #$01 inside OutputNumbers CLCs first so the
    // residual C from the LSRs doesn't matter; we don't need to
    // mimic the LSR's flag side effects.
    g_cpu.A = static_cast<std::uint8_t>(nybbles >> 4);
    call_by_address(kPC_OutputNumbers);
    // Return — RTS in 6502, normal C return here.
}

void Hud::add_to_score() {
    // $BC27: LDX $0753 — CurrentPlayer index.
    g_cpu.X = state_.read8(ram::CurrentPlayer);

    // $BC2A: LDY ROM_ScoreOffsets,X — pick per-player digit-start index.
    g_cpu.Y = nes_read(static_cast<std::uint16_t>(ram::ROM_ScoreOffsets + g_cpu.X));

    // $BC2D: JSR DigitsMathRoutine — applies staged DigitModifier[i]
    // values to the BCD score digits at $07D7+Y. Not owned (inner-label
    // issue); call into the natural-generated body.
    call_by_address(kPC_DigitsMathRoutine);

    // $BC30: LDY $0753 — reload CurrentPlayer.
    g_cpu.Y = state_.read8(ram::CurrentPlayer);

    // $BC33: LDA ROM_StatusBarNybbles,Y — which HUD fields to refresh
    // for this player.
    g_cpu.A = nes_read(static_cast<std::uint16_t>(ram::ROM_StatusBarNybbles + g_cpu.Y));

    // $BC36: JSR PrintStatusBarNumbers — dispatches back to THIS class
    // via our [[replace_func]] for $8F06.
    call_by_address(kPC_PrintStatusBarNum);

    // $BC39-$BC45: leading-zero suppression in the VRAM_Buffer1 entry.
    // Y = $0300 (VRAM_Buffer1_Offset). If $02FB+Y == 0, replace with
    // tile $24 (blank sky) so the rendered HUD doesn't show a leading
    // 0 digit.
    g_cpu.Y = state_.read8(ram::VRAM_Buffer1_Offset);
    const std::uint16_t leading_addr = static_cast<std::uint16_t>(
        ram::VRAM_Buffer1_BackQueue + g_cpu.Y);
    if (state_.read8(leading_addr) == 0) {
        state_.write8(leading_addr, 0x24);
    }

    // $BC46: LDX $08 — restore the scratch X save (caller saves X via
    // STX $08 before calling AddToScore in some paths).
    g_cpu.X = state_.read8(ram::ZP_Scratch_08);
    // RTS — normal C return.
}

}  // namespace smb::semcomp
