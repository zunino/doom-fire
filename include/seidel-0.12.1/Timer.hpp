/*
 * Timer.hpp
 *
 * Created 6 November 2020
*  Last modified 6 November 2020
 *
 * Andre Zunino <neyzunino@gmail.com>
 */

#ifndef SEIDEL_TIMER_HPP
#define SEIDEL_TIMER_HPP

#include <chrono>

#include <SDL2/SDL.h>

namespace sdl {

    struct Timer final {
        typedef std::chrono::milliseconds Duration;
        typedef std::chrono::system_clock Clock;
        typedef std::chrono::time_point<Clock> TimePoint;
        Timer(Duration ttl);
        bool elapsed() const;
        void reset();
    private:
        TimePoint start;
        Duration ttl;
    };

}

#endif
