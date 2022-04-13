cmake_minimum_required(VERSION 3.21)
project(CppDataStructures)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(dependencies)

enable_testing()
add_subdirectory(tests)


file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/charinfo.nlp DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


add_executable(CppDataStructures main.cpp String.h String.cpp Array.h Stack.h Queue.h Timer.cpp Timer.h List.h BidirectionalIterator.h LinkedList.h StringSplitOptions.h StringComparison.h UnicodeCategory.h Char.h TypeValue.h Int32.h CharUnicodeInfo.h Boolean.h Byte.h SByte.h Int16.h UInt16.h UInt32.h Int64.h UInt64.h Double.h Single.h CharUnicodeInfo.cpp Int32.cpp Char.cpp Byte.cpp NumberStyles.h Number.h Number.cpp Decimal.cpp Decimal.h BitConverter.h BitConverter.cpp "NumberFormatter.hpp")