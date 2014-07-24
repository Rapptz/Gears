// The MIT License (MIT)

// Copyright (c) 2012-2014 Danny Y., Rapptz

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

#ifndef GEARS_OPTPAESE_ACTIONS_HPP
#define GEARS_OPTPAESE_ACTIONS_HPP

#include "../string/lexical_cast.hpp"

namespace gears {
namespace optparse {
/**
 * @defgroup optparse_actions Option Actions
 * @ingroup optparse
 * @brief Actions provided by default.
 *
 * @details Actions are callback mechanisms used to "parse" the key
 * value pairs given by the command line options. For example:
 *
 * | Syntax   | Key     | Value |
 * |:--------:|:-------:|:-----:|
 * |`--key=v` | "--key" | "v"   |
 * |`--key v` | "--key" | "v"   |
 * |`-k=v`    | "-k"    | "v"   |
 * | `-k v`   | "-k"    | "v"   |
 * | `-ok=v`  | "-k"    | "v"   |
 * | `-ok=v`  | "-o"    | ""    |
 *
 * The signature of an action must be equivalent to
 * `T(const std::string& key, const std::string& value)`, where:
 *
 * - T is the type of the #typed_value<T>.
 * - key is the key of the key-value pair given by the table above.
 * - value is the value of the key-value pair given by the table above.
 *
 * The action can be a lambda, a function, a functor and any callable object
 * that meets the requirements above.
 */

/**
 * @ingroup optparse_actions
 * @brief The default action used for values.
 * @details The default action used for typed_value. It parses
 * a single string argument to the appropriate type provided.
 *
 * @tparam T The type to convert the value to.
 */
template<typename T>
struct store {
    /**
     * @brief The operator doing the conversion.
     * @details The operator doing the conversion from
     * string to the specified type. A specialisation is provided for
     * `bool` types that parses `"1"` and `"true"` as `true` and `"0"`
     * and `"false"` as `false`.
     *
     * @throws std::runtime_error If boolean conversion failed.
     * @throws std::bad_cast If other conversions failed.
     * @param key The key of the command line option.
     * @param value The value of the command line option.
     * @return The equivalent of doing `gears::string::lexical_cast<T>(value)`.
     */
    T operator()(const std::string&, const std::string& value) const {
        return string::lexical_cast<T>(value);
    }
};

template<>
struct store<bool> {
    bool operator()(const std::string& key, const std::string& value) const {
        if(value == "1" || value == "true") {
            return true;
        }
        else if(value == "0" || value == "false") {
            return false;
        }

        throw std::runtime_error("invalid boolean argument passed to '" + key + '\'');
    }
};


} // optparse
} // gears

#endif // GEARS_OPTPAESE_ACTIONS_HPP
