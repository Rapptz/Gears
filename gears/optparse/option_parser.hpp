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

#ifndef GEARS_OPTPARSE_OPTION_PARSER_HPP
#define GEARS_OPTPARSE_OPTION_PARSER_HPP

#include "error.hpp"
#include "formatter.hpp"
#include <iostream>
#include <cstdlib>

namespace gears {
namespace optparse {
/**
 * @ingroup optparse
 * @brief Handles command line parsing.
 * @details This class is mainly used for handling the
 * command line parsing of the command line arguments. It is also
 * used for registering subcommands, errors, and other general program
 * utilities.
 */
struct option_parser {
private:
    std::vector<subcommand> subcommands;
    option_set options;
    std::unique_ptr<formatter> format = utility::make_unique<formatter>();
    option_set* active_options = &options;
    std::ptrdiff_t active_subcommand_index = -1;

    bool is_option(const std::string& arg) const noexcept {
        return arg.size() >= 2 && arg.front() == '-';
    }

    template<typename ForwardIt>
    ForwardIt process_subcommand(ForwardIt begin, ForwardIt end) {
        if(begin == end) {
            return begin;
        }

        std::string arg = *begin;
        if(arg.empty()) {
            return begin;
        }

        auto&& it = std::find_if(subcommands.begin(), subcommands.end(), [&arg](const subcommand& sub) {
            return sub.name == arg;
        });

        if(it != subcommands.end()) {
            active_subcommand_index = std::distance(subcommands.begin(), it);
            active_options = &(it->options);
            ++begin;
            return begin;
        }

        if(!is_option(arg)) {
            throw error(program_name, arg + " is not a valid subcommand", arg);
        }

        return begin;
    }

    template<typename ForwardIt>
    ForwardIt parse_long_option(std::string key, ForwardIt begin, ForwardIt end) {
        std::string value;
        auto&& pos = key.find('=');
        bool has_explicit_value = false;

        // check if it's --long=arg
        if(pos != std::string::npos) {
            value = key.substr(pos + 1);
            key = key.substr(0, pos);
            has_explicit_value = true;
        }

        // check if the argument exists
        auto&& it = std::find_if(active_options->begin(), active_options->end(), [&key](const option& opt) {
            return opt.is(key.substr(2));
        });

        if(it == active_options->end()) {
            throw unrecognised_option(program_name, key);
        }

        auto&& opt = *it;
        size_t argc = std::distance(begin, end);

        // option doesn't take a value but it was explicitly provided
        // so throw an error
        if(!opt.takes_value() && has_explicit_value) {
            throw option_takes_no_value(program_name, key);
        }

        if(opt.takes_value() && !has_explicit_value) {
            // check number of arguments left
            if(argc - 1 < opt.nargs()) {
                throw missing_required_value(program_name, key, opt.nargs());
            }

            // get the arguments needed
            for(size_t i = 0; i < opt.nargs(); ++i) {
                value += *(++begin);
                value.push_back('\n');
            }

            // remove extraneous newline
            if(!value.empty() && value.back() == '\n') {
                value.pop_back();
            }
        }

        // parse it
        if(opt.ptr != nullptr) {
            opt.ptr->parse(key, value);
        }

        return begin;
    }

    template<typename ForwardIt>
    ForwardIt parse_short_option(const std::string& arg, ForwardIt begin, ForwardIt end) {
        std::string value;
        // loop due to concatenation of short options
        for(size_t j = 1 ; j < arg.size(); ++j) {
            auto&& ch = arg[j];
            bool has_explicit_value = false;
            std::string key = "-";
            key.push_back(ch);

            // check for -o=stuff
            if(j + 2 < arg.size() && arg[j + 1] == '=') {
                value = arg.substr(j + 2);
                // set loop counter to end explicitly after
                // this loop
                j = arg.size();
                has_explicit_value = true;
            }

            auto&& it = std::find_if(active_options->begin(), active_options->end(), [&ch](const option& opt) {
                return opt.is(ch);
            });

            if(it == active_options->end()) {
                throw unrecognised_option(program_name, key);
            }

            auto&& opt = *it;
            size_t argc = std::distance(begin, end);

            if(has_explicit_value && !opt.takes_value()) {
                throw option_takes_no_value(program_name, key);
            }

            // check for -o stuff
            if(opt.takes_value() && !has_explicit_value) {
                // note that -ostuff doesn't work due to ambiguity.
                if(j + 1 != arg.size()) {
                    throw error(program_name, "short option \'" + key + "\' and value must not be combined", arg);
                }

                if(argc - 1 < opt.nargs()) {
                    throw missing_required_value(program_name, key, opt.nargs());
                }

                for(size_t i = 0; i < opt.nargs(); ++i) {
                    value += *(++begin);
                    value.push_back('\n');
                }

                // remove extraneous newline
                if(!value.empty() && value.back() == '\n') {
                    value.pop_back();
                }
            }

            if(opt.ptr != nullptr) {
                opt.ptr->parse(key, value);
            }
        }

        return begin;
    }

