#include "Timer.h"
#include "Array.h"
#include "List.h"
#include <forward_list>
#include <array>

#include <iostream>

int main(int argc, char *argv[]) {

    List<int> a;

    for(size_t i = 0 ; i < 10; ++i){
        std::cout << "Pushing: " << i << std::endl;
        a.Add(i);
    }

    a.RemoveRange(0, 4);

    for(auto it = a.begin(); it != a.end(); ++it)
        std::cout << *it << std::endl;

    return 0;
}