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

#ifndef GEARS_META_CONDITIONAL_HPP
#define GEARS_META_CONDITIONAL_HPP

#include "core.hpp"

namespace gears {
namespace meta {
/**
 * @defgroup meta_conditional Conditional Metafunctions
 * @ingroup meta
 * @brief Provides metafunctions that do compile-time conditional statements.
 * @details These metafunctions are mainly used for compile-time type dispatching
 * or condition checking. Unlike other meta-functions that are in `snake_case`, the
 * meta-functions here are all in `CamelCase`.
 */

/**
 * @ingroup meta_conditional
 * @brief Template alias for `std::conditional`.
 * @details Template alias for `std::conditional`. Evaluates
 * the `Condition` as if `Condition::value` was passed.
 *
 * Example:
 *
 * @code
 * // passes the static_assert
 * static_assert(std::is_same<meta::if_<std::is_integral<int>, double&, int&>, double&>::value, "...");
 * @endcode
 */
template<typename Condition, typename Then, typename Else>
using if_ = eval<std::conditional<Condition::value, Then, Else>>;

/**
 * @ingroup meta_conditional
 * @brief Lazy evaluation of `if_`.
 * @details Sometimes lazy evaluation is wanted for certain
 * things. The use of meta::identity with LazyIf typically
 * forces evaluation to be called at a later point.
 * Consider the following code:
 *
 * @code
 * template<typename T>
 * struct has_const_iterator {
 *     // code to check for typename T::const_iterator
 * };
 *
 * template<typename T>
 * struct const_iterator_or_type {
 *     using type = lazy_if<has_const_iterator<T>,
 *                         identity<typename T::const_iterator>,
 *                         identity<T>>;
 * };
 * @endcode
 *
 * When the following code is called (with `has_const_iterator` properly implemented)
 * with a type that doesn't provide `typename T::const_iterator` then no error will happen.
 * So e.g., `const_iterator_or_type<int>` won't fail despite the fact that
 * `typename int::const_iterator` is invalid due to the lazy nature of this metafunction.
 */
template<typename Condition, typename Then, typename Else>
using lazy_if = eval<if_<Condition, Then, Else>>;

/**
 * @ingroup meta_conditional
 * @brief Logical not meta function
 * @details The equivalent of `operator!` for bools
 * except for meta functions. Returns `std::true_type` or
 * `std::false_type`.
 *
 * Example:
 *
 * @code
 * // passes the static_assert
 * static_assert(meta::negate<std::is_integral<float>>::value, "...");
 * @endcode
 *
 * @tparam T Meta function to use logical not on.
 */
template<typename T>
struct negate : boolean<!T::value> {};

/**
 * @ingroup meta_conditional
 * @brief Logical or meta function
 * @details The equivalent of `operator||` for bools
 * except for meta functions. Evaluates it based on the
 * argument's `value`. Returns `std::true_type` or
 * `std::false_type`.
 *
 * @code
 * // passes the static_assert
 * static_assert(meta::any<std::is_integral<int>, std::is_const<float>, std::is_function<int>>::value, "...");
 * @endcode
 *
 * @tparam Args Meta functions to use logical or on.
 */
template<typename... Args>
struct any : boolean<false> {};

template<typename T, typename... Args>
struct any<T, Args...> : if_<T, boolean<true>, any<Args...>> {};

/**
 * @ingroup meta_conditional
 * @brief Logical and meta function
 * @details The equivalent of `operator&&` for bools
 * except for meta functions. Evaluates it based on the
 * argument's `value`. Returns `std::true_type` or
 * `std::false_type`.
 *
 * @code
 * // fails the static_assert
 * static_assert(meta::all<std::is_integral<int>, std::is_const<float>, std::is_function<int>>::value, "...");
 * @endcode
 *
 * @tparam Args Meta functions to use logical and on.
 */
template<typename... Args>
struct all : boolean<true> {};

template<typename T, typename... Args>
struct all<T, Args...> : if_<T, all<Args...>, boolean<false>> {};
} // meta
} // gears

#endif // GEARS_META_CONDITIONAL_HPP
