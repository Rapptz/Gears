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

#ifndef GEARS_UTILITY_MAYBE_BASE_HPP
#define GEARS_UTILITY_MAYBE_BASE_HPP

#include <gears/utility/maybe/storage.hpp>

namespace gears {
namespace detail {
template<typename T>
struct maybe_base {
    bool valid;
    maybe_storage<T> storage;

    constexpr maybe_base() noexcept: valid(false), storage(default_init) {}
    constexpr explicit maybe_base(regular_init_t, bool valid) noexcept: valid(valid), storage(default_init) {}
    constexpr explicit maybe_base(const T& value): valid(true), storage(value) {}
    constexpr explicit maybe_base(T&& value): valid(true), storage(meta::cmove(value)) {}

    template<typename... Args>
    explicit maybe_base(in_place_t, Args&&... args): valid(true), storage(meta::cforward<Args>(args)...) {}

    ~maybe_base() {
        if(valid) {
            storage.value.T::~T();
        }
    }
};

template<typename T>
struct cmaybe_base {
    bool valid;
    cmaybe_storage<T> storage;

    constexpr cmaybe_base() noexcept: valid(false), storage(default_init) {}
    constexpr explicit cmaybe_base(regular_init_t, bool valid) noexcept: valid(valid), storage(default_init) {}
    constexpr explicit cmaybe_base(const T& value): valid(true), storage(value) {}
    constexpr explicit cmaybe_base(T&& value): valid(true), storage(meta::cmove(value)) {}

    template<typename... Args>
    constexpr explicit cmaybe_base(in_place_t, Args&&... args): valid(true), storage(meta::cforward<Args>(args)...) {}

    ~cmaybe_base() = default;
};
} // detail
} // gears

#endif // GEARS_UTILITY_MAYBE_BASE_HPP
