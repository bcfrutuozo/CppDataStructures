add_library(collections "")

set_target_properties(collections PROPERTIES LINKER_LANGUAGE CXX)

target_sources(collections
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Array.hpp
        ${CMAKE_CURRENT_LIST_DIR}/BidirectionalIterator.hpp
        ${CMAKE_CURRENT_LIST_DIR}/LinkedList.hpp
        ${CMAKE_CURRENT_LIST_DIR}/List.hpp
        ${CMAKE_CURRENT_LIST_DIR}/Queue.hpp
        ${CMAKE_CURRENT_LIST_DIR}/Stack.hpp
)

target_include_directories(collections
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)