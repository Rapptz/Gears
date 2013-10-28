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

#ifndef GEARS_UTILITY_MAYBE_HPP
#define GEARS_UTILITY_MAYBE_HPP

#include "maybe/traits.hpp"
#include "maybe/base.hpp"
#include <exception>

namespace gears {
namespace utility {
namespace detail {
struct bad_maybe_access : std::exception {
    virtual const char* what() const noexcept {
        return "bad maybe access";
    }
};
} // detail

template<typename T>
using MaybeBase = meta::If<std::is_trivially_destructible<T>, detail::cmaybe_base<T>, detail::maybe_base<T>>;

template<typename T>
class maybe : private MaybeBase<T> {
    static_assert(!std::is_same<meta::Decay<T>, nothing_t>(), "Invalid type. Must not be nothing");
    static_assert(!std::is_same<meta::Decay<T>, in_place_t>(), "Invalid type. Must not be in_place tag");
    static_assert(!std::is_reference<T>(), "Invalid type. Must not be a reference type");
    static_assert(!is_maybe<T>(), "Invalid type. Must not be a maybe type");

    constexpr bool is_valid() const noexcept {
        return MaybeBase<T>::valid;
    }

    T* data() {
        return std::addressof(MaybeBase<T>::storage.value);
    }

    constexpr const T* data() const {
        return detail::address_of(MaybeBase<T>::storage.value);
    }

    constexpr const T& internal() const {
        return MaybeBase<T>::storage.value;
    }

    T& internal() {
        return MaybeBase<T>::storage.value;
    }

    void clear() noexcept {
        if(is_valid()) {
            data()->T::~T();
        }
        MaybeBase<T>::valid = false;
    }

    template<typename... Args>
    void initialise(Args&&... args) noexcept(noexcept(T(std::forward<Args>(args)...))) {
        new(data()) T(std::forward<Args>(args)...);
        MaybeBase<T>::valid = true;
    }

public:
    using value_type = T;

    constexpr maybe() noexcept: MaybeBase<T>() {}
    constexpr maybe(nothing_t) noexcept : MaybeBase<T>() {}
    constexpr maybe(const T& value): MaybeBase<T>(value) {}
    constexpr maybe(T&& value): MaybeBase<T>(meta::cmove(value)) {}

    template<typename... Args>
    constexpr explicit maybe(in_place_t, Args&&... args): MaybeBase<T>(in_place, meta::cforward<Args>(args)...) {}

    maybe(const maybe& rhs): MaybeBase<T>(detail::regular_init, rhs.is_valid()) {
        if(rhs.is_valid()) {
            new(data()) T(rhs.internal());
        }
    }

    maybe(maybe&& rhs) noexcept(std::is_nothrow_move_constructible<T>()): MaybeBase<T>(detail::regular_init, rhs.is_valid()) {
        if(rhs.is_valid()) {
            new(data()) T(std::move(rhs.internal()));
        }
    }

    ~maybe() = default;

    maybe& operator=(nothing_t) noexcept {
        clear();
        return *this;
    }

    maybe& operator=(const maybe& rhs) {
        if(is_valid() && !rhs.is_valid()) {
            clear();
        }
        else if(!is_valid() && rhs.is_valid()) {
            initialise(rhs.internal());
        }
        else if(is_valid() && rhs.is_valid()) {
            internal() = rhs.internal();
        }

        return *this;
    }

    maybe& operator=(maybe&& rhs) noexcept(std::is_nothrow_move_assignable<T>() && std::is_nothrow_move_constructible<T>()) {
        if(is_valid() && !rhs.is_valid()) {
            clear();
        }
        else if(!is_valid() && rhs.is_valid()) {
            initialise(std::move(rhs.internal()));
        }
        else if(is_valid() && rhs.is_valid()) {
            internal() = std::move(rhs.internal());
        }

        return *this;
    }

    template<typename U, meta::EnableIf<std::is_constructible<T, meta::Decay<U>>, std::is_assignable<T, meta::Decay<U>>>...>
    maybe& operator=(U&& value) {
        if(is_valid()) {
            internal() = std::forward<U>(value);
        }
        else {
            initialise(std::forward<U>(value));
        }
        return *this;
    }

    template<typename... Args>
    void emplace(Args&&... args) {
        clear();
        initialise(std::forward<Args>(args)...);
    }

    constexpr const T* operator->() const {
        return data();
    }

    T* operator->() {
        return data();
    }

    constexpr const T& operator*() const {
        return internal();
    }

    T& operator*() {
        return internal();
    }

    constexpr const T& value() const {
        return is_valid() ? internal() : (throw detail::bad_maybe_access(), internal());
    }

    T& value() {
        return is_valid() ? internal() : (throw detail::bad_maybe_access(), internal());
    }

    constexpr explicit operator bool() const noexcept {
        return is_valid();
    }

