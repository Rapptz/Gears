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

#ifndef GEARS_IO_HPP
#define GEARS_IO_HPP

#include "io/prettyprint.hpp"
#include "io/print.hpp"
#include "io/lines.hpp"
#include "io/getline.hpp"

/**
 * @defgroup io Input/Output module
 *
 * @brief Provides utilities to aid with usage of iostreams.
 *
 * @details This module provides tools to help with iostreams, including
 * prettyprinting, typesafe printf and more.
 *
 * Prettyprinting is provided in the `<gears/io/prettyprint.hpp>` header.
 * It provides pretty printing for containers, tuples, and pairs. In order
 * to enable the usage of prettyprinting, you need to use
 * `using namespace gears::io::operators`. The list of outputs is as follows:
 *
 * | Type         | Output of `operator<<` |
 * |:------------:|:-----------------------|
 * | `std::pair`  | (a, b)                 |
 * | Containers   | [a, b, ..., n]         |
 * | `std::tuple` | (a, b, ..., n)         |
 *
 * Example usage:
 *
 * @code
 * #include <gears/io.hpp>
 * #include <vector>
 *
 * namespace io = gears::io;
 *
 * // needed for operator<< of standard library types
 * using namespace gears::io::operators;
 *
 * int main() {
 *     std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
 *     io::print("{0} + {0} = {1}\n", v.front(), v[1]);
 *
 *     // note: generic operator<< doesn't work with io::print
 *     std::cout << v;
 * }
 * @endcode
 *
 * Output:
 * <pre>
 * 1 + 1 = 2
 * [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
 * </pre>
 *
 */

#endif // GEARS_IO_HPP
