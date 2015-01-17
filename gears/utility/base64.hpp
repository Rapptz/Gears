// The MIT License (MIT)

// Copyright (c) 2012-2015 Danny Y., Rapptz

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

#ifndef GEARS_UTILITY_BASE64_HPP
#define GEARS_UTILITY_BASE64_HPP

#include <string>
#include <unordered_map>
#include <cstddef>
#include <exception>

namespace gears {

/**
 * @ingroup utility
 * @brief Exception thrown when input string is invalid base64.
 */
class invalid_base64 : public std::exception {
public:
    invalid_base64() = default;

    /**
     * @brief Returns the description string.
     * @details The description string is "base64 string provided is invalid".
     */
    const char* what() const noexcept override {
        return "base64 string provided is invalid";
    }
};

namespace base64 {
namespace detail {
const signed char npos = -1;
} // detail

/**
 * @ingroup utility
 * @brief Encodes a string to base64.
 * @details Encodes a string to base64. The string to encode is
 * done byte by byte. Padding is done through character `=`. The character
 * for the 62nd index is + and the index for the 63rd index is
 * /. There is no line limit imposed.
 *
 * @param str The string to encode.
 * @return base64 encoded string.
 */
inline std::string encode(const std::string& str) {
    size_t index = 0;
    static auto read = [&index](const std::string& s) -> signed char {
        if(index >= s.length() || s.empty()) {
            return detail::npos;
        }
        signed char result = s[index++] & 0xFF;
        return result;
    };

    static const char lookup[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    std::string result;
    signed char buffer[3]; // 24 bits

    while(true) {
        buffer[0] = read(str);
        if(buffer[0] == detail::npos) {
            break;
        }

        buffer[1] = read(str);
        buffer[2] = read(str);

        result += lookup[buffer[0] >> 2];
        if(buffer[1] != detail::npos) {
            result += lookup[((buffer[0] << 4) & 0x30) | (buffer[1] >> 4)];

            if(buffer[2] != detail::npos) {
                result += lookup[((buffer[1] << 2) & 0x3C) | (buffer[2] >> 6)];
                result += lookup[buffer[2] & 0x3F];
            }
            else {
                result += lookup[(buffer[1] << 2) & 0x3C];
                result += '=';
                break;
            }
        }
        else {
            result += lookup[(buffer[0] << 4) & 0x30];
            result += "==";
            break;
        }
    }

    return result;
}

/**
 * @ingroup utility
 * @brief Decodes a string from base64.
 * @details Decodes a string from base64. If the input
 * string is not in base64 then a `gears::invalid_base64`
 * exception is thrown.
 *
 * @param str The base64 string to decode.
 * @throws gears::invalid_base64 Thrown when the input string is invalid.
 * @return The decoded string
 */
inline std::string decode(const std::string& str) {
    size_t index = 0;

    static std::unordered_map<char,int> lookup = {
        {'A', 0},  {'B', 1},  {'C', 2},  {'D', 3},  {'E', 4},  {'F', 5},  {'G', 6},  {'H', 7}, {'I', 8},
        {'J', 9},  {'K', 10}, {'L', 11}, {'M', 12}, {'N', 13}, {'O', 14}, {'P', 15}, {'Q', 16},
        {'R', 17}, {'S', 18}, {'T', 19}, {'U', 20}, {'V', 21}, {'W', 22}, {'X', 23}, {'Y', 24},
        {'Z', 25}, {'a', 26}, {'b', 27}, {'c', 28}, {'d', 29}, {'e', 30}, {'f', 31}, {'g', 32},
        {'h', 33}, {'i', 34}, {'j', 35}, {'k', 36}, {'l', 37}, {'m', 38}, {'n', 39}, {'o', 40},
        {'p', 41}, {'q', 42}, {'r', 43}, {'s', 44}, {'t', 45}, {'u', 46}, {'v', 47}, {'w', 48},
        {'x', 49}, {'y', 50}, {'z', 51}, {'0', 52}, {'1', 53}, {'2', 54}, {'3', 55}, {'4', 56},
        {'5', 57}, {'6', 58}, {'7', 59}, {'8', 60}, {'9', 61}, {'+', 62}, {'/', 63}
    };

    static auto read = [&](const std::string& st) -> signed char {
        if(st.empty()) {
            return detail::npos;
        }

        while(true) {
            if(index > st.length()) {
                return detail::npos;
            }

            auto next = st[index];
            ++index;
            auto it = lookup.find(next);
            if(it != lookup.end()) {
                return it->second;
            }
        }
    };

    char buffer[4];
    std::string result;
    while(true) {
        buffer[0] = read(str);
        if(buffer[0] == detail::npos) {
            break;
        }

        buffer[1] = read(str);
        if(buffer[1] == detail::npos) {
            break;
        }


        buffer[2] = read(str);
        buffer[3] = read(str);
        result += ((buffer[0] << 2) & 0xFF) | (buffer[1] >> 4);

        if(buffer[2] == detail::npos) {
            break;
        }

        result += ((buffer[1] << 4) & 0xFF) | (buffer[2] >> 2);

        if(buffer[3] == detail::npos) {
            break;
        }

        result += ((buffer[2] << 6) & 0xFF) | buffer[3];
    }

    return result;
}
} // base64
} // gears

#endif // GEARS_UTILITY_BASE64_HPP
