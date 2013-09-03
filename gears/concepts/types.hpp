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

#ifndef GEARS_CONCEPTS_TYPES_HPP
#define GEARS_CONCEPTS_TYPES_HPP

#include <utility>
#include "alias.hpp"

namespace gears {
namespace detail {
struct is_swappable_impl {
    template<typename T, typename U>
    static auto test(int) -> decltype(std::swap(std::declval<T&>(), std::declval<U&>()), std::true_type{}) {}
    template<typename...>
    static std::false_type test(...);
};
} // detail

template<typename T, typename U = T>
struct is_swappable : TraitOf<detail::is_swappable_impl, T, U> {};

template<typename T, typename U = T>
using Swappable = is_swappable<T, U>;

template<typename T>
using ContextualBool = std::is_constructible<bool, T>;

template<typename T>
using Integral = std::is_integral<T>;

template<typename T>
using FloatingPoint = std::is_floating_point<T>;

template<typename T>
using Signed = std::is_signed<T>;

template<typename T>
using Unsigned = std::is_unsigned<T>;

template<typename T>
using Arithmetic = std::is_arithmetic<T>;

template<typename T>
using Fundamental = std::is_fundamental<T>;

template<typename T>
using Compound = std::is_compound<T>;

template<typename T>
using Pointer = std::is_pointer<T>;

template<typename T>
using LValueReference = std::is_lvalue_reference<T>;

template<typename T>
using RValueReference = std::is_rvalue_reference<T>;

template<typename T>
using Reference = std::is_reference<T>;
} // gears

#endif // GEARS_CONCEPTS_TYPES_HPP