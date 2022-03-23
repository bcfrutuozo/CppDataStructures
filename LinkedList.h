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

    constexpr void AddAt(const T &element, size_t index) {

        // By checking this, we eliminate the necessity to work with Head and Tail pointers
        if (index == LastIndex() + 1) {
            Add(element);
            return;
        }

        if ((ssize_t) index > LastIndex() + 1) throw std::out_of_range("Index is larger than the actual list index");

        auto n = Head;
        Node *previous = nullptr;
        Node *next = nullptr;

        // Move pointer and variables to the desired values
        for (size_t i = 0; i < index; ++i, previous = n, n = n->Next);

        auto newNode = new Node(element, previous);
        newNode->Next = n;
        n->Previous = newNode;

        if (previous == nullptr) Head = newNode;
        else previous->Next = newNode;

        ++Size;
    }

    constexpr void AddRange(const LinkedList<T> &list) noexcept {
        for (auto it = list.cbegin(); it != list.cend(); ++it) {
            Add(*it);
        }
    }

    constexpr void AddRangeAt(const LinkedList<T> &list, size_t index) {
        if (index == LastIndex() + 1) {
            AddRange(list);
            return;
        }

        if ((ssize_t) index > LastIndex() + 1) throw std::out_of_range("Index is larger than the actual list index");

        Node *previous = nullptr;
        Node *next = nullptr;
        bool isNearTail = (GetLength() - index) < index;
        Node* n;
        if(isNearTail){
            n = Tail;
            for(size_t i = LastIndex(); i >= index; --i, next = n, n = n->Previous);
        } else {
             n = Head;
            for (size_t i = 0; i < index; ++i, previous = n, n = n->Next);
        }

        // Now that we are within range, let's add it!
        if(isNearTail) {
            auto other = list.Tail;
            while (other != nullptr) {
                auto newNode = new Node(other->Data);
                if (next == nullptr) {
                    next = newNode;
                    // We never move Tail as we add it prior to it.
                    // To add after and move Tail the AddRange function is called
                    Tail = newNode;
                } else {
                    next->Previous = newNode;
                    newNode->Next = next;
                    next = newNode;
                }

                other = other->Previous;
                if (other == nullptr) {
                    newNode->Previous = n;
                    n->Next = newNode;
                }
            }
        }
        else {
            auto other = list.Head;
            while (other != nullptr) {
                auto newNode = new Node(other->Data);
                if (previous == nullptr) {
                    previous = newNode;
                    newNode->Next = Head;
                    Head->Previous = newNode;
                    Head = newNode;
                } else {
                    previous->Next = newNode;
                    newNode->Previous = previous;
                    previous = newNode;
                }

                other = other->Next;
                if (other == nullptr) {
                    newNode->Next = n;
                    n->Previous = newNode;
                }
            }
        }

        Size = GetLength() + list.GetLength();
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
        auto itself = cbegin();
        for (; itArray != array.end(); ++itArray, ++itself)
            *itArray = *itself;
    }

    constexpr size_t Count(const T &element) const noexcept {
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

        auto n = Tail;
        size_t i = LastIndex();
        ssize_t idx = -1;
        while (n != nullptr) {
            if (n->Data == element) idx = i;
            n = n->Previous;
            --i;
        }

        return idx;
    }

    [[nodiscard]] constexpr bool Remove(const T &element) noexcept {
        auto n = Head;
        Node *previous = nullptr;
        while (n != nullptr) {
            if (n->Data == element) {
                if (Head != n) {
                    previous->Next = n->Next;
                    if(n->Next != nullptr) n->Next->Previous = previous;
                }
                auto t = n;
                n = n->Next;
                if (Head == t) Head = n;
                if (Tail == t) Tail = previous;
                delete t;
                --Size;
                if (Size == 0) Head = Tail = nullptr;
                return true;
            }
            previous = n;
            n = n->Next;
        }
        return false;
    }

    constexpr void RemoveAll(const T &element) noexcept {
        auto n = Head;
        Node *previous = nullptr;
        while (n != nullptr) {
            if (n->Data == element) {
                if (Head != n) {
                    previous->Next = n->Next;
                    if(n->Next != nullptr) n->Next->Previous = previous;
                }
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

        // Empty for statement to move pointers to the desired ListNode. O(n) operation again...
        Node *previous = nullptr;
        bool isNearTail = (GetLength() - index) < index;
        Node* n;
        T obj;
        if(isNearTail){
            n = Tail;
            Node* next = nullptr;
            for(size_t i = LastIndex(); i > index; --i, next = n, n = n->Previous);

            if (next != nullptr) {
                next->Previous = n->Previous;
                if(n->Previous != nullptr) n->Previous->Next = next;
            }
            obj = n->Data;
            if (Head == n) Head = next;
            if (Tail == n) {
                Tail = n->Previous;
                Tail->Next = nullptr;
            }

        } else {
            n = Head;
            for (size_t i = 0; i < index; ++i, previous = n, n = n->Next);

            if (previous != nullptr) {
                previous->Next = n->Next;
                if(n->Next != nullptr) n->Next->Previous = previous;
            }

            obj = n->Data;
            if (Head == n) {
                Head = n->Next;
                Head->Previous = nullptr;
            }
            if (Tail == n) Tail = previous;
        }

        --Size;
        delete n;

        if (Size == 0) Head = Tail = nullptr;

        return obj;
    }

    [[nodiscard]] constexpr bool RemoveLast(const T& element) noexcept {
        auto n = Tail;
        Node *next = nullptr;
        while (n != nullptr) {
            if (n->Data == element) {
                if (Tail != n) {
                    if(next != nullptr) next->Previous = n->Previous;
                    if(n != Head) {
                        n->Previous->Next = next;
                        next->Previous = n->Previous;
                    }
                }
                auto t = n;
                if (Size == 1) Head = Tail = nullptr;

                else {
                    if (Head == t) {
                        Head = n->Next;
                        Head->Previous = nullptr;
                    }
                    if (Tail == t) {
                        Tail = t->Previous;
                        Tail->Next = nullptr;
                    }
                }

                delete t;
                --Size;
                return true;
            }
            next = n;
            n = n->Previous;
        }
        return false;
    }

    [[nodiscard]] constexpr Array<T> RemoveRange(size_t index, size_t count) {
        if (count < 1) throw std::invalid_argument("count cannot be 0 or negative");
        if ((ssize_t) index > LastIndex()) throw std::out_of_range("Index is out of bounds");
        if ((ssize_t) (index + count - 1) > LastIndex())
            throw std::out_of_range("Provided ranged is not valid for the operation");

        Node* n;
        Node *previous = nullptr;
        Array<T> array(count);
        // Empty for statement to move pointers to the desired ListNode. O(n) operation again...
        bool isNearTail = (GetLength() - index) < index;
        if(isNearTail){
            n = Tail;
            for(size_t i = LastIndex(); i >= index; --i, previous = n, n = n->Previous);
        } else {
            n = Head;
            for (size_t i = 0; i < index; ++i, previous = n, n = n->Next);
        }

        for (size_t i = 0; i < count; ++i) {
            if (previous != nullptr) {
                previous->Next = n->Next;
                if(n->Next != nullptr) n->Next->Previous = previous;
            }

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