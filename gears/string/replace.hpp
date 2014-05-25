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

#ifndef GEARS_STRING_REPLACE_HPP
#define GEARS_STRING_REPLACE_HPP

#include "../meta/alias.hpp"
#include <cstddef>

namespace gears {
namespace string {
namespace string_replace_detail {
template<typename String>
inline size_t nth_finder(const String& str, const String& find, size_t nth) {
    int start = 0;
    auto pos = str.find(find);
    while(start < nth && pos != String::npos) {
        pos = str.find(find, pos + find.length());
        ++start;
    }
    return pos;
}
} // string_replace_detail

/**
 * @ingroup string
 * @brief Replace first occurrence of the string.
 * @details Replace the first occurrence of the string with another.
 *
 * @param str The string to do the find and replacing on.
 * @param from The string to find.
 * @param to The string to replace with.
 * @return A new string with the replaced occurrence.
 */
template<typename String>
inline meta::Unqualified<String> replace_first(String str, const String& from, const String& to) {
    auto start_pos = str.find(from);
    if(start_pos == String::npos)
        return str;
    str.replace(start_pos, from.length(), to);
    return str;
}

/**
 * @ingroup string
 * @brief Replace last occurrence of the string.
 * @details Replace the last occurrence of the string with another.
 *
 * @param str The string to do the find and replacing on.
 * @param from The string to find.
 * @param to The string to replace with.
 * @return A new string with the replaced occurrence.
 */
template<typename String>
inline meta::Unqualified<String> replace_last(String str, const String& from, const String& to) {
    auto start_pos = str.rfind(from);
    if(start_pos == String::npos)
        return str;
    str.replace(start_pos, from.length(), to);
    return str;
}

/**
 * @ingroup string
 * @brief Replace Nth occurrence of the string.
 * @details Replace the Nth occurrence of the string with another.
 * If the Nth occurrence is not found, then no replacing takes place.
 *
 * @param str The string to do the find and replacing on.
 * @param nth The Nth occurrence.
 * @param from The string to find.
 * @param to The string to replace with.
 * @return A new string with the replaced occurrence.
 */
template<typename String>
inline meta::Unqualified<String> replace_nth(String str, size_t nth, const String& from, const String& to) {
    auto pos = string_replace_detail::nth_finder(str, from, nth);
    if(pos == String::npos)
        return str;
    str.replace(pos, from.length(), to);
    return str;
}

/**
 * @ingroup string
 * @brief Replace all occurrences of the string.
 * @details Replace all occurrences of the string with another.
 *
 * @param str The string to do the find and replacing on.
 * @param from The string to find.
 * @param to The string to replace with.
 * @return A new string with the replaced occurrence.
 */
template<typename String>
inline meta::Unqualified<String> replace_all(String str, const String& from, const String& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != String::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}

/**
 * @ingroup string
 * @brief Erases the first occurrence of the string.
 * @details Erases the first occurrence of the string. When
 * erasing, the string is deleted. It is as if called with
 * `replace` with an empty string.
 *
 * @param str The string to do the searching and erasing on.
 * @param erase The string to erase.
 * @return A new string with the erased occurrences removed.
 */
template<typename String>
inline meta::Unqualified<String> erase_first(String str, const String& erase) {
    auto start_pos = str.find(erase);
    if(start_pos == String::npos)
        return str;
    str.replace(start_pos, erase.length(), "");
    return str;
}

/**
 * @ingroup string
 * @brief Erases the last occurrence of the string.
 * @details Erases the last occurrence of the string. When
 * erasing, the string is deleted. It is as if called with
 * `replace` with an empty string.
 *
 * @param str The string to do the searching and erasing on.
 * @param erase The string to erase.
 * @return A new string with the erased occurrences removed.
 */
template<typename String>
inline meta::Unqualified<String> erase_last(String str, const String& erase) {
    auto start_pos = str.rfind(erase);
    if(start_pos == String::npos)
        return str;
    str.replace(start_pos, erase.length(), "");
    return str;
}

/**
 * @ingroup string
 * @brief Erases the Nth occurrence of the string.
 * @details Erases the Nth occurrence of the string. When
 * erasing, the string is deleted. It is as if called with
 * `replace` with an empty string.
 *
 * @param str The string to do the searching and erasing on.
 * @param nth The Nth occurrence.
 * @param erase The string to erase.
 * @return A new string with the erased occurrences removed.
 */
template<typename String>
inline meta::Unqualified<String> erase_nth(String str, size_t nth, const String& erase) {
    auto pos = string_replace_detail::nth_finder(str, erase, nth);
    if(pos == String::npos)
        return str;
    str.replace(pos, erase.length(), "");
    return str;
}

/**
 * @ingroup string
 * @brief Erases all occurrences of the string.
 * @details Erases all occurrences of the string. When
 * erasing, the string is deleted. It is as if called with
 * `replace` with an empty string.
 *
 * @param str The string to do the searching and erasing on.
 * @param erase The string to erase.
 * @return A new string with the erased occurrences removed.
 */
template<typename String>
inline meta::Unqualified<String> erase_all(String str, const String& erase) {
    size_t start_pos = 0;
    while((start_pos = str.find(erase, start_pos)) != String::npos) {
        str.replace(start_pos, erase.length(), "");
    }
    return str;
}
} // string
} // gears

#endif // GEARS_STRING_REPLACE_HPP
