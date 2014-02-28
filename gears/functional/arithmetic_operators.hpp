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

#ifndef GEARS_FUNCTIONAL_ARITHMETIC_OPERATORS_HPP
#define GEARS_FUNCTIONAL_ARITHMETIC_OPERATORS_HPP

#include <utility>

namespace gears {
namespace functional {
struct plus_type {
    template<typename T, typename U>
    constexpr auto operator()(T&& t, U&& u) const -> decltype(std::forward<T>(t) + std::forward<U>(u)) {
        return std::forward<T>(t) + std::forward<U>(u);
    }
};

struct minus_type {
    template<typename T, typename U>
    constexpr auto operator()(T&& t, U&& u) const -> decltype(std::forward<T>(t) - std::forward<U>(u)) {
        return std::forward<T>(t) - std::forward<U>(u);
    }
};

struct multiplies_type {
    template<typename T, typename U>
    constexpr auto operator()(T&& t, U&& u) const -> decltype(std::forward<T>(t) * std::forward<U>(u)) {
        return std::forward<T>(t) * std::forward<U>(u);
    }
};

struct divides_type {
    template<typename T, typename U>
    constexpr auto operator()(T&& t, U&& u) const -> decltype(std::forward<T>(t) / std::forward<U>(u)) {
        return std::forward<T>(t) / std::forward<U>(u);
    }
};

struct modulus_type {
    template<typename T, typename U>
    constexpr auto operator()(T&& t, U&& u) const -> decltype(std::forward<T>(t) % std::forward<U>(u)) {
        return std::forward<T>(t) % std::forward<U>(u);
    }
};

/**
 * @ingroup functional_objects
 * @brief Function object performing addition.
 * 
 * @details Effectively calls `operator+` on two variables in a
 * generic manner. This is an instance of a function object and
 * could be called just like a regular function.
 * 
 * @param t left parameter to add
 * @param u right parameter to add
 * @return the generic result of `t + u`
 */
constexpr plus_type plus{};

/**
 * @ingroup functional_objects
 * @brief Function object performing subtraction.
 * 
 * @details Effectively calls `operator-` on two variables in a
 * generic manner. This is an instance of a function object and
 * could be called just like a regular function.
 * 
 * @param t left parameter to subtract
 * @param u right parameter to subtract
 * @return the generic result of `t - u`
 */
constexpr minus_type minus{};

/**
 * @ingroup functional_objects
 * @brief Function object performing multiplication.
 * 
 * @details Effectively calls `operator*` on two variables in a
 * generic manner. This is an instance of a function object and
 * could be called just like a regular function.
 * 
 * @param t left parameter to multiply
 * @param u right parameter to multiply
 * @return the generic result of `t * u`
 */
constexpr multiplies_type multiplies{};

/**
 * @ingroup functional_objects
 * @brief Function object performing division.
 * 
 * @details Effectively calls `operator/` on two variables in a
 * generic manner. This is an instance of a function object and
 * could be called just like a regular function.
 * 
 * @param t left parameter to divide
 * @param u right parameter to divide
 * @return the generic result of `t / u`
 */
constexpr divides_type divides{};

/**
 * @ingroup functional_objects
 * @brief Function object performing modulus.
 * 
 * @details Effectively calls `operator%` on two variables in a
 * generic manner. This is an instance of a function object and
 * could be called just like a regular function.
 * 
 * @param t left parameter to mod
 * @param u right parameter to mod
 * @return the generic result of `t % u`
 */
constexpr modulus_type modulus{};
} // functional
} // gears

#endif // GEARS_FUNCTIONAL_ARITHMETIC_OPERATORS_HPP