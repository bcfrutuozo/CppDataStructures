//
// Created by bcfrutuozo on 14/03/2022.
//

#ifndef CPPDATASTRUCTURES_ARRAY_H
#define CPPDATASTRUCTURES_ARRAY_H

#include <stdexcept>
#include <algorithm>

template<typename T>
class Array {

private:

    //<editor-fold desc="Proxy to handle operator[] as Getter/Setter">
    class ArrayValue {
    private:

        T *pValue;

    public:

        explicit constexpr ArrayValue(T *value) noexcept
                :
                pValue(value) {}

        constexpr operator T() const noexcept { return *pValue; }

        constexpr void operator=(const T &val) noexcept { *pValue = val; }
    };
    //</editor-fold>

    //<editor-fold desc="Iterators implementation">
    struct Iterator {

        // Aliases to handle const and non-const iterators
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T *;  // or also value_type*
        using reference = T &;  // or also value_type&

        // Pointer field representation
        pointer pElement = nullptr;

        constexpr Iterator(T *ptr) noexcept : pElement(ptr) {}

        constexpr reference operator*() const { return *pElement; }

        constexpr pointer operator->() const { return pElement; }

        // Prefix increment
        constexpr Iterator &operator++() {
            this->pElement++;
            return *this;
        }

        // Postfix increment
        constexpr Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        constexpr friend bool operator==(const Iterator &a, const Iterator &b) noexcept {
            return a.pElement == b.pElement;
        };

        constexpr friend bool operator!=(const Iterator &a, const Iterator &b) noexcept {
            return a.pElement != b.pElement;
        };
    };

    struct ConstIterator {

        // Aliases to handle const and non-const iterators
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = const T;
        using pointer = const T *;  // or also value_type*
        using reference = const T &;  // or also value_type&

        // Pointer field representation
        pointer pElement = nullptr;

        constexpr ConstIterator(const T *ptr) noexcept: pElement(ptr) {}

        constexpr reference operator*() const { return *pElement; }

        constexpr pointer operator->() const { return pElement; }

        // Prefix increment
        constexpr ConstIterator &operator++() {
            this->pElement++;
            return *this;
        }

        // Postfix increment
        constexpr ConstIterator operator++(int) {
            ConstIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        constexpr friend bool operator==(const ConstIterator &a, const ConstIterator &b) noexcept {
            return a.pElement == b.pElement;
        };

        constexpr friend bool operator!=(const ConstIterator &a, const ConstIterator &b) noexcept {
            return a.pElement != b.pElement;
        };
    };

    struct ReverseIterator {

        // Aliases to handle const and non-const iterators
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T *;  // or also value_type*
        using reference = T &;  // or also value_type&

        // Pointer field representation
        pointer pElement = nullptr;

        constexpr ReverseIterator(T *ptr) noexcept: pElement(ptr) {}

        constexpr reference operator*() const { return *pElement; }

        constexpr pointer operator->() const { return pElement; }

        // Prefix increment
        constexpr ReverseIterator &operator++() {
            this->pElement--;
            return *this;
        }

        // Postfix increment
        constexpr ReverseIterator operator++(int) {
            ReverseIterator tmp = *this;
            --(*this);
            return tmp;
        }

        constexpr friend bool operator==(const ReverseIterator &a, const ReverseIterator &b) noexcept {
            return a.pElement == b.pElement;
        };

        constexpr friend bool operator!=(const ReverseIterator &a, const Iterator &b) noexcept {
            return a.pElement != b.pElement;
        };
    };

    struct ConstReverseIterator {

        // Aliases to handle const and non-const iterators
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = const T;
        using pointer = const T *;  // or also value_type*
        using reference = const T &;  // or also value_type&

        constexpr reference operator*() const { return *pElement; }

        constexpr pointer operator->() const { return pElement; }

        // Pointer field representation
        pointer pElement = nullptr;

        constexpr ConstReverseIterator(const T *ptr) noexcept: pElement(ptr) {}

        // Prefix increment
        constexpr ConstReverseIterator &operator++() {
            this->pElement--;
            return *this;
        }

        // Postfix increment
        constexpr ConstReverseIterator operator++(int) {
            ConstReverseIterator tmp = *this;
            --(*this);
            return tmp;
        }

        constexpr friend bool operator==(const ConstReverseIterator &a, const ConstReverseIterator &b) noexcept {
            return a.pElement == b.pElement;
        };

        constexpr friend bool operator!=(const ConstReverseIterator &a, const ConstReverseIterator &b) noexcept {
            return a.pElement != b.pElement;
        };
    };
    //</editor-fold>

    T *Data;
    size_t Size;

public:

    constexpr Array() noexcept
            :
            Data(nullptr),
            Size(0) {}

