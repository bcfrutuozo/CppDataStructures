#include "Timer.h"
#include "Array.h"
#include "List.h"
#include "LinkedList.h"
#include "Stack.h"
#include "Queue.h"
#include <forward_list>
#include <array>
#include <list>

#include <iostream>

int main(int argc, char *argv[]) {
    Timer t;

    LinkedList<int> a{0, 1, 2, 3, 4, 5, 6, 7, 8};

    for (auto it = a.cbegin(); it != a.cend(); ++it)
        std::cout << *it;
    std::cout << " | ";
    for (auto it = a.crbegin(); it != a.crend(); ++it)
        std::cout << *it;
    std::cout << std::endl;

    a.RemoveLast(0);
    for (auto it = a.cbegin(); it != a.cend(); ++it)
        std::cout << *it;
    std::cout << " | ";
    for (auto it = a.crbegin(); it != a.crend(); ++it)
        std::cout << *it;
    std::cout <<  std::endl;


    return 0;
}