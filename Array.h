//
// Created by bcfrutuozo on 14/03/2022.
//

#ifndef LNXCPPLEARNING_ARRAY_H
#define LNXCPPLEARNING_ARRAY_H

#include "ForwardIterator.h"

#include <stdexcept>
#include <iostream>

template<typename T>
class Array {

private:

    T *ptr;
    size_t m_Size;

    //<editor-fold desc="Proxy to handle operator[] as Getter/Setter">
    class ArrayValue {
    private:

        T *value;

    public:

        constexpr explicit ArrayValue(T *value)
                :
                value(value) {}

        constexpr operator T() const { return *value; }

        constexpr void operator=(const T &val) { *value = val; }
    };
    //</editor-fold>

    //<editor-fold desc="Iterators implementation">
    struct Iterator : ForwardIterator<T> {

        constexpr Iterator(T *ptr) : ForwardIterator<T>(ptr) {}

        // Prefix increment
        constexpr Iterator &operator++() override {
            this->pElement++;
            return *this;
        }

        // Postfix increment
        constexpr Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }
    };

    struct ConstIterator : ForwardIterator<const T> {

        constexpr ConstIterator(const T *ptr) : ForwardIterator<const T>(ptr) {}

        // Prefix increment
        constexpr ConstIterator &operator++() override {
            this->pElement++;
            return *this;
        }

        // Postfix increment
        constexpr ConstIterator operator++(int) {
            ConstIterator tmp = *this;
            ++(*this);
            return tmp;
        }
    };

    struct ReverseIterator : ForwardIterator<T> {

        constexpr ReverseIterator(T *ptr) : ForwardIterator<T>(ptr) {}

        // Prefix increment
        constexpr ReverseIterator &operator++() override {
            this->pElement--;
            return *this;
        }

        // Postfix increment
        constexpr ReverseIterator operator++(int) {
            ReverseIterator tmp = *this;
            --(*this);
            return tmp;
        }
    };

    struct ConstReverseIterator : ForwardIterator<const T> {

        constexpr ConstReverseIterator(const T *ptr) : ForwardIterator<const T>(ptr) {}

        // Prefix increment
        constexpr ConstReverseIterator &operator++() override {
            this->pElement--;
            return *this;
        }

        // Postfix increment
        constexpr ConstReverseIterator operator++(int) {
            ConstReverseIterator tmp = *this;
            --(*this);
            return tmp;
        }
    };
    //</editor-fold>

