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

#ifndef GEARS_FUNCTIONAL_COMPARISON_OPERATORS_HPP
#define GEARS_FUNCTIONAL_COMPARISON_OPERATORS_HPP

#include <utility>

namespace gears {
namespace functional {
struct equal_to_type {
    template<typename T, typename U>
    constexpr auto operator()(T&& t, U&& u) const -> decltype(std::forward<T>(t) == std::forward<U>(u)) {
        return std::forward<T>(t) == std::forward<U>(u);
    }
};

struct not_equal_to_type {
    template<typename T, typename U>
    constexpr auto operator()(T&& t, U&& u) const -> decltype(std::forward<T>(t) != std::forward<U>(u)) {
        return std::forward<T>(t) != std::forward<U>(u);
    }
};

struct greater_type {
    template<typename T, typename U>
    constexpr auto operator()(T&& t, U&& u) const -> decltype(std::forward<T>(t) > std::forward<U>(u)) {
        return std::forward<T>(t) > std::forward<U>(u);
    }
};

struct less_type {
    template<typename T, typename U>
    constexpr auto operator()(T&& t, U&& u) const -> decltype(std::forward<T>(t) < std::forward<U>(u)) {
        return std::forward<T>(t) < std::forward<U>(u);
    }
};

struct greater_equal_type {
    template<typename T, typename U>
    constexpr auto operator()(T&& t, U&& u) const -> decltype(std::forward<T>(t) >= std::forward<U>(u)) {
        return std::forward<T>(t) >= std::forward<U>(u);
    }
};

struct less_equal_type {
    template<typename T, typename U>
    constexpr auto operator()(T&& t, U&& u) const -> decltype(std::forward<T>(t) <= std::forward<U>(u)) {
        return std::forward<T>(t) <= std::forward<U>(u);
    }
};

/**
 * @ingroup functional_objects
 * @brief Function object performing equality comparison.
 * 
 * @details Effectively calls `operator==` on two variables in a
 * generic manner. This is an instance of a function object and
 * could be called just like a regular function.
 * 
 * @param t left side to compare
 * @param u right side to compare
 * @return the generic result of `t == u`
 */
constexpr equal_to_type equal_to{};

/**
 * @ingroup functional_objects
 * @brief Function object performing inequality comparison.
 * 
 * @details Effectively calls `operator!=` on two variables in a
 * generic manner. This is an instance of a function object and
 * could be called just like a regular function.
 * 
 * @param t left side to compare
 * @param u right side to compare
 * @return the generic result of `t != u`
 */
constexpr not_equal_to_type not_equal_to{};

/**
 * @ingroup functional_objects
 * @brief Function object performing greater than comparison.
 * 
 * @details Effectively calls `operator>` on two variables in a
 * generic manner. This is an instance of a function object and
 * could be called just like a regular function.
 * 
 * @param t left side to compare
 * @param u right side to compare
 * @return the generic result of `t > u`
 */
constexpr greater_type greater{};

/**
 * @ingroup functional_objects
 * @brief Function object performing less than comparison.
 * 
 * @details Effectively calls `operator<` on two variables in a
 * generic manner. This is an instance of a function object and
 * could be called just like a regular function.
 * 
 * @param t left side to compare
 * @param u right side to compare
 * @return the generic result of `t < u`
 */
constexpr less_type less{};

/**
 * @ingroup functional_objects
 * @brief Function object performing greater than or equal comparison.
 * 
 * @details Effectively calls `operator>=` on two variables in a
 * generic manner. This is an instance of a function object and
 * could be called just like a regular function.
 * 
 * @param t left side to compare
 * @param u right side to compare
 * @return the generic result of `t >= u`
 */
constexpr greater_equal_type greater_equal{};

/**
 * @ingroup functional_objects
 * @brief Function object performing less than or equal comparison.
 * 
 * @details Effectively calls `operator<=` on two variables in a
 * generic manner. This is an instance of a function object and
 * could be called just like a regular function.
 * 
 * @param t left side to compare
 * @param u right side to compare
 * @return the generic result of `t <= u`
 */
constexpr less_equal_type less_equal{};
} // functional
} // gears

#endif // GEARS_FUNCTIONAL_COMPARISON_OPERATORS_HPP
