//
// Created by bcfrutuozo on 17/03/2022.
//

#ifndef CPPDATASTRUCTURES_STACK_HPP
#define CPPDATASTRUCTURES_STACK_HPP

#include "../Platform.hpp"
#include "Array.hpp"

#include <stdexcept>
#include <algorithm>

template<typename T>
class Stack {
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
        Node *Previous;

        constexpr explicit Node(const_reference element) noexcept: Data(element), Previous(nullptr) {}

        constexpr Node(const_reference element, Node *previous) noexcept: Data(element), Previous(previous) {}
    };

    // Declarations
    using pointer = Node::pointer;
    using size_type = Node::size_type;
    using value_type = Node::value_type;
    using reference = Node::reference;
    using const_reference = Node::const_reference;
    using const_pointer = Node::const_pointer;

    inline constexpr void RemoveTop() noexcept {
        auto n = Top;
        Top = Top->Previous;
        --Size;
        delete n;
    }

    Node *Top;
    size_type Size;

public:

    constexpr Stack() noexcept: Top(nullptr), Size(0) {}

    constexpr Stack(const Stack &other) noexcept
            :
            Top(nullptr),
            Size(other.GetLength()) {
        if (other.IsEmpty()) return;

        auto p = other.Top;                 // points to current node on other
        auto tmp = new Node(p->Data); // make a copy of the first node
        Top = tmp;
        auto tail = tmp;              // points to last node of this list
        while (p->Previous != nullptr) {
            p = p->Previous;
            tmp = new Node(p->Data);
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

    constexpr Stack(std::initializer_list<value_type> l) noexcept
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

    constexpr bool operator==(const Stack &other) const noexcept {
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

    constexpr void Clear() noexcept {
        while (!IsEmpty())
            RemoveTop();
    }

    constexpr bool Contains(const_reference element) const noexcept {
        auto n = Top;
        while (n != nullptr) {
            if (Equals(n->Data, element)) return true;
            n = n->Previous;
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
        if (diff > 0) Array<value_type>::Resize(array, array.GetLength() + (size_type)diff);
        auto n = Top;
        for (size_type i = arrayIndex + this->GetLength() - 1; n != nullptr; --i, n = n->Previous) {
            array[i] = n->Data;
        }
    }

    inline constexpr bool IsEmpty() const noexcept { return (Top == nullptr); }

    inline constexpr size_type GetLength() const noexcept { return Size; }

    constexpr void Push(const_reference element) noexcept {
        auto n = new Node(element, Top);
        Top = n;
        ++Size;
    }

    constexpr void Push(const Array<value_type> &array) noexcept {
        for (auto it = array.cbegin(); it != array.cend(); ++it)
            Push(*it);
    }

    constexpr value_type Peek() const {
        if (IsEmpty()) throw std::out_of_range("Stack is empty");
        return Top->Data;
    }

    [[nodiscard]] constexpr value_type Pop() {
        if (IsEmpty()) throw std::out_of_range("Stack is empty");

        value_type obj = Peek();
        RemoveTop();
        return obj;
    }

    [[nodiscard]] constexpr Array<value_type> Pop(size_type amount) {
        if (amount > GetLength())
            throw std::out_of_range("Cannot Pop a number of elements higher than the Stack itself");

        Array<value_type> array(amount);
        for (auto i = 0; i < amount; ++i) {
            array[i] = Pop();
        }

        return array;
    }

    constexpr void Swap(Stack &other) noexcept {
        using std::swap;

        swap(Top, other.Top);
        swap(Size, other.Size);
    }

    constexpr Array<value_type> ToArray() const noexcept {
        if (IsEmpty()) return Array<value_type>(0);

        Array<value_type> a(Size);
        auto n = Top;
        for (auto i = a.GetLastIndex(); n != nullptr; --i, n = n->Previous)
            a[i] = n->Data;

        return a;
    }
};

#endif //CPPDATASTRUCTURES_STACK_HPP
