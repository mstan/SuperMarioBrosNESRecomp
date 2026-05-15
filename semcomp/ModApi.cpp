// semcomp/ModApi.cpp — Phase 0 stub. Stores registrations; fires nothing.
#include "semcomp/ModApi.h"

namespace smb::semcomp {

std::size_t ModApi::register_frame_hook(FrameHook hook, void* user) {
    if (hook == nullptr || count_ >= kMaxFrameHooks) {
        return kInvalidSlot;
    }
    slots_[count_] = {hook, user};
    return count_++;
}

void ModApi::dispatch_frame(SemcompGame* game) {
    for (std::size_t i = 0; i < count_; ++i) {
        slots_[i].hook(game, slots_[i].user);
    }
}

}  // namespace smb::semcomp
