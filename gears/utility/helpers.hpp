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

#ifndef GEARS_UTILITY_HELPERS_HPP
#define GEARS_UTILITY_HELPERS_HPP

#include <array>
#include <utility>
#include <type_traits>

namespace gears {
namespace utility {
/**
 * @ingroup utility
 * @brief Constructs an std::array instance.
 * @details Constructs an `std::array` instance from the
 * arguments provided of type T. This allows for quick generation
 * of `std::array` instances similar to raw C arrays.
 *
 * @code
 * auto arr = utility::make_array<int>(1, 2, 3, 4, 5, 6, 7, 8);
 * // same as
 * // int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
 * @endcode
 *
 * @param args Arguments to store into the array.
 * @tparam T The type of the array.
 * @return An `std::array` containing the elements provided.
 */
template<typename T, typename... Args>
constexpr std::array<T, sizeof...(Args)> make_array(Args&&... args) {
    return std::array<T, sizeof...(Args)>{{ std::forward<Args>(args)... }};
}
} // utility
} // gears

#endif // GEARS_UTILITY_HELPERS_HPP

