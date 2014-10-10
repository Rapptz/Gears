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

#ifndef GEARS_ADL_ITERATOR_HPP
#define GEARS_ADL_ITERATOR_HPP

#include <iterator>
#include <utility>

namespace gears {
namespace adl {
namespace detail {
using std::begin;
using std::end;

template<typename T>
constexpr auto adl_begin(T&& t) -> decltype(begin(std::declval<T>())) {
    return begin(std::forward<T>(t));
}

template<typename T>
constexpr auto adl_end(T&& t) -> decltype(end(std::declval<T>())) {
    return end(std::forward<T>(t));
}
} // detail

template<typename T>
constexpr auto begin(T&& t) -> decltype(detail::adl_begin(std::declval<T>())) {
    return detail::adl_begin(std::forward<T>(t));
}

template<typename T>
constexpr auto end(T&& t) -> decltype(detail::adl_end(std::declval<T>())) {
    return detail::adl_end(std::forward<T>(t));
}
} // adl
} // gears

#endif // GEARS_ADL_ITERATOR_HPP
