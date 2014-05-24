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

#ifndef GEARS_IO_FLAGS_HPP
#define GEARS_IO_FLAGS_HPP

#include <iosfwd>
#include "../meta/indices.hpp"
#include "../meta/expand.hpp"
#include "../adl/get.hpp"

namespace gears {
namespace io {
namespace detail {
template<typename T>
struct flag_type {
    const T& value;
    std::ios_base::fmtflags flag;
    flag_type(const T& t, std::ios_base::fmtflags flag): value(t), flag(flag) {}
};

template<typename T, typename... Flags>
struct manipulator_type {
    const T& value;
    std::tuple<Flags...> flags;
    manipulator_type(const T& t, Flags&&... f): value(t), flags(f...) {}
};

template<class Elem, class Traits, typename T>
inline std::basic_ostream<Elem, Traits>& operator<<(std::basic_ostream<Elem, Traits>& out, const flag_type<T>& f) {
    out.flags(f.flag);
    out << f.value;
    out.unsetf(f.flag);
    return out;
}

template<class Elem, class Traits, class Tuple, size_t... Indices>
inline void apply_flags(std::basic_ostream<Elem, Traits>& out, const Tuple& t, meta::indices<Indices...>) {
    GEARS_EXPAND(out << adl::get<Indices>(t));
}

template<class Elem, class Traits, typename T, typename... Flags>
inline std::basic_ostream<Elem, Traits>& operator<<(std::basic_ostream<Elem, Traits>& out, const manipulator_type<T, Flags...>& f) {
    apply_flags(out, f.flags, meta::build_indices<sizeof...(Flags)>{});
    return out << f.value;
}
} // detail

/**
 * @ingroup io
 * @brief A flag that only gets activated once.
 * @details A flag that gets activated once on the 
 * value of t. Useful for passing to io::print, 
 * io::fprint and io::sprint.
 * 
 * @param t Variable to get manipulated
 * @param flag Flag to manipulate the stream
 * @return Stream object that activates the flag once.
 */
template<typename T>
inline detail::flag_type<T> flags(T&& t, std::ios_base::fmtflags flag) {
    return { std::forward<T>(t), flag };
}

/**
 * @ingroup io
 * @brief A flag that is persistent.
 * @details A flag that persistent on the 
 * value of t and any value afterwards. Useful 
 * for passing to io::print, io::fprint and io::sprint.
 * Outside of using it for those functions, it's not
 * advised to use it.
 * 
 * @param t Variable to get manipulated
 * @param flags Flags to manipulate the stream persistently
 * @return Stream object that activates the flag persistently.
 */
template<typename T, typename... Flags>
inline detail::manipulator_type<T, Flags...> flags(T&& t, Flags&&... flags) {
    return { std::forward<T>(t), std::forward<Flags>(flags)... };
}
} // io
} // gears

#endif // GEARS_IO_FLAGS_HPP