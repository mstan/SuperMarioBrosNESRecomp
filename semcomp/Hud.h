// semcomp/Hud.h — facade over SMB's status-bar refresh + score-grant pipeline.
//
// Owns two routines architecturally via [[replace_func]]:
//   $BC27 AddToScore             -> Hud::add_to_score()
//   $8F06 PrintStatusBarNumbers  -> Hud::print_status_bar_numbers()
//
// Natural callers (every score-grant event in SMB, every HUD refresh)
// flow through this class. Test surface: coins, stomps, brick-bumps,
// fireball kills, end-of-level time-bonus tally — all credit score
// and refresh the HUD via these routines.
//
// $8F5F DigitsMathRoutine is NOT replaced here: it has the same
// inner-label issue as BumpBlock ($8F75 StoreNewD is emitted as a
// standalone helper that calls back into $8F68 AddModLoop which lives
// inside DigitsMathRoutine's body). We call_by_address into the
// natural-generated DigitsMathRoutine from add_to_score(); when we
// eventually reimplement BCD math in C++ end-to-end, the call site
// stays the same.
#pragma once

#include <cstdint>

namespace smb::semcomp {

class GameState;

class Hud {
public:
    explicit Hud(GameState& state) : state_(state) {}

    // print_status_bar_numbers: replacement body for $8F06.
    // Caller passes A = "nybbles" control byte (low + high nybble each
    // select one HUD field to refresh: score, coins, world, level,
    // time, etc.). We invoke OutputNumbers ($8F11) twice — first with
    // the low nybble, then with the high nybble. OutputNumbers itself
    // is a separately-emitted standalone routine that we don't own
    // (yet); it does the digit-tile staging into VRAM_Buffer1.
    void print_status_bar_numbers();

    // add_to_score: replacement body for $BC27.
    // Caller has pre-staged DigitModifier[i] entries at $0134..$0139
    // with the per-digit increments. We then:
    //   1. Read CurrentPlayer ($0753) into X.
    //   2. Y = ROM_ScoreOffsets[X] ($BBFA+X) — per-player digit start.
    //   3. JSR DigitsMathRoutine ($8F5F) — applies the BCD adds.
    //   4. Reload Y = CurrentPlayer.
    //   5. A = ROM_StatusBarNybbles[Y] ($BBFC+Y) — which fields to
    //      refresh for this player.
    //   6. JSR PrintStatusBarNumbers (which dispatches back into THIS
    //      class via our replacement).
    //   7. Suppress a leading-zero in the staged VRAM_Buffer1 entry
    //      (replace with tile $24 = blank) if needed.
    //   8. Restore X from ZP_Scratch_08.
    void add_to_score();

private:
    GameState& state_;
};

}  // namespace smb::semcomp
