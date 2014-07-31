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

#ifndef GEARS_OPTPARSE_HPP
#define GEARS_OPTPARSE_HPP

#include "optparse/option_parser.hpp"

/**
 * @defgroup optparse Option parsing module
 * @brief Provides a method of parsing command line arguments.
 *
 * @details This module is a way to parse command line arguments using
 * conventional POSIX/Unix standards. It is a more convenient and flexible
 * way of parsing command line options compared to rolling your own by hand.
 * This module has built-in support for subcommands so you could make your own
 * git-like programs with e.g. `git commit` and `git add`. This module is mainly
 * inspired by Python's `optparse` library and Boost.ProgramOptions. A more
 * in-depth tutorial can be found @ref optparse_tut "here".
 *
 * # Simple Example
 *
 * The following example takes a list of integers and multiplies, adds,
 * or finds the maximum between them.
 *
 * @code
 * #include <gears/optparse.hpp>
 * #include <numeric>
 *
 * namespace opt = gears::optparse;
 *
 * int main(int argc, char** argv) {
 *     opt::option_parser parser = {
 *         { "sum", "calculates the sum of the digits" },
 *         { "product", 'p', "calculates the product of the digits" },
 *         { "max", "calculates the maximum digit (default)" }
 *     };
 *     parser.description = "Calculates the maximum, sum, or product of integers";
 *     auto&& args = parser.parse(argv, argv + argc);
 *     if(args.positional.empty()) {
 *         parser.error("no input digits given");
 *     }
 *
 *     auto&& sum = [](int total, const std::string& str) { return total + std::stoi(str); };
 *     auto&& prod = [](int total, const std::string& str) { return total * std::stoi(str); };
 *     auto&& max = [](const std::string& lhs, const std::string& rhs) {
 *         return std::stoi(lhs) < std::stoi(rhs);
 *     };
 *
 *     auto&& begin = args.positional.begin();
 *     auto&& end = args.positional.end();
 *
 *     if(args.options.is_active("sum")) {
 *         std::cout << std::accumulate(begin, end, 0, sum) << '\n';
 *     }
 *     else if(args.options.is_active("product")) {
 *         std::cout << std::accumulate(begin, end, 1, prod) << '\n';
 *     }
 *     else {
 *         std::cout << *std::max_element(begin, end, max) << '\n';
 *     }
 * }
 * @endcode
 *
 * Assuming that the following code is stored under `dev.cpp` and executed under Linux, then you'd
 * get the following nicely formatted help message:
 *
 * @cmd
 * $ ./dev --help
 * usage: ./dev [options...]
 *
 * Calculates the maximum, sum, or product of integers
 *
 * options:
 *     -h, --help        shows this message and exits
 *         --sum         calculates the sum of the digits
 *     -p, --product     calculates the product of the digits
 *         --max         calculates the maximum digit (default)
 * @endcmd
 *
 * When the appropriate arguments are passed, you get the sum, product, or maximum
 * of the elements.
 *
 * <pre>
 * $ ./dev --sum 10 19 20 11
 * 60
 * $ ./dev -p 10 19 20 11
 * 41800
 * $ ./dev 10 19 20 11
 * 20
 * </pre>
 *
 * If an error is spotted then the program prints the error
 * and elegantly exits like so:
 *
 * <pre>
 * $ ./dev
 * usage: ./dev [options...]
 * ./dev: error: no input digits given
 * $ ./dev --other
 * usage: ./dev [options...]
 * ./dev: error: unrecognised option '--other'
 * </pre>
 *
 */

#endif // GEARS_OPTPARSE_HPP
