// The MIT License (MIT)

// Copyright (c) 2012-2014 Danny Y., Rapptz

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

#ifndef GEARS_CHRONO_HPP
#define GEARS_CHRONO_HPP

#include "chrono/literals.hpp"
#include "chrono/stopwatch.hpp"

/**
 * @defgroup chrono Chrono module
 *
 * @brief Provides time utilities.
 *
 * @details This module defines utilities that make working with the `<chrono>` header
 * easier and adds new tools for it as well.
 *
 * One of the first things the chrono module is useful for is the creation of
 * `std::chrono::duration`s using the new C++11 user defined literal feature. The table
 * below specifies the literals and their return value.
 *
 * | Literal | Result       |
 * |:-------:|:-------------|
 * | _h      | hours        |
 * | _min    | minutes      |
 * | _s      | seconds      |
 * | _ms     | milliseconds |
 * | _us     | microseconds |
 * | _ns     | nanoseconds  |
 *
 * All of these have `unsigned long long` and `long double` overloads. They reside in `<gears/chrono/literals.hpp>`.
 * Example usage can be found below.
 *
 * @code
 * #include <gears/chrono/literals.hpp>
 * #include <thread>
 * #include <iostream>
 *
 * // this line is required
 * using namespace gears::chrono::literals;
 *
 * void f() {
 *     std::this_thread::sleep_for(1.4_s); // 1.4 seconds
 * }
 *
 * int main() {
 *     std::cout << "Going to sleep for 1.4 seconds...";
 *     f();
 *     std::cout << "\nDone!";
 * }
 * @endcode
 *
 */

#endif // GEARS_CHRONO_HPP
