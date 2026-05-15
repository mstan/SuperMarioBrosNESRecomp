// semcomp/Trainer.h — runtime freeze/set table for verifying the facade.
//
// The Trainer maintains a small table of (addr, value) pairs. When
// enabled (via --trainer at runtime), Trainer::apply() runs every frame
// AFTER the game's frame update and re-writes each frozen byte. The
// effect is that the address holds the user-specified value regardless
// of whatever the game logic is doing.
//
// V1 scope: addr-keyed table only. The Python tool (tools/trainer.py)
// translates semantic names like "mario.x" to raw addresses using the
// constants in SmbRamMap.h.
//
// Validation pattern:
//   1. trainer_freeze 0x86 100  -> Mario X locked at 100
//   2. read Mario::x()          -> should return 100  (validates read)
//   3. trainer_thaw 0x86; Mario::set_x(50); read_ram 0x86
//                              -> should return 50   (validates write)
#pragma once

#include <cstddef>
#include <cstdint>

namespace smb::semcomp {

class GameState;

class Trainer {
public:
    static constexpr std::size_t kMaxFreezeEntries = 32;

    explicit Trainer(GameState& state) : state_(state) {}

    // One-shot write (no freeze). Returns true; reserved for failure
    // cases that V1 doesn't have.
    bool set(std::uint16_t addr, std::uint8_t val);

    // Add or update a frozen entry. Returns false only when the table
    // is full and the address isn't already present.
    bool freeze(std::uint16_t addr, std::uint8_t val);

    // Remove a frozen entry. Returns true if it was present.
    bool thaw(std::uint16_t addr);

    bool         is_frozen(std::uint16_t addr) const;
    std::uint8_t frozen_value(std::uint16_t addr) const;

    // Enumeration support for the trainer_list TCP command. Indices
    // [0, count()) span active entries only; thawed entries are
    // compacted out.
    std::size_t   count() const { return count_; }
    std::uint16_t entry_addr(std::size_t i) const;
    std::uint8_t  entry_value(std::size_t i) const;

    // Per-frame hook. Runs all frozen writes when enabled; no-op when
    // disabled. Safe to call every frame regardless of state.
    void apply();

    bool enabled() const { return enabled_; }
    void set_enabled(bool e) { enabled_ = e; }

private:
    struct Entry {
        std::uint16_t addr  = 0;
        std::uint8_t  value = 0;
    };
    Entry        slots_[kMaxFreezeEntries] = {};
    std::size_t  count_   = 0;
    bool         enabled_ = false;
    GameState&   state_;

    // Returns index in [0, count_) if found, else kMaxFreezeEntries.
    std::size_t find_index(std::uint16_t addr) const;
};

}  // namespace smb::semcomp