    template<typename U>
    constexpr T value_or(U&& value) const {
        return is_valid() ? internal() : static_cast<T>(meta::cforward<U>(value));
    }
};

template<typename T>
constexpr maybe<meta::Decay<T>> just(T&& t) {
    return { meta::cforward<T>(t) };
}

// Comparison with maybe<T> and maybe<T>
template<typename T>
constexpr bool operator==(const maybe<T>& lhs, const maybe<T>& rhs) {
    return static_cast<bool>(lhs) != static_cast<bool>(rhs) ? false : static_cast<bool>(lhs) == false ? true  : *lhs == *rhs;
}

template<typename T>
constexpr bool operator!=(const maybe<T>& lhs, const maybe<T>& rhs) {
    return !(lhs == rhs);
}

template<typename T>
constexpr bool operator<(const maybe<T>& lhs, const maybe<T>& rhs) {
    return !rhs ? false : !lhs ? true : *lhs < *rhs;
}

template<typename T>
constexpr bool operator>(const maybe<T>& lhs, const maybe<T>& rhs) {
    return (rhs < lhs);
}

template<typename T> 
constexpr bool operator<=(const maybe<T>& lhs, const maybe<T>& rhs) {
    return !(rhs < lhs);
}

template<typename T> 
constexpr bool operator>=(const maybe<T>& lhs, const maybe<T>& rhs) {
    return !(lhs < rhs);
}

// Comparison with nothing
template<typename T>
constexpr bool operator==(const maybe<T>& lhs, nothing_t) noexcept {
    return !lhs;
}

template<typename T>
constexpr bool operator==(nothing_t, const maybe<T>& rhs) noexcept {
    return !rhs;
}

template<typename T>
constexpr bool operator!=(const maybe<T>& lhs, nothing_t) noexcept {
    return static_cast<bool>(lhs);
}

template<typename T>
constexpr bool operator!=(nothing_t, const maybe<T>& rhs) noexcept {
    return static_cast<bool>(rhs);
}

template<typename T>
constexpr bool operator<(const maybe<T>& lhs, nothing_t) noexcept {
    return false;
}

template<typename T>
constexpr bool operator<(nothing_t, const maybe<T>& rhs) noexcept {
    return static_cast<bool>(rhs);
}

template<typename T> 
constexpr bool operator>(const maybe<T>& lhs, nothing_t) noexcept {
    return static_cast<bool>(lhs);
}

template<typename T> 
constexpr bool operator>(nothing_t, const maybe<T>&) noexcept {
    return false;
}

template<typename T>
constexpr bool operator<=(const maybe<T>& lhs, nothing_t) noexcept {
    return !lhs;
}

template<typename T>
constexpr bool operator<=(nothing_t, const maybe<T>&) noexcept {
    return true;
}

template<typename T> 
constexpr bool operator>=(const maybe<T>&, nothing_t) noexcept {
    return true;
}

template<typename T> 
constexpr bool operator>=(nothing_t, const maybe<T>& rhs) noexcept {
    return !rhs;
}

// Comparisons with T

template<typename T>
constexpr bool operator==(const maybe<T>& lhs, const T& value) {
    return static_cast<bool>(lhs) ? *lhs == value : false;
}

template<typename T>
constexpr bool operator==(const T& value, const maybe<T>& rhs) {
    return static_cast<bool>(rhs) ? value == *rhs : false;
}

template<typename T>
constexpr bool operator!=(const maybe<T>& lhs, const T& value) {
    return static_cast<bool>(lhs) ? *lhs != value : true;
}

template<typename T>
constexpr bool operator!=(const T& value, const maybe<T>& rhs) {
    return static_cast<bool>(rhs) ? value != *rhs : true;
}

template<typename T>
constexpr bool operator<(const maybe<T>& lhs, const T& value) {
    return static_cast<bool>(lhs) ? *lhs < value : true;
}

template<typename T>
constexpr bool operator>(const T& value, const maybe<T>& rhs) {
    return static_cast<bool>(rhs) ? value > *rhs : true;
}

template<typename T>
constexpr bool operator>(const maybe<T>& lhs, const T& value) {
    return static_cast<bool>(lhs) ? *lhs > value : false;
}

template<typename T>
constexpr bool operator<(const T& value, const maybe<T>& rhs) {
    return static_cast<bool>(rhs) ? value < *rhs : false;
}

template<typename T>
constexpr bool operator>=(const maybe<T>& lhs, const T& value) {
    return static_cast<bool>(lhs) ? *lhs >= value : false;
}

template<typename T>
constexpr bool operator<=(const T& value, const maybe<T>& rhs) {
    return static_cast<bool>(rhs) ? value <= *rhs : false;
}

template<typename T>
constexpr bool operator<=(const maybe<T>& lhs, const T& value) {
    return static_cast<bool>(lhs) ? *lhs <= value : true;
}

template<typename T>
constexpr bool operator>=(const T& value, const maybe<T>& rhs) {
    return static_cast<bool>(rhs) ? value >= *rhs : true;
}
} // utility
} // gears

#endif // GEARS_UTILITY_MAYBE_HPP