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

#ifndef GEARS_OPTPARSE_VALUE_HPP
#define GEARS_OPTPARSE_VALUE_HPP

#include "actions.hpp"
#include "../utility/helpers.hpp"

namespace gears {
namespace optparse {
struct value_base {
    std::string metavar;     ///< The value name to use in help messages
    size_t nargs = 1;        ///< Number of arguments to expect.
    bool required = false;

    virtual ~value_base() = default;
    virtual void parse(const std::string&, const std::string&) = 0;
    virtual bool is_active() const noexcept = 0;
    virtual std::unique_ptr<value_base> clone() const = 0;
};

/**
 * @ingroup optparse
 * @brief Represents a command line value.
 * @details A class that represents a command line value to be
 * used with command line options that expect one or more arguments
 * to be given. This class is usually not used explicitly as many factory
 * functions are provided for common use cases.
 *
 * @tparam T The type of argument expected.
 */
template<typename T>
struct typed_value : public value_base {
private:
    T* reference = nullptr;
    std::unique_ptr<T> value;
    std::function<T(const std::string&, const std::string&)> action_;
    bool active = false;

    void parse(const std::string& key, const std::string& val) override {
        auto&& result = action_(key, val);
        if(reference != nullptr) {
            *reference = result;
            active = true;
        }
        else {
            value.reset(new T(result));
            active = true;
        }
    }

    std::unique_ptr<value_base> clone() const override {
        auto&& ptr = utility::make_unique<typed_value<T>>();
        ptr->reference = reference;
        ptr->active = active;
        ptr->action_ = action_;
        ptr->nargs = nargs;
        ptr->metavar = metavar;
        ptr->required = required;
        return std::unique_ptr<value_base>{std::move(ptr)};
    }
public:
    /**
     * @brief Default constructor.
     */
    typed_value(): action_(store<T>{}) {}
    /**
     * @brief Constructs a typed_value storing its result to a variable.
     * @details Constructs a typed_value with an l-value variable. This
     * allows you to bind the result of the parsed result to a C++ variable
     * easily.
     *
     * @param object The object to bind the result of parsing to.
     */
    typed_value(T& object): reference(&object) {}

    /**
     * @brief Checks if the typed_value has gone through parsing.
     * @details Checks if the typed_value has gone through parsing successfully.
     * If the parsing threw then this returns false.
     * @return `true` if parsing was successful, `false` otherwise.
     */
    bool is_active() const noexcept override {
        return active;
    }

    /**
     * @brief Specifies the action callback to use for parsing.
     * @details Specifies the action callback to use for parsing. All parsing
     * of values is done through a callback mechanism called actions. The signature
     * of an action must be `T(const std::string&, const std::string&)`. Many actions
     * are provided with a reasonable default, this should only be called if you have
     * created a custom action. The first argument passed is the key of the command line
     * option, and the second one is the value. For example, passing `--foo=test` on the command
     * line would result in the first argument being `--foo` and the second being `test`.
     *
     * @param action The action callback to use.
     * @return A reference to the typed_value object.
     */
    template<typename Action>
    typed_value& action(Action&& action) {
        action_ = std::forward<Action>(action);
        return *this;
    }

    /**
     * @brief Retrieves the parsed value.
     * @details Retrieves the parsed value. If the
     * typed_value object hasn't gone through parsing yet
     * then this function throws.
     *
     * @throws std::runtime_error Thrown when #is_active is false.
     * @return The parsed value.
     */
    const T& get() const {
        if(!active) {
            throw std::runtime_error("value has not been parsed");
        }

        if(reference != nullptr) {
            return *reference;
        }
        return *value;
    }

    /**
     * @brief Retrieves the parsed value or a reasonable default.
     * @details Retrieves the parsed value or a reasonable default
     * if the value hasn't gone through parsing.
     *
     * @param def The default value if #is_active is false.
     * @return The parsed value or `def`.
     */
    const T& get_or(const T& def) const noexcept {
        if(is_active()) {
            if(reference != nullptr) {
                return *reference;
            }
            return *value;
        }
        return def;
    }
};

/**
 * @ingroup optparse
 * @brief Returns a typed_value that binds the result to a variable.
 * @details Returns a typed_value that when parsed, binds the result
 * to an l-value variable. For example, having an option being
 * declared like so:
 *
 * @code
 * int x;
 * opt::option test = { "test", 't', "tests something", opt::bind_to(x) };
 * @endcode
 *
 * When the command line is parsed with `10` as a value, e.g. `--test=10`
 * then the variable x will contain the value `10`.
 *
 * @param t The variable to bind the result to.
 * @param action The action to use for parsing the value. Defaults to optparse::store.
 * @return A polymorphic `typed_value` to use with optparse::option.
 */
template<typename T, typename Action = store<T>>
inline std::unique_ptr<value_base> bind_to(T& t, Action action = Action{}) {
    auto&& ptr = utility::make_unique<typed_value<T>>(t);
    ptr->action(std::move(action));
    return std::unique_ptr<value_base>{std::move(ptr)};
}

/**
 * @ingroup optparse
 * @brief Returns a typed_value that returns a constant value.
 * @details Returns a typed_value that returns a constant value.
 * This is a wrapper around creating a typed_value and setting the
 * action to optparse::store_const. Note that if this is used, then the
 * option object technically takes no value. So having, for example,
 * `--stuff=val` in the command line throws an error.
 *
 * @param t The constant value to return when the option is active.
 * @return A polymorphic `typed_value` to use with optparse::option.
 */
template<typename T>
inline std::unique_ptr<value_base> constant(const T& t) {
    auto&& ptr = utility::make_unique<typed_value<T>>();
    ptr->action(store_const<T>{t});
    ptr->nargs = 0;
    return std::unique_ptr<value_base>{std::move(ptr)};
}

/**
 * @brief Returns a regular typed_value.
 * @details Returns a regular typed_value. If a command line
 * value is required for your interface, this is the recommended
 * way of creating values.
 *
 * @param action The action used to parse values. If not provided, defaults to optparse::store.
 * @return A polymorphic `typed_value` to use with optparse::option.
 */
template<typename T, typename Action = store<T>>
inline std::unique_ptr<value_base> value(Action action = Action{}) {
    auto&& ptr = utility::make_unique<typed_value<T>>();
    ptr->action(std::move(action));
    return std::unique_ptr<value_base>{std::move(ptr)};
}
} // optparse
} // gears

#endif // GEARS_OPTPARSE_VALUE_HPP
