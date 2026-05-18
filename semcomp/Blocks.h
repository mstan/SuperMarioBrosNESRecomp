// semcomp/Blocks.h — facade over the block-bump routine ($BD9B).
//
// "Blocks" here means the metatile entries Mario can interact with from
// below: bricks, ? blocks, vine blocks, etc. The natural game's
// $BD9B BumpBlock is invoked from the player-block collision path when
// Mario's head touches a bumpable metatile. We own it architecturally
// via [[replace_func]] in game.toml so the recompiler dispatches into
// this class; the natural in-game caller continues to drive it, and
// our test surface is "jump into a brick, did it work".
//
// Sub-handlers (MushFlowerBlock $BDD2, VineBlock $BDDF, the various
// $BB38/$BDD5/$BDD8 entries) remain in the generated C — we
// call_by_address into them for the block-code dispatch. Only the
// entry-point control flow is owned by C++ in this phase.
#pragma once

#include <cstdint>

namespace smb::semcomp {

class GameState;

class Blocks {
public:
    explicit Blocks(GameState& state) : state_(state) {}

    // bump_block: replacement body for $BD9B. Caller (the natural
    // player-collision path) has X = entity slot index and A = block
    // code candidate set up. Reproduces the original 6502 flow:
    //   1. Queue Square1 block-bump SFX ($00FF = $02).
    //   2. Zero the per-slot bookkeeping ($60+X, $043C+X, $9F, $A8+X
    //      sentinel = $FE).
    //   3. Read metatile col from $05, call BlockBumpedChk ($BDF6).
    //   4. If no match (C clear), RTS.
    //   5. Otherwise dispatch to the matching block-type handler via
    //      the $8E04 inline-dispatch table (9 entries).
    void bump_block();

    // Phase 19 untangle — own all multi-entry-body entries + the two small
    // standalones so the dispatch chain stays coherent.
    //   $BDD2 MushFlowerBlock     — inner-label of $BD9B body
    //   $BDDF VineBlock           — inner-label of $BD9B body
    //   $BDD5 StarBlock           — small standalone
    //   $BDD8 ExtraLifeMushBlock  — small standalone
    void mush_flower_block();
    void vine_block();
    void star_block();
    void extra_life_mush_block();

private:
    GameState& state_;
};

}  // namespace smb::semcomp
