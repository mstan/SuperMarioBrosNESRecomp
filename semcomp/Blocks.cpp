// semcomp/Blocks.cpp — replacement body for $BD9B BumpBlock.
#include "semcomp/Blocks.h"

#include "semcomp/GameState.h"
#include "semcomp/SmbRamMap.h"
#include "semcomp/cpu_flags.h"

extern "C" {
#include "nes_runtime.h"
}

namespace smb::semcomp {

// Sub-handlers we dispatch to. None of these are replace_func'd, so
// the recompiler still emits their bodies and call_by_address resolves.
namespace {
constexpr std::uint16_t kPC_BlockBumpedChk  = 0xBDF6;
constexpr std::uint16_t kPC_MushFlowerBlock = 0xBDD2;
constexpr std::uint16_t kPC_VineBlock       = 0xBDDF;
constexpr std::uint16_t kPC_Block_BB38      = 0xBB38;
constexpr std::uint16_t kPC_Block_BDD5      = 0xBDD5;
constexpr std::uint16_t kPC_Block_BDD8      = 0xBDD8;
}  // namespace

void Blocks::bump_block() {
    // Snapshot X (per-slot index) before the JSR clobbers it. The
    // original code preserves X across the indexed stores via the
    // 6502's separate-X-register model; we hold it explicitly.
    const std::uint8_t slot = g_cpu.X;

    // $BD9B-$BDA0: queue Square1 block-bump SFX bit.
    state_.write8(0x00FF, 0x02);

    // $BDA2-$BDAD: per-slot bookkeeping. Zero $60+X, $043C+X, $9F;
    // store sentinel $FE at $A8+X (used by block-bounce animation).
    state_.write8(static_cast<std::uint16_t>(0x0060 + slot), 0);
    state_.write8(static_cast<std::uint16_t>(0x043C + slot), 0);
    state_.write8(0x009F, 0);
    state_.write8(static_cast<std::uint16_t>(0x00A8 + slot), 0xFE);

    // $BDAF-$BDB1: A = metatile column staged at $05; call
    // BlockBumpedChk which searches a table at $BDE8 for a matching
    // block code. On match: C=1, Y = match index (0..D).
    g_cpu.A = state_.read8(ram::Block_BumpedMetaCol);
    g_cpu.X = slot;
    call_by_address(kPC_BlockBumpedChk);

    // $BDB4: BCC NoMatch — exit cleanly if no block matched.
    if (!g_cpu.C) return;

    // $BDB6-$BDBB: A = Y. If A >= 9, A -= 5. This collapses the
    // table's 14-entry match space into the 9-entry dispatch table at
    // $8E04 — the natural-game dispatch logic.
    std::uint8_t idx = g_cpu.Y;
    if (idx >= 9) idx = static_cast<std::uint8_t>(idx - 5);

    // Restore X to the slot index in case BlockBumpedChk clobbered it
    // — the sub-handlers will index off X for entity slot.
    g_cpu.X = slot;
    g_cpu.A = idx;

    // $BDBD: inline dispatch via $8E04 table.
    switch (idx) {
        case 0: call_by_address(kPC_MushFlowerBlock); break;
        case 1: call_by_address(kPC_Block_BB38);      break;
        case 2: call_by_address(kPC_Block_BB38);      break;
        case 3: call_by_address(kPC_Block_BDD8);      break;
        case 4: call_by_address(kPC_MushFlowerBlock); break;
        case 5: call_by_address(kPC_VineBlock);       break;
        case 6: call_by_address(kPC_Block_BDD5);      break;
        case 7: call_by_address(kPC_Block_BB38);      break;
        case 8: call_by_address(kPC_Block_BDD8);      break;
        default: break;  // out-of-range — no-op (matches natural fallthrough)
    }
}

// Phase 19 untangle — sub-handlers extracted to standalone methods.
// MushFlowerBlock and VineBlock used to live as inner labels of $BD9B;
// $BDD5 StarBlock and $BDD8 ExtraLifeMushBlock were already standalone.

void Blocks::mush_flower_block() {
    (void)state_;
label_BDD2:; /* MushFlowerBlock */
    /* $BDD2: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_BDD4:;
    /* $BDD4: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x02A9); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BDD7:;
    /* $BDD7: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x03A9); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BDDA:;
    /* $BDDA: 85 */ maybe_trigger_vblank(3); nes_write(0x39, g_cpu.A);
label_BDDC:;
    /* $BDDC: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xBC49); return;
}

void Blocks::vine_block() {
    (void)state_;
label_BDDF:; /* VineBlock */
    /* $BDDF: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x05; FLAG_NZ(g_cpu.X);
label_BDE1:;
    /* $BDE1: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x03EE); FLAG_NZ(g_cpu.Y);
label_BDE4:;
    /* $BDE4: 20 */ maybe_trigger_vblank(6); call_by_address(0xB91E);
label_BDE7:; /* ExitBlockChk */
    /* $BDE7: 60 */ maybe_trigger_vblank(6);
}

void Blocks::star_block() {
    (void)state_;
label_BDD5:; /* StarBlock */
    /* $BDD5: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_BDD7:;
    /* $BDD7: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x03A9); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BDDA:;
    /* $BDDA: 85 */ maybe_trigger_vblank(3); nes_write(0x39, g_cpu.A);
label_BDDC:;
    /* $BDDC: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xBC49); return;
}

void Blocks::extra_life_mush_block() {
    (void)state_;
label_BDD8:; /* ExtraLifeMushBlock */
    /* $BDD8: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x03; FLAG_NZ(g_cpu.A);
label_BDDA:;
    /* $BDDA: 85 */ maybe_trigger_vblank(3); nes_write(0x39, g_cpu.A);
label_BDDC:;
    /* $BDDC: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xBC49); return;
}

}  // namespace smb::semcomp
