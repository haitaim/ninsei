#ifndef NINSEI_REG_ALIAS_HPP
#define NINSEI_REG_ALIAS_HPP

#include "memmap.hpp"
#include "mmioreg.hpp"
#include "regmask.hpp"
#include <cstdint>

namespace ninsei::reg {
namespace lcd {
    using Display_control = Mem_mapped_reg<
        std::uint32_t,
        readWriteMod::Read_write,
        memAddress::io_registers,
        mask::Display_control
        >;
    using Display_status = Mem_mapped_reg<std::uint16_t, readWriteMod::Read_write, memAddress::io_registers + 0x0004>;
    using Vertical_count = Mem_mapped_reg<std::uint16_t, readWriteMod::Read_only, memAddress::io_registers + 0x0006>;

    using Background0_control = Mem_mapped_reg<std::uint16_t, readWriteMod::Read_write, memAddress::io_registers + 0x0008>;
    using Background1_control = Mem_mapped_reg<std::uint16_t, readWriteMod::Read_write, memAddress::io_registers + 0x000A>;
    using Background2_control = Mem_mapped_reg<std::uint16_t, readWriteMod::Read_write, memAddress::io_registers + 0x000C>;
    using Background3_control = Mem_mapped_reg<std::uint16_t, readWriteMod::Read_write, memAddress::io_registers + 0x000E>;

    using Background0_horizontal_offset = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, memAddress::io_registers + 0x0010>;
    using Background0_vertical_offset = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, memAddress::io_registers + 0x0012>;
    using Background1_horizontal_offset = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, memAddress::io_registers + 0x0014>;
    using Background1_vertical_offset = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, memAddress::io_registers + 0x0016>;
    using Background2_horizontal_offset = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, memAddress::io_registers + 0x0018>;
    using Background2_vertical_offset = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, memAddress::io_registers + 0x001A>;
    using Background3_horizontal_offset = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, memAddress::io_registers + 0x001C>;
    using Background3_vertical_offset = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, memAddress::io_registers + 0x001E>;

    using Background2_parameter_a = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, memAddress::io_registers + 0x0020>;
    using Background2_parameter_b = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, memAddress::io_registers + 0x0022>;
    using Background2_parameter_c = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, memAddress::io_registers + 0x0024>;
    using Background2_parameter_d = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, memAddress::io_registers + 0x0026>;

    using Background2_x_reference = Mem_mapped_reg<std::uint32_t, readWriteMod::Write_only, memAddress::io_registers + 0x0028>;
    using Background2_y_reference = Mem_mapped_reg<std::uint32_t, readWriteMod::Write_only, memAddress::io_registers + 0x002C>;

    using Background3_parameter_a = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, memAddress::io_registers + 0x0030>;
    using Background3_parameter_b = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, memAddress::io_registers + 0x0032>;
    using Background3_parameter_c = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, memAddress::io_registers + 0x0034>;
    using Background3_parameter_d = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, memAddress::io_registers + 0x0036>;

    using Background3_x_reference = Mem_mapped_reg<std::uint32_t, readWriteMod::Write_only, memAddress::io_registers + 0x0038>;
    using Background3_y_reference = Mem_mapped_reg<std::uint32_t, readWriteMod::Write_only, memAddress::io_registers + 0x003C>;

    using Window0_horizontal_dimension = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, memAddress::io_registers + 0x0040>;
    using Window1_horizontal_dimension = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, memAddress::io_registers + 0x0042>;
    using Window0_vertical_dimension = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, memAddress::io_registers + 0x0044>;
    using Window1_vertical_dimension = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, memAddress::io_registers + 0x0046>;

    using Inside_windows = Mem_mapped_reg<std::uint16_t, readWriteMod::Read_write, memAddress::io_registers + 0x0048>;
    using Outside_windows = Mem_mapped_reg<std::uint16_t, readWriteMod::Read_write, memAddress::io_registers + 0x004A>;

    using Mosaic_size = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, memAddress::io_registers + 0x004C>;

    using Colour_effects = Mem_mapped_reg<std::uint16_t, readWriteMod::Read_write, memAddress::io_registers + 0x0050>;
    using Alpha_blend = Mem_mapped_reg<std::uint16_t, readWriteMod::Read_write, memAddress::io_registers + 0x0052>;
    using Brightness = Mem_mapped_reg<std::uint16_t, readWriteMod::Write_only, memAddress::io_registers + 0x0054>;
}
namespace sound {
    using Channel1_sweep = Mem_mapped_reg<std::uint16_t, readWriteMod::Read_write, memAddress::io_registers + 0x0060>;
    using Channel1_duty = Mem_mapped_reg<std::uint16_t, readWriteMod::Read_write, memAddress::io_registers + 0x0062>;
    using Channel1_frequency = Mem_mapped_reg<std::uint16_t, readWriteMod::Read_write, memAddress::io_registers + 0x0064>;

    using Channel2_duty = Mem_mapped_reg<std::uint16_t, readWriteMod::Read_write, memAddress::io_registers + 0x0068>;
    using Channel2_frequency = Mem_mapped_reg<std::uint16_t, readWriteMod::Read_write, memAddress::io_registers + 0x006C>;

    using Channel3_stop_wave = Mem_mapped_reg<std::uint16_t, readWriteMod::Read_write, memAddress::io_registers + 0x0070>;
    using Channel3_length = Mem_mapped_reg<std::uint16_t, readWriteMod::Read_write, memAddress::io_registers + 0x0072>;
    using Channel3_frequency = Mem_mapped_reg<std::uint16_t, readWriteMod::Read_write, memAddress::io_registers + 0x0074>;

    using Channel4_length = Mem_mapped_reg<std::uint16_t, readWriteMod::Read_write, memAddress::io_registers + 0x0078>;
    using Channel4_frequency = Mem_mapped_reg<std::uint16_t, readWriteMod::Read_write, memAddress::io_registers + 0x007C>;

    using Stereo_volume = Mem_mapped_reg<std::uint16_t, readWriteMod::Read_write, memAddress::io_registers + 0x0080>;
    using Mixing_dma = Mem_mapped_reg<std::uint16_t, readWriteMod::Read_write, memAddress::io_registers + 0x0082>;
    using Sound_on_off = Mem_mapped_reg<std::uint16_t, readWriteMod::Read_write, memAddress::io_registers + 0x0084>;
}
namespace dma {

}
namespace timer {

}
namespace serialCom {

}
namespace keypad {
    using Status = Mem_mapped_reg<std::uint16_t, readWriteMod::Read_only, memAddress::io_registers + 0x0130>;
    using Interrupt_control = Mem_mapped_reg<std::uint16_t, readWriteMod::Read_write, memAddress::io_registers + 0x0132>;
}
namespace interrupt {

}
}

#endif // NINSEI_REG_ALIAS_HPP
