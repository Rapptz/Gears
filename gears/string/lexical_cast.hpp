// The MIT License (MIT)

// Copyright (c) 2012-2014 Rapptz

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

#ifndef GEARS_STRING_LEXICAL_CAST_HPP
#define GEARS_STRING_LEXICAL_CAST_HPP

#include <string>
#include <sstream>
#include <stdexcept>

namespace gears {
namespace string {
namespace detail {
template<typename Target>
struct lexical_caster {
    template<typename CharT>
    static inline Target cast(const std::basic_string<CharT>& str) {
        std::basic_istringstream<CharT> ss(str);
        Target result;
        if((ss >> result).fail() || !(ss >> std::ws).eof()) {
            throw std::invalid_argument("lexical_cast failed");
        }
        return result;
    }
};

template<typename CharT>
struct lexical_caster<std::basic_string<CharT>> {
    static inline std::basic_string<CharT> cast(const std::basic_string<CharT>& str) {
        return str;
    }
};

template<>
struct lexical_caster<int> {
    template<typename CharT>
    static inline int cast(const std::basic_string<CharT>& str) {
        return std::stoi(str);
    }
};

template<>
struct lexical_caster<long> {
    template<typename CharT>
    static inline long cast(const std::basic_string<CharT>& str) {
        return std::stol(str);
    }
};


template<>
struct lexical_caster<long long> {
    template<typename CharT>
    static inline long long cast(const std::basic_string<CharT>& str) {
        return std::stoll(str);
    }
};

template<>
struct lexical_caster<float> {
    template<typename CharT>
    static inline float cast(const std::basic_string<CharT>& str) {
        return std::stof(str);
    }
};

template<>
struct lexical_caster<double> {
    template<typename CharT>
    static inline double cast(const std::basic_string<CharT>& str) {
        return std::stod(str);
    }
};

template<>
struct lexical_caster<long double> {
    template<typename CharT>
    static inline long double cast(const std::basic_string<CharT>& str) {
        return std::stold(str);
    }
};

template<>
struct lexical_caster<unsigned long> {
    template<typename CharT>
    static inline unsigned long cast(const std::basic_string<CharT>& str) {
        return std::stoul(str);
    }
};

template<>
struct lexical_caster<unsigned long long> {
    template<typename CharT>
    static inline unsigned long long cast(const std::basic_string<CharT>& str) {
        return std::stoull(str);
    }
};

template<typename T>
struct remove_const {
    using type = T;
};

template<typename T>
struct remove_const<const T> {
    using type = T;
};

template<typename T>
struct remove_volatile {
    using type = T;
};

template<typename T>
struct remove_volatile<volatile T> {
    using type = T;
};

template<typename T>
struct remove_cv {
    using type = typename std::remove_volatile<typename std::remove_const<T>::type>::type;
};
} // detail

/**
 * @ingroup string
 * @brief Converts a string to its integral representation.
 * @details Converts a string to its arithmetic representation.
 * A generic way of handling the standard library's std::sto* functions.
 * If the conversion fails, throws `std::invalid_argument`. If a
 * specialisation isn't picked, the function falls back to using
 * `std::basic_istringstream`. The type to convert to must be
 * `DefaultConstructible`. All cv-qualifiers are removed from
 * the type before casting.
 *
 * @param str String to convert from.
 * @tparam Target Type to convert to.
 * @throws std::invalid_argument thrown whenever conversion fails.
 * @return The arithmetic representation of the string.
 */
template<typename Target, typename CharT>
inline Target lexical_cast(const std::basic_string<CharT>& str) {
    return detail::lexical_caster<typename detail::remove_cv<Target>::type>::cast(str);
}
} // string
} // gears

#endif // GEARS_STRING_LEXICAL_CAST_HPP
