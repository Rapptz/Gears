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

#ifndef GEARS_IO_LINES_HPP
#define GEARS_IO_LINES_HPP

#include <gears/detail/addressof.hpp>
#include <istream>
#include <string>
#include <iterator>

namespace gears {
namespace io {
namespace detail {
template<typename CharT = char, typename Traits = std::char_traits<CharT>>
struct line_iterator : std::iterator<std::input_iterator_tag, std::basic_string<CharT, Traits>> {
private:
    std::basic_istream<CharT, Traits>* reader;
    std::basic_string<CharT, Traits> value;
    bool status;
public:
    line_iterator() noexcept: reader(nullptr), status(false) {}
    line_iterator(std::basic_istream<CharT, Traits>& out) noexcept: reader(gears::detail::addressof(out)) {
        status = reader && *reader && std::getline(*reader, value);
    }

    auto operator++() noexcept -> decltype(*this) {
        status = reader && *reader && std::getline(*reader, value);
        return *this;
    }

    line_iterator operator++(int) noexcept {
        auto copy = *this;
        ++(*this);
        return copy;
    }

    auto operator*() noexcept -> decltype(value) {
        return value;
    }

    auto operator->() noexcept -> decltype(gears::detail::addressof(value)) {
        return gears::detail::addressof(value);
    }

    bool operator==(const line_iterator& other) const noexcept {
        return (status == other.status)  && (!status || reader == other.reader);
    }

    bool operator!=(const line_iterator& other) const noexcept {
        return not (*this == other);
    }
};

template<typename CharT, typename Traits>
struct line_reader {
private:
    std::basic_istream<CharT, Traits>& in;
public:
    line_reader(std::basic_istream<CharT, Traits>& in) noexcept: in(in) {}

    line_iterator<CharT, Traits> begin() noexcept {
        return { in };
    }

    line_iterator<CharT, Traits> end() noexcept {
        return { };
    }
};
} // detail

template<typename CharT, typename Traits>
inline detail::line_reader<CharT, Traits> lines(std::basic_istream<CharT, Traits>& in) {
    return { in };
}
} // io
} // gears

#endif // GEARS_IO_LINES_HPP
