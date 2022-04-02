//
// Created by bcfrutuozo on 01/04/2022.
//

#ifndef CPPDATASTRUCTURES_BOOLEAN_H
#define CPPDATASTRUCTURES_BOOLEAN_H

#include "TypeValue.h"

class Boolean {

    friend class Byte;
    friend class Char;
    friend class Int16;
    friend class Int32;
    friend class Int64;
    friend class Double;
    friend class Float;
    friend class SByte;
    friend class UInt16;
    friend class UInt32;
    friend class UInt64;

private:

    bool Value;

public:

    constexpr bool const& GetValue() const noexcept { return Value; }

    constexpr Boolean() : Value() {};

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    constexpr Boolean(T const& value) noexcept requires(is_promotion_primitive<T>::value) : Value((value)) {}

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    constexpr explicit Boolean(T const& wrapper) noexcept requires(is_promotion_wrapper<T>::value) : Value(wrapper) {}

    constexpr Boolean(Boolean const &) = default;

    constexpr Boolean(Boolean &&) = default;

    constexpr Boolean &operator=(Boolean &&) = default;

    /****************************************************
     Operators overload
     ***************************************************/

    // Operator= (Assingment)
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    constexpr Boolean& operator=(T const& value) noexcept requires(is_promotion_primitive<T>::value) { return Value = value; };

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    constexpr Boolean& operator=(T const& wrapper) noexcept requires(is_promotion_wrapper<T>::value) { Value = wrapper.GetValue(); return *this; };

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    constexpr operator T() noexcept requires(is_promotion_primitive<T>::value) { return Value; };


    // Operator=(Equality)
    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr bool operator==(Boolean const& lhs, T const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs.Value == rhs; }

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    friend inline constexpr bool operator==(Boolean const& lhs, T const& rhs) noexcept requires(is_promotion_wrapper<T>::value) { return lhs.Value == rhs.GetValue(); }

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    friend inline constexpr bool operator==(T const& lhs, Boolean const& rhs) noexcept requires(is_promotion_primitive<T>::value) { return lhs == rhs.Value; }

    constexpr Boolean const& operator+() const noexcept {
        return *this;
    }

    constexpr Boolean operator-() const noexcept {
        return Boolean(-Value);
    }

    constexpr Boolean operator~() const noexcept {
        return Boolean(~Value);
    }

    constexpr bool operator!() const noexcept {
        return !Value;
    }
};

#endif //CPPDATASTRUCTURES_BOOLEAN_H
