// keypad.hpp
//
// Defines Keypad class for managing GBA input
#ifndef NINSEI_KEYPAD_HPP
#define NINSEI_KEYPAD_HPP

#include "regdef.hpp"
#include <cstdint>
#include <type_traits>

namespace ninsei {
class Keypad {
public:
    constexpr Keypad() noexcept {}

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

    inline void poll() const noexcept {
        previous_key = current_key;
        current_key = ~reg::keypad::Status().read() & 0x03FF;
    }

    template <typename... Key_masks>
    [[nodiscard("Unused key check")]]
    inline bool is_down(Key_mask first, Key_masks... rest) const noexcept {
        static_assert(std::conjunction_v<std::is_same<Key_mask, Key_masks>...>, "Only key masks accepted");
        std::uint32_t key_mask = make_mask(first, rest...);
        return (key_mask & current_key) == key_mask;
    }

    template <typename... Key_masks>
    [[nodiscard("Unused key check")]]
    inline bool was_down(Key_mask first, Key_masks... rest) const noexcept {
        static_assert(std::conjunction_v<std::is_same<Key_mask, Key_masks>...>, "Only key masks accepted");
        std::uint32_t key_mask = make_mask(first, rest...);
        return (key_mask & previous_key) == key_mask;
    }

    template <typename... Key_masks>
    [[nodiscard("Unused key check")]]
    inline bool is_hit(Key_mask first, Key_masks... rest) const noexcept {
        static_assert(std::conjunction_v<std::is_same<Key_mask, Key_masks>...>, "Only key masks accepted");
        std::uint32_t key_mask = make_mask(first, rest...);
        return (current_key & ~previous_key & key_mask) == key_mask;
    }

    template <typename... Key_masks>
    [[nodiscard("Unused key check")]]
    inline bool is_held(Key_mask first, Key_masks... rest) const noexcept {
        static_assert(std::conjunction_v<std::is_same<Key_mask, Key_masks>...>, "Only key masks accepted");
        std::uint32_t key_mask = make_mask(first, rest...);
        return (current_key & previous_key & key_mask) == key_mask;
    }

    template <typename... Key_masks>
    [[nodiscard("Unused key check")]]
    inline bool is_released(Key_mask first, Key_masks... rest) const noexcept {
        static_assert(std::conjunction_v<std::is_same<Key_mask, Key_masks>...>, "Only key masks accepted");
        std::uint32_t key_mask = make_mask(first, rest...);
        return (~current_key & previous_key & key_mask) == key_mask;
    }

    Keypad(const Keypad&) = delete;
    Keypad(Keypad&&) = delete;
    Keypad& operator=(const Keypad&) = delete;
    Keypad& operator=(Keypad&&) = delete;
private:
    static inline std::uint32_t current_key = 0;
    static inline std::uint32_t previous_key = 0;

    static constexpr std::uint32_t make_mask(Key_mask mask) noexcept {
        return static_cast<std::uint32_t>(mask);
    }

    template <typename... Key_masks>
    static constexpr std::uint32_t make_mask(Key_mask first, Key_masks ...rest) noexcept {
        return static_cast<std::uint32_t>(first) | make_mask(rest...);
    }
};
}

#endif // NINSEI_KEYPAD_HPP
