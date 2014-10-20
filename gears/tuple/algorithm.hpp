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

#ifndef GEARS_TUPLE_ALGORITHM_HPP
#define GEARS_TUPLE_ALGORITHM_HPP

#include <gears/meta/indices.hpp>
#include <gears/meta/expand.hpp>
#include <gears/adl/get.hpp>
#include <tuple>

namespace gears {
namespace tuple {
namespace detail {
template<typename Tuple>
using indices_for = meta::make_index_sequence<std::tuple_size<Tuple>::value>;

template<typename Tuple, typename Function, size_t... Indices>
constexpr decltype(nullptr) for_each(const Tuple& tuple, Function&& f, meta::index_sequence<Indices...>) {
    return GEARS_EXPAND(f(adl::get<Indices>(tuple))), nullptr;
}

template<typename Function, typename Tuple, size_t... Indices>
constexpr auto invoke(Function&& f, const Tuple& tuple, meta::index_sequence<Indices...>)
-> decltype(f(adl::get<Indices>(tuple)...)){
    return f(adl::get<Indices>(tuple)...);
}
} // detail

template<typename Tuple, typename Function>
constexpr decltype(nullptr) for_each(const Tuple& tuple, Function&& f) {
    return detail::for_each(tuple, std::forward<Function>(f), indices_for<Tuple>{});
}

template<typename Function, typename Tuple>
constexpr auto invoke(Function&& f, const Tuple& tuple)
-> decltype(detail::invoke(std::forward<Function>(f), tuple, indices_for<Tuple>{})) {
    return detail::invoke(std::forward<Function>(f), tuple, indices_for<Tuple>{});
}
} // tuple
} // gears

#endif // GEARS_TUPLE_ALGORITHM_HPP
