add_library(types "")

target_sources(types
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/BitConverter.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Byte.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Char.cpp
        ${CMAKE_CURRENT_LIST_DIR}/CharUnicodeInfo.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Int32.cpp
        ${CMAKE_CURRENT_LIST_DIR}/String.cpp
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/BitConverter.hpp
        ${CMAKE_CURRENT_LIST_DIR}/Boolean.hpp
        ${CMAKE_CURRENT_LIST_DIR}/Byte.hpp
        ${CMAKE_CURRENT_LIST_DIR}/Char.hpp
        ${CMAKE_CURRENT_LIST_DIR}/CharUnicodeInfo.hpp
        ${CMAKE_CURRENT_LIST_DIR}/Double.hpp
        ${CMAKE_CURRENT_LIST_DIR}/Int16.hpp
        ${CMAKE_CURRENT_LIST_DIR}/Int32.hpp
        ${CMAKE_CURRENT_LIST_DIR}/Int64.hpp
        ${CMAKE_CURRENT_LIST_DIR}/Primitives.hpp
        ${CMAKE_CURRENT_LIST_DIR}/SByte.hpp
        ${CMAKE_CURRENT_LIST_DIR}/Single.hpp
        ${CMAKE_CURRENT_LIST_DIR}/String.hpp
        ${CMAKE_CURRENT_LIST_DIR}/StringComparison.hpp
        ${CMAKE_CURRENT_LIST_DIR}/StringSplitOptions.hpp
        ${CMAKE_CURRENT_LIST_DIR}/TypeValue.hpp
        ${CMAKE_CURRENT_LIST_DIR}/UInt16.hpp
        ${CMAKE_CURRENT_LIST_DIR}/UInt32.hpp
        ${CMAKE_CURRENT_LIST_DIR}/UInt64.hpp
        ${CMAKE_CURRENT_LIST_DIR}/UnicodeCategory.hpp
)

target_include_directories(types
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)