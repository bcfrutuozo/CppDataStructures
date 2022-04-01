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

    template<typename U>
    constexpr Int32(U value) noexcept requires(is_promotion<U>::value) : Value(static_cast<U>(value)) {}

    template<typename U>
    constexpr operator U() const noexcept requires(is_promotion<U>::value) { return static_cast<U>(Value); }
};

#endif //CPPDATASTRUCTURES_INT32_H
