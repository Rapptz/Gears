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

#ifndef GEARS_FUNCTIONAL_PARTIAL_HPP
#define GEARS_FUNCTIONAL_PARTIAL_HPP

#include <gears/adl/get.hpp>
#include <gears/meta/indices.hpp>
#include <gears/meta/conditional.hpp>
#include <gears/meta/qualifiers.hpp>

namespace gears {
namespace functional {
namespace detail {
template<typename Tuple>
using IndicesFor = meta::make_index_sequence<std::tuple_size<Tuple>::value>;

template<typename F, typename Tuple, size_t... Indices,
         typename Return = decltype(std::declval<F>()(adl::get<Indices>(std::declval<Tuple>())...))>
constexpr Return invoke_impl(F&& f, Tuple&& t, meta::index_sequence<Indices...>) {
    return std::forward<F>(f)(adl::get<Indices>(std::forward<Tuple>(t))...);
}

template<typename F, typename Tuple,
         typename Return = decltype(invoke_impl(std::declval<F>(), std::declval<Tuple>(), IndicesFor<Tuple>{}))>
constexpr Return invoke_tup(F&& f, Tuple&& tuple) {
    return invoke_impl(std::forward<F>(f), std::forward<Tuple>(tuple), IndicesFor<Tuple>{});
}

struct is_reference_wrapper_impl {
    template<typename T, typename U = typename T::type>
    static auto test(int) -> decltype(std::declval<T&>().get(), std::is_convertible<T, U&>{}) {}
    template<typename...>
    static std::false_type test(...);
};

template<typename T>
struct is_reference_wrapper : decltype(is_reference_wrapper_impl::test<T>(0)) {};

template<typename T>
struct unref {
    using type = typename T::type&;
};

template<typename T>
struct special_decay {
    using type = meta::lazy_if<is_reference_wrapper<T>, unref<T>, meta::identity<T>>;
};

template<typename T>
using SpecialDecay = meta::eval<special_decay<meta::decay_t<T>>>;
} // detail

template<typename Function, typename... Args>
struct partial_type {
    using tuple_type = std::tuple<Args...>;
private:
    Function func;
    tuple_type args;
public:
    constexpr partial_type(Function&& f, tuple_type n) noexcept: func(std::forward<Function>(f)), args(std::move(n)) {}

    template<typename... T>
    constexpr auto operator()(T&&... t) -> decltype(detail::invoke_tup(func, std::tuple_cat(std::move(args), std::make_tuple(t...)))) {
        return detail::invoke_tup(func, std::tuple_cat(std::move(args), std::make_tuple(t...)));
    }
};

template<typename Function, typename... Args>
constexpr partial_type<Function, detail::SpecialDecay<Args>...> partial(Function&& f, Args&&... args) {
    return { std::forward<Function>(f), std::make_tuple(args...) };
}
} // functional
} // gears

#endif // GEARS_FUNCTIONAL_PARTIAL_HPP
