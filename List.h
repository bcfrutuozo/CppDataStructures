//
// Created by bcfrutuozo on 19/03/2022.
//

#ifndef CPPDATASTRUCTURES_LIST_H
#define CPPDATASTRUCTURES_LIST_H

#include "Array.h"
#include "Queue.h"
#include <algorithm>

template<typename T>
class List {
private:

    struct ListNode {
        T Data;
        ListNode *Next;

        constexpr explicit ListNode(const T &element) noexcept: Data(element), Next(nullptr) {}

        constexpr ListNode(const T &element, ListNode *next) noexcept: Data(element), Next(next) {}
    };

    //<editor-fold desc="Iterators implementation">
    struct Iterator {

        // Aliases to handle const and non-const iterators
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T *;  // or also value_type*
        using reference = T &;  // or also value_type&

        // Pointer field representation
        ListNode* pElement = nullptr;

        constexpr Iterator(ListNode *ptr) noexcept : pElement(ptr) {}

        constexpr reference operator*() const { return pElement->Data; }

        constexpr pointer operator->() const { return &(pElement->Data); }

        // Prefix increment
        constexpr Iterator &operator++() {
            this->pElement = this->pElement->Next;
            return *this;
        }

        // Postfix increment
        constexpr Iterator operator++(int) {
            Iterator tmp = *this;
            this->pElement = this->pElement->Next;
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
        ListNode* pElement = nullptr;

        constexpr ConstIterator(ListNode *ptr) noexcept: pElement(ptr) {}

        constexpr reference operator*() const { return pElement->Data; }

        constexpr pointer operator->() const { return &(pElement->Data); }

        // Prefix increment
        constexpr ConstIterator &operator++() {
            this->pElement = this->pElement->Next;
            return *this;
        }

        // Postfix increment
        constexpr ConstIterator operator++(int) {
            ConstIterator tmp = *this;
            this->pElement = this->pElement->Next;
            return tmp;
        }

        constexpr friend bool operator==(const ConstIterator &a, const ConstIterator &b) noexcept {
            return a.pElement == b.pElement;
        };

        constexpr friend bool operator!=(const ConstIterator &a, const ConstIterator &b) noexcept {
            return a.pElement != b.pElement;
        };
    };
    //</editor-fold>

    ListNode *Head;
    ListNode *Tail;
    size_t Size;

public:

    constexpr List() noexcept
            :
            Head(nullptr),
            Tail(nullptr),
            Size(0) {}

    constexpr List(const List &other) noexcept
            :
            Head(nullptr),
            Tail(nullptr),
            Size(other.Size) {
        if (Size == 0) return;

        auto n = other.Head;
        //ListNode begin = nullptr;
        ListNode* previous = nullptr;
        while (n != nullptr) {
            if (Head == nullptr) {
                Head = new ListNode(n->Data);
                //begin = Head;
                previous = Head;
                Tail = Head;
            } else {
                auto newNode = new ListNode(n->Data);
                Tail = newNode;
                previous->Next = newNode;
                previous = newNode;
            }
            n = n->Next;
        }
    }

    List(std::initializer_list<T> l) noexcept
            :
            Head(nullptr),
            Tail(nullptr),
            Size(0) {
        if (empty(l)) return;

        for (auto it = l.begin(); it != l.end(); ++it) {
            Add(*it);
        }
    }

    constexpr ~List() noexcept {
        Clear();
    }

    constexpr List &operator=(const List &other) noexcept {
        List copied(other);
        Swap(copied);
        return *this;
    }

    constexpr bool operator==(const List &other) const noexcept {
        if (GetLength() != other.GetLength()) return false;

        for (auto itself = cbegin(), itother = other.cbegin(); itself != cend(); ++itself, ++itother)
            if (*itself != *itother)
                return false;

        return true;
    }

    constexpr bool operator!=(const List &other) const noexcept {
        return !(*this == other);
    }

    constexpr void Add(const T &element) {
        auto n = new ListNode(element);

        if(GetLength() == 0) {
            Head = Tail = n;
        }else {
            auto t = Tail;
            Tail->Next = n;
            Tail = n;
        }
        ++Size;
    }

    constexpr void AddRange(const List<T> &list) {
        for (auto it = list.cbegin(); it != list.cend(); ++it) {
            Add(*it);
        }
    }

    constexpr void AddRangeAt(const List<T> &list, size_t index) {
        if(index == LastIndex() + 1) {
            AddRange(list);
            return;
        }

        if ((ssize_t)index > LastIndex() + 1) throw std::out_of_range("Index is larger than the actual list index");

        auto n = Head;
        size_t i = 0;
        ListNode *previous = nullptr;
        for (; i < index; ++i, previous = n, n = n->Next);

        // Now that we are within range, let's add it!
        auto other = list.Head;
        ListNode* otherPrevious = nullptr;
        size_t j = 0;
        while (other != nullptr) {
            auto newNode = new ListNode(other->Data);

            if(previous == nullptr)
            {
                previous = newNode;
                newNode->Next = Head;
                Head = newNode;
            } else {
                previous->Next = newNode;
                //newNode->Next = other;
                previous = newNode;
            }

            other = other->Next;
            //if(Tail == n) Tail = newNode;
            if(other == nullptr) newNode->Next = n;
        }

        Size = GetLength() + list.GetLength();
    }

