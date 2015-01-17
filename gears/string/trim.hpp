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

#ifndef GEARS_STRING_TRIM_HPP
#define GEARS_STRING_TRIM_HPP

#include <gears/string/find.hpp>
#include <gears/string/classification.hpp>

namespace gears {
namespace string {
/**
 * @ingroup string
 * @brief Removes the left part of the string until the predicate is met.
 * @details Removes the left part of the string until the predicate is met.
 *
 * Example:
 * @code
 * auto str = string::trim_left_if("12984713hello world"_s, [](char c) {
 *     return std::isdigit(c);
 * });
 * // str == "hello world"
 * @endcode
 *
 * If the predicate is never met, returns the original string.
 *
 * @param str String to search through.
 * @param pred Predicate to use.
 * @return A string with the left part removed.
 */
template<typename String, typename UnaryPredicate>
inline meta::unqualified_t<String> trim_left_if(String str, UnaryPredicate&& pred) {
    auto pos = find_first_not_of(str, std::forward<UnaryPredicate>(pred));
    if(pos != meta::unqualified_t<String>::npos) {
        return { str.substr(pos) };
    }
    return str;
}

/**
 * @ingroup string
 * @brief Removes the right part of the string until the predicate is met.
 * @details Removes the right part of the string until the predicate is met.
 *
 * Example:
 * @code
 * auto str = string::trim_right_if("hello world18324728361"_s, [](char c) {
 *     return std::isdigit(c);
 * });
 * // str == "hello world"
 * @endcode
 *
 * If the predicate is never met, returns the original string.
 *
 * @param str String to search through.
 * @param pred Predicate to use.
 * @return A string with the right part removed.
 */
template<typename String, typename UnaryPredicate>
inline meta::unqualified_t<String> trim_right_if(String str, UnaryPredicate&& pred) {
    auto pos = find_last_not_of(str, std::forward<UnaryPredicate>(pred));
    if(pos != meta::unqualified_t<String>::npos) {
        return { str.substr(0, pos + 1) };
    }
    return str;
}

/**
 * @ingroup string
 * @brief Removes both the left and the right part of the string given a predicate.
 * @details Removes both the left and the right part of the string given a predicate.
 *
 * Example:
 * @code
 * auto str = string::trim_right_if("123hello world123"_s, [](char c) {
 *     return std::isdigit(c);
 * });
 * // str == "hello world"
 * @endcode
 *
 * @param str The string to search through.
 * @param pred The predicate to use.
 * @return A string with the right and left part removed.
 */
template<typename String, typename UnaryPredicate>
inline meta::unqualified_t<String> trim_if(String&& str, UnaryPredicate&& pred) {
    return trim_left_if(trim_right_if(std::forward<String>(str), pred), pred);
}

/**
 * @ingroup string
 * @brief Removes the space characters from the left of the string.
 * @details Removes the space characters from the left of the string as
 * classified by the locale.
 *
 * @param str The string to trim.
 * @param loc The locale to classify spaces with.
 * @return A string with the left spaces removed.
 */
template<typename String>
inline meta::unqualified_t<String> trim_left(String&& str, const std::locale& loc = std::locale()) {
    return trim_left_if(std::forward<String>(str), is_space(loc));
}

/**
 * @ingroup string
 * @brief Removes the space characters from the right of the string.
 * @details Removes the space characters from the right of the string as
 * classified by the locale.
 *
 * @param str The string to trim.
 * @param loc The locale to classify spaces with.
 * @return A string with the right spaces removed.
 */
template<typename String>
inline meta::unqualified_t<String> trim_right(String&& str, const std::locale& loc = std::locale()) {
    return trim_right_if(std::forward<String>(str), is_space(loc));
}

/**
 * @ingroup string
 * @brief Removes the space characters from both the left and right of the string.
 * @details Removes the space characters from both the left and right of the string as
 * classified by the locale.
 *
 * @param str The string to trim.
 * @param loc The locale to classify spaces with.
 * @return A string with both the left and right spaces removed.
 */
template<typename String>
inline meta::unqualified_t<String> trim(String&& str, const std::locale& loc = std::locale()) {
    return trim_left(trim_right(std::forward<String>(str), loc), loc);
}
} // string
} // gears

#endif // GEARS_STRING_TRIM_HPP
