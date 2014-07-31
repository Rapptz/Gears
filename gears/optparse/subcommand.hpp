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

#ifndef GEARS_OPTPARSE_SUBCOMMAND_HPP
#define GEARS_OPTPARSE_SUBCOMMAND_HPP

#include "option_set.hpp"

namespace gears {
namespace optparse {
/**
 * @ingroup optparse
 * @brief Represents a command line subcommand.
 * @details A subcommand is typically the first
 * argument provided in the command line. Examples include
 * things like `svn checkout`, `git commit`, `git add`, and more.
 */
struct subcommand {
    std::string name;                   ///< The name of the subcommand.
    std::string description;            ///< A brief paragraph giving an overview of the subcommand
    std::string help;                   ///< A sentence explaining the subcommand. Shown in the help message
    std::string usage = "[options..]";  ///< The usage message for the subcommand
    std::string epilogue;               ///< A paragraph usually printed after the help message
    option_set options;                 ///< The options the subcommand contains.

    /**
     * @brief Default constructor
     */
    subcommand() = default;

    /**
     * @brief Constructs from a name.
     */
    subcommand(std::string name): name(std::move(name)) {}

    /**
     * @brief Constructs from a name and a list of options.
     */
    subcommand(std::string name, std::initializer_list<option> options): name(std::move(name)), options(std::move(options)) {}

    /**
     * @brief Constructs from a name, a help message and a list of options.
     */
    subcommand(std::string name, std::string help, std::initializer_list<option> options):
        name(std::move(name)), help(std::move(help)), options(std::move(options)) {}

    /**
     * @brief Constructs from a name, a help message and an option set.
     */
    subcommand(std::string name, std::string help, option_set options):
        name(std::move(name)), help(std::move(help)), options(std::move(options)) {}


    /**
     * @brief Constructs from a name and an option set.
     */
    subcommand(std::string name, option_set options): name(std::move(name)), options(std::move(options)) {}
};

/**
 * @ingroup optparse
 * @brief Represents the parsed results of option_parser.
 * @details Represents the parsed results of option_parser. These
 * include the current active option set, the name of the subcommand
 * that is active (or an empty string if not active) and a list of
 * positional arguments that are left over.
 */
struct arguments {
    const option_set& options;              ///< The current option_set
    std::vector<std::string> positional;    ///< The positional arguments
    std::string subcommand;                 ///< The active subcommand name
};
} // optparse
} // gears

#endif // GEARS_OPTPARSE_SUBCOMMAND_HPP
