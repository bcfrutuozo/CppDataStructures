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
#include "Byte.h"
#include "SByte.h"
#include "Int64.h"
#include "UInt64.h"
#include "Int16.h"
#include "UInt16.h"
#include "Double.h"
#include "Float.h"
#include "UInt32.h"

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
    Char c = 1;
    int ooo = 8;
    Int32 abc = 10;
    Boolean b1 = true;
    Boolean b2 = false;

    // Guarantee there is no overhead
    static_assert(sizeof(UInt32) == sizeof(unsigned int), "The wrapper has overhead.");
    static_assert(sizeof(Byte) == sizeof(char), "The wrapper has overhead.");
    static_assert(sizeof(SByte) == sizeof(signed char), "The wrapper has overhead.");
    static_assert(sizeof(Int32) == sizeof(int), "The wrapper has overhead.");
    static_assert(sizeof(Char) == sizeof(char), "The wrapper has overhead.");
    static_assert(sizeof(Boolean) == sizeof(bool), "The wrapper has overhead.");
    static_assert(sizeof(Float) == sizeof(float), "The wrapper has overhead.");
    static_assert(sizeof(Double) == sizeof(double), "The wrapper has overhead.");
    static_assert(sizeof(Int16) == sizeof(unsigned short), "The wrapper has overhead.");
    static_assert(sizeof(UInt16) == sizeof(short), "The wrapper has overhead.");
    static_assert(sizeof(Int64) == sizeof(long), "The wrapper has overhead.");
    static_assert(sizeof(UInt64) == sizeof(unsigned long), "The wrapper has overhead.");

    float f1 = 1.0f;
    f1 &= 2.0f;

#ifdef _WIN32
    _CrtDumpMemoryLeaks();
#endif

    return 0;
}