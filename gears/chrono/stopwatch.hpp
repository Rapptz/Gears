// The MIT License (MIT)

// Copyright (c) 2012-2013 Danny Y., Rapptz

// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef GEARS_CHRONO_STOPWATCH_HPP
#define GEARS_CHRONO_STOPWATCH_HPP

#include <chrono>

namespace gears {
template<class Clock>
struct basic_stopwatch {
public:
    using time_point = typename Clock::time_point;
    using duration = typename Clock::duration;
    using rep = typename Clock::rep;
    using period = typename Clock::period;
private:
    time_point now{};
    duration elapsed_time = duration::zero();
    bool running = false;
public:
    basic_stopwatch() = default;

    void start() {
        now = Clock::now();
        running = true;
    }

    void stop() {
        if(running) {
            elapsed_time += Clock::now() - now;
            running = false;
        }
    }

    void reset() {
        elapsed_time = duration::zero();
        running = false;
    }

    void restart() {
        elapsed_time = duration::zero();
        now = Clock::now();
        running = true;
    }

    template<typename Duration = std::chrono::milliseconds>
    rep elapsed() {
        if(running)
            return std::chrono::duration_cast<Duration>(elapsed_time + Clock::now() - now).count();
        return std::chrono::duration_cast<Duration>(elapsed_time).count();
    }

    bool is_running() const {
        return running;
    }
};

using stopwatch = basic_stopwatch<std::chrono::high_resolution_clock>;
} // gears

#endif // GEARS_CHRONO_STOPWATCH_HPP