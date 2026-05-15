// semcomp/PlayerSession.cpp — per-playthrough state reads.
#include "semcomp/PlayerSession.h"
#include "semcomp/GameState.h"
#include "semcomp/SmbRamMap.h"

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

void PlayerSession::set_coins(std::uint8_t v) {
    // Same caveat as set_lives — counter only; HUD doesn't auto-refresh.
    state_.write8(ram::CoinTally, clamp99(v));
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
    if (frozen_coins_active_) set_coins(frozen_coins_);
}

}  // namespace smb::semcomp
