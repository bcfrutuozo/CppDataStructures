#include "Timer.h"
#include "Array.h"
#include "List.h"
#include <forward_list>
#include <array>

#include <iostream>

int main(int argc, char *argv[]) {

    List<int> a = { 1, 3, 3, 5, 6, 3, 4};
    List<int> b = { 0, 0, 0, 0 };

    a.AddRangeAt(b, 0);

    return 0;
}