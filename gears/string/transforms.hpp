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
#include "../meta/alias.hpp"

namespace gears {
namespace string {
template<typename String>
inline meta::Unqualified<String> left(String str, size_t n) {
    if(n >= str.size())
        return str;
    return { str.substr(0, n) };
}

template<typename String>
inline meta::Unqualified<String> right(String str, size_t n) {
    if(n >= str.size())
        return str;
    return { str.substr(str.size() - n) };
}

template<typename String>
inline meta::Unqualified<String> reverse(String str) {
    auto first = str.begin();
    auto last = str.end();
    while((first != last) && (first != --last)) {
        using std::swap;
        swap(*first++, *last);
    }
    return str;
}

template<typename String, typename Cont>
inline meta::Unqualified<String> join(const Cont& cont, const String& sep) {
    auto first = cont.cbegin();
    auto last = cont.cend();
    std::basic_ostringstream<meta::ValueType<String>> ss;
    if(first != last) {
        ss << *first++;
    }
    while(first != last) {
        ss << sep << *first++;
    }
    return { ss.str() };
}

template<typename String, typename Cont, typename UnaryPredicate>
inline meta::Unqualified<String> join_if(const Cont& cont, const String& sep, UnaryPredicate&& pred) {
    auto first = cont.cbegin();
    auto last = cont.cend();
    std::basic_ostringstream<meta::ValueType<String>> ss;

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