    constexpr explicit Array(size_t size) noexcept
            :
            Data(new T[size]()),
            Size(size) {}

    constexpr Array(const T &defaultValue, size_t size) noexcept
            :
            Data(new T[size]()),
            Size(size) {
        Fill(defaultValue);
    }

    constexpr Array(const Array &other) noexcept
            :
            Data(nullptr),
            Size(other.Size) {
        if (other.Size == 0) return;

        Data = new T[Size];
        std::copy(other.Data, other.Data + other.Size, Data);
    }

    Array(std::initializer_list<T> l) noexcept:
            Data(nullptr),
            Size(l.size()) {
        if (empty(l)) return;

        Data = new T[Size];
        for (auto it = begin(), itl = l.begin(); it != end(); ++it, ++itl)
            *it = *itl;
    }

    constexpr ~Array() noexcept {
        if (Data != nullptr) {
            delete[] Data;
            Data = nullptr;
        }
    }

    // Using proxy class ArrayValue to handle this function as Getter/Setter
    constexpr ArrayValue operator[](size_t index) {
        if ((ssize_t) index > LastIndex())
            throw std::out_of_range("index is too large for the resized array");

        return ArrayValue(Data + index);
    }

    constexpr Array &operator=(const Array &other) noexcept {
        Array copied(other);
        Swap(copied);
        return *this;
    }

    inline constexpr bool operator==(const Array &other) const noexcept {
        if (Size != other.Size) return false;

        for (auto itself = cbegin(), itother = other.cbegin(); itself != cend(); ++itself, ++itother)
            if (*itself != *itother)
                return false;

        return true;
    }

    inline constexpr bool operator!=(const Array &other) const noexcept {
        return !(*this == other);
    }

    constexpr void Add(const T &element) noexcept {
        size_t newSize = Size + 1;
        auto *newArray = new T[newSize];
        std::copy(Data, Data + Size, newArray);

        delete[] Data;
        Data = newArray;
        Size = newSize;

        Data[LastIndex()] = element;
    }

