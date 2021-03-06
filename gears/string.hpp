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

#ifndef GEARS_STRING_HPP
#define GEARS_STRING_HPP

#include <gears/string/case.hpp>
#include <gears/string/predicate.hpp>
#include <gears/string/literals.hpp>
#include <gears/string/replace.hpp>
#include <gears/string/trim.hpp>
#include <gears/string/transforms.hpp>
#include <gears/string/lexical_cast.hpp>

/**
 * @defgroup string String module
 * @brief Provides string algorithms
 * @details This module provides string algorithms to help
 * with the lack of high level algorithms with `std::string`.
 * All the functions do not modify the string in-place and instead
 * return a new string.
 *
 * Under the `<gears/string/literals.hpp>` header there is a
 * user defined literal `_s` to help construct a string easier.
 * It's provided for all `basic_string` types, e.g. `std::wstring`,
 * `std::string`, etc.
 *
 * @code
 * using namespace gears::string::literals; // required
 * auto str = "hello world"_s; // decltype(str) is std::string
 * @endcode
 */

#endif // GEARS_STRING_HPP
