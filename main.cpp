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

    Int32 a = 8;
    Char c = a;
    int ooo = c;
    Int32 abc = c;
    a = c;


#ifdef _WIN32
    _CrtDumpMemoryLeaks();
#endif

    return 0;
}