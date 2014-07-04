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
 * // or
 * io::fprint(std::cout, "{0} {1} {0}"_s, 1, 2);
 * @endcode
 *
 * would print 1 2 1, with 1 being index 0 and 2 being index 1.
 *
 * If the argument is out of bounds, the function will throw
 * std::out_of_range. There are two specialisations provided for this
 * function, `io::print` and `io::sprint`. `io::print` is the equivalent of
 * `fprint(std::cout, ...)` or `fprint(std::wcout, ...)` depending on the
 * format string passed. io::sprint delegates the output stream to a
 * `std::stringstream` object to return a string, similar to `sprintf`.
 *
 * The format string is currently:
 *
 * @code
 * {index[,alignment][:format]}
 * @endcode
 *
 * Where:
 *
 * `index` is the required positional argument of the string.
 * If the positional argument is not found, then an exception is
 * thrown.
 *
 * `alignment` is an optional signed integer that dictates whether to
 * align left or right. A negative value aligns left, as if calling
 * `std::left` and a positive value will align right as if calling
 * `std::right`. The comma is required to specify the alignment, e.g.
 * `{0,-10}` or `{0,10}`.
 *
 * `format` is an optional format specifier that dictates how to format
 * the string. The format specifier has the syntax of `:CN` where `C` is
 * a character dictating the format and `N` is the precision. The `C`
 * argument of the format specifier is required to use the `N`
 * argument. The N argument is the equivalent of `std::setprecision(N)`.
 *
 * The format specifiers and their equivalences are as follows:
 *
 *
 * | Specifier | Equivalent        | Notes                            |
 * |:---------:|:------------------|:---------------------------------|
 * | F         | `std::fixed`      |                                  |
 * | E         | `std::scientific` | `std::uppercase` is enabled      |
 * | e         | `std::scientific` | `std::uppercase` is disabled     |
 * | O         | `std::oct`        |                                  |
 * | X         | `std::hex`        | `std::uppercase` is enabled      |
 * | x         | `std::hex`        | `std::uppercase` is disabled     |
 * | B         | `std::boolalpha`  |                                  |
 * | S         | `std::showpos`    |                                  |
 *
 *
 * In order to escape the `{` character, you have to insert another
 * one. So for example:
 *
 * @code
 * io:print("{{0}", 1);
 * // prints {0}
 * @endcode
 *
 * There is no need to escape the `}` character as it is not used to delimit
 * anything.
 *
 * @param out stream to print to
 * @param str format string
 * @param arguments args to print
 * @throws std::out_of_range index in the format string is out of bounds
 * @throws std::runtime_error invalid format string
 */
template<class Elem, class Traits, typename... Args>
inline void fprint(std::basic_ostream<Elem, Traits>& out, const std::basic_string<Elem, Traits>& str, Args&&... arguments) {
    if(sizeof...(arguments) < 1) {
        out << str;
        return;
    }

    auto args = std::make_tuple(std::forward<Args>(arguments)...);

    string::is_digit cmp;
    auto&& length = str.size();
    auto&& original_width = out.width();
    std::ios_base::fmtflags original_format = out.flags();
    auto&& original_precision = out.precision();

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

        // check the next characters
        auto j = i + 1;
        unsigned index = 0;
        decltype(out.width()) width = 0;
        decltype(out.precision()) precision = 0;
        auto format = original_format;

        // escaped character
        if(str[j] == out.widen('{')) {
            out << str[i];
            i = j;
            continue;
        }

        // now we're at a sane point where we can work with the format string
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
            throw std::runtime_error("invalid format string specified");
        }

        // check if alignment argument exists
        if(str[j] == out.widen(',')) {
            // check if the next character is valid
            if(j + 1 < length) {
                // check if the alignment is left or right
                if(str[j + 1] == out.widen('-')) {
                    format |= out.left;
                    // increment by two to get to the numerical section
                    j += 2;
                }
                else {
                    format |= out.right;
                    ++j;
                }
                // check if the next character is a digit
                if(j < length && cmp(str[j])) {
                    do {
                        // since it is, multiply the width
                        width = (width * 10) + (str[j++] - out.widen('0'));
                    }
                    while(j < length && cmp(str[j]));
                }
                else {
                    // invalid format string found
                    throw std::runtime_error("invalid format string specified");
                }

            }
        }

        // check if format specifier exists
        if(str[j] == out.widen(':')) {
            // check if the character is valid
            if(j + 1 < length) {
                auto&& specifier = str[j + 1];
                switch(specifier) {
                case 'F':
                    format |= out.fixed;
                    break;
                case 'O':
                    format = (format & ~out.basefield) | out.oct;
                    break;
                case 'x':
                    format = (format & ~out.basefield) | out.hex;
                    break;
                case 'X':
                    format = (format & ~out.basefield) | out.hex | out.uppercase;
                    break;
                case 'E':
                    format |= out.scientific | out.uppercase;
                    break;
                case 'e':
                    format |= out.scientific;
                    break;
                case 'B':
                    format |= out.boolalpha;
                    break;
                case 'S':
                    format |= out.showpos;
                    break;
                default:
                    throw std::runtime_error("no such format specifier found");
                    break;
                }
                j += 2;

                // handle precision specifier
                if(j < length && cmp(str[j])) {
                    do {
                        precision = (precision * 10) + (str[j++] - out.widen('0'));
                    }
                    while(j < length && cmp(str[j]));
                }
            }
        }

        // now that we're done processing, handle the results
        if(str[j] == out.widen('}')) {
            out.flags(format);
            out.width(width);
            out.precision(precision);
            detail::index_printer(out, index, args);
            out.width(original_width);
            out.flags(original_format);
            out.precision(original_precision);
            i = j;
        }
    }
}
} // io
} // gears

#endif // GEARS_IO_FPRINT_HPP
