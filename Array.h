//
// Created by bcfrutuozo on 14/03/2022.
//

#ifndef CPPDATASTRUCTURES_ARRAY_H
#define CPPDATASTRUCTURES_ARRAY_H

#include "ForwardIterator.h"

#include <stdexcept>
#include <algorithm>

template<typename T>
class Array {

private:

    T *pData;
    size_t Size;

    //<editor-fold desc="Proxy to handle operator[] as Getter/Setter">
    class ArrayValue {
    private:

        T *value;

    public:

        constexpr explicit ArrayValue(T *value) noexcept
                :
                value(value) {}

        constexpr operator T() const noexcept { return *value; }

        constexpr void operator=(const T &val) noexcept { *value = val; }
    };
    //</editor-fold>

    //<editor-fold desc="Iterators implementation">
    struct Iterator : ForwardIterator<T> {

        constexpr Iterator(T *ptr) noexcept: ForwardIterator<T>(ptr) {}

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

        constexpr ConstIterator(const T *ptr) noexcept: ForwardIterator<const T>(ptr) {}

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

        constexpr ReverseIterator(T *ptr) noexcept: ForwardIterator<T>(ptr) {}

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

        constexpr ConstReverseIterator(const T *ptr) noexcept: ForwardIterator<const T>(ptr) {}

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

    constexpr Array() noexcept
            :
            pData(nullptr),
            Size(0) {}

    constexpr explicit Array(size_t size) noexcept
            :
            pData(new T[size]()),
            Size(size) {}

    constexpr Array(const T &defaultValue, size_t size) noexcept
            :
            pData(new T[size]()),
            Size(size) {
        Fill(defaultValue);
    }

    constexpr Array(const Array &other) noexcept
            :
            Size(other.Size) {
        if (other.Size > 0) {
            Size = other.Size;
            pData = new T[Size];
            std::copy(other.pData, other.pData + other.Size, pData);
        } else {
            Size = 0;
            pData = nullptr;
        }
    }

    Array(std::initializer_list<T> l) noexcept {
        if (empty(l)) {
            pData = nullptr;
            Size = 0;
        } else {
            Size = l.size();
            pData = new T[Size];
            for (auto it = begin(), itl = l.begin(); it != end(); ++it, ++itl)
                *it = *itl;
        }
    }

    ~Array() noexcept {
        if (pData != nullptr) {
            delete[] pData;
            pData = nullptr;
        }
    }

    // Using proxy class ArrayValue to handle this function as Getter/Setter
    constexpr ArrayValue operator[](size_t index) {
        if ((ssize_t) index > LastIndex())
            throw std::out_of_range("index is too large for the resized array");

        return ArrayValue(pData + index);
    }

    constexpr Array &operator=(const Array &other) noexcept {
        Array copied(other);
        Swap(copied);
        return *this;
    }

    bool operator==(const Array &other) const noexcept {
        if (Size != other.Size) return false;

        for (auto itself = cbegin(), itother = other.cbegin(); itself != cend(); ++itself, ++itother)
            if (*itself != *itother)
                return false;

        return true;
    }

    bool operator!=(const Array &other) const noexcept {
        return !(*this == other);
    }

    void Add(const T &element) noexcept {
        size_t newSize = Size + 1;
        auto *newArray = new T[newSize];
        std::copy(pData, pData + Size, newArray);

        delete[] pData;
        pData = newArray;
        Size = newSize;

        pData[LastIndex()] = element;
    }

    void Add(const Array<T> &other) noexcept {
        if (other.IsEmpty()) return;

        auto newSize = Size + other.Size;
        T *newArray = new T[newSize];
        if (Size == 0) {
            std::copy(other.pData, other.pData + other.Size, newArray);
        } else {
            std::copy(pData, pData + Size, newArray);
            std::copy(other.pData, other.pData + other.Size, newArray + Size);
        }

        delete[] pData;
        pData = newArray;
        Size = newSize;
    }

