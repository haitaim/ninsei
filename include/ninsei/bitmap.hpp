// bitmap.hpp
//
// Contains basic functions for GBA bitmap modes such as displaying individual
// pixels and rectangles
#ifndef NINSEI_BITMAP_HPP
#define NINSEI_BITMAP_HPP

#include "memmap.hpp"
#include "video.hpp"
#include <cstdint>

namespace ninsei::bitmap {
using video::Colour15;

constexpr std::uint32_t frame_offset(std::uint32_t frame_number) noexcept {
    return (frame_number & 1) * 0xA000;
}

namespace mode3 {
    inline void plot(std::uint32_t x, std::uint32_t y, Colour15 colour) noexcept {
        reinterpret_cast<volatile Colour15*>(memAddress::video_ram)[y * video::lcd::width + x] = colour;
    }

    inline void rectangle(
        std::uint32_t left_x,
        std::uint32_t top_y,
        std::uint32_t right_x,
        std::uint32_t bottom_y,
        Colour15 colour
    ) noexcept {
        std::uint32_t length = right_x - left_x;
        std::uint32_t height = bottom_y - top_y;
        auto upper_left = reinterpret_cast<volatile Colour15*>(
            memAddress::video_ram + (((top_y * video::lcd::width) + left_x) * 2)
        );

        for (std::uint32_t i = 0; i < height; ++i) {
            for (std::uint32_t j = 0; j < length; ++j) {
                upper_left[i * video::lcd::width + j] = colour;
            }
        }
    }

    inline void fill(Colour15 colour) noexcept {
        std::uint32_t word_length_colours = colour | (colour << 16);
        for (std::uint32_t i = 0; i < ((video::lcd::width * video::lcd::height) / 2); ++i) {
            reinterpret_cast<volatile std::uint32_t*>(memAddress::video_ram)[i] = word_length_colours;
        }
    }
}
namespace mode4 {
    inline void fill(std::uint32_t palette_num, std::uint32_t frame_number = 0) noexcept {
        std::uint32_t word_length_palettes = palette_num
            | (palette_num << 8)
            | (palette_num << 16)
            | (palette_num << 24);

        const std::uint32_t frame_address = memAddress::video_ram + frame_offset(frame_number);
        for (std::uint32_t i = 0; i < ((video::lcd::width * video::lcd::height) / 2); ++i) {
            reinterpret_cast<volatile std::uint32_t*>(frame_address)[i] = word_length_palettes;
        }
    }
}
namespace mode5 {
    namespace lcd {
        inline constexpr std::uint32_t width = 160;
        inline constexpr std::uint32_t height = 128;
    }

    inline void plot(std::uint32_t x,
        std::uint32_t y,
        Colour15 colour,
        std::uint32_t frame_number = 0
    ) noexcept {
        const std::uint32_t frame_address = memAddress::video_ram + frame_offset(frame_number);
        reinterpret_cast<volatile Colour15*>(frame_address)[y * lcd::width + x] = colour;
    }

    inline void rectangle(
        std::uint32_t left_x,
        std::uint32_t top_y,
        std::uint32_t right_x,
        std::uint32_t bottom_y,
        Colour15 colour,
        std::uint32_t frame_number = 0
    ) noexcept {
        std::uint32_t length = right_x - left_x;
        std::uint32_t height = bottom_y - top_y;
        auto upper_left = reinterpret_cast<volatile Colour15*>(
            memAddress::video_ram + frame_offset(frame_number) + (((top_y * mode5::lcd::width) + left_x) * 2)
        );

        for (std::uint32_t i = 0; i < height; ++i) {
            for (std::uint32_t j = 0; j < length; ++j) {
                upper_left[i * mode5::lcd::width + j] = colour;
            }
        }
    }

    inline void fill(Colour15 colour, std::uint32_t frame_number = 0) noexcept {
        std::uint32_t word_length_colours = colour | (colour << 16);
        const std::uint32_t frame_address = memAddress::video_ram + frame_offset(frame_number);
        for (std::uint32_t i = 0; i < ((mode5::lcd::width * mode5::lcd::height) / 2); ++i) {
            reinterpret_cast<volatile std::uint32_t*>(frame_address)[i] = word_length_colours;
        }
    }
}
}

#endif // NINSEI_BITMAP_HPP
