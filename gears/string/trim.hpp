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

#ifndef GEARS_STRING_TRIM_HPP
#define GEARS_STRING_TRIM_HPP

#include "find.hpp"
#include "classification.hpp"

namespace gears {
namespace string {
template<typename String, typename UnaryPredicate>
inline meta::Unqualified<String> trim_left_if(String&& str, UnaryPredicate&& pred) {
    auto pos = find_first_not_of(std::forward<String>(str), std::forward<UnaryPredicate>(pred));
    if(pos != meta::Unqualified<String>::npos) {
        return { str.substr(pos) };
    }
    return { };
}

template<typename String, typename UnaryPredicate>
inline meta::Unqualified<String> trim_right_if(String&& str, UnaryPredicate&& pred) {
    auto pos = find_last_not_of(std::forward<String>(str), std::forward<UnaryPredicate>(pred));
    if(pos != meta::Unqualified<String>::npos) {
        return { str.substr(0, pos + 1) };
    }
    return { };
}

template<typename String, typename UnaryPredicate>
inline meta::Unqualified<String> trim_if(String&& str, UnaryPredicate&& pred) {
    return trim_left_if(trim_right_if(std::forward<String>(str), pred), pred);
}

template<typename String>
inline meta::Unqualified<String> trim_left(String&& str, const std::locale& loc = std::locale()) {
    return trim_left_if(std::forward<String>(str), is_space(loc));
}

template<typename String>
inline meta::Unqualified<String> trim_right(String&& str, const std::locale& loc = std::locale()) {
    return trim_right_if(std::forward<String>(str), is_space(loc));
}

template<typename String>
inline meta::Unqualified<String> trim(String&& str, const std::locale& loc = std::locale()) {
    return trim_left(trim_right(std::forward<String>(str), loc), loc);
}
} // string
} // gears

#endif // GEARS_STRING_TRIM_HPP
