//
// Created by bcfrutuozo on 14/03/2022.
//

#ifndef CPPDATASTRUCTURES_ARRAY_HPP
#define CPPDATASTRUCTURES_ARRAY_HPP

#include "../Platform.hpp"

#include <stdexcept>
#include <algorithm>
#include <type_traits>
#include <atomic>
#include <ranges>

template<typename T>
class Array {

private:

    // Declarations
    using pointer = T*;
    using size_type = size_t;
    using value_type = T;
    using reference = value_type &;
    using const_reference = const value_type&;
    using const_pointer = const value_type*;
    using const_iterator = const_pointer;
    using iterator = pointer;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using reverse_iterator = std::reverse_iterator<iterator>;

    pointer Data;
    size_type Size;

public:

    constexpr Array() noexcept
            :
            Data(nullptr),
            Size(0) {}

    constexpr explicit Array(size_type size) noexcept
            :
            Data(new value_type[size]),
            Size(size) {}

    constexpr Array(const_reference defaultValue, size_type size) noexcept
            :
            Data(new value_type[size]),
            Size(size) {
        Fill(defaultValue);
    }

    constexpr Array(const Array &other) noexcept
            :
            Data(nullptr),
            Size(other.Size) {
        if (other.Size == 0) return;

        Data = new value_type[Size];
        std::copy(other.Data, other.Data + other.Size, Data);
    }

    constexpr Array(Array &&other) noexcept:
            Data(std::move(other.Data)),
            Size(std::move(other.Size)) {
        other.Data = nullptr;
        other.Size = size_type();
    }

    constexpr Array(std::initializer_list<value_type> l) noexcept
            :
            Data(nullptr),
            Size(l.size()) {
        if (empty(l)) return;

        Data = new value_type[Size];
        auto it = begin();
        auto itl = l.begin();
        for (; it != end(); ++it, ++itl)
            *it = *itl;
    }

    template<typename It,
            std::enable_if_t<std::is_base_of_v<typename std::iterator_traits<It>::iterator_category,
                    std::random_access_iterator_tag>, bool> = true>
    constexpr Array(It begin, It end) noexcept
            :
            Size(std::distance(begin, end)) {
        // Use this approach to accept sequential and fragmented data structures in memory.
        Data = new value_type[Size];
        for (auto i = 0; begin != end; ++begin, ++i) {
            Data[i] = *begin;
        }
    }

    constexpr ~Array() noexcept {
        if (Data != nullptr) {
            delete[] Data;
            Data = nullptr;
        }
    }

    // Using proxy class ArrayValue to handle this function as Getter/Setter
    constexpr reference operator[](size_type index) {
        if (index >= Size) throw std::out_of_range("index is too large for the resized array");
        return Data[index];
    }

    constexpr Array &operator=(const Array &other) noexcept {
        Array copied(other);
        Swap(copied);
        return *this;
    }

    constexpr Array &operator=(Array &&other) noexcept {
        // Self-assignment detection
        if (&other == this) return *this;

        delete[] Data;
        Data = other.Data;
        Size = other.Size;

        other.Data = nullptr;
        other.Size = 0;

        return *this;
    }

    constexpr bool operator==(const Array &other) const noexcept {
        if (Size != other.Size) return false;

        for (auto itself = cbegin(), itother = other.cbegin(); itself != cend(); ++itself, ++itother)
            if (!Equals(*itself, *itother)) return false;

        return true;
    }

    inline constexpr bool operator!=(const Array &other) const noexcept {
        return !(*this == other);
    }

    constexpr void Add(const_reference element) noexcept {
        size_type newSize = Size + 1;
        auto newArray = new value_type[newSize];
        std::copy(Data, Data + Size, newArray);

        delete[] Data;
        Data = newArray;
        Data[Size] = element;
        Size = newSize;
    }

    constexpr void Add(const Array<value_type> &other) noexcept {
        if (other.IsEmpty()) return;

        auto newSize = Size + other.Size;
        auto newArray = new value_type[newSize];
        if (Size == 0) {
            std::copy(other.Data, other.Data + other.Size, newArray);
        } else {
            std::copy(Data, Data + Size, newArray);
            std::copy(other.Data, other.Data + other.Size, newArray + Size);
        }

        delete[] Data;
        Data = newArray;
        Size = newSize;
    }

