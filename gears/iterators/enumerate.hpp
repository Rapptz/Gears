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

#ifndef GEARS_ITERATORS_ENUMERATE_HPP
#define GEARS_ITERATORS_ENUMERATE_HPP

#include "primitives.hpp"

namespace gears {
template<typename T>
struct enumerator_data {
    T element;
    size_t index;
};

template<typename Iterable>
struct enumerator_iterator : input_iterator<enumerator_data<typename Iterable::value_type>> {
private:
    enumerator_data<typename Iterable::value_type> value;
    typename Iterable::const_iterator it;
    size_t count;
    size_t maximum;
public:
    enumerator_iterator() noexcept: count(0), maximum(0) {}
    enumerator_iterator(const Iterable& cont, size_t c = 0) noexcept: it(cont.cbegin()), count(c) {
        std::advance(it, count);
        maximum = std::distance(cont.cbegin(), cont.cend());
        if(count < maximum) {
            value.element = *it;
            value.index = count;
        }
    }

    auto operator++() noexcept -> decltype(*this) {
        if(count < maximum) {
            value.element = *++it;
            value.index = ++count;
        }
        return *this;
    }

    enumerator_iterator operator++(int) noexcept {
        auto copy(*this);
        ++(*copy);
        return copy;
    }

    auto operator*() const noexcept -> decltype(value) {
        return value;
    }

    auto operator->() const noexcept -> decltype(&value) {
        return &value;
    }

    bool operator==(const enumerator_iterator& other) const noexcept {
        bool status = count < maximum;
        bool other_status = other.count < other.maximum;
        return (status == other_status) && (!status || it == other.it);
    }

    bool operator!=(const enumerator_iterator& other) const noexcept {
        return not (*this == other);
    }
};

template<typename Iterable>
struct enumerator {
private:
    enumerator_iterator<Iterable> first;
public:
    enumerator(const Iterable& it, size_t count = 0) noexcept: first(it, count) {}

    auto begin() const noexcept -> decltype(first) {
        return first;
    }

    auto end() const noexcept -> decltype(first) {
        return {};
    }
};

template<typename Iterable>
inline enumerator<Iterable> enumerate(const Iterable& iterable, size_t count = 0) noexcept {
    return { iterable, count };
}
} // gears

#endif // GEARS_ITERATORS_ENUMERATE_HPP