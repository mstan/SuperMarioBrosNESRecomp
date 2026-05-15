// semcomp/Selftest.cpp — compile-checked exercise of every facade accessor.
//
// Phase 0 purpose: prove that the semcomp layer links cleanly against the
// nesrecomp runtime. The runner does not call selftest(); it exists so that
// every accessor has at least one caller in the executable, which prevents
// silent regressions where a class method is declared but never defined.
#include "semcomp/semcomp.h"

#include <cstdint>

namespace smb::semcomp {

bool selftest() {
    SemcompGame game;

    // Touch every read accessor. Values are intentionally unused; the only
    // thing that matters is that the symbols resolve and the types line up.
    volatile std::uint8_t  mx  = game.mario().x();
    volatile std::uint8_t  mp  = game.mario().page();
    volatile std::uint16_t mwx = game.mario().world_x();
    volatile std::uint8_t  msp = game.mario().spr_data_offset();
    volatile std::uint16_t cl  = game.camera().left_world_x();
    volatile std::uint16_t cr  = game.camera().right_world_x();
    volatile std::uint16_t cw  = game.camera().width();
    volatile bool          lp  = game.level().labels_pending();
    volatile std::uint8_t  ca  = game.state().cpu_a();

    // Phase 0: also exercise the ModApi surface so a registration regression
    // breaks the build instead of waiting for Phase 2 integration.
    auto noop = +[](SemcompGame*, void*) {};
    volatile std::size_t slot = game.mod_api().register_frame_hook(noop, nullptr);

    (void)mx; (void)mp; (void)mwx; (void)msp;
    (void)cl; (void)cr; (void)cw;
    (void)lp; (void)ca; (void)slot;
    return true;
}

}  // namespace smb::semcomp