    template<typename It>
    arguments make_args(It begin, It end) const {
        if(active_subcommand_index == -1) {
            return { *active_options, std::vector<std::string>(begin, end), "" };
        }
        auto&& sub = subcommands[active_subcommand_index];
        return { *active_options, std::vector<std::string>(begin, end), sub.name };
    }
public:
    std::string description;              ///< A brief paragraph giving an overview of the program
    std::string epilogue;                 ///< A paragraph printed after the help message
    std::string program_name;             ///< The program name, if not provided it's argv[0]
    std::string usage = "[options...]";   ///< The usage string

    /**
     * @brief Default constructor
     */
    option_parser() = default;

    /**
     * @brief Constructs an option_parser from an option_set
     */
    option_parser(option_set options): options(std::move(options)) {}

    /**
     * @brief Adds an option to the option_parser.
     * @details Adds an option to the option_parser. This
     * function is equivalent to the option_set::add function. The
     * option is added to the list of options when no subcommand is
     * specified.
     *
     * @param args The arguments to pass to option_set::add.
     * @return The return value of option_set::add.
     */
    #ifndef GEARS_FOR_DOXYGEN_ONLY
    template<typename... Args>
    auto add(Args&&... args) -> decltype(options.add(std::forward<Args>(args)...)) {
        return options.add(std::forward<Args>(args)...);
    }
    #else
    template<typename... Args>
    auto add(Args&&... args);
    #endif // GEARS_FOR_DOXYGEN_ONLY

    /**
     * @brief Registers a subcommand for parsing.
     * @details Registers a subcommand for parsing.
     *
     * @param sub The subcommand to register.
     * @return A reference to the option_parser.
     */
    option_parser& add_subcommand(subcommand sub) {
        subcommands.push_back(std::move(sub));
        return *this;
    }

    /**
     * @brief Sets the help formatter of the parser.
     * @details Sets the help formatter of the parser.
     * The formatter must inherit from optparse::formatter.
     *
     * @param form The formatter to use.
     */
    void help_formatter(const formatter& form) {
        format = utility::make_unique<formatter>(form.column);
    }

    /**
     * @brief Parses command line arguments without handling errors.
     * @details Parses command line arguments without handling errors.
     * Exceptions derived by optparse::error are thrown when an error is
     * spotted and all parsing stops. The following assumptions are made:
     *
     * - The first element is the program name.
     * - The second element is the subcommand if available. Skipped if unavailable.
     * - Dereferencing the iterators is implicitly convertible to `std::string`.
     *
     * Along with not checking for errors, this function does not check if
     * required arguments are present. This function should only be used if
     * you want to provide your own error handling mechanism.
     *
     * @param begin A ForwardIterator pointing to the first element to parse.
     * @param end A ForwardIterator pointing to one past the last element to parse.
     * @return An optparse::arguments object storing the result.
     */
    template<typename ForwardIt>
    arguments raw_parse(ForwardIt begin, ForwardIt end) {
        static_assert(std::is_constructible<std::string, decltype(*begin)>{},
                      "Iterator must return type convertible to std::string");

        if(begin == end) {
            return {*active_options, {}, ""};
        }

        // assign program name to argv[0] if it isn't provided
        if(program_name.empty()) {
            program_name = *begin++;
        }
        else {
            ++begin;
        }

        // check if argv[1] is a subcommand
        begin = process_subcommand(begin, end);

        // begin parsing command line arguments
        for(; begin != end; ++begin) {
            std::string arg = *begin;

            // -- is used to delimit options vs positional arguments
            if(arg == "--") {
                return make_args(++begin, end);
            }

            // check if it's an option
            if(is_option(arg)) {
                // check for long, i.e. --long
                if(arg[1] == '-') {
                    begin = parse_long_option(arg, begin, end);
                }
                else {
                    // short option, i.e. -s
                    begin = parse_short_option(arg, begin, end);
                }
            }
            else {
                // since it isn't an option, then the positional
                // arguments have begun so just stop parsing.
                break;
            }
        }

        return make_args(begin, end);
    }

