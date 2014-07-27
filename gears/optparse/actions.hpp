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
#include <functional>
#include <iterator>

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

/**
 * @ingroup optparse_actions
 * @brief An action used to store constant values.
 * @details An action used to store constant values. The type
 * provided must be copyable. When an option value is parsed,
 * the value provided is *always* returned. Usually used in
 * conjunction with the optparse::constant factory function.
 *
 * @tparam T The type of contant to store.
 */
template<typename T>
struct store_const {
private:
    T value;
public:
    /**
     * @brief Constructs with the value provided.
     */
    store_const(T val): value(std::move(val)) {}

    /**
     * @brief The operator doing the heavy lifting.
     * @details The operator doing the heavy lifting. The value
     * provided in the constructor is the one that is always returned
     * regardless of the key or value matched.
     *
     * @return The internal value held.
     */
    T operator()(const std::string&, const std::string&) const {
        return value;
    }
};

/**
 * @ingroup optparse_actions
 * @brief An action used to parse a list of values.
 * @details An action used to parse a list of values. The
 * parsing is done through continuous concatenation of the
 * values parsed with the action. By default, the action used
 * to parse and retrieve the values is optparse::store.
 *
 * @tparam Container The internal container to hold the list on.
 * @tparam Action The action used to parse the values. Defaults to store.
 */
template<typename Container, typename Action = store<typename Container::value_type>>
struct store_list {
    static_assert(std::is_convertible<decltype(std::declval<Action>()("","")), typename Container::value_type>::value,
                  "The action must return a type convertible to the container's value type");
private:
    Action action;
public:
    /**
     * @brief Constructs a store_list from an action.
     */
    store_list(Action action): action(std::move(action)) {}
    /**
     * @brief The operator that does the heavy lifting.
     * @details The operator that does the heavy lifting. The values
     * are retrieved as if splitting by the newline character, `'\n'`.
     * They are inserted into the container as if using
     * `c.insert(c.back(), action(key, split_value))`
     *
     * @param key The key of the command line option.
     * @param value The value of the command line option, delimited by newlines.
     * @return The container with the parsed values.
     */
    Container operator()(const std::string& key, const std::string& value) const {
        Container result;
        std::istringstream ss(value);
        std::insert_iterator<Container> it(result, result.end());
        for(std::string str; std::getline(ss, str); ) {
            *it = action(key, str);
        }
        return result;
    }
};


/**
 * @ingroup argparse_actions
 * @brief An action used to store a list.
 * @details An action used to store a list. Every time the argument
 * is called, it is parsed to the specific type using the action
 * provided. This should not be used directly, instead it is used
 * in conjunction with optparse::compose factory function.
 *
 * @tparam Container The internal container to hold the list on.
 */
template<typename Container>
struct append {
private:
    using value_type = typename Container::value_type;
    std::function<value_type(const std::string&, const std::string&)> action;
    Container cont;
public:
    template<typename Action>
    append(Action action): action(std::move(action)) {}

    /**
     * @brief The operator doing the heavy lifting.
     * @details The operator doing the heavy lifting. The
     * arguments are delegated to the action provided. The result
     * of the parsing is added to a list keeping track of the elements.
     * The result is inserted to the container by calling
     * `c.insert(c.end(), action(key, value))`. The container
     * is returned and move semantics take over from then.
     *
     * @param key The key of the command line argument.
     * @param value The value of the command line option.
     * @return The container in its current state.
     */
    Container operator()(const std::string& key, const std::string& value) {
        cont.insert(cont.end(), action(key, value));
        return cont;
    }
};
} // optparse
} // gears

#endif // GEARS_OPTPAESE_ACTIONS_HPP
