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

#ifndef GEARS_STRING_LITERALS_HPP
#define GEARS_STRING_LITERALS_HPP

#include <string>

namespace gears {
namespace literals {
inline std::basic_string<wchar_t> operator"" _s(const wchar_t* str, size_t n) {
    return { str, n };
}

inline std::basic_string<char> operator"" _s(const char* str, size_t n) {
    return { str, n };
}

inline std::basic_string<char32_t> operator"" _s(const char32_t* str, size_t n) {
    return { str, n };
}

inline std::basic_string<char16_t> operator"" _s(const char16_t* str, size_t n) {
    return { str, n };
}
} // literals
} // gears


#endif // GEARS_STRING_LITERALS_HPP