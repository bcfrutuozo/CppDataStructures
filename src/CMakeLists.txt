add_executable(cppds main.cpp)

add_subdirectory(types)
add_subdirectory(helpers)
add_subdirectory(collections)

target_link_libraries(cppds
        PRIVATE
        types
        helpers
        collections
)