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

#ifndef GEARS_UTILITY_MAYBE_TRAITS_HPP
#define GEARS_UTILITY_MAYBE_TRAITS_HPP

#include "../../meta/alias.hpp"
#include <memory> // addressof

namespace gears {
namespace utility {
namespace detail {
struct has_overloaded_address_of_impl {
    template<typename T>
    static auto test(int) -> decltype(std::declval<T&>().operator&(), std::true_type{}) {}
    template<typename...>
    static std::false_type test(...);
};

template<typename T>
struct has_overloaded_address_of : decltype(has_overloaded_address_of_impl::test<T>(0)) {};

template<typename T, meta::DisableIf<has_overloaded_address_of<T>> = meta::_>
constexpr T* address_of(T& t) noexcept {
    return &t;
}

template<typename T, meta::EnableIf<has_overloaded_address_of<T>> = meta::_>
T* address_of(T& t) noexcept {
    return std::addressof(t);
}
} // detail

template<typename T>
class maybe;

template<typename T>
class maybe<T&>;

template<typename T>
struct is_maybe : std::false_type {};

template<typename T>
struct is_maybe<maybe<T>> : std::true_type {};
} // utility
} // gears

#endif // GEARS_UTILITY_MAYBE_TRAITS_HPP
