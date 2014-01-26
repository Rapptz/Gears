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

#ifndef GEARS_CONCEPTS_HPP
#define GEARS_CONCEPTS_HPP

#include "concepts/container.hpp"
#include "concepts/function.hpp"

/**
 * @defgroup concepts Concepts module
 * 
 * @brief Provides an interface for concept checking.
 * 
 * @details This module is the basic implementation of Concepts
 * that were supposed to appear in C++11 but didn't make it due to
 * time constraints.
 * 
 * Concepts are split into two categories, Unary and Binary. A Unary Concept
 * is defined as a concept that takes in a single type. A Binary Concept is a
 * concept that takes in two types. Sometimes the second type is optional, this
<<<<<<< HEAD
 * depends on the Concept. Sometimes a concept is not part of these categories, this
 * makes the concept uncategorised. An example of this is Constructible.
=======
 * depends on the Concept.
>>>>>>> a8c3fd363a0f368ebf5ec78012dd2ecec67b3c4c
 * 
 * Just like the Concepts themselves are split into different categories, the
 * Concepts module itself is split into different categories which include:
 * 
 * - **Basic**: Concepts involving constructibility and operational semantics.
 * - **Container**: Concepts for checking container semantics and traits.
 * - **Function**: Concepts for checking function semantics and traits. 
 * - **Iterator**: Concepts for checking iterator categories.
 * 
 * The usage of Concepts is simple, most of which needs one function to assert 
 * your concepts.
 * 
 * Example:
 * 
 * @code 
 * #include <gears/concepts.hpp>
 * #include <vector>
 * using namespace gears::concepts;
 * 
 * template<typename Cont, typename T>
 * void compare_and_insert(Cont& c, const T& first, const T& second) {
 *     // first < second must be well defined.
 *     requires<T, LessThanComparable>();
 *     
 *     // Cont must be a sequence container
 *     requires<Cont, SequenceContainer>();
 *     
 *     if(first < second) {
 *         c.push_back(first);
 *     }
 *     else {
 *         c.push_back(second);
 *     }
 * }
 * 
 * int main() {
 *     std::vector<int> v = {1,2,3,4,5,6,7,8,9,10};
 *     compare_and_insert(v, 11, 12);
 * }
 * @endcode
 * 
 */

#endif // GEARS_CONCEPTS_HPP