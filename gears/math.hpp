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

#ifndef GEARS_MATH_HPP
#define GEARS_MATH_HPP

#include "math/uintx.hpp"
#include "math/generator.hpp"

/**
 * @defgroup math Math module
 * @brief Provides utilities to help with mathematics
 * @details This module provides an implementation of common
 * mathematical algorithms and an infinite precision integer.
 *
 * Example usage:
 *
 * @code
 * #include <gears/math.hpp>
 * #include <iostream>
 *
 * namespace math = gears::math;
 *
 * // needed to use _x user defined literal
 * using namespace gears::math::operators;
 *
 * int main() {
 *     auto lhs = 9384721983748274812387232191827321_x;
 *     auto rhs = 2937189237182973865769137697362736_x;
 *     std::cout << (lhs * rhs) << '\n';
 *     std::cout << math::factorial(10) << '\n';
 * }
 * @endcode
 *
 * Output
 * <pre>
 * 27564704404619880556797005156529364384954680388538087951954412110256
 * 3628800
 * </pre>
 *
 */

#endif // GEARS_MATH_HPP
