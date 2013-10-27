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

#ifndef GEARS_IO_PRETTYPRINT_HPP
#define GEARS_IO_PRETTYPRINT_HPP

#include "../meta/indices.hpp"
#include "../meta/alias.hpp"
#include "../utility/adl.hpp"
#include <iosfwd>

namespace gears {
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
} // detail

namespace operators {
template<typename Elem, typename Traits, typename Cont, EnableIf<detail::has_begin_end<Cont>>...>
inline auto operator<<(std::basic_ostream<Elem, Traits>& out, const Cont& cont) -> decltype(out) {
    auto first = begin(cont);
    auto last = end(cont);

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
} // gears

#endif // GEARS_IO_PRETTYPRINT_HPP