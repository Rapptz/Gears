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

#ifndef GEARS_MATH_ALGORITHM_HPP
#define GEARS_MATH_ALGORITHM_HPP

#include <type_traits>
#include <utility>

namespace gears {
namespace math {
template<typename Integral>
inline Integral fibonacci(Integral number) {
    if(number < 2) {
        return number;
    }

    Integral a(1);
    Integral b(0);
    Integral c(0);

    while(--number) {
        c = b;
        b = a;
        a = b + c;
    }

    return a;
}

template<typename Integral>
constexpr Integral factorial(const Integral& number) {
    return number == 0 ? 1 : number * factorial(number - 1);
}

template<typename Integral>
constexpr Integral gcd(const Integral& x, const Integral& y) {
    return y == 0 ? x : gcd(y, x % y);
}

template<typename Integral>
inline Integral mod_pow(Integral base, Integral exponent, const Integral& modulus) {
    Integral result(1);

    while(exponent) {
        if((exponent % 2) == 1) {
            result = (base * result) % modulus;
        }
        exponent /= 2;
        base = (base * base) % modulus;
    }

    return result;
}

template<typename Integral>
inline Integral sum_of_divisors(const Integral& number) {
    Integral result(0);
    for(Integral i(1); i * i <= number; ++i) {
        result += (number % i) ? 0 : ((i * i == number) ? i : i + number / i);
    }
    return result;
}

template<typename Integral>
inline bool is_prime(const Integral& number) {
    if(number == 1) {
        return false;
    }

    if(number < 4) {
        return true;
    }

    if(number % 2 == 0) {
        return false;
    }

    if(number < 9) {
        return true;
    }

    if(number % 3 == 0) {
        return false;
    }

    const Integral r(std::sqrt(number));
    Integral f(5);
    while(f <= r) {
        if(number % f == 0 || number % (f + 2) == 0) {
            return false;
        }
        f += 6;
    }
    return true;
}

template<typename T>
constexpr T abs(const T& t) {
    return t < 0 ? -t : t;
}

template<typename T>
constexpr T min(T&& t) {
    return std::forward<T>(t);
}

template<typename T, typename U>
constexpr typename std::common_type<T, U>::type min(T&& t, U&& u) {
    return u < t ? std::forward<U>(u) : std::forward<T>(t);
}

template<typename T, typename U, typename... Args>
constexpr typename std::common_type<T, U, Args...>::type min(T&& t, U&& u, Args&&... args) {
    return min(min(std::forward<T>(t), std::forward<U>(u)), min(std::forward<Args>(args)...));
}

template<typename T>
constexpr T max(T&& t) {
    return std::forward<T>(t);
}

template<typename T, typename U>
constexpr typename std::common_type<T, U>::type max(T&& t, U&& u) {
    return u < t ? std::forward<T>(t) : std::forward<U>(u);
}

template<typename T, typename U, typename... Args>
constexpr typename std::common_type<T, U, Args...>::type max(T&& t, U&& u, Args&&... args) {
    return max(max(std::forward<T>(t), std::forward<U>(u)), max(std::forward<Args>(args)...));
}
} // math
} // gears

#endif // GEARS_MATH_ALGORITHM_HPP
