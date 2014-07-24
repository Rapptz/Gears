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

#ifndef GEARS_OPTPARSE_ERROR_HPP
#define GEARS_OPTPARSE_ERROR_HPP

#include <string>
#include <stdexcept>

namespace gears {
namespace optparse {
/**
 * @defgroup optparse_errors Option Parsing Errors
 * @ingroup optparse
 * @brief Exceptions thrown by the optparse module.
 */

/**
 * @ingroup optparse_errors
 * @brief The base exception thrown in case of errors.
 */
class error : public std::runtime_error {
public:
    /**
     * @brief Constructs an exception.
     * @details Constructs an exception with the string
     * `"{name}: error: {str}"`. This is usually not thrown
     * directly, but rather by its inherited exception objects.
     *
     * @param name The name of the program.
     * @param str The error string.
     */
    error(const std::string& name, const std::string& str): std::runtime_error(name + ": error: " + str) {}
};

/**
 * @ingroup optparse_errors
 * @brief Exception thrown when an invalid option is passed.
 */
class unrecognised_option : public error {
public:
    /**
     * @brief Constructs an exception.
     * @details Constructs an exception with the string
     * <code>"{name}: error: unrecognised option '{op}'"</code>.
     *
     * @param name The name of the program.
     * @param op The option passed.
     */
    unrecognised_option(const std::string& name, const std::string& op):
    error(name, "unrecognised option '" + op + '\'') {}
};

/**
 * @ingroup optparse_errors
 * @brief Exception thrown when a required option is missing.
 */
class missing_required_option : public error {
public:
    /**
     * @brief Constructs an exception.
     * @details Constructs an exception with the string
     * <code>"{name}: error: missing required option '{op}'"</code>.
     *
     * @param name The name of the program.
     * @param op The option passed.
     */
    missing_required_option(const std::string& name, const std::string& op):
    error(name, "missing required option '" + op + '\'') {}
};

/**
 * @ingroup optparse_errors
 * @brief Exception thrown when a required value is missing.
 */
class missing_required_value : public error {
public:
    /**
     * @brief Constructs an exception.
     * @details Constructs an exception. The string
     * printed depends on the number of arguments expected.
     * If only `nargs` is equal to 1, then the error string is:
     * <code>"{name}: error: option '{op}' requires an argument"</code>. Otherwise
     * the error string is
     * <code>"{name}: error: option '{op}' requires {narg} arguments"</code>
     *
     * @param name The name of the program.
     * @param op The option passed.
     * @param nargs The number of arguments expected.
     */
    missing_required_value(const std::string& name, const std::string& op, size_t nargs):
    error(name, nargs == 1 ?
                "option '" + op + "' requires an argument" :
                "option '" + op + "' requires " + std::to_string(nargs) + " arguments") {}
};

/**
 * @ingroup optparse_errors
 * @brief Exception thrown when an option is given an explicit value when not needed.
 */
class option_takes_no_value : public error {
public:
    /**
     * @brief Constructs an exception.
     * @details Constructs an exception with the string
     * <code>"{name}: error: option '{op}' does not take a value"</code>.
     *
     * @param name The name of the program.
     * @param op The option passed.
     */
    option_takes_no_value(const std::string& name, const std::string& op):
    error(name, "option '" + op + "' does not take a value") {}
};
} // optparse
} // gears

#endif // GEARS_OPTPARSE_ERROR_HPP
