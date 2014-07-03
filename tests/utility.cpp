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
#include <gears/utility.hpp>
#include <type_traits>

namespace util = gears::utility;

TEST_CASE("Utility", "[utility]") {
    SECTION("array creation", "[utility-array]") {
        auto arr = util::make_array<int>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
        static_assert(std::is_same<decltype(arr), std::array<int, 10>>::value, "oops");
        REQUIRE(arr.size() == 10);
        REQUIRE(arr.front() == 1);
        REQUIRE(arr.back() == 10);
    }

    SECTION("base64", "[utility-base64]") {
        REQUIRE(util::base64::encode("Hello") == "SGVsbG8=");
        REQUIRE(util::base64::encode("Hello World") == "SGVsbG8gV29ybGQ=");
        REQUIRE(util::base64::encode("pleasure.") == "cGxlYXN1cmUu");
        REQUIRE(util::base64::encode("leasure.") == "bGVhc3VyZS4=");
        REQUIRE(util::base64::encode("easure.") == "ZWFzdXJlLg==");
        REQUIRE(util::base64::encode("asure.") == "YXN1cmUu");
        REQUIRE(util::base64::encode("sure.") == "c3VyZS4=");
        REQUIRE(util::base64::encode("any carnal pleasure.") == "YW55IGNhcm5hbCBwbGVhc3VyZS4=" );
        REQUIRE(util::base64::encode("any carnal pleasure") == "YW55IGNhcm5hbCBwbGVhc3VyZQ==");
        REQUIRE(util::base64::encode("any carnal pleasur") == "YW55IGNhcm5hbCBwbGVhc3Vy");
        REQUIRE(util::base64::encode("any carnal pleasu") == "YW55IGNhcm5hbCBwbGVhc3U=" );
        REQUIRE(util::base64::encode("any carnal pleas") == "YW55IGNhcm5hbCBwbGVhcw==");

        REQUIRE(util::base64::decode("SGVsbG8=") == "Hello");
        REQUIRE(util::base64::decode("SGVsbG8gV29ybGQ=") == "Hello World");
        REQUIRE(util::base64::decode("cGxlYXN1cmUu") == "pleasure.");
        REQUIRE(util::base64::decode("c3VyZS4=") == "sure.");
        REQUIRE(util::base64::decode("YW55IGNhcm5hbCBwbGVhcw==") == "any carnal pleas");
        REQUIRE(util::base64::decode("YW55IGNhcm5hbCBwbGVhc3U=") == "any carnal pleasu");
        REQUIRE(util::base64::decode("YW55IGNhcm5hbCBwbGVhc3VyZQ==") == "any carnal pleasure");
    }
}
