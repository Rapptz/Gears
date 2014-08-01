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

#ifndef GEARS_META_CORE_HPP
#define GEARS_META_CORE_HPP

#include <type_traits>

namespace gears {
namespace meta {
/**
 * @ingroup meta
 * @brief Template alias for getting the type
 */
template<typename T>
using Type = typename T::type;

/**
 * @ingroup meta
 * @brief Template alias for `std::integral_constant`.
 */
template<typename T, T t>
using Const = std::integral_constant<T,t>;


/**
 * @ingroup meta
 * @brief Template alias for integer `std::integral_constant`.
 */
template<int i>
using Integer = Const<int,i>;

/**
 * @ingroup meta
 * @brief Tag used to check if a type is deduced.
 */
struct deduced {};

/**
 * @ingroup meta
 * @brief Metafunction used to check if a type is the same as deduced.
 */
template<typename T>
using is_deduced = std::is_same<T, deduced>;

/**
 * @ingroup meta
 * @brief Identity meta function
 * @details The identity meta function. Typically
 * used for lazy evaluation or forced template parameter
 * evaluation.
 *
 */
template<typename T>
struct identity {
    using type = T;
};

/**
 * @ingroup meta
 * @brief Void meta function.
 * @details Void meta function. Used to swallow
 * arguments and evaluate to void.
 *
 */
template<typename...>
struct void_ {
    using type = void;
};

/**
 * @ingroup meta
 * @brief Template alias for void meta function.
 */
template<typename... T>
using Void = Type<void_<T...>>;

/**
 * @ingroup meta
 * @brief Template alias for `std::integral_constant<bool, B>`.
 */
template<bool B>
using Bool = Const<bool, B>;

/**
 * @ingroup meta
 * @brief Template alias for `std::aligned_storage` with proper alignment.
 */
template<typename T>
using StorageFor = Type<std::aligned_storage<sizeof(T), std::alignment_of<T>::value>>;
} // meta
} // gears

#endif // GEARS_META_CORE_HPP
