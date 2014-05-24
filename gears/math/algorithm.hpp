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

#ifndef GEARS_MATH_ALGORITHM_HPP
#define GEARS_MATH_ALGORITHM_HPP

#include <type_traits>

namespace gears {
namespace math {
template<typename T>
inline T fibonacci(T number) {
    static_assert(std::is_arithmetic<T>::value, "Type passed must be an integer or floating point type");
    if(number < 2)
        return number;
    T a(1);
    T b(0);
    T c(0);

    while(number--) {
        c = b;
        b = a;
        a = b + c;
    }

    return a;
}

template<typename T>
constexpr T factorial(const T& number) {
    static_assert(std::is_arithmetic<T>::value, "Type passed must be an integer or floating point type");
    return number == 0 ? 1 : number * factorial(number - 1);
}

template<typename T>
constexpr T gcd(const T& x, const T& y) {
    static_assert(std::is_arithmetic<T>::value, "Type passed must be an integer or floating point type");
    return y == 0 ? x : gcd(y, x % y);
}

template<typename T>
inline T mod_pow(T base, T exponent, const T& modulus) {
    static_assert(std::is_arithmetic<T>::value, "Type passed must be an integer or floating point type");
    T result(1);

    while(exponent) {
        if((exponent % 2) == 1) {
            result = (base * result) % modulus;
        }
        exponent /= 2;
        base = (base * base) % modulus;
    }

    return result;
}

template<typename T>
inline T sum_of_divisors(const T& number) noexcept {
    static_assert(std::is_arithmetic<T>::value, "Type passed must be an integer or floating point type");
    T result(0);
    for(T i(1); i * i <= number; ++i) {
        result += (number % i) ? 0 : ((i * i == number) ? i : i + number / i);
    }
    return result;
}
} // math
} // gears

#endif // GEARS_MATH_ALGORITHM_HPP
