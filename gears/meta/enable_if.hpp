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

#ifndef GEARS_META_ENABLE_IF_HPP
#define GEARS_META_ENABLE_IF_HPP

#include <gears/meta/conditional.hpp>

namespace gears {
namespace meta {
namespace detail {
enum class enabler { _ };
} // detail

/**
 * @defgroup meta_enable_if SFINAE-related Metafunctions
 * @ingroup meta
 * @brief Provides metafunctions that help with the usage of SFINAE.
 * @details The collection of meta functions provided in here are essentially
 * there to help make the usage of `enable_if` easier. A convenience alias
 * named `disable_if_t` is also provided, along with its counterpart metafunction
 * `disable_if`.
 */

/**
 * @ingroup meta_enable_if
 * @brief An unspecified value to assign enable_if_t with.
 */
constexpr auto _ = detail::enabler::_;

/**
 * @ingroup meta_enable_if
 * @brief Template alias for `std::enable_if`
 * @details Template alias for `std::enable_if`. All
 * arguments passed are evaluated as `T::value`. If any
 * of the boolean arguments return false, then the entire
 * thing returns false. Unlike regular `std::enable_if`, you
 * cannot provide a return statement on it. This allows you to
 * use it in template parameters.
 *
 * Example:
 *
 * @code
 * template<typename T, meta::enable_if_t<std::is_integral<T>> = meta::_>
 * @endcode
 */
template<typename... Args>
using enable_if_t = eval<std::enable_if<all<Args...>::value, detail::enabler>>;

/**
 * @ingroup meta_enable_if
 * @brief The negation of `enable_if_t`.
 */
template<typename... Args>
using disable_if_t = eval<std::enable_if<negate<all<Args...>>::value, detail::enabler>>;

/**
 * @ingroup meta_enable_if
 * @brief The negation of enable_if.
 */
template<bool B, typename T>
struct disable_if {
    using type = T;
};

template<typename T>
struct disable_if<true, T> {};

} // meta
} // gears

#endif // GEARS_META_ENABLE_IF_HPP
