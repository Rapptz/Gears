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

#ifndef GEARS_UTILITY_TRIPLE_HPP
#define GEARS_UTILITY_TRIPLE_HPP

#include <gears/meta/qualifiers.hpp>
#include <cstddef>

namespace gears {

/**
 * @ingroup utility
 * @brief Implements a three-element tuple.
 * @details Implements a three-element tuple. This class has
 * `std::get`, `std::tuple_element`, and `std::tuple_size` defined for
 * generic usage. For example:
 *
 * @code
 * constexpr triple<int, int, int> x = { 1, 2, 3 };
 * static_assert(std::is_same<std::tuple_element<0, decltype(x)>::value, "...");
 * static_assert(std::get<0>(x) == 1, "...");
 * static_assert(std::tuple_size<decltype(x)>::value == 3, "...");
 * @endcode
 *
 * `triple` is also an aggregate, so it could be created using curly bracket syntax.
 *
 * @code
 * constexpr triple<int, char, double> x = { 10, 'a', 12.0 };
 * @endcode
 *
 * @tparam T First type of the triple.
 * @tparam U Second type of the triple.
 * @tparam V Third type of the triple.
 */
template<typename T, typename U, typename V>
struct triple {
    using first_type  = T;
    using second_type = U;
    using third_type  = V;

    T first;
    U second;
    V third;

    /**
     * @brief Swaps the three elements of the triple.
     * @details Swaps the three elements of the triple.
     *
     * @param t Other triple to swap with
     */
    void swap(triple& t) noexcept(noexcept(std::swap(first, t.first))   &&
                                  noexcept(std::swap(second, t.second)) &&
                                  noexcept(std::swap(third, t.third))) {
        using std::swap;
        swap(first, t.first);
        swap(second, t.second);
        swap(third, t.third);
    }
};

/**
 * @relates triple
 * @brief Checks if two triple objects are equivalent.
 * @details Checks if two triple objects are equivalent.
 * In order for it to reach equivalence all members must be
 * equal to each other.
 *
 * @param lhs Left hand side of the expression.
 * @param rhs Right hand side of the expression.
 * @return `true` if both are equal, `false` otherwise.
 */
template<typename T, typename U, typename V>
constexpr bool operator==(const triple<T, U, V>& lhs, const triple<T, U, V>& rhs) {
    return lhs.first == rhs.first && lhs.second == rhs.second && lhs.third == rhs.third;
}

/**
 * @relates triple
 * @brief Checks if two triple objects are lexicographically less than each other.
 * @details Checks if two triple objects are lexicographically less than each other.
 *
 * @param lhs Left hand side of the expression.
 * @param rhs Right hand side of the expression.
 * @return `true` if `lhs` is lexicographically less than `rhs`, `false` otherwise.
 */
template<typename T, typename U, typename V>
constexpr bool operator<(const triple<T, U, V>& lhs, const triple<T, U, V>& rhs) {
    return   lhs.first < rhs.first  ? true  :
             rhs.first < lhs.first  ? false :
            lhs.second < rhs.second ? true  :
            rhs.second < lhs.second ? false :
             lhs.third < rhs.third;
}

/**
 * @relates triple
 * @brief Checks if two triple objects are not equivalent.
 * @details Checks if two triple objects are not equivalent.
 * This is the negation of `operator==`.
 *
 * @param lhs Left hand side of the expression.
 * @param rhs Right hand side of the expression.
 * @return `true` if they're not equal, `false` otherwise.
 */
template<typename T, typename U, typename V>
constexpr bool operator!=(const triple<T, U, V>& lhs, const triple<T, U, V>& rhs) {
    return !(lhs == rhs);
}

/**
 * @relates triple
 * @brief Checks if two triple objects are lexicographically greater than each other.
 * @details Checks if two triple objects are lexicographically greater than each other.
 *
 * @param lhs Left hand side of the expression.
 * @param rhs Right hand side of the expression.
 * @return `true` if `lhs` is lexicographically greater than `rhs`, `false` otherwise.
 */
template<typename T, typename U, typename V>
constexpr bool operator>(const triple<T, U, V>& lhs, const triple<T, U, V>& rhs) {
    return (rhs < lhs);
}

/**
 * @relates triple
 * @brief Compares both triple objects to see if they're greater than or equal to each other.
 * @details Checks if two triple objects are lexicographically greater than
 * or equal to each other.
 *
 * @param lhs Left hand side of the expression.
 * @param rhs Right hand side of the expression.
 * @return `true` if `lhs` is lexicographically greater than or equal to `rhs`, `false` otherwise.
 */
template<typename T, typename U, typename V>
constexpr bool operator>=(const triple<T, U, V>& lhs, const triple<T, U, V>& rhs) {
    return !(lhs < rhs);
}

/**
 * @relates triple
 * @brief Compares both triple objects to see if they're less than or equal to each other.
 * @details Checks if two triple objects are lexicographically less than
 * or equal to each other.
 *
 * @param lhs Left hand side of the expression.
 * @param rhs Right hand side of the expression.
 * @return `true` if `lhs` is lexicographically less than or equal to `rhs`, `false` otherwise.
 */
template<typename T, typename U, typename V>
constexpr bool operator<=(const triple<T, U, V>& lhs, const triple<T, U, V>& rhs) {
    return !(rhs < lhs);
}

/**
 * @relates triple
 * @brief Swaps the elements of the triple objects.
 * @details Swaps the elements of the triple objects.
 *
 * @param lhs Left hand side to swap with.
 * @param rhs Right hand side to swap with.
 */
template<typename T, typename U, typename V>
inline void swap(triple<T, U, V>& lhs, triple<T, U, V>& rhs) noexcept(noexcept(lhs.swap(rhs))) {
    lhs.swap(rhs);
}

/**
 * @relates triple
 * @brief Creates a triple object.
 * @details Creates a triple object. The template parameters
 * are passed through `std::decay` for storage purposes. THis function
 * is useful for `auto` purposes, e.g.
 *
 * @code
 * auto t = make_triple(10, 'a', 1.f);
 * // decltype(t) == triple<int, char, float>
 * @endcode
 *
 * @param t First element of the triple.
 * @param u Second element of the triple.
 * @param v Third element of the triple.
 * @return A triple containing the three elements provided.
 */
template<typename T, typename U, typename V>
constexpr triple<meta::decay_t<T>, meta::decay_t<U>, meta::decay_t<V>> make_triple(T&& t, U&& u, V&& v) {
    return { std::forward<T>(t), std::forward<U>(u), std::forward<V>(v) };
}

} // gears

