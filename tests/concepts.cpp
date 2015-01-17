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
        REQUIRE((require<x, DefaultConstructible, CopyConstructible, MoveConstructible>()));
        REQUIRE((require<int, Integral, Signed, Decrementable, Incrementable>()));
        REQUIRE((require<float, FloatingPoint>()));
        REQUIRE((require<unsigned int, Unsigned>()));
        REQUIRE((require<x*, Pointer, NullablePointer, Dereferenceable>()));
        REQUIRE((require<x&&, RValueReference, Reference>()));
        REQUIRE((require<x&, LValueReference, LValueSwappable, Reference>()));
        REQUIRE((require<std::shared_ptr<int>, NullablePointer, MoveConstructible, Dereferenceable>()));
        REQUIRE((require<std::unique_ptr<int>, ContextualBool, Dereferenceable, MoveConstructible>()));
        REQUIRE((require<std::vector<int>, Regular, Comparable, LessThanComparable>()));
    }

    SECTION("container", "[concepts-container]") {
        REQUIRE((require<std::vector<int>, Container, SequenceContainer, AllocatorAwareContainer, ReversibleContainer>()));
        REQUIRE((require<std::array<int, 5>, Container, SequenceContainer, ReversibleContainer>()));
        REQUIRE((require<std::forward_list<int>, Container, SequenceContainer, AllocatorAwareContainer>()));
        REQUIRE((require<std::set<int>, Container, AssociativeContainer>()));
    }

    SECTION("iterator", "[concepts-iterator]") {
        REQUIRE((require<int*, RandomAccessIterator, MutableRandomAccessIterator>()));
        REQUIRE((require<std::forward_list<int>::iterator, ForwardIterator>()));
        REQUIRE((require<std::vector<int>::iterator, RandomAccessIterator, MutableRandomAccessIterator>()));
    }

    SECTION("function", "[concepts-function]") {
        auto f = [](int x) { return x*3; };
        REQUIRE((Callable<decltype(f), int(int)>::value));
        REQUIRE(Function<decltype(f)>::value);
        auto g = [](){};
        REQUIRE(Generator<decltype(g)>::value);
    }
}
