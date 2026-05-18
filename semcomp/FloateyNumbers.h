// semcomp/FloateyNumbers.h — facade over the floating-points-sprite system.
//
// Owns $DA11 SetupFloateyNumber via [[replace_func]]. The per-frame
// animation tick at $84C3 FloateyNumbersRoutine is NOT replaced — it
// has the same inner-label issue as BumpBlock (a separately-emitted
// helper at $8534 jumps back into the routine's interior). The
// natural-generated body continues to run the upward-float animation;
// our replacement just owns the spawn step.
//
// Natural callers: every points-grant event in SMB (EnemyStomped at
// $D969, HandlePowerUpCollision at $D800, KickedShellPtsData paths,
// 1-Up / coin scoring, etc.) calls SetupFloateyNumber to pop a
// "+N pts" sprite above the relevant object slot. With this routine
// owned, every floatey spawn flows through C++.
#pragma once

#include <cstdint>

namespace smb::semcomp {

class GameState;

class FloateyNumbers {
public:
    explicit FloateyNumbers(GameState& state) : state_(state) {}

    // setup: replacement body for $DA11. Caller passes:
    //   A = points-table-index (0=100, 1=200, ..., 9=8000)
    //   X = floatey object slot (often the same slot index as the
    //       spawning entity so the floatey anchors to its Y position)
    // Writes:
    //   $0110+X = points index (read later by the per-frame animator
    //             to look up the tile sequence and final points
    //             value)
    //   $012C+X = $30 (initial animation counter; ticks down each frame)
    //   $011E+X = floatey Y position (copied from $00CF+X, the
    //             spawning slot's Y)
    //   $0117+X = $03AE (a global ROM-pending-score sentinel; the
    //             natural game reuses this slot as the floatey's
    //             lifetime timer)
    void setup();

private:
    GameState& state_;
};

}  // namespace smb::semcomp
