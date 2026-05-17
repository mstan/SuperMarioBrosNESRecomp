// semcomp/Camera.h — semantic facade over the scrolling-camera state.
//
// Camera bounds are the only place where the widescreen experiment
// (feature/widescreen-2026-04-11) made progress, so these labels are
// well-trusted. See HANDOFF.md and extras.c for the widescreen hooks.
#pragma once

#include <cstdint>

namespace smb::semcomp {

class GameState;

class Camera {
public:
    // Mutable now (Phase 4): set_world_x / lock both write to RAM.
    // Constructed in SemcompGame with a mutable GameState ref.
    explicit Camera(GameState& state) : state_(state) {}

    // ---- Reads -----------------------------------------------------------
    std::uint16_t left_world_x() const;     // ($071A << 8) | $071C
    std::uint16_t right_world_x() const;    // ($071B << 8) | $071D
    std::uint16_t width() const;            // right - left (always 256 stock)
    bool          is_locked() const;        // $0723 != 0

    // ---- Mutations -------------------------------------------------------
    // Teleport the camera. Writes the page byte and offset within page for
    // BOTH the left and right edges (keeping width=256). Level data won't
    // re-stream from ROM though — for small offsets within the current
    // loaded window the visual jump is clean; for large jumps you'll see
    // garbled or blank tiles until the player walks the level loader to
    // the new area.
    void set_world_x(std::uint16_t world_x);

    // Lock auto-scroll. Sets $0723 (the boss-room scroll-lock flag the
    // ScrollHandler reads at $AF9D). Reasserted every frame in
    // apply_freezes so the natural scroll code can't clear it.
    void lock();
    void unlock();

    // Called every frame by SemcompGame::apply_post_nmi.
    void apply_freezes();

private:
    GameState& state_;
    bool       locked_ = false;
};

}  // namespace smb::semcomp
