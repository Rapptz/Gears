// The MIT License (MIT)

// Copyright (c) 2012-2015 Danny Y., Rapptz

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
#include <string>
#include <gears/tuple.hpp>

using namespace gears;

struct accumulator {
    size_t total = 0;

    void operator()(float f) {
        total += static_cast<size_t>(f);
    }

    void operator()(const std::string& str) {
        total += str.size();
    }

    void operator()(int x) {
        total += x;
    }
};

TEST_CASE("for-each", "[tuple-for-each") {
    auto tup = std::make_tuple(10, "hello", 3.14f);
    accumulator f;
    tuple::for_each(tup, f);
    REQUIRE(f.total == 18);
}

TEST_CASE("invoke", "[tuple-invoke]") {
    auto tup = std::make_tuple(10, "hello world", '0');

    const auto func = [](int x, std::string str, char c) {
        return x + str.size() + (c - '0');
    };

    REQUIRE(tuple::invoke(func, tup) == 21);
}
