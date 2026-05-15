// semcomp/Level.h — semantic facade over the current stage identity.
//
// Phase 1: world/level accessors verified. Camera bounds remain on the
// separate Camera class; Level is for stage identity, not viewport.
#pragma once

#include <cstdint>

namespace smb::semcomp {

class GameState;

class Level {
public:
    explicit Level(const GameState& state) : state_(state) {}

    // 0-indexed. World 1-1 reads as world()=0, level()=0. Add 1 for HUD
    // display per the original SMB render routine.
    std::uint8_t world() const;
    std::uint8_t level() const;

    // Convenience: e.g. "1-1" → 0x11 (world 0 in high nibble, level 0
    // in low nibble, each plus 1). Useful for switch-statement
    // dispatch on stage identity.
    std::uint16_t world_level_packed() const {
        return static_cast<std::uint16_t>(((world() + 1) << 4) | (level() + 1));
    }

private:
    const GameState& state_;
};

}  // namespace smb::semcomp
