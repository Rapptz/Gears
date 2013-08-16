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

#include <string>
#include <locale>

namespace gears {
template<typename CharT, typename Traits>
inline bool iequal(const std::basic_string<CharT, Traits>& lhs, const std::basic_string<CharT, Traits>& rhs, const std::locale& loc = std::locale()) {
    if(lhs.length() != rhs.length())
        return false;
    for(auto i = lhs.cbegin(), auto j = rhs.cbegin(); i != lhs.cend() && j != rhs.cend(); ++i, ++j) {
        if(std::toupper(*i, loc) != std::toupper(*j, loc))
            return false;
    }
    return true;
}

template<typename CharT, typename Traits>
inline bool starts_with(const std::basic_string<CharT, Traits>& str, const std::basic_string<CharT, Traits>& other) {
    return str.find(other) == 0;
}

template<typename CharT, typename Traits>
inline bool istarts_with(const std::basic_string<CharT, Traits>& str, const std::basic_string<CharT, Traits>& other, const std::locale& loc = std::locale()) {
    if(other.length() > str.length())
        return false;
    for(unsigned i = 0; i < other.length(); ++i) {
        if(std::toupper(str[i], loc) != std::toupper(other[i], loc))
            return false;
    }
    return true;
}
} // gears

#endif // GEARS_STRING_PREDICATE_HPP