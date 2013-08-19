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
#include <gears/math/uintx.hpp>

TEST_CASE("Higher Precision Integer", "[uintx]") {
    SECTION("Addition", "[uintx-add]") {
        gears::uintx<> stuff("6719847289364162472817421");
        stuff += 1928317212831712ULL;
        REQUIRE(stuff == gears::uintx<>("6719847291292479685649133"));
        REQUIRE(stuff > 100);
        REQUIRE(stuff != 0);
    }

    SECTION("Subtraction", "[uintx-sub]") {
        gears::uintx<> stuff("9123847281347218347214212");
        stuff -= 9182371232121ULL;
        REQUIRE(stuff == gears::uintx<>("9123847281338035975982091"));
        REQUIRE(stuff > 100);
        REQUIRE(stuff != 0);
    }

    SECTION("Multiplication", "[uintx-mul]") {
        gears::uintx<> stuff("819374812937489172894782121212212");
        stuff *= 7182461231831ULL;
        REQUIRE(stuff == gears::uintx<>("5885127828262293680350082130474219356480320172"));
        REQUIRE(stuff > 100);
        REQUIRE(stuff != 0);
    }

    SECTION("Division", "[uintx-div]") {
        gears::uintx<> stuff("1927498748914987934621746728364782163748212212231");
        stuff /= 814371284321ULL;
        gears::uintx<> expected("2366855003393301719774904141041689695");
        REQUIRE(stuff == expected);
        REQUIRE(stuff > 100);
        REQUIRE(stuff != 0);
    }

    SECTION("Modulus", "[uintx-mod]") {
        gears::uintx<> stuff("91984712847987981232998147123812");
        stuff %= 8914712412LL;
        gears::uintx<> expected("3725426300");
        REQUIRE(stuff == expected);
        REQUIRE(stuff > 100);
        REQUIRE(stuff != 0);
    }

    SECTION("Conversion", "[uintx-conv]") {
        gears::uintx<> stuff("1234567890");
        auto i = gears::uintx_cast<long long>(stuff);
        REQUIRE(i == 1234567890LL);
        auto str = gears::uintx_cast<std::string>(stuff);
        REQUIRE(str == "1234567890");
    }
}