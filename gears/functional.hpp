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

#ifndef GEARS_FUNCTIONAL_HPP
#define GEARS_FUNCTIONAL_HPP

#include "functional/arithmetic_operators.hpp"
#include "functional/bitwise_operators.hpp"
#include "functional/logical_operators.hpp"
#include "functional/comparison_operators.hpp"
#include "functional/numeric_properties.hpp"
#include "functional/invoke.hpp"
#include "functional/partial.hpp"
#include "functional/compose.hpp"

/**
 * @defgroup functional Functional module
 *
 * @brief Provides support for functional programming.
 *
 * @details This module provides multiple function objects (also called
 * functors) and operations that make working in a functional manner easier.
 *
 * All of the function objects have a `constexpr` instantiation to allow working
 * with the other components of the module easier. It also allows the user to use the
 * function objects just like a regular function.
 *
 * There's also basic support for partial function application and composition.
 * More support for other things are coming soon.
 *
 * Example usage:
 * @code
 * #include <gears/functional.hpp>
 * #include <iostream>
 *
 * namespace fn = gears::functional;
 *
 * int main() {
 *     auto f = fn::compose(fn::even, fn::plus);
 *              // equivalent to
 *              // fn::even(fn::plus(...))
 *     std::cout << f(11, 15);
 * }
 * @endcode
 *
 * Output:
 * <pre>
 * 1
 * </pre>
 */

 /**
 * @defgroup functional_objects Function objects submodule
 * @ingroup functional
 *
 * @brief Provides function objects to use.
 * @details A function object is any object for which the function
 * call operator is defined. An instance of a function object could
 * be called just like a regular function and could emulate functions
 * as first class citizens.
 */

#endif // GEARS_FUNCTIONAL_HPP
