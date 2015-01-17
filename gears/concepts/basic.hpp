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

#ifndef GEARS_CONCEPTS_BASIC_HPP
#define GEARS_CONCEPTS_BASIC_HPP

#include <gears/concepts/alias.hpp>
#include <utility>

namespace gears {
namespace concepts {
namespace detail {
struct is_lvalue_swappable {
    template<typename T, typename U>
    static auto test(int) -> decltype(std::swap(std::declval<LRef<T>>(), std::declval<LRef<U>>()), std::true_type{}) {}
    template<typename...>
    static std::false_type test(...);
};

struct is_rvalue_swappable {
    template<typename T, typename U>
    static auto test(int) -> decltype(std::swap(std::declval<RRef<T>>(), std::declval<RRef<U>>()), std::true_type{}) {}
    template<typename...>
    static std::false_type test(...);
};
} // detail

/**
 * @defgroup basic_concepts Basic concepts submodule
 * @ingroup concepts
 *
 * @brief Concepts involving constructibility and operational semantics.
 *
 * @details This is a collection of concepts that deal mainly with properties
 * of objects such as constructibility (e.g. DefaultConstructible, MoveConstructible),
 * and other semantics relating to types such as Reference, LessThanComparable,
 * Integral, etc.
 */

/**
 * @ingroup basic_concepts
 * @brief Checks if a type is default constructible
 * @details A Unary concept to check if a type is default
 * constructible.
 *
 * This means that the following code must be
 * valid:
 *
 * @code
 * T t; // default constructed
 * @endcode
 *
 * @tparam T Type to check
 */
template<typename T>
struct DefaultConstructible : std::is_default_constructible<Bare<T>> {};

/**
 * @ingroup basic_concepts
 * @brief Checks if a type is move constructible
 * @details A Unary concept to check if a type is
 * move constructible.
 *
 * This means that the following code must be valid:
 *
 * @code
 * // other_var is of type T
 * T var(std::move(other_var)); // move constructor
 * @endcode
 *
 * @tparam T Type to check
 */
template<typename T>
struct MoveConstructible : std::is_move_constructible<Bare<T>> {};

/**
 * @ingroup basic_concepts
 * @brief Checks if a type is copy constructible
 * @details A Unary concept to check if a type is
 * copy constructible.
 *
 * This means that the following code must be valid:
 *
 * @code
 * // other_var is of type T
 * T var(other_var); // copy constructor
 * @endcode
 *
 * @tparam T Type to check
 */
template<typename T>
struct CopyConstructible : std::is_copy_constructible<Bare<T>> {};

/**
 * @ingroup basic_concepts
 * @brief Checks if a type is move assignable
 * @details A Unary concept to check if a type is
 * move assignable.
 *
 * This means that the following code must be valid:
 *
 * @code
 * // other_var is of type T
 * T var = std::move(other_var); // move assignment
 * @endcode
 *
 * @tparam T Type to check
 */
template<typename T>
struct MoveAssignable : std::is_move_assignable<Bare<T>> {};

/**
 * @ingroup basic_concepts
 * @brief Checks if a type is copy assignable
 * @details A Unary concept to check if a type is
 * copy assignable.
 *
 * This means that the following code must be valid:
 *
 * @code
 * // other_var is of type T
 * T var = other_var; // copy assignment
 * @endcode
 *
 * @tparam T Type to check
 */
template<typename T>
struct CopyAssignable : std::is_copy_assignable<Bare<T>> {};

/**
 * @ingroup basic_concepts
 * @brief Checks if a type has move assignment and constructor
 * @details A Unary concept to check if a type has a move assignment
 * and a move constructor.
 *
 * This means that the following code must be valid:
 *
 * @code
 * // other_var is of type T
 * T var(std::move(other_var)); // move constructor
 * T new_var = std::move(var); // move assignment
 * @endcode
 *
 * @tparam T Type to check
 */
template<typename T>
struct Movable : And<MoveAssignable<T>, MoveConstructible<T>> {};

/**
 * @ingroup basic_concepts
 * @brief Checks if a type has copy assignment and constructor
 * @details A Unary concept to check if a type has a copy assignment
 * and a copy constructor.
 *
 * This means that the following code must be valid:
 *
 * @code
 * // other_var is of type T
 * T var(other_var); // copy constructor
 * T new_var = var; // copy assignment
 * @endcode
 *
 * @tparam T Type to check
 */
template<typename T>
struct Copyable : And<CopyAssignable<T>, CopyConstructible<T>> {};

/**
 * @ingroup basic_concepts
 * @brief Checks if a type has move assignment and copy assignment.
 * @details A Unary concept to check if a type has a copy assignment
 * and a move assignment.
 *
 * This means that the following code must be valid:
 *
 * @code
 * // other_var is of type T
 * T var = other_var; // copy assignment
 * T new_var = std::move(var); // move assignment
 * @endcode
 *
 * @tparam T Type to check
 */
template<typename T>
struct Assignable : And<MoveAssignable<T>, CopyAssignable<T>> {};

/**
 * @ingroup basic_concepts
 * @brief Checks if a type has a destructor
 * @details A Unary concept to check if a type has a destructor.
 *
 * Classes without a destructor can typically not be instantiated with
 * automatic storage duration, so this would be useful to check in those
 * situations where this is a requirement. Types without a destructor are
 * often pretty rare, however.
 *
 * @tparam T Type to check
 */
template<typename T>
struct Destructible : std::is_destructible<Bare<T>> {};

/**
 * @ingroup basic_concepts
 * @brief Checks if a type is constructible.
 * @details An uncategorised concept that checks if a type can be constructed.
 *
 * Classes with a constructor can have multiple different ways of being constructed.
 * If you rely on a certain way to construct a type, then this concept can be used to
 * assert that a type meets those constructibility requirements. For example, if you want
 * the type of `MyClass` to have an `MyClass(int, int)` constructor, then you would check it
 * with `Constructible<MyClass, int, int>`.
 *
 * @tparam T Type to check
 * @tparam Args Types of the parameters expected in the constructor. If empty,
 * default constructor is assumed.
 */
template<typename T, typename... Args>
struct Constructible : std::is_constructible<Bare<T>, Args...> {};

/**
 * @ingroup basic_concepts
 * @brief Checks if a type has standard layout
 * @details A Unary concept that checks if a type has standard layout.
 *
 * A type with standard layout meets the following requirements:
 *
 * - No virtual functions.
 * - No virtual base classes.
 * - Same access control for all non-static data members.
 * - No base classes that don't meet the StandardLayout concept.
 * - No non-static members that don't meet the StandardLayout concept.
 * - No base class of the same type as the first non-static data member.
 *
 * @tparam T Type to check
 */
template<typename T>
struct StandardLayout : std::is_standard_layout<Bare<T>> {};

/**
 * @ingroup basic_concepts
 * @brief Checks if a type is a plain-old-data (POD).
 * @details A Unary concept that checks if a type is a plain old data (POD) type.
 *
 * A type that is a POD is a type that meets StandardLayout and is trivial.
 *
 * @tparam T Type to check
 */
template<typename T>
struct POD : std::is_pod<Bare<T>> {};

/**
 * @ingroup basic_concepts
 * @brief Checks if a type is semi-regular.
 * @details A Unary concept that checks if a type is semi-regular.
 *
 * A type that is semi-regular is one that can be usually used in a regular way.
 * In order to be a semi-regular type, a type must meet the Movable, Copyable, and
 * DefaultConstructible concepts.
 *
 * @tparam T Type to check
 */
template<typename T>
struct Semiregular : And<Movable<T>, Copyable<T>, DefaultConstructible<T>> {};

/**
 * @ingroup basic_concepts
 * @brief Checks if a type is l-value swappable.
 * @details A Binary concept that checks if a type is l-value swappable.
 *
 * To be l-value swappable then `std::swap(x, y)` must be valid where x and
 * y are l-values.
 *
 * @tparam T Left type to check
 * @tparam U Right type to check
 */
template<typename T, typename U = T>
struct LValueSwappable : TraitOf<detail::is_lvalue_swappable, T, U> {};

/**
 * @ingroup basic_concepts
 * @brief Checks if a type is r-value swappable.
 * @details A Binary concept that checks if a type is r-value swappable.
 *
 * To be r-value swappable then `std::swap(x, y)` must be valid where x and
 * y are r-values.
 *
 * @tparam T Left type to check
 * @tparam U Right type to check
 */
template<typename T, typename U = T>
struct RValueSwappable : TraitOf<detail::is_rvalue_swappable, T, U> {};

/**
 * @ingroup basic_concepts
 * @brief Checks if a type is swappable.
 * @details A Binary concept that checks if a type is swappable.
 *
 * To be swappable, then LValueSwappable and RValueSwappable must be valid.
 * That is to say, `swap(x, y)` must be valid for both l-values and r-values.
 *
 * @tparam T Left type to check
 * @tparam U Right type to check
 */
template<typename T, typename U = T>
struct Swappable : And<LValueSwappable<T, U>, RValueSwappable<T, U>> {};

/**
 * @ingroup basic_concepts
 * @brief Checks if a type can be convertible to bool.
 * @details A Unary concept that checks if a type can be convertible to bool.
 *
 * Convertibility to bool is helpful if you want to use the code as a predicate
 * or in boolean conditions. The following are situations where ContextualBool would
 * assert are valid:
 *
 * @code
 * if(X) {
 * }
 *
 * while(X) {
 * }
 *
 * else if(X) {
 * }
 * @endcode
 *
 * where X is an instance of type T.
 *
 * @tparam T Type to check
 */
template<typename T>
struct ContextualBool : std::is_constructible<bool, T> {};

/**
 * @ingroup basic_concepts
 * @brief Checks if a type is an integral type.
 * @details A Unary concept to check if a type is an integral type.
 *
 * This concept delegates the work to `std::is_integral<T>`. An integral type is
 * one of the following:
 *
 * `bool`, `char`, `wchar_t`, `char16_t`, `char32_t`, `long`,
 * `long long`, `short`, and `int`.
 *
 * Their `const`, `volatile`, `signed`, and `unsigned` variations are
 * valid as well.
 *
 * @tparam T Type to check.
 */
template<typename T>
struct Integral : std::is_integral<T> {};

/**
 * @ingroup basic_concepts
 * @brief Checks if a type is a floating point type.
 * @details A Unary concept to check if a type is a floating point type.
 *
 * This concept delegates the work to `std::is_floating_point<T>`. A floating point type
 * is `double`, `float`, or `long double`.
 *
 * Their `const` and `volatile` variations are valid as well.
 *
 * @tparam T Type to check.
 */
template<typename T>
struct FloatingPoint : std::is_floating_point<T> {};

/**
 * @ingroup basic_concepts
 * @brief Checks if a type is signed.
 * @details A Unary concept to check if a type is signed.
 *
 * An Integral type is `signed` by default. e.g. `int` is equivalent to
 * `signed int`.
 *
 * @tparam T Type to check.
 */
template<typename T>
struct Signed : std::is_signed<T> {};

/**
 * @ingroup basic_concepts
 * @brief Checks if a type is unsigned.
 * @details A Unary concept to check if a type is unsigned.
 *
 * An Integral type is `unsigned` if it has the modifier appended to it, e.g.
 * `unsigned int` is obviously unsigned.
 *
 * @tparam T Type to check.
 */
template<typename T>
struct Unsigned : std::is_unsigned<T> {};

/**
 * @ingroup basic_concepts
 * @brief Checks if a type is floating point or integral.
 * @details A Unary concept that checks if a type is an arithmetic type.
 *
 * An arithmetic type is a type that you could do basic mathematical arithmetic on.
 * These are the types that meet Integral or FloatingPoint.
 *
 * @tparam T Type to check
 */
template<typename T>
struct Arithmetic : std::is_arithmetic<T> {};

/**
 * @ingroup basic_concepts
 * @brief Checks if a type is a fundamental type.
 * @details A Unary concept that checks if a type is fundamental.
 *
 * A fundamental type is one that is either:
 *
 * - Arithmetic
 * - `void`
 * - `nullptr_t`
 *
 * @tparam T Type to check
 */
template<typename T>
struct Fundamental : std::is_fundamental<T> {};

/**
 * @ingroup basic_concepts
 * @brief Checks if a type is a compound type.
 * @details A Unary concept that checks if a type is compound.
 *
 * A compound type is the opposite of Fundamental. It's either:
 *
 * - a pointer
 * - an array
 * - an enumerator
 * - a reference
 * - a class (or struct)
 * - a union
 *
 * @tparam T Type to check
 */
template<typename T>
struct Compound : std::is_compound<T> {};

/**
 * @ingroup basic_concepts
 * @brief Checks if a type is a pointer.
 * @details A Unary concept to check if a type is a pointer.
 *
 * This concept delegates the work to `std::is_pointer<T>`.
 *
 * @tparam T Type to check.
 */
template<typename T>
struct Pointer : std::is_pointer<T> {};

/**
 * @ingroup basic_concepts
 * @brief Checks if a type is a l-value reference.
 * @details A Unary concept to check if a type is a l-value reference.
 *
 * This concept delegates the work to `std::is_lvalue_reference<T>`.
 *
 * @tparam T Type to check.
 */
template<typename T>
struct LValueReference : std::is_lvalue_reference<T> {};

/**
 * @ingroup basic_concepts
 * @brief Checks if a type is a r-value reference.
 * @details A Unary concept to check if a type is a r-value reference.
 *
 * This concept delegates the work to `std::is_rvalue_reference<T>`.
 *
 * @tparam T Type to check.
 */
template<typename T>
struct RValueReference : std::is_rvalue_reference<T> {};

/**
 * @ingroup basic_concepts
 * @brief Checks if a type is a reference.
 * @details A Unary concept to check if a type is a l-value reference.
 *
 * This concept delegates the work to `std::is_reference<T>`. A reference
 * can be either an r-value (T&&) or l-value (T&) reference.
 *
 * @tparam T Type to check.
 */
template<typename T>
struct Reference : std::is_reference<T> {};

namespace detail {
struct is_less_than_comparable {
    template<typename T, typename U,
             typename LT = decltype(std::declval<T&>() < std::declval<U&>()),
             TrueIf<ContextualBool<LT>>...>
    static std::true_type test(int);
    template<typename...>
    static std::false_type test(...);
};

struct is_equality_comparable {
    template<typename T, typename U,
             typename EQ = decltype(std::declval<T&>() == std::declval<U&>()),
             typename NE = decltype(std::declval<T&>() != std::declval<U&>()),
             TrueIf<ContextualBool<EQ>, ContextualBool<NE>>...>
    static std::true_type test(int);
    template<typename...>
    static std::false_type test(...);
};

struct is_comparable {
    template<typename T, typename U,
             typename LT = decltype(std::declval<T&>() <  std::declval<U&>()),
             typename LE = decltype(std::declval<T&>() <= std::declval<U&>()),
             typename GT = decltype(std::declval<T&>() >  std::declval<U&>()),
             typename GE = decltype(std::declval<T&>() >= std::declval<U&>()),
             TrueIf<ContextualBool<LT>, ContextualBool<LE>, ContextualBool<GT>, ContextualBool<GE>>...>
    static std::true_type test(int);
    template<typename...>
    static std::false_type test(...);
};

template<typename Pointer>
struct is_np_assignable_impl {
private:
    Pointer a;
    std::nullptr_t np = nullptr;
    const std::nullptr_t npc = nullptr;
public:
    static const bool one = std::is_same<Pointer&, decltype(a = np)>();
    static const bool two = std::is_same<Pointer&, decltype(a = npc)>();
    static const bool three = Constructible<Pointer, std::nullptr_t>();
    static const bool four = Constructible<Pointer, const std::nullptr_t>();
    static const bool value = one && two && three && four;
};

template<typename T>
struct is_np_assign : std::integral_constant<bool, is_np_assignable_impl<T>::value> {};

struct is_incrementable {
    template<typename T,
             typename Po = decltype(std::declval<T&>().operator++(0)),
             typename Pr = decltype(std::declval<T&>().operator++()),
             TrueIf<std::is_same<Pr, LRef<T>>>...>
    static std::true_type test(int);
    template<typename...>
    static std::false_type test(...);
};

struct is_decrementable {
    template<typename T,
             typename Po = decltype(std::declval<T&>().operator--(0)),
             typename Pr = decltype(std::declval<T&>().operator--()),
             TrueIf<std::is_same<Pr, LRef<T>>>...>
    static std::true_type test(int);
    template<typename...>
    static std::false_type test(...);
};

struct is_dereferenceable  {
    template<typename T,
             typename Re = decltype(std::declval<T&>().operator*()),
             typename Ar = decltype(std::declval<T&>().operator->())>
    static std::true_type test(int);
    template<typename...>
    static std::false_type test(...);
};
} // detail

/**
 * @ingroup basic_concepts
 * @brief Checks if a type can be compared with `<`.
 * @details A Binary concept that checks if a type can be compared
 * with `operator<`.
 *
 * In order for a type to meet this concept, the following expression
 * has to be valid:
 *
 * @code
 * bool b = x < y;
 * @endcode
 *
 * Where x is an instance of T, and y is an instance of U.
 *
 * The result of the expression must return `bool` or something convertible to
 * `bool`.
 *
 * @tparam T Left type to check
 * @tparam U Right type to check
 */
template<typename T, typename U = T>
struct LessThanComparable : TraitOf<detail::is_less_than_comparable, T, U> {};

/**
 * @ingroup basic_concepts
 * @brief Checks if a type can be checked for equality.
 * @details A Binary concept that checks if a type can be compared
 * with `operator==` and `operator!=`.
 *
 * In order for a type to meet this concept, the following expressions
 * has to be valid:
 *
 * @code
 * bool b = x == y;
 * bool c = x != y;
 * @endcode
 *
 * Where x is an instance of T, and y is an instance of U.
 *
 * The result of the expressions must return `bool` or something convertible to
 * `bool`.
 *
 * @tparam T Left type to check
 * @tparam U Right type to check
 */
template<typename T, typename U = T>
struct EqualityComparable : TraitOf<detail::is_equality_comparable, T, U> {};

/**
 * @ingroup basic_concepts
 * @brief Checks if a type is regular.
 * @details A Unary concept that checks if a type is regular.
 *
 * A type that is regular is one that can be used in a normal way.
 * In order to be a regular type, a type must meet the Semiregular
 * and EqualityComparable concepts.
 *
 * @tparam T Type to check
 */
template<typename T>
struct Regular : And<Semiregular<T>, EqualityComparable<T>> {};

/**
 * @ingroup basic_concepts
 * @brief Checks if a type can be compared.
 * @details A Binary concept that checks if a type can be compared
 * with `operator<`, `operator<=`, `operator>`, and `operator>=`.
 *
 * In order for a type to meet this concept, the following expressions
 * has to be valid:
 *
 * @code
 * bool a = x < y;
 * bool b = x > y;
 * bool c = x >= y;
 * bool d = x <= y;
 * @endcode
 *
 * Where x is an instance of T, and y is an instance of U.
 *
 * The result of the expressions must return `bool` or something convertible to
 * `bool`.
 *
 * @tparam T Left type to check
 * @tparam U Right type to check
 */
template<typename T, typename U = T>
struct Comparable : TraitOf<detail::is_comparable, T, U> {};

/**
 * @ingroup basic_concepts
 * @brief Checks if a type is pointer-like
 * @details A Unary concept to check if a type is a pointer-like type
 * that can be compared with `nullptr_t`.
 *
 * A NullablePointer must meet the concepts of:
 *
 * - DefaultConstructible
 * - MoveConstructible
 * - CopyConstructible
 * - CopyAssignable
 * - Destructible
 *
 * In addition to these concepts, the following expressions must be
 * valid:
 *
 * @code
 * T x(const nullptr);
 * T y(nullptr);
 * T a = nullptr;
 * T b = const nullptr;
 * b = nullptr;
 * bool c = b != nullptr;
 * bool d = b == nullptr;
 * bool e = b;
 * @endcode
 *
 * Contrary to belief, `std::unique_ptr` does not meet this concept.
 * `std::shared_ptr` however, does.
 *
 * @tparam T Type to check
 */
template<typename T>
struct NullablePointer :  And<DefaultConstructible<T>,
                              CopyConstructible<T>,
                              CopyAssignable<T>,
                              Destructible<T>,
                              ContextualBool<T>,
                              EqualityComparable<T, std::nullptr_t>,
                              EqualityComparable<std::nullptr_t, T>,
                              detail::is_np_assign<T>> {};

/**
 * @ingroup basic_concepts
 * @brief Checks if a type can be incremented.
 * @details A Unary concept that checks if a type can be incremented.
 *
 * In order for a type to meet this concept, the following expressions
 * has to be valid:
 *
 * @code
 * ++x;
 * x++;
 * @endcode
 *
 * Where x is an instance of T.
 *
 * @tparam T Type to check
 */
template<typename T>
struct Incrementable : Or<Fundamental<T>, Pointer<T>, TraitOf<detail::is_incrementable, T>> {};

/**
 * @ingroup basic_concepts
 * @brief Checks if a type can be decremented.
 * @details A Unary concept that checks if a type can be decremented.
 *
 * In order for a type to meet this concept, the following expressions
 * has to be valid:
 *
 * @code
 * --x;
 * x--;
 * @endcode
 *
 * Where x is an instance of T.
 *
 * @tparam T Type to check
 */
template<typename T>
struct Decrementable : Or<Fundamental<T>, Pointer<T>, TraitOf<detail::is_decrementable, T>> {};

/**
 * @ingroup basic_concepts
 * @brief Checks if a type can be dereferenced.
 * @details A Unary concept that checks if a type can be dereferenced.
 *
 * In order for a type to meet this concept, the following expressions
 * has to be valid:
 *
 * @code
 * auto& a = *x;
 * @endcode
 *
 * Where x is an instance of T.
 *
 * The returned type must be an l-value reference.
 *
 * @tparam T Left type to check
 */
template<typename T>
struct Dereferenceable : Or<Pointer<T>, TraitOf<detail::is_dereferenceable, T>> {};
} // concepts
} // gears

#endif // GEARS_CONCEPTS_BASIC_HPP
