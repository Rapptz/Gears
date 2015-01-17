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
#include <gears/leaf/string.hpp>

// macro to have every static assertion count towards total assertions
#define required(...) static_assert(__VA_ARGS__, #__VA_ARGS__); REQUIRE(true)

namespace gl = gears::leaf;

TEST_CASE("constexpr strings", "[gears-const-string]") {
    constexpr auto hello = gl::make_string("hello");
    required(hello == gl::make_string("hello"));
    required(hello.size() == 5);
    required(hello.max_size() == 6);
    required(!hello.empty());
    required(hello[0] == 'h');
    required(hello.front() == 'h');
    required(hello.back() == 'o');
    required(hello[3] == 'l');

    constexpr auto empty = gl::make_string("");
    required(empty.empty());
    required(empty.capacity() == 1);

    // find algorithms

    // find
    required(hello.find('h') == 0);
    required(hello.find('o') == 4);
    required(hello.find('l') == 2);
    required(hello.find('l', 3) == 3);
    required(hello.find('x') == hello.npos);
    required(hello.find(gl::make_string("ll")) == 2);
    required(hello.find(hello) == 0);
    required(hello.find(empty) == 0);
    required(empty.find('x') == empty.npos);

    constexpr auto hello2 = gl::make_string("hello hello");
    required(hello2.find(hello) == 0);
    required(hello2.find(hello, hello.size()) == 6);

    // rfind
    required(hello.rfind('h') == 0);
    required(hello.rfind('o') == 4);
    required(hello.rfind('l') == 3);
    required(hello.rfind('l', 0) == hello.npos);
    required(hello.rfind('x') == hello.npos);
    required(hello.rfind(gl::make_string("ll")) == 2);
    required(hello.rfind(hello) == 0);
    required(hello.rfind(empty) == 5);
    required(empty.rfind('x') == empty.npos);
    required(hello2.rfind(hello) == 6);
    required(hello2.rfind(hello, 0) == 0);

    // find_first_of
    required(hello.find_first_of('e') == 1);
    required(hello.find_first_of('l') == 2);
    required(hello.find_first_of(gl::make_string("abcde")) == 1);
    required(hello2.find_first_of(hello) == 0);
    required(hello2.find_first_of('l') == hello2.find('l'));
    required(hello.find_first_of(gl::make_string("qzxl")) == 2);
    required(hello.find_first_of(empty) == hello.npos);
    required(hello.find_first_of(gl::make_string("abce"), 3) == hello.npos);
    required(hello.find_first_of(gl::make_string("xyz")) == hello.npos);

    // find_first_not_of
    required(hello.find_first_not_of('x') == 0);
    required(hello.find_first_not_of(gl::make_string("elh")) == 4);
    required(hello.find_first_not_of(hello) == hello.npos);
    required(hello.find_first_not_of(empty) == 0);
    required(hello2.find_first_not_of(hello) == 5);

    // find_last_of
    required(hello.find_last_of('x') == hello.npos);
    required(hello.find_last_of('l') == 3);
    required(hello.find_last_of(empty) == hello.npos);
    required(hello.find_last_of(gl::make_string("abcdel")) == 3);
    required(hello.find_last_of(gl::make_string("axcl")) == 3);
    required(hello2.find_last_of('l') == 9);
    required(hello2.find_last_of(hello) == 10);

    // find_last_not_of
    required(hello.find_last_not_of('x') == hello.size() - 1);
    required(hello.find_last_not_of(empty) == hello.size() - 1);
    required(hello.find_last_not_of(gl::make_string("lo")) == 1);
    required(hello2.find_last_not_of(hello) == 5);

    // comparison operators
    required(hello == hello);
    required(hello != empty);
    required(hello != hello2);
    required(hello2 > hello);
    required(hello < hello2);
    required(hello > empty);
    required(hello2 > empty);
    required(hello >= hello);
    required(empty <= hello);
    required(gl::make_string("cat") > gl::make_string("animal"));
    required(gl::make_string("dog") > gl::make_string("cat"));

    // appending
    required(hello + gl::make_string(" world") == gl::make_string("hello world"));
    required(hello + hello == gl::make_string("hellohello"));
    required(hello + ' ' + hello == hello2);
}

#undef required
