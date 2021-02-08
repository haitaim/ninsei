#ifndef NINSEI_MEM_MAP_HPP
#define NINSEI_MEM_MAP_HPP

#include <cstdint>

namespace ninsei::memAddress {
    inline constexpr std::uint32_t external_work_ram = 0x0200'0000;
    inline constexpr std::uint32_t internal_work_ram = 0x0300'0000;
    inline constexpr std::uint32_t io_registers = 0x0400'0000;
    inline constexpr std::uint32_t pallete_ram = 0x0500'0000;
    inline constexpr std::uint32_t video_ram = 0x0600'0000;
    inline constexpr std::uint32_t object_attribute = 0x0700'0000;
    inline constexpr std::uint32_t cartridge_rom = 0x0800'0000;
    inline constexpr std::uint32_t cartridge_sram = 0x0E00'0000;
}

#endif // NINSEI_MEM_MAP_HPP
