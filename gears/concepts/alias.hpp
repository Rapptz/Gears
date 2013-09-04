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

#ifndef GEARS_CONCEPTS_ALIAS_HPP
#define GEARS_CONCEPTS_ALIAS_HPP

#include <type_traits>

namespace gears {
template<typename T>
using NoRef = typename std::remove_reference<T>::type;

template<typename T>
using ConstLRef = const NoRef<T>&;

template<typename T>
using LRef = NoRef<T>&;

template<typename T>
using RRef = NoRef<T>&&;

template<typename... Args>
struct And : std::true_type {};

template<typename T, typename... Args>
struct And<T, Args...> : std::conditional<T::value, And<Args...>, std::false_type>::type {};

template<typename... Args>
struct Or : std::false_type {};

template<typename T, typename... Args>
struct Or<T, Args...> : std::conditional<T::value, std::true_type, Or<Args...>>::type {};

template<typename Test, typename... Args>
using TraitOf = decltype(Test::template test<Args...>(0));

enum class concept_checker_t {};

template<typename... Concepts>
struct require_checker {
    static_assert(And<Concepts...>(), "Concept Violation");
    using type = concept_checker_t;
};

template<typename... Concepts>
using Require = typename require_checker<Concepts...>::type;

template<typename... Concepts>
using TrueIf = typename std::enable_if<And<Concepts...>::value, concept_checker_t>::type;

template<typename T, template<typename...> class... Concepts>
constexpr bool require() {
    static_assert(And<Concepts<T>...>(), "Concept Violation");
    return true;
}
} // gears

#endif // GEARS_CONCEPTS_ALIAS_HPP