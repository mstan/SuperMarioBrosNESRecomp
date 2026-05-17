// semcomp/RoutineRegistry.h — Phase 3 routine-replacement bookkeeping.
//
// Tracks which 6502 PCs have been replaced by semantic C++ implementations
// (via game.toml [[replace_func]]) and counts invocations of each. Lives on
// SemcompGame; queried via TCP for diagnostics ("did my replacement actually
// fire on the attract demo?").
//
// Parity verification is NOT done here — it lives in verify_mode.c's
// divergence ring, which compares full work-RAM against the Nestopia oracle
// every frame. The registry only answers "is this routine wired up."
#pragma once

#include <cstdint>
#include <cstddef>

namespace smb::semcomp {

class RoutineRegistry {
public:
    static constexpr std::size_t kMaxRoutines = 16;

    struct Entry {
        std::uint16_t pc;
        const char*   name;
        std::uint64_t invocations;
    };

    RoutineRegistry();

    // Register a replaced routine. Idempotent on pc. Returns the slot index,
    // or -1 if the table is full.
    int register_routine(std::uint16_t pc, const char* name);

    // Bump the invocation counter for pc. Silently ignored if pc is not
    // registered — calling code shouldn't break if registration was missed.
    void note_invocation(std::uint16_t pc);

    std::size_t count() const { return count_; }
    const Entry& entry(std::size_t i) const { return entries_[i]; }
    std::uint64_t invocations(std::uint16_t pc) const;

private:
    Entry       entries_[kMaxRoutines];
    std::size_t count_;
};

}  // namespace smb::semcomp
