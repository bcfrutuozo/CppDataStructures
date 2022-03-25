#include "Timer.h"
#include "Array.h"
#include "List.h"
#include "LinkedList.h"
#include "Stack.h"
#include "Queue.h"
#include <forward_list>
#include <array>
#include <list>
#include "String.h"
#include <string>

#include <iostream>

int main(int argc, char *argv[]) {
    Timer t;

    String s = "ABCDEFABCDEFABCFED";
    std::cout << s << std::endl;
    std::cout << "Length: " << s.GetLength() << std::endl;
    std::cout << "Count A: " << s.Count('A') << std::endl;

    auto z = s.Split("C");

    for(size_t i = 0; i < z.GetLength(); ++i)
        std::cout << z[i] << std::endl;

/*
 * BCDEF \0
 * BCEDF \0
 * BC FED\0
 */

    return 0;
}