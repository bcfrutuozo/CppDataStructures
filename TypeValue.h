//
// Created by bcfrutuozo on 31/03/2022.
//

#ifndef CPPDATASTRUCTURES_TYPEVALUE_H
#define CPPDATASTRUCTURES_TYPEVALUE_H

#include <type_traits>
#include <iostream>

template<typename T>
struct is_promotion : std::false_type {
};
template<>
struct is_promotion<int> : std::true_type {
};
template<>
struct is_promotion<unsigned int> : std::true_type {
};
template<>
struct is_promotion<long> : std::true_type {
};
template<>
struct is_promotion<short> : std::true_type {
};
template<>
struct is_promotion<char> : std::true_type {
};
template<>
struct is_promotion<unsigned char> : std::true_type {
};
template<>
struct is_promotion<unsigned short> : std::true_type {
};
template<>
struct is_promotion<signed char> : std::true_type {
};
template<>
struct is_promotion<unsigned long> : std::true_type {
};
template<>
struct is_promotion<double> : std::true_type {
};
template<>
struct is_promotion<float> : std::true_type {
};
template<>
struct is_promotion<bool> : std::true_type {
};

class Char;
class Int32;

template<>
struct is_promotion<Char> : std::true_type {
};

template<>
struct is_promotion<Int32> : std::true_type {
};


#endif //CPPDATASTRUCTURES_TYPEVALUE_H
