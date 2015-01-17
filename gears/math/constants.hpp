// The MIT License (MIT)

// Copyright (c) 2012-2015 Danny Y., Rapptz

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

#ifndef GEARS_MATH_CONSTANTS_HPP
#define GEARS_MATH_CONSTANTS_HPP

namespace gears {
namespace math {
namespace detail {
constexpr long double pi = 3.141592653589793238462643383279502884;
constexpr long double half = 0.5000000000000000000000000000000000000;
constexpr long double third = 0.3333333333333333333333333333333333333;
constexpr long double root_two = 1.414213562373095048801688724209698078;
constexpr long double ln_two = 0.6931471805599453094172321214581765680;
constexpr long double half_pi = 1.570796326794896619231321691639751442;
constexpr long double third_pi = 1.047197551196597746154214461093167628;
constexpr long double two_thirds_pi = 2.094395102393195492308428922186335256;
constexpr long double sixth_pi = 0.5235987755982988730771072305465838140;
constexpr long double three_fourths_pi = 2.356194490192344928846982537459627163;
constexpr long double four_thirds_pi = 4.188790204786390984616857844372670512;
constexpr long double two_pi = 6.283185307179586476925286766559005768;
} // detail

template<typename T>
constexpr T pi() noexcept {
    return static_cast<T>(detail::pi);
}

template<typename T>
constexpr T half() noexcept {
    return static_cast<T>(detail::half);
}

template<typename T>
constexpr T third() noexcept {
    return static_cast<T>(detail::third);
}

template<typename T>
constexpr T root_two() noexcept {
    return static_cast<T>(detail::root_two);
}

template<typename T>
constexpr T ln_two() noexcept {
    return static_cast<T>(detail::ln_two);
}

template<typename T>
constexpr T half_pi() noexcept {
    return static_cast<T>(detail::half_pi);
}

template<typename T>
constexpr T third_pi() noexcept {
    return static_cast<T>(detail::third_pi);
}

template<typename T>
constexpr T two_thirds_pi() noexcept {
    return static_cast<T>(detail::two_thirds_pi);
}

template<typename T>
constexpr T sixth_pi() noexcept {
    return static_cast<T>(detail::sixth_pi);
}

template<typename T>
constexpr T three_fourths_pi() noexcept {
    return static_cast<T>(detail::three_fourths_pi);
}

template<typename T>
constexpr T four_thirds_pi() noexcept {
    return static_cast<T>(detail::four_thirds_pi);
}

template<typename T>
constexpr T two_pi() noexcept {
    return static_cast<T>(detail::two_pi);
}
} // math
} // gears

#endif // GEARS_MATH_CONSTANTS_HPP
