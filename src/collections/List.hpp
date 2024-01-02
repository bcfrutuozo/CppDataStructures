//
// Created by bcfrutuozo on 19/03/2022.
//

#ifndef CPPDATASTRUCTURES_LIST_HPP
#define CPPDATASTRUCTURES_LIST_HPP

#include "../Platform.hpp"
#include "Array.hpp"
#include "Queue.hpp"

#include <algorithm>

template<typename T>
class List {
private:

    struct Node {

        // Declarations
        using pointer = T*;
        using size_type = size_t;
        using value_type = T;
        using reference = value_type &;
        using const_reference = const value_type&;
        using const_pointer = const value_type*;

        value_type  Data;
        Node *Next;

        constexpr explicit Node(const_reference element) noexcept: Data(element), Next(nullptr) {}

        constexpr Node(const_reference element, Node *next) noexcept: Data(element), Next(next) {}
    };

    //<editor-fold desc="Iterators implementation">
    struct Iterator {

        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        // Pointer field representation
        Node *pElement = nullptr;

        constexpr Iterator(Node *ptr) noexcept: pElement(ptr) {}

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
        using pointer = const T*;  // or also value_type*
        using reference = const T&;  // or also value_type&

        // Pointer field representation
        Node *pElement = nullptr;

        constexpr ConstIterator(Node *ptr) noexcept: pElement(ptr) {}

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

    // Declarations
    using pointer = Node::pointer;
    using size_type = Node::size_type;
    using value_type = Node::value_type;
    using reference = Node::reference;
    using const_reference = Node::const_reference;
    using const_pointer = Node::const_pointer;
    using iterator = List::Iterator;
    using const_iterator = List::ConstIterator;

