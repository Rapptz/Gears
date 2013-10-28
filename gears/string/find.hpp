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

#ifndef GEARS_STRING_FIND_HPP
#define GEARS_STRING_FIND_HPP

#include "../meta/alias.hpp"

namespace gears {
namespace string_find_detail {
template<typename T>
struct negator {
    T pred;
    negator(T t): pred(std::move(t)) {}
    template<typename... Args>
    auto operator()(Args&&... args) -> decltype(!pred(std::forward<Args>(args)...)) {
        return !pred(std::forward<Args>(args)...);
    }
};

template<typename T>
using SizeType = typename meta::Unqualified<T>::size_type;
} // string_find_detail

template<typename String, typename UnaryPredicate>
inline string_find_detail::SizeType<String> find_first_of(const String& str, UnaryPredicate&& pred) {
    for(unsigned i = 0; i < str.size(); ++i) {
        if(pred(str[i]))
            return i;
    }
    return string_find_detail::SizeType<String>(-1); // npos
}

template<typename String, typename UnaryPredicate>
inline string_find_detail::SizeType<String> find_first_not_of(const String& str, UnaryPredicate&& pred) {
    return find_first_of(str, string_find_detail::negator<UnaryPredicate>(pred));
}

template<typename String, typename UnaryPredicate>
inline string_find_detail::SizeType<String> find_last_of(const String& str, UnaryPredicate&& pred) {
    for(unsigned i = str.size() - 1; i >= 0; --i) {
        if(pred(str[i]))
            return i;
    }
    return string_find_detail::SizeType<String>(-1); // npos
}

template<typename String, typename UnaryPredicate>
inline string_find_detail::SizeType<String> find_last_not_of(const String& str, UnaryPredicate&& pred) {
    return find_last_of(str, string_find_detail::negator<UnaryPredicate>(pred));
}
} // gears

#endif // GEARS_STRING_FIND_HPP