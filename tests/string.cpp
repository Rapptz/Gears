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
#include <vector>
#include <iterator>
#include <gears/string.hpp>
#include <limits>

using namespace gears::string::literals;
using namespace gears;

TEST_CASE("Case convert", "[case]") {
    REQUIRE(string::to_lower("HELLO wOrLD"_s) == "hello world");
    REQUIRE(string::to_upper("hello world"_s) == "HELLO WORLD");
    REQUIRE(string::is_all_lower("hello world"_s));
    REQUIRE(string::is_all_upper("HELLO WORLD"_s));
}

TEST_CASE("Predicates", "[pred]") {
    REQUIRE(string::iequal("hello"_s, "HELLO"_s));
    REQUIRE(string::starts_with("Hello World"_s, "Hello"_s));
    REQUIRE(string::istarts_with("HELLO world"_s, "hello"_s));
    REQUIRE(string::ends_with("Hello World"_s, "World"_s));
    REQUIRE(string::iends_with("Hello World"_s, "WoRLd"_s));
    REQUIRE(string::contains("Hello World"_s, "World"_s));
    REQUIRE(string::icontains("Hello World"_s, "Lo WoRL"_s));
    REQUIRE(string::all("i3aa34"_s, string::is_any_of<>("i3a4")));
}

TEST_CASE("Replacing", "[replace]") {
    std::string test("Hello Hello Hello");

    SECTION("Replace Algorithms", "[replace-algo]") {
        REQUIRE(string::replace_first(test, "Hello"_s, "Bye"_s) == "Bye Hello Hello");
        REQUIRE(string::replace_last(test, "Hello"_s, "Bye"_s) == "Hello Hello Bye");
        REQUIRE(string::replace_nth(test, 1, "Hello"_s, "Bye"_s) == "Hello Bye Hello");
        REQUIRE(string::replace_all(test, "Hello"_s, "Bye"_s) == "Bye Bye Bye");
    }

    SECTION("Erase Algorithms", "[erase-algo]") {
        REQUIRE(string::erase_first(test, "Hello"_s) == " Hello Hello");
        REQUIRE(string::erase_last(test, "Hello"_s) == "Hello Hello ");
        REQUIRE(string::erase_nth(test, 1, "Hello"_s) == "Hello  Hello");
        REQUIRE(string::erase_all(test, "Hello"_s) == "  ");
    }
}

TEST_CASE("Finding", "[find]") {
    REQUIRE(string::find_first_of("Hello"_s, string::is_any_of<>("lo")) == 2u);
    REQUIRE(string::find_first_of("Hello"_s, string::is_any_of<>("a")) == std::string::npos);
    REQUIRE(string::find_first_not_of("Hello There"_s, string::is_any_of<>("HeloThr")) == 5u);
    REQUIRE(string::find_last_of("Hello"_s, string::is_any_of<>("l")) == 3u);
    REQUIRE(string::find_last_not_of(" Hello "_s, string::is_any_of<>(" ")) == 5u);
}

TEST_CASE("Trim", "[trim]") {
    std::string test("  Hello  ");
    REQUIRE(string::trim_left(test) == "Hello  ");
    REQUIRE(string::trim_right(test) == "  Hello");
    REQUIRE(string::trim(test) == "Hello");
    REQUIRE(test == "  Hello  ");
}

TEST_CASE("Transforms", "[trans]") {
    std::vector<int> v = {1,2,3,4,5};
    std::vector<std::string> a;
    std::vector<std::string> expected_one = {"a", "b", "c", "d"};
    REQUIRE(string::right("abcdef"_s, 4) == "cdef");
    REQUIRE(string::right("abcdef"_s, 10) == "abcdef");
    REQUIRE(string::left("abcdef"_s, 4) == "abcd");
    REQUIRE(string::left("abcdef"_s, 10) == "abcdef");
    REQUIRE(string::reverse("abcdef"_s) == "fedcba");
    REQUIRE(string::join(v, ", "_s) == "1, 2, 3, 4, 5");
    REQUIRE(string::join_if(v, ", "_s, [](int x) { return x < 3; }) == "1, 2");
    string::split("a, b, c, d"_s, ", "_s, std::back_inserter(a));
    REQUIRE((a == expected_one)); // work around
}


TEST_CASE("Lexical Cast", "[lexical-cast]") {
    REQUIRE(string::lexical_cast<int>("100"_s) == 100);
    REQUIRE(string::lexical_cast<double>("3.14"_s) == 3.14);
    REQUIRE(string::lexical_cast<std::string>("300"_s) == "300");
    constexpr int max = std::numeric_limits<int>::max();
    constexpr int min = std::numeric_limits<int>::min();
    REQUIRE(string::lexical_cast<int>(std::to_string(max)) == max);
    REQUIRE(string::lexical_cast<int>(std::to_string(min)) == std::numeric_limits<int>::min());
}
