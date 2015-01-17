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

#ifndef GEARS_UTILITY_MAYBE_HPP
#define GEARS_UTILITY_MAYBE_HPP

#include <gears/utility/maybe/traits.hpp>
#include <gears/utility/maybe/base.hpp>
#include <exception>

namespace gears {
struct bad_maybe_access : std::exception {
    virtual const char* what() const noexcept {
        return "bad maybe access";
    }
};

template<typename T>
using MaybeBase = meta::iif<std::is_trivially_destructible<T>, detail::cmaybe_base<T>, detail::maybe_base<T>>;

/**
 * @ingroup utility
 * @brief An optional data type.
 * @details Implements an optional data type, similar to Haskell's
 * `Maybe` monad and Boost's `boost::optional`. It manages a value that
 * might not be there, similar to a pointer being possibly null. A lot of
 * effort to make `maybe<T>` be a possible constant expression was made.
 * As a result of this, you can make `maybe` be a `constexpr` variable
 * if needed.
 *
 * The type to manage must not be `nothing_t`, `in_place_t`, a reference,
 * or another `maybe`. This might change in the future, but for now
 * this is the restriction in place.
 *
 * `maybe` has two states -- disengaged and engaged states. A disengaged
 * state is when `maybe` does not contain a value, i.e. it contains
 * `nothing`. An engaged state is when `maybe` does contain a value to
 * manage.
 *
 * Example:
 * @code
 * #include <gears/utility.hpp>
 * #include <iostream>
 *
 * gears::maybe<int> special(int x) {
 *     return x > 10 ? gears::just(x * 10) : gears::nothing;
 * }
 *
 * int main() {
 *     auto x = special(8);
 *     auto y = special(25);
 *
 *     if(x) {
 *         std::cout << "x has a value\n";
 *     }
 *
 *     if(y) {
 *         std::cout << "y has a value\n";
 *     }
 *
 *     std::cout << x.value_or(20) << '\n' << y.value_or(10) << '\n';
 * }
 * @endcode
 *
 * Output:
 * <pre>
 * y has a value
 * 20
 * 250
 * </pre>
 *
 * @tparam T Underlying type to manage.
 */
template<typename T>
class maybe : private MaybeBase<T> {
private:
    static_assert(!std::is_same<meta::decay_t<T>, nothing_t>(), "Invalid type. Must not be nothing");
    static_assert(!std::is_same<meta::decay_t<T>, in_place_t>(), "Invalid type. Must not be in_place tag");
    static_assert(!std::is_reference<T>(), "Invalid type. Must not be a reference type");
    static_assert(!is_maybe<T>(), "Invalid type. Must not be a maybe type");

    constexpr bool is_valid() const noexcept {
        return MaybeBase<T>::valid;
    }

    T* data() {
        return std::addressof(MaybeBase<T>::storage.value);
    }

    constexpr const T* data() const {
        return detail::address_of(MaybeBase<T>::storage.value);
    }

    constexpr const T& internal() const {
        return MaybeBase<T>::storage.value;
    }

    T& internal() {
        return MaybeBase<T>::storage.value;
    }

    void clear() noexcept {
        if(is_valid()) {
            data()->T::~T();
        }
        MaybeBase<T>::valid = false;
    }

    template<typename... Args>
    void initialise(Args&&... args) noexcept(noexcept(T(std::forward<Args>(args)...))) {
        new(data()) T(std::forward<Args>(args)...);
        MaybeBase<T>::valid = true;
    }

public:
    using value_type = T;

    /**
     * @brief Constructs `maybe` in a disengaged state.
     */
    constexpr maybe() noexcept: MaybeBase<T>() {}

    /**
     * @brief Constructs `maybe` in a disengaged state.
     */
    constexpr maybe(nothing_t) noexcept : MaybeBase<T>() {}

    /**
     * @brief Constructs `maybe` in an engaged state containing the value.
     */
    constexpr maybe(const T& value): MaybeBase<T>(value) {}

    /**
     * @brief Constructs `maybe` in an engaged state containing the value.
     */
    constexpr maybe(T&& value): MaybeBase<T>(meta::cmove(value)) {}

    /**
     * @brief Constructs `maybe` in place.
     * @details Constructs `maybe` in place with the `in_place` tag.
     *
     * Example:
     * @code
     * #include <gears/utility.hpp>
     * #include <iostream>
     * #include <string>
     *
     * struct my_class {
     * private:
     *     std::string name;
     * public:
     *     my_class(std::string name): name(std::move(name)) {
     *         std::cout << "constructed\n";
     *     }
     *     my_class(my_class&& o): name(std::move(o.name)) {
     *         std::cout << "moved\n";
     *     }
     * };
     *
     * int main() {
     *     gears::maybe<my_class> x(my_class{"Bob"});
     *     std::cout << "---\n";
     *     gears::maybe<my_class> y(gears::in_place, "Bob");
     * }
     * @endcode
     *
     * Output:
     * <pre>
     * constructed
     * moved
     * ---
     * constructed
     * </pre>
     *
     * @param args Parameters to forward to the constructor.
     */
    template<typename... Args>
    constexpr explicit maybe(in_place_t, Args&&... args): MaybeBase<T>(in_place, meta::cforward<Args>(args)...) {}

