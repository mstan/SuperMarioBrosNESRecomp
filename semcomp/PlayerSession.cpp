// semcomp/PlayerSession.cpp — per-playthrough state reads.
#include "semcomp/PlayerSession.h"
#include "semcomp/GameState.h"
#include "semcomp/SmbRamMap.h"
#include "semcomp/SmbRoutines.h"

extern "C" {
#include "nes_runtime.h"  // maybe_trigger_vblank
}

namespace smb::semcomp {

std::uint8_t PlayerSession::lives() const {
    return state_.read8(ram::NumberofLives);
}

std::uint8_t PlayerSession::coins() const {
    return state_.read8(ram::CoinTally);
}

namespace {
inline std::uint8_t clamp99(std::uint8_t v) {
    return v > 99 ? std::uint8_t{99} : v;
}
}  // namespace

void PlayerSession::set_lives(std::uint8_t v) {
    // Clamp to 0..99: the in-level lives HUD font is only digits 0-9,
    // and the level-intro card displays two digits. Values >= 100 get
    // re-interpreted as tile indices by some render paths, producing
    // garbled glyphs (the user observed "F" for 25 — that's the byte
    // landing in the letter region of the CHR tileset).
    //
    // NOTE: this only updates the internal counter. The HUD itself
    // lives in PPU VRAM and refreshes only on game events. See class
    // doc comment.
    state_.write8(ram::NumberofLives, clamp99(v));
}

void PlayerSession::write_coins_raw(std::uint8_t v) {
    state_.write8(ram::CoinTally, clamp99(v));
}

void PlayerSession::set_coins(std::uint8_t v) {
    // Phase 3: write the counter, queue the coin pickup SFX ($00FE bit
    // 0 — the audible "ding"), and push a single status-bar refresh
    // into VRAM_Buffer1 so the HUD digits reflect the new value at the
    // next NMI.
    //
    // Unlike give_coin() (which would only handle +1 increments and
    // bring score / 1-Up side effects), this is idempotent for arbitrary
    // set-to-N values: counter is written exactly, no score change, no
    // life grant, one SFX, one HUD refresh.
    write_coins_raw(v);
    int c = 0;
    c += smb::semcomp::play_coin_pickup_sfx();
    c += smb::semcomp::refresh_status_bar_cycles();
    maybe_trigger_vblank(c);
}

// ---- Semantic freezes -------------------------------------------------------

void PlayerSession::freeze_lives(std::uint8_t v) {
    frozen_lives_active_ = true;
    frozen_lives_        = clamp99(v);
    set_lives(v);
}
void PlayerSession::thaw_lives() { frozen_lives_active_ = false; }

void PlayerSession::freeze_coins(std::uint8_t v) {
    frozen_coins_active_ = true;
    frozen_coins_        = clamp99(v);
    set_coins(v);
}
void PlayerSession::thaw_coins() { frozen_coins_active_ = false; }

void PlayerSession::apply_freezes() {
    if (frozen_lives_active_) set_lives(frozen_lives_);
    // Coins: re-assert the byte without churning the HUD queue each frame.
    // The initial freeze_coins() call already did one set_coins() (raw +
    // refresh), so the on-screen value is correct from that point on.
    if (frozen_coins_active_) write_coins_raw(frozen_coins_);
}

}  // namespace smb::semcomp
