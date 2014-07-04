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

#ifndef GEARS_UTILITY_TRIBOOL_HPP
#define GEARS_UTILITY_TRIBOOL_HPP

#include <utility>

namespace gears {
namespace utility {
struct indeterminate_t {
    constexpr indeterminate_t() {}
};

/**
 * @ingroup utility
 * @brief Represents an intermediate tribool value
 */
constexpr indeterminate_t indeterminate{};

/**
 * @ingroup utility
 * @brief Implements Kleene's logic for three-state booleans.
 * @details Implements Kleene's logic for three-state booleans. This
 * class should be preferred to `gears::utility::maybe<bool>` as it implements
 * true three-state logic. The three states for the boolean are `true`, `false`,
 * and `indeterminate`. So for example all three are valid:
 *
 * @code
 * namespace util = gears::utility;
 * util::tribool x = true;
 * x = false;
 * x = util::indeterminate;
 * @endcode
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
} // utility
} // gears

#endif // GEARS_UTILITY_TRIBOOL_HPP
