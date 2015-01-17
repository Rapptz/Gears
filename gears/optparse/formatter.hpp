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

#ifndef GEARS_OPTPARSE_FORMATTER_HPP
#define GEARS_OPTPARSE_FORMATTER_HPP

#include <gears/optparse/subcommand.hpp>

namespace gears {
namespace optparse {
/**
 * @ingroup optparse
 * @brief A class that handles the formatting of the help message.
 * @details A class that handles the formatting of the help message.
 * This class could be inherited and you could override its virtual
 * member functions that handle the printing of the message. A default
 * implementation is provided.
 */
struct formatter {
    size_t column;     ///< The maximum column before wrap around

    /**
     * @brief Constructs a formatter with a column defaulting to 80.
     */
    formatter(size_t column = 80): column(column) {}

    /**
     * @brief Virtual destructor.
     */
    virtual ~formatter() = default;

    /**
     * @brief Wraps a string at the column point.
     * @details Wraps a string at the column point. It also
     * handles initial indentation size if needed. The implementation
     * by default wraps based on characters determined to be spaces by
     * the `std::stringstream` object. Indentation is done through spaces.
     *
     * @param str The string to wrap around.
     * @param indent The indentation to have.
     * @returns The string wrapped around based on column - 2.
     */
    virtual std::string wrap(const std::string& str, size_t indent = 0) {
        if(str.empty()) {
            return str;
        }

        size_t c = column - 2;
        std::string result;
        std::string indentation(indent, ' ');

        if(str.size() + indent > c) {
            std::istringstream in(str);
            std::string word;
            if(in >> word) {
                result.append(word);
                size_t spaces = c - word.size() - indent;
                while(in >> word) {
                    if(spaces < word.size() + 1) {
                        result.append(1, '\n').append(indent, ' ').append(word);
                        spaces = c - word.size() - indent;
                    }
                    else {
                        result.append(1, ' ').append(word);
                        spaces -= word.size() + 1;
                    }
                }
            }
            result.push_back('\n');
        }
        else {
            result.append(str).push_back('\n');
        }

        return result;
    }

    /**
     * @brief Handles the usage message.
     * @details Handles the usage message. The default behaviour
     * wraps around based on `usage: {prog} {command} {str}`.
     *
     * @param name The program name.
     * @param command The subcommand name. Empty is not valid.
     * @param str The usage string provided by the user or automatically.
     * @return The resulting usage string.
     */
    virtual std::string usage(const std::string& name, const std::string& command, const std::string& str) {
        std::string result = "usage: " + name;
        if(!command.empty()) {
            result.push_back(' ');
            result += command;
        }
        result.push_back(' ');
        result += str;
        return wrap(result);
    }

    /**
     * @brief Handles the description message.
     * @details Handles the description message. The
     * description is the short brief paragraph that describes
     * the program in the beginning of the help message. By default
     * a newline is appended if the message is non-empty and the wrapped
     * around string is returned.
     *
     * @param str The description message.
     * @return The wrapped around description message.
     */
    virtual std::string description(const std::string& str) {
        auto&& desc = wrap(str);
        if(!str.empty()) {
            desc.push_back('\n');
        }
        return desc;
    }

    /**
     * @brief Handles the epilogue message.
     * @details Handles the epilogue message. The
     * epilogue is the short brief paragraph at the end of the
     * help message. By default, this string is just wrapped around
     * and nothing else is done to it.
     *
     * @param str The epilogue message.
     * @return The wrapped around epilogue message.
     */
    virtual std::string epilogue(const std::string& str) {
        return wrap(str);
    }

    /**
     * @brief Handles the list of subcommands.
     * @details Handles the list of subcommands. This is typically
     * printed after the description in the help message but before the
     * list of options. By default this returns the list of subcommands
     * in name-description indented pairs. Indentation is 4 spaces.
     *
     * @param subs A vector of optparse::subcommand objects.
     * @return The resultant string.
     */
    virtual std::string subcommands(const std::vector<subcommand>& subs) {
        if(subs.empty()) {
            return "";
        }


        std::string out = "subcommands\n";

        auto&& max = std::max_element(subs.begin(), subs.end(), [](const subcommand& lhs, const subcommand& rhs) {
            return lhs.name < rhs.name;
        });

        size_t indent = 20u;
        if(max != subs.end()) {
            indent += max->name.size();
        }

        for(auto&& i : subs) {
            out.append(4, ' ').append(i.name);
            size_t current = indent - 4 - i.name.size();
            out.append(current, ' ');
            if(!i.help.empty()) {
                out.append(wrap(i.help, current));
            }
            else {
                out.push_back('\n');
            }
        }

        return out;
    }

    /**
     * @brief Handles the list of options.
     * @details Handles the list of options. This is typically printed
     * after the list of subcommands, if applicable, or the description. This
     * is also typically printed before the epilogue message. By default
     * this returns a string of indented name-help indented pairs. Indentation
     * defaults to 4 spaces.
     *
     * For options, the default printing is as follows:
     *
     * | Long Form | Short Form | Metavar | Result              |
     * |:---------:|:----------:|:-------:|:-------------------:|
     * | "test"    | 't'        | ""      | "-t, --test       " |
     * | "test"    | '\0'       | ""      | "    --test       " |
     * | ""        | 't'        | ""      | "-t               " |
     * | "test"    | 't'        | "to"    | "-t, --test[=<to>]" |
     * | ""        | 't'        | "to"    | "-t <to>          " |
     *
     *
     * @param opts The current list of active options.
     * @return The resultant string.
     */
    virtual std::string options(const option_set& opts) {
        if(opts.empty()) {
            return "";
        }

        std::string result = "options:\n";

        auto&& max_name = std::max_element(opts.begin(), opts.end(), [](const option& lhs, const option& rhs) {
            return lhs.name < rhs.name;
        });

        auto&& max_meta = std::max_element(opts.begin(), opts.end(), [](const option& lhs, const option& rhs) {
            return lhs.metavar() < rhs.metavar();
        });

        size_t max_indent = 14u;

        if(max_name != opts.end()) {
            max_indent += max_name->name.size();
        }

        if(max_meta != opts.end()) {
            max_indent += 5u + max_meta->metavar().size();
        }

        for(auto&& opt : opts) {
            if((opt.flags & trait::hidden) == trait::hidden) {
                continue;
            }

            size_t indent = max_indent;
            const bool has_long_option  = !opt.name.empty();
            const bool has_short_option = opt.alias != '\0';
            const std::string metavar   = opt.metavar();
            const bool has_metavar      = !metavar.empty();

            if(has_long_option && has_short_option) {
                result.append(4, ' ').append(1, '-').append(1, opt.alias).append(", --").append(opt.name);
                indent -= 10u + opt.name.size();
            }
            else if(has_long_option) {
                result.append(4, ' ').append("    --").append(opt.name);
                indent -= 10u + opt.name.size();
            }
            else if(has_short_option) {
                result.append(4, ' ').append(1, '-').append(1, opt.alias);
                indent -= 6u;
            }

            if(has_metavar) {
                if(has_long_option) {
                    result.append("[=<").append(metavar).append(">]");
                    indent -= 5u + metavar.size();
                }
                else {
                    result.append(1, ' ').append(1, '<').append(metavar).append(1, '>');
                    indent -= 3u + metavar.size();
                }
            }

            result.append(indent, ' ');

            if(opt.help.empty()) {
                result.push_back('\n');
                continue;
            }

            result.append(wrap(opt.help, indent));
        }

        return result;
    }
};
} // optparse
} // gears

#endif // GEARS_OPTPARSE_FORMATTER_HPP
