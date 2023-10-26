cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(CppDataStructures LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Check platforms
if (CMAKE_HOST_WIN32)
    set(WINDOWS 1)
elseif(CMAKE_HOST_APPLE)
    set(MACOS 1)
elseif(CMAKE_HOST_UNIX)
    set(LINUX 1)
endif()

# Check compilers
MESSAGE( STATUS ">>>>>>>> ${CMAKE_CXX_COMPILER_ID}")
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    MESSAGE( STATUS "Using Clang" )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    MESSAGE( STATUS "Using GNU" )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
    MESSAGE( STATUS "Using Intel" )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    MESSAGE( STATUS "Using MSVC" )
endif()

# Set RPATH
if(CMAKE_HOST_UNIX)
    if(CMAKE_HOST_APPLE)
        SET(CMAKE_CXX_FLAGS "-std=c++23 -O3 -Wl,-rpath,@loader_path")
        SET(CMAKE_INSTALL_RPATH "@loader_path")
    else()
        SET(CMAKE_CXX_FLAGS "-std=c++23 -O3 -Wl,-rpath=$ORIGIN")
        SET(CMAKE_INSTALL_RPATH "$ORIGIN")
    endif()
    SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
endif()

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/charinfo.nlp DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
        ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
        ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
        ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

# defines targets and sources
add_subdirectory(src)

# contains an "external" library we will link to
add_subdirectory(external)

# enable testing and define tests
add_subdirectory(tests)