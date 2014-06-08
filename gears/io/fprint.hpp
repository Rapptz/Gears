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
 * io::fprint(std::cout, std::string("{0} {1} {0}"), 1, 2);
 * // could be shortened to:
 * io::print("{0} {1} {0}", 1, 2);
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
    const auto length = str.size();
    for(decltype(str.size()) i = 0; i < length; ++i) {
        auto&& c = str[i];
        // doesn't start with { so just print it and continue
        if(c != out.widen('{')) {
            out << c;
            continue;
        }

        // at this point, the character c points to {
        // check if we're done printing
        if(i + 1 > length) {
            out << c;
            break;
        }

        // now we're at a sane point where we can work with the format string
        auto j = i + 1;
        unsigned index = 0;

        // check if the next character is a digit
        if(cmp(str[j])) {
            do {
                // since it is, multiply the index
                index = (index * 10) + (str[j++] - out.widen('0'));
            }
            while(j < length && cmp(str[j]));
        }
        else {
            // since it isn't a digit, it doesn't match our format string
            out << str[i];
            continue;
        }

        // now that we're done processing, handle the results
        if(str[j] == out.widen('}')) {
            detail::index_printer(out, index, args);
        }

        i = j;
    }
}
} // io
} // gears

#endif // GEARS_IO_FPRINT_HPP
