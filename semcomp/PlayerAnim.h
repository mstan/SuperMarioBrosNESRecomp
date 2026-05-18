// semcomp/PlayerAnim.h — facade over Mario's per-frame animation states.
//
// Phase 10 ownership via [[replace_func]] — four per-frame routines that
// PlayerCtrlRoutine ($B0E9) dispatches to via the $000E selector:
//
//   $B233 PlayerChangeSize    -> PlayerAnim::change_size      ($0E = $09)
//   $B245 PlayerInjuryBlink   -> PlayerAnim::injury_blink     ($0E = $0A)
//   $B269 PlayerDeath         -> PlayerAnim::player_death     ($0E = $0B)
//   $B27D PlayerFireFlower    -> PlayerAnim::fire_flower      ($0E = $0C)
//
// Each routine is small (a $0747 timer threshold check + dispatch to a
// natural-generated helper). The Mario state machine cycles through
// these to drive the grow/shrink, invuln blink, death drop, and fire-
// flower palette flash animations.
//
// Helpers called via call_by_address (still natural-generated):
//   $B0E9 PlayerCtrlRoutine — base ctrl dispatcher
//   $B255 InitChangeSize    — toggles PlayerSize + ChangeSizeFlag
//   $B273 DonePlayerTask    — clears $0747 and resets $0E = 8
//   $B288 CyclePlayerPalette — palette-cycle helper
//   $B29A ResetPalStar      — palette-reset to base
//
// Natural test surface: any time Mario grows / shrinks / blinks /
// dies / catches a fire flower, our class drives it. Already
// exercised by give_power_up + take_damage Mario verbs which trigger
// the animation state changes via $0747.
#pragma once

#include <cstdint>

namespace smb::semcomp {

class GameState;

class PlayerAnim {
public:
    explicit PlayerAnim(GameState& state) : state_(state) {}

    // $B233 PlayerChangeSize — grow/shrink animation tick.
    //   $0747 == $F8 -> InitChangeSize (toggle PlayerSize)
    //   $0747 == $C4 -> DonePlayerTask (end animation)
    //   else         -> RTS
    void change_size();

    // $B245 PlayerInjuryBlink — invuln blink during the post-damage
    // invulnerability window.
    //   $0747 == $F0 -> fall-through to InitChangeSize (toggle visibility)
    //   $0747 >  $F0 -> exit (animation not yet at trigger point)
    //   $0747 == $C8 -> DonePlayerTask (end animation)
    //   $0747 <  $C8 -> JMP PlayerCtrlRoutine (run normal ctrl)
    void injury_blink();

    // $B269 PlayerDeath — death-drop animation tick.
    //   $0747 >= $F0 -> exit
    //   else         -> JMP PlayerCtrlRoutine (apply gravity / movement)
    void player_death();

    // $B27D PlayerFireFlower — fire-flower palette flash on pickup.
    //   $0747 == $C0 -> ResetPalFireFlower (DonePlayerTask + ResetPalStar)
    //   else         -> CyclePlayerPalette (palette flicker tick)
    void fire_flower();

private:
    GameState& state_;
};

}  // namespace smb::semcomp
