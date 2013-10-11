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

#ifndef GEARS_PROGRAM_OPTIONS_ARG_HPP
#define GEARS_PROGRAM_OPTIONS_ARG_HPP

#include <string>

#ifndef GEARS_NO_IOSTREAM
#include <iosfwd>
#endif // GEARS_NO_IOSTREAM

namespace gears {
struct arg {
private:
    friend class program_options;
    std::string name;
    std::string description;
    std::string parameter;
    std::string value;
    bool active = false;
    char short_name = '\0';
public:
    arg(std::string name, std::string desc = "", char shorter = '\0', std::string p = "") noexcept: 
    name(std::move(name)), description(std::move(desc)), parameter(std::move(p)), short_name(shorter) {}

    bool is_value() const noexcept {
        return !parameter.empty();
    }

    arg& shorter(char c) noexcept {
        short_name = c;
        return *this;
    }

    arg& help(std::string str) noexcept {
        description = std::move(str);
        return *this;
    }

    arg& param(std::string str) noexcept {
        parameter = std::move(str);
        return *this;
    }

    #ifndef GEARS_NO_IOSTREAM

    template<typename Elem, typename Traits>
    friend auto operator<<(std::basic_ostream<Elem, Traits>& out, const arg& a) -> decltype(out) {
        int spaces = 30;
        out << "    ";
        if(!a.name.empty()) {
            if(a.short_name != '\0') {
                out << '-' << a.short_name << ", ";
                spaces -= 4;
            }

            out << "--" << a.name;
            spaces -= 2 + a.name.size();

            if(!a.parameter.empty()) {
                out << "[=<" << a.parameter << ">]";
                spaces -= 5 + a.parameter.size();
            }

            for(int i = 0; i < spaces; ++i) {
                out << ' ';
            }

            out << a.description << '\n';
        }

        return out;
    }

    #endif // GEARS_NO_IOSTREAM
};
} // gears

#endif // GEARS_PROGRAM_OPTIONS_ARG_HPP