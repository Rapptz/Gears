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

#ifndef GEARS_MATH_ALGORITHM_HPP
#define GEARS_MATH_ALGORITHM_HPP

namespace gears {
namespace math {
template<typename T = unsigned long long>
inline T fibonacci(T number) {
    if(number < 2)
        return number;
    T a(1);
    T b(0);
    T c(0);

    while(--number) {
        c = b;
        b = a;
        a = b + c;
    }

    return a;
}

template<typename T = unsigned long long>
constexpr T factorial(const T& number) {
    return number == 0 ? 1 : number * factorial(number - 1);
}

template<typename T = unsigned long long>
constexpr T gcd(const T& x, const T& y) {
    return y == 0 ? x : gcd(y, x % y);
}

template<typename T = unsigned long long>
inline T mod_pow(T base, T exponent, const T& modulus) {
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
} // math
} // gears

#endif // GEARS_MATH_ALGORITHM_HPP