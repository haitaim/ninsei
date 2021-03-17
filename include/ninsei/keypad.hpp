// keypad.hpp
//
// Defines Keypad class for managing GBA input
#ifndef NINSEI_KEYPAD_HPP
#define NINSEI_KEYPAD_HPP

#include "regdef.hpp"
#include <cstdint>

namespace ninsei {
enum class Key_mask : std::uint32_t {
    a_button = 1,
    b_button = 1 << 1,
    select = 1 << 2,
    start = 1 << 3,
    right = 1 << 4,
    left = 1 << 5,
    up = 1 << 6,
    down = 1 << 7,
    right_shoulder = 1 << 8,
    left_shoulder = 1 << 9
};

constexpr Key_mask operator|(Key_mask lhs, Key_mask rhs) noexcept {
    return static_cast<Key_mask>(static_cast<std::uint32_t>(lhs) | static_cast<std::uint32_t>(rhs));
}

class Keypad {
public:
    constexpr Keypad() noexcept {}

    void poll() const noexcept {
        previous_key = current_key;
        current_key = ~reg::keypad::Status().read() & 0x03FF;
    }

    [[nodiscard("Unused key check")]]
    bool is_down(Key_mask mask) const noexcept {
        const auto key_mask = static_cast<std::uint32_t>(mask);
        return (key_mask & current_key) == key_mask;
    }

    [[nodiscard("Unused key check")]]
    bool was_down(Key_mask mask) const noexcept {
        const auto key_mask = static_cast<std::uint32_t>(mask);
        return (key_mask & previous_key) == key_mask;
    }

    [[nodiscard("Unused key check")]]
    bool is_hit(Key_mask mask) const noexcept {
        const auto key_mask = static_cast<std::uint32_t>(mask);
        return (current_key & ~previous_key & key_mask) == key_mask;
    }

    [[nodiscard("Unused key check")]]
    bool is_held(Key_mask mask) const noexcept {
        const auto key_mask = static_cast<std::uint32_t>(mask);
        return (current_key & previous_key & key_mask) == key_mask;
    }

    [[nodiscard("Unused key check")]]
    bool is_released(Key_mask mask) const noexcept {
        const auto key_mask = static_cast<std::uint32_t>(mask);
        return (~current_key & previous_key & key_mask) == key_mask;
    }

    [[nodiscard("Unused key check")]]
    std::int32_t horizontal_direction() const noexcept {
        return ((current_key >> 4) & 1) - ((current_key >> 5) & 1);
    }

    [[nodiscard("Unused key check")]]
    std::int32_t vertical_direction() const noexcept {
        return ((current_key >> 7) & 1) - ((current_key >> 6) & 1);
    }

    Keypad(const Keypad&) = delete;
    Keypad(Keypad&&) = delete;
    Keypad& operator=(const Keypad&) = delete;
    Keypad& operator=(Keypad&&) = delete;
    ~Keypad() = default;
private:
    static inline std::uint32_t current_key = 0;
    static inline std::uint32_t previous_key = 0;
};
}

#endif // NINSEI_KEYPAD_HPP
