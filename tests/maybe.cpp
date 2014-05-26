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
#include <gears/utility/maybe.hpp>

namespace gu = gears::utility;

struct maybe_test {
    int x, y, z;
    maybe_test(int x, int y, int z): x(x), y(y), z(z) {}
};

TEST_CASE("maybe<T>", "[maybe-util]") {

    SECTION("Literal type", "[maybe-lit]") {
        constexpr gu::maybe<int> f;
        static_assert(f == gu::nothing, "...");
        static_assert(f.value_or(40) == 40, "...");
        REQUIRE(f == gu::nothing);
        REQUIRE(f.value_or(40) == 40);
    }

    SECTION("nothing", "[maybe-nothing]") {
        gu::maybe<int> g;
        REQUIRE(g == gu::nothing);
        REQUIRE(g.value_or(20) == 20);
        REQUIRE_THROWS(g.value());
    }

    SECTION("with value", "[maybe-value]") {
        auto g = gu::just(10);

        REQUIRE(g == 10);
        REQUIRE(g != gu::nothing);
        REQUIRE_NOTHROW(g.value());
        REQUIRE(g > 9);
        REQUIRE(g < 200);
        REQUIRE(g.value() == 10);
        REQUIRE(g.value() < 90);
        REQUIRE(g.value_or(10) > 4);
        REQUIRE((g)); // explicit bool
        REQUIRE(g == gu::just(10));
    }

    SECTION("emplacing", "[maybe-emplace]") {
        gu::maybe<maybe_test> x;

        REQUIRE(x == gu::nothing);
        REQUIRE_THROWS(x.value());
        REQUIRE(!(x > gu::nothing));
        REQUIRE(!(gu::nothing < x));

        x.emplace(10, 11, 12);

        REQUIRE(x->x == 10);
        REQUIRE(x->y == 11);
        REQUIRE(x->z == 12);
        REQUIRE(x != gu::nothing);
        REQUIRE_NOTHROW(x.value());

        x = gu::nothing;
        REQUIRE(x == gu::nothing);
        REQUIRE_THROWS(x.value());
    }

    SECTION("in-place", "[maybe-inplace]") {
        gu::maybe<maybe_test> x(gu::in_place, 10, 11, 12);

        REQUIRE(x != gu::nothing);
        REQUIRE(x->x == 10);
        REQUIRE(x->y == 11);
        REQUIRE(x->z == 12);
        REQUIRE_NOTHROW(x.value());
        REQUIRE(x > gu::nothing);
        REQUIRE(gu::nothing < x);

        x = gu::nothing;

        REQUIRE(x == gu::nothing);
        REQUIRE_THROWS(x.value());
    }
}