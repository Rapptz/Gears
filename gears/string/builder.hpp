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

#ifndef GEARS_STRING_BUILDER_HPP
#define GEARS_STRING_BUILDER_HPP

#include <sstream>
#include <utility>

namespace gears {
namespace string {
template<typename CharT = char>
struct stringbuilder {
private:
    std::basic_ostringstream<CharT> ss;
public:
    stringbuilder() = default;
    stringbuilder(decltype(ss.str()) str): ss(std::move(str), std::ios_base::ate) {}

    template<typename T>
    auto operator<<(T&& data) -> decltype(*this) {
        ss << std::forward<T>(data);
        return *this;
    }

    template<typename T>
    auto append(T&& data) -> decltype(*this) {
        ss << std::forward<T>(data);
        return *this;
    }

    auto clear() -> decltype(*this) {
        ss.str(CharT());
        ss.clear();
        return *this;
    }

    auto to_string() -> decltype(ss.str()) {
        return { ss.str() };
    }

    operator decltype(ss.str())() {
        return { ss.str() };
    }
};
} // string
} // gears

#endif // GEARS_STRING_BUILDER_HPP
