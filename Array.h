//
// Created by bcfrutuozo on 14/03/2022.
//

#ifndef CPPDATASTRUCTURES_ARRAY_H
#define CPPDATASTRUCTURES_ARRAY_H

#include "ForwardIterator.h"

#include <stdexcept>
#include <iostream>
#include <algorithm>

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
            ptr(new T[size]()),
            m_Size(size) {}

    constexpr Array(const T &defaultValue, size_t size)
            :
            ptr(new T[size]()),
            m_Size(size) {
        Fill(defaultValue);
    }

    constexpr Array(const Array &other)
            :
            m_Size(other.m_Size) {
        if (other.m_Size > 0) {
            m_Size = other.m_Size;
            ptr = new T[m_Size];
            std::copy(other.ptr, other.ptr + other.m_Size, ptr);
        } else {
            m_Size = 0;
            ptr = nullptr;
        }
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
        if (ptr != nullptr) {
            delete[] ptr;
            ptr = nullptr;
        }
    }

    // Using proxy class ArrayValue to handle this function as Getter/Setter
    constexpr ArrayValue operator[](size_t index) {
        if (index > m_Size - 1)
            throw std::out_of_range("index is too large for the resized array");

        return ArrayValue(ptr + index);
    }

    constexpr Array& operator=(const Array &other) {
        Array copied(other);
        Swap(copied);
        return *this;
    }

    bool operator==(const Array &other) const {
        if (m_Size != other.m_Size) return false;

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
        if(other.m_Size == 0) return;

        auto newSize = m_Size + other.m_Size;
        T* newArray = new T[newSize];
        if(m_Size == 0){
            std::copy(other.ptr, other.ptr + other.m_Size, newArray);
        } else {
            std::copy(ptr, ptr + m_Size, newArray);
            std::copy(other.ptr, other.ptr + other.m_Size, newArray + m_Size);
        }

        delete[] ptr;
        ptr = newArray;
        m_Size = newSize;
    }

    void AddAtIndex(const T &element, size_t index) {
        if (m_Size == 0 || index > m_Size - 1)
            throw std::out_of_range("Invalid array boundaries");

        if (m_Size == 0)
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

    void AddAtIndex(const Array &a, size_t index) {
        if (m_Size == 0 || index > m_Size - 1)
            throw std::out_of_range("Invalid array boundaries");

        if (m_Size == 0)
            Add(a);
        else {
            size_t newSize = m_Size + a.m_Size;
            T *newArray = new T[newSize];

            // Copy pre-block from start until the desired index
            std::copy(ptr, ptr + index, newArray);

            // Copy the following blocks until the end of the array
            std::copy(ptr + index, ptr + m_Size, newArray + index + a.m_Size);

            // Fill the desired index block with the new element
            std::copy(a.ptr, a.ptr + a.m_Size, newArray + index);

            delete[] ptr;
            ptr = newArray;
            m_Size = newSize;
        }
    }

    static void Copy(Array &sourceArray, Array &destinationArray) {
        if (sourceArray.m_Size > destinationArray.m_Size)
            destinationArray = sourceArray;
        else {
            for (auto itsource = sourceArray.begin(), itdestination = destinationArray.begin();
                 itsource != sourceArray.end(); ++itsource, ++itdestination) {
                *itdestination = *itsource;
            }
        }
    }

    static void Copy(Array& sourceArray, size_t sourceIndex, Array& destinationArray, size_t destinationIndex){
        if(sourceIndex > sourceArray.m_Size - 1 || destinationIndex > destinationArray.m_Size - 1)
            throw std::out_of_range("Specified index is out of array bounds");

        ssize_t copyAmount = sourceArray.m_Size - sourceIndex;
        ssize_t availableSpace = destinationArray.m_Size - destinationIndex;

        bool needExtraSpace = (copyAmount - availableSpace) > 0;
        if(needExtraSpace)
            Array::Resize(destinationArray, destinationArray.m_Size + (copyAmount - availableSpace));

        std::copy(sourceArray.ptr + sourceIndex, sourceArray.ptr + sourceIndex + copyAmount, destinationArray.ptr + destinationIndex);
    }

    size_t Count(const T &element) const {
        size_t total = 0;
        for (auto it = cbegin(); it != cend(); ++it)
            if (*it == element)
                ++total;
        return total;
    }

    bool Exists(const T &other) const {
        if (m_Size == 0) return false;

        for (auto it = cbegin(); it != cend(); ++it)
            if (*it == other)
                return true;

        return false;
    }

    void Fill(const T &element) {
        for (auto it = begin(); it != end(); ++it)
            *it = element;
    }

    constexpr T &GetBack() const {
        if (m_Size == 0)
            throw std::out_of_range("The array is empty");

        return *(ptr + m_Size - 1);
    }

    constexpr T &GetFront() const {
        if (m_Size == 0)
            throw std::out_of_range("The array is empty");

        return *ptr;
    }

    inline constexpr size_t GetLength() const { return m_Size; }

    size_t IndexOf(const T &element) const {
        for (auto it = cbegin(); it != cend(); ++it)
            if (*it == element)
                return std::distance(cbegin(), it);

        throw std::out_of_range("The array doesn't have the provided argument in it");
    }

    Array<size_t> IndicesOf(const T &element) const {
        size_t count = Count(element);
        Array<size_t> a(count);

        for (size_t i = 0, j = 0; i < m_Size; ++i) {
            if (*(ptr + i) == element) {
                a[j] = i;
                ++j;

                if (j == count) break;
            }
        }

        return a;
    }

    inline constexpr bool IsEmpty() const { return m_Size == 0; }

    inline constexpr ssize_t LastIndex() const { return m_Size - 1; }

    size_t LastIndexOf(const T &element) const {
        for (auto it = crbegin(); it != crend(); ++it)
            if (*it == element)
                return (m_Size - 1) - std::distance(crbegin(), it);

        throw std::out_of_range("The array doesn't have the provided argument in it");
    }

    [[nodiscard]] T RemoveAt(size_t index) {
        if (m_Size == 0 || index > m_Size - 1)
            throw std::out_of_range("index is too large for the resized array");

        size_t newSize = m_Size - 1;
        T *newArray = nullptr;
        T obj = *(ptr + index);

        if (newSize > 0) {
            newArray = new T[newSize];
            if (index == 0) {
                std::copy(ptr + 1, ptr + m_Size, newArray);
            } else if (index == m_Size - 1) {
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
        if (m_Size == 0)
            throw std::out_of_range("Cannot remove element from an empty array");

        size_t newSize = m_Size - 1;
        T *newArray = nullptr;
        T obj = *(ptr + newSize);

        if (newSize > 0) {
            newArray = new T[newSize];
            std::copy(ptr, ptr + m_Size - 1, newArray);
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

    static void Resize(Array &a, size_t newSize) {
        if (newSize == a.m_Size) return;

        T *newArray = nullptr;

        if (newSize > 0) {
            newArray = new T[newSize];
            if (newSize > a.m_Size) {
                // Create a default object to fill the new spaces
                T def{0};

                if (a.GetLength() > 0) {
                    std::copy(a.ptr, a.ptr + a.m_Size, newArray);
                    for (size_t i = a.m_Size; i < newSize; ++i)
                        newArray[i] = def;
                } else {
                    for (size_t i = 0; i < newSize; ++i)
                        newArray[i] = def;
                }
            } else
                std::copy(a.ptr, a.ptr + newSize, newArray);
        }

        delete[] a.ptr;
        a.ptr = newArray;
        a.m_Size = newSize;
    }

    void Reverse() {
        for (auto itb = begin(), ite = rbegin(); &(*itb) < &(*ite); ++itb, ++ite) {
            auto tmp = *ite;
            *ite = *itb;
            *itb = tmp;
        }
    }

    void Swap(Array& other){
        using std::swap;

        swap(ptr, other.ptr);
        swap(m_Size, other.m_Size);
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

#endif //CPPDATASTRUCTURES_ARRAY_H
