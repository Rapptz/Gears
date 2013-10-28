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

#ifndef GEARS_STRING_CLASSIFICATION_HPP
#define GEARS_STRING_CLASSIFICATION_HPP

#include <locale>

namespace gears {
namespace string {
struct is_lower {
private:
    std::locale loc;
public:
    is_lower(const std::locale& loc = std::locale()): loc(loc) {}
    template<typename CharT>
    bool operator()(CharT c) const {
        return std::islower(c, loc);
    }
};

struct is_upper {
private:
    std::locale loc;
public:
    is_upper(const std::locale& loc = std::locale()): loc(loc) {}
    template<typename CharT>
    bool operator()(CharT c) const {
        return std::isupper(c, loc);
    }
};

struct is_space {
private:
    std::locale loc;
public:
    is_space(const std::locale& loc = std::locale()): loc(loc) {}
    template<typename CharT>
    bool operator()(CharT c) const {
        return std::isspace(c, loc);
    }
};

struct is_cntrl {
private:
    std::locale loc;
public:
    is_cntrl(const std::locale& loc = std::locale()): loc(loc) {}
    template<typename CharT>
    bool operator()(CharT c) const {
        return std::iscntrl(c, loc);
    }
};

struct is_alpha {
private:
    std::locale loc;
public:
    is_alpha(const std::locale& loc = std::locale()): loc(loc) {}
    template<typename CharT>
    bool operator()(CharT c) const {
        return std::isalpha(c, loc);
    }
};

struct is_digit {
private:
    std::locale loc;
public:
    is_digit(const std::locale& loc = std::locale()): loc(loc) {}
    template<typename CharT>
    bool operator()(CharT c) const {
        return std::isdigit(c, loc);
    }
};

struct is_punct {
private:
    std::locale loc;
public:
    is_punct(const std::locale& loc = std::locale()): loc(loc) {}
    template<typename CharT>
    bool operator()(CharT c) const {
        return std::ispunct(c, loc);
    }
};

struct is_alnum {
private:
    std::locale loc;
public:
    is_alnum(const std::locale& loc = std::locale()): loc(loc) {}
    template<typename CharT>
    bool operator()(CharT c) const {
        return std::isalnum(c, loc);
    }
};

struct is_print {
private:
    std::locale loc;
public:
    is_print(const std::locale& loc = std::locale()): loc(loc) {}
    template<typename CharT>
    bool operator()(CharT c) const {
        return std::isprint(c, loc);
    }
};

struct is_graph {
private:
    std::locale loc;
public:
    is_graph(const std::locale& loc = std::locale()): loc(loc) {}
    template<typename CharT>
    bool operator()(CharT c) const {
        return std::isgraph(c, loc);
    }
};

struct is_xdigit {
private:
    std::locale loc;
public:
    is_xdigit(const std::locale& loc = std::locale()): loc(loc) {}
    template<typename CharT>
    bool operator()(CharT c) const {
        return std::isxdigit(c, loc);
    }
};
} // string
} // gears

#endif // GEARS_STRING_CLASSIFICATION_HPP