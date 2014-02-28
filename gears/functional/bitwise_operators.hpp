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

#ifndef GEARS_FUNCTIONAL_BITWISE_OPERATORS_HPP
#define GEARS_FUNCTIONAL_BITWISE_OPERATORS_HPP

#include <utility>

namespace gears {
namespace functional {
struct bit_and_type {
    template<typename T, typename U>
    constexpr auto operator()(T&& t, U&& u) const -> decltype(std::forward<T>(t) & std::forward<U>(u)) {
        return std::forward<T>(t) & std::forward<U>(u);
    }
};

struct bit_or_type {
    template<typename T, typename U>
    constexpr auto operator()(T&& t, U&& u) const -> decltype(std::forward<T>(t) | std::forward<U>(u)) {
        return std::forward<T>(t) | std::forward<U>(u);
    }
};

struct bit_xor_type {
    template<typename T, typename U>
    constexpr auto operator()(T&& t, U&& u) const -> decltype(std::forward<T>(t) ^ std::forward<U>(u)) {
        return std::forward<T>(t) ^ std::forward<U>(u);
    }
};

struct bit_not_type {
    template<typename T>
    constexpr auto operator()(T&& t) const -> decltype(~std::forward<T>(t)) {
        return ~std::forward<T>(t);
    }
};

struct lshift_type {
    template<typename T, typename U>
    constexpr auto operator()(T&& t, U&& u) const -> decltype(std::forward<T>(t) << std::forward<U>(u)) {
        return std::forward<T>(t) << std::forward<U>(u);
    }
};

struct rshift_type {
    template<typename T, typename U>
    constexpr auto operator()(T&& t, U&& u) const -> decltype(std::forward<T>(t) >> std::forward<U>(u)) {
        return std::forward<T>(t) >> std::forward<U>(u);
    }
};


/**
 * @ingroup functional_objects
 * @brief Function object performing bitwise and.
 * 
 * @details Effectively calls `operator&` on two variables in a
 * generic manner. This is an instance of a function object and
 * could be called just like a regular function.
 * 
 * @param t left parameter to bit and
 * @param u right parameter to bit and
 * @return the generic result of `t & u`
 */
constexpr bit_and_type bit_and{};


/**
 * @ingroup functional_objects
 * @brief Function object performing bitwise or.
 * 
 * @details Effectively calls `operator|` on two variables in a
 * generic manner. This is an instance of a function object and
 * could be called just like a regular function.
 * 
 * @param t left parameter to bit or
 * @param u right parameter to bit or
 * @return the generic result of `t | u`
 */
constexpr bit_or_type bit_or{};


/**
 * @ingroup functional_objects
 * @brief Function object performing bitwise xor.
 * 
 * @details Effectively calls `operator^` on two variables in a
 * generic manner. This is an instance of a function object and
 * could be called just like a regular function.
 * 
 * @param t left parameter to xor
 * @param u right parameter to xor
 * @return the generic result of `t ^ u`
 */
constexpr bit_xor_type bit_xor{};


/**
 * @ingroup functional_objects
 * @brief Function object performing bitwise not.
 * 
 * @details Effectively calls `operator~` on a variable in a
 * generic manner. This is an instance of a function object and
 * could be called just like a regular function.
 * 
 * @param t parameter to bit not
 * @return the generic result of `~t`
 */
constexpr bit_not_type bit_not{};


/**
 * @ingroup functional_objects
 * @brief Function object performing bitwise left shift.
 * 
 * @details Effectively calls `operator<<` on two variables in a
 * generic manner. This is an instance of a function object and
 * could be called just like a regular function.
 * 
 * @param t left parameter to left shift
 * @param u right parameter to left shift
 * @return the generic result of `t << u`
 */
constexpr lshift_type lshift{};


/**
 * @ingroup functional_objects
 * @brief Function object performing bitwise right shift.
 * 
 * @details Effectively calls `operator>>` on two variables in a
 * generic manner. This is an instance of a function object and
 * could be called just like a regular function.
 * 
 * @param t left parameter to right shift
 * @param u right parameter to right shift
 * @return the generic result of `t >> u`
 */
constexpr rshift_type rshift{};
} // functional
} // gears


#endif // GEARS_FUNCTIONAL_BITWISE_OPERATORS_HPP