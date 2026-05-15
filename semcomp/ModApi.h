// semcomp/ModApi.h — registration surface for future mod hooks.
//
// Phase 0 stub: registration is accepted and stored, but nothing fires.
// Phase 2 wires this into the runner's frame path.
#pragma once

#include <cstddef>
#include <cstdint>

namespace smb::semcomp {

class SemcompGame;

// Per-frame hook signature. The game pointer is non-owning; callers must
// not store it past the hook invocation.
using FrameHook = void (*)(SemcompGame* game, void* user);

class ModApi {
public:
    static constexpr std::size_t kMaxFrameHooks = 8;

    ModApi() = default;

    // Returns the slot index on success, or kInvalidSlot if full.
    static constexpr std::size_t kInvalidSlot = static_cast<std::size_t>(-1);
    std::size_t register_frame_hook(FrameHook hook, void* user);

    // Phase 0: not called by the runner. Phase 2 invokes once per frame.
    void dispatch_frame(SemcompGame* game);

    std::size_t hook_count() const { return count_; }

private:
    struct Slot {
        FrameHook hook = nullptr;
        void*     user = nullptr;
    };
    Slot slots_[kMaxFrameHooks] = {};
    std::size_t count_ = 0;
};

}  // namespace smb::semcomp
