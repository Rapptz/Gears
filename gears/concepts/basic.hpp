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

#ifndef GEARS_CONCEPTS_BASIC_HPP
#define GEARS_CONCEPTS_BASIC_HPP

#include "alias.hpp"
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
<<<<<<< HEAD
 * and other semantics relating to types such as Reference, LessThanComparable, 
=======
 * and other semantics relating to types such as Reference, LessThanConstructible, 
>>>>>>> a8c3fd363a0f368ebf5ec78012dd2ecec67b3c4c
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
<<<<<<< HEAD
 * @ingroup basic_concepts
=======
>>>>>>> a8c3fd363a0f368ebf5ec78012dd2ecec67b3c4c
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
<<<<<<< HEAD
 * @ingroup basic_concepts
=======
>>>>>>> a8c3fd363a0f368ebf5ec78012dd2ecec67b3c4c
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
<<<<<<< HEAD
 * @ingroup basic_concepts
=======
>>>>>>> a8c3fd363a0f368ebf5ec78012dd2ecec67b3c4c
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
<<<<<<< HEAD
 * @ingroup basic_concepts
=======
>>>>>>> a8c3fd363a0f368ebf5ec78012dd2ecec67b3c4c
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

template<typename T, typename U = T>
struct LValueSwappable : TraitOf<detail::is_lvalue_swappable, T, U> {};

template<typename T, typename U = T>
struct RValueSwappable : TraitOf<detail::is_rvalue_swappable, T, U> {};

template<typename T, typename U = T>
struct Swappable : And<LValueSwappable<T, U>, RValueSwappable<T, U>> {};

template<typename T>
struct ContextualBool : std::is_constructible<bool, T> {};

template<typename T>
struct Integral : std::is_integral<T> {};

template<typename T>
struct FloatingPoint : std::is_floating_point<T> {};

template<typename T>
struct Signed : std::is_signed<T> {};

template<typename T>
struct Unsigned : std::is_unsigned<T> {};

template<typename T>
struct Arithmetic : std::is_arithmetic<T> {};

template<typename T>
struct Fundamental : std::is_fundamental<T> {};

template<typename T>
struct Compound : std::is_compound<T> {};

template<typename T>
struct Pointer : std::is_pointer<T> {};

template<typename T>
struct LValueReference : std::is_lvalue_reference<T> {};

template<typename T>
struct RValueReference : std::is_rvalue_reference<T> {};

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

template<typename T, typename U = T>
struct LessThanComparable : TraitOf<detail::is_less_than_comparable, T, U> {};

template<typename T, typename U = T>
struct EqualityComparable : TraitOf<detail::is_equality_comparable, T, U> {};

template<typename T>
struct Regular : And<Semiregular<T>, EqualityComparable<T>> {};

template<typename T, typename U = T>
struct Comparable : TraitOf<detail::is_comparable, T, U> {};

template<typename T>
struct NullablePointer :  And<DefaultConstructible<T>, 
                              CopyConstructible<T>, 
                              CopyAssignable<T>, 
                              Destructible<T>,
                              EqualityComparable<T, std::nullptr_t>, 
                              EqualityComparable<std::nullptr_t, T>, 
                              detail::is_np_assign<T>> {};

template<typename T>
struct Incrementable : Or<Fundamental<T>, Pointer<T>, TraitOf<detail::is_incrementable, T>> {};

template<typename T>
struct Decrementable : Or<Fundamental<T>, Pointer<T>, TraitOf<detail::is_decrementable, T>> {};

template<typename T>
struct Dereferenceable : Or<Pointer<T>, TraitOf<detail::is_dereferenceable, T>> {};
} // concepts
} // gears

#endif // GEARS_CONCEPTS_BASIC_HPP