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

#include <gears/io/detail/stream_state.hpp>
#include <gears/io/detail/tuple.hpp>
#include <string>

namespace gears {
namespace io {
namespace detail {
template<typename Char>
inline std::tuple<size_t, bool> parse_integer(const Char*& str, const Char zero) {
    size_t result = 0;
    bool b = false;
    //             checks if a character is a digit
    while(*str >= zero && *str <= zero + 9) {
        b = true;
        result = (result * 10) + (*str++ - zero);
    }
    return std::make_tuple(result, b);
}

template<typename Char, typename Trait, typename... Args>
inline void fprint(std::basic_ostream<Char, Trait>& out, const Char* str, const Args&... arguments) {
    // format-string ::= "|" <`parameter`> [":" `format-spec`] "|"
    // parameter     ::= <integer>
    // format-spec   ::= [`fill`][`align`][`width`]["." `precision`][`verb`]*
    // fill          ::= "'" <any character>
    // align         ::= "<" | ">" | "^"
    // width         ::= <integer> | "*" <integer>
    // precision     ::= <integer> | "*" <integer>
    // verb          ::= "f" | "e" | "g" | "x" | "b" | "o" | "d" | "u" | "p" | "t"
    auto args = std::tie(arguments...);
    stream_state<Char, Trait> original{out};
    stream_state<Char, Trait> changed;
    auto&& original_flags = out.flags();
    auto func = make_printer(out);
    const Char pipe = out.widen('|');
    const Char zero = out.widen('0');
    size_t position = 0;
    size_t temp_pos = 0;
    bool has_integer = false;

    while(*str) {
        // not a |
        if(!Trait::eq(*str, pipe)) {
            out << *str++;
            continue;
        }

        // at this point -- *str == '|'
        // so just increment it to get to the format-spec
        ++str;

        // escaped | so format-spec is over
        if(Trait::eq(*str, pipe)) {
            out << pipe;
            ++str;
            continue;
        }

        // actual beginning of format-spec
        changed.reset();
        out.flags((out.dec | out.skipws) & ~out.floatfield);
        has_integer = false;

        // retrieve parameter
        std::tie(position, has_integer) = parse_integer(str, zero);

        if(!has_integer) {
            throw std::runtime_error("numeric parameter expected");
        }

        // check if format spec exists
        if(Trait::eq(*str, out.widen(':'))) {
            ++str;

            // check for [fill]
            if(Trait::eq(*str, out.widen('\'')) && *(str + 1)) {
                ++str;
                changed.fill = *str;
                ++str;
            }

            // check for [align]
            if(Trait::eq(*str, out.widen('<'))) {
                out.setf(out.left, out.adjustfield);
                ++str;
            }
            else if(Trait::eq(*str, out.widen('>'))) {
                out.setf(out.right, out.adjustfield);
                ++str;
            }
            else if(Trait::eq(*str, out.widen('^'))) {
                out.setf(out.internal, out.adjustfield);
                ++str;
            }

            // check for [width]
            if(Trait::eq(*str, out.widen('*'))) {
                ++str;
                std::tie(temp_pos, has_integer) = parse_integer(str, zero);
                if(!has_integer) {
                    throw std::runtime_error("expected positional index after *");
                }
                apply(args, temp_pos, make_extractor(changed.width));
            }
            else {
                std::tie(changed.width, std::ignore) = parse_integer(str, zero);
            }

            // check for [.precision]
            if(Trait::eq(*str, out.widen('.'))) {
                ++str;
                if(Trait::eq(*str, out.widen('*'))) {
                    ++str;
                    std::tie(temp_pos, has_integer) = parse_integer(str, zero);
                    if(!has_integer) {
                        throw std::runtime_error("expected positional index after *");
                    }
                    apply(args, temp_pos, make_extractor(changed.precision));
                }
                else {
                    std::tie(changed.precision, has_integer) = parse_integer(str, zero);
                    if(!has_integer) {
                        throw std::runtime_error("expected precision number after .");
                    }
                }
            }

            // check for [verbs]
            // they are as follows:
            // f  - Set std::fixed
            // e  - Set std::scientific
            // u  - Set std::uppercase
            // x  - Set std::hex
            // b  - Set std::showbase
            // o  - Set std::oct
            // d  - Set std::dec
            // t  - Set std::boolalpha
            // +  - Set std::showpos
            // p  - Set std::showpoint
            // g  - Set std::defaultfloat
            while(*str) {
                if(Trait::eq(*str, out.widen('f'))) {
                    out.setf(out.fixed, out.floatfield);
                }
                else if(Trait::eq(*str, out.widen('e'))) {
                    out.setf(out.scientific, out.floatfield);
                }
                else if(Trait::eq(*str, out.widen('g'))) {
                    out.unsetf(out.floatfield);
                }
                else if(Trait::eq(*str, out.widen('u'))) {
                    out.setf(out.uppercase);
                }
                else if(Trait::eq(*str, out.widen('x'))) {
                    out.setf(out.hex, out.basefield);
                }
                else if(Trait::eq(*str, out.widen('o'))) {
                    out.setf(out.oct, out.basefield);
                }
                else if(Trait::eq(*str, out.widen('d'))) {
                    out.setf(out.dec, out.basefield);
                }
                else if(Trait::eq(*str, out.widen('b'))) {
                    out.setf(out.showbase);
                }
                else if(Trait::eq(*str, out.widen('t'))) {
                    out.setf(out.boolalpha);
                }
                else if(Trait::eq(*str, out.widen('p'))) {
                    out.setf(out.showpoint);
                }
                else if(Trait::eq(*str, out.widen('+'))) {
                    out.setf(out.showpos);
                }
                else {
                    // unknown flag
                    break;
                }
                ++str;
            }
        }

        if(Trait::eq(*str, pipe)) {
            // apply the changes
            changed.apply(out);
            // print it out
            apply(args, position, func);
            // revert changed
            original.apply(out);
            ++str;
        }
        else {
            throw std::runtime_error("expected end of format string");
        }
    }

    out.flags(original_flags);
}
} // detail

template<typename Char, typename Trait, typename Alloc, typename... Args>
inline void fprint(std::basic_ostream<Char, Trait>& out, const std::basic_string<Char, Trait, Alloc>& str, const Args&... args) {
    detail::fprint(out, str.c_str(), args...);
}

template<typename Char, typename Trait, typename... Args>
inline void fprint(std::basic_ostream<Char, Trait>& out, const Char* str, const Args&... args) {
    detail::fprint(out, str, args...);
}
} // io
} // gears

#endif // GEARS_IO_FPRINT_HPP
