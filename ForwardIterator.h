//
// Created by bcfrutuozo on 16/03/2022.
//

#ifndef LNXCPPLEARNING_FORWARDITERATOR_H
#define LNXCPPLEARNING_FORWARDITERATOR_H

#include <iterator>

template<typename T>
class ForwardIterator {
public:

    // Aliases to handle const and non-const iterators
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T *;  // or also value_type*
    using reference = T &;  // or also value_type&

    // Pointer field representation
    pointer pElement = nullptr;

    constexpr ForwardIterator(pointer ptr)
            :
            pElement(ptr) {
    }

    constexpr reference operator*() const { return *pElement; }

    constexpr pointer operator->() const { return pElement; }

    // Prefix increment
    virtual constexpr ForwardIterator &operator++() = 0;

    /* Postfix increment cannot be created in an abstract class
     * So we manually implement it in each one of the children
     * There's a workaround for it which is pretty complicated and would force to allocate the iterators
     * ON THE HEAP! (MEHHHHHHHHHHHHHHHHHHHHHHH) WHY SHOULD ANYONE DO THIS?!?!?!
     * Link to the implementation: https://stackoverflow.com/questions/63160628/how-to-declare-operatorint-in-an-abstract-class
    */
    //virtual constexpr ForwardIterator& operator++(int) = 0;

    constexpr friend bool operator==(const ForwardIterator &a, const ForwardIterator &b) {
        return a.pElement == b.pElement;
    };

    constexpr friend bool operator!=(const ForwardIterator &a, const ForwardIterator &b) {
        return a.pElement != b.pElement;
    };
};

#endif //LNXCPPLEARNING_FORWARDITERATOR_H
