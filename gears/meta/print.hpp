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

#ifndef GEARS_META_PRINT_HPP
#define GEARS_META_PRINT_HPP

namespace gears {
namespace meta {
/**
 * @ingroup meta
 * @brief Prints the type of T fully expanded through a warning trigger.
 * @details Prints the type of T fully expanded through a warning trigger.
 * This is compiler specific and so far has only been tested on GCC and Clang.
 * You should use `-Wall` flag to make this work.
 *
 * @tparam T The type to fully expand.
 */
template<typename T>
struct print {
    using type = T;
#ifdef __clang__
    const int x = 1 / (sizeof(T) - sizeof(T));
#else
    enum { x = sizeof(T) > -1 };
#endif
};
} // meta
} // gears

#endif // GEARS_META_PRINT_HPP
