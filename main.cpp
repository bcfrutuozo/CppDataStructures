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

    LinkedList<int> a{1, 2, 3, 4, 5, 6, 7, 8};

    for(auto it = a.crbegin(); it != a.crend(); ++it)
        std::cout << *it;


    return 0;
}