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

#ifndef GEARS_META_UTILITY_HPP
#define GEARS_META_UTILITY_HPP

#include <type_traits>

namespace gears {
namespace meta {
/**
 * @ingroup meta
 * @brief Returns a non-const lvalue reference as a const lvalue reference.
 *
 * @param t lvalue reference to turn to const lvalue reference.
 * @return const lvalue reference.
 */
template<typename T>
constexpr const T& as_const(T& t) {
    return t;
}

template<typename T>
constexpr T&& cforward(typename std::remove_reference<T>::type& t) noexcept {
    return static_cast<T&&>(t);
}

/**
 * @ingroup meta
 * @brief constexpr enabled alternative to `std::forward`.
 *
 * @param t variable to forward
 * @tparam T Type of parameter being forwarded.
 * @return `static_cast<T&&>(t)`.
 */
template<typename T>
constexpr T&& cforward(typename std::remove_reference<T>::type&& t) noexcept {
    static_assert(!std::is_lvalue_reference<T>(), "error");
    return static_cast<T&&>(t);
}

/**
 * @ingroup meta
 * @brief constexpr enabled alternative to `std::move`.
 *
 * @param t variable to move
 * @tparam T Type of parameter being enabled to be moved.
 * @return `static_cast<RemoveRef<T>&&>(t)`.
 */
template<typename T>
constexpr typename std::remove_reference<T>::type&& cmove(T&& t) noexcept {
    return static_cast<typename std::remove_reference<T>::type&&>(t);
}
} // meta
} // gears

#endif // GEARS_META_UTILITY_HPP
