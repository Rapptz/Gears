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

#ifndef GEARS_CONCEPTS_BASIC_HPP
#define GEARS_CONCEPTS_BASIC_HPP

#include "alias.hpp"

namespace gears {
template<typename T>
using DefaultConstructible = std::is_default_constructible<Bare<T>>;

template<typename T>
using MoveConstructible = std::is_move_constructible<Bare<T>>;

template<typename T>
using CopyConstructible = std::is_copy_constructible<Bare<T>>;

template<typename T>
using MoveAssignable = std::is_move_assignable<Bare<T>>;

template<typename T>
using CopyAssignable = std::is_copy_assignable<Bare<T>>;

template<typename T>
using Movable = And<MoveAssignable<T>, MoveConstructible<T>>;

template<typename T>
using Copyable = And<CopyAssignable<T>, CopyConstructible<T>>;

template<typename T>
using Assignable = And<MoveAssignable<T>, CopyAssignable<T>>;

template<typename T>
using Destructible = std::is_destructible<Bare<T>>;

template<typename T>
using Constructible = std::is_constructible<Bare<T>>;

template<typename T>
using StandardLayout = std::is_standard_layout<Bare<T>>;

template<typename T>
using POD = std::is_pod<Bare<T>>;
} // gears

#endif // GEARS_CONCEPTS_BASIC_HPP