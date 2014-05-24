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

#ifndef GEARS_CONCEPTS_FUNCTION_HPP
#define GEARS_CONCEPTS_FUNCTION_HPP

#include "alias.hpp"
#include <utility>

namespace gears {
namespace concepts {
namespace detail {
template<typename...>
struct void_type {
    using type = void;
};

template<typename... Args>
using Void_ = typename void_type<Args...>::type;

template<typename T>
void sink(T);

template<typename T, typename... Args>
using FRet = decltype(std::declval<T>()(std::declval<Args>()...));

template<typename T, typename Signature, typename = void>
struct is_callable : std::false_type {
    static_assert(std::is_function<Signature>(), "Signature must be a function");
};

template<typename T, typename = concept_checker_t>
struct is_function_impl : std::is_function<T> {};

template<typename T>
struct is_function_impl<T, TrueIf<std::is_class<Bare<T>>>> {
    using yes = char;
    using no = struct { char s[2]; };

    struct F { void operator()(); };
    struct Derived : T, F { };
    template<typename U, U> struct Check;

    template<typename V>
    static no test(Check<void (F::*)(), &V::operator()>*);

    template<typename>
    static yes test(...);

    static const bool value = sizeof(test<Derived>(0)) == sizeof(yes);
};

template<typename T, typename R, typename... Args>
struct is_callable<T, R(Args...), Void_<decltype(sink<R>(std::declval<T>()(std::declval<Args>()...)))>> : std::true_type {};

template<typename T, typename... Args>
struct is_callable<T, void(Args...), Void_<FRet<T, Args...>>> : std::is_void<FRet<T, Args...>> {};

struct is_generator {
    template<typename T>
    static auto test(int) -> decltype(std::declval<T&>()(), std::true_type{}) {}
    template<typename>
    static std::false_type test(...);
};
} // detail

/**
 * @defgroup function_concepts Function concepts submodule
 * @ingroup concepts
 * 
 * @brief Concepts involving functions.
 * 
 * @details A collection of concepts that deal with how functions
 * are used or invoked. Unfortunately, many of the useful function
 * concepts are not possible without compiler magic, and thus this 
 * collection is the least exhaustive. 
 */

/**
 * @ingroup function_concepts
 * @brief Checks if a function is callable with a certain signature.
 * @details A Binary concept that checks if a function can be called with
 * a certain provided signature.
 * 
 * For example, `void f(int)` can be met with `Callable<T, void(int)>`.
 * 
 * @tparam T Type to check.
 * @tparam Signature Signature of the function to check.
 */
template<typename T, typename Signature>
struct Callable : detail::is_callable<T, Signature> {};

/**
 * @ingroup function_concepts
 * @brief Checks if a function returns nothing.
 * @details A Unary concept that checks if a function returns nothing (i.e. `void`).
 * 
 * For example. `void f(int, int);` meets the concept of `Generator`.
 * 
 * @tparam T Type to check.
 */
template<typename T>
struct Generator : TraitOf<detail::is_generator, T> {};

/**
 * @ingroup function_concepts
 * @brief Checks if a type can be called in general.
 * @details A Unary concept that checks if a function or type can be invoked
 * through an `operator()`.  
 * 
 * @tparam T Type to check.
 */
template<typename T>
struct Function : std::integral_constant<bool, detail::is_function_impl<typename std::remove_pointer<T>::type>::value> {};
} // concepts
} // gears

#endif // GEARS_CONCEPTS_FUNCTION_HPP