    Node *Head;
    Node *Tail;
    size_type Size;

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
        Node *previous = nullptr;
        while (n != nullptr) {
            if (Head == nullptr) {
                Head = new Node(n->Data);
                //begin = Head;
                previous = Head;
                Tail = Head;
            } else {
                auto newNode = new Node(n->Data);
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

    constexpr List(std::initializer_list<value_type> l) noexcept
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

    constexpr void Add(const_reference element) noexcept {
        auto n = new Node(element);

        if (GetLength() == 0) {
            Head = Tail = n;
        } else {
            auto t = Tail;
            Tail->Next = n;
            Tail = n;
        }
        ++Size;
    }

    constexpr void AddAt(const_reference element, size_type index) {

        // By checking this, we eliminate the necessity to work with Head and Tail pointers
        if (index == GetLastIndex() + 1) {
            Add(element);
            return;
        }

        if (index > GetLastIndex() + 1) throw std::out_of_range("Index is larger than the actual list index");

        auto n = Head;
        Node *previous = nullptr;

        // Move pointer and variables to the desired values
        for (auto i = 0; i < index; ++i, previous = n, n = n->Next);

        auto newNode = new Node(element);
        newNode->Next = n;

        if (previous == nullptr) Head = newNode;
        else previous->Next = newNode;

        ++Size;
    }

    constexpr void AddRange(const List<value_type > &list) noexcept {
        for (auto it = list.cbegin(); it != list.cend(); ++it) {
            Add(*it);
        }
    }

    constexpr void AddRangeAt(const List<value_type > &list, size_type index) {
        if (index == GetLastIndex() + 1) {
            AddRange(list);
            return;
        }

        if (index > GetLastIndex() + 1) throw std::out_of_range("Index is larger than the actual list index");

        auto n = Head;
        Node *previous = nullptr;
        for (size_t i = 0; i < index; ++i, previous = n, n = n->Next);

        // Now that we are within range, let's add it!
        auto other = list.Head;
        while (other != nullptr) {
            auto newNode = new Node(other->Data);
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

    constexpr bool Contains(const_reference other) const noexcept {
        if (IsEmpty()) return false;

        for (auto it = cbegin(); it != cend(); ++it)
            if (Equals(*it, other)) return true;

        return false;
    }

    constexpr void CopyTo(Array<value_type> &array, size_type arrayIndex) const {
        if (arrayIndex > array.GetLastIndex()) throw std::out_of_range("arrayIndex is out of Array boundaries");
        if (IsEmpty()) return;

        /* diff represents the amount of additional space the provided array needs to
         * successfully copy all data at the desired index. If its 0 or negative, means
         * the array has plenty of space. Otherwise, it represents the number of
         * additional slots
        */
        ssize_t diff = (array.GetLength() + arrayIndex) - GetLength();
        if (diff > 0) Array<value_type >::Resize(diff, array.GetLength() + diff);

        auto itArray = array.begin();
        auto itself = cbegin();
        for (; itArray != array.end(); ++itArray, ++itself)
            *itArray = *itself;
    }

    constexpr size_type Count(const_reference element) const noexcept {
        size_type total = 0;
        for (auto it = cbegin(); it != cend(); ++it)
            if (Equals(*it, element)) ++total;
        return total;
    }

    inline constexpr size_type GetLastIndex() const {
        if (IsEmpty()) throw std::out_of_range("The list is empty");
        return Size - 1;
    }

    inline constexpr size_type GetLength() const noexcept { return Size; }

    constexpr size_type IndexOf(const_reference element) const noexcept {
        if (GetLength() == 0) return -1;

        auto n = Head;
        size_type i = 0;
        while (n != nullptr) {
            if (Equals(n->Data, element)) return i;
            n = n->Next;
            ++i;
        }

        return -1;
    }

    constexpr Array<size_type> IndicesOf(const_reference element) const noexcept {
        if (GetLength() == 0) return Array<size_type>(0);

        auto n = Head;
        size_type i = 0;
        Queue<size_type> indices;
        while (n != nullptr) {
            if (Equals(n->Data, element)) indices.Enqueue(i);
            n = n->Next;
            ++i;
        }

        return indices.ToArray();
    }

    inline constexpr bool IsEmpty() const noexcept { return Size == 0; }

    constexpr size_type LastIndexOf(const_reference element) const noexcept {
        if (GetLength() == 0) return -1;

        auto n = Head;
        size_type i = 0, foundIndex = 0;
        bool found = false;
        while (n != nullptr) {
            if (Equals(n->Data, element)) {
                found = true;
                foundIndex = i;
                break;
            }
            n = n->Next;
            ++i;
        }

        if(!found) throw std::out_of_range("No element found in the list");

        return foundIndex;
    }

    [[nodiscard]] constexpr bool Remove(const_reference element) noexcept {
        auto n = Head;
        Node *previous = nullptr;
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

    constexpr void RemoveAll(const_reference element) noexcept {
        auto n = Head;
        Node *previous = nullptr;
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

    [[nodiscard]] constexpr value_type RemoveAt(size_type index) {
        if (index > GetLastIndex()) throw std::out_of_range("Index is out of bounds");

        auto n = Head;
        Node *previous = nullptr;

        // Empty for statement to move pointers to the desired ListNode. O(n) operation again...
        for (auto i = 0; i < index; ++i, previous = n, n = n->Next);

        if (previous != nullptr) previous->Next = n->Next;
        value_type obj = n->Data;
        if (Head == n) Head = n->Next;
        if (Tail == n) Tail = previous;

        --Size;
        delete n;

        if (Size == 0) Head = Tail = nullptr;

        return obj;
    }

    [[nodiscard]] constexpr Array<value_type> RemoveRange(size_type index, size_type count) {
        if (count < 1) throw std::invalid_argument("count cannot be 0 or negative");
        if (index > GetLastIndex()) throw std::out_of_range("Index is out of bounds");
        if ((index + count - 1) > GetLastIndex())
            throw std::out_of_range("Provided ranged is not valid for the operation");

        auto n = Head;
        Node *previous = nullptr;
        Array<value_type> array(count);
        // Empty for statement to move pointers to the desired ListNode. O(n) operation again...
        for (auto i = 0; i < index; ++i, previous = n, n = n->Next);

        for (auto i = 0; i < count; ++i) {
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

    constexpr Array<value_type > ToArray() const noexcept {
        if (IsEmpty()) return Array<value_type >(0);

        Array<value_type > a(Size);
        auto n = Head;
        for (auto i = 0; n != nullptr; ++i, n = n->Next)
            a[i] = n->Data;

        return a;
    }

    constexpr iterator begin() noexcept { return Head; }

    constexpr iterator end() noexcept { return nullptr; }

    constexpr const_iterator cbegin() const noexcept { return Head; }

    constexpr const_iterator cend() const noexcept { return nullptr; }
};

#endif //CPPDATASTRUCTURES_LIST_HPP
