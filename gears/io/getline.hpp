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

#ifndef GEARS_IO_GETLINE_HPP
#define GEARS_IO_GETLINE_HPP

#include <iosfwd>
#include <string>

namespace gears {
namespace io {
/**
 * @ingroup io
 * @brief Reads a string until a predicate is met.
 * @details Reads a string until a predicate is met. This function
 * behaves similarly to `std::getline` except that rather than
 * reading until a newline, it reads until a predicate given.
 * The predicate given must have a signature of `bool(const CharT&)`.
 * While this isn't strictly enforced, it's a good idea to not modify
 * the characters as this might lead to unexpected behaviour.
 *
 * @param in The input stream to read from.
 * @param str String to write to.
 * @param p Predicate to use.
 * @return The input stream.
 */
template<typename CharT, typename Traits, typename Alloc, typename Pred>
inline auto getline_until(std::basic_istream<CharT, Traits>& in, std::basic_string<CharT, Traits, Alloc>& str, Pred p) -> decltype(in) {
    std::ios_base::iostate state = std::ios_base::goodbit;
    bool extracted = false;
    const typename std::basic_istream<CharT, Traits>::sentry s(in, true);
    if(s) {
        try {
            str.erase();
            typename Traits::int_type ch = in.rdbuf()->sgetc();
            for(; ; ch = in.rdbuf()->snextc()) {
                if(Traits::eq_int_type(ch, Traits::eof())) {
                    // eof spotted, quit
                    state |= std::ios_base::eofbit;
                    break;
                }
                else if(p(Traits::to_char_type(ch))) {
                    // predicate met, discard and quit
                    extracted = true;
                    in.rdbuf()->sbumpc();
                    break;
                }
                else if(str.max_size() <= str.size()) {
                    // string too big
                    state |= std::ios_base::failbit;
                    break;
                }
                else {
                    // character valid
                    str.push_back(Traits::to_char_type(ch));
                    extracted = true;
                }
            }
        }
        catch(...) {
            in.setstate(std::ios_base::badbit);
        }
    }

    if(!extracted) {
        state |= std::ios_base::failbit;
    }

    in.setstate(state);
    return in;
}
} // io
} // gears

#endif // GEARS_IO_GETLINE_HPP
