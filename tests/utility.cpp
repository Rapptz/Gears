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
#include <sstream>
#include <string>

namespace util = gears::utility;

TEST_CASE("Utility", "[utility]") {
    SECTION("array creation", "[utility-array]") {
        auto arr = util::make_array<int>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
        static_assert(std::is_same<decltype(arr), std::array<int, 10>>::value, "oops");
        REQUIRE(arr.size() == 10);
        REQUIRE(arr.front() == 1);
        REQUIRE(arr.back() == 10);
    }

    SECTION("unique_ptr creation", "[utility-unique-ptr]") {
        // regular ptrs
        auto ptr1 = util::make_unique<int>(10);
        REQUIRE(ptr1 != nullptr);
        REQUIRE(*ptr1 == 10);
        auto ptr2 = util::make_unique<std::string>(10, 'a');
        REQUIRE(ptr2 != nullptr);
        REQUIRE(*ptr2 == "aaaaaaaaaa");

        // arrays
        auto ptr3 = util::make_unique<int[]>(10);
        REQUIRE(ptr3 != nullptr);

        for(unsigned i = 0; i < 10; ++i) {
            REQUIRE(ptr3[i] == 0);
        }
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

#define GEARS_REQUIRE_TRUE(...) \
    REQUIRE(is_true(__VA_ARGS__)); \
    REQUIRE(!is_indeterminate(__VA_ARGS__)); \
    REQUIRE(!is_false(__VA_ARGS__));

#define GEARS_REQUIRE_FALSE(...) \
    REQUIRE(is_false(__VA_ARGS__)); \
    REQUIRE(!is_indeterminate(__VA_ARGS__)); \
    REQUIRE(!is_true(__VA_ARGS__));

#define GEARS_REQUIRE_INDETERMINATE(...) \
    REQUIRE(!is_false(__VA_ARGS__)); \
    REQUIRE(is_indeterminate(__VA_ARGS__)); \
    REQUIRE(!is_true(__VA_ARGS__));

TEST_CASE("tribool", "[utility-tribool]") {
    using namespace gears::utility;

    SECTION("indeterminate") {
        tribool x;
        GEARS_REQUIRE_INDETERMINATE(x);
        GEARS_REQUIRE_INDETERMINATE(x == indeterminate);
        GEARS_REQUIRE_INDETERMINATE(!x == indeterminate);

        x = indeterminate;
        GEARS_REQUIRE_INDETERMINATE(x);
        GEARS_REQUIRE_INDETERMINATE(x == indeterminate);
        GEARS_REQUIRE_INDETERMINATE(!x == indeterminate);
        GEARS_REQUIRE_INDETERMINATE(x != true);
        GEARS_REQUIRE_INDETERMINATE(x != false);
        GEARS_REQUIRE_INDETERMINATE(x == x);
        GEARS_REQUIRE_INDETERMINATE(!(x != x));
    }

    SECTION("true") {
        tribool x = true;
        GEARS_REQUIRE_TRUE(x);
        GEARS_REQUIRE_TRUE(x == true);
        GEARS_REQUIRE_TRUE(x);
        GEARS_REQUIRE_TRUE(x != false);
        GEARS_REQUIRE_INDETERMINATE(x != indeterminate);
        GEARS_REQUIRE_TRUE(!x == false);
        GEARS_REQUIRE_TRUE(x == x);
        GEARS_REQUIRE_TRUE(!(x != x));
    }

    SECTION("false") {
        tribool x = false;
        GEARS_REQUIRE_FALSE(x);
        GEARS_REQUIRE_TRUE(x == false);
        GEARS_REQUIRE_TRUE(!x);
        GEARS_REQUIRE_TRUE(x != true);
        GEARS_REQUIRE_INDETERMINATE(x != indeterminate);
        GEARS_REQUIRE_TRUE(x == x);
        GEARS_REQUIRE_TRUE(!(x != x));
    }

    SECTION("logical and") {
        tribool x = false;
        tribool y = true;
        tribool z;

        REQUIRE(is_true(y && y));
        REQUIRE(is_false(y && x));
        REQUIRE(is_indeterminate(y && z));
        REQUIRE(is_false(x && y));
        REQUIRE(is_false(x && x));
        REQUIRE(is_false(x && z));
        REQUIRE(is_indeterminate(z && y));
        REQUIRE(is_false(z && x));
        REQUIRE(is_indeterminate(z && z));
    }

    SECTION("logical or") {
        tribool x = false;
        tribool y = true;
        tribool z;

        REQUIRE(is_true(y || y));
        REQUIRE(is_true(y || z));
        REQUIRE(is_true(y || x));
        REQUIRE(is_true(x || y));
        REQUIRE(is_false(x || x));
        REQUIRE(is_indeterminate(x || z));
        REQUIRE(is_true(z || y));
        REQUIRE(is_indeterminate(z || z));
        REQUIRE(is_indeterminate(z || x));
    }

    SECTION("output") {
        tribool x = true;
        std::ostringstream out;
        out << x;
        REQUIRE(out.str() == "1");
        x = false;
        out << x;
        REQUIRE(out.str() == "10");
        x = indeterminate;
        out << x;
        REQUIRE(out.str() == "102");
        out.str("");

        out << std::boolalpha << x;
        REQUIRE(out.str() == "indeterminate");
        out.str("");
        x = true;
        out << std::boolalpha << x;
        REQUIRE(out.str() == "true");
        x = false;
        out.str("");
        out << std::boolalpha << x;
        REQUIRE(out.str() == "false");

        // custom name facet
        indeterminate_t null{};
        out.str("");
        out.imbue(std::locale(out.getloc(), new indeterminate_name<char>("null")));
        x = null;
        out << std::boolalpha << x;
        REQUIRE(out.str() == "null");
    }

    SECTION("input") {
        tribool x, y, z;
        std::istringstream ss("0 1 2");
        REQUIRE((ss >> x >> y >> z));
        GEARS_REQUIRE_FALSE(x);
        GEARS_REQUIRE_TRUE(y);
        GEARS_REQUIRE_INDETERMINATE(z);

        ss.str("false true indeterminate");
        ss.clear();
        REQUIRE((ss >> std::boolalpha >> x >> y >> z));
        GEARS_REQUIRE_FALSE(x);
        GEARS_REQUIRE_TRUE(y);
        GEARS_REQUIRE_INDETERMINATE(z);

        // custom name facet
        ss.str("null");
        ss.clear();
        ss.imbue(std::locale(ss.getloc(), new indeterminate_name<char>("null")));
        REQUIRE((ss >> std::boolalpha >> x));
        GEARS_REQUIRE_INDETERMINATE(x);
    }
}
