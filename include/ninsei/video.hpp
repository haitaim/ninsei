// video.hpp
//
// Includes miscellaneous functions and constants related to video output
#ifndef NINSEI_VIDEO_HPP
#define NINSEI_VIDEO_HPP

#include "regdef.hpp"
#include <cstdint>

namespace ninsei {
namespace video {
namespace lcd {
    inline constexpr std::uint32_t width = 240;
    inline constexpr std::uint32_t height = 160;
    inline constexpr std::uint32_t horizontal_blank = 68;
    inline constexpr std::uint32_t vertical_blank = 68;
}

inline void vertical_sync() noexcept {
    reg::lcd::Vertical_count count;
    // Finish remaining vertical blank cycles
    while (count.read() >= lcd::height);
    // Wait for beginning of new vertical blank period
    while (count.read() < lcd::height);
}
}

using Colour15 = std::uint16_t;
namespace colour {
    constexpr Colour15 rgb_conversion(std::uint32_t red, std::uint32_t green, std::uint32_t blue) noexcept {
        return red | (green << 5) | (blue << 10);
    }

    inline constexpr Colour15 black = 0x0000;
    inline constexpr Colour15 white = 0x7FFF;

    inline constexpr Colour15 red = 0x001F;
    inline constexpr Colour15 yellow = 0x03FF;
    inline constexpr Colour15 green = 0x03E0;
    inline constexpr Colour15 cyan = 0x7FE0;
    inline constexpr Colour15 blue = 0x7C00;
    inline constexpr Colour15 magenta = 0x7C1F;
}
}

#endif // NINSEI_VIDEO_HPP
