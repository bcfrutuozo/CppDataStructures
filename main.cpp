#include "Array.h"
#include "String.h"
#include <vector>
#include <iostream>

void Test() {

    Array<int> a = { 0, 1, 2, 3, 4, 5};
    Array<int> b = { 5, 4, 3, 2, 1, 0};

    Array<int>::Copy(a, 0, b, 0);

    std::cout << a << std::endl;
    std::cout << b << std::endl;
}

int main(int argc, char *argv[]) {
    Test();

    std::vector<int> z = { 1, 2, 3, 4, 5};

    return 0;
}