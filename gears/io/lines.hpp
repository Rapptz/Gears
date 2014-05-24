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

#ifndef GEARS_IO_LINES_HPP
#define GEARS_IO_LINES_HPP

#include <istream>
#include <string>
#include <iterator>

namespace gears {
namespace io {
/**
 * @ingroup io
 * @brief Iterator that iterates through stdin lines.
 * @details An iterator that iterates through lines given by stdin such as
 * `std::cin`, `std::ifstream`, and `std::istringstream`. This iterator is basically
 * a wrapper around `std::getline` and `std::istream`. This should not be used directly.
 *
 * @tparam CharT Underlying character type of the string.
 * @tparam Traits Underlying `std::char_traits`-like of the string.
 */
template<typename CharT = char, typename Traits = std::char_traits<CharT>>
struct line_iterator : std::iterator<std::input_iterator_tag, std::basic_string<CharT, Traits>> {
private:
    std::basic_istream<CharT, Traits>* reader;
    std::basic_string<CharT, Traits> value;
    bool status;
public:
    line_iterator() noexcept: reader(nullptr), status(false) {}
    line_iterator(std::basic_istream<CharT, Traits>& out) noexcept: reader(&out) {
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

    auto operator->() noexcept -> decltype(&value) {
        return &value;
    }

    bool operator==(const line_iterator& other) const noexcept {
        return (status == other.status)  && (!status || reader == other.reader);
    }

    bool operator!=(const line_iterator& other) const noexcept {
        return not (*this == other);
    }
};

/**
 * @ingroup io
 * @brief A range object that returns line_iterators.
 * @details A range object that returns line_iterators. This shouldn't be used
 * directly and instead should be used with `lines`.
 *
 * @tparam CharT Underlying character type.
 * @tparam Traits Underlying character traits type.
 */
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

/**
 * @ingroup io
 * @brief Returns a range object to iterate through input lines.
 * @details Iterates through input lines. Best used with the range-based
 * for loop.
 *
 * @param in `std::istream` derived object to iterate through lines
 * @return `line_reader` object to iterate through.
 */
template<typename CharT, typename Traits>
inline line_reader<CharT, Traits> lines(std::basic_istream<CharT, Traits>& in) {
    return line_reader<CharT, Traits>(in);
}
} // io
} // gears

#endif // GEARS_IO_LINES_HPP
