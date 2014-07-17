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

#ifndef GEARS_CONTAINER_HPP
#define GEARS_CONTAINER_HPP

#include "container/static_vector.hpp"

/**
 * @defgroup container Container module
 * @brief Provides new containers and tools to aid with standard containers.
 *
 * @details This module extends the standard containers through new containers and
 * new allocators that help with the current containers.
 *
 * Example usage:
 *
 * @code
 * #include <iostream>
 * #include <gears/container/static_vector.hpp>
 *
 * using namespace gears::container;
 *
 * int main() {
 *     static_vector<int, 10> v;
 *     std::cout << v.size() << '\n';
 *     for(unsigned i = 0; i < v.max_size(); ++i) {
 *         v.push_back(i);
 *     }
 *     std::cout << v.size() << '\n';
 * }
 * @endcode
 *
 * Output:
 * <pre>
 * 0
 * 10
 * </pre>
 */

#endif // GEARS_CONTAINER_HPP
