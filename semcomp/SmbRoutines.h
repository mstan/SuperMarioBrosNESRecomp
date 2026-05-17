// semcomp/SmbRoutines.h — semantic re-implementations of replaced 6502 routines.
//
// Each function here is the C++ counterpart of a SMB subroutine that has been
// (or will be) wired in via game.toml [[replace_func]]. The semantic
// implementation must produce the same observable side effects (work-RAM
// writes, PPU VRAM-buffer queue entries, CPU register state at RTS) as the
// original — verify_mode's per-frame WRAM diff against Nestopia is the
// parity check.
//
// Semantic routines may call back into still-generated helpers via extern "C"
// (e.g. DigitsMathRoutine / PrintStatusBarNumbers) — only the entry-point
// function is replaced, not the whole transitive call tree.
#pragma once

#include <cstdint>

namespace smb::semcomp {

// ---------------------------------------------------------------------------
// Primitives — small, reusable building blocks. Each owns one 6502
// instruction sequence and settles its own NMI cycle cost. See the .cpp
// for per-primitive instruction-level breakdowns.
// ---------------------------------------------------------------------------

// Primitives return their cycle cost so composing routines can sum and
// call maybe_trigger_vblank() once at the end (matching the original
// 6502's "no-backward-branch routines fire NMI only at their tail"
// shape). Callers that use a single primitive standalone should pass
// the returned cycles to maybe_trigger_vblank() themselves.

// ---- Real SFX queue writes ----
// SoundEngine handlers consume bitmask queues in zero page. Game code
// triggers an effect by storing the bit pattern.
// Each SFX primitive does BOTH: OR the natural caller's queue bit into
// $00FE/$00FF, and direct-call the corresponding Play* routine via
// call_by_address. The double-fire is intentional — see SmbRoutines.cpp
// header note. From a trainer (TCP) context either path has timing
// quirks; combined they cover the race for most SFX.
//
// Verified status (2026-05-17, trainer context):
//   power_up_grab   — AUDIBLE
//   pipe_down_injury— AUDIBLE
//   extra_life      — untested but same Square2 path as power_up_grab
//   coin_pickup     — KNOWN-SILENT (see SmbRoutines.cpp inline comment;
//                     left in place as a no-op so re-tests are one
//                     change away).
int play_coin_pickup_sfx();    // $00FE |= $01 + JSR PlayCoinGrab  (silent)
int play_extra_life_jingle();  // $00FE |= $40 + JSR PlayExtraLife
int play_power_up_grab();      // $00FE |= $20 + JSR PlayPowerUpGrab
int play_pipe_down_injury();   // $00FF |= $10 + JSR PlayPipeDownInj

// ---- DigitModifier setup (NOT sound writes — these prime the BCD
// add buffer that DigitsMathRoutine reads on its next call) ----
int prep_add_one_to_coin_display();  // DigitModifier[5] = 1
int prep_add_200_to_score();         // DigitModifier[4] = 2 → +200 in BCD

// Generic DigitsMathRoutine driver: LDX CurrentPlayer; LDA table,X; JSR.
// `rom_offset_table` is the ROM address of the per-player Y-index table
// (e.g. ROM_CoinTallyOffsets / ROM_ScoreOffsets). The caller must have
// already populated the relevant DigitModifier[] slot(s) before calling.
int apply_digits_math(std::uint16_t rom_offset_table);

// INC NumberofLives + play_extra_life_jingle. No clamping; mirrors the
// 6502's plain INC. Suitable for any 1-Up grant (coin rollover, mushroom,
// hidden block).
int grant_extra_life();

// $BC0C-$BC21 of GiveOneCoin. INC CoinTally; if it wraps to 100, reset
// to 0 and grant a 1-Up. Optional `fired_1up` out-parameter is set true
// iff the rollover branch fired.
int increment_coin_tally_with_1up_check(bool* fired_1up = nullptr);

// $BC30-$BC45 tail. refresh_status_bar_cycles() returns cost without
// settling vblank (use when composing with other primitives);
// refresh_status_bar() is a void wrapper that settles once on its own,
// for stand-alone callers like PlayerSession::set_coins.
int  refresh_status_bar_cycles();
void refresh_status_bar();

// ---------------------------------------------------------------------------
// High-level routines — composed from primitives. Wired in via
// game.toml [[replace_func]] for the address-pinned ones.
// ---------------------------------------------------------------------------

// $BBFE GiveOneCoin — grant a coin: SFX, advance coin digits, increment
// $075E (1-Up at 100), points chime, +200 score, HUD refresh.
//
// Fall-through to CoinPoints ($BC22) and AddToScore ($BC27) is preserved
// by primitive ordering. AddToScore remains separately callable via the
// generated func_BC27_b0 entry — that's untouched.
void give_coin();

// ---- Trainer convenience wrappers ----
// These adjust counters, refresh the HUD, and fire one audible SFX per
// call. They do NOT preserve byte-for-byte game parity (use
// give_coin via replace_func for that). The SFX is triggered by
// directly invoking the game's PlayCoinGrab / PlayExtraLife routines
// (call_by_address) rather than queueing $00FE — that bypasses the
// $00FE-queue-vs-NMI-timing race that was eating the SFX in TCP context.

// Add N to CoinTally. Rolls over to 0 every 100, granting one extra life
// per rollover. One SFX per call: coin grab on normal add, extra-life
// jingle if any 1-Up rollover fired. No score change (that's a
// give_coin feature, not Add Coins).
void add_coins(std::uint8_t n);

// Subtract N from CoinTally (clamped at 0); refresh HUD. Silent — there
// is no "un-grab a coin" game verb.
void remove_coins(std::uint8_t n);

// Add N to NumberofLives (clamped at 99 — values higher render as garbled
// HUD tiles). One extra-life jingle, one HUD refresh.
void add_lives(std::uint8_t n);

// Subtract N from NumberofLives (clamped at 0). Silent; HUD refresh.
void remove_lives(std::uint8_t n);

// ---- Score primitives + trainer wrappers ----
// Score is 6 BCD digits stored at two locations (see SmbRamMap.h). These
// primitives read / write both atomically. Trainer wrappers refresh the
// HUD; they don't fire SFX (there's no "score change" sound in SMB).
std::uint32_t read_player_score();           // decodes BCD → integer
void          write_player_score(std::uint32_t value);  // encodes int → BCD, writes both copies
void          set_score(std::uint32_t value);           // = write + HUD refresh
void          add_score(std::int32_t delta);            // = read + clamp + write + HUD refresh

// ---- Timer primitives + trainer wrappers ----
// Game timer is 3 BCD digits at $07F8..$07FA. Range 0..999.
std::uint16_t read_game_timer();
void          write_game_timer(std::uint16_t seconds);
void          set_timer(std::uint16_t seconds);
void          add_timer(std::int16_t delta);

}  // namespace smb::semcomp
