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

#include <catch.hpp>
#include <gears/functional.hpp>
#include <string>
#include <functional>

struct functional_test {
    template<typename T, typename U>
    constexpr auto operator()(T&& t, U&& u) const noexcept -> decltype(std::forward<T>(t) + std::forward<U>(u)) {
        return std::forward<T>(t) + std::forward<U>(u);
    }

    template<typename T, typename U, typename V>
    constexpr auto operator()(T&& t, U&& u, V&& v) const noexcept 
    -> decltype((std::forward<T>(t) + std::forward<U>(u)) * std::forward<V>(v)) {
        return (std::forward<T>(t) + std::forward<U>(u)) * std::forward<V>(v);
    }

    template<typename T>
    void operator()(T& value, const T& val, const T& x, const T& y) const {
        value = (val + x * y) * val;
    }
};

struct invoke_test {
    int f() {
        return 10;
    }

    int g(int x, int y) {
        return 10 + x + y;
    }
};

TEST_CASE("Functional", "[functional]") {
    namespace gf = gears::functional;
    SECTION("Arithmetic Functors", "[arithmetic-funct]") {
        static_assert(gf::plus(1,11) == 12, "...");
        static_assert(gf::multiplies(10, 10) == 100, "...");
        static_assert(gf::minus(100, 92) == 8, "...");
        static_assert(gf::modulus(122, 4) == 2, "...");
        static_assert(gf::divides(10.f, 4.f) == 2.5f, "...");
        int x = 10;
        REQUIRE(gf::plus(x, 1) == 11);
        REQUIRE(gf::multiplies(10, x) == 100);
        REQUIRE(gf::plus(std::string("Hello"), " World") == "Hello World");
        REQUIRE(gf::minus(x, 2) == 8);
        REQUIRE(gf::modulus(x, 5) == 0);
        REQUIRE(gf::divides(125.f, x) == 12.5f);
    }

    SECTION("Comparison Functors", "[comp-funct]") {
        static_assert(gf::equal_to(100, 100), "...");
        static_assert(gf::not_equal_to(1021821094, 1982381273), "...");
        static_assert(gf::less(10219212, 8174178414), "...");
        static_assert(gf::greater(12978414134, 120), "...");
        static_assert(gf::less_equal(10210, 10215), "...");
        static_assert(gf::greater_equal(120129, 12423), "...");

        int x = 100;
        std::string str = "Hello";
        REQUIRE(gf::equal_to(x, 100));
        REQUIRE(gf::not_equal_to(104.f, x));
        REQUIRE(gf::less(x, 900));
        REQUIRE(gf::greater(900, x));
        REQUIRE(gf::less_equal(x, 100));
        REQUIRE(gf::greater_equal(4781, x));

        REQUIRE(gf::equal_to(str, "Hello"));
        REQUIRE(gf::not_equal_to("World", str));
        REQUIRE(gf::less(str, "World"));
        REQUIRE(gf::greater("John Doe", str));
        REQUIRE(gf::less_equal(str, "Xerneas"));
        REQUIRE(gf::greater_equal("John", str));
    }

    SECTION("Logical Functors", "[logic-funct]") {
        static_assert(gf::logical_or(true, false), "...");
        static_assert(gf::logical_and(true, true), "...");
        static_assert(gf::logical_not(false), "...");

        bool b = false;
        REQUIRE(gf::logical_or(true, false));
        REQUIRE(!gf::logical_and(true, b));
        REQUIRE(gf::logical_and(true, !b));
        REQUIRE(gf::logical_not(b));
    }

    SECTION("Numeric Properties", "[numeric-properties]") {
        static_assert(gf::even(100), "...");
        static_assert(gf::odd(101), "...");

        int x = 1021;
        REQUIRE(gf::even(x + 3));
        REQUIRE(gf::odd(x));
    }

    SECTION("Function Composition", "[compose-funct]") {
        auto f = [](int x) { return std::to_string(x); };
        auto g = [](const std::string& str) { return "number is " + str; };

        REQUIRE(gf::compose(g, f)(10) == "number is 10");

        auto a = []() { return 10; };
        auto b = [](int x) { return x * 100; };
        auto c = [](int x) { return std::to_string(x); };
        auto d = [](const std::string& str) { return str + " is valid"; };

        REQUIRE(gf::compose(d, c, b, a)() == "1000 is valid");
    }

    SECTION("Function Currying", "[curry-funct]") {
        static_assert(gf::curry(gf::plus, 10)(100) == 110, "...");
        static_assert(gf::curry(functional_test{}, 10)(1) == 11, "...");
        static_assert(gf::curry(functional_test{}, 50)(90, 90) == 12600, "...");

        int x = 100;
        REQUIRE(gf::curry(gf::multiplies, x)(10) == 1000);
        REQUIRE(gf::curry(functional_test{}, x)(10, 90) == 9900);
        REQUIRE(gf::curry(functional_test{}, x, 100)(5) == 1000);
        REQUIRE(x == 100);
        gf::curry(functional_test{}, std::ref(x))(10, 11, 200);

        REQUIRE(x == 22100);

        REQUIRE(gf::curry([](int x, int y) { return x * x * y * y; }, 10)(4) == 1600);
    }

    SECTION("Invoke", "[invoke-funct]") {
        invoke_test x;
        invoke_test* y = &x;

        REQUIRE(gf::invoke(&invoke_test::f, x) == 10);
        REQUIRE(gf::invoke(&invoke_test::f, y) == 10);
        REQUIRE(gf::invoke(&invoke_test::g, x, 20, 30) == 60);
        REQUIRE(gf::invoke(&invoke_test::g, y, 20, 30) == 60);
        REQUIRE(gf::invoke([](int x, int y) { return (x * x) + (y * y); }, 5, 10) == 125);
    }
}