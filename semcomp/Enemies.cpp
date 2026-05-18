// semcomp/Enemies.cpp — container over the 5 enemy slots.
#include "semcomp/Enemies.h"

#include "semcomp/GameState.h"
#include "semcomp/SmbRamMap.h"

extern "C" {
#include "nes_runtime.h"
}

namespace smb::semcomp {

namespace {
// Routines we delegate to via call_by_address. Standalone-emitted, not
// owned by us.
constexpr std::uint16_t kPC_C35A_InitBoundBox = 0xC35A;  // tail-called by InitNormalEnemy
constexpr std::uint16_t kPC_BF63_FallE_Pre    = 0xBF63;  // vertical-gravity pre
constexpr std::uint16_t kPC_BF02_MoveHoriz    = 0xBF02;  // horizontal-pos-from-XSpd
constexpr std::uint16_t kPC_CAC8_ReviveStunned = 0xCAC8;  // separate-emitted ReviveStunned
constexpr std::uint16_t kPC_CAE5_MoveDefeated = 0xCAE5;  // separate-emitted MoveDefeatedEnemy
constexpr std::uint16_t kROM_AccelTable        = 0xC9D0;  // 6-entry XSpd accel table
constexpr std::uint16_t kRam_HardWorldFlag     = 0x076A;  // 0 = normal, !=0 = hard worlds 5+
}  // namespace

int Enemies::active_count() const {
    int n = 0;
    for (int i = 0; i < kSlotCount; ++i) {
        if (Enemy(const_cast<GameState&>(state_), (std::uint8_t)i).active())
            ++n;
    }
    return n;
}

void Enemies::kill_all() {
    for (int i = 0; i < kSlotCount; ++i) {
        Enemy e(state_, (std::uint8_t)i);
        if (e.active()) e.kill();
    }
}

void Enemies::stomp_all() {
    for (int i = 0; i < kSlotCount; ++i) {
        Enemy e(state_, (std::uint8_t)i);
        if (e.active()) e.stomp();
    }
}

void Enemies::freeze_all() {
    for (int i = 0; i < kSlotCount; ++i) {
        Enemy e(state_, (std::uint8_t)i);
        if (e.active()) e.freeze();
    }
}

// ---- Replace_func bodies (Phase 8) ----------------------------------------

void Enemies::init_normal_enemy() {
    // Mirrors $C30E InitNormalEnemy. Caller has set X = enemy slot;
    // Y will be derived from the world-difficulty flag.
    const std::uint8_t slot = g_cpu.X;

    // $C30E: LDY #$01
    g_cpu.Y = 0x01;

    // $C310-$C315: if HardWorldFlag ($076A) is zero, DEY → Y=0
    // (i.e. picks the easier initial speed from the C30C table).
    if (state_.read8(kRam_HardWorldFlag) == 0) {
        g_cpu.Y = 0;
    }

    // $C316 GetESpd: A = ROM[$C30C + Y]   (per-difficulty initial XSpd)
    // $C319 SetESpd: $58+X = A           (store XSpd in the slot)
    {
        const std::uint8_t xspd = nes_read(
            static_cast<std::uint16_t>(0xC30C + g_cpu.Y));
        g_cpu.A = xspd;
        state_.write8(static_cast<std::uint16_t>(ram::Enemy_XSpeed_Base + slot),
                      xspd);
    }

    // $C31B: JMP $C35A (tail-call to bounding-box init, separately
    // emitted as func_C35A — not replaced by us).
    g_cpu.X = slot;
    call_by_address(kPC_C35A_InitBoundBox);
}

void Enemies::move_normal_enemy() {
    // Mirrors $CA77 MoveNormalEnemy. Caller has set X = enemy slot.
    // Reads enemy state byte at $1E+X; gates dispatch into FallE /
    // MEHor / SlowM / SteadM / MoveDefeated / ReviveStunned based on
    // state bits. The accel table at $C9D0 produces the per-frame
    // displacement applied by $BF02.
    const std::uint8_t slot = g_cpu.X;
    std::uint8_t y_reg = 0;   // tracks the natural Y register

    // $CA77-$CA8E: state-dispatch chain.
    std::uint8_t state = state_.read8(
        static_cast<std::uint16_t>(ram::Enemy_State_Base + slot));

    bool to_fall_e   = false;
    bool to_steadm   = false;

    // $CA7B-$CA7D: state & $40 → FallE
    if (state & 0x40) {
        to_fall_e = true;
    } else if (state & 0x80) {
        // $CA81-$CA82: ASL+BCS → bit 7 of state set → SteadM
        to_steadm = true;
    } else if (state & 0x20) {
        // $CA86-$CA88: stomped bit → MoveDefeatedEnemy (delegated)
        g_cpu.X = slot;
        call_by_address(kPC_CAE5_MoveDefeated);
        return;
    } else {
        // $CA8C-$CA96: low 3 bits classification.
        const std::uint8_t low = state & 0x07;
        if (low == 0) {
            to_steadm = true;
        } else if (low == 5) {
            to_fall_e = true;
        } else if (low >= 3) {
            // ReviveStunned (delegated)
            g_cpu.X = slot;
            call_by_address(kPC_CAC8_ReviveStunned);
            return;
        } else {
            // low in {1, 2}: fall through to FallE per natural
            // sequence ($CA98 is the next byte after the BCS).
            to_fall_e = true;
        }
    }

    bool to_mehor = false;
    bool to_slowm = false;

    if (to_fall_e) {
        // $CA98 FallE: JSR $BF63 (vertical/gravity pre-step).
        g_cpu.X = slot;
        call_by_address(kPC_BF63_FallE_Pre);

        // $CA9B: Y = 0
        y_reg = 0;
        // $CA9D-$CAA1: A = state again; if A == 2 → MEHor
        state = state_.read8(
            static_cast<std::uint16_t>(ram::Enemy_State_Base + slot));
        if (state == 0x02) {
            to_mehor = true;
        } else if ((state & 0x40) == 0) {
            // $CAA3-$CAA5: state & $40 == 0 → SteadM with Y=0
            to_steadm = true;
        } else {
            // $CAA7-$CAAB: if Enemy_ID == $2E → SteadM
            const std::uint8_t eid = state_.read8(
                static_cast<std::uint16_t>(ram::Enemy_ID_Base + slot));
            if (eid == 0x2E) {
                to_steadm = true;
            } else {
                // $CAAD-$CAB2: BNE → SlowM
                to_slowm = true;
            }
        }
    }

    if (to_mehor) {
        // $CAAF MEHor: JMP $BF02 (apply horizontal movement, tail).
        g_cpu.X = slot;
        call_by_address(kPC_BF02_MoveHoriz);
        return;
    }

    if (to_slowm) {
        // $CAB2 SlowM: Y = 1, fall through to SteadM.
        y_reg = 1;
    }

    // $CAB4 SteadM: read XSpd, push, conditionally adjust Y for
    // negative XSpd, compute new XSpd = original + ROM[$C9D0+Y],
    // store, apply movement via $BF02, restore original XSpd.
    {
        const std::uint8_t orig_xspd = state_.read8(
            static_cast<std::uint16_t>(ram::Enemy_XSpeed_Base + slot));

        // $CAB7: BPL → AddHS (if XSpd positive, skip the Y+=2)
        // i.e. if XSpd is negative (bit 7 set), Y += 2 to pick the
        // negative-direction accel-table entry.
        if (orig_xspd >= 0x80) {
            y_reg = static_cast<std::uint8_t>(y_reg + 2);
        }

        // $CABB AddHS: C=0; ADC ROM[$C9D0+Y]  (then $CABF: STA $58+X).
        const std::uint8_t accel = nes_read(
            static_cast<std::uint16_t>(kROM_AccelTable + y_reg));
        const std::uint8_t adjusted = static_cast<std::uint8_t>(
            orig_xspd + accel);
        state_.write8(static_cast<std::uint16_t>(ram::Enemy_XSpeed_Base + slot),
                      adjusted);

        // $CAC1: JSR $BF02 (apply position delta using current XSpd).
        g_cpu.X = slot;
        call_by_address(kPC_BF02_MoveHoriz);

        // $CAC4-$CAC5: restore the original XSpd into $58+X. The
        // adjusted value was per-frame transient; persisted speed
        // stays at the original (so enemies don't accumulate accel).
        state_.write8(static_cast<std::uint16_t>(ram::Enemy_XSpeed_Base + slot),
                      orig_xspd);
        // $CAC7: RTS — return.
    }
}

}  // namespace smb::semcomp
