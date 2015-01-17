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

#ifndef GEARS_META_INDICES_HPP
#define GEARS_META_INDICES_HPP

#include <cstddef>

namespace gears {
namespace meta {
/**
 * @ingroup meta
 * @brief Represents a compile-time integer sequence.
 * @details Typically used for iterating over template
 * parameters, tuples, tuple-like objects, etc.
 *
 * A template alias, `index_sequence` is provided for
 * `size_t` integer_sequences.
 *
 * @tparam T The integral type to use.
 * @tparam Integers The sequence.
 */
template<typename T, T... Integers>
struct integer_sequence {
    using value_type = T;

    /**
     * @brief Returns the size of the sequence.
     */
    static constexpr size_t size() noexcept {
        return sizeof...(Integers);
    }
};

namespace detail {
template<size_t... I>
struct indices {
    using type = indices;
};

template<typename Left, typename Right>
struct concat;

template<size_t... I, size_t... J>
struct concat<indices<I...>, indices<J...>> : indices<I..., (J + sizeof...(I))...> {};

template<size_t N>
struct build_indices : concat<typename build_indices<N / 2>::type, typename build_indices<N - N / 2>::type> {};

template<>
struct build_indices<0> : indices<> {};

template<>
struct build_indices<1> : indices<0> {};

template<typename T, T N, typename X = typename build_indices<N>::type>
struct generator;

template<typename T, T N, size_t... Indices>
struct generator<T, N, indices<Indices...>> {
    static_assert(N >= 0, "integer sequence must be positive");
    using type = integer_sequence<T, static_cast<T>(Indices)...>;
};
} // detail

//@{
/**
 * @ingroup meta
 * @brief Creates an integer sequence.
 * @details Creates an integer sequence.
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
 * auto apply(Function f, const std::tuple<Args...>& t, index_sequence<Indices...>) -> decltype(f(adl::get<Indices>(t)...)) {
 *     return f(adl::get<Indices>(t)...);
 * }
 *
 * template<typename Function, typename... Args>
 * auto apply(Function f, const std::tuple<Args...>& t) -> decltype(apply(f, t, index_sequence_for<Args...>{})) {
 *     return apply(f, t, index_sequence_for<Args...>{});
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
template<typename T, T Max>
using make_integer_sequence = typename detail::generator<T, Max>::type;

template<size_t Max>
using make_index_sequence = typename detail::generator<size_t, Max>::type;

template<typename... Args>
using index_sequence_for = make_index_sequence<sizeof...(Args)>;
//@}

template<size_t... Indices>
using index_sequence = integer_sequence<size_t, Indices...>;
} // meta
} // gears

#endif // GEARS_META_INDICES_HPP
