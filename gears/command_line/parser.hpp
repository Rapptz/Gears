// The MIT License (MIT)

// Copyright (c) 2012-2013 Danny Y., Rapptz

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

#ifndef GEARS_COMMAND_LINE_PARSER_HPP
#define GEARS_COMMAND_LINE_PARSER_HPP

#include <map>
#include "details.hpp"
#include "arg.hpp"

namespace gears {
namespace command_line {
class parser {
private:
    std::map<std::string, arg> args;
    std::string program_name;
    std::string program_usage;

    int parse_value(arg& argu, char* argv[], int counter) {
        // next arg isn't a flag or option
        // intersperse values with a space separator
        if(argv[counter] != nullptr && argv[counter][0] != '-') {
            // overwrite value
            argu.value = argv[counter];
            ++counter;
        }

        while(argv[counter] != nullptr && argv[counter][0] != '-') {
            // append the value to the space separated list
            argu.value.push_back(' ');
            argu.value.append(argv[counter++]);
        }

        return counter - 1;
    }

    void parse_short_option(const std::string& option, int& i, char* argv[]) {
        for(auto&& arg : args) {

            auto pos = option.find(arg.second.short_name);

            // Single flag or option with value
            if(option.size() == 2) {
                if(pos != std::string::npos) {
                    if(arg.second.is_value()) {
                        i = parse_value(arg.second, argv, i + 1);
                        break;
                    }

                    // regular flag

                    arg.second.active = true;
                }
            }

            // Grouped character or grouped option
            else if(option.size() > 2) {

                // Grouped option
                if(arg.second.is_value() && option[1] == arg.second.short_name) {
                    arg.second.value.append(std::begin(option) + 2, std::end(option));
                    arg.second.active = true;
                    break;
                }

                // regular flag with grouped characters                
                arg.second.active = pos != std::string::npos;
            }
            else {
                // Seems to be neither
                break; 
            }
        }
    }
public:
    parser() = default;

    parser(std::initializer_list<arg> l) {
        for(auto&& i : l) {
            args.insert(std::make_pair("--" + i.name, i));
        }
    }

    arg& add(const std::string& name) {
        auto p = args.emplace(std::piecewise_construct, 
                              std::forward_as_tuple("--" + name), 
                              std::forward_as_tuple(name));
        return (p.first)->second;
    }

    parser& add(const arg& argument) {
        args.insert(std::make_pair("--" + argument.name, argument));
        return *this;
    }

    void parse(int argc, char* argv[]) {
        std::string current;

        if(program_name.empty()) {
            program_name = argv[0];
        }

        for(int i = 1; i < argc; ++i) {
            current = argv[i];

            // Stop parsing if it's --
            if(current == "--")
                break;

            // current arg has equal sign            
            auto pos = current.find('=');
            if(pos != std::string::npos) {
                auto it = args.find(current.substr(0, pos));

                // make sure the argument is valid
                if(it != args.end()) {
                    // Override value
                    it->second.value = current.substr(pos + 1);
                }

                continue;
            }

            auto it = args.find(current);

            if(it != args.end()) {

                // value options
                if(it->second.is_value()) {
                    i = parse_value(it->second, argv, i + 1);
                }

                // regular flag
                
                it->second.active = true;
                continue;
            }

            // short options found
            if(current.front() == '-') {
                parse_short_option(current, i, argv);
            }
            else {
                // otherwise, it is an unrecognised argument
                throw detail::unrecognised_arg(program_name, current);
            }
        }
    }

    bool is_active(const std::string& name) const noexcept {
        auto it = args.find("--" + name);
        if(it != args.end()) {
            return it->second.active;
        }
        return false;
    }

    parser& usage(std::string str) noexcept {
        program_usage = std::move(str);
        return *this;
    }

    parser& name(std::string str) noexcept {
        program_name = std::move(str);
        return *this;
    }

    template<typename T = std::string>
    T get(const std::string& str) const {
        const auto& argument = "--" + str;
        auto it = args.find(argument);
        if(it != args.end()) {
            if(it->second.is_value())
                return detail::lexical_cast<T>(it->second.value);
        }

        throw detail::invalid_arg_get(argument);
    }

    template<typename T>
    T get_list(const std::string& str) const {
        const auto& argument = "--" + str;
        auto it = args.find(argument);
        if(it != args.end()) {
            if(it->second.is_value()) {
                T result;
                std::istringstream ss(it->second.value);
                typename T::value_type x;
                while(ss >> x) {
                    detail::insert_impl(result, x);
                }

                return result;
            }
        }

        throw detail::invalid_arg_get(argument);
    }

    void check_required_args() const {
        // loop through every argument to see if the required
        // arguments haven't been provided.
        for(auto&& arg : args) {
            if(arg.second.req && !arg.second.active) {
                throw detail::missing_required_arg(program_name, "--" + arg.second.name);
            }
        }
    }

    #ifndef GEARS_NO_IOSTREAM

    template<typename Elem, typename Traits>
    friend auto operator<<(std::basic_ostream<Elem, Traits>& out, const parser& po) -> decltype(out) {
        out << "usage: " << po.program_name << ' ' << po.program_usage << "\n\n";

        for(auto&& arg : po.args) {
            out << arg.second;            
        }

        return out;
    }

    #endif // GEARS_NO_IOSTREAM
};
} // command_line
} // gears

#endif // GEARS_COMMAND_LINE_PARSER_HPP