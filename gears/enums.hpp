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

#ifndef GEARS_ENUMS_HPP
#define GEARS_ENUMS_HPP

#include "enums/operators.hpp"

/**
 * @defgroup enums Enums module
 * @brief Provides support for using enums as bitmasks.
 *
 * @details This module is meant to help with the usage of enums
 * as bitmasks. C++11 has added support for strongly typed enums through
 * the usage of `enum class` or `enum struct`. A big problem with using
 * the strongly typed enums is that the usual operators are unavailable
 * for usage. For example, the following code is not well formed:
 *
 * @code
 * enum class test {
 *     one = 1 << 0,
 *     two = 1 << 1
 * };
 *
 * int main() {
 *     auto x = test::one & test::two;
 * }
 * @endcode
 *
 * The purpose of this module is to aid in the usage of enums by making it
 * a little bit easier than having to define the entire set of operators yourself.
 * To fix the error above, all you have to do is the following:
 *
 * @code
 * #include <gears/enums.hpp>
 * using namespace gears::enums::operators;
 *
 * enum class test {
 *     one = 1 << 0,
 *     two = 1 << 1
 * };
 *
 * int main() {
 *     auto x = test::one & test::two;
 * }
 * @endcode
 */

#endif // GEARS_ENUMS_HPP