    /**
     * @brief Copy constructor.
     * @details Copy constructs `maybe`. If `rhs` is disengaged,
     * then the class is constructed as disengaged. Otherwise,
     * the class is constructed as engaged.
     *
     * @param rhs Other maybe to copy from.
     */
    maybe(const maybe& rhs): MaybeBase<T>(detail::regular_init, rhs.is_valid()) {
        if(rhs.is_valid()) {
            new(data()) T(rhs.internal());
        }
    }

    /**
     * @brief Move constructor.
     * @details Move constructs `maybe`. If `rhs` is disengaged,
     * then the class is constructed as disengaged. Otherwise,
     * the class is constructed as engaged. The move constructor of
     * the internal class should not throw.
     *
     * @param rhs Other maybe to move from.
     */
    maybe(maybe&& rhs) noexcept(std::is_nothrow_move_constructible<T>()): MaybeBase<T>(detail::regular_init, rhs.is_valid()) {
        if(rhs.is_valid()) {
            new(data()) T(std::move(rhs.internal()));
        }
    }

    ~maybe() = default;

    /**
     * @brief Assignment with `nothing`.
     * @details Assigns the internal data with `nothing`.
     * This results in a disengaged state.
     *
     * @code
     * maybe<int> x(4);
     * x = nothing;
     * @endcode
     */
    maybe& operator=(nothing_t) noexcept {
        clear();
        return *this;
    }

    /**
     * @brief Copy assignment. Behaves similar to the copy constructor.
     */
    maybe& operator=(const maybe& rhs) {
        if(is_valid() && !rhs.is_valid()) {
            clear();
        }
        else if(!is_valid() && rhs.is_valid()) {
            initialise(rhs.internal());
        }
        else if(is_valid() && rhs.is_valid()) {
            internal() = rhs.internal();
        }

        return *this;
    }

    /**
     * @brief Move assignment. Behaves similar to the move constructor.
     */
    maybe& operator=(maybe&& rhs) noexcept(std::is_nothrow_move_assignable<T>() && std::is_nothrow_move_constructible<T>()) {
        if(is_valid() && !rhs.is_valid()) {
            clear();
        }
        else if(!is_valid() && rhs.is_valid()) {
            initialise(std::move(rhs.internal()));
        }
        else if(is_valid() && rhs.is_valid()) {
            internal() = std::move(rhs.internal());
        }

        return *this;
    }

    /**
     * @brief Assigns `maybe` in an engaged state with the value given.
     * @details Assigns `maybe` in an engaged state with the value
     * given. If current state is engaged, then the value is replaced
     * with the one given, when replaced then the destructor of the
     * managed type is called.
     *
     * @param value The value to assign to `maybe`.
     */
    template<typename U, meta::enable_if_t<std::is_constructible<T, meta::decay_t<U>>, std::is_assignable<T, meta::decay_t<U>>> = meta::_>
    maybe& operator=(U&& value) {
        if(is_valid()) {
            internal() = std::forward<U>(value);
        }
        else {
            initialise(std::forward<U>(value));
        }
        return *this;
    }

    /**
     * @brief Constructs the contained value in place.
     * @details Constructs the contained value in place. If the
     * current state is engaged, then it is replaced with the newly
     * constructed value. When replaced, then the destructor of the
     * managed type is called. This works similar to the `in_place_t`
     * constructor.
     *
     * @param args Parameter to forward to the managed type's constructor.
     */
    template<typename... Args>
    void emplace(Args&&... args) {
        clear();
        initialise(std::forward<Args>(args)...);
    }

    //@{
    /**
     * @brief Returns a pointer to the contained value.
     * @details Returns a pointer to the contained value.
     * If the current state is disengaged, then the behaviour
     * is undefined. This is should only be used for accessing
     * member functions of the internal value.
     *
     * @code
     * struct my_class { int x; };
     * maybe<my_class> stuff({ 10 });
     * // access my_class::x
     * std::cout << stuff->x;
     * @endcode
     *
     * @return Pointer to contained value.
     */
    constexpr const T* operator->() const {
        return data();
    }

    T* operator->() {
        return data();
    }
    //@}

