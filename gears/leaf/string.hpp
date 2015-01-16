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

#ifndef GEARS_LEAF_STRING_HPP
#define GEARS_LEAF_STRING_HPP

#include <gears/meta/core.hpp>
#include <gears/meta/indices.hpp>
#include <string>
#include <stdexcept>

namespace gears {
namespace leaf {
template<typename CharT, size_t N, typename Traits = std::char_traits<CharT>>
struct basic_string {
private:
    CharT str[N];

    template<size_t... Indices>
    constexpr basic_string(const CharT (&arr)[N], meta::index_sequence<Indices...>): str{ arr[Indices]... } {}

    constexpr size_t rfind_character(CharT c, size_t i) const noexcept {
        return i == 0 && !Traits::eq(str[i], c) ?
               npos : Traits::eq(str[i], c) ?
                      i : rfind_character(c, i - 1);
    }

    template<size_t M>
    constexpr bool equal_substr(const basic_string<CharT, M, Traits>& s, size_t pos, size_t i = 0) const noexcept {
        return i >= s.size() ?
               true : Traits::eq(str[pos + i], s[i]) ?
                      equal_substr(s, pos, i + 1) : false;
    }

    constexpr size_t min(size_t x, size_t y) const noexcept {
        return y < x ? y : x;
    }

    template<size_t M>
    constexpr size_t find_substr(const basic_string<CharT, M, Traits>& s, size_t pos) const noexcept {
        return pos > size() - s.size() ?
               npos : Traits::eq(str[pos], s[0]) && equal_substr(s, pos) ?
                      pos : find_substr(s, pos + 1);
    }

    template<size_t M>
    constexpr size_t rfind_substr(const basic_string<CharT, M, Traits>& s, size_t pos) const noexcept {
        return pos == 0 ?
               npos : equal_substr(s, pos) ?
                      pos : rfind_substr(s, pos - 1);
    }

    template<size_t M>
    constexpr size_t find_last_tail(const basic_string<CharT, M, Traits>& s, size_t pos) const noexcept {
        return pos == 0 ?
               npos : s.find(str[pos]) != npos ?
                      pos : find_last_tail(s, pos - 1);
    }

    constexpr size_t find_last_not_character(CharT c, size_t pos) const noexcept {
        return pos == 0 ?
               npos : !Traits::eq(str[pos], c) ?
                      pos : find_last_not_character(c, pos - 1);
    }

    template<size_t M>
    constexpr size_t find_last_not_tail(const basic_string<CharT, M, Traits>& s, size_t pos) const noexcept {
        return pos == 0 ?
               npos : s.find(str[pos]) == npos ?
                      pos : find_last_not_tail(s, pos - 1);
    }

