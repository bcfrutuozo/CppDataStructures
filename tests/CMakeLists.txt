add_executable(tests test_array.hpp test_stack.hpp test_main.cpp)
target_link_libraries(tests Catch2::Catch2)