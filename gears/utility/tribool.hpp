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

#ifndef GEARS_UTILITY_TRIBOOL_HPP
#define GEARS_UTILITY_TRIBOOL_HPP

#include <utility>
#ifndef GEARS_NO_IOSTREAM
#include <iosfwd>
#include <locale>
#include <string>
#endif // GEARS_NO_IOSTREAM

namespace gears {
struct indeterminate_t {
    constexpr indeterminate_t() {}
};

/**
 * @ingroup utility
 * @brief Represents an indeterminate tribool value
 */
constexpr indeterminate_t indeterminate{};

/**
 * @ingroup utility
 * @brief Implements Kleene's logic for three-state booleans.
 * @details Implements Kleene's logic for three-state booleans. This
 * class should be preferred to `gears::maybe<bool>` as it implements
 * true three-state logic. The three states for the boolean are `true`, `false`,
 * and `indeterminate`. So for example all three are valid:
 *
 * @code
 * gears::tribool x = true;
 * x = false;
 * x = gears::indeterminate;
 * @endcode
 *
 * The input and output operators are supported by default. In order to disable
 * it, you have to define the macro `GEARS_NO_IOSTREAM`. The input/output
 * operators behave similarly to `bool` values, except `indeterminate` can be
 * read or output as 2. When `std::boolalpha` is active, they can be read
 * and written in the same similar manner except the default string would be
 * "indeterminate". For example:
 *
 * @code
 * gears::tribool x = gears::indeterminate;
 * std::cout << std::boolalpha << x << '\n';
 * @endcode
 *
 * Output:
 * <pre>
 * indeterminate
 * </pre>
 *
 * You can change the `indeterminate` value through instantiating a value of
 * type `indeterminate_t`. Likewise, you can change the default string read or
 * written through the use of the `indeterminate_name` facet. For example:
 *
 * @code
 * constexpr gears::indeterminate_t null{};
 * gears::tribool x = null; // defined our own "keyword"
 *
 * // change the default string to null
 * std::locale myloc(std::cout.getloc(), new gears::indeterminate_name<char>("null"));
 * std::cout.imbue(myloc);
 *
 * std::cout << std::boolalpha << x << '\n';
 * @endcode
 *
 * Output:
 * <pre>
 * null
 * </pre>
 *
 */
struct tribool {
private:
    enum class state : char {
        true_, false_, unknown
    } value;
public:
    /**
     * @brief Creates a tribool with an indeterminate value.
     */
    constexpr tribool() noexcept: value(state::unknown) {}

    /**
     * @brief Creates a tribool with an indeterminate value.
     */
    constexpr tribool(indeterminate_t) noexcept: value(state::unknown) {}

    /**
     * @brief Creates a tribool with a boolean value.
     */
    constexpr tribool(bool v) noexcept: value(v ? state::true_ : state::false_) {}

    /**
     * @brief Turns the tribool into a boolean.
     * @return `true` if the tribool stores `true`, `false` otherwise.
     */
    explicit constexpr operator bool() const noexcept {
        return value == state::true_;
    }

    /**
     * @brief Checks if the tribool is true.
     * @param tri The tribool to check.
     * @return `true` if the tribool stores `true`, `false` otherwise.
     */
    friend constexpr bool is_true(const tribool& tri) noexcept {
        return tri.value == state::true_;
    }

    /**
     * @brief Checks if the tribool is false.
     * @param tri The tribool to check.
     * @return `true` if the tribool stores `false`, `false` otherwise.
     */
    friend constexpr bool is_false(const tribool& tri) noexcept {
        return tri.value == state::false_;
    }

    /**
     * @brief Checks if the tribool is indeterminate.
     * @param tri The tribool to check.
     * @return `true` if the tribool stores indeterminate, `false` otherwise.
     */
    friend constexpr bool is_indeterminate(const tribool& tri) noexcept {
        return tri.value == state::unknown;
    }

    /**
     * @brief Checks if both tribool are equal.
     * @details Checks if both tribool are equal based on the
     * following truth table.
     *
     * | ==            | true          | false         | indeterminate |
     * |:-------------:|:-------------:|:-------------:|:-------------:|
     * | true          | true          | false         | indeterminate |
     * | false         | false         | true          | indeterminate |
     * | indeterminate | indeterminate | indeterminate | indeterminate |
     *
     * @param rhs Other tribool to check.
     * @return A tribool according to the table above.
     */
    constexpr tribool operator==(const tribool& rhs) const noexcept {
        return (value == state::unknown || rhs.value == state::unknown) ?
                    tribool(indeterminate) : tribool(value == rhs.value);
    }

