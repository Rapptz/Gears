// The MIT License (MIT)

// Copyright (c) 2012-2014 Rapptz

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

#ifndef GEARS_MATH_GENERATOR_HPP
#define GEARS_MATH_GENERATOR_HPP

#include <vector>
#include <iterator>
#include <cmath>
#include <gears/math/algorithm.hpp>

namespace gears {
namespace math {
/**
 * @ingroup math
 * @brief Generates primes using a modified Sieve of Eratosthenes.
 * @details Generates primes using a modified Sieve of Eratosthenes. The
 * function will generate primes up to the limit provided. e.g. if limit is
 * 100, then the last prime generated would be 97. The container must have an
 * integral `value_type` for best results. Currently this function only works
 * on containers that provide the `push_back` function. This might be changed
 * in the future. The first two primes (2 and 3) are always provided regardless
 * of the limit given.
 *
 * @param limit The upper limit of primes to generate.
 * @param cont The container to insert the primes to.
 */
template<typename Container, typename Value = typename Container::value_type>
inline void primes(Value limit, Container& cont) {
    cont.push_back(2);
    cont.push_back(3);

    Value offset = limit % 6 > 1;
    Value wheels[6] = { limit, limit - 1, limit + 4, limit + 3, limit + 2, limit + 1 };
    Value k = 0;
    Value n = wheels[limit % 6];
    std::vector<bool> sieve(n / 3, true);
    sieve[0] = false;
    for(Value i = 0, upper = static_cast<Value>(std::sqrt(n))/3; i <= upper; ++i) {
        if(sieve[i]) {
            k = (3 * i + 1) | 1;
            for(Value j = (k * k) / 3; j < n / 3; j += 2 * k) {
                sieve[j] = false;
            }

            for(Value j = (k * k + 4 * k - 2 * k * (i & 1)) / 3; j < n / 3; j += 2 * k) {
                sieve[j] = false;
            }
        }
    }

    for(Value i = 1; i < n / 3 - offset; ++i) {
        if(sieve[i]) {
            cont.push_back((3 * i + 1) | 1);
        }
    }
}

/**
 * @ingroup math
 * @brief Generates Pythagorean triples.
 * @details Generates Pythagorean triples and puts the results
 * into a container provided. The results are added to the container as if
 * calling:
 *
 * @code
 * cont.emplace_back(x, y, z)
 * @endcode
 *
 * @param limit The upper limit of Pythagorean triples to generate.
 * @param cont The container to emplace the Pythagorean triples.
 */
template<typename Container, typename Integral>
inline void pythagorean_triples(Integral limit, Container& cont) {
    for(Integral i = 1; i < limit; ++i) {
        if((i * i + (i + 1) * (i + 1)) > limit) {
            break;
        }

        for(Integral j = i + 1; j < limit; j += 2) {
            if(j * j + i * i > limit) {
                break;
            }

            if(gcd(i, j) > 1) {
                continue;
            }

            cont.emplace_back(j * j - i * i, 2 * i * j, i * i + j * j);
        }
    }
}
} // math
} // gears

#endif // GEARS_MATH_GENERATOR_HPP
