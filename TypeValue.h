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

/*
 * FORWARD DECLARATION OF ALL WRAPPERS
 *
 * This is more than necessary since all wrappers are including  he TypeValue.h
 * So they must be forwarded declared before to handle their implementations
 * on their respective headers
*/
class Boolean;
class Byte;
class Char;
class Int16;
class Int32;
class Int64;
class Double;
class Float;
class SByte;
class UInt16;
class UInt32;
class UInt64;

template<typename T>
struct is_promotion_wrapper : std::false_type {};

template<>
struct is_promotion_wrapper<Boolean> : std::true_type {};

template<>
struct is_promotion_wrapper<Byte> : std::true_type {};

template<>
struct is_promotion_wrapper<Char> : std::true_type {};

template<>
struct is_promotion_wrapper<Int16> : std::true_type {};

template<>
struct is_promotion_wrapper<Int32> : std::true_type {};

template<>
struct is_promotion_wrapper<Int64> : std::true_type {};

template<>
struct is_promotion_wrapper<Double> : std::true_type {};

template<>
struct is_promotion_wrapper<Float> : std::true_type {};

template<>
struct is_promotion_wrapper<SByte> : std::true_type {};

template<>
struct is_promotion_wrapper<UInt16> : std::true_type {};

template<>
struct is_promotion_wrapper<UInt32> : std::true_type {};

template<>
struct is_promotion_wrapper<UInt64> : std::true_type {};

#endif //CPPDATASTRUCTURES_TYPEVALUE_H
