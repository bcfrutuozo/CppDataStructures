//
// Created by bcfrutuozo on 18/03/2022.
//

#ifndef CPPDATASTRUCTURES_QUEUE_H
#define CPPDATASTRUCTURES_QUEUE_H

#include <stdexcept>
#include <iostream>
#include "Array.h"

template<typename T>
class Queue {

private:

    struct QueueNode {
        T Data;
        QueueNode *Next;

        constexpr explicit QueueNode(const T &element) noexcept: Data(element), Next(nullptr) {}

        constexpr QueueNode(const T &element, QueueNode *next) noexcept: Data(element), Next(next) {}
    };

    inline constexpr void DeleteFront() noexcept {
        auto f = Front;
        Front = Front->Next;
        delete f;

        if (Front == nullptr) Rear = nullptr;
        --Size;
    }

    QueueNode *Front;
    QueueNode *Rear;
    size_t Size;

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
            auto n = new QueueNode(poRear->Data);

            if (Front == nullptr && Rear == nullptr) {
                Front = Rear = n;
            } else {
                Rear->Next = n;
                Rear = n;
            }

            poRear = poRear->Next;
        };
    }

    Queue(std::initializer_list<T> l) noexcept
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

    constexpr bool operator==(const Queue &other) const noexcept {
        if (GetLength() != other.GetLength()) return false;

        auto r = Front;
        auto o = other.Front;
        while (r != nullptr) {
            if (o->Data != r->Data) return false;
            r = r->Next;
            o = o->Next;
        }

        return true;
    }

    constexpr bool operator!=(const Queue &other) const noexcept {
        return !(*this == other);
    }

    inline constexpr void Clear() noexcept {
        while (!IsEmpty()) DeleteFront();
    }

    constexpr bool Contains(const T &element) const noexcept {
        auto n = Front;
        while (n != nullptr) {
            if (n->Data == element) return true;
            n = n->Next;
        }
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
        auto n = Front;
        size_t i = 0;
        for (size_t i = 0; n != nullptr; ++i, n = n->Next) {
            array[i] = n->Data;
        }
    }

    constexpr void Enqueue(const T &element) noexcept {
        auto n = new QueueNode(element);
        if (Rear == nullptr) {
            Rear = n;
            Front = n;
        } else {
            Rear->Next = n;
            Rear = n;
        }
        ++Size;
    }

    constexpr void Enqueue(const Array<T> &array) noexcept {
        for (auto it = array.cbegin(); it != array.cend(); ++it) {
            Enqueue(*it);
        }
    }

    [[nodiscard]] constexpr T Dequeue() {
        if (IsEmpty()) throw std::out_of_range("Queue is already empty");

        T obj = Peek();
        DeleteFront();
        return obj;
    }

    [[nodiscard]] constexpr Array<T> Dequeue(size_t amount) {
        if (amount > GetLength())
            throw std::out_of_range("Cannot Pop a number of elements higher than the Stack itself");

        Array<T> array(amount);
        for (size_t i = 0; i < amount; ++i) {
            array[i] = Dequeue();
        }

        return array;
    }

    inline constexpr size_t GetLength() const noexcept { return Size; }

    inline constexpr bool IsEmpty() const noexcept { return Size == 0; }

    inline constexpr T Peek() const {
        if (IsEmpty()) throw std::out_of_range("Queue is empty. There's no element to check");
        return Front->Data;
    }

    constexpr void Swap(Queue &other) noexcept {
        using std::swap;

        swap(Front, other.Front);
        swap(Rear, other.Rear);
        swap(Size, other.Size);
    }

    constexpr Array<T> ToArray() const noexcept {
        if (IsEmpty()) return Array<T>(0);

        Array<T> a(Size);
        auto n = Front;
        for (size_t i = 0; n != nullptr; ++i, n = n->Next)
            a[i] = n->Data;

        return a;
    }
};

#endif //CPPDATASTRUCTURES_QUEUE_H
