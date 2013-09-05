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
namespace basic_detail {
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
} // basic_detail

template<typename T>
struct DefaultConstructible : std::is_default_constructible<NoRef<T>> {};

template<typename T>
struct MoveConstructible : std::is_move_constructible<NoRef<T>> {};

template<typename T>
struct CopyConstructible : std::is_copy_constructible<NoRef<T>> {};

template<typename T>
struct MoveAssignable : std::is_move_assignable<NoRef<T>> {};

template<typename T>
struct CopyAssignable : std::is_copy_assignable<NoRef<T>> {};

template<typename T>
struct Movable : And<MoveAssignable<T>, MoveConstructible<T>> {};

template<typename T>
struct Copyable : And<CopyAssignable<T>, CopyConstructible<T>> {};

template<typename T>
struct Assignable : And<MoveAssignable<T>, CopyAssignable<T>> {};

template<typename T>
struct Destructible : std::is_destructible<NoRef<T>> {};

template<typename T, typename... Args>
struct Constructible : std::is_constructible<NoRef<T>, Args...> {};

template<typename T>
struct StandardLayout : std::is_standard_layout<NoRef<T>> {};

template<typename T>
struct POD : std::is_pod<NoRef<T>> {};

template<typename T>
struct Semiregular : And<Movable<T>, Copyable<T>, DefaultConstructible<T>> {}; 

template<typename T, typename U = T>
struct LValueSwappable : TraitOf<basic_detail::is_lvalue_swappable, T, U> {};

template<typename T, typename U = T>
struct RValueSwappable : TraitOf<basic_detail::is_rvalue_swappable, T, U> {};

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

namespace basic_detail {
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
} // basic_detail

template<typename T, typename U = T>
struct LessThanComparable : TraitOf<basic_detail::is_less_than_comparable, T, U> {};

template<typename T, typename U = T>
struct EqualityComparable : TraitOf<basic_detail::is_equality_comparable, T, U> {};

template<typename T>
struct Regular : And<Semiregular<T>, EqualityComparable<T>> {};

template<typename T, typename U = T>
struct Comparable : TraitOf<basic_detail::is_comparable, T, U> {};

template<typename T>
struct NullablePointer :  And<DefaultConstructible<T>, 
                              CopyConstructible<T>, 
                              CopyAssignable<T>, 
                              Destructible<T>,
                              EqualityComparable<T, std::nullptr_t>, 
                              EqualityComparable<std::nullptr_t, T>, 
                              basic_detail::is_np_assign<T>> {};

template<typename T>
struct Incrementable : Or<Fundamental<T>, Pointer<T>, TraitOf<basic_detail::is_incrementable, T>> {};

template<typename T>
struct Decrementable : Or<Fundamental<T>, Pointer<T>, TraitOf<basic_detail::is_decrementable, T>> {};

template<typename T>
struct Dereferenceable : Or<Pointer<T>, TraitOf<basic_detail::is_dereferenceable, T>> {};
} // gears

#endif // GEARS_CONCEPTS_BASIC_HPP