    void AddAtIndex(const T &element, size_t index) {

        if (GetLength() == 0 && index == 0) Add(element);

        if ((ssize_t) index > LastIndex())
            throw std::out_of_range("Invalid array boundaries");

        size_t newSize = Size + 1;
        T *newArray = new T[newSize];

        // Copy preblock from start until the desired index
        std::copy(pData, pData + index, newArray);

        // Copy the following blocks until the end of the array
        std::copy(pData + index, pData + Size, newArray + index + 1);

        // Fill the desired index block with the new element
        *(newArray + index) = element;

        delete[] pData;
        pData = newArray;
        Size = newSize;

    }

    void AddAtIndex(const Array &a, size_t index) {
        if ((ssize_t) index > LastIndex())
            throw std::out_of_range("Invalid array boundaries");

        if (IsEmpty())
            Add(a);
        else {
            size_t newSize = Size + a.Size;
            T *newArray = new T[newSize];

            // Copy pre-block from start until the desired index
            std::copy(pData, pData + index, newArray);

            // Copy the following blocks until the end of the array
            std::copy(pData + index, pData + Size, newArray + index + a.Size);

            // Fill the desired index block with the new element
            std::copy(a.pData, a.pData + a.Size, newArray + index);

            delete[] pData;
            pData = newArray;
            Size = newSize;
        }
    }

    static void Copy(Array &sourceArray, Array &destinationArray) noexcept {
        if (sourceArray.Size > destinationArray.Size)
            destinationArray = sourceArray;
        else {
            for (auto itsource = sourceArray.begin(), itdestination = destinationArray.begin();
                 itsource != sourceArray.end(); ++itsource, ++itdestination) {
                *itdestination = *itsource;
            }
        }
    }

    static void Copy(Array &sourceArray, size_t sourceIndex, Array &destinationArray, size_t destinationIndex) {
        if (sourceIndex > sourceArray.LastIndex() || destinationIndex > destinationArray.LastIndex())
            throw std::out_of_range("Specified index is out of array bounds");

        ssize_t copyAmount = sourceArray.Size - sourceIndex;
        ssize_t availableSpace = destinationArray.Size - destinationIndex;

        bool needExtraSpace = (copyAmount - availableSpace) > 0;
        if (needExtraSpace)
            Array::Resize(destinationArray, destinationArray.Size + (copyAmount - availableSpace));

        std::copy(sourceArray.pData + sourceIndex, sourceArray.pData + sourceIndex + copyAmount,
                  destinationArray.pData + destinationIndex);
    }

    size_t Count(const T &element) const noexcept {
        size_t total = 0;
        for (auto it = cbegin(); it != cend(); ++it)
            if (*it == element)
                ++total;
        return total;
    }

    bool Exists(const T &other) const noexcept {
        if (IsEmpty()) return false;

        for (auto it = cbegin(); it != cend(); ++it)
            if (*it == other)
                return true;

        return false;
    }

    void Fill(const T &element) noexcept {
        for (auto it = begin(); it != end(); ++it)
            *it = element;
    }

    constexpr T &GetBack() const {
        if (IsEmpty())
            throw std::out_of_range("The array is empty");

        return *(pData + LastIndex());
    }

    constexpr T &GetFront() const {
        if (IsEmpty())
            throw std::out_of_range("The array is empty");

        return *pData;
    }

    inline constexpr size_t GetLength() const noexcept { return Size; }

    size_t IndexOf(const T &element) const {
        for (auto it = cbegin(); it != cend(); ++it)
            if (*it == element)
                return std::distance(cbegin(), it);

        throw std::out_of_range("The array doesn't have the provided argument in it");
    }

    Array<size_t> IndicesOf(const T &element) const noexcept {
        size_t count = Count(element);
        Array<size_t> a(count);

        for (size_t i = 0, j = 0; i < Size; ++i) {
            if (*(pData + i) == element) {
                a[j] = i;
                ++j;

                if (j == count) break;
            }
        }

        return a;
    }

