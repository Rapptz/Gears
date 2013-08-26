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

#ifndef GEARS_FORMAT_DETAIL_INDEX_PRINTER_HPP
#define GEARS_FORMAT_DETAIL_INDEX_PRINTER_HPP

#include <tuple>
#include <iosfwd>
#include <cstddef>
#include <stdexcept>
#include "../../meta/alias.hpp"

namespace gears {
namespace format_detail {
template<size_t N = 0, class Elem, class Traits, typename... Args, EnableIf<Bool<(N >= sizeof...(Args))>>...>
inline void index_printer(std::basic_ostream<Elem,Traits>& out, const size_t i, const std::tuple<Args...>& tup) {
    throw std::out_of_range("Index exceeds number of arguments provided");
}

template<size_t N = 0, class Elem, class Traits, typename... Args, EnableIf<Bool<(N < sizeof...(Args))>>...>
inline void index_printer(std::basic_ostream<Elem,Traits>& out, const size_t i, const std::tuple<Args...>& tup) {
    if(i != N) {
        index_printer<N+1, Elem, Traits, Args...>(out, i, tup);
        return;
    }
    using std::get;
    out << get<N>(tup);
}
} // format_detail
} // gears

#endif // GEARS_FORMAT_DETAIL_INDEX_PRINTER_HPP