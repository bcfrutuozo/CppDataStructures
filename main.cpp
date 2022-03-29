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

    String s = "ABCDEABCDAAAABABZUHWUHIIHUAWDJANJKCHIANDIQWUCBAIBBOISPOSPOÁŚDOQIUQHUDQIUHHUVNNMLKAJKOBALASPJOASUBDYUQIUOQWIWDAPNA";
    std::cout << s << std::endl;
    std::cout << "Length: " << s.GetLength() << std::endl; //OK
    std::cout << "Count A: " << s.Count('A') << std::endl; //OK
    std::cout << "TrimStart(A): " << s.TrimStart('A') << std::endl; //OK
    std::cout << "TrimStart(A): " << s.TrimStart("A") << std::endl; //OK
    std::cout << "IndexOf(A): " << s.IndexOf("AB", 1, 8) << std::endl; //OK
    std::cout << "IndexOfAny(QD): " << s.IndexOfAny("QWHUA", 15, 6) << std::endl;
    std::cout << "IndexOf(A): " << s.IndexOf("A") << std::endl; //OK
    std::cout << "LastIndex(A): " << s.LastIndexOf("AN", 8, 80) << std::endl; //OK
    std::cout << "LastIndex(A): " << s.LastIndexOf("A") << std::endl; //OK

/*
 * BCDEF \0
 * BCEDF \0
 * BC FED\0
 */

    return 0;
}