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
#include <memory>
#include <vector>
#include <forward_list>
#include <array>
#include <set>
#include <gears/concepts.hpp>

using namespace gears::concepts;

TEST_CASE("Concepts", "[concepts]") {
    struct x {};
    SECTION("basic", "[concepts-basic]") {
        REQUIRE((requires<x, DefaultConstructible, CopyConstructible, MoveConstructible>()));
        REQUIRE((requires<int, Integral, Signed, Decrementable, Incrementable>()));
        REQUIRE((requires<float, FloatingPoint>()));
        REQUIRE((requires<unsigned int, Unsigned>()));
        REQUIRE((requires<x*, Pointer, NullablePointer, Dereferenceable>()));
        REQUIRE((requires<x&&, RValueReference, Reference>()));
        REQUIRE((requires<x&, LValueReference, LValueSwappable, Reference>()));
        REQUIRE((requires<std::shared_ptr<int>, NullablePointer, MoveConstructible, Dereferenceable>()));
        REQUIRE((requires<std::unique_ptr<int>, ContextualBool, Dereferenceable, MoveConstructible>()));
        REQUIRE((requires<std::vector<int>, Regular, Comparable, LessThanComparable>()));
    }

    SECTION("container", "[concepts-container]") {
        REQUIRE((requires<std::vector<int>, Container, SequenceContainer, AllocatorAwareContainer, ReversibleContainer>()));
        REQUIRE((requires<std::array<int, 5>, Container, SequenceContainer, ReversibleContainer>()));
        REQUIRE((requires<std::forward_list<int>, Container, SequenceContainer, AllocatorAwareContainer>()));
        REQUIRE((requires<std::set<int>, Container, AssociativeContainer>()));
    }

    SECTION("iterator", "[concepts-iterator]") {
        REQUIRE((requires<int*, RandomAccessIterator, MutableRandomAccessIterator>()));
        REQUIRE((requires<std::forward_list<int>::iterator, ForwardIterator>()));
        REQUIRE((requires<std::vector<int>::iterator, RandomAccessIterator, MutableRandomAccessIterator>()));
    }

    SECTION("function", "[concepts-function]") {
        auto f = [](int x) { return x*3; };
        REQUIRE((Callable<decltype(f), int(int)>::value));
        REQUIRE(Function<decltype(f)>::value);
        auto g = [](){};
        REQUIRE(Generator<decltype(g)>::value);
    }
}