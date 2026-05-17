// semcomp/SmbRoutines.cpp — semantic re-implementations of SMB subroutines.
//
// Two layers:
//
//   1. PRIMITIVES — small, single-purpose translations of recurring 6502
//      instruction sequences (digit-math setup, HUD refresh) OR direct
//      invocations of game-side SFX routines via call_by_address. Each
//      returns the cycle cost of the 6502 work it represents; composing
//      routines sum and call maybe_trigger_vblank() once at the end.
//
//   2. HIGH-LEVEL ROUTINES — wired in via game.toml's [[replace_func]]
//      (give_coin) and trainer-convenience wrappers (add_coins,
//      remove_coins, add_lives, remove_lives) that adjust counters,
//      refresh the HUD, and fire SFX in one call.
//
// On SFX (tandem approach): the natural in-game caller — JCoinC for coin,
// HandlePowerUpCollision for power-ups, InjurePlayer for damage — writes
// a bit into the $00FE/$00FF SFX queue and lets SoundEngine consume it
// during NMI. From a TCP/trainer context that's been timing-fragile in
// isolation (handoff: $00FE write got consumed but no audible output).
// The fix the trainer takes here is to do BOTH:
//   1. OR the queue bit (matches the natural caller exactly).
//   2. Also call the corresponding Play* routine via call_by_address —
//      this writes the Square2/Square1 APU registers and SFX-length
//      counter directly so the sound is set up even if SoundEngine's
//      queue-consume step happens before or after our hook misfires.
// The game keeps the two paths separate by design (queue write in the
// caller; SoundEngine drives the queue from NMI). The trainer is under
// no obligation to mimic that split — we call BOTH explicitly and let
// whichever fires win. Idempotent: a second invocation just rewrites
// the same APU regs.

#include "semcomp/SmbRoutines.h"

#include "semcomp/SmbRamMap.h"

extern "C" {
#include "nes_runtime.h"

// Generated helpers / SFX entry points we call back into.
void func_8F5F_b0(void);  // DigitsMathRoutine — BCD digit add via DigitModifier
void func_8F06_b0(void);  // PrintStatusBarNumbers — push HUD digits into VRAM_Buffer1

// Game-side SFX setup routines. The recompiler exposes any PC via the
// dispatch table; call_by_address(pc) invokes the function generated for
// that 6502 address. Trainer SFX primitives below call these in tandem
// with the natural-caller's $00FE/$00FF queue write (see header note).
constexpr std::uint16_t kPC_PlayCoinGrab    = 0xF518;
constexpr std::uint16_t kPC_PlayExtraLife   = 0xF5E2;
constexpr std::uint16_t kPC_PlayPowerUpGrab = 0xF552;
constexpr std::uint16_t kPC_PlayPipeDownInj = 0xF4B6;
}