    /**
     * @brief Checks if both tribool are not equal.
     * @details Checks if both tribool are not equal based on the
     * following truth table.
     *
     * | !=            | true          | false         | indeterminate |
     * |:-------------:|:-------------:|:-------------:|:-------------:|
     * | true          | false         | true          | indeterminate |
     * | false         | true          | false         | indeterminate |
     * | indeterminate | indeterminate | indeterminate | indeterminate |
     *
     * @param rhs Other tribool to check.
     * @return A tribool according to the table above.
     */
    constexpr tribool operator!=(const tribool& rhs) const noexcept {
        return (value == state::unknown || rhs.value == state::unknown) ?
                    tribool(indeterminate) : tribool(value != rhs.value);
    }

    /**
     * @brief Negates a tribool value.
     * @details Negates a tribool value based on the
     * table below.
     *
     * | !             | Result        |
     * |:-------------:|:-------------:|
     * | true          | false         |
     * | false         | true          |
     * | indeterminate | indeterminate |
     *
     *
     * @return A tribool based on the table above.
     */
    constexpr tribool operator!() const noexcept {
        return value == state::unknown ? tribool(indeterminate) : tribool(!(value == state::true_));
    }
};

/**
 * @relates tribool
 * @brief Computes the logical and of two tribool.
 * @details Computes the logical and of two tribool.
 * Due to the nature of C++'s short circuiting, no
 * short circuiting is done through overloading of this
 * operators. The value returned is based on the following
 * table.
 *
 * | AND           | true          | false         | indeterminate |
 * |:-------------:|:-------------:|:-------------:|:-------------:|
 * | true          | true          | false         | indeterminate |
 * | false         | false         | false         | false         |
 * | indeterminate | indeterminate | false         | indeterminate |
 *
 * @param lhs Left hand side of the expression.
 * @param rhs Right hand side of the expression.
 * @return A tribool based on the truth table above.
 */
constexpr tribool operator&&(const tribool& lhs, const tribool& rhs) noexcept {
    return is_false(lhs) || is_false(rhs) ? tribool(false) :
                is_indeterminate(lhs) || is_indeterminate(rhs) ? tribool(indeterminate) : tribool(true);
}

constexpr tribool operator&&(const tribool& lhs, bool b) noexcept {
    return lhs && tribool(b);
}

constexpr tribool operator&&(bool b, const tribool& rhs) noexcept {
    return tribool(b) && rhs;
}

/**
 * @relates tribool
 * @brief Computes the logical or of two tribool.
 * @details Computes the logical or of two tribool.
 * Due to the nature of C++'s short circuiting, no
 * short circuiting is done through overloading of this
 * operators. The value returned is based on the following
 * table.
 *
 * | OR            | true          | false         | indeterminate |
 * |:-------------:|:-------------:|:-------------:|:-------------:|
 * | true          | true          | true          | true          |
 * | false         | true          | false         | indeterminate |
 * | indeterminate | true          | indeterminate | indeterminate |
 *
 * @param lhs Left hand side of the expression.
 * @param rhs Right hand side of the expression.
 * @return A tribool based on the truth table above.
 */
constexpr tribool operator||(const tribool& lhs, const tribool& rhs) noexcept {
    return is_true(lhs) || is_true(rhs) ? tribool(true) :
                is_indeterminate(lhs) || is_indeterminate(rhs) ? tribool(indeterminate) : tribool(false);
}

constexpr tribool operator||(const tribool& lhs, bool b) noexcept {
    return lhs || tribool(b);
}

constexpr tribool operator||(bool b, const tribool& rhs) noexcept {
    return tribool(b) || rhs;
}

#ifndef GEARS_NO_IOSTREAM
/**
 * @relates tribool
 * @brief Returns the default indeterminate name.
 * @details Returns the default indeterminate name
 * based on the character type provided. Only `char`
 * and `wchar_t` specialisations are provided. The
 * default value is the string "indeterminate".
 *
 * This function is only available if `GEARS_NO_IOSTREAM` is
 * not defined.
 *
 * @tparam CharT The character type of the string.
 * @return The default indeterminate name, "indeterminate".
 */
template<typename CharT>
constexpr const CharT* get_default_indeterminate_name() noexcept;

template<>
constexpr const char* get_default_indeterminate_name<char>() noexcept {
    return "indeterminate";
}

template<>
constexpr const wchar_t* get_default_indeterminate_name<wchar_t>() noexcept {
    return L"indeterminate";
}

/**
 * @relates tribool
 * @brief A locale facet for specifying the indeterminate name of tribool.
 * @details A locale facet for specifying the indeterminate name of tribool.
 * This facet is only activated when `std::boolalpha` has been specified on the
 * stream doing the output or input.
 *
 * This class is only available if `GEARS_NO_IOSTREAM` is
 * not defined.
 *
 * @tparam CharT Character type of the facet.
 */
template<typename CharT>
struct indeterminate_name : public std::locale::facet {
public:
    using char_type = CharT;
    using string_type = std::basic_string<CharT>;
private:
    string_type name_ = get_default_indeterminate_name<CharT>();
public:
    /**
     * @brief Constructs the facet with #get_default_indeterminate_name
     */
    indeterminate_name() = default;

