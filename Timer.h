//
// Created by bcfrutuozo on 18/03/2022.
//

#ifndef CPPDATASTRUCTURES_TIMER_H
#define CPPDATASTRUCTURES_TIMER_H

#include "Platform.h"

#include <chrono>

class Timer {

private:

    std::chrono::steady_clock::time_point last;

public:

    Timer() noexcept;

    float Mark() noexcept;

    float Peek() const noexcept;
};


#endif //CPPDATASTRUCTURES_TIMER_H
