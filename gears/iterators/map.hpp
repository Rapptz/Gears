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

#ifndef GEARS_ITERATORS_MAP_HPP
#define GEARS_ITERATORS_MAP_HPP

#include "primitives.hpp"
#include <utility>

namespace gears {
template<typename Cont, typename Function>
struct map_iterator : input_iterator<decltype(std::declval<Function&>()(*std::declval<Cont&>().begin()))> {
private:
    const Function* func;
    const Cont* reader;
    typename Cont::const_iterator it;
    decltype(std::declval<Function&>()(*std::declval<Cont&>().begin())) value;
    bool status;
public:
    map_iterator() noexcept: func(nullptr), reader(nullptr), status(false) {}
    map_iterator(const Cont& c, const Function& f) noexcept: func(&f), reader(&c), it(c.cbegin()) {
        status = it != reader->cend();
        if(!status)
            return;
        auto&& temp = *func;
        value = temp(*it);
    }

    auto operator++() noexcept -> decltype(*this) {
        if(status) {
            auto&& temp = *func;
            value = temp(*++it);
        }
        status = status && it != reader->cend();
        return *this;
    }

    map_iterator operator++(int) noexcept {
        auto copy(*this);
        ++(*this);
        return copy;
    }

    auto operator*() const noexcept -> decltype(value) {
        return value;
    }

    auto operator->() const noexcept -> decltype(&value) {
        return &value;
    }

    bool operator==(const map_iterator& other) const noexcept {
        return status == other.status && (!status || reader == other.reader);
    }

    bool operator!=(const map_iterator& other) const noexcept {
        return not (*this == other);
    }
};

template<typename Cont, typename Function>
struct mapper {
private:
    map_iterator<Cont, Function> first;
public:
    mapper(const Cont& c, Function&& f): first(c, std::forward<Function>(f)) {}

    auto begin() noexcept -> decltype(first) {
        return first;
    }

    auto end() noexcept -> decltype(first) {
        return {};
    }
};

template<typename Cont, typename Function>
inline mapper<Cont, Function> map(const Cont& c, Function&& f) {
    return { c, std::forward<Function>(f) };
}
} // gears
 
#endif // GEARS_ITERATORS_MAP_HPP