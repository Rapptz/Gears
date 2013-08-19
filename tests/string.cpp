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
#include <vector>
#include <iterator>
#include <gears/string.hpp>

TEST_CASE("Case convert", "[case]") {
    using namespace gears::literals;
    REQUIRE(gears::to_lower("HELLO wOrLD"_s) == "hello world");
    REQUIRE(gears::to_upper("hello world"_s) == "HELLO WORLD");
    REQUIRE(gears::is_all_lower("hello world"_s));
    REQUIRE(gears::is_all_upper("HELLO WORLD"_s));
}

TEST_CASE("Predicates", "[pred]") {
    using namespace gears::literals;
    REQUIRE(gears::iequal("hello"_s, "HELLO"_s));
    REQUIRE(gears::starts_with("Hello World"_s, "Hello"_s));
    REQUIRE(gears::istarts_with("HELLO world"_s, "hello"_s));
    REQUIRE(gears::ends_with("Hello World"_s, "World"_s));
    REQUIRE(gears::iends_with("Hello World"_s, "WoRLd"_s));
    REQUIRE(gears::contains("Hello World"_s, "World"_s));
    REQUIRE(gears::icontains("Hello World"_s, "Lo WoRL"_s));
    REQUIRE(gears::all("i3aa34"_s, gears::is_any_of<>("i3a4")));
}

TEST_CASE("Replacing", "[replace]") {
    using namespace gears::literals;
    std::string test("Hello Hello Hello");

    SECTION("Replace Algorithms", "[replace-algo]") {
        REQUIRE(gears::replace_first(test, "Hello"_s, "Bye"_s) == "Bye Hello Hello");
        REQUIRE(gears::replace_last(test, "Hello"_s, "Bye"_s) == "Hello Hello Bye");
        REQUIRE(gears::replace_nth(test, 1, "Hello"_s, "Bye"_s) == "Hello Bye Hello");
        REQUIRE(gears::replace_all(test, "Hello"_s, "Bye"_s) == "Bye Bye Bye");
    }

    SECTION("Erase Algorithms", "[erase-algo]") {
        REQUIRE(gears::erase_first(test, "Hello"_s) == " Hello Hello");
        REQUIRE(gears::erase_last(test, "Hello"_s) == "Hello Hello ");
        REQUIRE(gears::erase_nth(test, 1, "Hello"_s) == "Hello  Hello");
        REQUIRE(gears::erase_all(test, "Hello"_s) == "  ");
    }
}

TEST_CASE("Finding", "[find]") {
    using namespace gears::literals;
    REQUIRE(gears::find_first_of("Hello"_s, gears::is_any_of<>("lo")) == 2);
    REQUIRE(gears::find_first_of("Hello"_s, gears::is_any_of<>("a")) == std::string::npos);
    REQUIRE(gears::find_first_not_of("Hello There"_s, gears::is_any_of<>("HeloThr")) == 5);
    REQUIRE(gears::find_last_of("Hello"_s, gears::is_any_of<>("l")) == 3);
    REQUIRE(gears::find_last_not_of(" Hello "_s, gears::is_any_of<>(" ")) == 5);
}

TEST_CASE("Trim", "[trim]") {
    using namespace gears::literals;
    std::string test("  Hello  ");
    REQUIRE(gears::trim_left(test) == "Hello  ");
    REQUIRE(gears::trim_right(test) == "  Hello");
    REQUIRE(gears::trim(test) == "Hello");
    REQUIRE(test == "  Hello  ");
}

TEST_CASE("Transforms", "[trans]") {
    using namespace gears::literals;
    std::vector<int> v = {1,2,3,4,5};
    std::vector<std::string> a;
    std::vector<std::string> expected_one = {"a", "b", "c", "d"};
    REQUIRE(gears::right("abcdef"_s, 4) == "cdef");
    REQUIRE(gears::right("abcdef"_s, 10) == "abcdef");
    REQUIRE(gears::left("abcdef"_s, 4) == "abcd");
    REQUIRE(gears::left("abcdef"_s, 10) == "abcdef");
    REQUIRE(gears::reverse("abcdef"_s) == "fedcba");
    REQUIRE(gears::join(v, ", "_s) == "1, 2, 3, 4, 5");
    REQUIRE(gears::join_if(v, ", "_s, [](int x) { return x < 3; }) == "1, 2");
    gears::split("a, b, c, d"_s, ", "_s, std::back_inserter(a));
    REQUIRE((a == expected_one)); // work around
}

TEST_CASE("String Builder", "[builder]") {
    using namespace gears::literals;
    std::string a = (gears::stringbuilder<>("Hello") << " World!");
    auto b = (gears::stringbuilder<>() << "Hello" << " World").append('!').to_string();
    auto c = (gears::stringbuilder<wchar_t>() << L"Hello").to_string();
    REQUIRE(a == "Hello World!"_s);
    REQUIRE(b == "Hello World!"_s);
    REQUIRE(c == L"Hello"_s);
}