//
// Created by bcfrutuozo on 21/03/2022.
//

#ifndef CPPDATASTRUCTURES_LINKEDLIST_H
#define CPPDATASTRUCTURES_LINKEDLIST_H

template<typename T>
class LinkedList {

private:

    struct Node {

        T Data;
        Node *Previous;
        Node *Next;

        constexpr explicit Node(const T &element) noexcept: Data(element) {}

        constexpr Node(const T &element, Node *previous, Node *next) noexcept: Data(element), Previous(previous),
                                                                               Next(next) {}
    };

public:



};


#endif //CPPDATASTRUCTURES_LINKEDLIST_H
