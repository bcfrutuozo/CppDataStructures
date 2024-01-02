//
// Created by bcfrutuozo on 18/03/2022.
//

#ifndef CPPDATASTRUCTURES_QUEUE_HPP
#define CPPDATASTRUCTURES_QUEUE_HPP

#include "../Platform.hpp"
#include "Array.hpp"

#include <stdexcept>
#include <iostream>

template<typename T>
class Queue {

private:

    struct Node {

        // Declarations
        using pointer = T*;
        using size_type = size_t;
        using value_type = T;
        using reference = value_type &;
        using const_reference = const value_type&;
        using const_pointer = const value_type*;

        value_type Data;
        Node *Next;

        constexpr explicit Node(const_reference element) noexcept: Data(element), Next(nullptr) {}

        constexpr Node(const_reference element, Node *next) noexcept: Data(element), Next(next) {}
    };

    // Declarations
    using pointer = Node::pointer;
    using size_type = Node::size_type;
    using value_type = Node::value_type;
    using reference = Node::reference;
    using const_reference = Node::const_reference;
    using const_pointer = Node::const_pointer;

    inline constexpr void DeleteFront() noexcept {
        auto f = Front;
        Front = Front->Next;
        delete f;

        if (Front == nullptr) Rear = nullptr;
        --Size;
    }

    Node *Front;
    Node *Rear;
    size_type Size;

public:

    constexpr Queue() noexcept
            :
            Front(nullptr),
            Rear(nullptr),
            Size(0) {}

    constexpr Queue(const Queue &other) noexcept:
            Front(nullptr),
            Rear(nullptr),
            Size(other.GetLength()) {
        if (other.IsEmpty()) return;

        auto poRear = other.Front;
        while (poRear != nullptr) {
            auto n = new Node(poRear->Data);

            if (Front == nullptr && Rear == nullptr) {
                Front = Rear = n;
            } else {
                Rear->Next = n;
                Rear = n;
            }

            poRear = poRear->Next;
        };
    }

    constexpr Queue(Queue &&other) noexcept:
            Front(std::move(other.Front)),
            Rear(std::move(other.Rear)),
            Size(std::move(other.Size)) {
        other.Front = other.Rear = nullptr;
        other.Size = 0;
    }

    constexpr Queue(std::initializer_list<T> l) noexcept
            :
            Front(nullptr),
            Rear(nullptr),
            Size(0) { // Initialize it with 0 because Size will be increment in Enqueue function
        if (empty(l)) return;

        for (auto it = l.begin(); it != l.end(); ++it) {
            Enqueue(*it);
        }
    }

    constexpr ~Queue() noexcept {
        Clear();
    }

    constexpr Queue &operator=(const Queue &other) noexcept {
        Queue copied(other);
        Swap(copied);
        return *this;
    }

    constexpr Queue &operator=(Queue &&other) noexcept {

        // Self-assignment detection
        if (&other == this) return *this;

        // First clear the actual list
        Clear();
        Front = other.Front;
        Rear = other.Rear;
        Size = other.Size;

        other.Front = other.Rear = nullptr;
        other.Size = 0;

        return *this;
    }

    constexpr bool operator==(const Queue &other) const noexcept {
        if (GetLength() != other.GetLength()) return false;

        auto r = Front;
        auto o = other.Front;
        while (r != nullptr) {
            if (!Equals(o->Data, r->Data)) return false;
            r = r->Next;
            o = o->Next;
        }

        return true;
    }

    inline constexpr bool operator!=(const Queue &other) const noexcept {
        return !(*this == other);
    }

    constexpr void Clear() noexcept {
        while (!IsEmpty())
            DeleteFront();
    }

    constexpr bool Contains(const T &element) const noexcept {
        auto n = Front;
        while (n != nullptr) {
            if (Equals(n->Data, element)) return true;
            n = n->Next;
        }
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
        ssize_t diff = GetLength() - (array.GetLength() - arrayIndex);
        if (diff > 0) Array<value_type>::Resize(array, array.GetLength() + (size_type) diff);
        auto n = Front;
        for (auto i = arrayIndex; n != nullptr; ++i, n = n->Next) {
            array[i] = n->Data;
        }
    }

    constexpr void Enqueue(const_reference element) noexcept {
        auto n = new Node(element);
        if (Rear == nullptr) {
            Rear = n;
            Front = n;
        } else {
            Rear->Next = n;
            Rear = n;
        }
        ++Size;
    }

    constexpr void Enqueue(const Array<value_type> &array) noexcept {
        for (auto it = array.cbegin(); it != array.cend(); ++it) {
            Enqueue(*it);
        }
    }

    [[nodiscard]] constexpr value_type Dequeue() {
        if (IsEmpty()) throw std::out_of_range("Queue is already empty");

        value_type obj = Peek();
        DeleteFront();
        return obj;
    }

    [[nodiscard]] constexpr Array<value_type > Dequeue(size_type amount) {
        if (amount > GetLength())
            throw std::out_of_range("Cannot Pop a number of elements higher than the Stack itself");

        Array<value_type> array(amount);
        for (size_t i = 0; i < amount; ++i) {
            array[i] = Dequeue();
        }

        return array;
    }

    inline constexpr size_type GetLength() const noexcept { return Size; }

    inline constexpr bool IsEmpty() const noexcept { return Size == 0; }

    constexpr value_type Peek() const {
        if (IsEmpty()) throw std::out_of_range("Queue is empty. There's no element to check");
        return Front->Data;
    }

    constexpr void Swap(Queue &other) noexcept {
        using std::swap;

        swap(Front, other.Front);
        swap(Rear, other.Rear);
        swap(Size, other.Size);
    }

    constexpr Array<value_type > ToArray() const noexcept {
        if (IsEmpty()) return Array<value_type >(0);

        Array<value_type > a(Size);
        auto n = Front;
        for (auto i = 0; n != nullptr; ++i, n = n->Next)
            a[i] = n->Data;

        return a;
    }
};

#endif //CPPDATASTRUCTURES_QUEUE_HPP
