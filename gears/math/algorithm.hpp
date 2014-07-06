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
#include <utility>

namespace gears {
namespace math {
/**
 * @ingroup math
 * @brief Calculates the nth fibonacci number.
 * @details Calculates the nth fibonacci number. The internal
 * implementation does not use the naive recursion.
 *
 * @param number Which fibonacci number to calculate.
 * @return Nth fibonacci number.
 */
template<typename T>
inline T fibonacci(T number) {
    if(number < 2) {
        return number;
    }

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

/**
 * @ingroup math
 * @brief Calculates the Nth factorial.
 * @details Calculates the Nth factorial. The internal
 * implementation uses the naive recursion way of doing it
 * in order to preserve C++11 `constexpr` status.
 *
 * @param number Which factorial to calculate.
 * @return Nth factorial number.
 */
template<typename T>
constexpr T factorial(const T& number) {
    return number == 0 ? 1 : number * factorial(number - 1);
}

/**
 * @ingroup math
 * @brief Calculates the greatest common divisor.
 * @details Calculates the greatest common divisor between
 * two numbers. Uses Euclid's algorithm to compute it.
 *
 * @param x Left hand side.
 * @param y Right hand side.
 * @return The greatest common divisor between the numbers.
 */
template<typename T>
constexpr T gcd(const T& x, const T& y) {
    return y == 0 ? x : gcd(y, x % y);
}

/**
 * @ingroup math
 * @brief Calculates the modular exponentiation.
 * @details Calculates the modular exponentiation. That is,
 * it computes essentially `(base ** exponent) % modulus` where
 * `**` denotes exponentiation. All numbers provided must be
 * positive.
 *
 * @param base The base number of the formula.
 * @param exponent The exponent number of the formula.
 * @param modulus The modulo number of the formula.
 * @return `(base ** exponent) % modulus`.
 */
template<typename T>
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

/**
 * @ingroup math
 * @brief Calculates the sum of divisors function.
 * @details Calculates the sum of divisors of a given integer.
 * For example, the divisors for the number 12 are 1, 2, 3, 4,
 * 6, and 12. The sum of these numbers is 28. So
 * `sum_of_divisors(12)` would return 28.
 *
 * @param number The number to take the sum of divisors for.
 * @return The sum of the number's divisors.
 */
template<typename T>
inline T sum_of_divisors(const T& number) noexcept {
    T result(0);
    for(T i(1); i * i <= number; ++i) {
        result += (number % i) ? 0 : ((i * i == number) ? i : i + number / i);
    }
    return result;
}

/**
 * @ingroup math
 * @brief Calculates the absolute value of a number.
 * @details Calculates the absolute value of a number.
 * This uses the incredibly naive implementation and should
 * only be used for its `constexpr` status, which the function
 * in `<cmath>` lacks.
 *
 * @param t The number to make positive.
 * @return The absolute value of a number.
 */
template<typename T>
constexpr T abs(T t) {
    return t < 0 ? -t : t;
}

//@{
template<typename T>
constexpr T min(T&& t) {
    return std::forward<T>(t);
}

template<typename T, typename U>
constexpr typename std::common_type<T, U>::type min(T&& t, U&& u) {
    return u < t ? std::forward<U>(u) : std::forward<T>(t);
}

/**
 * @ingroup math
 * @brief Calculates the minimum value of a list of numbers.
 * @details Calculates the minimum value of a list of numbers.
 * It is recommended to not mix different types when using this
 * function as it will promote types and make it unsafe.
 *
 * @param t First type to compare against.
 * @param u Second type to compare against.
 * @param args Other types to compare against.
 * @return The minimum value of the list of numbers.
 */
template<typename T, typename U, typename... Args>
constexpr typename std::common_type<T, U, Args...>::type min(T&& t, U&& u, Args&&... args) {
    return min(min(std::forward<T>(t), std::forward<U>(u)), min(std::forward<Args>(args)...));
}
//@}

//@{
template<typename T>
constexpr T max(T&& t) {
    return std::forward<T>(t);
}

template<typename T, typename U>
constexpr typename std::common_type<T, U>::type max(T&& t, U&& u) {
    return u < t ? std::forward<T>(t) : std::forward<U>(u);
}

/**
 * @ingroup math
 * @brief Calculates the maximum value of a list of numbers.
 * @details Calculates the maximum value of a list of numbers.
 * It is recommended to not mix different types when using this
 * function as it will promote types and make it unsafe.
 *
 * @param t First type to compare against.
 * @param u Second type to compare against.
 * @param args Other types to compare against.
 * @return The maximum value of the list of numbers.
 */
template<typename T, typename U, typename... Args>
constexpr typename std::common_type<T, U, Args...>::type max(T&& t, U&& u, Args&&... args) {
    return max(max(std::forward<T>(t), std::forward<U>(u)), max(std::forward<Args>(args)...));
}
//@}
} // math
} // gears

#endif // GEARS_MATH_ALGORITHM_HPP
