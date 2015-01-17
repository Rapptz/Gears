// The MIT License (MIT)

// Copyright (c) 2012-2015 Danny Y., Rapptz

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

#ifndef GEARS_IO_DETAIL_TUPLE_HPP
#define GEARS_IO_DETAIL_TUPLE_HPP

#include <gears/meta/indices.hpp>
#include <gears/meta/enable_if.hpp>
#include <tuple>
#include <stdexcept>

namespace gears {
namespace io {
namespace detail {
template<typename Stream>
struct printer {
private:
    Stream& out;
public:
    printer(Stream& out): out(out) {}

    template<typename T>
    void operator()(T&& t) const {
        out << std::forward<T>(t);
    }
};

template<typename T>
struct extractor {
private:
    T& val;
public:
    extractor(T& val): val(val) {}

    template<typename U, meta::enable_if_t<std::is_constructible<T, U>> = meta::_>
    void operator()(U&& t) const noexcept {
        val = std::forward<U>(t);
    }

    template<typename U, meta::disable_if_t<std::is_constructible<T, U>> = meta::_>
    void operator()(U&&) const noexcept {}
};

template<typename T>
inline extractor<T> make_extractor(T& t) {
    return { t };
}

template<typename T>
inline printer<T> make_printer(T& t) {
    return { t };
}

template<typename Tuple, typename Function>
inline void apply_impl(const Tuple&, size_t, const Function&, meta::index_sequence<>) {
    throw std::out_of_range("tuple index is out of bounds");
}

template<size_t N, size_t... Tail, typename Tuple, typename Function>
inline void apply_impl(const Tuple& tuple, size_t index, const Function& f, meta::index_sequence<N, Tail...>) {
    if(index == N) {
        f(std::get<N>(tuple));
    }
    else {
        apply_impl(tuple, index, f, meta::index_sequence<Tail...>{});
    }
}

template<typename Tuple, typename Function>
inline void apply(const Tuple& tuple, size_t index, const Function& f) {
    apply_impl(tuple, index, f, meta::make_index_sequence<std::tuple_size<Tuple>::value>{});
}
} // detail
} // io
} // gears

#endif // GEARS_IO_DETAIL_TUPLE_HPP
