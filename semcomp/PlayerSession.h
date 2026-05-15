// semcomp/PlayerSession.h — semantic facade over per-playthrough state.
//
// PlayerSession tracks values that persist across Mario's deaths within a
// single game: lives, coins, score, timer. The Mario class tracks the
// in-world avatar; PlayerSession tracks the run that contains him.
//
// Phase 1: only lives and coins are verified. Score, timer, and the
// continue/2P-state byte are TODO(phase1.5) — they exist in RAM but
// their addresses are not yet trace-verified for this repo.
#pragma once

#include <cstdint>

namespace smb::semcomp {

class GameState;

class PlayerSession {
public:
    explicit PlayerSession(const GameState& state) : state_(state) {}

    // Raw life count. SMB displays this value plus 1 on the HUD (so a
    // value of 2 in RAM renders as "x3" on screen because Mario himself
    // is also alive). Callers wanting the HUD number should add 1.
    std::uint8_t lives() const;

    // Coins picked up in the current run, 0..99. Rolls over to 0 and
    // grants a 1-up at 100.
    std::uint8_t coins() const;

    // TODO(phase1.5): score (BCD triplet at $07FC..$07FE — addresses
    // present in extras.c's smb_state but not yet independently
    // verified by trace), game timer, and the 2P-mode/player-select
    // byte.

private:
    const GameState& state_;
};

}  // namespace smb::semcomp
