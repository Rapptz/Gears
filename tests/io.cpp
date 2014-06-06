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
#include <gears/string/literals.hpp>
#include <gears/io.hpp>

namespace io = gears::io;
using namespace gears::string::literals;

TEST_CASE("Input/Output", "[io]") {
    SECTION("Basics", "[io-basic]") {
        REQUIRE(io::sprint("{0} {1} {0}"_s, 1, 2) == "1 2 1");
        REQUIRE(io::sprint("{0} + {0} = {1}"_s, 1, 2) == "1 + 1 = 2");
        REQUIRE(io::sprint("{{0}} {{1}}"_s, 'a', 'b') == "{a} {b}");
        auto&& longer = io::sprint("{0}{1}{2}{3}{4}{5}{6}{7}{8}{9}{10}{11}"_s, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
        REQUIRE(longer == "123456789101112");
        REQUIRE(io::sprint("{{{{{0}"_s, 1) == "{{{{1");
        REQUIRE(io::sprint("{{{{{0}{{"_s, 1) == "{{{{1{{");
        REQUIRE(io::sprint("{{{{{0}{{}{}"_s, 1) == "{{{{1{{}{}");
        REQUIRE(io::sprint(true ? "[{0}]" : "{{0}}"_s, 10) == "[10]");
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
}
