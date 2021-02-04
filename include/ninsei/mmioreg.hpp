// mmioreg.hpp
//
// Implements general register class which includes read/write protection.
#ifndef NINSEI_MMIO_REG_HPP
#define NINSEI_MMIO_REG_HPP

#include <cstdint>
#include <concepts>
#include <type_traits>

namespace ninsei {
    namespace readWriteMod {
        // Modifier tags
        class Read_only {};
        class Write_only {};
        class Read_write : public Read_only, public Write_only {};

        template <typename T>
        concept ReadAccess = std::derived_from<T, Read_only>;
        template <typename T>
        concept WriteAccess = std::derived_from<T, Write_only>;
        template <typename T>
        concept RegisterAccess = ReadAccess<T> || WriteAccess<T>;
    }
    namespace reg {
        template <std::unsigned_integral Reg_size, readWriteMod::RegisterAccess Reg_access, std::uint32_t address>
        class Mem_mapped_reg {
        public:
            Mem_mapped_reg() : reg_address { reinterpret_cast<volatile Reg_size*>(address) } {};

            [[nodiscard("Unused volatile read")]]
            Reg_size read() const noexcept requires readWriteMod::ReadAccess<Reg_access> {
                return *reg_address;
            }

            Mem_mapped_reg& operator=(Reg_size bitmask) noexcept requires readWriteMod::WriteAccess<Reg_access> {
                *reg_address = bitmask;
                return *this;
            }

            Mem_mapped_reg(const Mem_mapped_reg&) = delete;
            Mem_mapped_reg(Mem_mapped_reg&&) = delete;
            Mem_mapped_reg& operator=(const Mem_mapped_reg&) = delete;
            Mem_mapped_reg& operator=(Mem_mapped_reg&&) = delete;

        private:
            volatile Reg_size* reg_address;
        };
    }
}

#endif // NINSEI_MMIO_REG_HPP
