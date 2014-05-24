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

#ifndef GEARS_META_ALIAS_HPP
#define GEARS_META_ALIAS_HPP

#include "meta.hpp"

namespace gears {
namespace meta {
namespace alias_detail {
enum class enabler { _ };
} // alias_detail

constexpr auto _ = alias_detail::enabler::_;

template<typename... Args>
using EnableIf = Type<std::enable_if<All<Args...>::value, alias_detail::enabler>>;

template<typename... Args>
using DisableIf = Type<std::enable_if<meta::Not<All<Args...>>::value, alias_detail::enabler>>;

template<typename T>
using Decay = Type<std::decay<T>>;

template<typename T>
using RemoveRef = Type<std::remove_reference<T>>;

template<typename T>
using RemoveCV = Type<std::remove_cv<T>>;

template<typename T>
using RemoveConst = Type<std::remove_const<T>>;

template<typename T>
using RemoveVolatile = Type<std::remove_volatile<T>>;

template<typename T>
using RemoveExtents = Type<std::remove_all_extents<T>>;

template<typename T>
using RemovePointer = Type<std::remove_pointer<T>>;

template<typename T>
using AddLValueRef = Type<std::add_lvalue_reference<T>>;

template<typename T>
using AddRValueRef = Type<std::add_rvalue_reference<T>>;

template<typename T>
using AddCV = Type<std::add_cv<T>>;

template<typename T>
using AddConst = Type<std::add_const<T>>;

template<typename T>
using AddVolatile = Type<std::add_volatile<T>>;

template<typename T>
using AddPointer = Type<std::add_pointer<T>>;

template<typename T>
using MakeSigned = Type<std::make_signed<T>>;

template<typename T>
using MakeUnsigned = Type<std::make_unsigned<T>>;

template<typename T>
using Unqualified = RemoveCV<RemoveRef<T>>;

template<typename T>
using ValueType = typename Unqualified<T>::value_type;

template<typename T>
using StorageFor = Type<std::aligned_storage<sizeof(T), std::alignment_of<T>::value>>;
} // meta
} // gears

#endif // GEARS_META_ALIAS_HPP