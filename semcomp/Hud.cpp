// semcomp/Hud.cpp — replacement bodies for $8F06 + $BC27.
#include "semcomp/Hud.h"

#include "semcomp/GameState.h"
#include "semcomp/SmbRamMap.h"
#include "semcomp/cpu_flags.h"

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

// Phase 20 — HUD math untangle (verbatim ports).

void Hud::digits_math_routine() {
    (void)state_;
label_8F5F:; /* DigitsMathRoutine */
    /* $8F5F: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0770); FLAG_NZ(g_cpu.A);
label_8F62:;
    /* $8F62: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x00; g_cpu.C=(g_cpu.A>=0x00)?1:0; FLAG_NZ(r&0xFF); }
label_8F64:;
    /* $8F64: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_8F7C;
label_8F66:;
    /* $8F66: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x05; FLAG_NZ(g_cpu.X);
label_8F68:; /* AddModLoop */
    /* $8F68: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0134 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_8F6B:;
    /* $8F6B: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_8F6C:;
    /* $8F6C: 79 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x07D7 + g_cpu.Y) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_8F6F:;
    /* $8F6F: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_8F87;
label_8F71:;
    /* $8F71: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0A; g_cpu.C=(g_cpu.A>=0x0A)?1:0; FLAG_NZ(r&0xFF); }
label_8F73:;
    /* $8F73: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_8F8E;
label_8F75:; /* StoreNewD */
    /* $8F75: 99 */ maybe_trigger_vblank(5); nes_write((0x07D7 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_8F78:;
    /* $8F78: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_8F79:;
    /* $8F79: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_8F7A:;
    /* $8F7A: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
        maybe_trigger_vblank(2);
        goto label_8F68;
    }
label_8F7C:; /* EraseDMods */
    /* $8F7C: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_8F7E:;
    /* $8F7E: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x06; FLAG_NZ(g_cpu.X);
label_8F80:; /* EraseMLoop */
    /* $8F80: 9D */ maybe_trigger_vblank(5); nes_write((0x0133 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_8F83:;
    /* $8F83: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_8F84:;
    /* $8F84: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
        maybe_trigger_vblank(2);
        goto label_8F80;
    }
label_8F86:;
    /* $8F86: 60 */ maybe_trigger_vblank(6);
    return;
label_8F87:; /* BorrowOne */
    /* $8F87: DE */ maybe_trigger_vblank(7); { uint16_t a=(0x0133 + g_cpu.X) & 0xFFFF; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_8F8A:;
    /* $8F8A: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x09; FLAG_NZ(g_cpu.A);
label_8F8C:;
    /* $8F8C: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
        maybe_trigger_vblank(2);
        goto label_8F75;
    }
label_8F8E:; /* CarryOne */
    /* $8F8E: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_8F8F:;
    /* $8F8F: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x0A; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_8F91:;
    /* $8F91: FE */ maybe_trigger_vblank(7); { uint16_t a=(0x0133 + g_cpu.X) & 0xFFFF; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_8F94:;
    /* $8F94: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0x8F75); return;
}

void Hud::add_mod_loop() {
    // $8F68 AddModLoop — recompiler's standalone emission. Same body as
    // the $8F68 label inside digits_math_routine() but entered with Y, X
    // already set up by external callers (e.g., the StoreNewD continuation).
    (void)state_;
label_8F68:; /* AddModLoop */
    /* $8F68: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0134 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_8F6B:;
    /* $8F6B: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_8F6C:;
    /* $8F6C: 79 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x07D7 + g_cpu.Y) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_8F6F:;
    /* $8F6F: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_8F87;
label_8F71:;
    /* $8F71: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0A; g_cpu.C=(g_cpu.A>=0x0A)?1:0; FLAG_NZ(r&0xFF); }
label_8F73:;
    /* $8F73: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_8F8E;
label_8F75:; /* StoreNewD */
    /* $8F75: 99 */ maybe_trigger_vblank(5); nes_write((0x07D7 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_8F78:;
    /* $8F78: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_8F79:;
    /* $8F79: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_8F7A:;
    /* $8F7A: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
        maybe_trigger_vblank(2);
        goto label_8F68;
    }
label_8F7C:;
    /* $8F7C: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_8F7E:;
    /* $8F7E: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x06; FLAG_NZ(g_cpu.X);
label_8F80:;
    /* $8F80: 9D */ maybe_trigger_vblank(5); nes_write((0x0133 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_8F83:;
    /* $8F83: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_8F84:;
    /* $8F84: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
        maybe_trigger_vblank(2);
        goto label_8F80;
    }
label_8F86:;
    /* $8F86: 60 */ maybe_trigger_vblank(6);
    return;
label_8F87:;
    /* $8F87: DE */ maybe_trigger_vblank(7); { uint16_t a=(0x0133 + g_cpu.X) & 0xFFFF; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_8F8A:;
    /* $8F8A: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x09; FLAG_NZ(g_cpu.A);
label_8F8C:;
    /* $8F8C: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
        maybe_trigger_vblank(2);
        goto label_8F75;
    }
label_8F8E:;
    /* $8F8E: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_8F8F:;
    /* $8F8F: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x0A; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_8F91:;
    /* $8F91: FE */ maybe_trigger_vblank(7); { uint16_t a=(0x0133 + g_cpu.X) & 0xFFFF; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_8F94:;
    /* $8F94: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0x8F75); return;
}

void Hud::store_new_d() {
    (void)state_;
label_8F75:; /* StoreNewD */
    /* $8F75: 99 */ maybe_trigger_vblank(5); nes_write((0x07D7 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_8F78:;
    /* $8F78: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_8F79:;
    /* $8F79: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_8F7A:;
    /* $8F7A: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) { call_by_address(0x8F68); return; }
label_8F7C:;
    /* $8F7C: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_8F7E:;
    /* $8F7E: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x06; FLAG_NZ(g_cpu.X);
label_8F80:;
    /* $8F80: 9D */ maybe_trigger_vblank(5); nes_write((0x0133 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_8F83:;
    /* $8F83: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_8F84:;
    /* $8F84: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
        maybe_trigger_vblank(2);
        goto label_8F80;
    }
label_8F86:;
    /* $8F86: 60 */ maybe_trigger_vblank(6);
}

void Hud::output_numbers() {
    (void)state_;
label_8F11:; /* OutputNumbers */
    /* $8F11: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_8F12:;
    /* $8F12: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x01 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x01); g_cpu.A=r&0xFF; }
label_8F14:;
    /* $8F14: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x0F; FLAG_NZ(g_cpu.A);
label_8F16:;
    /* $8F16: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x06; g_cpu.C=(g_cpu.A>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_8F18:;
    /* $8F18: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_8F5E;
label_8F1A:;
    /* $8F1A: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_8F1B:;
    /* $8F1B: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_8F1C:;
    /* $8F1C: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_8F1D:;
    /* $8F1D: AE */ maybe_trigger_vblank(4); g_cpu.X = nes_read(0x0300); FLAG_NZ(g_cpu.X);
label_8F20:;
    /* $8F20: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x20; FLAG_NZ(g_cpu.A);
label_8F22:;
    /* $8F22: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x00; g_cpu.C=(g_cpu.Y>=0x00)?1:0; FLAG_NZ(r&0xFF); }
label_8F24:;
    /* $8F24: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_8F28;
label_8F26:;
    /* $8F26: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x22; FLAG_NZ(g_cpu.A);
label_8F28:;
    /* $8F28: 9D */ maybe_trigger_vblank(5); nes_write((0x0301 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_8F2B:;
    /* $8F2B: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x8EF4 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_8F2E:;
    /* $8F2E: 9D */ maybe_trigger_vblank(5); nes_write((0x0302 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_8F31:;
    /* $8F31: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x8EF5 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_8F34:;
    /* $8F34: 9D */ maybe_trigger_vblank(5); nes_write((0x0303 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_8F37:;
    /* $8F37: 85 */ maybe_trigger_vblank(3); nes_write(0x03, g_cpu.A);
label_8F39:;
    /* $8F39: 86 */ maybe_trigger_vblank(3); nes_write(0x02, g_cpu.X);
label_8F3B:;
    /* $8F3B: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_8F3C:;
    /* $8F3C: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_8F3D:;
    /* $8F3D: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x8F00 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_8F40:;
    /* $8F40: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_8F41:;
    /* $8F41: F9 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x8EF5 + g_cpu.Y) & 0xFFFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_8F44:;
    /* $8F44: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_8F45:;
    /* $8F45: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x02); FLAG_NZ(g_cpu.X);
label_8F47:;
    /* $8F47: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x07D7 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_8F4A:;
    /* $8F4A: 9D */ maybe_trigger_vblank(5); nes_write((0x0304 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_8F4D:;
    /* $8F4D: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_8F4E:;
    /* $8F4E: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_8F4F:;
    /* $8F4F: C6 */ maybe_trigger_vblank(5); { uint16_t a=0x03; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_8F51:;
    /* $8F51: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
        maybe_trigger_vblank(2);
        goto label_8F47;
    }
label_8F53:;
    /* $8F53: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_8F55:;
    /* $8F55: 9D */ maybe_trigger_vblank(5); nes_write((0x0304 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_8F58:;
    /* $8F58: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_8F59:;
    /* $8F59: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_8F5A:;
    /* $8F5A: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_8F5B:;
    /* $8F5B: 8E */ maybe_trigger_vblank(4); nes_write(0x0300, g_cpu.X);
label_8F5E:;
    /* $8F5E: 60 */ maybe_trigger_vblank(6);
}

}  // namespace smb::semcomp