    //@{
    /**
     * @brief Returns a reference to the contained value.
     * @details Returns a reference to the contained value.
     * If the current state is disengaged, then the behaviour
     * is undefined.
     * @return Reference to the contained value.
     */
    constexpr const T& operator*() const {
        return internal();
    }

    T& operator*() {
        return internal();
    }
    //@}

    //@{
    /**
     * @brief Accesses the contained value.
     * @details Accesses the contained value. If the current
     * state is disengaged, an exception is thrown.
     *
     * @throws gears::bad_maybe_access Thrown if the current state is disengaged.
     * @return Returns the a reference to the contained value.
     */
    constexpr const T& value() const {
        return is_valid() ? internal() : (throw bad_maybe_access(), internal());
    }

    T& value() {
        return is_valid() ? internal() : (throw bad_maybe_access(), internal());
    }
    //@}

    /**
     * @brief Checks if the current state is engaged.
     * @details Checks if the current state is engaged.
     * @return `true` if the current state is engaged, `false` otherwise.
     */
    constexpr explicit operator bool() const noexcept {
        return is_valid();
    }

    /**
     * @brief Accesses the contained value or a reasonable default.
     * @details Accesses the contained value of a reasonable default.
     * Unlike #value and #operator* this does not return a reference but
     * a copy.
     *
     * @param value The default value if the current state is disengaged.
     * @return The contained value or a default if current state is disengaged.
     */
    template<typename U>
    constexpr T value_or(U&& value) const {
        return is_valid() ? internal() : static_cast<T>(meta::cforward<U>(value));
    }
};

/**
 * @relates maybe
 * @brief Helper function to create an engaged `maybe` object.
 * @details Helper function to create an engaged `maybe` object.
 * This typically moves or copies and does not create the contained
 * value in place.
 *
 * @param t Value for the contained value.
 * @return A new `maybe` object that is engaged with the value.
 */
template<typename T>
constexpr maybe<meta::decay_t<T>> just(T&& t) {
    return { meta::cforward<T>(t) };
}

/**
 * @name Comparison with maybe<T> and maybe<T>
 * @relates maybe
 * @brief Compares the contained value of both `maybe<T>`s.
 * @details If both `maybe<T>` are disengaged, then the comparison
 * returns `true`. If only one `maybe<T>` is disengaged, then the
 * comparison returns `false`. Otherwise it uses the internal comparison
 * operator on both contained values.
 *
 * @param lhs Left hand side of the comparison
 * @param rhs Right hand side of the comparison
 */

//@{
/**
 * @brief Checks if two `maybe<T>` are equal.
 */
template<typename T>
constexpr bool operator==(const maybe<T>& lhs, const maybe<T>& rhs) {
    return static_cast<bool>(lhs) != static_cast<bool>(rhs) ? false : static_cast<bool>(lhs) == false ? true  : *lhs == *rhs;
}

/**
 * @brief Checks if two `maybe<T>` are not equal.
 */
template<typename T>
constexpr bool operator!=(const maybe<T>& lhs, const maybe<T>& rhs) {
    return !(lhs == rhs);
}

/**
 * @brief Checks if one `maybe<T>` is less than another `maybe<T>`.
 */
template<typename T>
constexpr bool operator<(const maybe<T>& lhs, const maybe<T>& rhs) {
    return !rhs ? false : !lhs ? true : *lhs < *rhs;
}

/**
 * @brief Checks if one `maybe<T>` is greater than another `maybe<T>`.
 */
template<typename T>
constexpr bool operator>(const maybe<T>& lhs, const maybe<T>& rhs) {
    return (rhs < lhs);
}

/**
 * @brief Checks if one `maybe<T>` is less than or equal to another `maybe<T>`.
 */
template<typename T>
constexpr bool operator<=(const maybe<T>& lhs, const maybe<T>& rhs) {
    return !(rhs < lhs);
}

/**
 * @brief Checks if one `maybe<T>` is greater than or equal to another `maybe<T>`.
 */
template<typename T>
constexpr bool operator>=(const maybe<T>& lhs, const maybe<T>& rhs) {
    return !(lhs < rhs);
}
//@}

// Comparison with nothing
/**
 * @name Comparison with nothing.
 * @relates maybe
 * @brief Compares `maybe<T>` with `nothing`.
 * @details For completeness sakes, you can compare
 * `nothing` with `maybe<T>`. `nothing` will always evaluate
 * to `false`. So all comparisons are based on truth values
 * with `maybe` converted into a boolean `true` or `false` depending
 * on the engaged state it is at. For example:
 *
 * @code
 * my_maybe == nothing;
 * // bool(my_maybe) == false
 * @endcode
 *
 * Where `bool(my_maybe)` is given through #operator bool()
 *
 * Although only one comparison is shown, all comparison operators
 * are overloaded for both directions.
 */

//@{
/**
 * @brief Compares with `nothing`
 */
template<typename T>
constexpr bool operator==(const maybe<T>& lhs, nothing_t) noexcept {
    return !lhs;
}

template<typename T>
constexpr bool operator==(nothing_t, const maybe<T>& rhs) noexcept {
    return !rhs;
}

template<typename T>
constexpr bool operator!=(const maybe<T>& lhs, nothing_t) noexcept {
    return static_cast<bool>(lhs);
}

template<typename T>
constexpr bool operator!=(nothing_t, const maybe<T>& rhs) noexcept {
    return static_cast<bool>(rhs);
}

template<typename T>
constexpr bool operator<(const maybe<T>&, nothing_t) noexcept {
    return false;
}

template<typename T>
constexpr bool operator<(nothing_t, const maybe<T>& rhs) noexcept {
    return static_cast<bool>(rhs);
}

template<typename T>
constexpr bool operator>(const maybe<T>& lhs, nothing_t) noexcept {
    return static_cast<bool>(lhs);
}

template<typename T>
constexpr bool operator>(nothing_t, const maybe<T>&) noexcept {
    return false;
}

template<typename T>
constexpr bool operator<=(const maybe<T>& lhs, nothing_t) noexcept {
    return !lhs;
}

template<typename T>
constexpr bool operator<=(nothing_t, const maybe<T>&) noexcept {
    return true;
}

template<typename T>
constexpr bool operator>=(const maybe<T>&, nothing_t) noexcept {
    return true;
}

template<typename T>
constexpr bool operator>=(nothing_t, const maybe<T>& rhs) noexcept {
    return !rhs;
}
//@}

/**
 * @name Comparisons with other values.
 * @relates maybe
 * @brief Compares the contained value with another value.
 * @details Although both directions are not shown, both directions of
 * operator overloads are provided. Comparison is done through the operator
 * overloaded, i.e. the `operator==` overload would compare the contained
 * value and the other value with their `operator==`.
 */
//@{
/**
 * @brief If the current state is disengaged, returns false. Otherwise compares.
 */
template<typename T>
constexpr bool operator==(const maybe<T>& lhs, const T& value) {
    return static_cast<bool>(lhs) ? *lhs == value : false;
}

template<typename T>
constexpr bool operator==(const T& value, const maybe<T>& rhs) {
    return static_cast<bool>(rhs) ? value == *rhs : false;
}

/**
 * @brief If the current state is disengaged, returns true. Otherwise compares.
 */
template<typename T>
constexpr bool operator!=(const maybe<T>& lhs, const T& value) {
    return static_cast<bool>(lhs) ? *lhs != value : true;
}

template<typename T>
constexpr bool operator!=(const T& value, const maybe<T>& rhs) {
    return static_cast<bool>(rhs) ? value != *rhs : true;
}

/**
 * @brief If the current state is disengaged, returns true. Otherwise compares.
 */
template<typename T>
constexpr bool operator<(const maybe<T>& lhs, const T& value) {
    return static_cast<bool>(lhs) ? *lhs < value : true;
}

template<typename T>
constexpr bool operator>(const T& value, const maybe<T>& rhs) {
    return static_cast<bool>(rhs) ? value > *rhs : true;
}

/**
 * @brief If the current state is disengaged, returns false. Otherwise compares.
 */
template<typename T>
constexpr bool operator>(const maybe<T>& lhs, const T& value) {
    return static_cast<bool>(lhs) ? *lhs > value : false;
}

template<typename T>
constexpr bool operator<(const T& value, const maybe<T>& rhs) {
    return static_cast<bool>(rhs) ? value < *rhs : false;
}

/**
 * @brief If the current state is disengaged, returns false. Otherwise compares.
 */
template<typename T>
constexpr bool operator>=(const maybe<T>& lhs, const T& value) {
    return static_cast<bool>(lhs) ? *lhs >= value : false;
}

template<typename T>
constexpr bool operator<=(const T& value, const maybe<T>& rhs) {
    return static_cast<bool>(rhs) ? value <= *rhs : false;
}

/**
 * @brief If the current state is disengaged, returns true. Otherwise compares.
 */
template<typename T>
constexpr bool operator<=(const maybe<T>& lhs, const T& value) {
    return static_cast<bool>(lhs) ? *lhs <= value : true;
}

template<typename T>
constexpr bool operator>=(const T& value, const maybe<T>& rhs) {
    return static_cast<bool>(rhs) ? value >= *rhs : true;
}
//@}
} // gears

#endif // GEARS_UTILITY_MAYBE_HPP
