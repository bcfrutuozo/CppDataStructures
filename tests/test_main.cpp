//
// Created by bcfrutuozo on 18/03/2022.
//

#ifndef CPPDATASTRUCTURES_TEST_MAIN_CPP
#define CPPDATASTRUCTURES_TEST_MAIN_CPP

#ifdef __linux__ 
    //linux code goes here
#elif _WIN32
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#else

#endif

//#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp>
#include "test_array.hpp"
#include "test_stack.hpp"
#include "test_queue.hpp"
#include "test_list.hpp"
#include "test_linkedlist.hpp"

int main(int argc, char* argv[])
{
    // your setup ...

    int result = Catch::Session().run(argc, argv);

#if _WIN32
    _CrtDumpMemoryLeaks();
#endif

    return result;
}

#endif //CPPDATASTRUCTURES_TEST_MAIN_CPP