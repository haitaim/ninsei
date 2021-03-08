// regalias.hpp
//
// Contains typedefs and interfaces for GBA io registers
#ifndef NINSEI_REG_ALIAS_HPP
#define NINSEI_REG_ALIAS_HPP

#include "memmap.hpp"
#include "mmioreg.hpp"
#include <cstdint>

namespace ninsei::reg {
    template<typename Reg_size>
    inline Reg_size enable_bit(Reg_size bitmask, const unsigned bit_position, bool enable) {
        if (enable) {
            bitmask |= (1 << bit_position);
        } else {
            bitmask &= ~(1 << bit_position);
        }
        return bitmask;
    }

namespace lcd {
    // General display registers
    class Display_control : public Interface_reg<
        std::uint32_t,
        readWriteMod::Read_write,
        memAddress::io_registers
    > {
    public:
        constexpr Display_control(): Interface_reg{} {}

        template <unsigned mode>
        Display_control& set_mode() {
            static_assert(mode >= 0 && mode <= 5, "Invalid display mode number");
            internal_bitmask &= ~(3);
            internal_bitmask |= mode;
            return *this;
        }
        Display_control& swap_page() {
            internal_bitmask ^= (1 << 4);
            return *this;
        }
        Display_control& oam_hblank_access(bool enable) {
            internal_bitmask = enable_bit(internal_bitmask, 5, enable);
            return *this;
        }
        template <unsigned mode>
        Display_control& object_mapping_mode() {
            static_assert(mode == 0 || mode == 1, "Invalid object mapping mode number");
            if (mode == 1) {
                internal_bitmask |= (1 << 6);
            } else {
                internal_bitmask &= ~(1 << 6);
            }
            return *this;
        }
        Display_control& force_blank(bool enable) {
            internal_bitmask = enable_bit(internal_bitmask, 7, enable);
            return *this;
        }
        template <unsigned bg_num>
        Display_control& enable_background(bool enable) {
            static_assert(bg_num >= 0 && bg_num <= 3, "Invalid background number");
            internal_bitmask = enable_bit(internal_bitmask, 8 + bg_num, enable);
            return *this;
        }
        Display_control& enable_obj_background(bool enable) {
            internal_bitmask = enable_bit(internal_bitmask, 0xC, enable);
            return *this;
        }
    };
    class Display_status : public Interface_reg<
        std::uint16_t,
        readWriteMod::Read_write,
        memAddress::io_registers + 0x0004
    > {
    public:
        constexpr Display_status(): Interface_reg{} {}

        Display_status& vblank_interrupt(bool enable) {
            internal_bitmask = enable_bit(internal_bitmask, 3, enable);
            return *this;
        }
        Display_status& hblank_interrupt(bool enable) {
            internal_bitmask = enable_bit(internal_bitmask, 4, enable);
            return *this;
        }
        Display_status& vertical_count_interrupt(bool enable) {
            internal_bitmask = enable_bit(internal_bitmask, 5, enable);
            return *this;
        }
        Display_status& set_vertical_count_trigger(std::uint8_t value) {
            internal_bitmask &= 0xFF;
            internal_bitmask |= (value << 8);
            return *this;
        }
    };
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

    enum class Matrix_parameter {A, B, C, D};
    template <unsigned bg_num, Matrix_parameter parameter>
    requires (bg_num == 2 || bg_num == 3)
    using Background_rotation_scaling = Mem_mapped_reg<
        std::uint16_t,
        readWriteMod::Write_only,
        memAddress::io_registers + 0x0020 + ((bg_num - 2) * 0x10) + (static_cast<int>(parameter) * 2)
    >;

    enum class Ref_point_variable {x, y};
    template <unsigned bg_num, Ref_point_variable variable>
    requires (bg_num == 2 || bg_num == 3)
    using Background_reference_point = Mem_mapped_reg<
        std::uint32_t,
        readWriteMod::Write_only,
        memAddress::io_registers + 0x0028  + ((bg_num - 2) * 0x10) + (static_cast<int>(variable) * 4)
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