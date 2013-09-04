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

#ifndef GEARS_META_META_HPP
#define GEARS_META_META_HPP

#include <type_traits>
#include <utility>

namespace gears {
template<typename T>
using Type = typename T::type;

template<typename... Args>
using CommonType = Type<std::common_type<Args...>>;

template<typename T>
using UnderlyingType = Type<std::underlying_type<T>>;

template<typename T, T t>
using Const = std::integral_constant<T,t>;

template<int i>
using Integer = Const<int,i>;

template<typename T>
struct identity {
    using type = T;
};

template<typename...>
struct void_ { 
    using type = void;
};

template<typename... T>
using Void = Type<void_<T...>>;

template<bool I>
using Bool = Const<bool, I>;

template<typename If, typename Then, typename Else>
using Conditional = Type<std::conditional<If::value, Then, Else>>;

template<typename T>
using Not = Bool<!T::value>;

template<typename... Args>
struct Any : Bool<false> {};

template<typename T, typename... Args>
struct Any<T, Args...> : Conditional<T, Bool<true>, Any<Args...>> {};

template<typename... Args>
struct All : Bool<true> {};

template<typename T, typename... Args>
struct All<T, Args...> : Conditional<T, All<Args...>, Bool<false>> {};

template<typename Signature, typename Anon = void>
struct result_of_impl {};

template<typename Function, typename... Args>
struct result_of_impl<Function(Args...), Void<decltype(std::declval<Function>()(std::declval<Args>()...))>> {
    using type = decltype(std::declval<Function>()(std::declval<Args>()...));
};

template<typename Signature>
using ResultOf = Type<result_of_impl<Signature>>;

template<typename T>
constexpr const T& as_const(T& t) {
    return t;
}

template<typename T>
constexpr T abs(T t) {
    return t < 0 ? -t : t;
}

template<typename T>
constexpr T min(T&& t) {
    return std::forward<T>(t);
}

template<typename T, typename U>
constexpr auto min(T&& t, U&& u) -> CommonType<T,U> {
    return t < u ? std::forward<T>(t) : std::forward<U>(u);
}

template<typename T, typename U, typename... Args>
constexpr auto min(T&& t, U&& u, Args&&... args) -> CommonType<T,U,Args...> {
    return min(min(std::forward<T>(t), std::forward<U>(u)), std::forward<Args>(args)...);
}

template<typename T>
constexpr T max(T&& t) {
    return std::forward<T>(t);
}

template<typename T, typename U>
constexpr auto max(T&& t, U&& u) -> CommonType<T,U> {
    return t > u ? std::forward<T>(t) : std::forward<U>(u);
}

template<typename T, typename U, typename... Args>
constexpr auto max(T&& t, U&& u, Args&&... args) -> CommonType<T,U,Args...> {
    return max(max(std::forward<T>(t), std::forward<U>(u)), std::forward<Args>(args)...);
}
} // gears

#endif // GEARS_META_META_HPP