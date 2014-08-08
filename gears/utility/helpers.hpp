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

#ifndef GEARS_UTILITY_HELPERS_HPP
#define GEARS_UTILITY_HELPERS_HPP

#include "../meta/indices.hpp"
#include <array>
#include <utility>
#include <memory>
#include <type_traits>

namespace gears {
namespace detail {
template<typename T>
struct unique_type {
    using single = std::unique_ptr<T>;
};

template<typename T>
struct unique_type<T[]> {
    using array = std::unique_ptr<T[]>;
};

template<typename T, size_t N>
struct unique_type<T[N]> {
    using unknown = void;
};

template<typename CharT, size_t N, size_t... Indices>
constexpr std::array<CharT, N> literal_to_array(const CharT (&arr)[N], meta::indices<Indices...>) {
    return std::array<CharT, N>{{ arr[Indices]... }};
}
} // detail

/**
 * @ingroup utility
 * @brief Constructs an std::array instance.
 * @details Constructs an `std::array` instance from the
 * arguments provided of type T. This allows for quick generation
 * of `std::array` instances similar to raw C arrays.
 *
 * @code
 * auto arr = make_array<int>(1, 2, 3, 4, 5, 6, 7, 8);
 * // same as
 * // int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
 * @endcode
 *
 * @param args Arguments to store into the array.
 * @tparam T The type of the array.
 * @return An `std::array` containing the elements provided.
 */
template<typename T, typename... Args>
constexpr std::array<T, sizeof...(Args)> make_array(Args&&... args) {
    return std::array<T, sizeof...(Args)>{{ std::forward<Args>(args)... }};
}

/**
 * @ingroup utility
 * @brief Constructs an std::array instance from a string literal.
 * @details Constructs an std::array instance from a string literal.
 * This works similar to the other make_array function but with
 * strings instead. C arrays have a special case for string literals
 * to allow you to automatically get the size through `sizeof`. This
 * just emulates the special behaviour:
 *
 * @code
 * auto str = make_array("hello");
 * // same as
 * // char str[] = "hello";
 * @endcode
 *
 * Note that this means the null character is the last character.
 *
 * @param str The string literal to construct the array with.
 * @return An `std::array` containing the characters of the string.
 */
template<typename CharT, size_t N>
constexpr std::array<CharT, N> make_array(const CharT (&str)[N]) {
    return detail::literal_to_array(str, meta::build_indices<N>{});
}

/**
 * @ingroup utility
 * @brief Constructs an std::unique_ptr instance.
 * @details Constructs an `std::unique_ptr` instance from
 * the arguments provided. This is the same function as `std::make_unique`
 * which was added in C++14. Constructing a type with known bounds is forbidden.
 *
 *
 * @param args Arguments to pass to the constructor of the type.
 * @param size The size of the array to construct.
 * @tparam T Type to construct.
 * @return An `std::unique_ptr` containing the resource made.
 */
template<typename T, typename... Args>
inline typename detail::unique_type<T>::single make_unique(Args&&... args) {
    return std::unique_ptr<T>{new T(std::forward<Args>(args)...)};
}

/**
 * @ingroup utility
 * @copydoc gears::make_unique
 *
 * @param size The size of the array to construct.
 * @tparam T Type to construct.
 * @return An `std::unique_ptr` containing an array.
 */
template<typename T>
inline typename detail::unique_type<T>::array make_unique(size_t size) {
    using U = typename std::remove_extent<T>::type;
    return std::unique_ptr<T>{new U[size]()};
}

template<typename T, typename... Args>
inline typename detail::unique_type<T>::unknown make_unique(Args&&...) = delete;
} // gears

#endif // GEARS_UTILITY_HELPERS_HPP

