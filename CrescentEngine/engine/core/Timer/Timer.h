//
// Created by manan on 27/07/2021.
//

#ifndef CRESCENTENGINE_TIMER_H
#define CRESCENTENGINE_TIMER_H


#include <chrono>

namespace crescent
{

    class Timer
    {
    public:
        Timer();
        Timer(const Timer& timer);
        ~Timer();

        void		Reset();
        float		GetDeltaTime() const;
        float		GetElapsedTime() const;

    protected:
        std::chrono::high_resolution_clock::time_point startTime;
        std::chrono::high_resolution_clock::time_point frameTime;
    };

}

#endif //CRESCENTENGINE_TIMER_H
