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

#ifdef __linux__ 
//linux code goes here
#elif _WIN32
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#else

#endif

int main(int argc, char *argv[]) {
    Timer t;

    String s = "ABCDEABCDAAAABAÁŚDOQIUQHUDQIUHHUVNNMLKAJKOBALASPJOASUBDYUQIUOQWIWDAPNA";
    std::cout << s << std::endl;
    std::cout << "Length: " << s.GetLength() << std::endl; //OK
    std::cout << "Count A: " << s.Count('A') << std::endl; //OK
    std::cout << "LastIndex(PN): " << s.LastIndexOfAny("AP", 1, 3) << std::endl; //OK


    String a = { "BCZZZ" };
    String b = a.Replace("CZ", "11111");

    std::cout << b << std::endl;

    return 0;
}