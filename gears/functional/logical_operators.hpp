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

#ifndef GEARS_FUNCTIONAL_LOGICAL_OPERATORS_HPP
#define GEARS_FUNCTIONAL_LOGICAL_OPERATORS_HPP

#include <utility>

namespace gears {
namespace functional {
struct logical_and_type {
    template<typename T, typename U>
    constexpr auto operator()(T&& t, U&& u) const -> decltype(std::forward<T>(t) && std::forward<U>(u)) {
        return std::forward<T>(t) && std::forward<U>(u);
    }
};

struct logical_or_type {
    template<typename T, typename U>
    constexpr auto operator()(T&& t, U&& u) const -> decltype(std::forward<T>(t) || std::forward<U>(u)) {
        return std::forward<T>(t) || std::forward<U>(u);
    }
};

struct logical_not_type {
    template<typename T>
    constexpr auto operator()(T&& t) const -> decltype(!std::forward<T>(t)) {
        return !std::forward<T>(t);
    }
};

/**
 * @ingroup functional_objects
 * @brief Function object performing logical and.
 * 
 * @details Effectively calls `operator&&` on two variables in a
 * generic manner. This is an instance of a function object and
 * could be called just like a regular function.
 * 
 * Note that this does **not** short circuit.
 * 
 * @param t left side to check
 * @param u right side to check
 * @return the generic result of `t && u`
 */
constexpr logical_and_type logical_and{};

/**
 * @ingroup functional_objects
 * @brief Function object performing logical or.
 * 
 * @details Effectively calls `operator||` on two variables in a
 * generic manner. This is an instance of a function object and
 * could be called just like a regular function.
 * 
 * Note that this does **not** short circuit.
 * 
 * @param t left side to check
 * @param u right side to check
 * @return the generic result of `t || u`
 */
constexpr logical_or_type logical_or{};

/**
 * @ingroup functional_objects
 * @brief Function object performing logical not.
 * 
 * @details Effectively calls `operator!` on a variable in a
 * generic manner. This is an instance of a function object and
 * could be called just like a regular function.
 * 
 * @param t object to logically negate
 * @return the generic result of `!t`
 */
constexpr logical_not_type logical_not{};
} // functional
} // gears

#endif // GEARS_FUNCTIONAL_LOGICAL_OPERATORS_HPP