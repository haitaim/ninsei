// regalias.hpp
//
// Contains typedefs for GBA io registers
#ifndef NINSEI_REG_ALIAS_HPP
#define NINSEI_REG_ALIAS_HPP

#include "memmap.hpp"
#include "mmioreg.hpp"
#include "regmask.hpp"
#include <cstdint>

namespace ninsei::reg {
namespace lcd {
    // General display registers
    using Display_control = Mem_mapped_reg<
        std::uint32_t,
        readWriteMod::Read_write,
        memAddress::io_registers,
        mask::Display_control
        >;
    using Display_status = Mem_mapped_reg<
        std::uint16_t,
        readWriteMod::Read_write,
        memAddress::io_registers + 0x0004,
        mask::Display_status
        >;
    using Vertical_count = Mem_mapped_reg<
        std::uint16_t,
        readWriteMod::Read_only,
        memAddress::io_registers + 0x0006
        >;

    // Background registers
    template <unsigned bg_num> requires (bg_num >= 0 && bg_num <= 3)
    using Background_control = Mem_mapped_reg<
        std::uint16_t,
        readWriteMod::Read_write,
        memAddress::io_registers + 0x0008 + (2 * bg_num)
        >;
    template <unsigned bg_num> requires (bg_num >= 0 && bg_num <= 3)
    using Background_horizontal_offset = Mem_mapped_reg<
        std::uint16_t,
        readWriteMod::Write_only,
        memAddress::io_registers + 0x0010 + (4 * bg_num)
        >;
    template <unsigned bg_num> requires (bg_num >= 0 && bg_num <= 3)
    using Background_vertical_offset = Mem_mapped_reg<
        std::uint16_t,
        readWriteMod::Write_only,
        memAddress::io_registers + 0x0012 + (4 * bg_num)
        >;
    template <unsigned bg_num, char parameter>
    requires ((bg_num == 2 || bg_num == 3) && (parameter >= 'A' && parameter <= 'D'))
    using Background_rotation_scaling = Mem_mapped_reg<
        std::uint16_t,
        readWriteMod::Write_only,
        memAddress::io_registers + 0x0020 + ((bg_num - 2) * 0x10) + ((parameter - 'A') * 2)
        >;
    template <unsigned bg_num, char variable>
    requires ((bg_num == 2 || bg_num == 3) && (variable == 'x' || variable == 'y'))
    using Background_reference_point = Mem_mapped_reg<
        std::uint32_t,
        readWriteMod::Write_only,
        memAddress::io_registers + 0x0028  + ((bg_num - 2) * 0x10) + ((variable - 'x') * 4)
        >;
    
    // Window registers
    template <unsigned window_num> requires (window_num == 0 || window_num == 1)
    using Window_horizontal_dimension = Mem_mapped_reg<
        std::uint16_t,
        readWriteMod::Write_only,
        memAddress::io_registers + 0x0040 + (window_num * 2)
        >;
    template <unsigned window_num> requires (window_num == 0 || window_num == 1)
    using Window_vertical_dimension = Mem_mapped_reg<
        std::uint16_t,
        readWriteMod::Write_only,
        memAddress::io_registers + 0x0044 + (window_num * 2)
        >;
    using Inside_windows = Mem_mapped_reg<
        std::uint16_t,
        readWriteMod::Read_write,
        memAddress::io_registers + 0x0048
        >;
    using Outside_windows = Mem_mapped_reg<
        std::uint16_t,
        readWriteMod::Read_write,
        memAddress::io_registers + 0x004A
        >;

    // Other lcd registers
    using Mosaic_size = Mem_mapped_reg<
        std::uint16_t,
        readWriteMod::Write_only,
        memAddress::io_registers + 0x004C
        >;
    using Colour_effects = Mem_mapped_reg<
        std::uint16_t,
        readWriteMod::Read_write,
        memAddress::io_registers + 0x0050
        >;
    using Alpha_blend = Mem_mapped_reg<
        std::uint16_t,
        readWriteMod::Read_write,
        memAddress::io_registers + 0x0052
        >;
    using Brightness = Mem_mapped_reg<
        std::uint16_t,
        readWriteMod::Write_only,
        memAddress::io_registers + 0x0054
        >;
}
namespace sound {
    using Channel1_sweep = Mem_mapped_reg<
        std::uint16_t,
        readWriteMod::Read_write,
        memAddress::io_registers + 0x0060
        >;
    using Channel1_duty = Mem_mapped_reg<
        std::uint16_t,
        readWriteMod::Read_write,
        memAddress::io_registers + 0x0062
        >;
    using Channel1_frequency = Mem_mapped_reg<
        std::uint16_t,
        readWriteMod::Read_write,
        memAddress::io_registers + 0x0064
        >;

    using Channel2_duty = Mem_mapped_reg<
        std::uint16_t,
        readWriteMod::Read_write,
        memAddress::io_registers + 0x0068
        >;
    using Channel2_frequency = Mem_mapped_reg<
        std::uint16_t,
        readWriteMod::Read_write,
        memAddress::io_registers + 0x006C
        >;

    using Channel3_stop_wave = Mem_mapped_reg<
        std::uint16_t,
        readWriteMod::Read_write,
        memAddress::io_registers + 0x0070
        >;
    using Channel3_length = Mem_mapped_reg<
        std::uint16_t,
        readWriteMod::Read_write,
        memAddress::io_registers + 0x0072
        >;
    using Channel3_frequency = Mem_mapped_reg<
        std::uint16_t,
        readWriteMod::Read_write,
        memAddress::io_registers + 0x0074
        >;

    using Channel4_length = Mem_mapped_reg<
        std::uint16_t,
        readWriteMod::Read_write,
        memAddress::io_registers + 0x0078
        >;
    using Channel4_frequency = Mem_mapped_reg<
        std::uint16_t,
        readWriteMod::Read_write,
        memAddress::io_registers + 0x007C
        >;

    using Stereo_volume = Mem_mapped_reg<
        std::uint16_t,
        readWriteMod::Read_write,
        memAddress::io_registers + 0x0080
        >;
    using Mixing_dma = Mem_mapped_reg<
        std::uint16_t,
        readWriteMod::Read_write,
        memAddress::io_registers + 0x0082
        >;
    using Sound_on_off = Mem_mapped_reg<
        std::uint16_t,
        readWriteMod::Read_write,
        memAddress::io_registers + 0x0084
        >;
}
namespace dma {

}
namespace timer {

}
namespace serialCom {

}
namespace keypad {
    using Status = Mem_mapped_reg<
        std::uint16_t,
        readWriteMod::Read_only,
        memAddress::io_registers + 0x0130
        >;
    using Interrupt_control = Mem_mapped_reg<
        std::uint16_t,
        readWriteMod::Read_write,
        memAddress::io_registers + 0x0132
        >;
}
namespace interrupt {

}
}

#endif // NINSEI_REG_ALIAS_HPP
