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
#include <tuple>
#include <gears/utility/triple.hpp>
#include <gears/adl/get.hpp>

TEST_CASE("Triples", "[triple]") {
    constexpr gears::triple<int, float, char> a = {1, 2.f, '3'};
    static_assert(a.first  == 1  , "..");
    static_assert(a.second == 2.f, "..");
    static_assert(a.third  == '3', "..");
    static_assert(gears::adl::get<0>(a) == 1, "..");
    static_assert(gears::adl::get<1>(a) == 2.f, "..");
    static_assert(gears::adl::get<2>(a) == '3', "..");
    constexpr auto b = gears::make_triple(20, 3.f, 'b');
    static_assert(a != b, "..");
    static_assert(a < b, "..");
    static_assert(a <= b, "..");
    constexpr auto c = a;
    static_assert(a == c, "..");
}
