cmake_minimum_required(VERSION 3.21)
project(lnxcpplearning)

set(CMAKE_CXX_STANDARD 23)

add_executable(lnxcpplearning main.cpp String.cpp String.h cmake-build-debug/Char.cpp cmake-build-debug/Char.h cmake-build-debug/UnicodeCategory.h cmake-build-debug/CharUnicodeInfo.h Array.h ForwardIterator.h)