    constexpr void AddAtIndex(const_reference element, size_type index) {
        if (GetLength() == 0 && index == 0) {
            Add(element);
            return;
        }

        if (index >= Size)
            throw std::out_of_range("Invalid array boundaries");

        size_type newSize = Size + 1;
        auto newArray = new value_type[newSize];

        // Copy pre-block from start until the desired index
        std::copy(Data, Data + index, newArray);

        // Copy the following blocks until the end of the array
        std::copy(Data + index, Data + Size, newArray + index + 1);

        // Fill the desired index block with the new element
        newArray[index] = element;

        delete[] Data;
        Data = newArray;
        Size = newSize;

    }

    constexpr void AddAtIndex(const Array &a, size_type index) {
        if (index >= Size)
            throw std::out_of_range("Invalid array boundaries");

        if (IsEmpty())
            Add(a);
        else {
            size_type newSize = Size + a.Size;
            auto newArray = new value_type[newSize];

            // Copy pre-block from start until the desired index
            std::copy(Data, Data + index, newArray);

            // Copy the following blocks until the end of the array
            std::copy(Data + index, Data + Size, newArray + index + a.Size);

            // Fill the desired index block with the new element
            std::copy(a.Data, a.Data + a.Size, newArray + index);

            delete[] Data;
            Data = newArray;
            Size = newSize;
        }
    }

    constexpr void Clear() noexcept {
        // Create a default object to fill the new spaces
        value_type def{0};
        for (auto i = 0; i < Size; ++i) { Data[i] = def; }
    }

    static constexpr void Clear(Array &a, size_type index, size_type length) {
        // Create a default object to fill the new spaces
        value_type def{0};
        auto maxOffset = index + length;
        if (maxOffset > a.GetLength())
            throw std::invalid_argument("Index and length combination goes outside of Array");
        for (; index < maxOffset; ++index) a.Data[index] = def;
    }

    constexpr bool Contains(const_reference other) const noexcept {
        if (IsEmpty()) return false;

        for (auto it = cbegin(); it != cend(); ++it)
            if (Equals(*it, other)) return true;

        return false;
    }

    static constexpr void
    Copy(Array &sourceArray, size_type sourceIndex, Array &destinationArray, size_type destinationIndex) {
        if (sourceIndex >= sourceArray.GetLength() || destinationIndex >= destinationArray.GetLength())
            throw std::out_of_range("Specified index is out of array bounds");

        ssize_t copyAmount = sourceArray.Size - sourceIndex;
        ssize_t availableSpace = destinationArray.Size - destinationIndex;

        bool needExtraSpace = (copyAmount - availableSpace) > 0;
        if (needExtraSpace)
            Array::Resize(destinationArray, destinationArray.Size + (copyAmount - availableSpace));

        std::copy(sourceArray.Data + sourceIndex, sourceArray.Data + sourceIndex + copyAmount,
                  destinationArray.Data + destinationIndex);
    }

    constexpr size_type Count(const_reference element) const noexcept {
        size_type total = 0;
        for (auto it = cbegin(); it != cend(); ++it)
            if (Equals(*it, element)) ++total;
        return total;
    }

    static constexpr void Copy(const Array &sourceArray, Array &destinationArray) noexcept {
        if (sourceArray.Size > destinationArray.Size)
            destinationArray = sourceArray;
        else {
            for (auto itsource = sourceArray.begin(), itdestination = destinationArray.begin();
                 itsource != sourceArray.end(); ++itsource, ++itdestination) {
                *itdestination = *itsource;
            }
        }
    }

    constexpr void Fill(const_reference element) noexcept {
        for (auto it = begin(); it != end(); ++it)
            *it = element;
    }

    constexpr const_reference GetBack() const {
        if (IsEmpty())
            throw std::out_of_range("The array is empty");

        return Data[Size - 1];
    }

    constexpr const_reference GetFront() const {
        if (IsEmpty())
            throw std::out_of_range("The array is empty");

        return Data[0];
    }

    inline constexpr size_type GetLastIndex() const {
        if (IsEmpty()) throw std::out_of_range("The array is empty");
        return Size - 1;
    }

    inline constexpr size_type GetLength() const noexcept { return Size; }

    constexpr size_type IndexOf(const_reference element) const {
        for (auto it = cbegin(); it != cend(); ++it)
            if (Equals(*it, element)) return std::distance(cbegin(), it);

        throw std::out_of_range("Element is not within array");;
    }

    constexpr Array<size_type> IndicesOf(const_reference element) const noexcept {
        size_type count = Count(element);
        Array<size_type> a(count);

        for (auto i = 0, j = 0; i < Size; ++i) {
            if (Equals(Data[i], element)) {
                a[j] = i;
                ++j;

                if (j == count) break;
            }
        }

        return a;
    }

