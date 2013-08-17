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

#ifndef GEARS_STRING_REPLACE_HPP
#define GEARS_STRING_REPLACE_HPP

#include "../meta/alias.hpp"

namespace gears {
namespace string_replace_detail {
template<typename String>
inline size_t nth_finder(const String& str, const String& find, size_t nth) {
    int start = 0;
    size_t pos = str.find(find);
    while(start < nth && pos != String::npos) {
        pos = str.find(find, pos + find.length());
        ++start;
    }
    return pos;
}
} // string_replace_detail

template<typename String>
inline Unqualified<String> replace_first(String str, const String& from, const String& to) {
    auto start_pos = str.find(from);
    if(start_pos == String::npos) 
        return str;
    str.replace(start_pos, from.length(), to);
    return str;
}

template<typename String>
inline Unqualified<String> replace_last(String str, const String& from, const String& to) {
    auto start_pos = str.rfind(from);
    if(start_pos == String::npos) 
        return str;
    str.replace(start_pos, from.length(), to);
    return str;
}

template<typename String>
inline Unqualified<String> replace_nth(String str, size_t nth, const String& from, const String& to) {
    auto pos = string_replace_detail::nth_finder(str, from, nth);
    if(pos == String::npos)
        return str;
    str.replace(pos, from.length(), to);
    return str;
}

template<typename String>
inline Unqualified<String> replace_all(String str, const String& from, const String& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != String::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}

template<typename String>
inline Unqualified<String> erase_first(String str, const String& erase) {
    auto start_pos = str.find(erase);
    if(start_pos == String::npos)
        return str;
    str.replace(start_pos, erase.length(), "");
    return str;
}

template<typename String>
inline Unqualified<String> erase_last(String str, const String& erase) {
    auto start_pos = str.rfind(erase);
    if(start_pos == String::npos)
        return str;
    str.replace(start_pos, erase.length(), "");
    return str;
}

template<typename String>
inline Unqualified<String> erase_nth(String str, size_t nth, const String& erase) {
    auto pos = string_replace_detail::nth_finder(str, erase, nth);
    if(pos == String::npos)
        return str;
    str.replace(pos, erase.length(), "");
    return str;
}

template<typename String>
inline Unqualified<String> erase_all(String str, const String& erase) {
    size_t start_pos = 0;
    while((start_pos = str.find(erase, start_pos)) != String::npos) {
        str.replace(start_pos, erase.length(), "");
    }
    return str;
}
} // gears

#endif // GEARS_STRING_REPLACE_HPP