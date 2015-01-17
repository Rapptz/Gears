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

#ifndef GEARS_STRING_CLASSIFICATION_HPP
#define GEARS_STRING_CLASSIFICATION_HPP

#include <locale>

/**
 * @ingroup string
 * @defgroup string_function_objects String classification function objects
 * @brief Provides string related function objects for classification.
 */

namespace gears {
namespace string {
/**
 * @ingroup string_function_objects
 * @brief Checks if a character is lower case.
 * @details Checks if a character is lower case given a locale.
 * This is a wrapper around `std::islower(CharT, std::locale)`
 */
struct is_lower {
private:
    std::locale loc;
public:
    /**
     * @brief Constructs the function object with the given locale
     */
    is_lower(const std::locale& loc = std::locale()): loc(loc) {}

    template<typename CharT>
    bool operator()(CharT c) const {
        return std::islower(c, loc);
    }
};

/**
 * @ingroup string_function_objects
 * @brief Checks if a character is upper case.
 * @details Checks if a character is upper case given a locale.
 * This is a wrapper around `std::isupper(CharT, std::locale)`
 */
struct is_upper {
private:
    std::locale loc;
public:
    /**
     * @brief Constructs the function object with the given locale
     */
    is_upper(const std::locale& loc = std::locale()): loc(loc) {}

    template<typename CharT>
    bool operator()(CharT c) const {
        return std::isupper(c, loc);
    }
};

/**
 * @ingroup string_function_objects
 * @brief Checks if a character is a space.
 * @details Checks if a character is a space given a locale.
 * This is a wrapper around `std::isspace(CharT, std::locale)`
 */
struct is_space {
private:
    std::locale loc;
public:
    /**
     * @brief Constructs the function object with the given locale
     */
    is_space(const std::locale& loc = std::locale()): loc(loc) {}

    template<typename CharT>
    bool operator()(CharT c) const {
        return std::isspace(c, loc);
    }
};

/**
 * @ingroup string_function_objects
 * @brief Checks if a character is a control character.
 * @details Checks if a character is a control character given a locale.
 * This is a wrapper around `std::iscntrl(CharT, std::locale)`
 */
struct is_cntrl {
private:
    std::locale loc;
public:
    /**
     * @brief Constructs the function object with the given locale
     */
    is_cntrl(const std::locale& loc = std::locale()): loc(loc) {}

    template<typename CharT>
    bool operator()(CharT c) const {
        return std::iscntrl(c, loc);
    }
};

/**
 * @ingroup string_function_objects
 * @brief Checks if a character is alphabetic.
 * @details Checks if a character is alphabetic given a locale.
 * This is a wrapper around `std::isalpha(CharT, std::locale)`
 */
struct is_alpha {
private:
    std::locale loc;
public:
    /**
     * @brief Constructs the function object with the given locale
     */
    is_alpha(const std::locale& loc = std::locale()): loc(loc) {}

    template<typename CharT>
    bool operator()(CharT c) const {
        return std::isalpha(c, loc);
    }
};

/**
 * @ingroup string_function_objects
 * @brief Checks if a character is a digit.
 * @details Checks if a character is a digit given a locale.
 * This is a wrapper around `std::isdigit(CharT, std::locale)`
 */
struct is_digit {
private:
    std::locale loc;
public:
    /**
     * @brief Constructs the function object with the given locale
     */
    is_digit(const std::locale& loc = std::locale()): loc(loc) {}

    template<typename CharT>
    bool operator()(CharT c) const {
        return std::isdigit(c, loc);
    }
};

/**
 * @ingroup string_function_objects
 * @brief Checks if a character is a punctuation character.
 * @details Checks if a character is a punctuation character given a locale.
 * This is a wrapper around `std::ispunct(CharT, std::locale)`
 */
struct is_punct {
private:
    std::locale loc;
public:
    /**
     * @brief Constructs the function object with the given locale
     */
    is_punct(const std::locale& loc = std::locale()): loc(loc) {}

    template<typename CharT>
    bool operator()(CharT c) const {
        return std::ispunct(c, loc);
    }
};

/**
 * @ingroup string_function_objects
 * @brief Checks if a character is alphanumeric.
 * @details Checks if a character is alphanumeric given a locale.
 * This is a wrapper around `std::isalnum(CharT, std::locale)`
 */
struct is_alnum {
private:
    std::locale loc;
public:
    /**
     * @brief Constructs the function object with the given locale
     */
    is_alnum(const std::locale& loc = std::locale()): loc(loc) {}

    template<typename CharT>
    bool operator()(CharT c) const {
        return std::isalnum(c, loc);
    }
};

/**
 * @ingroup string_function_objects
 * @brief Checks if a character is a print character.
 * @details Checks if a character is a print character given a locale.
 * This is a wrapper around `std::isprint(CharT, std::locale)`
 */
struct is_print {
private:
    std::locale loc;
public:
    /**
     * @brief Constructs the function object with the given locale
     */
    is_print(const std::locale& loc = std::locale()): loc(loc) {}

    template<typename CharT>
    bool operator()(CharT c) const {
        return std::isprint(c, loc);
    }
};

/**
 * @ingroup string_function_objects
 * @brief Checks if a character is a graph character.
 * @details Checks if a character is a graph character given a locale.
 * This is a wrapper around `std::isgraph(CharT, std::locale)`
 */
struct is_graph {
private:
    std::locale loc;
public:
    /**
     * @brief Constructs the function object with the given locale
     */
    is_graph(const std::locale& loc = std::locale()): loc(loc) {}

    template<typename CharT>
    bool operator()(CharT c) const {
        return std::isgraph(c, loc);
    }
};

/**
 * @ingroup string_function_objects
 * @brief Checks if a character is hexadecimal.
 * @details Checks if a character is hexadecimal given a locale.
 * This is a wrapper around `std::isxdigit(CharT, std::locale)`
 */
struct is_xdigit {
private:
    std::locale loc;
public:
    /**
     * @brief Constructs the function object with the given locale
     */
    is_xdigit(const std::locale& loc = std::locale()): loc(loc) {}

    template<typename CharT>
    bool operator()(CharT c) const {
        return std::isxdigit(c, loc);
    }
};
} // string
} // gears

#endif // GEARS_STRING_CLASSIFICATION_HPP
