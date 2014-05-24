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

#ifndef GEARS_META_INDICES_HPP
#define GEARS_META_INDICES_HPP

#include <cstddef>

namespace gears {
namespace meta {
/**
 * @ingroup meta
 * @brief Represents an index sequence.
 * @details Represents an index sequence. Used for
 * iterating over template parameters.
 *
 * @tparam Ns The indices.
 */
template<size_t... Ns>
struct indices {};

/**
 * @ingroup meta
 * @brief Creates an index sequence.
 * @details Creates an index sequence. `build_indices<N>` would
 * create `indices<0, 1, 2, ..., N - 1>`.
 *
 * Example:
 *
 * @code
 * #include <gears/meta/indices.hpp>
 * #include <gears/adl/get.hpp>
 * #include <tuple>
 * #include <iostream>
 *
 * using namespace gears::meta;
 * namespace adl = gears::adl;
 *
 * // turns f(std::tuple<Args...>) to f(Args...)
 * template<typename Function, typename... Args, size_t... Indices>
 * auto apply(Function f, const std::tuple<Args...>& t, indices<Indices...>) -> decltype(f(adl::get<Indices>(t)...)) {
 *     return f(adl::get<Indices>(t)...);
 * }
 *
 * template<typename Function, typename... Args>
 * auto apply(Function f, const std::tuple<Args...>& t) -> decltype(apply(f, t, build_indices<sizeof...(Args)>{})) {
 *     return apply(f, t, build_indices<sizeof...(Args)>{});
 * }
 *
 * int f(int x, int y, int z) {
 *     return x + y + z;
 * }
 *
 * int main() {
 *     auto args = std::make_tuple(10, 11, 12);
 *     std::cout << apply(f, args);
 * }
 * @endcode
 *
 * Output:
 * <pre>
 * 33
 * </pre>
 *
 * @tparam N Length of the index.
 */
template<size_t N, size_t... Ns>
struct build_indices : build_indices<N-1, N-1, Ns...> {};

template<size_t... Ns>
struct build_indices<0, Ns...> : indices<Ns...> {};
} // meta
} // gears

#endif // GEARS_META_INDICES_HPP
