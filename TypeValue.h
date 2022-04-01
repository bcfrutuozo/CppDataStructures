//
// Created by bcfrutuozo on 31/03/2022.
//

#ifndef CPPDATASTRUCTURES_TYPEVALUE_H
#define CPPDATASTRUCTURES_TYPEVALUE_H

#include <type_traits>
#include <iostream>

template<typename T>
struct is_promotion_primitive : std::false_type {
};
template<>
struct is_promotion_primitive<int> : std::true_type {
};
template<>
struct is_promotion_primitive<unsigned int> : std::true_type {
};
template<>
struct is_promotion_primitive<long> : std::true_type {
};
template<>
struct is_promotion_primitive<short> : std::true_type {
};
template<>
struct is_promotion_primitive<char> : std::true_type {
};
template<>
struct is_promotion_primitive<unsigned char> : std::true_type {
};
template<>
struct is_promotion_primitive<unsigned short> : std::true_type {
};
template<>
struct is_promotion_primitive<signed char> : std::true_type {
};
template<>
struct is_promotion_primitive<unsigned long> : std::true_type {
};
template<>
struct is_promotion_primitive<double> : std::true_type {
};
template<>
struct is_promotion_primitive<float> : std::true_type {
};
template<>
struct is_promotion_primitive<bool> : std::true_type {
};

// Forward declaration of all wrappers
class Char;
class Int32;

template<typename T>
struct is_promotion_wrapper : std::false_type {};

template<>
struct is_promotion_wrapper<Char> : std::true_type {};
template<>
struct is_promotion_wrapper<Int32> : std::true_type {};

#endif //CPPDATASTRUCTURES_TYPEVALUE_H
