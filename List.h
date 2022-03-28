//
// Created by bcfrutuozo on 19/03/2022.
//

#ifndef CPPDATASTRUCTURES_LIST_H
#define CPPDATASTRUCTURES_LIST_H

#include "Platform.h"
#include "Array.h"
#include "Queue.h"

#include <algorithm>

template<typename T>
class List : protected Container<T>{
private:

    struct ListNode {
        T Data;
        ListNode *Next;

        constexpr explicit ListNode(const T &element) noexcept: Data(element), Next(nullptr) {}

        constexpr ListNode(const T &element, ListNode *next) noexcept: Data(element), Next(next) {}
    };

    //<editor-fold desc="Iterators implementation">
    struct Iterator {

        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T *;  // or also value_type*
        using reference = T &;  // or also value_type&

        // Pointer field representation
        ListNode *pElement = nullptr;

        constexpr Iterator(ListNode *ptr) noexcept: pElement(ptr) {}

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
            return !(a == b);
        };
    };

    struct ConstIterator {

        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = const T;
        using pointer = const T *;  // or also value_type*
        using reference = const T &;  // or also value_type&

        // Pointer field representation
        ListNode *pElement = nullptr;

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
            return !(a == b);
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
        ListNode *previous = nullptr;
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

    constexpr List(List &&other) noexcept:
            Head(std::move(other.Head)),
            Tail(std::move(other.Tail)),
            Size(std::move(other.Size)) {
        other.Head = other.Tail = nullptr;
        other.Size = 0;
    }

    constexpr List(std::initializer_list<T> l) noexcept
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

    constexpr List &operator=(List &&other) noexcept {

        // Self-assignment detection
        if (&other == this) return *this;

        // First clear the actual list
        Clear();
        Head = other.Head;
        Tail = other.Tail;
        Size = other.Size;

        other.Head = other.Tail = nullptr;
        other.Size = 0;

        return *this;
    }

    constexpr bool operator==(const List &other) const noexcept {
        if (GetLength() != other.GetLength()) return false;

        for (auto itself = cbegin(), itother = other.cbegin(); itself != cend(); ++itself, ++itother)
            if (!Equals(*itself, *itother))
                return false;

        return true;
    }

    inline constexpr bool operator!=(const List &other) const noexcept {
        return !(*this == other);
    }

    constexpr void Add(const T &element) noexcept {
        auto n = new ListNode(element);

        if (GetLength() == 0) {
            Head = Tail = n;
        } else {
            auto t = Tail;
            Tail->Next = n;
            Tail = n;
        }
        ++Size;
    }

    constexpr void AddAt(const T &element, size_t index) {

        // By checking this, we eliminate the necessity to work with Head and Tail pointers
        if (index == LastIndex() + 1) {
            Add(element);
            return;
        }

        if ((ssize_t) index > LastIndex() + 1) throw std::out_of_range("Index is larger than the actual list index");

        auto n = Head;
        ListNode *previous = nullptr;

        // Move pointer and variables to the desired values
        for (size_t i = 0; i < index; ++i, previous = n, n = n->Next);

        auto newNode = new ListNode(element);
        newNode->Next = n;

        if (previous == nullptr) Head = newNode;
        else previous->Next = newNode;

        ++Size;
    }

    constexpr void AddRange(const List<T> &list) noexcept {
        for (auto it = list.cbegin(); it != list.cend(); ++it) {
            Add(*it);
        }
    }

    constexpr void AddRangeAt(const List<T> &list, size_t index) {
        if (index == LastIndex() + 1) {
            AddRange(list);
            return;
        }

        if ((ssize_t) index > LastIndex() + 1) throw std::out_of_range("Index is larger than the actual list index");

        auto n = Head;
        ListNode *previous = nullptr;
        for (size_t i = 0; i < index; ++i, previous = n, n = n->Next);

        // Now that we are within range, let's add it!
        auto other = list.Head;
        while (other != nullptr) {
            auto newNode = new ListNode(other->Data);
            if (previous == nullptr) {
                previous = newNode;
                newNode->Next = Head;
                Head = newNode;
            } else {
                previous->Next = newNode;
                previous = newNode;
            }

            other = other->Next;
            if (other == nullptr) newNode->Next = n;
        }

        Size = GetLength() + list.GetLength();
    }

    constexpr void Clear() noexcept {
        while (Head != nullptr) {
            auto t = Head;
            Head = Head->Next;
            delete t;
            --Size;
        }

        Head = Tail = nullptr;
    }

    constexpr bool Contains(const T &other) const noexcept {
        if (IsEmpty()) return false;

        for (auto it = cbegin(); it != cend(); ++it)
            if (Equals(*it, other)) return true;

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
        auto itself = cbegin();
        for (; itArray != array.end(); ++itArray, ++itself)
            *itArray = *itself;
    }

    constexpr size_t Count(const T &element) const noexcept {
        size_t total = 0;
        for (auto it = cbegin(); it != cend(); ++it)
            if (Equals(*it, element)) ++total;
        return total;
    }

    inline constexpr size_t GetLength() const noexcept { return Size; }

    constexpr ssize_t IndexOf(const T &element) const noexcept {
        if (GetLength() == 0) return -1;

        auto n = Head;
        size_t i = 0;
        while (n != nullptr) {
            if (Equals(n->Data, element)) return i;
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
            if (Equals(n->Data, element)) indices.Enqueue(i);
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
            if (Equals(n->Data, element)) idx = i;
            n = n->Next;
            ++i;
        }

        return idx;
    }

    [[nodiscard]] constexpr bool Remove(const T &element) noexcept {
        auto n = Head;
        ListNode *previous = nullptr;
        while (n != nullptr) {
            if (Equals(n->Data, element)) {
                if (Head != n) previous->Next = n->Next;
                auto t = n;
                if (Size == 1) Head = Tail = nullptr;
                else {
                    n = n->Next;
                    if (Head == t) Head = n;
                    if (Tail == t) Tail = previous;
                }
                delete t;
                --Size;
                return true;
            }
            previous = n;
            n = n->Next;
        }
        return false;
    }

    constexpr void RemoveAll(const T &element) noexcept {
        auto n = Head;
        ListNode *previous = nullptr;
        while (n != nullptr) {
            if (Equals(n->Data, element)) {
                if (Head != n) previous->Next = n->Next;
                auto t = n;
                n = n->Next;
                if (Head == t) Head = n;
                if (Tail == t) Tail = previous;
                delete t;
                --Size;
            } else {
                previous = n;
                n = n->Next;
            }
        }

        if (Size == 0) Head = Tail = nullptr;
    }

    [[nodiscard]] constexpr T RemoveAt(size_t index) {
        if ((ssize_t) index > LastIndex()) throw std::out_of_range("Index is out of bounds");

        auto n = Head;
        ListNode *previous = nullptr;

        // Empty for statement to move pointers to the desired ListNode. O(n) operation again...
        for (size_t i = 0; i < index; ++i, previous = n, n = n->Next);

        if (previous != nullptr) previous->Next = n->Next;
        T obj = n->Data;
        if (Head == n) Head = n->Next;
        if (Tail == n) Tail = previous;

        --Size;
        delete n;

        if (Size == 0) Head = Tail = nullptr;

        return obj;
    }

    [[nodiscard]] constexpr Array<T> RemoveRange(size_t index, size_t count) {
        if (count < 1) throw std::invalid_argument("count cannot be 0 or negative");
        if ((ssize_t) index > LastIndex()) throw std::out_of_range("Index is out of bounds");
        if ((ssize_t) (index + count - 1) > LastIndex())
            throw std::out_of_range("Provided ranged is not valid for the operation");

        auto n = Head;
        ListNode *previous = nullptr;
        Array<T> array(count);
        // Empty for statement to move pointers to the desired ListNode. O(n) operation again...
        for (size_t i = 0; i < index; ++i, previous = n, n = n->Next);

        for (size_t i = 0; i < count; ++i) {
            if (previous != nullptr) previous->Next = n->Next;

            if (Head == n) Head = n->Next;
            if (Tail == n) Tail = previous;
            array[i] = n->Data;
            auto t = n->Next;
            delete n;
            n = t;
        }

        Size -= count;

        if (Size == 0) Head = Tail = nullptr;

        return array;
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

    constexpr Iterator end() noexcept { return nullptr; }

    constexpr ConstIterator cbegin() const noexcept { return Head; }

    constexpr ConstIterator cend() const noexcept { return nullptr; }
};

#endif //CPPDATASTRUCTURES_LIST_H
