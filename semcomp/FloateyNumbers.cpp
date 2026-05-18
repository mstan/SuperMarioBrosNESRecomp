// semcomp/FloateyNumbers.cpp — replacement body for $DA11 SetupFloateyNumber.
#include "semcomp/FloateyNumbers.h"

#include "semcomp/GameState.h"

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

}  // namespace smb::semcomp
