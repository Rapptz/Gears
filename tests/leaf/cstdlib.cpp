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
#include <gears/leaf/cstdlib.hpp>

// macro to have every static assertion count towards total assertions
#define required(...) static_assert(__VA_ARGS__, #__VA_ARGS__); REQUIRE(true)

namespace gl = gears::leaf;

TEST_CASE("constexpr cstdlib", "[gears-constexpr-cstdlib]") {
    constexpr auto d = gl::div(9, 4);
    required(d.quot == 1);
    required(d.rem == 2);

    required(gl::abs(-10) == 10);
    required(gl::abs(-0.0f) == 0.0f);

    required(gl::atoi<int>("10") == 10);
    required(gl::atoi<long long>("21474836481") == 21474836481LL);
    required(gl::atoi<int>("-10") == -10);
    required(gl::atoi<unsigned>("-1") == static_cast<unsigned>(-1));
}
