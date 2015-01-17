// The MIT License (MIT)

// Copyright (c) 2012-2015 Danny Y., Rapptz

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

#ifndef GEARS_META_EXPAND_HPP
#define GEARS_META_EXPAND_HPP

namespace gears {
namespace meta {
namespace expand_detail {
using expander = int[];
} // expand_detail
} // meta
} // gears

/**
 * @ingroup meta
 * @brief Expands a variadic template.
 * @details Expands a variadic template. This is typically
 * used in combination with indices and/or void functions.
 *
 * Example:
 *
 * @code
 * template<typename T>
 * void f(T t) {
 *     std::cout << t << '\n';
 * }
 *
 * template<typename... Args>
 * void print(Args&&... args) {
 *     GEARS_EXPAND(f(args));
 * }
 * @endcode
 *
 */
#define GEARS_EXPAND(...) void(::gears::meta::expand_detail::expander{((__VA_ARGS__), void(), 0)...})

#endif // GEARS_META_EXPAND_HPP
