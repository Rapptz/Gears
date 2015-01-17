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

#ifndef GEARS_OPTPARSE_OPTION_HPP
#define GEARS_OPTPARSE_OPTION_HPP

#include <gears/optparse/value.hpp>
#include <gears/enums/operators.hpp>

using namespace gears::enums::operators;

namespace gears {
namespace optparse {
/**
 * @relates option
 * @brief List of traits that modify an option's behaviour.
 * @details List of traits that modify an option's behaviour.
 * This allows you to set whether an option should be required
 * or hidden. These are bit flags so they should be used similar
 * to any other type of bit flag such as, e.g., `std::ios_base`.
 */
enum class trait : char {
    none     = 0,        ///< Represents no traits being set.
    required = 1 << 0,   ///< The option is required to appear, or an error is thrown.
    hidden   = 1 << 1    ///< The option is suppressed from the default --help output.
};

/**
 * @ingroup optparse
 * @brief Represents a command line option.
 * @details A class that represents a command line option. A command line
 * option is a command line argument used to specify information to the
 * program.
 */
struct option {
private:
    using value_type = std::unique_ptr<value_base>;
    value_type ptr;
    friend struct option_parser;
public:
    std::string name;   ///< The long name of the option, e.g. "help"
    std::string help;   ///< The description used for the help output
    trait flags;       ///< The trait flags to modify the option's behaviour
    char alias = '\0';  ///< The short name of the option, e.g. 'h'

    /**
     * @brief Constructs an option from a long name, a description, a value, and trait.
     */
    option(std::string name, std::string help = "", value_type value = constant(true), trait flags = trait::none):
        ptr(std::move(value)), name(std::move(name)), help(std::move(help)), flags(std::move(flags)) {}
    /**
     * @brief Constructs an option from a long name, short name, a description, a value, and trait.
     */
    option(std::string name, char alias, std::string help = "", value_type value = constant(true), trait flags = trait::none):
        ptr(std::move(value)), name(std::move(name)), help(std::move(help)), flags(std::move(flags)), alias(alias) {}

    /**
     * @brief Constructs an option from a short name, description, a value, and traits.
     */
    option(char alias, std::string help = "", value_type value = constant(true), trait flags = trait::none):
        ptr(std::move(value)), help(std::move(help)), flags(std::move(flags)), alias(alias) {}

    /**
     * @brief Copy constructor
     */
    option(const option& other):
        ptr(other.ptr == nullptr ? nullptr : other.ptr->clone()),
        name(other.name), help(other.help), flags(other.flags), alias(other.alias) {}

    /**
     * @brief Copy assignment
     */
    option& operator=(const option& other) {
        ptr = other.ptr == nullptr ? nullptr : other.ptr->clone();
        name = other.name;
        help = other.help;
        flags = other.flags;
        alias = other.alias;
        return *this;
    }

    /**
     * @brief Move constructor
     */
    option(option&&) = default;

    /**
     * @brief Move assignment
     */
    option& operator=(option&&) = default;

    /**
     * @brief Destructor
     */
    ~option() = default;

    /**
     * @brief Checks if the option accepts a value.
     */
    bool takes_value() const noexcept {
        return ptr != nullptr && ptr->nargs > 0;
    }

    /**
     * @brief Returns the number of arguments expected by the value.
     * @return Returns the number of arguments expected by the value.
     * If no value is expected, i.e. #takes_value is false, then 0 is
     * returned.
     */
    size_t nargs() const noexcept {
        return takes_value() ? ptr->nargs : 0;
    }

    //@{
    /**
     * @brief Checks if the option is represented by a long or short option.
     * @details Checks if the option is represented by a long or short option.
     * This function is typically used to avoid code repetition when handling
     * predicates dealing with checking for a long name or short name. This
     * is a member function rather than an `operator==` or `operator!=` to
     * disallow obfuscation and code duplication (e.g. `"help" == op` vs `op == "help"`).
     *
     * Example usage:
     *
     * @code
     * optparse::option x = { "help", 'h', "show message" };
     * x.is("help");    // true
     * x.is('h');       // true
     * x.is("stuff");   // false
     * @endcode
     *
     * @param arg Long or short option to check for.
     * @return `true` if the option can be represented by arg.
     */
    bool is(char arg) const noexcept {
        return alias == arg;
    }

    bool is(const std::string& arg) const noexcept {
        return name == arg;
    }
    //@}

    /**
     * @brief Retrieves the internal value of the option.
     * @details Retrieves the internal value of the option.
     * If the option has no value then an exception is thrown.
     *
     * @throws std::runtime_error Thrown if the option has not been parsed.
     * @throws std::invalid_argument Thrown for invalid casting or if the option has no value.
     * @return The internal value.
     */
    template<typename T>
    const T& get() const {
        if(ptr == nullptr) {
            throw std::invalid_argument("option does not take value");
        }
        auto val = dynamic_cast<typed_value<T>*>(ptr.get());

        if(val == nullptr) {
            throw std::invalid_argument("invalid cast for option");
        }
        return val->get();
    }

    /**
     * @brief Retrieves the internal value of the option or a reasonable default.
     * @details Retrieves the internal value of the option or a reasonable default.
     * If the option has no value then the default is returned. If the type is not
     * a valid cast then the default is returned.
     *
     * @return The internal value or a reasonable default.
     */
    template<typename T>
    const T& get_or(const typename std::remove_reference<T>::type& def) const noexcept {
        if(ptr == nullptr) {
            return def;
        }

        auto val = dynamic_cast<typed_value<T>*>(ptr.get());
        return val == nullptr ? def : val->get_or(def);
    }

    /**
     * @brief Checks if the option has gone through parsing.
     */
    bool is_active() const noexcept {
        return ptr != nullptr && ptr->is_active();
    }

    /**
     * @brief Retrieves the internal option's metavar member.
     * @details Retrieves the internal value's metavar member. If
     * #takes_value returns false, then an empty string is returned.
     * @return The internal value's metavar member.
     */
    std::string metavar() const noexcept {
        return takes_value() ? ptr->metavar : "";
    }
};
} // optparse
} // gears

#endif // GEARS_OPTPARSE_OPTION_HPP
