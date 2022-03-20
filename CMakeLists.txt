cmake_minimum_required(VERSION 3.21)
project(CppDataStructures)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(dependencies)

enable_testing()
add_subdirectory(tests)

add_executable(CppDataStructures main.cpp String.cpp String.h Array.h Stack.h Queue.h Timer.cpp Timer.h List.h BidirectionalIterator.h)