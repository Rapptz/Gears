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

#ifndef GEARS_IO_PRINT_HPP
#define GEARS_IO_PRINT_HPP

#include "fprint.hpp"
#include <iostream>
#include <sstream>

namespace gears {
namespace io {
template<typename... Args>
inline void print(const std::string& str, Args&&... args) {
    fprint(std::cout, str, std::forward<Args>(args)...);
}

template<typename... Args>
inline void print(const std::wstring& str, Args&&... args) {
    fprint(std::wcout, str, std::forward<Args>(args)...);
}

template<typename Elem, typename Traits, typename... Args>
inline std::basic_string<Elem, Traits> sprint(const std::basic_string<Elem, Traits>& str, Args&&... args) {
    std::basic_ostringstream<Elem, Traits> out;
    fprint(out, str, std::forward<Args>(args)...);
    return out.str();
}
} // io
} // gears

#endif // GEARS_IO_PRINT_HPP