    inline constexpr bool IsEmpty() const noexcept { return Size == 0; }

    constexpr size_type LastIndexOf(const_reference element) const {
        if(IsEmpty()) throw std::out_of_range("The array is empty");

        size_type i = GetLastIndex();

        while(true)
        {
            if(element == Data[i]) return i;
            if(i == 0) break;
            --i;
        }

        throw std::out_of_range("Element is not within the array");
    }

    [[nodiscard]] constexpr value_type RemoveAt(size_type index) {
        if (IsEmpty() || index >= Size)
            throw std::out_of_range("index is too large for the resized array");

        size_type newSize = Size - 1;
        pointer newArray = nullptr;
        value_type obj = Data[index];

        if (newSize > 0) {
            newArray = new value_type[newSize];
            if (index == 0) {
                std::copy(Data + 1, Data + Size, newArray);
            } else if (index == Size - 1) {
                std::copy(Data, Data + index, newArray);
            } else {
                std::copy(Data, Data + index, newArray);
                std::copy(Data + index + 1, Data + Size, newArray + index);
            }
        }

        delete[] Data;
        Data = newArray;
        Size = newSize;

        return obj;
    }

    [[nodiscard]] constexpr value_type RemoveBack() {
        if (IsEmpty())
            throw std::out_of_range("Cannot remove element from an empty array");

        size_type newSize = Size - 1;
        pointer newArray = nullptr;
        value_type obj = Data[newSize];

        if (newSize > 0) {
            newArray = new value_type[newSize];
            std::copy(Data, Data + Size - 1, newArray);
        }

        delete[] Data;
        Data = newArray;
        Size = newSize;

        return obj;
    }

    [[nodiscard]] constexpr value_type RemoveFront() {
        if (IsEmpty())
            throw std::out_of_range("Cannot remove element from an empty array");

        size_type newSize = Size - 1;
        pointer newArray = nullptr;
        value_type obj = Data[0];

        if (newSize > 0) {
            newArray = new value_type[newSize];
            std::copy(Data + 1, Data + Size, newArray);
        }

        delete[] Data;
        Data = newArray;
        Size = newSize;

        return obj;
    }

    static constexpr void Resize(Array &a, size_type newSize) noexcept {
        if (newSize == a.Size) return;

        pointer newArray = nullptr;

        if (newSize > 0) {
            newArray = new value_type[newSize];
            if (newSize > a.Size) {
                // Create a default object to fill the new spaces
                value_type def{0};

                if (a.GetLength() > 0) {
                    std::copy(a.Data, a.Data + a.Size, newArray);
                    for (auto i = a.Size; i < newSize; ++i)
                        newArray[i] = def;
                } else {
                    for (auto i = 0; i < newSize; ++i)
                        newArray[i] = def;
                }
            } else
                std::copy(a.Data, a.Data + newSize, newArray);
        }

        delete[] a.Data;
        a.Data = newArray;
        a.Size = newSize;
    }

    constexpr void Reverse() noexcept {

        /* Performed the declaration outside because we have two data types:
         * ConstReverseIterator and ConstIterator
         * In C++ it still not possible to declare two distinct types of variables
         * within the for loop.
         * It might recompile without it as we could use auto for it. However, it's
         * not a decent thing to do it so.
         */
        reverse_iterator ite = rbegin();
        iterator itb = begin();

        // We can compare the addresses between ite and itb because array always reallocates
        // itself to another block. So we can perform pointer comparison
        for (; &(*itb) < &(*ite); ++itb, ++ite) {
            value_type tmp = *ite;
            *ite = *itb;
            *itb = tmp;
        }
    }

    constexpr void Swap(Array &other) noexcept {
        using std::swap;

        swap(Data, other.Data);
        swap(Size, other.Size);
    }

    constexpr iterator begin() noexcept { return Data; }

    constexpr iterator end() noexcept { return Data + Size; }

    constexpr const_iterator cbegin() const noexcept { return Data; }

    constexpr const_iterator cend() const noexcept { return Data + Size; }

    constexpr reverse_iterator rbegin() noexcept { return std::reverse_iterator(end()); }

    constexpr reverse_iterator rend() noexcept { return std::reverse_iterator(begin()); }

    constexpr const_reverse_iterator crbegin() const noexcept { return std::reverse_iterator(cend()); }

    constexpr const_reverse_iterator crend() const noexcept { return std::reverse_iterator(cbegin()); }
};

#endif //CPPDATASTRUCTURES_ARRAY_HPP
