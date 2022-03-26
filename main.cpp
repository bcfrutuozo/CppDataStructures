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

    String s = "ABA";
    std::cout << s << std::endl;
    std::cout << "Length: " << s.GetLength() << std::endl; //OK
    std::cout << "Count A: " << s.Count('A') << std::endl; //OK
    std::cout << "TrimStart(A): " << s.TrimStart('A') << std::endl; //OK
    std::cout << "TrimStart(A): " << s.TrimStart("A") << std::endl; //OK
    std::cout << "IndexOf(A): " << s.IndexOf('A') << std::endl; //OK
    std::cout << "IndexOf(A): " << s.IndexOf("A") << std::endl; //OK
    std::cout << "LastIndex(A): " << s.LastIndexOf('A') << std::endl; //OK
    std::cout << "LastIndex(A): " << s.LastIndexOf("A") << std::endl; //OK
    auto idx = s.IndicesOf('A');

    for(size_t i = 0; i < idx.GetLength(); ++i)
        std::cout << idx[i];

    std::cout << std::endl;
    String strim = "  ABCDEF ABC ABCDEFG  ";
    //String strim = " A ";
    std::cout << strim << std::endl;
    std::cout << "TrimStart(A): " << strim.TrimStart() << std::endl; //OK
    std::cout << "TrimEnd(A): " << strim.TrimEnd() << std::endl; //OK
    std::cout << "Trim(A): " << strim.Trim() << std::endl; //OK


    auto z = s.Split("A");

    for(size_t i = 0; i < z.GetLength(); ++i)
        std::cout << z[i] << std::endl;

/*
 * BCDEF \0
 * BCEDF \0
 * BC FED\0
 */

    return 0;
}