    /**
     * @brief Constructs the facet with the string provided.
     */
    explicit constexpr indeterminate_name(string_type name) noexcept: name_(std::move(name)) {}

    /**
     * @brief Returns the indeterminate name.
     */
    constexpr string_type name() const noexcept {
        return name_;
    }

    static std::locale::id id;
};

template<typename CharT>
std::locale::id indeterminate_name<CharT>::id;

/**
 * @relates tribool
 * @brief Outputs the value of the tribool to the stream provided.
 * @details Outputs the value of the tribool to the stream provided.
 *
 * The value written when `std::boolalpha` is not active is as follows:
 *
 * | internal value  | output |
 * |:---------------:|:------:|
 * | `false`         | 0      |
 * | `true`          | 1      |
 * | `indeterminate` | 2      |
 *
 * If `std::boolalpha` is written then the name written to depends on the
 * facet provided. The `true` and `false` values are provided by the
 * `std::numpunct` functions that implement `do_truename` and `do_falsename`.
 * The indeterminate value is provided by the `indeterminate_name` facet.
 *
 * Assuming everything is defaulted, the values written are as follows:
 *
 * | internal value  | output          |
 * |:---------------:|:---------------:|
 * | `false`         | "false"         |
 * | `true`          | "true"          |
 * | `indeterminate` | "indeterminate" |
 *
 * This operator overload is only available if `GEARS_NO_IOSTREAM` is not
 * defined.
 *
 * @param out Output stream to write to.
 * @param tri Tribool to read from.
 * @return The output stream.
 */
template<typename CharT, typename Traits>
inline auto operator<<(std::basic_ostream<CharT, Traits>& out, const tribool& tri) -> decltype(out) {
    if(!is_indeterminate(tri)) {
        return out << static_cast<bool>(tri);
    }

    typename std::basic_ostream<CharT, Traits>::sentry sentry(out);
    if(sentry) {
        if(out.flags() & std::ios_base::boolalpha) {
            if(std::has_facet<indeterminate_name<CharT>>(out.getloc())) {
                auto&& facet = std::use_facet<indeterminate_name<CharT>>(out.getloc());
                out << facet.name();
            }
            else {
                out << get_default_indeterminate_name<CharT>();
            }
        }
        else {
            out << 2;
        }
    }

    return out;
}

/**
 * @relates tribool
 * @brief Reads a tribool value from an input stream.
 * @details Reads a tribool value from an input stream. This function
 * works similarly to the output stream except inverted. That is, if
 * `std::boolalpha` is not active, then the values of 0, 1, and 2 will
 * set the tribool appropriately otherwise failure will be set.
 *
 * If `std::boolalpha` is set then the string is read from the appropriate
 * facets. Which are `std::numpunct` for `true` and `false` and `indeterminate_name`
 * for the indeterminate value.
 *
 * This operator overload is only available if `GEARS_NO_IOSTREAM` is not
 * defined.
 *
 * @param in The input stream to read from.
 * @param tri The tribool to place the value to.
 * @return The input stream.
 */
template<typename CharT, typename Traits>
inline auto operator>>(std::basic_istream<CharT, Traits>& in, tribool& tri) -> decltype(in) {
    if(in.flags() & std::ios_base::boolalpha) {
        typename std::basic_istream<CharT, Traits>::sentry sentry(in);
        if(sentry) {
            auto&& loc = in.getloc();
            auto&& numpunct_facet = std::use_facet<std::numpunct<CharT>>(loc);
            auto&& false_name = numpunct_facet.falsename();
            auto&& true_name = numpunct_facet.truename();

            using other_facet = indeterminate_name<CharT>;
            std::basic_string<CharT> other_name = get_default_indeterminate_name<CharT>();
            if(std::has_facet<other_facet>(loc)) {
                auto&& facet = std::use_facet<other_facet>(loc);
                other_name = facet.name();
            }

            std::basic_string<CharT> str;
            if(in >> str) {
                if(str == false_name) {
                    tri = false;
                }
                else if(str == true_name) {
                    tri = true;
                }
                else if(str == other_name) {
                    tri = indeterminate;
                }
                else {
                    in.setstate(std::ios_base::failbit);
                }
            }
            return in;
        }
    }
    else {
        int x;
        if(in >> x) {
            switch(x) {
            case 0: tri = false;         break;
            case 1: tri = true;          break;
            case 2: tri = indeterminate; break;
            default:
                in.setstate(std::ios_base::failbit);
                break;
            }
        }
    }
    return in;
}

#endif // GEARS_NO_IOSTREAM
} // gears

#endif // GEARS_UTILITY_TRIBOOL_HPP
