// mmioreg.hpp
//
// Implements general register class which includes read/write protection, and
// basic class to be inherited by registers with an interface
#ifndef NINSEI_MMIO_REG_HPP
#define NINSEI_MMIO_REG_HPP

#include <cstdint>
#include <concepts>
#include <type_traits>

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
    constexpr Mem_mapped_reg() = default;

    [[nodiscard("Unused volatile read")]]
    Reg_size read() noexcept requires readWriteMod::ReadAccess<Reg_access> {
        return *reinterpret_cast<volatile Reg_size*>(address);
    }

    void write(Reg_size bitmask) noexcept requires readWriteMod::WriteAccess<Reg_access> {
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
    void write() noexcept {
        *reinterpret_cast<volatile Reg_size*>(address) = internal_bitmask;
    }
protected:
    constexpr Interface_reg(): internal_bitmask {0} {}
    Reg_size internal_bitmask;
};
}

#endif // NINSEI_MMIO_REG_HPP
