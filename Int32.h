//
// Created by bcfrutuozo on 31/03/2022.
//

#ifndef CPPDATASTRUCTURES_INT32_H
#define CPPDATASTRUCTURES_INT32_H

#include "TypeValue.h"
#include <cstdint>

class Int32 {

private:

    int32_t Value;

public:

    constexpr Int32() : Value() {};

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    constexpr Int32(T value) noexcept requires(is_promotion_primitive<T>::value) : Value((value)) {}

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    constexpr explicit Int32(T value) noexcept requires(is_promotion_wrapper<T>::value) : Value((value)) {}

    Int32(Int32 const &) = default;

    Int32(Int32 &&) = default;

    Int32 &operator=(Int32 const &) = default;

    Int32 &operator=(Int32 &&) = default;

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    constexpr Int32 operator=(T value) noexcept requires(is_promotion_primitive<T>::value) { return Value = value; };

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    constexpr Int32 operator=(T value) noexcept requires(is_promotion_wrapper<T>::value) { return Value = value; };

    template<typename T, std::enable_if_t<is_promotion_primitive<T>::value, bool> = true>
    constexpr operator T() noexcept requires(is_promotion_primitive<T>::value) { return Value; };

    template<typename T, std::enable_if_t<is_promotion_wrapper<T>::value, bool> = true>
    constexpr operator T() noexcept requires(is_promotion_wrapper<T>::value) { return Value; };
};

#endif //CPPDATASTRUCTURES_INT32_H
