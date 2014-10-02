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

#ifndef GEARS_IO_PRETTYPRINT_HPP
#define GEARS_IO_PRETTYPRINT_HPP

#include "../meta/indices.hpp"
#include "../meta/enable_if.hpp"
#include "../meta/expand.hpp"
#include "../adl/get.hpp"
#include "../adl/iterator.hpp"
#include <iosfwd>

namespace gears {
namespace io {
namespace detail {
struct has_begin_end_impl {
    template<typename T, typename B = decltype(std::declval<T&>().begin()),
                         typename E = decltype(std::declval<T&>().end())>
    static std::true_type test(int);
    template<typename...>
    static std::false_type test(...);
};

template<typename T>
struct has_begin_end : decltype(has_begin_end_impl::test<T>(0)) {};

struct has_get_impl {
    template<typename T>
    static auto test(int) -> decltype(adl::get<0>(std::declval<T>()), std::true_type{}) {}
    template<typename...>
    static std::false_type test(...);
};

template<typename T>
struct has_get : decltype(has_get_impl::test<T>(0)) {};

template<typename Elem, typename Traits, typename Tuple, size_t... Indices>
void print_expander(std::basic_ostream<Elem, Traits>& out, const Tuple& t, meta::indices<Indices...>) noexcept {
    GEARS_EXPAND(out << (!Indices ? "" : ", ") << adl::get<Indices>(t));
}
} // detail

namespace operators {
template<typename Elem, typename Traits, typename Tuple,
         meta::enable_if_t<detail::has_get<Tuple>, meta::negate<detail::has_begin_end<Tuple>>> = meta::_>
inline auto operator<<(std::basic_ostream<Elem, Traits>& out, const Tuple& t) -> decltype(out) {
    out << "(";
    detail::print_expander(out, t, meta::build_indices<std::tuple_size<Tuple>::value>{});
    out << ")";
    return out;
}

template<typename Elem, typename Traits, typename Cont, meta::enable_if_t<detail::has_begin_end<Cont>> = meta::_>
inline auto operator<<(std::basic_ostream<Elem, Traits>& out, const Cont& cont) -> decltype(out) {
    auto first = adl::begin(cont);
    auto last = adl::end(cont);

    if(first == last) {
        out << "[]";
        return out;
    }
    else {
        out << '[' << *first++;
    }
    while(first != last) {
        out << ", " << *first++;
    }

    out << ']';
    return out;
}
} // operators
} // io
} // gears

#endif // GEARS_IO_PRETTYPRINT_HPP
