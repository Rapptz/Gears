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

#ifndef GEARS_PROGRAM_OPTIONS_DETAILS_HPP
#define GEARS_PROGRAM_OPTIONS_DETAILS_HPP

#include <typeinfo>
#include <sstream>
#include <utility>

namespace gears {
namespace detail {
struct bad_lexical_cast : std::bad_cast {
    virtual const char* what() const noexcept {
        return "bad_lexical_cast";
    }
};

struct arg_not_found : std::exception {
    std::string str;
    arg_not_found(const std::string& str): str(str) {}
    virtual const char* what() const noexcept {
        return str.c_str();
    }
};

template<typename T>
T lexical_cast(const std::string& str) {
    std::stringstream ss(str);
    T result;
    if((ss >> result).fail() || !(ss >> std::ws).eof())
        throw bad_lexical_cast();
    return result;
}

template<typename Cont, typename T>
auto insert_impl(Cont& c, T&& t) -> decltype(c.push_back(std::forward<T>(t)), void()) {
    c.push_back(std::forward<T>(t));
}

template<typename Cont, typename T>
auto insert_impl(Cont& c, T&& t) -> decltype(c.insert(std::forward<T>(t)), void()) {
    c.insert(std::forward<T>(t));
}
} // detail
} // gears

#endif // GEARS_PROGRAM_OPTIONS_DETAILS_HPP