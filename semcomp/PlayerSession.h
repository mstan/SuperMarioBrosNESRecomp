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
    // Phase 2: ctor takes mutable GameState so set_* can write.
    explicit PlayerSession(GameState& state) : state_(state) {}

    // Raw life count. SMB displays this value plus 1 on the HUD (so a
    // value of 2 in RAM renders as "x3" on screen because Mario himself
    // is also alive). Callers wanting the HUD number should add 1.
    std::uint8_t lives() const;

    // Coins picked up in the current run, 0..99. Rolls over to 0 and
    // grants a 1-up at 100.
    std::uint8_t coins() const;

    // ---- Writes (Phase 2 → Phase 3) --------------------------------------
    // Values are clamped to 0..99 because the HUD font only renders two
    // decimal digits; values >= 100 produce garbled glyphs (the byte is
    // used as a tile index in some render paths).
    //
    // set_coins (Phase 3): writes $075E AND emits a single status-bar
    // refresh entry into VRAM_Buffer1, so the on-screen coin digits
    // reflect the new value within one NMI. Uses
    // smb::semcomp::refresh_status_bar() — no SFX, no score, no $0748
    // tally side effects (unlike a full GiveOneCoin call). The freeze
    // re-apply path uses write_coins_raw() to avoid churning the VRAM
    // queue every frame for an unchanging value.
    //
    // set_lives: still raw-only — there's no GiveOneLife semantic routine
    // yet, so the HUD does not auto-refresh for life writes. See
    // memory/project_smb_hud_in_ppu.md for the broader HUD story.
    void set_lives(std::uint8_t v);
    void set_coins(std::uint8_t v);

    // ---- Semantic freezes (Phase 2.5) ------------------------------------
    // Same shape as Mario's freezes: record value, set immediately,
    // re-assert each frame via apply_freezes().
    void freeze_lives(std::uint8_t v);
    void thaw_lives();
    bool is_lives_frozen() const { return frozen_lives_active_; }
    std::uint8_t frozen_lives_value() const { return frozen_lives_; }

    void freeze_coins(std::uint8_t v);
    void thaw_coins();
    bool is_coins_frozen() const { return frozen_coins_active_; }
    std::uint8_t frozen_coins_value() const { return frozen_coins_; }

    void apply_freezes();

    // TODO(phase1.5): score (BCD triplet at $07FC..$07FE — addresses
    // present in extras.c's smb_state but not yet independently
    // verified by trace), game timer, and the 2P-mode/player-select
    // byte.

private:
    // Per-frame freeze maintenance path: bytes only, no HUD refresh, to
    // avoid pushing a fresh status-bar update into VRAM_Buffer1 every
    // frame for an unchanging frozen value.
    void write_coins_raw(std::uint8_t v);

    GameState&    state_;
    bool          frozen_lives_active_ = false;
    std::uint8_t  frozen_lives_        = 0;
    bool          frozen_coins_active_ = false;
    std::uint8_t  frozen_coins_        = 0;
};

}  // namespace smb::semcomp
