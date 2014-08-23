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

#ifndef GEARS_META_CONST_CSTDLIB_HPP
#define GEARS_META_CONST_CSTDLIB_HPP

#include <stdexcept>
#include <type_traits>

/**
 * @defgroup constexpr_cstdlib `constexpr`-enabled `<cstdlib>`.
 * @ingroup constexpr
 * @brief Provides `constexpr` functions found in `<cstdlib>`.
 * @details This submodule's purpose is to provide some of the old
 * C functions found in `<cstdlib>` with a `constexpr` interface. As
 * a result of this, all the functions are generalised. That is, there
 * will be no type suffixes for ad-hoc function overloading. Note, not all
 * functions are provided either.
 */

namespace gears {
namespace meta {
/**
 * @ingroup constexpr_cstdlib
 * @brief A structure that represents the result of `div`.
 * @details A structure that represents the result of the
 * `div` function.
 *
 * @tparam Integer The internal integer type.
 */
template<typename Integer>
struct div_t {
    Integer rem;    ///< Represents the remainder, i.e. rem = x / y
    Integer quot;   ///< Represents the quotient, i.e. quot = x % y
};

/**
 * @ingroup constexpr_cstdlib
 * @brief Computes the quotient and remainder of two integers.
 * @details Computes the quotient and remainder of two integers.
 * The integral type must have `operator/` and `operator%` defined
 * for this function to work. The return value is the `div_t` struct
 * containing the remainder and quotient.
 *
 * @param x The left hand side of the expression.
 * @param y The right hand side of the expression.
 * @return div_t containing the remainder and quotient.
 */
template<typename Integer>
constexpr div_t<Integer> div(Integer x, Integer y) {
    return { x / y, x % y };
}


/**
 * @ingroup constexpr_cstdlib
 * @brief Computes the absolute value of a number.
 * @details Computes the absolute value of a number.
 * This just uses the naive implementation of
 * `number < 0 ? -number : number;` which is a valid
 * `constexpr` program. The behaviour is undefined if
 * the number cannot be represented in which case on a
 * conforming compiler would be undefined behaviour.
 *
 * @param number The number to turn to an absolute value.
 * @return The absolute value of the number.
 */
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

/**
 * @ingroup constexpr_cstdlib
 * @brief Converts a null terminated string to an integer type.
 * @details Converts a null terminated string to an integer type.
 * The string must be all digits (i.e. in the range of '0' and '9'). If
 * the string isn't full of digits, then an exception is thrown which
 * is a compile time error if used in a constant expression. If the number
 * starts with +, then the string is processed as a positive number. If the
 * number string starts with - however, then the result of the conversion will
 * be multiplied with `static_cast<Integral>(-1)`.
 *
 * @param str The numeric string to convert to a digit.
 * @tparam Integral The integral type to convert to. Must not be a floating point.
 * @return The string converted into an integral type.
 */
template<typename Integral>
constexpr Integral atoi(const char* str) {
    static_assert(!std::is_floating_point<Integral>::value, "Type to cast must not be a floating point");
    return *str != '-' ?
           detail::atoi(str + (*str == '+'), static_cast<Integral>(0)) :
           static_cast<Integral>(-1) * detail::atoi(str + 1, static_cast<Integral>(0));
}
} // meta
} // gears

#endif // GEARS_META_CONST_CSTDLIB_HPP
