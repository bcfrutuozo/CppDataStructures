#include "Timer.h"
#include "Array.h"
#include "List.h"
#include <forward_list>
#include <array>

#include <iostream>

int main(int argc, char *argv[]) {

    List<int> a = { 0, 0, 1, 0, 0};
    List<int> b = { 0, 0, 0, 0 };

    a.RemoveAll(0);

    for(auto it = a.begin(); it != a.end(); ++it)
        std::cout << *it;
    std::cout << std::endl;

    return 0;
}