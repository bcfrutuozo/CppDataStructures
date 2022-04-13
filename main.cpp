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
#include "Decimal.h"

#include <iostream>

#ifdef _WIN32
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

int main(int argc, char *argv[]) {
    Timer t;

    Boolean b = true;
    String s  = "ABCDEFA";
    auto z = s.ToCharArray();

    char a = 'a';
    Char* p = a;

    for(size_t i = 0; i < s.GetLength(); ++i){
        std::cout << s[i].GetHashCode() << std::endl;
    }

#ifdef _WIN32
    _CrtDumpMemoryLeaks();
#endif

    return 0;
}