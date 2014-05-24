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
namespace chrono {
template<typename Clock>
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

    /**
     * @brief Starts the stopwatch
     * 
     */
    void start() {
        now = Clock::now();
        running = true;
    }

    /**
     * @brief Stops the stopwatch
     * 
     */ 
    void stop() {
        if(running) {
            elapsed_time += Clock::now() - now;
            running = false;
        }
    }

    /**
     * @brief Resets the stopwatch
     * @details Resets the stopwatch and pauses it. Meaning that it
     * sets the elapsed time to zero and the post-condition of #is_running
     * is false.
     * 
     * @see restart
     */
    void reset() {
        elapsed_time = duration::zero();
        running = false;
    }

    /**
     * @brief Restarts the stopwatch
     * @details Restarts the stopwatch, meaning that it sets the elapsed
     * time to zero, and starts the stopwatch again. This is equivalent to
     * doing the following:
     * 
     * @code
     * my_stopwatch.reset();
     * my_stopwatch.start();
     * @endcode
     * 
     * @see reset
     */
    void restart() {
        elapsed_time = duration::zero();
        now = Clock::now();
        running = true;
    }

    /**
     * @brief Returns the elapsed time.
     * @details The elapsed time is considered the time since the stopwatch was
     * started via the #start member function. Consecutive calls to elapsed 
     * would not stop the watch and would simply return the elapsed time since the 
     * starting point.
     * 
     * @tparam Duration The duration to cast the elapsed time to. Defaults to `std::chrono::milliseconds`.
     * 
     * @return Elapsed time since the stopwatch started.
     */
    template<typename Duration = std::chrono::milliseconds>
    rep elapsed() {
        if(running)
            return std::chrono::duration_cast<Duration>(elapsed_time + Clock::now() - now).count();
        return std::chrono::duration_cast<Duration>(elapsed_time).count();
    }

    /**
     * @brief Checks if the stopwatch is running
     * 
     */
    bool is_running() const {
        return running;
    }
};

using stopwatch = basic_stopwatch<std::chrono::high_resolution_clock>;
} // chrono
} // gears

/**
 * @struct gears::chrono::basic_stopwatch
 * @ingroup chrono
 * @brief A basic stopwatch for measuring time.
 * 
 * @tparam Clock The internal clock to use to calculate time
 * 
 * basic_stopwatch is a class that defines the most basic stopwatch representation.
 * It's underlying clock can be configured through its template parameter to give you the
 * most flexibility desired. 
 * 
 * For convenience, a typedef named `stopwatch` is provided that defaults to 
 * `std::chrono::high_resolution_clock` as the internal clock used.
 * 
 * Example usage:
 * 
 * @code
 * #include <gears/chrono.hpp>
 * #include <thread>
 * #include <iostream>
 * 
 * namespace ch = gears::chrono;
 * 
 * void f() {
 *     using namespace ch::literals;
 *     std::this_thread::sleep_for(1.16_s);
 * }
 * 
 * int main() {
 *     ch::stopwatch w;
 *     w.start();
 *     f();
 *     w.stop();
 *     std::cout << w.elapsed() << ' ' << w.elapsed<std::chrono::seconds>();
 * }
 * @endcode
 * 
 * Possible Output:
 * <pre>1159 1</pre>
 */

#endif // GEARS_CHRONO_STOPWATCH_HPP