    inline constexpr bool IsEmpty() const noexcept { return Size == 0; }

    inline constexpr ssize_t LastIndex() const noexcept { return Size - 1; }

    size_t LastIndexOf(const T &element) const {
        for (auto it = crbegin(); it != crend(); ++it)
            if (*it == element)
                return LastIndex() - std::distance(crbegin(), it);

        throw std::out_of_range("The array doesn't have the provided argument in it");
    }

    [[nodiscard]] T RemoveAt(size_t index) {
        if (IsEmpty() || (ssize_t) index > LastIndex())
            throw std::out_of_range("index is too large for the resized array");

        size_t newSize = Size - 1;
        T *newArray = nullptr;
        T obj = *(pData + index);

        if (newSize > 0) {
            newArray = new T[newSize];
            if (index == 0) {
                std::copy(pData + 1, pData + Size, newArray);
            } else if (index == LastIndex()) {
                std::copy(pData, pData + index, newArray);
            } else {
                std::copy(pData, pData + index, newArray);
                std::copy(pData + index + 1, pData + Size, newArray + index);
            }
        }

        delete[] pData;
        pData = newArray;
        Size = newSize;

        return obj;
    }

    [[nodiscard]] T RemoveBack() {
        if (IsEmpty())
            throw std::out_of_range("Cannot remove element from an empty array");

        size_t newSize = Size - 1;
        T *newArray = nullptr;
        T obj = *(pData + newSize);

        if (newSize > 0) {
            newArray = new T[newSize];
            std::copy(pData, pData + Size - 1, newArray);
        }

        delete[] pData;
        pData = newArray;
        Size = newSize;

        return obj;
    }

    [[nodiscard]] T RemoveFront() {
        if (IsEmpty())
            throw std::out_of_range("Cannot remove element from an empty array");

        size_t newSize = Size - 1;
        T *newArray = nullptr;

        T obj = *pData;

        if (newSize > 0) {
            newArray = new T[newSize];
            std::copy(pData + 1, pData + Size, newArray);
        }

        delete[] pData;
        pData = newArray;
        Size = newSize;

        return obj;
    }

    static void Resize(Array &a, size_t newSize) noexcept {
        if (newSize == a.Size) return;

        T *newArray = nullptr;

        if (newSize > 0) {
            newArray = new T[newSize];
            if (newSize > a.Size) {
                // Create a default object to fill the new spaces
                T def{0};

                if (a.GetLength() > 0) {
                    std::copy(a.pData, a.pData + a.Size, newArray);
                    for (size_t i = a.Size; i < newSize; ++i)
                        newArray[i] = def;
                } else {
                    for (size_t i = 0; i < newSize; ++i)
                        newArray[i] = def;
                }
            } else
                std::copy(a.pData, a.pData + newSize, newArray);
        }

        delete[] a.pData;
        a.pData = newArray;
        a.Size = newSize;
    }

    void Reverse() noexcept {
        for (auto itb = begin(), ite = rbegin(); &(*itb) < &(*ite); ++itb, ++ite) {
            auto tmp = *ite;
            *ite = *itb;
            *itb = tmp;
        }
    }

    void Swap(Array &other) noexcept {
        using std::swap;

        swap(pData, other.pData);
        swap(Size, other.Size);
    }

    constexpr Iterator begin() noexcept { return pData; }

    constexpr Iterator end() noexcept { return pData + Size; }

    constexpr ConstIterator cbegin() const noexcept { return pData; }

    constexpr ConstIterator cend() const noexcept { return pData + Size; }

    constexpr ReverseIterator rbegin() noexcept { return pData + LastIndex(); }

    constexpr ReverseIterator rend() noexcept { return pData - 1; }

    constexpr ConstReverseIterator crbegin() const noexcept { return pData + LastIndex(); }

    constexpr ConstReverseIterator crend() const noexcept { return pData - 1; }
};

#endif //CPPDATASTRUCTURES_ARRAY_H