    /**
     * @brief Parses the command line arguments while handling errors.
     * @details Parses the command line arguments while handling errors. All
     * exceptions are thrown and sent to the error stream provided. If the help
     * command line option is active, then the help message is sent to the output
     * stream provided. Required arguments are checked and the thrown exceptions are
     * also caught and output to the error stream. The assumptions of the arguments
     * are the same as the ones provided by #raw_parse. If exceptions are caught
     * then the program exits as if calling `std::exit(EXIT_FAILURE)`. If the help
     * message is active while no errors are spotted, then the program exits as if
     * calling `std::exit(EXIT_SUCCESS)`. The help message is output as if calling
     * #format_help.
     *
     * @param begin A ForwardIterator pointing to the first element to parse.
     * @param end A ForwardIterator pointing to one past the last element to parse.
     * @param out The output stream to output the help message to.
     * @param err The error stream to output the errors to.
     * @return An optparse::argument object storing the result.
     */
    template<typename ForwardIt>
    arguments parse(ForwardIt begin, ForwardIt end, std::ostream& out = std::cout, std::ostream& err = std::cerr) {
        try {
            auto&& args = raw_parse(begin, end);

            if(args.options.is_active("help")) {
                out << format_help();
                std::exit(EXIT_SUCCESS);
            }

            return args;
        }
        catch(const std::exception& e) {
            err << format_usage() << '\n' << e.what() << '\n';
            if(active_options->is_active("help")) {
                out << format_description()
                    << format_subcommands()
                    << format_options()
                    << format_epilogue();
            }

            std::exit(EXIT_FAILURE);
        }
    }

    /**
     * @brief Returns the formatted description message.
     * @details Returns the formatted description message. This delegates
     * the work to the optparse::formatter currently active.
     * @return The formatted message.
     */
    std::string format_description() const noexcept {
        return format->description(description);
    }

    /**
     * @brief Returns the formatted epilogue message.
     * @details Returns the formatted epilogue message. This delegates
     * the work to the optparse::formatter currently active.
     * @return The formatted message.
     */
    std::string format_epilogue() const noexcept {
        return format->epilogue(epilogue);
    }

    /**
     * @brief Returns the formatted usage message.
     * @details Returns the formatted usage message. This delegates
     * the work to the optparse::formatter currently active.
     * @return The formatted message.
     */
    std::string format_usage() const noexcept {
        return format->usage(program_name, usage,
                             active_subcommand_index == -1 ? "" : subcommands[active_subcommand_index].name);
    }

    /**
     * @brief Returns the formatted subcommands message.
     * @details Returns the formatted subcommands message. This delegates
     * the work to the optparse::formatter currently active.
     * @return The formatted message.
     */
    std::string format_subcommands() const noexcept {
        return format->subcommands(subcommands);
    }

    /**
     * @brief Returns the formatted options message.
     * @details Returns the formatted options message. This delegates
     * the work to the optparse::formatter currently active. Note that this
     * passes the current option_set that is currently active.
     * @return The formatted message.
     */
    std::string format_options() const noexcept {
        return format->options(*active_options);
    }

    /**
     * @brief Returns the formatted help message.
     * @details Returns the formatted help message. The help message is
     * done as if calling the formatter's member functions in the following
     * order:
     *
     * - usage
     * - description
     * - subcommands
     * - options
     * - epilogue
     *
     * If a different order is needed, you may call the
     * individual member functions that handle the formatting, i.e.
     * the `format_*` functions.
     *
     * @return The help message.
     */
    std::string format_help() const noexcept {
        std::string result = format_usage();
        result.append(format_description()).append(format_subcommands());
        result.append(format_options()).append(format_epilogue());
        return result;
    }
};
} // optparse
} // gears

#endif // GEARS_OPTPARSE_OPTION_PARSER_HPP
