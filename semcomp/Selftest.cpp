// semcomp/Selftest.cpp — compile-checked exercise of every facade accessor.
//
// The runner does not call selftest(); it exists so that every accessor
// has at least one caller in the executable, which catches "declared
// but never defined" regressions at link time instead of when a Phase 2+
// caller appears.
#include "semcomp/semcomp.h"

#include <cstdint>

namespace smb::semcomp {

bool selftest() {
    SemcompGame game;

    // Mario reads.
    volatile std::uint8_t  mx  = game.mario().x();
    volatile std::uint8_t  my  = game.mario().y();
    volatile std::uint8_t  mp  = game.mario().page();
    volatile std::uint16_t mwx = game.mario().world_x();
    volatile std::int8_t   mvx = game.mario().x_velocity();
    volatile std::int8_t   mvy = game.mario().y_velocity();
    volatile std::uint8_t  msa = game.mario().x_speed_absolute();
    volatile PowerStatus   mpw = game.mario().power();
    volatile std::uint8_t  msb = game.mario().size_byte();
    volatile std::uint8_t  mps = game.mario().physics_state_raw();
    volatile bool          mog = game.mario().on_ground();
    volatile Direction     mf  = game.mario().facing();
    volatile Direction     mm  = game.mario().moving();
    volatile std::uint8_t  mso = game.mario().spr_data_offset();

    // Level reads.
    volatile std::uint8_t  lw  = game.level().world();
    volatile std::uint8_t  ll  = game.level().level();
    volatile std::uint16_t lwl = game.level().world_level_packed();

    // Camera reads.
    volatile std::uint16_t cl  = game.camera().left_world_x();
    volatile std::uint16_t cr  = game.camera().right_world_x();
    volatile std::uint16_t cw  = game.camera().width();

    // PlayerSession reads.
    volatile std::uint8_t  sl  = game.session().lives();
    volatile std::uint8_t  sc  = game.session().coins();

    // PlayerSession writes (Phase 2).
    game.session().set_lives(0);
    game.session().set_coins(0);

    // CPU state.
    volatile std::uint8_t  ca  = game.state().cpu_a();

    // ModApi surface.
    auto noop = +[](SemcompGame*, void*) {};
    volatile std::size_t   slot = game.mod_api().register_frame_hook(noop, nullptr);

    // Mario writes (Phase 2). These touch g_ram, so they're cheap and
    // safe in a selftest harness only because selftest() is never
    // invoked from the runner. Do not call selftest() at runtime.
    game.mario().set_x(0);
    game.mario().set_y(0);
    game.mario().set_page(0);
    game.mario().set_power(PowerStatus::Small);
    game.mario().set_physics_state_raw(0);
    game.mario().set_facing(Direction::Right);

    // Trainer surface.
    volatile bool tf1 = game.trainer().freeze(0x0086, 0);
    volatile bool tf2 = game.trainer().is_frozen(0x0086);
    volatile std::uint8_t tv = game.trainer().frozen_value(0x0086);
    volatile std::size_t tc = game.trainer().count();
    volatile std::uint16_t ea = game.trainer().entry_addr(0);
    volatile std::uint8_t  ev = game.trainer().entry_value(0);
    volatile bool tt = game.trainer().thaw(0x0086);
    game.trainer().set(0x0086, 0);
    game.trainer().set_enabled(false);
    game.trainer().apply();

    (void)mx; (void)my; (void)mp; (void)mwx;
    (void)mvx; (void)mvy; (void)msa;
    (void)mpw; (void)msb; (void)mps; (void)mog;
    (void)mf; (void)mm; (void)mso;
    (void)lw; (void)ll; (void)lwl;
    (void)cl; (void)cr; (void)cw;
    (void)sl; (void)sc;
    (void)ca; (void)slot;
    (void)tf1; (void)tf2; (void)tv; (void)tc; (void)ea; (void)ev; (void)tt;
    return true;
}

}  // namespace smb::semcomp
