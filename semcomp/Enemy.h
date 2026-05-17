// semcomp/Enemy.h — single-enemy facade over one slot of the 5-slot array.
//
// SMB's enemies live in a parallel array of per-byte attributes
// (see SmbRamMap.h's Enemy_*_Base addresses). The natural game code
// indexes those arrays via the Y register inside enemy-update loops.
// This C++ facade carries a slot index and reads `base + slot` via
// GameState — same model, just typed.
//
// Enemy IDs come from the 6502 dispatch table at $C26C
// (CheckpointEnemyID). Below we enumerate the names we're confident
// about; the rest are exposed via raw IDs in the trainer's "spawn
// arbitrary" path. Confirm-in-game before adding to the safe-spawn
// dropdown.
#pragma once

#include <cstdint>

namespace smb::semcomp {

class GameState;

// Verified enemy type IDs (smbdis canonical). Members not listed below
// are valid slot byte values but their game behavior hasn't been
// confirmed against this repo — use raw u8 if you want one of those.
enum class EnemyType : std::uint8_t {
    GreenKoopaTroopa  = 0x00,
    RedKoopaTroopa    = 0x01,
    BuzzyBeetle       = 0x02,
    RedKoopaNoFall    = 0x03,
    HammerBro         = 0x04,
    GreenKoopaPatient = 0x05,
    BigGoomba         = 0x06,  // a.k.a. "fast goomba" in some refs
    Bloober           = 0x07,
    Bowser            = 0x2D,  // smbdis: Bowser_Flag. Confirm in-game.
    // ... more added as we verify them.
};

// Per-slot enemy state byte ($001E+slot). Common values surfaced from
// the agent's research; treat unlisted values as opaque movement state.
enum class EnemyMoveState : std::uint8_t {
    Walking         = 0x00,
    KoopaDefensive  = 0x01,
    DemotedShell    = 0x03,  // Koopa demoted to walking-shell post-stomp
    StompedAtRest   = 0x20,  // EnemyStomped sets this
};

class Enemy {
public:
    Enemy(GameState& state, std::uint8_t slot) : state_(state), slot_(slot) {}

    std::uint8_t slot() const { return slot_; }

    // ---- Reads ---------------------------------------------------------
    bool          active() const;        // $000F+slot != 0
    std::uint8_t  id_raw() const;        // $0016+slot
    EnemyType     type() const { return static_cast<EnemyType>(id_raw()); }
    std::uint8_t  state_raw() const;     // $001E+slot
    std::uint8_t  x() const;             // $0087+slot
    std::uint8_t  y() const;             // $00CF+slot
    std::uint8_t  x_page() const;        // $006E+slot
    std::uint8_t  y_page() const;        // $0076+slot
    std::uint16_t world_x() const { return (std::uint16_t)((x_page() << 8) | x()); }
    std::int8_t   x_velocity() const;    // $0058+slot (signed)
    std::int8_t   y_velocity() const;    // $00B6+slot (signed)

    // ---- Mutations -----------------------------------------------------
    // kill: instant remove via $E18E KillEnemyAboveBlock. No score, no
    // floatey number, no anim. Good for "wipe screen" trainer verb.
    void kill();

    // stomp: routes through $D969 EnemyStomped. Grants the stomp-chain
    // score (100/200/400/...) and triggers the floatey-number + bounce
    // anim. Caller is responsible for chaining order (each stomp
    // increments the chain counter).
    void stomp();

    // freeze: zero $0058 (x-vel) and $00B6 (y-vel). BEST-EFFORT ONLY —
    // MoveNormalEnemy at $CA77 push/pops the velocity around its
    // per-frame movement (PHA $58+X at $CAB6, PLA STA $58+X at $CAC5),
    // and the AddHS step at $CABB applies an accel-table delta. So
    // walking Goombas / Koopas re-accelerate to walking speed on the
    // next frame. Stationary enemies (stunned shells, Bowser between
    // movements) hold the zero. A real freeze needs either a sticky
    // post-NMI re-zero loop, or state-byte manipulation to gate the
    // move-dispatch into a no-op branch — TODO.
    void freeze();

private:
    GameState& state_;
    std::uint8_t slot_;
};

}  // namespace smb::semcomp
