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

    String s = "ABCDEF ABCDEF ABC FED";
    std::cout << s << std::endl;
    std::cout << "Length: " << s.GetLength() << std::endl;
    std::cout << "Count A: " << s.Count('A') << std::endl;

    auto z = s.Split("AB");

    for(size_t i = 0; i < z.GetLength(); ++i)
        std::cout << z[i] << std::endl;

    return 0;
}