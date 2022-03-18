//
// Created by bcfrutuozo on 17/03/2022.
//

#ifndef CPPDATASTRUCTURES_STACK_H
#define CPPDATASTRUCTURES_STACK_H

#include <stdexcept>
#include <iostream>
#include <algorithm>

#include "ForwardIterator.h"
#include "Array.h"

template<typename T>
class Stack {
private:

    struct StackNode {
        T Data;
        StackNode *Previous;

        constexpr explicit StackNode(const T &element) : Data(element), Previous(nullptr) {}
        constexpr StackNode(const T &element, StackNode *previous) : Data(element), Previous(previous) {}
    };

    StackNode *top;
    size_t size;

    void RemoveTop() {
        if (top == nullptr) throw std::out_of_range("Stack is empty");
        auto n = top;
        top = top->Previous;
        --size;
        delete n;
    }

public:

    constexpr Stack() : top(nullptr), size(0) {}

    constexpr Stack(const Stack &other)
            :
            size(other.size) {
        if (other.IsEmpty()) {
            top = nullptr;
        } else {
            auto p = other.top;                 // points to current node on other
            auto tmp = new StackNode(p->Data); // make a copy of the first node
            top = tmp;
            auto tail = tmp;              // points to last node of this list
            while (p->Previous != nullptr) {
                p = p->Previous;
                tmp = new StackNode(p->Data);
                tail->Previous = tmp;
                tail = tmp;
            }
        }
    }

    Stack(std::initializer_list<T> l)
            :
            top(nullptr),
            size(0) {
        if (empty(l)) {
            top = nullptr;
        } else {
            for (auto it = l.begin(); it != l.end(); ++it) {
                Push(*it);
            }
        }
    }

    ~Stack() {
        while (!IsEmpty()) RemoveTop();
    }

    constexpr Stack& operator=(const Stack &other) {
        Stack copied(other);
        Swap(copied);
        return *this;
    }

    bool operator==(const Stack &other) const {
        if(size != other.size) return false;

        auto a = top;
        auto b = other.top;

        while (a != nullptr && b != nullptr) {
            if (a->Data != b->Data) return false;

            a = a->Previous;
            b = b->Previous;
        }

        return true;
    }

    bool operator!=(const Stack &other) const {
        return !(*this == other);
    }

    friend std::ostream &operator<<(std::ostream &os, const Stack &s) {
        auto n = s.top;
        while (n != nullptr) {
            os << n->Data;
            n = n->Previous;
        }
        return os;
    }

    inline constexpr bool IsEmpty() const { return (top == nullptr); }

    inline constexpr size_t GetLength() const { return size; }

    void Push(const T &element) {
        auto n = new StackNode(element, top);
        top = n;
        ++size;
    }

    void Push(const Array<T>& array){
        for(auto it = array.cbegin(); it != array.cend(); ++it)
            Push(*it);
    }

    T Peek() const {
        if (top == nullptr) throw std::out_of_range("Stack is empty");
        return top->Data;
    }

    T Pop() {
        if (top == nullptr) throw std::out_of_range("Stack is empty");

        T obj = Peek();
        RemoveTop();
        return obj;
    }

    Array<T> Pop(size_t amount) {
        if(amount > size) throw std::out_of_range("Cannot Pop a number of elements higher than the Stack itself");

        Array<T> array(amount);
        for(size_t i = 0; i < amount; ++i){
            array[i] = Pop();
        }

        return array;
    }

    void Swap(Stack& other){
        using std::swap;

        swap(top, other.top);
        swap(size, other.size);
    }

    inline constexpr T Top() const {
        if (top == nullptr) throw std::out_of_range("Stack is empty");
        return top->Data;
    }

    constexpr Array<T> ToArray() const {
        if (size == 0) return Array<T>(0);

        Array<T> a(size);
        auto n = top;
        for (size_t i = 0; n != nullptr; ++i, n = n->Previous)
            a[i] = n->Data;

        return a;
    }

    static void UnloadInto(Stack& sourceStack, Stack& destinationStack)
    {
        while(!sourceStack.IsEmpty())
            destinationStack.Push(sourceStack.Pop());
    }
};

#endif //CPPDATASTRUCTURES_STACK_H
