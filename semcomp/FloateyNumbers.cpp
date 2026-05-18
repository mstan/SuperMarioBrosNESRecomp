// semcomp/FloateyNumbers.cpp — replacement body for $DA11 SetupFloateyNumber.
#include "semcomp/FloateyNumbers.h"

#include "semcomp/GameState.h"
#include "semcomp/cpu_flags.h"

extern "C" {
#include "nes_runtime.h"
}

namespace smb::semcomp {

void FloateyNumbers::setup() {
    const std::uint8_t slot = g_cpu.X;
    const std::uint8_t points_index = g_cpu.A;

    // $DA11: STA $0110,X — store points-table index.
    state_.write8(static_cast<std::uint16_t>(0x0110 + slot), points_index);

    // $DA14-$DA16: A = $30; STA $012C,X — initial animation counter.
    state_.write8(static_cast<std::uint16_t>(0x012C + slot), 0x30);

    // $DA19-$DA1B: A = $CF+X (spawning slot's Y); STA $011E+X.
    {
        const std::uint8_t spawn_y = state_.read8(
            static_cast<std::uint16_t>(0x00CF + slot));
        state_.write8(static_cast<std::uint16_t>(0x011E + slot), spawn_y);
    }

    // $DA1E-$DA21: A = $03AE; STA $0117+X (lifetime timer seed).
    {
        const std::uint8_t timer_seed = state_.read8(0x03AE);
        state_.write8(static_cast<std::uint16_t>(0x0117 + slot), timer_seed);
    }
    // $DA24 ExSFN: RTS
}

// Phase 21 — Floatey per-frame untangle.

void FloateyNumbers::per_frame_tick() {
    (void)state_;
label_84C3:; /* FloateyNumbersRoutine */
    /* $84C3: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0110 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_84C6:;
    /* $84C6: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { call_by_address(0x8486); return; }
label_84C8:;
    /* $84C8: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0B; g_cpu.C=(g_cpu.A>=0x0B)?1:0; FLAG_NZ(r&0xFF); }
label_84CA:;
    /* $84CA: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_84D1;
label_84CC:;
    /* $84CC: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0B; FLAG_NZ(g_cpu.A);
label_84CE:;
    /* $84CE: 9D */ maybe_trigger_vblank(5); nes_write((0x0110 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_84D1:;
    /* $84D1: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_84D2:;
    /* $84D2: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x012C + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_84D5:;
    /* $84D5: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_84DB;
label_84D7:;
    /* $84D7: 9D */ maybe_trigger_vblank(5); nes_write((0x0110 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_84DA:;
    /* $84DA: 60 */ maybe_trigger_vblank(6);
    return;
label_84DB:;
    /* $84DB: DE */ maybe_trigger_vblank(7); { uint16_t a=(0x012C + g_cpu.X) & 0xFFFF; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_84DE:;
    /* $84DE: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x2B; g_cpu.C=(g_cpu.A>=0x2B)?1:0; FLAG_NZ(r&0xFF); }
label_84E0:;
    /* $84E0: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_8500;
label_84E2:;
    /* $84E2: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x0B; g_cpu.C=(g_cpu.Y>=0x0B)?1:0; FLAG_NZ(r&0xFF); }
label_84E4:;
    /* $84E4: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_84ED;
label_84E6:;
    /* $84E6: EE */ maybe_trigger_vblank(6); { uint16_t a=0x075A; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_84E9:;
    /* $84E9: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x40; FLAG_NZ(g_cpu.A);
label_84EB:;
    /* $84EB: 85 */ maybe_trigger_vblank(3); nes_write(0xFE, g_cpu.A);
label_84ED:;
    /* $84ED: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x84B7 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_84F0:;
    /* $84F0: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_84F1:;
    /* $84F1: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_84F2:;
    /* $84F2: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_84F3:;
    /* $84F3: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_84F4:;
    /* $84F4: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_84F5:;
    /* $84F5: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x84B7 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_84F8:;
    /* $84F8: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x0F; FLAG_NZ(g_cpu.A);
label_84FA:;
    /* $84FA: 9D */ maybe_trigger_vblank(5); nes_write((0x0134 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_84FD:;
    /* $84FD: 20 */ maybe_trigger_vblank(6); call_by_address(0xBC27);
label_8500:;
    /* $8500: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x06E5 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_8503:;
    /* $8503: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_8505:;
    /* $8505: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x12; g_cpu.C=(g_cpu.A>=0x12)?1:0; FLAG_NZ(r&0xFF); }
label_8507:;
    /* $8507: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_852B;
label_8509:;
    /* $8509: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0D; g_cpu.C=(g_cpu.A>=0x0D)?1:0; FLAG_NZ(r&0xFF); }
label_850B:;
    /* $850B: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_852B;
label_850D:;
    /* $850D: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x05; g_cpu.C=(g_cpu.A>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_850F:;
    /* $850F: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_8523;
label_8511:;
    /* $8511: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0A; g_cpu.C=(g_cpu.A>=0x0A)?1:0; FLAG_NZ(r&0xFF); }
label_8513:;
    /* $8513: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_852B;
label_8515:;
    /* $8515: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0B; g_cpu.C=(g_cpu.A>=0x0B)?1:0; FLAG_NZ(r&0xFF); }
label_8517:;
    /* $8517: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_852B;
label_8519:;
    /* $8519: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x09; g_cpu.C=(g_cpu.A>=0x09)?1:0; FLAG_NZ(r&0xFF); }
label_851B:;
    /* $851B: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_8523;
label_851D:;
    /* $851D: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_851F:;
    /* $851F: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x02; g_cpu.C=(g_cpu.A>=0x02)?1:0; FLAG_NZ(r&0xFF); }
label_8521:;
    /* $8521: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_852B;
label_8523:;
    /* $8523: AE */ maybe_trigger_vblank(4); g_cpu.X = nes_read(0x03EE); FLAG_NZ(g_cpu.X);
label_8526:;
    /* $8526: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x06EC + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_8529:;
    /* $8529: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_852B:;
    /* $852B: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x011E + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_852E:;
    /* $852E: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x18; g_cpu.C=(g_cpu.A>=0x18)?1:0; FLAG_NZ(r&0xFF); }
label_8530:;
    /* $8530: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_8537;
label_8532:;
    /* $8532: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x01; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_8534:;
    /* $8534: 9D */ maybe_trigger_vblank(5); nes_write((0x011E + g_cpu.X) & 0xFFFF, g_cpu.A);
label_8537:;
    /* $8537: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x011E + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_853A:;
    /* $853A: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x08; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_853C:;
    /* $853C: 20 */ maybe_trigger_vblank(6); call_by_address(0xE5C1);
label_853F:;
    /* $853F: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0117 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_8542:;
    /* $8542: 99 */ maybe_trigger_vblank(5); nes_write((0x0203 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_8545:;
    /* $8545: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_8546:;
    /* $8546: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x08 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x08); g_cpu.A=r&0xFF; }
label_8548:;
    /* $8548: 99 */ maybe_trigger_vblank(5); nes_write((0x0207 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_854B:;
    /* $854B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_854D:;
    /* $854D: 99 */ maybe_trigger_vblank(5); nes_write((0x0202 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_8550:;
    /* $8550: 99 */ maybe_trigger_vblank(5); nes_write((0x0206 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_8553:;
    /* $8553: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0110 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_8556:;
    /* $8556: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_8557:;
    /* $8557: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_8558:;
    /* $8558: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x849F + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_855B:;
    /* $855B: 99 */ maybe_trigger_vblank(5); nes_write((0x0201 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_855E:;
    /* $855E: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x84A0 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_8561:;
    /* $8561: 99 */ maybe_trigger_vblank(5); nes_write((0x0205 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_8564:;
    /* $8564: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_8566:;
    /* $8566: 60 */ maybe_trigger_vblank(6);
}

void FloateyNumbers::floatey_part_8534() {
    // $8534 — re-entry into FloateyNumbersRoutine at the floatey-part
    // SetupNumSpr block, used when the caller has already set X (slot
    // index) and just wants the sprite-stage portion to run.
    (void)state_;
label_8534:; /* FloateyPart re-entry */
    /* $8534: 9D */ maybe_trigger_vblank(5); nes_write((0x011E + g_cpu.X) & 0xFFFF, g_cpu.A);
label_8537:;
    /* $8537: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x011E + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_853A:;
    /* $853A: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x08; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_853C:;
    /* $853C: 20 */ maybe_trigger_vblank(6); call_by_address(0xE5C1);
label_853F:;
    /* $853F: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0117 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_8542:;
    /* $8542: 99 */ maybe_trigger_vblank(5); nes_write((0x0203 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_8545:;
    /* $8545: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_8546:;
    /* $8546: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x08 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x08); g_cpu.A=r&0xFF; }
label_8548:;
    /* $8548: 99 */ maybe_trigger_vblank(5); nes_write((0x0207 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_854B:;
    /* $854B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_854D:;
    /* $854D: 99 */ maybe_trigger_vblank(5); nes_write((0x0202 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_8550:;
    /* $8550: 99 */ maybe_trigger_vblank(5); nes_write((0x0206 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_8553:;
    /* $8553: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0110 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_8556:;
    /* $8556: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_8557:;
    /* $8557: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_8558:;
    /* $8558: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x849F + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_855B:;
    /* $855B: 99 */ maybe_trigger_vblank(5); nes_write((0x0201 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_855E:;
    /* $855E: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x84A0 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_8561:;
    /* $8561: 99 */ maybe_trigger_vblank(5); nes_write((0x0205 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_8564:;
    /* $8564: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_8566:;
    /* $8566: 60 */ maybe_trigger_vblank(6);
}

}  // namespace smb::semcomp
