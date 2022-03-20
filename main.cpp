#include "Timer.h"
#include "Array.h"
#include "List.h"

#include <iostream>

int main(int argc, char *argv[]) {

    List<int> a = {1, 2, 3, 4, 5};
    List<int> b(a);
    b.Add(4);
    std::cout << (a == b) << std::endl;

    return 0;
}