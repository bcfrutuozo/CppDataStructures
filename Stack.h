//
// Created by bcfrutuozo on 17/03/2022.
//

#ifndef CPPDATASTRUCTURES_STACK_H
#define CPPDATASTRUCTURES_STACK_H

#include "Platform.h"
#include "Array.h"

#include <stdexcept>
#include <algorithm>

template<typename T>
class Stack : protected Container<T> {
private:

    struct StackNode {
        T Data;
        StackNode *Previous;

        constexpr explicit StackNode(const T &element) noexcept: Data(element), Previous(nullptr) {}

        constexpr StackNode(const T &element, StackNode *previous) noexcept: Data(element), Previous(previous) {}
    };

    inline constexpr void RemoveTop() noexcept {
        auto n = Top;
        Top = Top->Previous;
        --Size;
        delete n;
    }

    StackNode *Top;
    size_t Size;

public:

    constexpr Stack() noexcept: Top(nullptr), Size(0) {}

    constexpr Stack(const Stack &other) noexcept
            :
            Top(nullptr),
            Size(other.GetLength()) {
        if (other.IsEmpty()) return;

        auto p = other.Top;                 // points to current node on other
        auto tmp = new StackNode(p->Data); // make a copy of the first node
        Top = tmp;
        auto tail = tmp;              // points to last node of this list
        while (p->Previous != nullptr) {
            p = p->Previous;
            tmp = new StackNode(p->Data);
            tail->Previous = tmp;
            tail = tmp;
        }
    }

    constexpr Stack(Stack &&other) noexcept:
            Top(std::move(other.Top)),
            Size(std::move(other.Size)) {
        other.Top = nullptr;
        other.Size = 0;
    }

    constexpr Stack(std::initializer_list<T> l) noexcept
            :
            Top(nullptr),
            Size(0) {   // Initialize it with 0 because Size will be increment in Push function
        if (empty(l)) return;

        for (auto it = l.begin(); it != l.end(); ++it) {
            Push(*it);
        }
    }

    constexpr ~Stack() noexcept {
        Clear();
    }

    constexpr Stack &operator=(const Stack &other) noexcept {
        Stack copied(other);
        Swap(copied);
        return *this;
    }

    constexpr Stack &operator=(Stack &&other) noexcept {

        // Self-assignment detection
        if (&other == this) return *this;

        // First clear the actual list
        Clear();
        Top = other.Top;
        Size = other.Size;

        other.Top = nullptr;
        other.Size = 0;

        return *this;
    }

    inline constexpr bool operator==(const Stack &other) const noexcept {
        if (GetLength() != other.GetLength()) return false;

        auto a = Top;
        auto b = other.Top;

        while (a != nullptr && b != nullptr) {
            if (!Equals(a->Data, b->Data)) return false;
            a = a->Previous;
            b = b->Previous;
        }

        return true;
    }

    inline constexpr bool operator!=(const Stack &other) const noexcept {
        return !(*this == other);
    }

    inline constexpr void Clear() noexcept {
        while (!IsEmpty()) RemoveTop();
    }

    constexpr bool Contains(const T &element) const noexcept {
        auto n = Top;
        while (n != nullptr) {
            if (Equals(n->Data, element)) return true;
            n = n->Previous;
        }
        return false;
    }

    constexpr void CopyTo(Array<T> &array, size_t arrayIndex) const {
        if ((ssize_t)arrayIndex > array.LastIndex()) throw std::out_of_range("arrayIndex is out of Array boundaries");
        if (IsEmpty()) return;

        /* diff represents the amount of additional space the provided array needs to
         * successfully copy all data at the desired index. If its 0 or negative, means
         * the array has plenty of space. Otherwise it represents the number of
         * additional slots
        */
        ssize_t diff = GetLength() - (array.GetLength() - arrayIndex);
        if (diff > 0) Array<T>::Resize(array, array.GetLength() + (size_t)diff);
        auto n = Top;
        for (size_t i = arrayIndex + this->GetLength() - 1; n != nullptr; --i, n = n->Previous) {
            array[i] = n->Data;
        }
    }

    inline constexpr bool IsEmpty() const noexcept { return (Top == nullptr); }

    inline constexpr size_t GetLength() const noexcept { return Size; }

    constexpr void Push(const T &element) noexcept {
        auto n = new StackNode(element, Top);
        Top = n;
        ++Size;
    }

    constexpr void Push(const Array<T> &array) noexcept {
        for (auto it = array.cbegin(); it != array.cend(); ++it)
            Push(*it);
    }

    constexpr T Peek() const {
        if (IsEmpty()) throw std::out_of_range("Stack is empty");
        return Top->Data;
    }

    [[nodiscard]] constexpr T Pop() {
        if (IsEmpty()) throw std::out_of_range("Stack is empty");

        T obj = Peek();
        RemoveTop();
        return obj;
    }

    [[nodiscard]] constexpr Array<T> Pop(size_t amount) {
        if (amount > GetLength())
            throw std::out_of_range("Cannot Pop a number of elements higher than the Stack itself");

        Array<T> array(amount);
        for (ssize_t i = 0; i < amount; ++i) {
            array[i] = Pop();
        }

        return array;
    }

    constexpr void Swap(Stack &other) noexcept {
        using std::swap;

        swap(Top, other.Top);
        swap(Size, other.Size);
    }

    constexpr Array<T> ToArray() const noexcept {
        if (IsEmpty()) return Array<T>(0);

        Array<T> a(Size);
        auto n = Top;
        for (ssize_t i = a.LastIndex(); n != nullptr; --i, n = n->Previous)
            a[i] = n->Data;

        return a;
    }
};

#endif //CPPDATASTRUCTURES_STACK_H
