//
// Created by bcfrutuozo on 31/03/2022.
//

#ifndef CPPDATASTRUCTURES_INT32_H
#define CPPDATASTRUCTURES_INT32_H

#include "TypeValue.h"
#include <cstdint>

class Int32 {

    friend class Boolean;
    friend class Byte;
    friend class Char;
    friend class Int16;
    friend class Int64;
    friend class Double;
    friend class Float;
    friend class SByte;
    friend class UInt16;
    friend class UInt32;
    friend class UInt64;

private:

    int32_t Value;

public:

    constexpr int32_t const& GetValue() const noexcept { return Value; }

    constexpr Int32() : Value() {};

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    constexpr Int32(T value) noexcept requires(is_promotion_primitive<T>::value) : Value((value)) {}

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    constexpr explicit Int32(T const& wrapper) noexcept requires(is_promotion_wrapper<T>::value) : Value(wrapper) {}

    constexpr Int32(Int32 const &) = default;

    Int32(Int32 &&) = default;

    constexpr Int32 &operator=(Int32 const &) = default;

    constexpr Int32 &operator=(Int32 &&) = default;

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    constexpr Int32 operator=(T const& value) noexcept requires(is_promotion_primitive<T>::value) { return Value = value; };

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    constexpr Int32& operator=(T const& wrapper) noexcept requires(is_promotion_wrapper<T>::value) { Value = wrapper.GetValue(); return *this; };

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    constexpr operator T() noexcept requires(is_promotion_primitive<T>::value) { return Value; };

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr bool operator==(Int32 const& lhs, T const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs.Value == rhs; }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    friend inline constexpr bool operator==(Int32 const& lhs, T const& rhs) noexcept requires(is_promotion_wrapper<T>::value) { return lhs.Value == rhs.GetValue(); }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr bool operator==(T const& lhs, Int32 const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs == rhs.Value; }

    constexpr Int32 const& operator+() const noexcept {
        return *this;
    }

    constexpr Int32 operator-() const noexcept {
        return Int32(-Value);
    }

    constexpr Int32 operator~() const noexcept {
        return Int32(~Value);
    }

    constexpr bool operator!() const noexcept {
        return !Value;
    }

    Int32& operator++() noexcept {
        ++Value;
        return *this;
    }
    Int32 operator++(int) noexcept {
        return Int32(Value++);
    }

    Int32& operator--() noexcept {
        --Value;
        return *this;
    }

    Int32 operator--(int) noexcept {
        return Int32(Value--);
    }
};

#endif //CPPDATASTRUCTURES_INT32_H
