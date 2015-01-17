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

#ifndef GEARS_STRING_FORMAT_HPP
#define GEARS_STRING_FORMAT_HPP

#include <gears/io/fprint.hpp>
#include <sstream>

namespace gears {
namespace string {
template<typename Char, typename Trait, typename Alloc, typename... Args>
inline std::basic_string<Char, Trait> format(const std::basic_string<Char, Trait, Alloc>& str, const Args&... args) {
    std::basic_ostringstream<Char, Trait> out;
    io::detail::fprint(out, str.c_str(), args...);
    return out.str();
}

template<typename Char, typename... Args>
inline std::basic_string<Char> format(const Char* str, const Args&... args) {
    std::basic_ostringstream<Char> out;
    io::detail::fprint(out, str, args...);
    return out.str();
}
} // string
} // gears

#endif // GEARS_STRING_FORMAT_HPP
