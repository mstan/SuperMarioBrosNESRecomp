// semcomp/TrainerUI.h — in-game SDL text overlay for the trainer.
//
// The overlay is keyboard-driven and renders into the 256x240
// framebuffer via game_post_render(). When visible, it grabs keyboard
// input so navigation doesn't bleed into the game's controller bytes.
//
// Controls (while visible):
//   Up / Down       select slot
//   Left / Right    -1 / +1 to selected slot's displayed value
//   Enter           freeze selected slot at displayed value
//   Backspace       thaw selected slot
//   F8 / Esc        close
//
// While invisible, only F8 is monitored (toggles to visible).
#pragma once

#include <cstdint>
#include <cstddef>

namespace smb::semcomp {

class SemcompGame;

class TrainerUI {
public:
    explicit TrainerUI(SemcompGame& game) : game_(game) {}

    bool visible() const { return visible_; }
    void set_visible(bool v) { visible_ = v; }

    // Whether the UI is currently consuming keyboard input. extras.c
    // suppresses g_controller1_buttons while this is true.
    bool grabbing_input() const { return visible_; }

    // Per-frame keyboard polling. Reads SDL_GetKeyboardState() and updates
    // selection / values. Toggles visibility on F8 edge. Safe to call
    // every frame regardless of state.
    void tick();

    // Blit the overlay into a 256x240 ARGB framebuffer. No-op when not
    // visible. Caller passes the actual framebuffer dimensions; for
    // standard SMB this is always (256, 240).
    void render(std::uint32_t* fb, int width, int height) const;

    // Slot count is fixed; exposed for the host loop to know about
    // selection bounds.
    static constexpr int kSlotCount = 6;

private:
    enum Slot {
        kSlotX = 0,
        kSlotY,
        kSlotPage,
        kSlotPower,
        kSlotPhysics,
        kSlotFacing,
    };

    SemcompGame& game_;
    bool visible_ = false;
    int  selected_ = 0;
    // Per-slot edit-value buffer. Initialized from the current RAM byte
    // when the overlay opens; left/right adjust this without writing
    // until Enter is pressed.
    std::uint8_t edit_value_[kSlotCount] = {0};
    // Edge-detection state for keys (so holding a key doesn't repeat
    // every frame at 60Hz).
    bool key_prev_[16] = {false};

    // Helpers (defined in TrainerUI.cpp).
    void on_open();
    std::uint16_t slot_addr(int slot) const;
    std::uint8_t  slot_current_raw(int slot) const;
    bool          slot_is_frozen(int slot) const;
    const char*   slot_label(int slot) const;
    void          format_slot_value(int slot, std::uint8_t val,
                                     char* out, std::size_t out_sz) const;
};

}  // namespace smb::semcomp
