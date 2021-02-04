#ifndef NINSEI_REG_ALIAS_HPP
#define NINSEI_REG_ALIAS_HPP

#include "mmioreg.hpp"
#include <cstdint>

namespace ninsei {
    constexpr inline std::uint32_t mmio_address = 0x0400'0000;

    using Display_control = Mem_mapped_reg<std::uint32_t, readWriteMod::Read_write, mmio_address>;
    using Display_status = Mem_mapped_reg<std::uint16_t, readWriteMod::Read_write, mmio_address + 0x0004>;
    using Vertical_count = Mem_mapped_reg<std::uint16_t, readWriteMod::Read_only, mmio_address + 0x0006>;

    using Background0_control = Mem_mapped_reg<std::uint16_t, readWriteMod::Read_write, mmio_address + 0x0008>;
    using Background1_control = Mem_mapped_reg<std::uint16_t, readWriteMod::Read_write, mmio_address + 0x000A>;
    using Background2_control = Mem_mapped_reg<std::uint16_t, readWriteMod::Read_write, mmio_address + 0x000C>;
    using Background3_control = Mem_mapped_reg<std::uint16_t, readWriteMod::Read_write, mmio_address + 0x000E>;

    using Background0_horizontal_offset = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, mmio_address + 0x0010>;
    using Background0_vertical_offset = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, mmio_address + 0x0012>;
    using Background1_horizontal_offset = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, mmio_address + 0x0014>;
    using Background1_vertical_offset = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, mmio_address + 0x0016>;
    using Background2_horizontal_offset = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, mmio_address + 0x0018>;
    using Background2_vertical_offset = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, mmio_address + 0x001A>;
    using Background3_horizontal_offset = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, mmio_address + 0x001C>;
    using Background3_vertical_offset = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, mmio_address + 0x001E>;

    using Background2_parameter_a = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, mmio_address + 0x0020>;
    using Background2_parameter_b = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, mmio_address + 0x0022>;
    using Background2_parameter_c = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, mmio_address + 0x0024>;
    using Background2_parameter_d = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, mmio_address + 0x0026>;

    using Background2_x_reference = Mem_mapped_reg<std::uint32_t, readWriteMod::Write_only, mmio_address + 0x0028>;
    using Background2_y_reference = Mem_mapped_reg<std::uint32_t, readWriteMod::Write_only, mmio_address + 0x002C>;

    using Background3_parameter_a = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, mmio_address + 0x0030>;
    using Background3_parameter_b = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, mmio_address + 0x0032>;
    using Background3_parameter_c = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, mmio_address + 0x0034>;
    using Background3_parameter_d = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, mmio_address + 0x0036>;

    using Background3_x_reference = Mem_mapped_reg<std::uint32_t, readWriteMod::Write_only, mmio_address + 0x0038>;
    using Background3_y_reference = Mem_mapped_reg<std::uint32_t, readWriteMod::Write_only, mmio_address + 0x003C>;

    using Window0_horizontal_dimension = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, mmio_address + 0x0040>;
    using Window1_horizontal_dimension = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, mmio_address + 0x0042>;
    using Window0_vertical_dimension = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, mmio_address + 0x0044>;
    using Window1_vertical_dimension = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, mmio_address + 0x0046>;

    using Inside_windows = Mem_mapped_reg<std::uint16_t, readWriteMod::Read_write, mmio_address + 0x0048>;
    using Outside_windows = Mem_mapped_reg<std::uint16_t, readWriteMod::Read_write, mmio_address + 0x004A>;

    using Mosaic_size = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, mmio_address + 0x004C>;

    using Colour_effects = Mem_mapped_reg<std::uint16_t, readWriteMod::Read_write, mmio_address + 0x0050>;
    using Alpha_blend = Mem_mapped_reg<std::uint16_t, readWriteMod::Read_write, mmio_address + 0x0052>;
    using Brightness = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, mmio_address + 0x0054>;
}

#endif // NINSEI_REG_ALIAS_HPP