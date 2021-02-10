#ifndef NINSEI_REG_MASK_HPP
#define NINSEI_REG_MASK_HPP

#include "mmioreg.hpp"
#include <cstdint>

namespace ninsei::reg {
namespace mask {
    template<typename Reg_size>
    inline Reg_size enable_bit(Reg_size bitmask, const unsigned int bit_position, bool enable) {
        if (enable) {
            bitmask |= (1 << bit_position);
        } else {
            bitmask &= ~(1 << bit_position);
        }
        return bitmask;
    }
    
    class Display_control : public Register_mask {
    public:
        Display_control() : bitmask { 0 } {}
        Display_control(std::uint32_t input_mask) : bitmask { input_mask } {}
        
        template <unsigned mode> requires (mode >= 0 && mode <= 3)
        void set_mode() {
            bitmask &= ~(3);
            bitmask |= mode;
        }
        void swap_page() {
            bitmask ^= (1 << 4);
        }
        void oam_hblank_access(bool enable) {
            bitmask = enable_bit(bitmask, 5, enable);
        }
        void object_mapping_mode(bool mode) {
            bitmask = enable_bit(bitmask, 6, mode);
        }
        void force_blank(bool enable) {
            bitmask = enable_bit(bitmask, 7, enable);
        }
        template <unsigned bg_num> requires (bg_num >= 0 && bg_num <= 3)
        void enable_background(bool enable) {
            bitmask = enable_bit(bitmask, 8 + bg_num, enable);
        }
        void enable_obj_background(bool enable) {
            bitmask = enable_bit(bitmask, 0xC, enable);
        }
        std::uint32_t raw_bitmask() {
            return bitmask;
        }

    private:
        std::uint32_t bitmask;
    };
}
}

#endif // NINSEI_REG_MASK_HPP
