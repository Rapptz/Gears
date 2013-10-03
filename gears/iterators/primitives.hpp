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

#ifndef GEARS_ITERATORS_PRIMITIVES_HPP
#define GEARS_ITERATORS_PRIMITIVES_HPP

#include <iterator>

namespace gears {
template<typename... Args>
struct input_iterator : std::iterator<std::input_iterator_tag, Args...> {};

template<typename... Args>
struct random_access_iterator : std::iterator<std::random_access_iterator_tag, Args...> {};

template<typename... Args>
struct bidirectional_iterator : std::iterator<std::bidirectional_iterator_tag, Args...> {};

template<typename... Args>
struct forward_iterator : std::iterator<std::forward_iterator_tag, Args...> {};

template<typename... Args>
struct output_iterator : std::iterator<std::output_iterator_tag, Args...> {};
} // gears

#endif // GEARS_ITERATORS_PRIMITIVES_HPP