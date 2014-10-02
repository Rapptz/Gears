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

#ifndef GEARS_IO_DETAIL_INDEX_PRINTER_HPP
#define GEARS_IO_DETAIL_INDEX_PRINTER_HPP

#include <iosfwd>
#include <cstddef>
#include <stdexcept>
#include "../../meta/enable_if.hpp"
#include "../../adl/get.hpp"

namespace gears {
namespace io {
namespace detail {
template<size_t N = 0, class Elem, class Traits, typename... Args,
         meta::disable_if_t<meta::boolean<(N < sizeof...(Args))>> = meta::_>
inline void index_printer(std::basic_ostream<Elem,Traits>&, const size_t, const std::tuple<Args...>&) {
    throw std::out_of_range("Index exceeds number of arguments provided");
}

template<size_t N = 0, class Elem, class Traits, typename... Args, meta::enable_if_t<meta::boolean<(N < sizeof...(Args))>> = meta::_>
inline void index_printer(std::basic_ostream<Elem,Traits>& out, const size_t i, const std::tuple<Args...>& tup) {
    if(i != N) {
        index_printer<N + 1>(out, i, tup);
        return;
    }
    out << adl::get<N>(tup);
}
} // detail
} // io
} // gears

#endif // GEARS_IO_DETAIL_INDEX_PRINTER_HPP
