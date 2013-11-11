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

#ifndef GEARS_ADL_GET_HPP
#define GEARS_ADL_GET_HPP

#include <tuple>
#include <utility>
#include <cstddef>

namespace gears {
namespace adl {
namespace detail {
using std::get;

template<size_t N, typename T>
constexpr auto adl_get(T&& t) -> decltype(get<N>(std::declval<T>())) {
    return get<N>(std::forward<T>(t));
}
} // detail

///
/// \brief ADL enabled get function for tuple-like interfaces
/// 
/// Allows for argument dependent lookup of `std::get`-like interfaces
/// 
/// \tparam N Index to get
/// \param t Tuple-like class to receive index from
/// \return automatically deduced return value of `get<N>(t)`
/// 
template<size_t N, typename T>
constexpr auto get(T&& t) -> decltype(detail::adl_get<N>(std::declval<T>())) {
    return detail::adl_get<N>(std::forward<T>(t));
}
} // adl
} // gears

/// \file get.hpp
/// \ingroup adl
/// 
/// \brief ADL-enabled get
/// 
/// This function is very simple, allowing for an ADL-enabled `get` call.
/// This is useful because it allows you to write generic code that relies on `std::get`
/// without actually having to specify `using std::get` in every line.
/// 
/// Example usage:
/// \code
/// #include <gears/adl/get.hpp>
/// #include <tuple>
/// #include <iostream>
/// 
/// namespace adl = gears::adl;
/// 
/// namespace my {
/// struct get_example {
///     int x;
///     int y;
/// };
/// 
/// template<size_t N>
/// constexpr int get(const get_example& g) {
///     return N == 0 ? g.x : g.y;
/// }
/// } // my
/// 
/// int main() {
///     auto tup = std::make_tuple("hello", 3.14);
///     my::get_example f = {10, 11};
///     
///     std::cout << adl::get<0>(tup) << ' ' << adl::get<0>(f);
/// 
/// }
/// 
/// \endcode
/// 
/// Output:
/// <pre>
/// hello 10
/// </pre>
/// 

#endif // GEARS_ADL_GET_HPP