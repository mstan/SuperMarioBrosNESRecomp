// semcomp/Level.h — semantic facade over the current world/area state.
//
// Phase 0 is intentionally thin: WorldNumber/LevelNumber/AreaNumber addresses
// are not yet verified against this repo's traces, so the class compiles but
// exposes only documented entry points and a phase marker.
#pragma once

#include <cstdint>

namespace smb::semcomp {

class GameState;

class Level {
public:
    explicit Level(const GameState& state) : state_(state) {}

    // TODO(phase1): world(), level(), area() once $075F/$0760/$0750 (or the
    // verified equivalents) are confirmed against a recorded trace. Returning
    // unverified RAM here in Phase 0 would violate the "no invented mappings"
    // rule from the handoff.

    // True when phase-1 RAM-label work has not yet landed for the level
    // subsystem. Callers can use this as a feature gate while migration is
    // in flight.
    bool labels_pending() const { return true; }

private:
    const GameState& state_;
};

}  // namespace smb::semcomp
