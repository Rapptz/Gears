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

#ifndef GEARS_STRING_CASE_HPP
#define GEARS_STRING_CASE_HPP

#include <locale>
#include "../meta/alias.hpp"

namespace gears {
namespace string {
/**
 * @ingroup string
 * @brief Turns a string to lower case
 * @details Turns a string to lower case with the provided locale.
 *
 * @param str String to transform to lower case.
 * @param loc The locale to use.
 * @return the lower case string
 */
template<typename String>
inline meta::Unqualified<String> to_lower(String str, const std::locale& loc = std::locale()) {
    for(auto&& c : str) {
        c = std::tolower(c, loc);
    }
    return str;
}

/**
 * @ingroup string
 * @brief Turns a string to upper case
 * @details Turns a string to upper case with the provided locale.
 *
 * @param str String to transform to upper case.
 * @param loc The locale to use.
 * @return the upper case string
 */
template<typename String>
inline meta::Unqualified<String> to_upper(String str, const std::locale& loc = std::locale()) {
    for(auto&& c : str) {
        c = std::toupper(c, loc);
    }
    return str;
}

/**
 * @ingroup string
 * @brief Checks if a string is all lower case.
 * @details Checks if a string is all lower case with the provided locale.
 *
 * @param str String to search through
 * @param loc The locale to use.
 * @return `true` is all characters are lower case, `false` otherwise.
 */
template<typename String>
inline bool is_all_lower(const String& str, const std::locale& loc = std::locale()) {
    for(auto&& c : str) {
        if(c != std::tolower(c, loc))
            return false;
    }
    return true;
}

/**
 * @ingroup string
 * @brief Checks if a string is all upper case.
 * @details Checks if a string is all upper case with the provided locale.
 *
 * @param str String to search through
 * @param loc The locale to use.
 * @return `true` is all characters are upper case, `false` otherwise.
 */
template<typename String>
inline bool is_all_upper(const String& str, const std::locale& loc = std::locale()) {
    for(auto&& c : str) {
        if(c != std::toupper(c, loc))
            return false;
    }
    return true;
}
} // string
} // gears

#endif // GEARS_STRING_CASE_HPP
