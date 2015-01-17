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

#ifndef GEARS_FUNCTIONAL_NUMERICAL_PROPERTIES_HPP
#define GEARS_FUNCTIONAL_NUMERICAL_PROPERTIES_HPP

#include <utility>

namespace gears {
namespace functional {
struct even_type {
    template<typename T>
    constexpr auto operator()(T&& t) const -> decltype(std::forward<T>(t) % 2 == 0) {
        return std::forward<T>(t) % 2 == 0;
    }
};

struct odd_type {
    template<typename T>
    constexpr auto operator()(T&& t) const -> decltype(std::forward<T>(t) % 2 != 0) {
        return std::forward<T>(t) % 2 != 0;
    }
};

/**
 * @ingroup functional_objects
 * @brief Function object checking if a numeric type is even.
 *
 * @details Checks if a numeric instance is even by effectively
 * checking if `t % 2 == 0`.
 *
 * @param t numeric type to check
 * @return generic result of `t % 2 == 0`, usually bool.
 */
constexpr even_type even{};

/**
 * @ingroup functional_objects
 * @brief Function object checking if a numeric type is odd.
 *
 * @details Checks if a numeric instance is odd by effectively
 * checking if `t % 2 != 0`.
 *
 * @param t numeric type to check
 * @return generic result of `t % 2 != 0`, usually bool.
 */
constexpr odd_type odd{};
} // functional
} // gears

#endif // GEARS_FUNCTIONAL_NUMERICAL_PROPERTIES_HPP
