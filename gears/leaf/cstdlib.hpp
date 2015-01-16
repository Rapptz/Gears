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

#ifndef GEARS_LEAF_CSTDLIB_HPP
#define GEARS_LEAF_CSTDLIB_HPP

#include <stdexcept>
#include <type_traits>

namespace gears {
namespace leaf {
template<typename Integer>
struct div_t {
    Integer rem;
    Integer quot;
};

template<typename Integer>
constexpr div_t<Integer> div(Integer x, Integer y) {
    return { x / y, x % y };
}


template<typename Number>
constexpr Number abs(Number number) {
    return number < 0 ? -number : number;
}

namespace detail {
constexpr bool is_digit(const char c) {
    return c >= '0' && c <= '9';
}

template<typename Integral>
constexpr Integral atoi(const char* str, Integral value) {
    return *str == '\0' ?
            value : !is_digit(*str) ?
                    (throw std::invalid_argument("invalid string"), value) : atoi(str + 1, (*str - '0') + value * 10);
}
} // detail

template<typename Integral>
constexpr Integral atoi(const char* str) {
    static_assert(!std::is_floating_point<Integral>::value, "Type to cast must not be a floating point");
    return *str != '-' ?
           detail::atoi(str + (*str == '+'), static_cast<Integral>(0)) :
           static_cast<Integral>(-1) * detail::atoi(str + 1, static_cast<Integral>(0));
}
} // leaf
} // gears

#endif // GEARS_LEAF_CSTDLIB_HPP
