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

#ifndef GEARS_FORMAT_SPRINT_HPP
#define GEARS_FORMAT_SPRINT_HPP

#include <string>
#include <sstream>
#include "detail/index_printer.hpp"
#include "../string/classification.hpp"

namespace gears {
template<typename CharT, size_t N, typename... Args>
inline std::basic_string<CharT> sprint(const CharT (&str)[N], Args&&... arguments) {
    if(sizeof...(Args) < 1)
        return { str, N };

    auto args = std::make_tuple(std::forward<Args>(arguments)...);
    std::basic_ostringstream<CharT> out;

    is_digit cmp;

    auto first = str;
    size_t index = 0;

    while(*first) {
        if(*first != out.widen('{')) {
            out << *first++;
            continue;
        }

        auto check = first;

        // Handle special cases
        if(!*(++check) || *check == out.widen('}')) {
            out << *first++;
            continue;
        }

        index = 0;
        while(*check && cmp(*check)) {
            index = (index * 10) + (*check++ - out.widen('0'));
        }

        if(*check == out.widen('}')) {
            format_detail::index_printer(out, index, args);
            ++check;
        }
        else {
            out << *check;
        }

        first = check;
    }

    return out.str();
}
} // gears

#endif // GEARS_FORMAT_SPRINT_HPP