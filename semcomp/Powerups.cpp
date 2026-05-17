// semcomp/Powerups.cpp — replacement body for $BC49 SetupPowerUp.
#include "semcomp/Powerups.h"

#include "semcomp/GameState.h"
#include "semcomp/SmbRamMap.h"

extern "C" {
#include "nes_runtime.h"
}

namespace smb::semcomp {

void Powerups::setup() {
    const std::uint8_t slot = g_cpu.X;

    // $BC49-$BC4B: $1B = $2E
    state_.write8(0x001B, 0x2E);

    // $BC4D-$BC4F: $73 = $76+X (Y page from slot's spawn position).
    {
        const std::uint8_t v = state_.read8(static_cast<std::uint16_t>(0x0076 + slot));
        state_.write8(0x0073, v);
    }

    // $BC51-$BC53: $8C = $8F+X
    {
        const std::uint8_t v = state_.read8(static_cast<std::uint16_t>(0x008F + slot));
        state_.write8(0x008C, v);
    }

    // $BC55-$BC57: $BB = $01
    state_.write8(0x00BB, 0x01);

    // $BC59-$BC5E: $D4 = $D7+X - 8  (the 6502 SEC/SBC #$08 here)
    {
        const std::uint8_t v = state_.read8(static_cast<std::uint16_t>(0x00D7 + slot));
        state_.write8(0x00D4, static_cast<std::uint8_t>(v - 8));
    }

    // $BC60-$BC68 PwrUpJmp: mark the power-up object active.
    state_.write8(0x0023, 0x01);
    state_.write8(0x0014, 0x01);
    state_.write8(0x049F, 0x03);

    // $BC6B-$BC79: PowerUpType translation. If base type is mushroom
    // (0) or fire-flower (1), upgrade it based on Mario's current
    // PlayerStatus — Small gets mushroom, Big/Fire gets fire flower.
    // (Star = 2 and 1-Up = 3 skip this translation.)
    std::uint8_t powerup_type = state_.read8(ram::PowerUpType);
    if (powerup_type < 0x02) {
        std::uint8_t player_status = state_.read8(ram::PlayerStatus);
        if (player_status >= 0x02) player_status >>= 1;  // Fire -> Flower equivalent
        state_.write8(ram::PowerUpType, player_status);
    }

    // $BC7B-$BC82: $03CA = $20 (sprite attribute), $00FE = $02
    // (Square2 SFX queue: power-up grab "ding-ding" appeared bit).
    state_.write8(0x03CA, 0x20);
    state_.write8(0x00FE, 0x02);
}

}  // namespace smb::semcomp
