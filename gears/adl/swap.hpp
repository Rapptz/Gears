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

#ifndef GEARS_ADL_SWAP_HPP
#define GEARS_ADL_SWAP_HPP

namespace gears {
namespace adl {
namespace detail {
using std::swap;

template<typename T, typename U, typename R = decltype(swap(std::declval<T>(), std::declval<U>()))>
constexpr R adl_swap(T&& t, U&& u) noexcept(swap(std::declval<T>(), std::declval<U>())) {
    return swap(std::declval<T>(), std::declval<U>());
}
} // detail

/// 
/// \ingroup adl
/// \brief ADL-enabled swap.
/// 
/// Allows for ADL-enabled `swap`. Equivalent to doing the following:
/// 
/// \code
/// using std::swap;
/// swap(x, y);
/// \endcode
/// 
/// \param t First element to swap.
/// \param u Second element to swap.
/// \return automatically deduced return value of `swap(t, u)`.
/// 
template<typename T, typename U, typename R = decltype(detail::adl_swap(std::declval<T>(), std::declval<U>()))> 
constexpr R swap(T&& t, U&& u) noexcept(detail::adl_swap(std::declval<T>(), std::declval<U>())) {
    return detail::adl_swap(std::declval<T>(), std::declval<U>());
}
} // adl
} // gears

#endif // GEARS_ADL_SWAP_HPP