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

#ifndef GEARS_STRING_TRANSFORMS_HPP
#define GEARS_STRING_TRANSFORMS_HPP

#include <string>
#include <sstream>
#include "../meta/qualifiers.hpp"

namespace gears {
namespace string {
/**
 * @ingroup string
 * @brief Returns the left portion of a string.
 * @details Returns the left portion of a string by a given
 * shift.
 *
 * If the shift provided is larger than the size, then the original
 * string is returned.
 *
 * @code
 * auto str = string::left("hello world"_s, 6);
 * // str == "hello"
 * @endcode
 *
 * @param str The string to shift left by.
 * @param n The number of places to shift left by.
 * @return A string shifted left.
 */
template<typename String>
inline meta::unqualified_t<String> left(String str, size_t n) {
    if(n >= str.size())
        return str;
    return { str.substr(0, n) };
}

/**
 * @ingroup string
 * @brief Returns the right portion of a string.
 * @details Returns the right portion of a string by a given
 * shift.
 *
 * If the shift provided is larger than the size, then the original
 * string is returned.
 *
 * @code
 * auto str = string::right("hello world"_s, 6);
 * // str == "world"
 * @endcode
 *
 * @param str The string to shift right by.
 * @param n The number of places to shift right by.
 * @return A string shifted right.
 */
template<typename String>
inline meta::unqualified_t<String> right(String str, size_t n) {
    if(n >= str.size())
        return str;
    return { str.substr(str.size() - n) };
}

/**
 * @ingroup string
 * @brief Reverses a string.
 * @details Reverses a string.
 *
 * @param str The string to reverse.
 * @return The reversed string.
 */
template<typename String>
inline meta::unqualified_t<String> reverse(String str) {
    auto first = str.begin();
    auto last = str.end();
    while((first != last) && (first != --last)) {
        using std::swap;
        swap(*first++, *last);
    }
    return str;
}

/**
 * @ingroup string
 * @brief Joins a container together with a separator.
 * @details Joins a container together with a separator.
 *
 * Example:
 *
 * @code
 * #include <gears/string.hpp>
 * #include <iostream>
 * #include <vector>
 *
 * namespace string = gears::string;
 * using namespace gears::string::literals;
 *
 * int main() {
 *     std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7 };
 *     std::cout << string::join(v, ", "_s);
 * }
 * @endcode
 *
 * Output:
 * <pre>
 * 1, 2, 3, 4, 5, 6, 7
 * </pre>
 *
 * @param cont Container to join.
 * @param sep The separator to join with.
 * @return A string with the values of the container separated by the separator.
 */
template<typename String, typename Cont>
inline meta::unqualified_t<String> join(const Cont& cont, const String& sep) {
    auto first = cont.cbegin();
    auto last = cont.cend();
    std::basic_ostringstream<typename String::value_type> ss;
    if(first != last) {
        ss << *first++;
    }
    while(first != last) {
        ss << sep << *first++;
    }
    return { ss.str() };
}

/**
 * @ingroup string
 * @brief Joins a container together with a separator and a filter.
 * @details Joins a container together with a separator when the predicate
 * is met. If the predicate isn't met, then the value will not be in the
 * final string.
 *
 * @param cont Container to join.
 * @param sep The separator to join with.
 * @param pred The predicate used to filter.
 * @return A string with the filtered values and separated by the separator.
 */
template<typename String, typename Cont, typename UnaryPredicate>
inline meta::unqualified_t<String> join_if(const Cont& cont, const String& sep, UnaryPredicate&& pred) {
    auto first = cont.cbegin();
    auto last = cont.cend();
    std::basic_ostringstream<typename String::value_type> ss;

    // Increase first until predicate is met
    while(!pred(*first)) ++first;

    if(first != last) {
        ss << *first++;
    }

    while(first != last) {
        if(pred(*first)) {
            ss << sep << *first++;
            continue;
        }
        ++first;
    }

    return { ss.str() };
}

/**
 * @ingroup string
 * @brief Splits a string into a container.
 * @details Splits a string into a container.
 *
 * Example:
 *
 * @code
 * #include <gears/string.hpp>
 * #include <gears/io/prettyprint.hpp>
 * #include <vector>
 * #include <iterator>
 * #include <iostream>
 *
 * namespace string = gears::string;
 * using namespace gears::string::literals;
 * using namespace gears::io::operators;
 *
 * int main() {
 *     auto str = "hello;one;two;three;four;five"_s;
 *     std::vector<std::string> strings;
 *     string::split(str, ";"_s, std::back_inserter(strings));
 *     std::cout << strings;
 * }
 * @endcode
 *
 * Output:
 * <pre>
 * [hello, one, two, three, four, five]
 * </pre>
 *
 * @param str The string to split.
 * @param sep The substring to split against.
 * @param it An output iterator to insert into.
 * @return The output iterator.
 */
template<typename String, typename OutIt>
inline OutIt split(const String& str, const String& sep, OutIt it) {
    size_t start = 0, end = 0;
    while((end = str.find(sep, start)) != String::npos) {
        *it++ = str.substr(start, end - start);
        start = end + sep.length();
    }
    *it++ = str.substr(start);
    return it;
}
} // string
} // gears

#endif // GEARS_STRING_TRANSFORMS_HPP
