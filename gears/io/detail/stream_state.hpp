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

#ifndef GEARS_IO_DETAIL_STREAM_STATE_HPP
#define GEARS_IO_DETAIL_STREAM_STATE_HPP

#include <iosfwd>

namespace gears {
namespace io {
namespace detail {
template<typename Char, typename Trait>
struct stream_state {
    using ostream_type = std::basic_ostream<Char, Trait>;
    using istream_type = std::basic_istream<Char, Trait>;
    std::streamsize width = 0;
    std::streamsize precision = 6;
    Char fill = 0x20;

    stream_state() = default;
    stream_state(const stream_state&) = default;

    template<typename Stream>
    stream_state(const Stream& s): width(s.width()), precision(s.precision()), fill(s.fill()) {}

    void reset() {
        width = 0;
        precision = 6;
        fill = 0x20;
    }

    template<typename Stream>
    void apply(Stream& s) {
        s.width(width);
        s.precision(precision);
        s.fill(fill);
    }
};
} // detail
} // io
} // gears

#endif // GEARS_IO_DETAIL_STREAM_STATE_HPP
