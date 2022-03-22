//
// Created by bcfrutuozo on 21/03/2022.
//

#ifndef CPPDATASTRUCTURES_LINKEDLIST_H
#define CPPDATASTRUCTURES_LINKEDLIST_H

#include <iterator>

template<typename T>
class LinkedList {

private:

    struct Node {

        T Data;
        Node *Previous;
        Node *Next;

        constexpr explicit Node(const T &element) noexcept: Data(element) {}

        constexpr Node(const T &element, Node *previous) noexcept: Data(element), Previous(previous) {}

        constexpr Node(const T &element, Node *previous, Node *next) noexcept: Data(element), Previous(previous),
                                                                               Next(next) {}
    };

    //<editor-fold desc="Iterators implementation">
    struct Iterator {

        // Aliases to handle const and non-const iterators
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T *;  // or also value_type*
        using reference = T &;  // or also value_type&

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

        // Prefix decrement
        constexpr Iterator &operator--() {
            this->pElement = this->pElement->Previous;
            return *this;
        }

        // Postfix decrement
        constexpr Iterator operator--(int) {
            Iterator tmp = *this;
            this->pElement = this->pElement->Previous;
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
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = const T;
        using pointer = const T *;  // or also value_type*
        using reference = const T &;  // or also value_type&

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

        // Prefix decrement
        constexpr ConstIterator &operator--() {
            this->pElement = this->pElement->Previous;
            return *this;
        }

        // Postfix decrement
        constexpr ConstIterator operator--(int) {
            Iterator tmp = *this;
            this->pElement = this->pElement->Previous;
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
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T *;  // or also value_type*
        using reference = T &;  // or also value_type&

        // Pointer field representation
        Node *pElement = nullptr;

        constexpr ReverseIterator(Node *ptr) noexcept: pElement(ptr) {}

        constexpr reference operator*() const { return pElement->Data; }

        constexpr pointer operator->() const { return &(pElement->Data); }

        // Prefix increment
        constexpr ReverseIterator &operator++() {
            this->pElement = this->pElement->Previous;
            return *this;
        }

        // Postfix increment
        constexpr ReverseIterator operator++(int) {
            Iterator tmp = *this;
            this->pElement = this->pElement->Previous;
            return tmp;
        }

        // Prefix decrement
        constexpr ReverseIterator &operator--() {
            this->pElement = this->pElement->Next;
            return *this;
        }

        // Postfix decrement
        constexpr ReverseIterator operator--(int) {
            Iterator tmp = *this;
            this->pElement = this->pElement->Next;
            return tmp;
        }

        constexpr friend bool operator==(const ReverseIterator &a, const ReverseIterator &b) noexcept {
            return a.pElement == b.pElement;
        };

        constexpr friend bool operator!=(const ReverseIterator &a, const ReverseIterator &b) noexcept {
            return a.pElement != b.pElement;
        };
    };

    struct ConstReverseIterator {

        // Aliases to handle const and non-const iterators
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = const T;
        using pointer = const T *;  // or also value_type*
        using reference = const T &;  // or also value_type&

        // Pointer field representation
        Node *pElement = nullptr;

        constexpr ConstReverseIterator(Node *ptr) noexcept: pElement(ptr) {}

        constexpr reference operator*() const { return pElement->Data; }

        constexpr pointer operator->() const { return &(pElement->Data); }

        // Prefix increment
        constexpr ConstReverseIterator &operator++() {
            this->pElement = this->pElement->Previous;
            return *this;
        }

        // Postfix increment
        constexpr ConstReverseIterator operator++(int) {
            ConstIterator tmp = *this;
            this->pElement = this->pElement->Previous;
            return tmp;
        }

        // Prefix decrement
        constexpr ConstReverseIterator &operator--() {
            this->pElement = this->pElement->Next;
            return *this;
        }

        // Postfix decrement
        constexpr ConstReverseIterator operator--(int) {
            Iterator tmp = *this;
            this->pElement = this->pElement->Next;
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

    Node *Head;
    Node *Tail;
    size_t Size;

public:

    constexpr LinkedList() noexcept
            :
            Head(nullptr),
            Tail(nullptr),
            Size(0) {}

    constexpr LinkedList(const LinkedList &other) noexcept:
            Head(nullptr),
            Tail(nullptr),
            Size(other.Size) {

    }

    constexpr LinkedList(LinkedList&& other) noexcept :
            Head(std::move(other.Head)),
            Tail(std::move(other.Tail)),
            Size(std::move(other.Size)) {
        other.Head = other.Tail = nullptr;
        Size = 0;
    }

    constexpr LinkedList(std::initializer_list<T> l) noexcept
            :
            Head(nullptr),
            Tail(nullptr),
            Size(0) {
        if (empty(l)) return;

        for (auto it = l.begin(); it != l.end(); ++it) {
            Add(*it);
        }
    }

    constexpr ~LinkedList() noexcept {
        Clear();
    }

    constexpr LinkedList &operator=(const LinkedList &other) noexcept {
        List copied(other);
        Swap(copied);
        return *this;
    }

    constexpr LinkedList &operator=(LinkedList &&other) noexcept {

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

    constexpr bool operator==(const LinkedList &other) const noexcept {
        if (GetLength() != other.GetLength()) return false;

        for (auto itself = cbegin(), itother = other.cbegin(); itself != cend(); ++itself, ++itother)
            if (*itself != *itother)
                return false;

        return true;
    }

    constexpr bool operator!=(const LinkedList &other) const noexcept {
        return !(*this == other);
    }

    constexpr void Add(const T &element) noexcept {
        auto n = new Node(element, Tail);

        if (GetLength() == 0) {
            Head = Tail = n;
        } else {
            auto t = Tail;
            Tail->Next = n;
            Tail = n;
        }
        ++Size;
    }

    constexpr void Clear(){
        while (Head != nullptr) {
            auto t = Head;
            if(Head != Tail) Head->Next->Previous = nullptr;
            Head = Head->Next;
            delete t;
            --Size;
        }

        Head = Tail = nullptr;
    }

    inline constexpr size_t GetLength() const noexcept { return Size; }

    inline constexpr bool IsEmpty() const noexcept { return Size == 0; }

    inline constexpr ssize_t LastIndex() const noexcept { return Size - 1; }

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
        for (size_t i = 0; i < GetLength() / 2; ++itb, ++ite, ++i) {
            T tmp = *ite;
            *ite = *itb;
            *itb = tmp;
        }
    }

    constexpr void Swap(LinkedList &other) noexcept {
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

    constexpr Iterator end() noexcept { return Tail->Next; }

    constexpr ConstIterator cbegin() const noexcept { return Head; }

    constexpr ConstIterator cend() const noexcept { return Tail->Next; }

    constexpr ReverseIterator rbegin() noexcept { return Tail; }

    constexpr ReverseIterator rend() noexcept { return Head->Previous; }

    constexpr ConstReverseIterator crbegin() const noexcept { return Tail; }

    constexpr ConstReverseIterator crend() const noexcept { return Head->Previous; }

};

#endif //CPPDATASTRUCTURES_LINKEDLIST_H