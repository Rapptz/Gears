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

#ifndef GEARS_IO_FPRINT_HPP
#define GEARS_IO_FPRINT_HPP

#include "detail/index_printer.hpp"
#include "../string/classification.hpp"
#include <string>

namespace gears {
namespace io {

/**
 * @ingroup io
 * @brief Type-safe iostream alternative to printf
 * @details `fprint` is the type-safe and iostream alternative
 * to `fprintf`. It accepts any ostream type and uses positional
 * arguments rather than format specifiers. Index starts at 0.
 *
 * Example:
 * @code
 * io::fprint(std::cout, "{0} {1} {0}", 1, 2);
 * @endcode
 *
 * would print 1 2 1, with 1 being index 0 and 2 being index 1.
 *
 * If the argument is out of bounds, the function will throw
 * std::out_of_range. There are two specialisations provided for this
 * function, `io::print` and `io::sprint`. `io::print` is the equivalent of
 * `fprint(std::cout, ...)` or `fprint(std::wcout, ...)` depending on the
 * format string passed. io::sprint delegates the output stream to a
 * `std::stringstream` object to return a string, similar to `sprintf`
 *
 * @param out stream to print to
 * @param str format string
 * @param arguments args to print
 * @throws std::out_of_range index in the format string is out of bounds
 */
template<class Elem, class Traits, typename... Args>
inline void fprint(std::basic_ostream<Elem, Traits>& out, const std::basic_string<Elem, Traits>& str, Args&&... arguments) {
    if(sizeof...(arguments) < 1) {
        out << str;
        return;
    }

    auto args = std::make_tuple(std::forward<Args>(arguments)...);

    string::is_digit cmp;

    auto first = str.begin();
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
            detail::index_printer(out, index, args);
            ++check;
        }
        else {
            out << *check;
        }

        first = check;
    }
}
} // io
} // gears

#endif // GEARS_IO_FPRINT_HPP