namespace smb::semcomp {

namespace {
inline void set_nz(std::uint8_t v) {
    g_cpu.Z = (v == 0);
    g_cpu.N = (v >> 7) & 1;
}
}  // namespace

// ---------------------------------------------------------------------------
// SFX primitives (direct routine invocation)
// ---------------------------------------------------------------------------

// Tandem helper: OR `bit` into the Square2 ($00FE) or Square1 ($00FF)
// SFX queue (matches the exact natural-caller pattern: LDA $FE / ORA
// #bit / STA $FE), then JSR the corresponding Play* routine via
// call_by_address. Idempotent on a hot frame.
static inline void queue_and_call(std::uint16_t queue_addr,
                                  std::uint8_t  bit,
                                  std::uint16_t play_pc) {
    const std::uint8_t cur = nes_read(queue_addr);
    nes_write(queue_addr, static_cast<std::uint8_t>(cur | bit));
    call_by_address(play_pc);
}

int play_coin_pickup_sfx() {
    // KNOWN-SILENT in trainer context. Verified 2026-05-17.
    //
    // Approaches tried, all silent from TCP/trainer:
    //   (a) write $00FE = $01            — bit consumed by SoundEngine,
    //                                       no audio (handoff).
    //   (b) call_by_address(0xF518)      — PlayCoinGrab direct, sets up
    //                                       APU regs, no audio.
    //   (c) BOTH (a)+(b) tandem (below) — also silent, this session.
    //
    // The same tandem pattern works for power-up grab ($20 / $F552) and
    // pipe-down injury ($FF=$10 / $F4B6). Whatever's different about
    // the coin-pickup SFX path specifically is unidentified — possibly
    // PlayCoinGrab's APU-reg writes are stomped between our hook and
    // Square2SfxHandler's next-frame run. Accepted as a silent no-op;
    // the trainer's coin grant still updates HUD + counter correctly.
    //
    // Re-test path if revisiting: read $07BD (Square2_SfxLenCounter)
    // immediately before/after add_coins and watch for an $8D it
    // should briefly land at while the sound plays.
    queue_and_call(ram::Square2_SoundQueue, ram::SFX_CoinPickup,
                   kPC_PlayCoinGrab);
    return 6 + 3 + 5;
}

int play_extra_life_jingle() {
    // Bit 6 of $00FE → 1-Up jingle. Natural source is the rollover path
    // inside GiveOneCoin's IsAMario / HandleCoinMetatile branches.
    queue_and_call(ram::Square2_SoundQueue, ram::SFX_ExtraLifeJingle,
                   kPC_PlayExtraLife);
    return 6 + 3 + 5;
}

int play_power_up_grab() {
    // Bit 5 of $00FE → power-up grab. Natural source is
    // HandlePowerUpCollision at $D808 (LDA #$20 / STA $FE).
    queue_and_call(ram::Square2_SoundQueue, /*$20=*/0x20,
                   kPC_PlayPowerUpGrab);
    return 6 + 3 + 5;
}

int play_pipe_down_injury() {
    // Bit 4 of $00FF → pipe-down "injury" warble. Natural source is
    // InjurePlayer at $D93F (STA $FF, A==$10). Trainer calls this after
    // InjurePlayer for the same belt-and-suspenders reason as above.
    queue_and_call(ram::Square1_SoundQueue, /*$10=*/0x10,
                   kPC_PlayPipeDownInj);
    return 6 + 3 + 5;
}

// ---------------------------------------------------------------------------
// DigitModifier setup primitives
// ---------------------------------------------------------------------------
// DigitsMathRoutine ($8F5F) reads $0134-$0139 (the DigitModifier array)
// for per-digit-position add deltas. The original GiveOneCoin uses two
// slots; we expose the setup as named primitives so future routines can
// reuse them.

int prep_add_one_to_coin_display() {
    g_cpu.A = 0x01;
    set_nz(g_cpu.A);
    nes_write(ram::DigitModifier_5, 0x01);
    return 2 + 4;  // LDA imm + STA abs
}

int prep_add_200_to_score() {
    g_cpu.A = 0x02;
    set_nz(g_cpu.A);
    nes_write(ram::DigitModifier_4, 0x02);
    return 2 + 4;
}

// ---------------------------------------------------------------------------
// BCD digit-math primitive (calls the generated helper)
// ---------------------------------------------------------------------------

int apply_digits_math(std::uint16_t rom_offset_table) {
    const std::uint8_t player = nes_read(ram::CurrentPlayer);
    g_cpu.X = player;
    set_nz(player);
    const std::uint8_t offset =
        nes_read(static_cast<std::uint16_t>(rom_offset_table + player));
    g_cpu.Y = offset;
    set_nz(offset);
    func_8F5F_b0();
    return 4 + 4 + 6;  // LDX abs + LDA abs,X + JSR
}

// ---------------------------------------------------------------------------
// Life primitives
// ---------------------------------------------------------------------------

int grant_extra_life() {
    // INC NumberofLives + play the 1-Up jingle. Mirrors the 6502's
    // plain INC (no clamping); coin rollover and 1-Up mushroom paths
    // both target this.
    const std::uint8_t lives = static_cast<std::uint8_t>(
        (nes_read(ram::NumberofLives) + 1) & 0xFF);
    nes_write(ram::NumberofLives, lives);
    set_nz(lives);
    int c = 6;                          // INC abs
    c += play_extra_life_jingle();
    return c;
}

int increment_coin_tally_with_1up_check(bool* fired_1up) {
    const std::uint8_t tally = static_cast<std::uint8_t>(
        (nes_read(ram::CoinTally) + 1) & 0xFF);
    nes_write(ram::CoinTally, tally);
    set_nz(tally);
    g_cpu.A = tally;
    {
        const int r = tally - 0x64;
        g_cpu.C = (tally >= 0x64) ? 1 : 0;
        set_nz(static_cast<std::uint8_t>(r & 0xFF));
    }
    int c = 6 + 4 + 2;

    if (tally == 0x64) {
        g_cpu.A = 0x00;
        set_nz(g_cpu.A);
        nes_write(ram::CoinTally, 0x00);
        c += 2 + 2 + 4;
        c += grant_extra_life();
        if (fired_1up) *fired_1up = true;
    } else {
        c += 3;
        if (fired_1up) *fired_1up = false;
    }
    return c;
}

// ---------------------------------------------------------------------------
// Status bar refresh
// ---------------------------------------------------------------------------

int refresh_status_bar_cycles() {
    g_cpu.Y = nes_read(ram::CurrentPlayer);
    set_nz(g_cpu.Y);
    const std::uint8_t nybbles =
        nes_read(static_cast<std::uint16_t>(ram::ROM_StatusBarNybbles + g_cpu.Y));
    g_cpu.A = nybbles;
    set_nz(nybbles);
    int c = 4 + 4;

    func_8F06_b0();
    c += 6;

    g_cpu.Y = nes_read(ram::VRAM_Buffer1_Offset);
    set_nz(g_cpu.Y);
    const std::uint16_t first_digit_addr =
        static_cast<std::uint16_t>(ram::VRAM_Buffer1_BackQueue + g_cpu.Y);
    const std::uint8_t first_digit = nes_read(first_digit_addr);
    g_cpu.A = first_digit;
    set_nz(first_digit);
    c += 4 + 4;

    if (first_digit == 0x00) {
        g_cpu.A = 0x24;
        set_nz(g_cpu.A);
        nes_write(first_digit_addr, 0x24);
        c += 2 + 2 + 5;
    } else {
        c += 3;
    }
    return c;
}

void refresh_status_bar() {
    maybe_trigger_vblank(refresh_status_bar_cycles());
}

// ---------------------------------------------------------------------------
// High-level routines
// ---------------------------------------------------------------------------

void give_coin() {
    // $BBFE GiveOneCoin — byte-for-byte parity with the ROM. Does NOT
    // queue the coin pickup SFX (the caller, JCoinC at $BB79, does that).
    int c = 0;
    c += prep_add_one_to_coin_display();
    c += apply_digits_math(ram::ROM_CoinTallyOffsets);
    c += increment_coin_tally_with_1up_check();
    c += prep_add_200_to_score();
    c += apply_digits_math(ram::ROM_ScoreOffsets);
    c += refresh_status_bar_cycles();

    const std::uint8_t saved_x = nes_read(ram::ZP_Scratch_08);
    g_cpu.X = saved_x;
    set_nz(saved_x);
    c += 3 + 6;

    maybe_trigger_vblank(c);
}

// ---------------------------------------------------------------------------
// Trainer-convenience wrappers
// ---------------------------------------------------------------------------
// These DO NOT preserve byte-for-byte game parity (use give_coin via
// replace_func for that). They give the user a single button that:
//   • adjusts the counter (clamped sensibly)
//   • refreshes the HUD via VRAM_Buffer1
//   • plays one audible SFX so the action has feedback
//
// "add_*" rolls 100-coin overflows into 1-Ups (one jingle per 100, same
// as natural coin grabs) and emits one coin-grab SFX per call. "remove_*"
// is silent — there's no game verb for it.

void add_coins(std::uint8_t n) {
    if (n == 0) return;
    const std::uint8_t cur = nes_read(ram::CoinTally);
    const int total = static_cast<int>(cur) + static_cast<int>(n);
    const std::uint8_t new_tally = static_cast<std::uint8_t>(total % 100);
    const int rollovers = total / 100;

    nes_write(ram::CoinTally, new_tally);

    // Grant 1-Ups for each rollover. We sum cycles + fire one jingle
    // (multiple jingles would just overwrite each other in the Square2
    // length counter — game behavior).
    int c = 0;
    if (rollovers > 0) {
        const std::uint8_t lives = static_cast<std::uint8_t>(
            (nes_read(ram::NumberofLives) + rollovers) & 0xFF);
        nes_write(ram::NumberofLives, lives);
        c += play_extra_life_jingle();
    } else {
        c += play_coin_pickup_sfx();
    }
    c += refresh_status_bar_cycles();
    maybe_trigger_vblank(c);
}

void remove_coins(std::uint8_t n) {
    const std::uint8_t cur = nes_read(ram::CoinTally);
    const std::uint8_t next = (n >= cur) ? std::uint8_t{0}
                                          : static_cast<std::uint8_t>(cur - n);
    nes_write(ram::CoinTally, next);
    maybe_trigger_vblank(refresh_status_bar_cycles());
}

void add_lives(std::uint8_t n) {
    if (n == 0) return;
    const std::uint8_t cur = nes_read(ram::NumberofLives);
    const int total = static_cast<int>(cur) + static_cast<int>(n);
    // Clamp at 99 — the in-game lives display only renders two decimal
    // digits, and values above the digit-tile range render as garbled
    // glyphs (the byte is reused as a CHR tile index in some paths).
    const std::uint8_t new_lives = static_cast<std::uint8_t>(
        total > 99 ? 99 : total);
    nes_write(ram::NumberofLives, new_lives);

    int c = 0;
    c += play_extra_life_jingle();
    c += refresh_status_bar_cycles();
    maybe_trigger_vblank(c);
}

void remove_lives(std::uint8_t n) {
    const std::uint8_t cur = nes_read(ram::NumberofLives);
    const std::uint8_t next = (n >= cur) ? std::uint8_t{0}
                                          : static_cast<std::uint8_t>(cur - n);
    nes_write(ram::NumberofLives, next);
    maybe_trigger_vblank(refresh_status_bar_cycles());
}

// ---------------------------------------------------------------------------
// Score
// ---------------------------------------------------------------------------
// Score is encoded as 6 individual BCD digits (one per byte, 0..9). Two
// parallel copies exist: $07D7 display and $07DD internal. We keep them
// in sync because the in-game UpdateTopScore copy only fires when the
// current run beats the top — for trainer use we want immediate HUD
// reflection regardless.

std::uint32_t read_player_score() {
    // Read the internal (gameplay) score, BCD digits 0..9 per byte.
    std::uint32_t v = 0;
    for (int i = 0; i < ram::kScoreDigits; ++i) {
        const std::uint8_t d = nes_read(
            static_cast<std::uint16_t>(ram::PlayerOneScore_Internal + i));
        v = v * 10 + (d <= 9 ? d : 0);
    }
    return v;
}

void write_player_score(std::uint32_t value) {
    // Clamp to 6 BCD digits (max 999999).
    if (value > 999999u) value = 999999u;
    // Decompose high-to-low.
    std::uint8_t digits[ram::kScoreDigits];
    std::uint32_t v = value;
    for (int i = ram::kScoreDigits - 1; i >= 0; --i) {
        digits[i] = static_cast<std::uint8_t>(v % 10);
        v /= 10;
    }
    for (int i = 0; i < ram::kScoreDigits; ++i) {
        nes_write(static_cast<std::uint16_t>(ram::PlayerOneScore_Display  + i), digits[i]);
        nes_write(static_cast<std::uint16_t>(ram::PlayerOneScore_Internal + i), digits[i]);
    }
}

void set_score(std::uint32_t value) {
    write_player_score(value);
    maybe_trigger_vblank(refresh_status_bar_cycles());
}

void add_score(std::int32_t delta) {
    const std::int64_t cur  = static_cast<std::int64_t>(read_player_score());
    std::int64_t        next = cur + delta;
    if (next < 0)         next = 0;
    if (next > 999999)    next = 999999;
    write_player_score(static_cast<std::uint32_t>(next));
    maybe_trigger_vblank(refresh_status_bar_cycles());
}

// ---------------------------------------------------------------------------
// Game timer
// ---------------------------------------------------------------------------
// 3 BCD digits, hundreds/tens/units. Naturally counts down during
// gameplay; trainer wrappers let you freeze, extend, or zero it.

std::uint16_t read_game_timer() {
    const std::uint8_t h = nes_read(ram::GameTimer_Hundreds);
    const std::uint8_t t = nes_read(ram::GameTimer_Tens);
    const std::uint8_t u = nes_read(ram::GameTimer_Units);
    return static_cast<std::uint16_t>(
        (h <= 9 ? h : 0) * 100 +
        (t <= 9 ? t : 0) * 10  +
        (u <= 9 ? u : 0));
}

void write_game_timer(std::uint16_t seconds) {
    if (seconds > 999) seconds = 999;
    nes_write(ram::GameTimer_Hundreds, static_cast<std::uint8_t>((seconds / 100) % 10));
    nes_write(ram::GameTimer_Tens,     static_cast<std::uint8_t>((seconds / 10)  % 10));
    nes_write(ram::GameTimer_Units,    static_cast<std::uint8_t>( seconds        % 10));
}

void set_timer(std::uint16_t seconds) {
    write_game_timer(seconds);
    maybe_trigger_vblank(refresh_status_bar_cycles());
}

void add_timer(std::int16_t delta) {
    const std::int32_t cur  = static_cast<std::int32_t>(read_game_timer());
    std::int32_t        next = cur + delta;
    if (next < 0)   next = 0;
    if (next > 999) next = 999;
    write_game_timer(static_cast<std::uint16_t>(next));
    maybe_trigger_vblank(refresh_status_bar_cycles());
}

}  // namespace smb::semcomp
