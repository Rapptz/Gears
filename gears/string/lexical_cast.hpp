// The MIT License (MIT)

// Copyright (c) 2012-2014 Rapptz

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

#ifndef GEARS_STRING_LEXICAL_CAST_HPP
#define GEARS_STRING_LEXICAL_CAST_HPP

#include <string>
#include <sstream>
#include <stdexcept>

namespace gears {
namespace string {
/**
 * @ingroup string
 * @brief Converts a string to its integral representation.
 * @details Converts a string to its arithmetic representation.
 * A generic way of handling the standard library's std::sto* functions.
 * If the conversion fails, throws `std::invalid_argument`. If a
 * specialisation isn't picked, the function falls back to using
 * `std::basic_istringstream`. The type to convert to must be
 * `DefaultConstructible`.
 *
 * @param str String to convert from.
 * @tparam T Type to convert to.
 * @throws std::invalid_argument thrown whenever conversion fails.
 * @return The arithmetic representation of the string.
 */
template<typename T>
inline T lexical_cast(const std::string& str) {
    std::istringstream ss(str);
    T result;
    if((ss >> result).fail() || !(ss >> std::ws).eof()) {
        throw std::invalid_argument("lexical_cast failed");
    }
    return result;
}

template<>
inline int lexical_cast<int>(const std::string& str) {
    return std::stoi(str);
}

template<>
inline long lexical_cast<long>(const std::string& str) {
    return std::stol(str);
}

template<>
inline long long lexical_cast<long long>(const std::string& str) {
    return std::stoll(str);
}

template<>
inline float lexical_cast<float>(const std::string& str) {
    return std::stof(str);
}

template<>
inline double lexical_cast<double>(const std::string& str) {
    return std::stod(str);
}

template<>
inline long double lexical_cast<long double>(const std::string& str) {
    return std::stold(str);
}

template<>
inline unsigned long lexical_cast<unsigned long>(const std::string& str) {
    return std::stoul(str);
}

template<>
inline unsigned long long lexical_cast<unsigned long long>(const std::string& str) {
    return std::stoull(str);
}

template<>
inline std::string lexical_cast<std::string>(const std::string& str) {
    return str;
}
} // string
} // gears

#endif // GEARS_STRING_LEXICAL_CAST_HPP
