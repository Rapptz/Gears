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

#ifndef GEARS_META_META_HPP
#define GEARS_META_META_HPP

#include <type_traits>
#include <utility>

namespace gears {
namespace meta {
/**
 * @ingroup meta
 */
template<typename T>
using Type = typename T::type;

/**
 * @ingroup meta
 * @brief Template alias for `std::common_type`.
 */
template<typename... Args>
using CommonType = Type<std::common_type<Args...>>;


/**
 * @ingroup meta
 * @brief Template alias for `std::underlying_type`.
 */
template<typename T>
using UnderlyingType = Type<std::underlying_type<T>>;


/**
 * @ingroup meta
 * @brief Template alias for `std::integral_constant`.
 */
template<typename T, T t>
using Const = std::integral_constant<T,t>;


/**
 * @ingroup meta
 */
template<int i>
using Integer = Const<int,i>;

struct deduced {};

template<typename T>
using is_deduced = std::is_same<T, deduced>;

/**
 * @ingroup meta
 * @brief Identity meta function
 * @details The identity meta function. Typically
 * used for lazy evaluation or forced template parameter
 * evaluation.
 *
 */
template<typename T>
struct identity {
    using type = T;
};

/**
 * @ingroup meta
 * @brief Void meta function.
 * @details Void meta function. Used to swallow
 * arguments and evaluate to void.
 *
 */
template<typename...>
struct void_ {
    using type = void;
};

/**
 * @ingroup meta
 * @brief Template alias for void meta function.
 */
template<typename... T>
using Void = Type<void_<T...>>;

/**
 * @ingroup meta
 * @brief Template alias for `std::integral_constant<bool, B>`.
 */
template<bool B>
using Bool = Const<bool, B>;

/**
 * @ingroup meta
 * @brief Template alias for `std::conditional`.
 * @details Template alias for `std::conditional`. Evaluates
 * the `Condition` as if `Condition::value` was passed.
 *
 * Example:
 *
 * @code
 * // passes the static_assert
 * static_assert(std::is_same<meta::If<std::is_integral<int>, double&, int&>, double&>::value, "...");
 * @endcode
 */
template<typename Condition, typename Then, typename Else>
using If = Type<std::conditional<Condition::value, Then, Else>>;

/**
 * @ingroup meta
 * @brief Lazy evaluation of `If`
 */
template<typename Condition, typename Then, typename Else>
using TypeIf = Type<If<Condition, Then, Else>>;

/**
 * @ingroup meta
 * @brief Logical Not meta function
 * @details The equivalent of `operator!` for bools
 * except for meta functions. Returns `std::true_type` or
 * `std::false_type`.
 *
 * Example:
 *
 * @code
 * // passes the static_assert
 * static_assert(meta::Not<std::is_integral<float>>::value, "...");
 * @endcode
 *
 * @tparam T Meta function to use logical not on.
 */
template<typename T>
struct Not : Bool<!T::value> {};

/**
 * @ingroup meta
 * @brief Logical Or meta function
 * @details The equivalent of `operator||` for bools
 * except for meta functions. Evaluates it based on the
 * argument's `::value`. Returns `std::true_type` or
 * `std::false_type`.
 *
 * @code
 * // passes the static_assert
 * static_assert(meta::Any<std::is_integral<int>, std::is_const<float>, std::is_function<int>>::value, "...");
 * @endcode
 *
 * @tparam Args Meta functions to use logical or on.
 */
template<typename... Args>
struct Any : Bool<false> {};

template<typename T, typename... Args>
struct Any<T, Args...> : If<T, Bool<true>, Any<Args...>> {};

/**
 * @ingroup meta
 * @brief Logical And meta function
 * @details The equivalent of `operator&&` for bools
 * except for meta functions. Evaluates it based on the
 * argument's `::value`. Returns `std::true_type` or
 * `std::false_type`.
 *
 * @code
 * // fails the static_assert
 * static_assert(meta::All<std::is_integral<int>, std::is_const<float>, std::is_function<int>>::value, "...");
 * @endcode
 *
 * @tparam Args Meta functions to use logical and on.
 */
template<typename... Args>
struct All : Bool<true> {};

template<typename T, typename... Args>
struct All<T, Args...> : If<T, All<Args...>, Bool<false>> {};

template<typename Signature, typename Anon = void>
struct result_of_impl {};

template<typename Function, typename... Args>
struct result_of_impl<Function(Args...), Void<decltype(std::declval<Function>()(std::declval<Args>()...))>> {
    using type = decltype(std::declval<Function>()(std::declval<Args>()...));
};

/**
 * @ingroup meta
 * @brief SFINAE-safe `std::result_of` alternative
 */
template<typename Signature>
using ResultOf = Type<result_of_impl<Signature>>;

/**
 * @ingroup meta
 * @brief Class of meta function.
 * @details Class of meta function. Evaluates the
 * underlying class of a member function pointer.
 *
 * Example:
 *
 * @code
 * #include <gears/meta.hpp>
 *
 * namespace meta = gears::meta;
 *
 * struct f {
 *     int g() {
 *         return 10;
 *     }
 * };
 *
 * int main() {
 *     // passes static_assert
 *     static_assert(std::is_same<meta::ClassOf<decltype(&f::g)>, f>::value, "...");
 * }
 * @endcode
 */
template<typename T>
struct class_of {};

template<typename Signature, typename Class>
struct class_of<Signature Class::*> : identity<Class> {};

/**
 * @ingroup meta
 * @brief Template alias for `class_of` meta function.
 */
template<typename T>
using ClassOf = Type<class_of<T>>;

/**
 * @ingroup meta
 * @brief Returns a non-const lvalue reference as a const lvalue reference.
 *
 * @param t lvalue reference to turn to const lvalue reference.
 * @return const lvalue reference.
 */
template<typename T>
constexpr const T& as_const(T& t) {
    return t;
}

template<typename T>
constexpr T&& cforward(typename std::remove_reference<T>::type& t) noexcept {
    return static_cast<T&&>(t);
}

/**
 * @ingroup meta
 * @brief constexpr enabled alternative to `std::forward`.
 *
 * @param t variable to forward
 * @tparam T Type of parameter being forwarded.
 * @return `static_cast<T&&>(t)`.
 */
template<typename T>
constexpr T&& cforward(typename std::remove_reference<T>::type&& t) noexcept {
    static_assert(!std::is_lvalue_reference<T>(), "error");
    return static_cast<T&&>(t);
}

/**
 * @ingroup meta
 * @brief constexpr enabled alternative to `std::move`.
 *
 * @param t variable to move
 * @tparam T Type of parameter being enabled to be moved.
 * @return `static_cast<RemoveRef<T>&&>(t)`.
 */
template<typename T>
constexpr typename std::remove_reference<T>::type&& cmove(T&& t) noexcept {
    return static_cast<typename std::remove_reference<T>::type&&>(t);
}
} // meta
} // gears

#endif // GEARS_META_META_HPP
