#include "Array.h"
#include "String.h"
#include <vector>
#include <iostream>

void Test() {

    Array<int> a = {0, 0, 0};
    Array<int> b = {4, 2, 6, 2, 2, 2, 1, 1, 2, 4, 5, 5, 5, 2, 1, 2, 1};
    Array<String> c = {"ABC", "DEF", "111"};

    Array<String> z = { "OI1", "OI2" };
    c.AddAtIndex(z, 0);
    std::cout << c << std::endl;

    for(auto it = b.begin(); it != b.end(); ++it)
        std::cout << *it;

}

int main(int argc, char *argv[]) {
    Test();

    std::vector<int> z = { 1, 2, 3, 4, 5};

    return 0;
}