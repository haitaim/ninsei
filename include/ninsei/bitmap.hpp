// bitmap.hpp
//
// Contains basic functions for GBA bitmap modes such as displaying individual
// pixels and rectangles
#ifndef NINSEI_BITMAP_HPP
#define NINSEI_BITMAP_HPP

#include "memmap.hpp"
#include "video.hpp"
#include <cstdint>

namespace ninsei {
namespace bitmapHelper {
    constexpr std::uint32_t frame_offset(std::uint32_t frame_number) noexcept {
        return (frame_number & 1) * 0xA000;
    }
}

template <unsigned mode>
class bitmap {
    static_assert(mode >= 3 && mode <= 5, "Only modes 3, 4, and 5 are valid bitmap modes");
};

template <>
class bitmap<3> {
public:
    static inline void plot(std::uint32_t x, std::uint32_t y, Colour15 colour) noexcept {
        reinterpret_cast<volatile Colour15*>(memAddress::video_ram)[y * video::lcd::width + x] = colour;
    }

    static inline void rectangle(
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

    static inline void fill(Colour15 colour) noexcept {
        std::uint32_t word_length_colours = colour | (colour << 16);
        for (std::uint32_t i = 0; i < ((video::lcd::width * video::lcd::height) / 2); ++i) {
            reinterpret_cast<volatile std::uint32_t*>(memAddress::video_ram)[i] = word_length_colours;
        }
    }

    bitmap<3>() = delete;
};

template <>
class bitmap<4> {
public:
    static inline void fill(std::uint32_t palette_num, std::uint32_t frame_number = 0) noexcept {
        std::uint32_t word_length_palettes = palette_num
            | (palette_num << 8)
            | (palette_num << 16)
            | (palette_num << 24);

        const std::uint32_t frame_address = memAddress::video_ram
            + bitmapHelper::frame_offset(frame_number);
        for (std::uint32_t i = 0; i < ((video::lcd::width * video::lcd::height) / 2); ++i) {
            reinterpret_cast<volatile std::uint32_t*>(frame_address)[i] = word_length_palettes;
        }
    }

    bitmap<4>() = delete;
};

template <>
class bitmap<5> {
public:
    static inline constexpr std::uint32_t width = 160;
    static inline constexpr std::uint32_t height = 128;

    static inline void plot(std::uint32_t x,
        std::uint32_t y,
        Colour15 colour,
        std::uint32_t frame_number = 0
    ) noexcept {
        const std::uint32_t frame_address = memAddress::video_ram + bitmapHelper::frame_offset(frame_number);
        reinterpret_cast<volatile Colour15*>(frame_address)[y * width + x] = colour;
    }

    static inline void rectangle(
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
            memAddress::video_ram
            + bitmapHelper::frame_offset(frame_number)
            + (((top_y * width) + left_x) * 2)
        );

        for (std::uint32_t i = 0; i < height; ++i) {
            for (std::uint32_t j = 0; j < length; ++j) {
                upper_left[i * width + j] = colour;
            }
        }
    }

    static inline void fill(Colour15 colour, std::uint32_t frame_number = 0) noexcept {
        std::uint32_t word_length_colours = colour | (colour << 16);
        const std::uint32_t frame_address = memAddress::video_ram
            + bitmapHelper::frame_offset(frame_number);
        for (std::uint32_t i = 0; i < ((width * height) / 2); ++i) {
            reinterpret_cast<volatile std::uint32_t*>(frame_address)[i] = word_length_colours;
        }
    }

    bitmap<5>() = delete;
};
}

#endif // NINSEI_BITMAP_HPP
