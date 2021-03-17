// bitmap.hpp
//
// Contains basic functions for GBA bitmap modes such as displaying individual
// pixels and rectangles
// Also includes Buffer_offset class to manage page flipping
#ifndef NINSEI_BITMAP_HPP
#define NINSEI_BITMAP_HPP

#include "memmap.hpp"
#include "video.hpp"
#include <cstdint>

namespace ninsei {

class Buffer_offset {
public:
    constexpr Buffer_offset() noexcept : buffer_number { 0 } {}

    void swap_buffer() noexcept {
        buffer_number ^= 0xA000;
    }

    Buffer_offset(const Buffer_offset&) = default;
    Buffer_offset(Buffer_offset&&) = delete;
    Buffer_offset& operator=(const Buffer_offset&) = delete;
    Buffer_offset& operator=(Buffer_offset&&) = delete;
    ~Buffer_offset() = default;

    template <unsigned mode>
    friend class bitmap;
private:
    std::uint32_t buffer_number;
};

template <unsigned mode>
class bitmap {
    static_assert(mode >= 3 && mode <= 5, "Only modes 3, 4, and 5 are valid bitmap modes");
};

template <>
class bitmap<3> {
public:
    static inline void plot(std::uint32_t x, std::uint32_t y, Colour15 colour) noexcept {
        reinterpret_cast<volatile Colour15*>(address::video_ram)[y * video::lcd::width + x] = colour;
    }

    static inline void rectangle(
        std::uint32_t left_x,
        std::uint32_t top_y,
        std::uint32_t right_x,
        std::uint32_t bottom_y,
        Colour15 colour
    ) noexcept {
        const std::uint32_t length = right_x - left_x;
        const std::uint32_t height = bottom_y - top_y;
        const auto upper_left = reinterpret_cast<volatile Colour15*>(address::video_ram)
            + (top_y * video::lcd::width + left_x);

        for (std::uint32_t i = 0; i < height; ++i) {
            for (std::uint32_t j = 0; j < length; ++j) {
                upper_left[i * video::lcd::width + j] = colour;
            }
        }
    }

    static inline void fill(Colour15 colour) noexcept {
        const std::uint32_t word_length_colours = colour | (colour << 16);
        constexpr std::uint32_t word_scaled_size = video::lcd::size / 2;

        for (std::uint32_t i = 0; i < word_scaled_size; ++i) {
            reinterpret_cast<volatile std::uint32_t*>(address::video_ram)[i] = word_length_colours;
        }
    }

    bitmap<3>() = delete;
};

template <>
class bitmap<4> {
public:
    static inline void plot(
        std::uint32_t x,
        std::uint32_t y,
        std::uint32_t palette_num,
        Buffer_offset offset = Buffer_offset{}
    ) noexcept {
        const auto two_points =
            reinterpret_cast<volatile std::uint16_t*>(address::video_ram + offset.buffer_number)
            + ((y * video::lcd::width + x) / 2);

        if ((x & 1) == 0) {
            *two_points = (*two_points & ~0xFF) | palette_num;
        } else {
            *two_points = (*two_points & 0xFF) | (palette_num << 8);
        }
    }

    static inline void fill(std::uint32_t palette_num, Buffer_offset offset = Buffer_offset{}) noexcept {
        const std::uint32_t word_length_palettes = palette_num
            | (palette_num << 8)
            | (palette_num << 16)
            | (palette_num << 24);
        constexpr std::uint32_t word_scaled_frame = video::lcd::size / 4;
        const auto frame = reinterpret_cast<volatile std::uint32_t*>(
            address::video_ram + offset.buffer_number
        );

        for (std::uint32_t i = 0; i < word_scaled_frame; ++i) {
            frame[i] = word_length_palettes;
        }
    }

    bitmap<4>() = delete;
};

template <>
class bitmap<5> {
public:
    static inline constexpr std::uint32_t width = 160;
    static inline constexpr std::uint32_t height = 128;
    static inline constexpr std::uint32_t size = width * height;

    static inline void plot(
        std::uint32_t x,
        std::uint32_t y,
        Colour15 colour,
        Buffer_offset offset = Buffer_offset{}
    ) noexcept {
        const auto frame = reinterpret_cast<volatile Colour15*>(
            address::video_ram + offset.buffer_number
        );
        frame[y * width + x] = colour;
    }

    static inline void rectangle(
        std::uint32_t left_x,
        std::uint32_t top_y,
        std::uint32_t right_x,
        std::uint32_t bottom_y,
        Colour15 colour,
        Buffer_offset offset = Buffer_offset{}
    ) noexcept {
        const std::uint32_t length = right_x - left_x;
        const std::uint32_t height = bottom_y - top_y;
        const auto upper_left =
            reinterpret_cast<volatile Colour15*>(address::video_ram + offset.buffer_number)
            + (top_y * width + left_x);

        for (std::uint32_t i = 0; i < height; ++i) {
            for (std::uint32_t j = 0; j < length; ++j) {
                upper_left[i * width + j] = colour;
            }
        }
    }

    static inline void fill(Colour15 colour, Buffer_offset offset = Buffer_offset{}) noexcept {
        const std::uint32_t word_length_colours = colour | (colour << 16);
        constexpr std::uint32_t word_scaled_frame = bitmap<5>::size / 2;
        const auto frame = reinterpret_cast<volatile std::uint32_t*>(
            address::video_ram + offset.buffer_number
        );

        for (std::uint32_t i = 0; i < word_scaled_frame; ++i) {
            frame[i] = word_length_colours;
        }
    }

    bitmap<5>() = delete;
};
}

#endif // NINSEI_BITMAP_HPP
