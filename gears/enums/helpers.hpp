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

#ifndef GEARS_ENUMS_HELPERS_HPP
#define GEARS_ENUMS_HELPERS_HPP

#include <type_traits>

namespace gears {
namespace enums {
/**
 * @ingroup enums
 * @brief Casts an enum to its underlying type.
 * @details Casts an enum to its underlying type.
 * This is the equivalent of calling:
 *
 * @code
 * static_cast<typename std::underlying_type<Enum>::type>(x);
 * @endcode
 *
 * @param x enum or enum class to cast
 * @return The enum's value in its underlying type.
 */
template<typename Enum, typename Underlying = typename std::underlying_type<Enum>::type>
constexpr Underlying to_underlying(Enum x) noexcept {
    return static_cast<Underlying>(x);
}
} // enums
} // gears

#endif // GEARS_ENUMS_HELPERS_HPP
