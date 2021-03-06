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
#include <gears/utility/any.hpp>

TEST_CASE("Any", "[any]") {
    SECTION("Basic", "[any-basic]") {
        gears::any x, y;
        y = x;
        REQUIRE(!x);
        REQUIRE(!y);
    }

    SECTION("Basic II", "[any-basic-two]") {
        gears::any x, y;
        x = 10;
        REQUIRE(x);
        REQUIRE(x.is<int>());
        REQUIRE_NOTHROW(x.as<int>());
        REQUIRE_NOTHROW(gears::any_cast<int>(x));
        int test = x.as<int>();
        REQUIRE(test == 10);
    }

    SECTION("Copy/Move", "[any-cm]") {
        gears::any x, y;
        x = 871286126121ULL;
        y = x;
        using ullong = unsigned long long;

        REQUIRE(x.is<ullong>());
        REQUIRE(y.is<ullong>());
        REQUIRE_NOTHROW(x.as<ullong>());
        REQUIRE_NOTHROW(y.as<ullong>());
        REQUIRE_NOTHROW(gears::any_cast<ullong>(x));
        REQUIRE_NOTHROW(gears::any_cast<ullong>(y));
        ullong one = x.as<ullong>();
        ullong two = y.as<ullong>();
        REQUIRE(one == two);
    }

    SECTION("Error Handling", "[any-error]") {
        gears::any x = "Hello";
        REQUIRE(x.is<const char*>());
        REQUIRE(!x.is<int>());
        REQUIRE_THROWS(x.as<float>());
        REQUIRE_THROWS(gears::any_cast<int>(x));
    }
}
