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

#ifndef GEARS_UTILITY_TRIPLE_HPP
#define GEARS_UTILITY_TRIPLE_HPP

#include "../meta/alias.hpp"
#include <cstddef>

namespace gears {
namespace utility {
template<typename T, typename U, typename V>
struct triple {
    using first_type  = T;
    using second_type = U;
    using third_type  = V;

    T first;
    U second;
    V third;

    triple()              noexcept = default;
    triple(const triple&) noexcept = default;
    triple(triple&&)      noexcept = default;
    
    void swap(triple& t) noexcept(noexcept(std::swap(first, t.first))   &&
                                  noexcept(std::swap(second, t.second)) &&
                                  noexcept(std::swap(third, t.third))) {
        using std::swap;
        swap(first, t.first);
        swap(second, t.second);
        swap(third, t.third);
    }
};

template<typename T, typename U, typename V>
constexpr bool operator==(const triple<T, U, V>& lhs, const triple<T, U, V>& rhs) {
    return lhs.first == rhs.first && lhs.second == rhs.second && lhs.third == rhs.third;
}

template<typename T, typename U, typename V>
constexpr bool operator<(const triple<T, U, V>& lhs, const triple<T, U, V>& rhs) {
    return   lhs.first < rhs.first  ? true  :
             rhs.first < lhs.first  ? false :
            lhs.second < rhs.second ? true  :
            rhs.second < lhs.second ? false :
             lhs.third < rhs.third;
}

template<typename T, typename U, typename V>
constexpr bool operator!=(const triple<T, U, V>& lhs, const triple<T, U, V>& rhs) {
    return !(lhs == rhs);
}

template<typename T, typename U, typename V>
constexpr bool operator>(const triple<T, U, V>& lhs, const triple<T, U, V>& rhs) {
    return (rhs < lhs);
}

template<typename T, typename U, typename V>
constexpr bool operator>=(const triple<T, U, V>& lhs, const triple<T, U, V>& rhs) {
    return !(lhs < rhs);
}

template<typename T, typename U, typename V>
constexpr bool operator<=(const triple<T, U, V>& lhs, const triple<T, U, V>& rhs) {
    return !(rhs < lhs);
}

template<typename T, typename U, typename V>
inline void swap(triple<T, U, V>& lhs, triple<T, U, V>& rhs) noexcept(noexcept(lhs.swap(rhs))) {
    lhs.swap(rhs);
}

template<typename T, typename U, typename V>
constexpr triple<meta::Decay<T>, meta::Decay<U>, meta::Decay<V>> make_triple(T&& t, U&& u, V&& v) {
    return { std::forward<T>(t), std::forward<U>(u), std::forward<V>(v) };
}
} // utility
} // gears

namespace triple_detail {
template<size_t N> struct triple_get;

template<>
struct triple_get<0> {
    template<typename T, typename U, typename V>
    static constexpr T& get(gears::utility::triple<T, U, V>& t) noexcept {
        return t.first;
    }

    template<typename T, typename U, typename V>
    static constexpr const T& const_get(const gears::utility::triple<T, U, V>& t) noexcept {
        return t.first;
    }

    template<typename T, typename U, typename V>
    static constexpr T&& move_get(gears::utility::triple<T, U, V>&& t) noexcept {
        return std::forward<T>(t.first);
    }
};

template<>
struct triple_get<1> {
    template<typename T, typename U, typename V>
    static constexpr U& get(gears::utility::triple<T, U, V>& t) noexcept {
        return t.second;
    }

    template<typename T, typename U, typename V>
    static constexpr const U& const_get(const gears::utility::triple<T, U, V>& t) noexcept {
        return t.second;
    }

    template<typename T, typename U, typename V>
    static constexpr U&& move_get(gears::utility::triple<T, U, V>&& t) noexcept {
        return std::forward<U>(t.second);
    }
};

template<>
struct triple_get<2> {
    template<typename T, typename U, typename V>
    static constexpr V& get(gears::utility::triple<T, U, V>& t) noexcept {
        return t.third;
    }

    template<typename T, typename U, typename V>
    static constexpr const V& const_get(const gears::utility::triple<T, U, V>& t) noexcept {
        return t.third;
    }

    template<typename T, typename U, typename V>
    static constexpr V&& move_get(gears::utility::triple<T, U, V>&& t) noexcept {
        return std::forward<V>(t.third);
    }
};
} // triple_detail

namespace std {
template<typename T> struct tuple_size;
template<size_t N, typename T> struct tuple_element;

template<typename T, typename U, typename V>
struct tuple_size<gears::utility::triple<T, U, V>> : gears::meta::Const<size_t, 3> {};

template<typename T, typename U, typename V>
struct tuple_element<0, gears::utility::triple<T, U, V>> {
    using type = T;
};

template<typename T, typename U, typename V>
struct tuple_element<1, gears::utility::triple<T, U, V>> {
    using type = U;
};

template<typename T, typename U, typename V>
struct tuple_element<2, gears::utility::triple<T, U, V>> {
    using type = V;
};
} // std

namespace gears {
namespace utility {
template<size_t N, typename T, typename U, typename V>
constexpr gears::meta::Type<std::tuple_element<N, triple<T, U, V>>>& get(triple<T, U, V>& t) noexcept {
    return triple_detail::triple_get<N>::get(t);
}

template<size_t N, typename T, typename U, typename V>
constexpr const gears::meta::Type<std::tuple_element<N, triple<T, U, V>>>& get(const triple<T, U, V>& t) noexcept {
    return triple_detail::triple_get<N>::const_get(t);
}

template<size_t N, typename T, typename U, typename V>
constexpr gears::meta::Type<std::tuple_element<N, triple<T, U, V>>>&& get(triple<T, U, V>&& t) noexcept {
    return triple_detail::triple_get<N>::move_get(std::move(t));
}
} // utility
} // gears

#endif // GEARS_UTILITY_TRIPLE_HPP