public:

    constexpr Array()
            :
            ptr(nullptr),
            m_Size(0) {}

    constexpr explicit Array(size_t size)
            :
            ptr(new T[size]),
            m_Size(size) {}

    constexpr Array(const T &defaultValue, size_t size)
            :
            ptr(new T[size]),
            m_Size(size) {
        Fill(defaultValue);
    }

    Array(std::initializer_list<T> l) {
        if (empty(l)) {
            ptr = nullptr;
            m_Size = 0;
        } else {
            m_Size = l.size();
            ptr = new T[m_Size];
            for (auto it = begin(), itl = l.begin(); it != end(); ++it, ++itl)
                *it = *itl;
        }
    }

    ~Array() {
        delete[] ptr;
    }

    // Using proxy class ArrayValue to handle this function as Getter/Setter
    constexpr ArrayValue operator[](size_t index) {
        if (index > LastIndex())
            throw std::out_of_range("index is too large for the resized array");

        return ArrayValue(ptr + index);
    }

    bool operator==(const Array &other) const {
        if (m_Size != other.GetSize()) return false;

        for (auto itself = cbegin(), itother = other.cbegin(); itself != cend(); ++itself, ++itother)
            if (*itself != *itother)
                return false;

        return true;
    }

    bool operator!=(const Array &other) const {
        return !(*this == other);
    }

    friend std::ostream &operator<<(std::ostream &os, const Array &a) {
        for (auto it = a.cbegin(); it != a.cend(); ++it)
            os << *it;
        return os;
    }

    void Add(const T &element) {
        size_t newSize = m_Size + 1;
        auto *newArray = new T[newSize];
        std::copy(ptr, ptr + m_Size, newArray);

        delete[] ptr;
        ptr = newArray;
        m_Size = newSize;

        ptr[m_Size - 1] = element;
    }

    void Add(const Array<T> &other) {
        for (auto it = other.cbegin(); it != other.cend(); ++it)
            Add(*it);
    }

    void AddAtIndex(const T &element, size_t index) {
        if(index > LastIndex())
            throw std::out_of_range("Invalid array boundaries");

        if (IsEmpty())
            Add(element);
        else {
            size_t newSize = m_Size + 1;
            T *newArray = new T[newSize];

            // Copy preblock from start until the desired index
            std::copy(ptr, ptr + index, newArray);

            // Copy the following blocks until the end of the array
            std::copy(ptr + index, ptr + m_Size, newArray + index + 1);

            // Fill the desired index block with the new element
            *(newArray + index) = element;

            delete[] ptr;
            ptr = newArray;
            m_Size = newSize;
        }
    }

    void AddAtIndex(const Array& a, size_t index) {
        if(index > LastIndex())
            throw std::out_of_range("Invalid array boundaries");

        if (IsEmpty())
            Add(a);
        else {
            size_t newSize = m_Size + a.GetSize();
            T *newArray = new T[newSize];

            // Copy pre-block from start until the desired index
            std::copy(ptr, ptr + index, newArray);

            // Copy the following blocks until the end of the array
            std::copy(ptr + index, ptr + m_Size, newArray + index + a.GetSize());

            // Fill the desired index block with the new element
            std::copy(a.ptr, a.ptr + a.m_Size, newArray + index);

            delete[] ptr;
            ptr = newArray;
            m_Size = newSize;
        }
    }

    bool Contains(const T &other) const {
        if (IsEmpty()) return false;

        for (auto it = cbegin(); it != cend(); ++it)
            if (*it == other)
                return true;

        return false;
    }

    size_t Count(const T &element) const {
        size_t total = 0;
        for (auto it = cbegin(); it != cend(); ++it)
            if (*it == element)
                ++total;
        return total;
    }

    void Fill(const T &element) {
        for (auto it = begin(); it != end(); ++it)
            *it = element;
    }

    constexpr T &GetAtIndex(size_t index) const {
        if (index > LastIndex())
            throw std::out_of_range("index is too large for the resized array");

        return *(ptr + index);
    }

    constexpr T &GetBack() const {
        if (IsEmpty())
            throw std::out_of_range("The array is empty");

        return *(ptr + m_Size - 1);
    }

    constexpr T &GetFront() const {
        if (IsEmpty())
            throw std::out_of_range("The array is empty");

        return *ptr;
    }

    inline constexpr size_t GetSize() const { return m_Size; }

    inline constexpr bool IsEmpty() const { return m_Size == 0; }

    inline constexpr ssize_t LastIndex() const { return m_Size - 1; }

    [[nodiscard]] T RemoveAt(size_t index) {
        if (index > LastIndex())
            throw std::out_of_range("index is too large for the resized array");

        size_t newSize = m_Size - 1;
        T *newArray = nullptr;
        T obj = *(ptr + index);

        if (newSize > 0) {
            newArray = new T[newSize];
            if (index == 0) {
                std::copy(ptr + 1, ptr + m_Size, newArray);
            } else if (index == LastIndex()) {
                std::copy(ptr, ptr + index, newArray);
            } else {
                std::copy(ptr, ptr + index, newArray);
                std::copy(ptr + index + 1, ptr + m_Size, newArray + index);
            }
        }

        delete[] ptr;
        ptr = newArray;
        m_Size = newSize;

        return obj;
    }

    [[nodiscard]] T RemoveBack() {
        if (IsEmpty())
            throw std::out_of_range("Cannot remove element from an empty array");

        size_t newSize = m_Size - 1;
        T *newArray = nullptr;
        T obj = *(ptr + newSize);

        if (newSize > 0) {
            newArray = new T[newSize];
            std::copy(ptr, ptr + LastIndex(), newArray);
        }

        delete[] ptr;
        ptr = newArray;
        m_Size = newSize;

        return obj;
    }

    [[nodiscard]] T RemoveFront() {
        if (m_Size == 0)
            throw std::out_of_range("Cannot remove element from an empty array");

        size_t newSize = m_Size - 1;
        T *newArray = nullptr;

        T obj = *ptr;

        if (newSize > 0) {
            newArray = new T[newSize];
            std::copy(ptr + 1, ptr + m_Size, newArray);
        }

        delete[] ptr;
        ptr = newArray;
        m_Size = newSize;

        return obj;
    }

    void Reverse() {
        for (auto itb = begin(), ite = rbegin(); &(*itb) < &(*ite); ++itb, ++ite) {
            auto tmp = *ite;
            *ite = *itb;
            *itb = tmp;
        }
    }

    Array<size_t> WhereAreAll(const T &element) const {
        size_t count = Count(element);
        Array<size_t> a(count);

        for (size_t i = 0, j = 0; i < GetSize(); ++i) {
            if (*(ptr + i) == element) {
                a[j] = i;
                ++j;

                if (j == count) break;
            }
        }

        return a;
    }

    size_t WhereIsFirstElement(const T &element) const {
        for (auto it = cbegin(); it != cend(); ++it)
            if (*it == element)
                return std::distance(cbegin(), it);

        throw std::out_of_range("The array doesn't have the provided argument in it");
    }

    size_t WhereIsLastElement(const T &element) const {
        for (auto it = crbegin(); it != crend(); ++it)
            if (*it == element)
                return LastIndex() - std::distance(crbegin(), it);

        throw std::out_of_range("The array doesn't have the provided argument in it");
    }

    constexpr Iterator begin() { return ptr; }

    constexpr Iterator end() { return ptr + m_Size; }

    constexpr ConstIterator cbegin() const { return ptr; }

    constexpr ConstIterator cend() const { return ptr + m_Size; }

    constexpr ReverseIterator rbegin() { return ptr + m_Size - 1; }

    constexpr ReverseIterator rend() { return ptr - 1; }

    constexpr ConstReverseIterator crbegin() const { return ptr + m_Size - 1; }

    constexpr ConstReverseIterator crend() const { return ptr - 1; }
};

#endif //LNXCPPLEARNING_ARRAY_H
