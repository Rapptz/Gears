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

#ifndef GEARS_OPTPARSE_OPTION_HPP
#define GEARS_OPTPARSE_OPTION_HPP

#include "value.hpp"

namespace gears {
namespace optparse {
/**
 * @ingroup optparse
 * @brief Represents a command line option.
 * @details A class that represents a command line option. A command line
 * option is a command line argument used to specify information to the
 * program.
 *
 */
struct option {
private:
    using value_type = std::unique_ptr<value_base>;
    value_type ptr = nullptr;
public:
    std::string name;   ///< The long name of the option, e.g. "help"
    std::string help;   ///< The description used for the help output
    char alias = '\0';  ///< The short name of the option, e.g. 'h'

    /**
     * @brief Constructs an option from a long name, a description, and a value
     */
    option(std::string name, std::string help = "", value_type value = nullptr):
        ptr(std::move(value)), name(std::move(name)), help(std::move(help)) {}
    /**
     * @brief Constructs an option from a long name, short name, a description, and a value.
     */
    option(std::string name, char alias, std::string help = "", value_type value = nullptr):
        ptr(std::move(value)), name(std::move(name)), help(std::move(help)), alias(alias) {}

    /**
     * @brief Constructs an option from a short name, description and value.
     */
    option(char alias, std::string help = "", value_type value = nullptr):
        ptr(std::move(value)), help(std::move(help)), alias(alias) {}

    /**
     * @brief Checks if the option accepts a value.
     */
    bool takes_value() const noexcept {
        return ptr != nullptr;
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
};
} // optparse
} // gears

#endif // GEARS_OPTPARSE_OPTION_HPP
