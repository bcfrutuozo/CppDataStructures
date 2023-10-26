add_library(helpers "")

target_sources(helpers
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/Timer.cpp
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Algorithm.hpp
        ${CMAKE_CURRENT_LIST_DIR}/Timer.hpp
)

target_include_directories(helpers
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)