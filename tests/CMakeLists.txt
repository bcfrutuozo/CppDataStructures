add_executable(tests test_array.hpp test_stack.hpp test_main.cpp test_queue.hpp test_list.hpp)
target_link_libraries(tests Catch2::Catch2)