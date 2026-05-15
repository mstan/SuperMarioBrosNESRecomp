// semcomp/GameState.h — typed read-only view over the recomp runtime state.
//
// GameState is the only class in semcomp that touches g_ram / g_cpu directly.
// Every other facade (Mario, Level, Camera) delegates here. Concentrating the
// raw-memory access in one place keeps the rest of the layer testable without
// needing the full nesrecomp runtime linked in.
#pragma once

#include <cstdint>

namespace smb::semcomp {

class GameState {
public:
    GameState() = default;

    // Raw 8-bit read from work RAM ($0000-$07FF). Mirrors above $0800 are
    // not modeled here; callers must pass addresses already in the canonical
    // 2KB window.
    std::uint8_t read8(std::uint16_t addr) const;

    // Convenience for SMB's page+offset pair pattern:
    //   world16 = (read8(page_addr) << 8) | read8(offset_addr)
    std::uint16_t read_page_offset(std::uint16_t page_addr,
                                    std::uint16_t offset_addr) const;

    // Raw 8-bit write into work RAM. Phase 2: only the Trainer and Mario
    // setters write through here. Ordinary game logic writes via
    // nes_write() inside the recompiled code path; this is a back-door
    // intended for mod-style overrides applied AFTER the game's frame
    // update.
    void write8(std::uint16_t addr, std::uint8_t val);

    // CPU register snapshot. Read-only.
    std::uint8_t cpu_a() const;
    std::uint8_t cpu_x() const;
    std::uint8_t cpu_y() const;
    std::uint8_t cpu_p() const;
    std::uint8_t cpu_s() const;
};

}  // namespace smb::semcomp
