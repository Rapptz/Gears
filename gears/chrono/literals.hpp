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

#ifndef GEARS_CHRONO_LITERALS_HPP
#define GEARS_CHRONO_LITERALS_HPP

#include <chrono>

namespace gears {
namespace literals {
constexpr std::chrono::duration<long double, std::ratio<3600>> operator"" _h(long double hours) {
    return std::chrono::duration<long double, std::ratio<3600>>{ hours };
}

constexpr std::chrono::duration<long double, std::ratio<60>> operator"" _min(long double minutes) {
    return std::chrono::duration<long double, std::ratio<60>>{ minutes };
}

constexpr std::chrono::duration<long double> operator"" _s(long double seconds) {
    return std::chrono::duration<long double>{ seconds };
}

constexpr std::chrono::duration<long double, std::milli> operator"" _ms(long double milliseconds) {
    return std::chrono::duration<long double, std::milli>{ milliseconds };
}

constexpr std::chrono::duration<long double, std::micro> operator"" _us(long double microseconds) {
    return std::chrono::duration<long double, std::micro>{ microseconds };
}

constexpr std::chrono::duration<long double, std::nano> operator"" _ns(long double nanoseconds) {
    return std::chrono::duration<long double, std::nano>{ nanoseconds };
}

constexpr std::chrono::duration<unsigned long long, std::ratio<3600>> operator"" _h(unsigned long long hours) {
    return std::chrono::duration<unsigned long long, std::ratio<3600>>{ hours };
}

constexpr std::chrono::duration<unsigned long long, std::ratio<60>> operator"" _min(unsigned long long minutes) {
    return std::chrono::duration<unsigned long long, std::ratio<60>>{ minutes };
}

constexpr std::chrono::duration<unsigned long long> operator"" _s(unsigned long long seconds) {
    return std::chrono::duration<unsigned long long>{ seconds };
}

constexpr std::chrono::duration<unsigned long long, std::milli> operator"" _ms(unsigned long long milliseconds) {
    return std::chrono::duration<unsigned long long, std::milli>{ milliseconds };
}

constexpr std::chrono::duration<unsigned long long, std::micro> operator"" _us(unsigned long long microseconds) {
    return std::chrono::duration<unsigned long long, std::micro>{ microseconds };
}

constexpr std::chrono::duration<unsigned long long, std::nano> operator"" _ns(unsigned long long nanoseconds) {
    return std::chrono::duration<unsigned long long, std::nano>{ nanoseconds };
}
} // literals
} // gears


#endif // GEARS_CHRONO_LITERALS_HPP