namespace triple_detail {
template<size_t N> struct triple_get;

template<>
struct triple_get<0> {
    template<typename T, typename U, typename V>
    static constexpr T& get(gears::triple<T, U, V>& t) noexcept {
        return t.first;
    }

    template<typename T, typename U, typename V>
    static constexpr const T& const_get(const gears::triple<T, U, V>& t) noexcept {
        return t.first;
    }

    template<typename T, typename U, typename V>
    static constexpr T&& move_get(gears::triple<T, U, V>&& t) noexcept {
        return std::forward<T>(t.first);
    }
};

template<>
struct triple_get<1> {
    template<typename T, typename U, typename V>
    static constexpr U& get(gears::triple<T, U, V>& t) noexcept {
        return t.second;
    }

    template<typename T, typename U, typename V>
    static constexpr const U& const_get(const gears::triple<T, U, V>& t) noexcept {
        return t.second;
    }

    template<typename T, typename U, typename V>
    static constexpr U&& move_get(gears::triple<T, U, V>&& t) noexcept {
        return std::forward<U>(t.second);
    }
};

template<>
struct triple_get<2> {
    template<typename T, typename U, typename V>
    static constexpr V& get(gears::triple<T, U, V>& t) noexcept {
        return t.third;
    }

    template<typename T, typename U, typename V>
    static constexpr const V& const_get(const gears::triple<T, U, V>& t) noexcept {
        return t.third;
    }

    template<typename T, typename U, typename V>
    static constexpr V&& move_get(gears::triple<T, U, V>&& t) noexcept {
        return std::forward<V>(t.third);
    }
};
} // triple_detail

namespace std {
template<typename T> struct tuple_size;
template<size_t N, typename T> struct tuple_element;

template<typename T, typename U, typename V>
struct tuple_size<gears::triple<T, U, V>> : gears::meta::constant<size_t, 3> {};

template<typename T, typename U, typename V>
struct tuple_element<0, gears::triple<T, U, V>> {
    using type = T;
};

template<typename T, typename U, typename V>
struct tuple_element<1, gears::triple<T, U, V>> {
    using type = U;
};

template<typename T, typename U, typename V>
struct tuple_element<2, gears::triple<T, U, V>> {
    using type = V;
};
} // std

namespace gears {

template<size_t N, typename T, typename U, typename V>
constexpr gears::meta::eval<std::tuple_element<N, triple<T, U, V>>>& get(triple<T, U, V>& t) noexcept {
    return triple_detail::triple_get<N>::get(t);
}

template<size_t N, typename T, typename U, typename V>
constexpr const gears::meta::eval<std::tuple_element<N, triple<T, U, V>>>& get(const triple<T, U, V>& t) noexcept {
    return triple_detail::triple_get<N>::const_get(t);
}

template<size_t N, typename T, typename U, typename V>
constexpr gears::meta::eval<std::tuple_element<N, triple<T, U, V>>>&& get(triple<T, U, V>&& t) noexcept {
    return triple_detail::triple_get<N>::move_get(std::move(t));
}
} // gears

#endif // GEARS_UTILITY_TRIPLE_HPP