    template<size_t M>
    constexpr int compare_impl(const basic_string<CharT, M, Traits>& s, size_t pos) const noexcept {
        return pos == size() && pos == s.size() ?
               0 : pos == size() ?
                   -1 : pos == s.size() ?
                        +1 : Traits::eq(str[pos], s[pos]) ?
                             compare_impl(s, pos + 1) : Traits::lt(str[pos], s[pos]) ?
                                                        -1 : +1;
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
    static constexpr size_type npos = static_cast<size_type>(-1);

    constexpr basic_string(const CharT (&arr)[N]): basic_string(arr, meta::make_index_sequence<N>{}) {}

    constexpr size_type size() const noexcept {
        return N - 1;
    }

    constexpr size_type length() const noexcept {
        return N - 1;
    }

    constexpr bool empty() const noexcept {
        return size() == 0;
    }

    constexpr size_type capacity() const noexcept {
        return N;
    }

    constexpr size_type max_size() const noexcept {
        return N;
    }

    constexpr const_reference operator[](size_type index) const noexcept {
        return str[index];
    }

    constexpr const_reference at(size_type index) const {
        return index < size() ? str[index] : (throw std::out_of_range("access is out of bounds"), str[index]);
    }

    constexpr const_reference front() const noexcept {
        return str[0];
    }

    constexpr const_reference back() const noexcept {
        return str[size() - 1];
    }

#if defined(GEARS_META_HAS_CPP14)
    constexpr const_pointer data() const noexcept {
        return static_cast<const_pointer>(str);
    }

    constexpr const_pointer c_str() const noexcept {
        return static_cast<const_pointer>(str);
    }

    constexpr const_iterator begin() const noexcept {
        return str;
    }

    constexpr const_iterator cbegin() const noexcept {
        return str;
    }

    constexpr const_iterator end() const noexcept {
        return str + size();
    }

    constexpr const_iterator cend() const noexcept {
        return str + size();
    }
#endif // C++14

    constexpr size_type find(CharT c, size_type pos = 0) const noexcept {
        return pos >= size() ?
               npos : Traits::eq(str[pos], c) ?
                      pos : find(c, pos + 1);
    }

    template<size_t M>
    constexpr size_type find(const basic_string<CharT, M, Traits>& s, size_type pos = 0) const noexcept {
        return s.empty() && pos <= size() ?
               pos : find_substr(s, pos);
    }

    constexpr size_type rfind(CharT c, size_type pos = npos) const noexcept {
        return !empty() && size() - 1 > pos ?
               rfind_character(c, pos + 1) : rfind_character(c, size());
    }

    template<size_t M>
    constexpr size_type rfind(const basic_string<CharT, M, Traits>& s, size_type pos = npos) const noexcept {
        return s.size() > size() ?
               npos : equal_substr(s, min(size() - s.size(), pos)) ?
                      min(size() - s.size(), pos) : rfind_substr(s, min(size() - s.size(), pos));
    }

    constexpr size_type find_first_of(CharT c, size_type pos = 0) const noexcept {
        return find(c, pos);
    }

    template<size_t M>
    constexpr size_type find_first_of(const basic_string<CharT, M, Traits>& s, size_type pos = 0) const noexcept {
        return s.empty() ?
               npos : pos >= size() ?
                      npos : s.find(str[pos]) != npos ?
                             pos : find_first_of(s, pos + 1);
    }

    constexpr size_type find_first_not_of(CharT c, size_type pos = 0) const noexcept {
        return pos >= size() ?
               npos : !Traits::eq(str[pos], c) ?
                      pos : find_first_not_of(c, pos + 1);
    }

    template<size_t M>
    constexpr size_type find_first_not_of(const basic_string<CharT, M, Traits>& s, size_type pos = 0) const noexcept {
        return pos >= size() ?
               npos : s.find(str[pos]) == npos ?
                      pos : find_first_not_of(s, pos + 1);
    }

    constexpr size_type find_last_of(CharT c, size_type pos = npos) const noexcept {
        return rfind(c, pos);
    }

    template<size_t M>
    constexpr size_type find_last_of(const basic_string<CharT, M, Traits>& s, size_type pos = npos) const noexcept {
        return s.empty() ?
               npos :  find_last_tail(s, min(size() - 1, pos));
    }

    constexpr size_type find_last_not_of(CharT c, size_type pos = npos) const noexcept {
        return find_last_not_character(c, min(size() - 1, pos));
    }

    template<size_t M>
    constexpr size_type find_last_not_of(const basic_string<CharT, M, Traits>& s, size_type pos = npos) const noexcept {
        return empty() ?
               npos : find_last_not_tail(s, min(size() - 1, pos));
    }

    template<size_t M>
    constexpr int compare(const basic_string<CharT, M, Traits>& s) const noexcept {
        return compare_impl(s, 0);
    }
};

namespace detail {
template<typename C, typename T, size_t N, size_t M, size_t... Indices1, size_t... Indices2>
constexpr basic_string<C, N + M - 1, T> append(const basic_string<C, N, T>& lhs, const basic_string<C, M, T>& rhs,
                                               meta::index_sequence<Indices1...>, meta::index_sequence<Indices2...>) noexcept {
    return {{ lhs[Indices1]..., rhs[Indices2]...,  T::to_char_type(0) }};
}
} // detail

template<typename CharT, typename Traits, size_t N, size_t M>
constexpr bool operator==(const basic_string<CharT, N, Traits>& lhs, const basic_string<CharT, M, Traits>& rhs) noexcept {
    return lhs.compare(rhs) == 0;
}

template<typename CharT, typename Traits, size_t N, size_t M>
constexpr bool operator!=(const basic_string<CharT, N, Traits>& lhs, const basic_string<CharT, M, Traits>& rhs) noexcept {
    return lhs.compare(rhs) != 0;
}

template<typename CharT, typename Traits, size_t N, size_t M>
constexpr bool operator<(const basic_string<CharT, N, Traits>& lhs, const basic_string<CharT, M, Traits>& rhs) noexcept {
    return lhs.compare(rhs) < 0;
}

template<typename CharT, typename Traits, size_t N, size_t M>
constexpr bool operator>(const basic_string<CharT, N, Traits>& lhs, const basic_string<CharT, M, Traits>& rhs) noexcept {
    return lhs.compare(rhs) > 0;
}

template<typename CharT, typename Traits, size_t N, size_t M>
constexpr bool operator>=(const basic_string<CharT, N, Traits>& lhs, const basic_string<CharT, M, Traits>& rhs) noexcept {
    return !(lhs < rhs);
}

template<typename CharT, typename Traits, size_t N, size_t M>
constexpr bool operator<=(const basic_string<CharT, N, Traits>& lhs, const basic_string<CharT, M, Traits>& rhs) noexcept {
    return !(rhs < lhs);
}

template<typename CharT, typename Traits, size_t N, size_t M, typename Result = basic_string<CharT, N + M - 1, Traits>>
constexpr Result operator+(const basic_string<CharT, N, Traits>& lhs, const basic_string<CharT, M, Traits>& rhs) noexcept {
    return detail::append(lhs, rhs, meta::make_index_sequence<N - 1>{}, meta::make_index_sequence<M - 1>{});
}

template<typename CharT, typename Traits, size_t N>
constexpr basic_string<CharT, N + 1, Traits> operator+(const basic_string<CharT, N, Traits>& lhs, CharT rhs) noexcept {
    return lhs + basic_string<CharT, 2, Traits>{{ rhs, Traits::to_char_type(0) }};
}

template<typename CharT, typename Traits, size_t N>
constexpr basic_string<CharT, N + 1, Traits> operator+(CharT lhs, const basic_string<CharT, N, Traits>& rhs) noexcept {
    return basic_string<CharT, 2, Traits>{{ lhs, Traits::to_char_type(0) }} + rhs;
}

template<typename CharT, size_t N>
constexpr basic_string<CharT, N> make_string(const CharT (&arr)[N]) {
    return { arr };
}
} // leaf
} // gears

#endif // GEARS_LEAF_STRING_HPP
