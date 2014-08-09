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

#ifndef GEARS_META_CONST_STRING_HPP
#define GEARS_META_CONST_STRING_HPP

#include "../core.hpp"
#include "../indices.hpp"
#include <string>
#include <stdexcept>

namespace gears {
namespace meta {
/**
 * @ingroup constexpr
 * @brief `constexpr`-enabled string class.
 * @details This class provides a `constexpr` enabled interface for
 * `std::basic_string`. Note, however, that it doesn't mimic the entire
 * interface, just the parts that make sense. The only part of the interface
 * that is provided are the immutable parts. The reason for this is to keep
 * compatibility with C++11, where `constexpr` functions that modify variables
 * are not allowed. The string must have a null terminator at position `N`.
 * A character trait class could be provided to customise the comparisons
 * that the class implements. The only requirements for the interface is that
 * it provides the following `constexpr`, `noexcept`, `static` member functions:
 *
 * @code
 * static constexpr bool eq(char_type);
 * static constexpr bool lt(char_type);
 * static constexpr int_type to_int_type(char_type);
 * static constexpr char_type to_char_type(int_type);
 * @endcode
 *
 * Some member functions can be exposed through the use of a macro denoting
 * C++14 support is available. This macro is `GEARS_META_HAS_CPP14`. Currently,
 * it is set to `1` if compiling on Clang 3.4 or higher.
 *
 * @tparam CharT The internal character type to store.
 * @tparam N The size of the string literal with the null terminator included.
 * @tparam Traits The character traits class to do comparison with.
 */
template<typename CharT, size_t N, typename Traits = std::char_traits<CharT>>
struct basic_string {
private:
    CharT str[N];

    template<size_t... Indices>
    constexpr basic_string(const CharT (&arr)[N], indices<Indices...>): str{ arr[Indices]... } {}

    constexpr size_t find_character(CharT c, size_t pos = 0, size_t i = 0) const noexcept {
        return i + pos >= size() ?
               npos : Traits::eq(str[i + pos], c) ?
                      i + pos : find_character(c, pos, i + 1);
    }

    constexpr size_t rfind_character(CharT c, size_t i) const noexcept {
        return i == 0 ?
               npos : Traits::eq(str[i], c) ?
                      i : rfind_character(c, i - 1);
    }

    template<size_t M>
    constexpr bool cmp(const basic_string<CharT, M, Traits>& s, size_t pos, size_t i = 0) const noexcept {
        return i >= s.size() ?
               true : Traits::eq(str[pos + i], s[i]) ?
                      cmp(s, pos, i + 1) : false;
    }

    constexpr size_t min(size_t x, size_t y) const noexcept {
        return y < x ? y : x;
    }

    template<size_t M>
    constexpr size_t find_substr(const basic_string<CharT, M, Traits>& s, size_t pos) const noexcept {
        return pos > size() - s.size() ?
               npos : Traits::eq(str[pos], s[0]) && cmp(s, pos) ?
                      pos : find_substr(s, pos + 1);
    }

    template<size_t M>
    constexpr size_t rfind_substr(const basic_string<CharT, M, Traits>& s, size_t pos) const noexcept {
        return pos == 0 ?
               npos : cmp(s, pos) ?
                      pos : rfind_substr(s, pos - 1);
    }
public:
    using traits_type     = Traits;
    using value_type      = typename Traits::char_type;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using pointer         = value_type*;
    using const_pointer   = const value_type*;
    using iterator        = pointer;
    using const_iterator  = const_pointer;
    static constexpr size_type npos = static_cast<size_type>(-1); ///< Represents a position not found


    /**
     * @brief Constructs a basic_string from a character array.
     * @details Constructs a basic_string from a character array.
     * The character array must have a null terminator as its last
     * character.
     *
     * @param arr The character array to construct with.
     */
    constexpr basic_string(const CharT (&arr)[N]): basic_string(arr, build_indices<N>{}) {}

    //@{
    /**
     * @brief Returns the size of the string without the null terminator.
     */
    constexpr size_type size() const noexcept {
        return N - 1;
    }

    constexpr size_type length() const noexcept {
        return N - 1;
    }
    //}

    /**
     * @brief Checks if the string is empty.
     * @details Checks if the string is empty. A string
     * is considered empty if the only character it has is the
     * null terminator.
     * @return `true` if empty, `false` otherwise.
     */
    constexpr bool empty() const noexcept {
        return size() == 0;
    }

    /**
     * @brief Returns the capacity of the string. i.e. `N`.
     */
    constexpr size_type capacity() const noexcept {
        return N;
    }

    /**
     * @brief Returns the max size of the string. i.e. `N`.
     */
    constexpr size_type max_size() const noexcept {
        return N;
    }

    /**
     * @brief Access a specified character.
     * @details Returns a reference to a character without
     * bounds checking at the specified position. Note that
     * accessing an out of bounds character is undefined behaviour.
     * Use #at instead to get a compile time error when out of bounds.
     * In C++14, undefined behaviour in a constant expression results
     * in a compilation error.
     *
     * @param index The specified position to get the character at.
     * @return A reference to the character.
     */
    constexpr const_reference operator[](size_type index) const noexcept {
        return str[index];
    }

