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

#ifndef GEARS_META_QUALIFIERS_HPP
#define GEARS_META_QUALIFIERS_HPP

#include <gears/meta/core.hpp>

namespace gears {
namespace meta {
/**
 * @defgroup meta_qualifiers Type Qualifiers Metafunctions
 * @ingroup meta
 * @brief Provides metafunctions that deal with addition or removal of type qualifiers.
 * @details The collection of meta functions are mainly there to provide the removal
 * of type qualifiers. Which in this case include `const`, `volatile`, pointers,
 * references, and `signed` or `unsigned`.
 */

/**
 * @ingroup meta_qualifiers
 * @brief Template alias for `std::decay`.
 */
template<typename T>
using decay_t = eval<std::decay<T>>;

/**
 * @ingroup meta_qualifiers
 * @brief Template alias for `std::remove_reference`.
 */
template<typename T>
using remove_reference_t = eval<std::remove_reference<T>>;

/**
 * @ingroup meta_qualifiers
 * @brief Template alias for `std::remove_cv`.
 */
template<typename T>
using remove_cv_t = eval<std::remove_cv<T>>;

/**
 * @ingroup meta_qualifiers
 * @brief Template alias for `std::remove_const`.
 */
template<typename T>
using remove_const_t = eval<std::remove_const<T>>;

/**
 * @ingroup meta_qualifiers
 * @brief Template alias for `std::remove_volatile`.
 */
template<typename T>
using remove_volatile_t = eval<std::remove_volatile<T>>;

/**
 * @ingroup meta_qualifiers
 * @brief Template alias for `std::remove_all_extents`.
 */
template<typename T>
using remove_all_extents_t = eval<std::remove_all_extents<T>>;

/**
 * @ingroup meta_qualifiers
 * @brief Template alias for `std::remove_pointer`.
 */
template<typename T>
using remove_pointer_t = eval<std::remove_pointer<T>>;

/**
 * @ingroup meta_qualifiers
 * @brief Template alias for `std::add_lvalue_reference`.
 */
template<typename T>
using add_lvalue_reference_t = eval<std::add_lvalue_reference<T>>;

/**
 * @ingroup meta_qualifiers
 * @brief Template alias for `std::add_rvalue_reference`.
 */
template<typename T>
using add_rvalue_reference_t = eval<std::add_rvalue_reference<T>>;

/**
 * @ingroup meta_qualifiers
 * @brief Template alias for `std::add_cv`.
 */
template<typename T>
using add_cv_t = eval<std::add_cv<T>>;

/**
 * @ingroup meta_qualifiers
 * @brief Template alias for `std::add_const`.
 */
template<typename T>
using add_const_t = eval<std::add_const<T>>;

/**
 * @ingroup meta_qualifiers
 * @brief Template alias for `std::add_volatile`.
 */
template<typename T>
using add_volatile_t = eval<std::add_volatile<T>>;

/**
 * @ingroup meta_qualifiers
 * @brief Template alias for `std::add_pointer`.
 */
template<typename T>
using add_pointer_t = eval<std::add_pointer<T>>;

/**
 * @ingroup meta_qualifiers
 * @brief Template alias for `std::make_signed`.
 */
template<typename T>
using make_signed_t = eval<std::make_signed<T>>;

/**
 * @ingroup meta_qualifiers
 * @brief Template alias for `std::make_unsigned`.
 */
template<typename T>
using make_unsigned_t = eval<std::make_unsigned<T>>;

/**
 * @ingroup meta_qualifiers
 * @brief Template alias that removes all cv and ref qualifiers.
 */
template<typename T>
using unqualified_t = typename unqualified<T>::type;
} // meta
} // gears

#endif // GEARS_META_QUALIFIERS_HPP
