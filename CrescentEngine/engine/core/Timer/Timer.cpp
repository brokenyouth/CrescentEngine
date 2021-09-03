//
// Created by manan on 27/07/2021.
//

#include "Timer.h"

namespace crescent
{

    Timer::Timer()
    {
        Reset();
    }

    Timer::Timer(const Timer& timer)
    {

    }


    void Timer::Reset()
    {
        startTime = std::chrono::high_resolution_clock::now();
        frameTime = startTime;
    }

    float Timer::GetDeltaTime() const
    {
        std::chrono::duration<double> time = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - frameTime);
        return (float)time.count();
    }

    float Timer::GetElapsedTime() const
    {
        std::chrono::duration<double> time = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - startTime);
        return (float)time.count();
    }


    Timer::~Timer()
    {

    }

}