    /**
     * @brief Access a specified character with bounds checking.
     * @details Returns a reference to a character with bounds
     * checking at a specified position. Bounds checking is done
     * by throwing an exception of type `std::out_of_range`. When
     * used in a constant expression, this turns into a compile-time
     * error.
     *
     * @throws std::out_of_range Thrown when the position is out of bounds.
     * @param index The specified position to get the character at.
     * @return A reference to the character.
     */
    constexpr const_reference at(size_type index) const {
        return index < size() ? str[index] : (throw std::out_of_range("access is out of bounds"), str[index]);
    }

    /**
     * @brief Accesses the first character.
     * @details Accesses the first character. On an
     * empty string this would return the null character.
     * @return A reference to the first character.
     */
    constexpr const_reference front() const noexcept {
        return str[0];
    }

    /**
     * @brief Accesses the last character.
     * @details Accesses the last character. On an
     * empty string this would result in undefined behaviour.
     * In C++14 undefined behaviour in a constant expression
     * ends in a compilation error.
     * @return A reference to the last character.
     */
    constexpr const_reference back() const noexcept {
        return str[size() - 1];
    }

#ifdef GEARS_META_HAS_CPP14
    /**
     * @name C++14 Only
     * These are member functions that are only provided
     * if the compiler has support for C++14. At the moment,
     * the only compiler with support for these is Clang
     * 3.4 or higher.
     */
    //@{
    /**
     * @brief Returns a pointer to the first character of the string.
     */
    constexpr const_pointer data() const noexcept {
        return static_cast<const_pointer>(str);
    }

    /**
     * @brief Returns a pointer to the first character of the string.
     */
    constexpr const_pointer c_str() const noexcept {
        return static_cast<const_pointer>(str);
    }

    /**
     * @brief Returns an iterator pointing to the first element.
     */
    constexpr const_iterator begin() const noexcept {
        return str;
    }

    /**
     * @brief Returns an iterator pointing to the first element.
     */
    constexpr const_iterator cbegin() const noexcept {
        return str;
    }

    /**
     * @brief Returns an iterator pointing to the one past the last element.
     */
    constexpr const_iterator end() const noexcept {
        return str + size();
    }

    /**
     * @brief Returns an iterator pointing to the one past the last element.
     */
    constexpr const_iterator cend() const noexcept {
        return str + size();
    }
    //@}
#endif // C++14

    /**
     * @brief Finds a character in the string.
     * @details Finds a character in the string. This
     * function finds the first occurrence of the character.
     * If the character is not found, #npos is returned.
     *
     * @param c The character to look for.
     * @param pos The position to start the search at.
     * @return The position of the character found.
     */
    constexpr size_type find(CharT c, size_type pos = 0) const noexcept {
        return find_character(c, pos);
    }

    /**
     * @brief Finds a substring in a string.
     * @details Finds a substring in the string. This function
     * finds the first occurrence of the substring. If the substring
     * is not found, #npos is returned.
     *
     * @param s The substring to look for.
     * @param pos The position to start the search at.
     * @return The position of the substring.
     */
    template<size_t M>
    constexpr size_type find(const basic_string<CharT, M, Traits>& s, size_type pos = 0) const noexcept {
        return s.empty() && pos <= size() ?
               pos : find_substr(s, pos);
    }

    /**
     * @brief Finds the last character in the string.
     * @details Finds the last character in the string. This
     * function finds the last occurrence of the character.
     * If the character is not found, #npos is returned.
     *
     * @param c The character to look for.
     * @param pos The position to start the search at.
     * @return The position of the character found.
     */
    constexpr size_type rfind(CharT c, size_type pos = npos) const noexcept {
        return !empty() && size() - 1 > pos ?
               rfind_character(c, pos + 1) : rfind_character(c, size());
    }

    /**
     * @brief Finds the last substring in a string.
     * @details Finds the last substring in the string. This function
     * finds the last occurrence of the substring. If the substring
     * is not found, #npos is returned.
     *
     * @param s The substring to look for.
     * @param pos The position to start the search at.
     * @return The position of the substring.
     */
    template<size_t M>
    constexpr size_type rfind(const basic_string<CharT, M, Traits>& s, size_type pos = npos) const noexcept {
        return s.size() > size() ?
               npos : cmp(s, min(size() - s.size(), pos)) ?
                      min(size() - s.size(), pos) : rfind_substr(s, min(size() - s.size(), pos));
    }
};

/**
 * @relates basic_string
 * @brief Factory function to make a constexpr enabled string.
 * @details A factory function to create a `constexpr` enabled
 * string. This is meant to be used with string literals and
 * is the preferred way to create the string instances.
 *
 * @param arr The string literal to construct the string with.
 * @return A `basic_string` instance containing the literal.
 */
template<typename CharT, size_t N>
constexpr basic_string<CharT, N> make_string(const CharT (&arr)[N]) {
    return { arr };
}
} // meta
} // gears

#endif // GEARS_META_CONST_STRING_HPP
