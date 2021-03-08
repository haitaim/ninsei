// mmioreg.hpp
//
// Implements general register class which includes read/write protection and
// basic class to be inherited by registers with an interface
#ifndef NINSEI_MMIO_REG_HPP
#define NINSEI_MMIO_REG_HPP

#include <cstdint>
#include <concepts>

namespace ninsei::reg {
namespace readWriteMod {
    // Modifier tags
    class Read_only {};
    class Write_only {};
    class Read_write : public Read_only, public Write_only {};

    template <typename T>
    concept ReadAccess = std::derived_from<T, Read_only>;
    template <typename T>
    concept WriteAccess = std::derived_from<T, Write_only>;
}

template <typename Reg_size, typename Reg_access, unsigned address>
class Mem_mapped_reg {
public:
    constexpr Mem_mapped_reg() noexcept {}

    [[nodiscard("Unused volatile read")]]
    Reg_size read() const noexcept requires readWriteMod::ReadAccess<Reg_access> {
        return *reinterpret_cast<volatile Reg_size*>(address);
    }

    void write(Reg_size bitmask) const noexcept requires readWriteMod::WriteAccess<Reg_access> {
        *reinterpret_cast<volatile Reg_size*>(address) = bitmask;
    }

    Mem_mapped_reg(const Mem_mapped_reg&) = delete;
    Mem_mapped_reg(Mem_mapped_reg&&) = delete;
    Mem_mapped_reg& operator=(const Mem_mapped_reg&) = delete;
    Mem_mapped_reg& operator=(Mem_mapped_reg&&) = delete;
};

template <typename Reg_size, typename Reg_access, unsigned address>
class Interface_reg : public Mem_mapped_reg<Reg_size, Reg_access, address> {
public:
    void write() const noexcept {
        *reinterpret_cast<volatile Reg_size*>(address) = internal_bitmask;
    }
protected:
    constexpr Interface_reg() noexcept : internal_bitmask { 0 } {}

    Reg_size internal_bitmask;

    void enable_bit(unsigned bit_position, bool enable) noexcept {
        if (enable) {
            internal_bitmask |= (1 << bit_position);
        } else {
            internal_bitmask &= ~(1 << bit_position);
        }
    }
};
}

#endif // NINSEI_MMIO_REG_HPP
