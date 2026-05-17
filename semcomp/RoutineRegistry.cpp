#include "semcomp/RoutineRegistry.h"

namespace smb::semcomp {

RoutineRegistry::RoutineRegistry() : entries_{}, count_(0) {}

int RoutineRegistry::register_routine(std::uint16_t pc, const char* name) {
    for (std::size_t i = 0; i < count_; ++i) {
        if (entries_[i].pc == pc) return static_cast<int>(i);
    }
    if (count_ >= kMaxRoutines) return -1;
    entries_[count_] = Entry{pc, name, 0};
    return static_cast<int>(count_++);
}

void RoutineRegistry::note_invocation(std::uint16_t pc) {
    for (std::size_t i = 0; i < count_; ++i) {
        if (entries_[i].pc == pc) { entries_[i].invocations++; return; }
    }
}

std::uint64_t RoutineRegistry::invocations(std::uint16_t pc) const {
    for (std::size_t i = 0; i < count_; ++i) {
        if (entries_[i].pc == pc) return entries_[i].invocations;
    }
    return 0;
}

}  // namespace smb::semcomp
