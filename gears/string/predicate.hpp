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

#ifndef GEARS_STRING_PREDICATE_HPP
#define GEARS_STRING_PREDICATE_HPP

#include <locale>

namespace gears {
namespace string {
template<typename CharT = char>
struct is_any_of {
    const CharT* str;
    is_any_of(const CharT* str): str(str) {}
    bool operator()(CharT s) const {
        auto copy = str;
        while(*copy) {
            if(*copy++ == s)
                return true;
        }
        return false;
    }
};

template<typename String>
inline bool iequal(const String& lhs, const String& rhs, const std::locale& loc = std::locale()) {
    if(lhs.length() != rhs.length())
        return false;
    auto i = lhs.cbegin();
    auto j = rhs.cbegin();
    for(; i != lhs.cend() && j != rhs.cend(); ++i, ++j) {
        if(std::toupper(*i, loc) != std::toupper(*j, loc))
            return false;
    }
    return true;
}

template<typename String>
inline bool starts_with(const String& str, const String& other) {
    return str.find(other) == 0;
}

template<typename String>
inline bool istarts_with(const String& str, const String& other, const std::locale& loc = std::locale()) {
    if(other.length() > str.length())
        return false;
    for(unsigned i = 0; i < other.length(); ++i) {
        if(std::toupper(str[i], loc) != std::toupper(other[i], loc))
            return false;
    }
    return true;
}

template<typename String>
inline bool ends_with(const String& str, const String& other) {
    if(str.length() >= other.length())
        return str.compare(str.length() - other.length(), other.length(), other) == 0;
    else
        return false;
}

template<typename String>
inline bool iends_with(const String& str, const String& other, const std::locale& loc = std::locale()) {
    if(str.length() >= other.length()) {
        for(unsigned start = str.length() - other.length(), i = 0; i < other.length(); ++i, ++start) {
            if(std::toupper(str[start], loc) != std::toupper(other[i], loc))
                return false;
        }
        return true;
    }
    else 
        return false;
}

template<typename String>
inline bool contains(const String& str, const String& other) {
    return str.find(other) != String::npos;
}

template<typename String>
inline bool icontains(const String& str, const String& other, const std::locale& loc = std::locale()) {
    auto first = str.cbegin();
    auto last = str.cend();
    auto other_last = other.cend();
    for(; ; ++first) {
        auto it = first;
        for(auto i = other.cbegin(); ; ++i, ++it) {
            if(i == other_last)
                return true;
            if(it == last)
                return false;
            if(std::toupper(*it, loc) != std::toupper(*i, loc))
                break;
        }
    }
}

template<typename String, typename BinaryPredicate>
inline bool all(const String& str, BinaryPredicate&& pred) {
    for(auto&& c : str) {
        if(!pred(c))
            return false;
    }
    return true;
}
} // string
} // gears

#endif // GEARS_STRING_PREDICATE_HPP