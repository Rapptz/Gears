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

#ifndef GEARS_COMMAND_LINE_DETAILS_HPP
#define GEARS_COMMAND_LINE_DETAILS_HPP

#include <typeinfo>
#include <sstream>
#include <utility>

namespace gears {
namespace command_line {
namespace detail {
struct bad_lexical_cast : std::bad_cast {
    virtual const char* what() const noexcept {
        return "bad_lexical_cast";
    }
};

struct invalid_arg_get : std::exception {
private:
    std::string str;
public:
    invalid_arg_get(const std::string& str): str("error: " + str + " is not a value or valid argument") {}

    virtual const char* what() const noexcept {
        return str.c_str();
    }
};

struct missing_required_arg : std::exception {
private:
    std::string str;
public:
    using string_type = const std::string&;
    missing_required_arg(string_type prog, string_type str): str(prog + ": error: missing required argument: " + str) {}

    virtual const char* what() const noexcept {
        return str.c_str();
    }
};

struct unrecognised_arg : std::exception {
private:
    std::string str;
public:
    using string_type = const std::string&;
    unrecognised_arg(string_type prog, string_type str): str(prog + ": error: unrecognised argument: " + str) {}

    virtual const char* what() const noexcept {
        return str.c_str();
    }
};

template<typename T>
inline T lexical_cast(const std::string& str) {
    std::stringstream ss(str);
    T result;
    if((ss >> result).fail() || !(ss >> std::ws).eof())
        throw bad_lexical_cast();
    return result;
}

template<>
inline std::string lexical_cast<std::string>(const std::string& str) {
    return str;
}

template<typename Cont, typename T>
inline auto insert_impl(Cont& c, T&& t) -> decltype(c.push_back(std::forward<T>(t)), void()) {
    c.push_back(std::forward<T>(t));
}

template<typename Cont, typename T>
inline auto insert_impl(Cont& c, T&& t) -> decltype(c.insert(std::forward<T>(t)), void()) {
    c.insert(std::forward<T>(t));
}
} // detail
} // command_line
} // gears

#endif // GEARS_COMMAND_LINE_DETAILS_HPP