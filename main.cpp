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
#include "Char.h"
#include "Int32.h"
#include "Boolean.h"

#include <iostream>

#ifdef _WIN32
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

int main(int argc, char *argv[]) {
    Timer t;

    String b = "0123456789";
    String s = "ABCDEABCDAAAABAÁŚDOQIUQHUDQIUHHUVNNMLKAJKOBALASPJOASUBDYUQIUOQWIWDAPNA";
    std::cout << s << std::endl;
    std::cout << "Length: " << s.GetLength() << std::endl; //OK
    std::cout << "Count A: " << s.Count('A') << std::endl; //OK
    std::cout << "LastIndex(PN): " << s.LastIndexOfAny("AP", 1, 3) << std::endl; //OK

    constexpr Int32 a = 8;
    constexpr Char c = 1;
    constexpr int ooo = 8;
    Int32 abc = 10;
    constexpr Boolean b1 = true;

    // Guarantee there is no overhead
    static_assert(sizeof(Int32) == sizeof(int), "The wrapper has overhead.");
    static_assert(sizeof(Char) == sizeof(char), "The wrapper has overhead.");
    static_assert(sizeof(Boolean) == sizeof(bool), "The wrapper has overhead.");

    static_assert(c == b1);


#ifdef _WIN32
    _CrtDumpMemoryLeaks();
#endif

    return 0;
}