#include "Timer.h"
#include "Array.h"

#include <iostream>

int main(int argc, char *argv[]) {

    Timer t;

    Array<char> a = {'1', '3', '4', '2', '8'};
    a.AddAtIndex('1', 2);
    Array<char> b = {'1', '3', '1', '4', '2', '8'};
    std::cout << (a == b);
    a.AddAtIndex('9', 5);
    Array<char> c = {'1', '3', '1', '4', '2', '9', '8'};
    std::cout << (a == c);

    std::cout << std::endl;

    for(size_t i = 0; i < a.GetLength(); ++i)
        std::cout << a[i];

    std::cout << std::endl;

    for(size_t i = 0; i < c.GetLength(); ++i)
        std::cout << c[i];

    std::cout << std::endl;

    return 0;
}