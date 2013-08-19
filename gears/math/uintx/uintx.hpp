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

#ifndef GEARS_MATH_UINTX_UINTX_HPP
#define GEARS_MATH_UINTX_UINTX_HPP

#include <cstddef>
#include <limits>
#include <vector>
#include <string>
#include "../../meta/alias.hpp"

namespace gears {
namespace uintx_detail {
constexpr size_t pow(size_t base, size_t exponent) {
    return exponent == 0 ? 1 : (base * pow(base, exponent - 1));
}

template<typename Cont>
inline void reverse(Cont& c) {
    auto first = std::begin(c);
    auto last = std::end(c);

    if(first == last)
        return;
    --last;
    while(first < last) {
        using std::swap;
        swap(*first, *last);
        ++first;
        --last;
    }
}
} // uintx_detail

template<size_t Bits = -1, typename Digit = unsigned int, typename Digits = unsigned long long>
struct uintx {
private:
    using signed_type = typename std::make_signed<Digits>::type;
    static constexpr size_t digit_bits = sizeof(Digits) * 8;
    static constexpr size_t digit_count = Bits == size_t(-1) ? -1 : (Bits / digit_bits);
    static_assert(digit_count, "Invalid bits parameter. >= 128 recommended or none for infinite precision");

    std::vector<Digits> digits;

    struct add {
        Digits operator()(Digits a, Digits b) {
            return a + b;
        }
    };

    struct carry {
        Digits& c;
        carry(Digits& a): c(a) {}

        Digits operator()(Digits n) {
            n += c;
            c = n / base;
            n %= base;

            return n;
        }
    };

    template<class Base>
    struct operator_carry : public Base, public carry {
        operator_carry(Digits& c): carry(c) {}

        Digits operator()(Digits a) {
            return carry::operator()(Base::operator()(a));
        }

        Digits operator()(Digits a, Digits b) {
            return carry::operator()(Base::operator()(a, b));
        }
    };

    void normalize() {
        while(digits.size() > 1) {
            if(digits.back() == 0)
                digits.pop_back();
            else
                break;
        }
    }

    void check_bits() {
        if(digit_count == Bits)
            return;
        if(digits.capacity() >= digit_count)
            digits.resize(digit_count);
    }

public:
    static constexpr size_t digits10 = std::numeric_limits<Digit>::digits10;
    static constexpr size_t base = detail::pow(10, digits10);
    uintx(): digits(1) {}

    template<typename Integer, EnableIf<std::is_integral<Integer>>...>
    uintx(Integer value) {
        value = abs(value);
        do {
            digits.push_back(value % base);
            value /= base;
        }
        while(value > 0);
    }

    uintx(const std::string& s) {
        size_t count = digits10 - (s.size() % digits10);
        std::string str(count, '0');
        str += s;
        digits.reserve(str.size() / digits10 + 1);
        auto size = str.size();
        size_t position = 0;

        while(position != size) {
            digits.push_back(std::stoull(str.substr(position, digits10)));
            position += digits10;
        }

        uintx_detail::reverse(digits);
        check_bits();
    }

    uintx& operator+=(const uintx& other) {
        if(digits.size() < other.digits.size()) {
            digits.resize(other.digits.size());
        }

        Digits c = 0;
        operator_carry<add> addwc(c);

        using uintx_detail::map;

        auto it = map(other.digits.begin(), other.digits.end(), digits.begin(), digits.begin(), addwc);
        map(it, digits.end(), it, carry(c));

        if(c)
            digits.push_back(c);

        normalize();
        check_bits();
        return *this;
    }

    uintx operator+(const uintx& other) const {
        uintx result(*this);
        return (result += other);
    }
};
} // gears

#endif // GEARS_MATH_UINTX_UINTX_HPP