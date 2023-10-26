add_executable(Array test_array.cpp)
add_executable(LinkedList test_linkedlist.cpp)
add_executable(List test_list.cpp)
add_executable(Queue test_queue.cpp)
add_executable(Stack test_stack.cpp)

add_test(
        NAME
        Array
        COMMAND
        $<TARGET_FILE:Array>
)

add_test(
        NAME
        LinkedList
        COMMAND
        $<TARGET_FILE:LinkedList>
)

add_test(
        NAME
        List
        COMMAND
        $<TARGET_FILE:List>
)

add_test(
        NAME
        Queue
        COMMAND
        $<TARGET_FILE:Queue>
)

add_test(
        NAME
        Stack
        COMMAND
        $<TARGET_FILE:Stack>
)