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

#ifndef GEARS_META_TRAITS_HPP
#define GEARS_META_TRAITS_HPP

#include <gears/meta/core.hpp>

namespace gears {
namespace meta {
/**
 * @defgroup meta_traits Miscellaneous Type Traits
 * @ingroup meta
 * @brief Provides miscellaneous type traits that don't have a category.
 * @details The type traits provided here usually are too minor to deserve their
 * own header or category. At this time, they currently include SFINAE-safe
 * `result_of` and a `class_of` type trait.
 */

/**
 * @ingroup meta_traits
 * @brief Deduces the return type of a function call expression in an SFINAE-safe manner.
 */
template<typename Signature, typename Anon = void>
struct result_of {};

template<typename Function, typename... Args>
struct result_of<Function(Args...), void_t<decltype(std::declval<Function>()(std::declval<Args>()...))>> {
    using type = decltype(std::declval<Function>()(std::declval<Args>()...));
};

/**
 * @ingroup meta_traits
 * @brief Template alias for SFINAE-safe `result_of`.
 */
template<typename Signature>
using result_of_t = eval<result_of<Signature>>;

/**
 * @ingroup meta_traits
 * @brief Class of meta function.
 * @details Class of meta function. Evaluates the
 * underlying class of a member function pointer.
 *
 * Example:
 *
 * @code
 * #include <gears/meta.hpp>
 *
 * namespace meta = gears::meta;
 *
 * struct f {
 *     int g() {
 *         return 10;
 *     }
 * };
 *
 * int main() {
 *     // passes static_assert
 *     static_assert(std::is_same<meta::class_of_t<decltype(&f::g)>, f>::value, "...");
 * }
 * @endcode
 */
template<typename T>
struct class_of {};

template<typename Signature, typename Class>
struct class_of<Signature Class::*> : identity<Class> {};

/**
 * @ingroup meta_traits
 * @brief Template alias for `class_of` meta function.
 */
template<typename T>
using class_of_t = eval<class_of<T>>;
} // meta
} // gears

#endif // GEARS_META_TRAITS_HPP