    constexpr void Add(const Array<T> &other) noexcept {
        if (other.IsEmpty()) return;

        auto newSize = Size + other.Size;
        T *newArray = new T[newSize];
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

    constexpr void AddAtIndex(const T &element, size_t index) {
        if (GetLength() == 0 && index == 0) {
            Add(element);
            return;
        }

        if ((ssize_t) index > LastIndex())
            throw std::out_of_range("Invalid array boundaries");

        size_t newSize = Size + 1;
        T *newArray = new T[newSize];

        // Copy preblock from start until the desired index
        std::copy(Data, Data + index, newArray);

        // Copy the following blocks until the end of the array
        std::copy(Data + index, Data + Size, newArray + index + 1);

        // Fill the desired index block with the new element
        *(newArray + index) = element;

        delete[] Data;
        Data = newArray;
        Size = newSize;

    }

    constexpr void AddAtIndex(const Array &a, size_t index) {
        if ((ssize_t) index > LastIndex())
            throw std::out_of_range("Invalid array boundaries");

        if (IsEmpty())
            Add(a);
        else {
            size_t newSize = Size + a.Size;
            T *newArray = new T[newSize];

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

    constexpr bool Contains(const T &other) const noexcept {
        if (IsEmpty()) return false;

        for (auto it = cbegin(); it != cend(); ++it)
            if (*it == other)
                return true;

        return false;
    }

    static constexpr void Copy(Array &sourceArray, Array &destinationArray) noexcept {
        if (sourceArray.Size > destinationArray.Size)
            destinationArray = sourceArray;
        else {
            for (auto itsource = sourceArray.begin(), itdestination = destinationArray.begin();
                 itsource != sourceArray.end(); ++itsource, ++itdestination) {
                *itdestination = *itsource;
            }
        }
    }

    static constexpr void
    Copy(Array &sourceArray, size_t sourceIndex, Array &destinationArray, size_t destinationIndex) {
        if (sourceIndex > sourceArray.LastIndex() || destinationIndex > destinationArray.LastIndex())
            throw std::out_of_range("Specified index is out of array bounds");

        ssize_t copyAmount = sourceArray.Size - sourceIndex;
        ssize_t availableSpace = destinationArray.Size - destinationIndex;

        bool needExtraSpace = (copyAmount - availableSpace) > 0;
        if (needExtraSpace)
            Array::Resize(destinationArray, destinationArray.Size + (copyAmount - availableSpace));

        std::copy(sourceArray.Data + sourceIndex, sourceArray.Data + sourceIndex + copyAmount,
                  destinationArray.Data + destinationIndex);
    }

    constexpr size_t Count(const T &element) const noexcept {
        size_t total = 0;
        for (auto it = cbegin(); it != cend(); ++it)
            if (*it == element)
                ++total;
        return total;
    }

    constexpr void Fill(const T &element) noexcept {
        for (auto it = begin(); it != end(); ++it)
            *it = element;
    }

    constexpr T &GetBack() const {
        if (IsEmpty())
            throw std::out_of_range("The array is empty");

        return *(Data + LastIndex());
    }

    constexpr T &GetFront() const {
        if (IsEmpty())
            throw std::out_of_range("The array is empty");

        return *Data;
    }

    inline constexpr size_t GetLength() const noexcept { return Size; }

    constexpr ssize_t IndexOf(const T &element) const {
        for (auto it = cbegin(); it != cend(); ++it)
            if (*it == element)
                return std::distance(cbegin(), it);

        return -1;
    }

    constexpr Array<size_t> IndicesOf(const T &element) const noexcept {
        size_t count = Count(element);
        Array<size_t> a(count);

        for (size_t i = 0, j = 0; i < Size; ++i) {
            if (*(Data + i) == element) {
                a[j] = i;
                ++j;

                if (j == count) break;
            }
        }

        return a;
    }

    inline constexpr bool IsEmpty() const noexcept { return Size == 0; }

    inline constexpr ssize_t LastIndex() const noexcept { return Size - 1; }

    constexpr ssize_t LastIndexOf(const T &element) const noexcept {
        for (auto it = crbegin(); it != crend(); ++it)
            if (*it == element)
                return LastIndex() - std::distance(crbegin(), it);

        return -1;
    }

    [[nodiscard]] constexpr T RemoveAt(size_t index) {
        if (IsEmpty() || (ssize_t) index > LastIndex())
            throw std::out_of_range("index is too large for the resized array");

        size_t newSize = Size - 1;
        T *newArray = nullptr;
        T obj = *(Data + index);

        if (newSize > 0) {
            newArray = new T[newSize];
            if (index == 0) {
                std::copy(Data + 1, Data + Size, newArray);
            } else if (index == LastIndex()) {
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

    [[nodiscard]] constexpr T RemoveBack() {
        if (IsEmpty())
            throw std::out_of_range("Cannot remove element from an empty array");

        size_t newSize = Size - 1;
        T *newArray = nullptr;
        T obj = *(Data + newSize);

        if (newSize > 0) {
            newArray = new T[newSize];
            std::copy(Data, Data + Size - 1, newArray);
        }

        delete[] Data;
        Data = newArray;
        Size = newSize;

        return obj;
    }

    [[nodiscard]] constexpr T RemoveFront() {
        if (IsEmpty())
            throw std::out_of_range("Cannot remove element from an empty array");

        size_t newSize = Size - 1;
        T *newArray = nullptr;

        T obj = *Data;

        if (newSize > 0) {
            newArray = new T[newSize];
            std::copy(Data + 1, Data + Size, newArray);
        }

        delete[] Data;
        Data = newArray;
        Size = newSize;

        return obj;
    }

    static constexpr void Resize(Array &a, size_t newSize) noexcept {
        if (newSize == a.Size) return;

        T *newArray = nullptr;

        if (newSize > 0) {
            newArray = new T[newSize];
            if (newSize > a.Size) {
                // Create a default object to fill the new spaces
                T def{0};

                if (a.GetLength() > 0) {
                    std::copy(a.Data, a.Data + a.Size, newArray);
                    for (size_t i = a.Size; i < newSize; ++i)
                        newArray[i] = def;
                } else {
                    for (size_t i = 0; i < newSize; ++i)
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
        ReverseIterator ite = rbegin();
        Iterator itb = begin();

        // We can compare the addresses between ite and itb because array always reallocates
        // itself to another block. So we can perform pointer comparison
        for (; &(*itb) < &(*ite); ++itb, ++ite) {
            T tmp = *ite;
            *ite = *itb;
            *itb = tmp;
        }
    }

    constexpr void Swap(Array &other) noexcept {
        using std::swap;

        swap(Data, other.Data);
        swap(Size, other.Size);
    }

    constexpr Iterator begin() noexcept { return Data; }

    constexpr Iterator end() noexcept { return Data + Size; }

    constexpr ConstIterator cbegin() const noexcept { return Data; }

    constexpr ConstIterator cend() const noexcept { return Data + Size; }

    constexpr ReverseIterator rbegin() noexcept { return Data + LastIndex(); }

    constexpr ReverseIterator rend() noexcept { return Data - 1; }

    constexpr ConstReverseIterator crbegin() const noexcept { return Data + LastIndex(); }

    constexpr ConstReverseIterator crend() const noexcept { return Data - 1; }
};

#endif //CPPDATASTRUCTURES_ARRAY_H
