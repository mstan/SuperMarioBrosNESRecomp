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
    explicit Camera(const GameState& state) : state_(state) {}

    // Left edge of the visible screen in world coordinates.
    std::uint16_t left_world_x() const;
    // Right edge of the visible screen in world coordinates.
    std::uint16_t right_world_x() const;

    // Convenience: width of the camera in world pixels.
    // Always 256 in stock SMB; included for parity with future widescreen
    // semcomp work where camera width is variable.
    std::uint16_t width() const;

private:
    const GameState& state_;
};

}  // namespace smb::semcomp
