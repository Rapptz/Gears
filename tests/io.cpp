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
#include <gears/io.hpp>
#include <gears/string/format.hpp> // using string::format makes it easier to test
#include <cctype>

using namespace gears;

TEST_CASE("Input/Output", "[io]") {
    SECTION("Basics", "[io-basic]") {
        REQUIRE(string::format("|0| |1| |0|", 1, 2) == "1 2 1");
        REQUIRE(string::format("|0| + |0| = |1|", 1, 2) == "1 + 1 = 2");
        REQUIRE(string::format("|||0||| |||1|||", 'a', 'b') == "|a| |b|");
        auto&& longer = string::format("|0||1||2||3||4||5||6||7||8||9||10||11|", 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
        REQUIRE(longer == "123456789101112");
        REQUIRE(string::format("|||0|", 1) == "|1");
        REQUIRE(string::format("|||||0|||", 1) == "||1|");
        REQUIRE(string::format("|||||0|||||||||", 1) == "||1||||");
        REQUIRE(string::format(true ? "[|0|]" : "|||0|||", 10) == "[10]");
    }

    SECTION("Alignment", "[io-align]") {
        // without fill character
        REQUIRE(string::format("|0:>10|", "Hello") == "     Hello");
        REQUIRE(string::format("|0:<10|", "Hello") == "Hello     ");
        REQUIRE(string::format("||0:<10||", 10) == "|0:<10|");
        REQUIRE(string::format(".|0:>10|.\n.|0:<10|.\n.|0:>10|.", "Hello") == ".     Hello.\n.Hello     .\n.     Hello.");
        REQUIRE(string::format("|0:>*1|", "Hello", 10) == "     Hello");
        REQUIRE(string::format("|0:<*1|", "Hello", 10) == "Hello     ");
        REQUIRE(string::format("||0:<*1||", 10, 10) == "|0:<*1|");
        REQUIRE(string::format(".|0:>*1|.\n.|0:<*1|.\n.|0:>*1|.", "Hello", 10) == ".     Hello.\n.Hello     .\n.     Hello.");

        // with fill character
        REQUIRE(string::format("|0:'#>10|", "Hello") == "#####Hello");
        REQUIRE(string::format("|0:'#<10|", "Hello") == "Hello#####");
        REQUIRE(string::format("||0:'#<10||", 10) == "|0:'#<10|");
        REQUIRE(string::format(".|0:'#>10|.\n.|0:'#<10|.\n.|0:'#>10|.", "Hello") == ".#####Hello.\n.Hello#####.\n.#####Hello.");
        REQUIRE(string::format("|0:'#>*1|", "Hello", 10) == "#####Hello");
        REQUIRE(string::format("|0:'#<*1|", "Hello", 10) == "Hello#####");
        REQUIRE(string::format("||0:'#<*1||", 10, 10) == "|0:'#<*1|");
        REQUIRE(string::format(".|0:'#>*1|.\n.|0:'#<*1|.\n.|0:'#>*1|.", "Hello", 10) == ".#####Hello.\n.Hello#####.\n.#####Hello.");
    }

    SECTION("Format", "[io-format]") {
        // basic format
        REQUIRE(string::format("|0:.2f|", 2.142134) == "2.14");
        REQUIRE(string::format("|0:+| |1:+|", -1, 1) == "-1 +1");
        REQUIRE(string::format("|0:p|", 1.0) == "1.00000");
        REQUIRE(string::format("0x|0:xu| |0:xb| |0:xub|", 1001) == "0x3E9 0x3e9 0X3E9");
        REQUIRE(string::format("|0:e| |0:eu|", 6e+100) == "6.000000e+100 6.000000E+100");
        REQUIRE(string::format("|0:.3e| |0:.3eu|", 6.1232e+100) == "6.123e+100 6.123E+100");
        REQUIRE(string::format("|0:ob|", 100) == "0144");
        REQUIRE(string::format("|0:t| |1:t|", true, false) == "true false");
        REQUIRE(string::format("|0:tu|", true) == "true");
        REQUIRE(string::format("|0:d|", 10) == "10");

        // bit more complicated
        REQUIRE(string::format("|0:'0>10|", 10) == "0000000010");
        REQUIRE(string::format("|0:'0>*1|", 10, 10) == "0000000010");
        REQUIRE(string::format("|0:'0<10|", 10) == "1000000000");
        REQUIRE(string::format("|0:'0<*1|", 10, 10) == "1000000000");
        REQUIRE(string::format("|0:'#<10.5f|", 3.14) == "3.14000###");
        REQUIRE(string::format("|0:'#>10.5f|", 3.14) == "###3.14000");
        REQUIRE(string::format("|0:'#<*1.*2f|", 3.14, 10, 5) == "3.14000###");
        REQUIRE(string::format("|0:'#>*1.*2f|", 3.14, 10, 5) == "###3.14000");
    }

    SECTION("Format Regressions", "[io-format-regr]") {
        // test the functions being 'stateless'
        std::ostringstream ss;
        ss.fill('#');
        REQUIRE_NOTHROW(io::fprint(ss, "|0:10|", "hello"));
        REQUIRE(ss.str() == "     hello");
        ss.clear();
        ss.str("");
        ss.precision(10);
        REQUIRE_NOTHROW(io::fprint(ss, "|0|", 1.23456789));
        REQUIRE(ss.str() == "1.23457");
        ss.clear();
        ss.str("");

        REQUIRE_THROWS(io::fprint(ss, "|0"));
        REQUIRE_THROWS(io::fprint(ss, "|0|"));
        REQUIRE_THROWS(io::fprint(ss, "|0:.|", 10));
        ss.clear();
        ss.str("");
    }

    SECTION("Lines", "[io-lines]") {
        std::istringstream iss("10\n11\n12\n13\n14\n15");
        unsigned number_of_lines = 0;
        for(auto&& line : io::lines(iss)) {
            REQUIRE(std::stoi(line) >= 10);
            ++number_of_lines;
        }
        REQUIRE(number_of_lines == 6);
    }

    SECTION("Getline", "[io-getlines]") {
        std::istringstream iss("1234567890abcdef");
        std::string str;
        REQUIRE((io::getline_until(iss, str, [](char c) { return !isdigit(c); })));
        REQUIRE(str == "1234567890");
    }
}
