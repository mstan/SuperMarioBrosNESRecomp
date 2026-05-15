// semcomp/Mario.h — semantic facade over the player avatar.
//
// Reads-only in Phase 0. Future phases add write accessors and behavior
// (jump, walk, fireball) that route through a runtime switch with the
// generated implementation as fallback.
#pragma once

#include <cstdint>

namespace smb::semcomp {

class GameState;

class Mario {
public:
    explicit Mario(const GameState& state) : state_(state) {}

    // Position within the current 256-pixel page.
    std::uint8_t x() const;
    // TODO(phase1): y() once Player_Y_Position is verified.

    // Page index (each page is 256 pixels wide).
    std::uint8_t page() const;

    // Full 16-bit world X = (page << 8) | x.
    std::uint16_t world_x() const;

    // OAM byte offset for Mario's sprite block. Useful for renderer hooks.
    std::uint8_t spr_data_offset() const;

private:
    const GameState& state_;
};

}  // namespace smb::semcomp
