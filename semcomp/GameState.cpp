// semcomp/GameState.cpp — bridge from semcomp facade to nesrecomp C runtime.
#include "semcomp/GameState.h"

extern "C" {
#include "nes_runtime.h"
}

namespace smb::semcomp {

std::uint8_t GameState::read8(std::uint16_t addr) const {
    // Work RAM is the canonical $0000-$07FF window; nes_read handles mirrors
    // and PPU/APU register reads. Phase 0 only models work RAM.
    return g_ram[addr & 0x07FFu];
}

std::uint16_t GameState::read_page_offset(std::uint16_t page_addr,
                                          std::uint16_t offset_addr) const {
    const std::uint16_t page   = read8(page_addr);
    const std::uint16_t offset = read8(offset_addr);
    return static_cast<std::uint16_t>((page << 8) | offset);
}

std::uint8_t GameState::cpu_a() const { return g_cpu.A; }
std::uint8_t GameState::cpu_x() const { return g_cpu.X; }
std::uint8_t GameState::cpu_y() const { return g_cpu.Y; }
std::uint8_t GameState::cpu_p() const { return g_cpu.P; }
std::uint8_t GameState::cpu_s() const { return g_cpu.S; }

}  // namespace smb::semcomp
