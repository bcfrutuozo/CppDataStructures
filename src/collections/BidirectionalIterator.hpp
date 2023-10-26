//
// Created by bcfrutuozo on 19/03/2022.
//

#ifndef CPPDATASTRUCTURES_BIDIRECTIONALITERATOR_HPP
#define CPPDATASTRUCTURES_BIDIRECTIONALITERATOR_HPP

#include <iterator>

template<typename T>
class BidirectionalIterator {
public:

    // Aliases to handle const and non-const iterators
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T *;  // or also value_type*
    using reference = T &;  // or also value_type&

    // Pointer field representation
    pointer pElement = nullptr;

    constexpr BidirectionalIterator(pointer ptr) noexcept
            :
            pElement(ptr) {
    }

    constexpr reference operator*() const { return *pElement; }

    constexpr pointer operator->() const { return pElement; }

    // Prefix increment
    virtual constexpr BidirectionalIterator &operator++() = 0;

    // Prefix decrement
    virtual constexpr BidirectionalIterator &operator--() = 0;

    // Postfix operations are not supported in abstract classes
    // Check the details in the ForwardIterator.h
    //virtual constexpr BidirectionalIterator operator++(int) = 0;
    //virtual constexpr BidirectionalIterator operator--(int) = 0;

    constexpr friend bool operator==(const BidirectionalIterator &a, const BidirectionalIterator &b) {
        return a.pElement == b.pElement;
    };

    constexpr friend bool operator!=(const BidirectionalIterator &a, const BidirectionalIterator &b) {
        return a.pElement != b.pElement;
    };
};

#endif //CPPDATASTRUCTURES_BIDIRECTIONALITERATOR_HPP
