// semcomp/Enemies.h — facade over the 5-slot enemy array.
//
// Not a concept the original 6502 had as a discrete object — SMB just
// iterates the parallel arrays directly. This class is one of the
// semcomp layer's "we're allowed to introduce abstractions the ROM
// didn't have" affordances: trainer code wants to think in terms of
// "the enemies on screen", not "the per-byte arrays at $000F+, $0016+,
// $001E+ ...".
//
// The 5-slot count is fixed (SMB allocates exactly 5; the 6th
// notionally exists for the player's projectile / floatey-number
// slots but isn't an enemy). Wraps Enemy instances on demand —
// nothing is stored in the container; the live state always reads
// through GameState.
#pragma once

#include <cstdint>

#include "semcomp/Enemy.h"

namespace smb::semcomp {

class GameState;

class Enemies {
public:
    static constexpr int kSlotCount = 5;

    explicit Enemies(GameState& state) : state_(state) {}

    // Slot access. Returns a value Enemy (cheap — holds a reference +
    // an index).
    Enemy slot(std::uint8_t i) { return Enemy(state_, i); }

    // Count of slots with non-zero $000F+slot flag.
    int active_count() const;

    // ---- Bulk verbs ----------------------------------------------------

    // kill_all: every active slot → kill() (instant disappear, no
    // score, no anim). The "wipe the screen" cheat.
    void kill_all();

    // stomp_all: every active slot → stomp() (score grant + bounce
    // animation per slot). Scores accumulate.
    void stomp_all();

    // freeze_all: every active slot → freeze() (zero velocities).
    // Resistant to per-frame velocity recompute (Piranha Plant,
    // Lakitu schedule, etc.) — accepted limitation for v1.
    void freeze_all();

private:
    GameState& state_;
};

}  // namespace smb::semcomp