    constexpr void Clear() noexcept {
        while (Head != nullptr)
        {
            auto t = Head;
            Head = Head->Next;
            delete t;
        }
    }

    constexpr bool Contains(const T &other) const noexcept {
        if (IsEmpty()) return false;

        for (auto it = cbegin(); it != cend(); ++it)
            if (*it == other)
                return true;

        return false;
    }

    constexpr void CopyTo(Array<T> &array, size_t arrayIndex) const {
        if (arrayIndex > array.LastIndex()) throw std::out_of_range("arrayIndex is out of Array boundaries");
        if (IsEmpty()) return;

        /* diff represents the amount of additional space the provided array needs to
         * successfully copy all data at the desired index. If its 0 or negative, means
         * the array has plenty of space. Otherwise it represents the number of
         * additional slots
        */
        ssize_t diff = (array.GetLength() + arrayIndex) - GetLength();
        if (diff > 0) Array<T>::Resize(diff, array.GetLength() + diff);

        auto itArray = array.begin();
        Iterator itself;
        for (; itArray != array.end(); ++itArray, ++itself)
            *itArray = *itself;
    }

    constexpr size_t Count(const T &element) {
        size_t total = 0;
        for (auto it = cbegin(); it != cend(); ++it)
            if (*it == element)
                ++total;
        return total;
    }

    inline constexpr size_t GetLength() const noexcept { return Size; }

    constexpr ssize_t IndexOf(const T &element) const noexcept {
        if (GetLength() == 0) return -1;

        auto n = Head;
        size_t i = 0;
        while (n != nullptr) {
            if (n->Data == element) return i;
            n = n->Next;
            ++i;
        }

        return -1;
    }

    constexpr Array<size_t> IndicesOf(const T &element) const noexcept {
        if (GetLength() == 0) return Array<size_t>(0);

        auto n = Head;
        size_t i = 0;
        Queue<size_t> indices;
        while (n != nullptr) {
            if (n->Data == element) indices.Enqueue(i);
            n = n->Next;
            ++i;
        }

        return indices.ToArray();
    }

    inline constexpr bool IsEmpty() const noexcept { return Size == 0; }

    inline constexpr ssize_t LastIndex() const noexcept { return Size - 1; }

    constexpr ssize_t LastIndexOf(const T &element) const noexcept {
        if (GetLength() == 0) return -1;

        auto n = Head;
        size_t i = 0;
        ssize_t idx = -1;
        while (n != nullptr) {
            if (n->Data == element) idx = i;
            n = n->Next;
            ++i;
        }

        return idx;
    }

    constexpr void Remove(const T &element) {
        auto n = Head;
        ListNode* previous = nullptr;
        while (n != nullptr) {
            if (n->Data == element) {
                previous->Next = n->Next;
                delete n;
                return;
            }
            previous = n;
            n = n->Next;
        }
        --Size;
    }

    constexpr void RemoveAll(const T &element) {
        auto n = Head;
        ListNode* previous = nullptr;
        while (n != nullptr) {
            if (n->Data == element) {
                previous->Next = n->Next;
                auto t = n;
                n = n->Next;
                delete t;
                --Size;
            } else
            {
                previous = n;
                n = n->Next;
            }
        }
    }

    constexpr void RemoveAt(size_t index) {
        if ((ssize_t) index > LastIndex()) throw std::out_of_range("Index is out of bounds");

        auto n = Head;
        ListNode *previous = nullptr;

        // Empty for statement to move pointers to the desired ListNode. O(n) operation again...
        for (size_t i = 0; i < index; ++i, previous = n, n = n->Next);

        if(previous != nullptr) previous->Next = n->Next;
        if (Head == n) Head = n->Next;
        if (Tail == n) { Tail = previous;}

        --Size;
        delete n;
    }

    constexpr void RemoveRange(size_t index, size_t count) {
        if ((ssize_t) index > LastIndex()) throw std::out_of_range("Index is out of bounds");
        if ((index + count - 1) > LastIndex())
            throw std::out_of_range("Provided ranged is not valid for the operation");

        auto n = Head;
        ListNode *previous = nullptr;

        // Empty for statement to move pointers to the desired ListNode. O(n) operation again...
        for (size_t i = 0; i < index; ++i, previous = n, n = n->Next);

        for (size_t i = 0; i < count; ++i) {
            if(previous != nullptr) previous->Next = n->Next;

            if (Head == n) Head = n->Next;
            if (Tail == n) Tail = previous;
            auto t = n->Next;
            delete n;
            n = t;
        }

        Size -= count;
    }

    constexpr void Swap(List &other) noexcept {
        using std::swap;

        swap(Head, other.Head);
        swap(Tail, other.Tail);
        swap(Size, other.Size);
    }

    constexpr Array<T> ToArray() const noexcept {
        if (IsEmpty()) return Array<T>(0);

        Array<T> a(Size);
        auto n = Head;
        for (size_t i = 0; n != nullptr; ++i, n = n->Next)
            a[i] = n->Data;

        return a;
    }

    constexpr Iterator begin() noexcept { return Head; }

    constexpr Iterator end() noexcept { return (Tail == nullptr ? nullptr : Tail->Next); }

    constexpr ConstIterator cbegin() const noexcept { return Head; }

    constexpr ConstIterator cend() const noexcept { return (Tail == nullptr ? nullptr : Tail->Next); }
};

#endif //CPPDATASTRUCTURES_LIST_H
