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

#ifndef GEARS_UTILITY_MAYBE_STORAGE_HPP
#define GEARS_UTILITY_MAYBE_STORAGE_HPP

#include "tags.hpp"
#include "../../meta/utility.hpp"
#include "../../meta/enable_if.hpp"
#include "../../meta/qualifiers.hpp"

namespace gears {
namespace utility {
namespace detail {
template<typename T>
union maybe_storage {
    unsigned char c;
    T value;

    template<typename... Args>
    constexpr maybe_storage(Args&&... args): value(meta::cforward<Args>(args)...) {}
    constexpr maybe_storage(default_init_t) noexcept: c() {}
    ~maybe_storage() {}
};

template<typename T>
union cmaybe_storage {
    unsigned char c;
    T value;

    template<typename... Args>
    constexpr cmaybe_storage(Args&&... args): value(meta::cforward<Args>(args)...) {}
    constexpr cmaybe_storage(default_init_t) noexcept: c() {}
    ~cmaybe_storage() = default;
};
} // detail
} // utility
} // gears

#endif // GEARS_UTILITY_MAYBE_STORAGE_HPP
