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
#include <gears/enums.hpp>

using namespace gears;

TEST_CASE("enums", "[enums]") {
    enum class under : char {
        a = 0x61,
        b = 0x62,
        c = 0x63
    };

    REQUIRE(enums::to_underlying(under::a) == 'a');
    REQUIRE(enums::to_underlying(under::b) == 'b');
    REQUIRE(enums::to_underlying(under::c) == 'c');

    enum class test : int {
        none = 0,
        a = 1 << 0,
        b = 1 << 1,
        c = 1 << 2,
        d = 1 << 3,
        e = 1 << 4
    };

    // test constexpr status
    constexpr test flags = enums::activate_flags(test::a, test::b, test::e);
    static_assert(enums::has_flags(flags, test::b), "...");
    static_assert(enums::has_flags(flags, test::a), "...");
    static_assert(enums::has_flags(flags, test::e), "...");
    static_assert(enums::has_flags(flags, test::a, test::b, test::e ), "...");

    // normal enum test
    test flags_two = test::none;

    // set flags
    enums::set_flags(flags_two, test::a, test::b, test::c);
    REQUIRE(enums::has_flags(flags_two, test::a));
    REQUIRE(enums::has_flags(flags_two, test::b));
    REQUIRE(enums::has_flags(flags_two, test::c));
    REQUIRE(enums::has_flags(flags_two, test::a, test::b, test::c));

    // unset flags
    enums::remove_flags(flags_two, test::b);
    REQUIRE(enums::has_flags(flags_two, test::a));
    REQUIRE(!enums::has_flags(flags_two, test::b));
    REQUIRE(enums::has_flags(flags_two, test::c));
    REQUIRE(!enums::has_flags(flags_two, test::a, test::b, test::c));
    REQUIRE(enums::has_flags(flags_two, test::a, test::c));
}

TEST_CASE("enum operators", "[enums-operators]") {
    using namespace gears::enums::operators;

    enum class test : int {
        none = 0,
        a = 1 << 0,
        b = 1 << 1,
        c = 1 << 2,
        d = 1 << 3,
        e = 1 << 4
    };

    // test constexpr status
    constexpr test compile = test::a | test::b | test::c;
    static_assert((compile & test::b) != 0, "...");
    static_assert((compile & test::a) != 0, "...");
    static_assert((compile & test::c) != 0, "...");
    static_assert((compile & (test::a | test::b | test::c)) == compile, "...");

    // normal tests
    test flags = test::none;

    flags |= test::a | test::b | test::c;
    REQUIRE(((flags & test::b) != 0));
    REQUIRE(((flags & test::a) != 0));
    REQUIRE(((flags & test::e) == 0));
    REQUIRE(((flags & test::d) == 0));
    REQUIRE(((flags & test::c) != 0));
    REQUIRE(((flags & (test::a | test::b | test::c)) == flags));

    // unset flags
    flags &= ~test::b;
    REQUIRE(((flags & test::b) == 0));
    REQUIRE(((flags & test::a) != 0));
    REQUIRE(((flags & test::c) != 0));
}
