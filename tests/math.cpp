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

#include <catch.hpp>
#include <gears/math.hpp>
#include <tuple>
#include <algorithm>

TEST_CASE("Higher Precision Integer", "[uintx]") {
    using namespace gears::math::literals;
    SECTION("Addition", "[uintx-add]") {
        auto stuff = 6719847289364162472817421_x;
        stuff += 1928317212831712ULL;
        REQUIRE(stuff == 6719847291292479685649133_x);
        REQUIRE(stuff > 100);
        REQUIRE(stuff != 0);
    }

    SECTION("Subtraction", "[uintx-sub]") {
        auto stuff = 9123847281347218347214212_x;
        stuff -= 9182371232121ULL;
        REQUIRE(stuff == 9123847281338035975982091_x);
        REQUIRE(stuff > 100);
        REQUIRE(stuff != 0);
    }

    SECTION("Multiplication", "[uintx-mul]") {
        auto stuff = 819374812937489172894782121212212_x;
        stuff *= 7182461231831ULL;
        REQUIRE(stuff == 5885127828262293680350082130474219356480320172_x);
        REQUIRE(stuff > 100);
        REQUIRE(stuff != 0);
    }

    SECTION("Division", "[uintx-div]") {
        auto stuff = 1927498748914987934621746728364782163748212212231_x;
        stuff /= 814371284321ULL;
        auto expected = 2366855003393301719774904141041689695_x;
        REQUIRE(stuff == expected);
        REQUIRE(stuff > 100);
        REQUIRE(stuff != 0);
    }

    SECTION("Modulus", "[uintx-mod]") {
        auto stuff = 91984712847987981232998147123812_x;
        stuff %= 8914712412LL;
        auto expected = 3725426300_x;
        REQUIRE(stuff == expected);
        REQUIRE(stuff > 100);
        REQUIRE(stuff != 0);
    }

    SECTION("Conversion", "[uintx-conv]") {
        auto stuff = 1234567890_x;
        auto i = gears::math::uintx_cast<long long>(stuff);
        REQUIRE(i == 1234567890LL);
        auto str = gears::math::uintx_cast<std::string>(stuff);
        REQUIRE(str == "1234567890");
    }
}

TEST_CASE("Basic Algorithms", "[math-basic-algo]") {
    constexpr size_t n = 10;
    REQUIRE(gears::math::factorial(10) == 3628800);
    REQUIRE(gears::math::fibonacci(20) == 6765);
    REQUIRE(gears::math::gcd(252, 105) == 21);
    REQUIRE(gears::math::min(1,2,3,4,5,6) == 1);
    REQUIRE(gears::math::max(5,11,9,14,19,192) == 192);
    REQUIRE((std::is_same<decltype(gears::math::max(10,1)), int>()));
    REQUIRE(n == gears::math::max(10,9,1,4));
}

TEST_CASE("Generators", "[math-generator]") {
    using namespace gears;
    std::vector<int> primes;
    math::primes(100, primes);
    REQUIRE(primes.size() == 25);
    REQUIRE(primes.back() == 97);
    REQUIRE(primes.front() == 2);
    REQUIRE(std::accumulate(std::begin(primes), std::end(primes), 0) == 1060);
    std::vector<std::tuple<int, int, int>> triples;
    math::pythagorean_triples(100, triples);
    REQUIRE(triples.size() == 16);
    int a, b, c;
    for(auto&& triple : triples) {
        std::tie(a, b, c) = triple;
        REQUIRE((a * a + b * b) == c * c);
    }

    SECTION("primality test") {
        std::vector<int> more_primes;
        math::primes(2000, more_primes);
        REQUIRE(more_primes.size() == 303);
        REQUIRE(more_primes.back() == 1999);
        REQUIRE(more_primes.front() == 2);

        for(auto&& prime : more_primes) {
            if(math::is_prime(prime)) {
                REQUIRE(true);
            }
            else {
                REQUIRE(std::to_string(prime) == "");
            }
        }
    }
}
