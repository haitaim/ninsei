#ifndef NINSEI_REG_ALIAS_HPP
#define NINSEI_REG_ALIAS_HPP

#include "mmioreg.hpp"
#include <cstdint>

namespace ninsei {
    constexpr inline std::uint32_t mmio_address = 0x0400'0000;

    using Display_control = Mem_mapped_reg<std::uint32_t, readWriteMod::Read_write, mmio_address>;
    using Display_status = Mem_mapped_reg<std::uint16_t, readWriteMod::Read_write, mmio_address + 0x004>;
    using Vertical_count = Mem_mapped_reg<std::uint16_t, readWriteMod::Read_only, mmio_address + 0x006>;
}

#endif // NINSEI_REG_ALIAS_HPP