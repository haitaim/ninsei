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
    }
    namespace reg {
        template <std::unsigned_integral Reg_size, typename Reg_access, std::uint32_t address>
        class Mem_mapped_reg {
        public:
            [[nodiscard("Unused volatile read")]]
            static inline Reg_size read() noexcept requires readWriteMod::ReadAccess<Reg_access> {
                return *reinterpret_cast<volatile Reg_size*>(address);
            }

            static inline void write(Reg_size bitmask) noexcept requires readWriteMod::WriteAccess<Reg_access> {
                *reinterpret_cast<volatile Reg_size*>(address) = bitmask;
            }

            Mem_mapped_reg() = delete;
            Mem_mapped_reg(const Mem_mapped_reg&) = delete;
            Mem_mapped_reg(Mem_mapped_reg&&) = delete;
            Mem_mapped_reg& operator=(const Mem_mapped_reg&) = delete;
            Mem_mapped_reg& operator=(Mem_mapped_reg&&) = delete;
        };
    }
}

#endif // NINSEI_MMIO_REG_HPP
