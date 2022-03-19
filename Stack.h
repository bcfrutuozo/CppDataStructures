//
// Created by bcfrutuozo on 17/03/2022.
//

#ifndef CPPDATASTRUCTURES_STACK_H
#define CPPDATASTRUCTURES_STACK_H

#include <stdexcept>
#include <algorithm>

#include "ForwardIterator.h"
#include "Array.h"

template<typename T>
class Stack {
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
            Size(other.GetLength()) {
        if (other.IsEmpty()) {
            Top = nullptr;
        } else {
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
    }

    Stack(std::initializer_list<T> l) noexcept
            :
            Top(nullptr),
            Size(0) {
        if (empty(l)) {
            Top = nullptr;
        } else {
            for (auto it = l.begin(); it != l.end(); ++it) {
                Push(*it);
            }
        }
    }

    ~Stack() noexcept {
        Clear();
    }

    constexpr Stack &operator=(const Stack &other) noexcept {
        Stack copied(other);
        Swap(copied);
        return *this;
    }

    bool operator==(const Stack &other) const noexcept {
        if (GetLength() != other.GetLength()) return false;

        auto a = Top;
        auto b = other.Top;

        while (a != nullptr && b != nullptr) {
            if (a->Data != b->Data) return false;

            a = a->Previous;
            b = b->Previous;
        }

        return true;
    }

    bool operator!=(const Stack &other) const noexcept {
        return !(*this == other);
    }

    inline void Clear() noexcept {
        while (!IsEmpty()) RemoveTop();
    }

    bool Contains(const T &element) const noexcept {
        auto n = Top;
        while (n != nullptr) {
            if (n->Data == element) return true;
            n = n->Previous;
        }
        return false;
    }

    void CopyTo(Array<T> &array, size_t arrayIndex) {
        if (arrayIndex > array.LastIndex()) throw std::out_of_range("arrayIndex is out of Array boundaries");
        if (IsEmpty()) return;

        /* diff represents the amount of additional space the provided array needs to
         * successfully copy all data at the desired index. If its 0 or negative, means
         * the array has plenty of space. Otherwise it represents the number of
         * additional slots
        */
        ssize_t diff = (array.GetLength() + arrayIndex) - GetLength();
        if (diff > 0) Array<T>::Resize(diff, array.GetLength() + diff);
        auto n = Top;
        size_t i = 0;
        for (size_t i = arrayIndex + this->GetLength(); n != nullptr; --i, n = n->Previous) {
            array[i] = n->Data;
        }
    }

    inline constexpr bool IsEmpty() const noexcept { return (Top == nullptr); }

    inline constexpr size_t GetLength() const noexcept { return Size; }

    void Push(const T &element) noexcept {
        auto n = new StackNode(element, Top);
        Top = n;
        ++Size;
    }

    void Push(const Array<T> &array) noexcept {
        for (auto it = array.cbegin(); it != array.cend(); ++it)
            Push(*it);
    }

    T Peek() const {
        if (IsEmpty()) throw std::out_of_range("Stack is empty");
        return Top->Data;
    }

    [[nodiscard]] T Pop() {
        if (IsEmpty()) throw std::out_of_range("Stack is empty");

        T obj = Peek();
        RemoveTop();
        return obj;
    }

    [[nodiscard]] Array<T> Pop(size_t amount) {
        if (amount > GetLength())
            throw std::out_of_range("Cannot Pop a number of elements higher than the Stack itself");

        Array<T> array(amount);
        for (size_t i = amount - 1; i >= 0; --i) {
            array[i] = Pop();
        }

        return array;
    }

    void Swap(Stack &other) noexcept {
        using std::swap;

        swap(Top, other.Top);
        swap(Size, other.Size);
    }

    constexpr Array<T> ToArray() const noexcept {
        if (IsEmpty()) return Array<T>(0);

        Array<T> a(Size);
        auto n = Top;
        for (size_t i = 0; n != nullptr; ++i, n = n->Previous)
            a[i] = n->Data;

        return a;
    }

    static void UnloadInto(Stack &sourceStack, Stack &destinationStack) {
        while (!sourceStack.IsEmpty())
            destinationStack.Push(sourceStack.Pop());
    }
};

#endif //CPPDATASTRUCTURES_STACK_H
