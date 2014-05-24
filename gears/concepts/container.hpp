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

#ifndef GEARS_CONCEPTS_CONTAINER_HPP
#define GEARS_CONCEPTS_CONTAINER_HPP

#include "iterator.hpp"

namespace gears {
namespace concepts {
namespace detail {
struct is_container {
    template<typename C,
             typename T  = typename Bare<C>::value_type,
             typename R  = typename Bare<C>::reference,
             typename Cr = typename Bare<C>::const_reference,
             typename It = typename Bare<C>::iterator,
             typename Ci = typename Bare<C>::const_iterator,
             typename Dt = typename Bare<C>::difference_type,
             typename St = typename Bare<C>::size_type,
             typename B  = decltype(std::declval<LRef<C>>().begin()),
             typename E  = decltype(std::declval<LRef<C>>().end()),
             typename Cb = decltype(std::declval<LRef<C>>().cbegin()),
             typename Ce = decltype(std::declval<LRef<C>>().cend()),
             typename Sw = decltype(std::declval<LRef<C>>().swap(std::declval<LRef<C>>())),
             typename Si = decltype(std::declval<LRef<C>>().size()),
             typename Ms = decltype(std::declval<LRef<C>>().max_size()),
             typename Em = decltype(std::declval<LRef<C>>().empty()),
             TrueIf<ContextualBool<Em>,         std::is_same<Si, St>, 
                    std::is_same<Ms, St>,       std::is_same<Cb, Ci>, 
                    std::is_same<Ce, Ci>,       std::is_convertible<It, Ci>, 
                    std::is_convertible<B, Ci>, std::is_convertible<E, Ci>,
                    ForwardIterator<It>>...>
    static std::true_type test(int);
    template<typename...>
    static std::false_type test(...);
};

struct is_forward_list {
    template<typename C,
             typename T = typename Bare<C>::value_type,
             typename It = typename Bare<C>::const_iterator,
             typename Ia = decltype(std::declval<LRef<C>>().insert_after(std::declval<It&>(), std::declval<T&>())),
             typename Em = decltype(std::declval<LRef<C>>().emplace_after(std::declval<It&>())),
             typename Ea = decltype(std::declval<LRef<C>>().erase_after(std::declval<It&>())),
             typename Sa = decltype(std::declval<LRef<C>>().splice_after(std::declval<It&>(), std::declval<LRef<C>>()))>
    static std::true_type test(int);
    template<typename...>
    static std::false_type test(...);
};

struct is_reversible {
    template<typename C,
             typename Ri = typename Bare<C>::reverse_iterator,
             typename Cr = typename Bare<C>::const_reverse_iterator,
             typename Rb = decltype(std::declval<LRef<C>>().rbegin()),
             typename Re = decltype(std::declval<LRef<C>>().rend()),
             typename Cb = decltype(std::declval<LRef<C>>().crbegin()),
             typename Ce = decltype(std::declval<LRef<C>>().crend()),
             TrueIf<std::is_convertible<Ri, Cr>, std::is_convertible<Rb, Cr>,
                    std::is_convertible<Re, Cr>, std::is_same<Cb, Cr>,
                    std::is_same<Ce, Cr>>...>
    static std::true_type test(int);
    template<typename...>
    static std::false_type test(...);
};

struct is_allocator_aware {
    template<typename C,
             typename A = typename Bare<C>::allocator_type,
             typename G = decltype(std::declval<LRef<C>>().get_allocator()),
             TrueIf<std::is_same<A, G>>...>
    static std::true_type test(int);
    template<typename...>
    static std::false_type test(...);
};

struct is_sequence_container {
    template<typename C,
             typename B = Bare<C>,
             typename T  = typename B::value_type,
             typename St = typename B::size_type,
             typename It = typename B::iterator,
             typename C1 = decltype(B(St(), std::declval<LRef<T>>())),
             typename C2 = decltype(B(std::declval<It&>(), std::declval<It&>())),
             typename E1 = decltype(std::declval<B&>().emplace(std::declval<It&>())),
             typename E2 = decltype(std::declval<B&>().emplace(std::declval<It&>(), std::declval<LRef<T>>())),
             typename I  = decltype(std::declval<B&>().insert(std::declval<It&>(), St(), std::declval<LRef<T>>())),
             typename I2 = decltype(std::declval<B&>().insert(std::declval<It&>(), std::declval<It&>(), std::declval<It&>())),
             typename E3 = decltype(std::declval<B&>().erase(std::declval<It&>())),
             typename E4 = decltype(std::declval<B&>().erase(std::declval<It&>(), std::declval<It&>())),
             typename Cl = decltype(std::declval<B&>().clear()),
             typename A1 = decltype(std::declval<B&>().assign(std::declval<It&>(), std::declval<It&>())),
             typename A2 = decltype(std::declval<B&>().assign(St(), std::declval<LRef<T>>()))>
    static std::true_type test(int);
    template<typename...>
    static std::false_type test(...);
};

struct is_array_sequence {
    template<typename C>
    static auto test(int) -> decltype(std::declval<LRef<C>>().fill(0), std::true_type{}) {}
    template<typename>
    static std::false_type test(...);
};

struct is_associative_container {
    template<typename C,
             typename B  = Bare<C>,
             typename Kt = typename B::key_type,
             typename T  = typename B::value_type,
             typename It = typename B::iterator,
             typename Kc = typename B::key_compare,
             typename Vc = typename B::value_compare,
             typename St = typename B::size_type,
             typename KC = decltype(std::declval<B&>().key_comp()),
             typename VC = decltype(std::declval<B&>().value_comp()),
             typename Em = decltype(std::declval<B&>().emplace()),
             typename Eh = decltype(std::declval<B&>().emplace_hint(std::declval<It&>())),
             typename I1 = decltype(std::declval<B&>().insert(std::declval<T&>())),
             typename I2 = decltype(std::declval<B&>().insert(std::declval<It&>(), std::declval<T&>())),
             typename I3 = decltype(std::declval<B&>().insert(std::declval<It&>(), std::declval<It&>())),
             typename E1 = decltype(std::declval<B&>().erase(std::declval<Kt&>())),
             typename E2 = decltype(std::declval<B&>().erase(std::declval<It&>())),
             typename E3 = decltype(std::declval<B&>().erase(std::declval<It&>(), std::declval<It&>())),
             typename Cl = decltype(std::declval<B&>().clear()),
             typename Fi = decltype(std::declval<B&>().find(std::declval<Kt>())),
             typename Co = decltype(std::declval<B&>().count(std::declval<Kt>())),
             typename Lb = decltype(std::declval<B&>().lower_bound(std::declval<Kt>())),
             typename Ub = decltype(std::declval<B&>().upper_bound(std::declval<Kt>())),
             typename Er = decltype(std::declval<B&>().equal_range(std::declval<Kt>())),
             TrueIf<std::is_constructible<B, It, It, Kc>,
                    std::is_constructible<B, It, It>,
                    std::is_convertible<I2, It>,
                    std::is_convertible<E1, St>,
                    std::is_convertible<E2, It>,
                    std::is_convertible<E3, It>,
                    std::is_convertible<Fi, It>,
                    std::is_convertible<Co, St>,
                    std::is_convertible<Lb, It>,
                    std::is_convertible<Ub, It>>...>
    static std::true_type test(int);
    template<typename...>
    static std::false_type test(...);
};
} // detail

/**
 * @defgroup container_concepts Container concepts submodule
 * @ingroup concepts
 * 
 * @brief Concepts involving the standard C++ containers.
 * 
 * @details A collection of concepts that deal with the semantics of 
 * what entails a C++ standard container or a type that meets similar
 * requirements. 
 */


/**
 * @ingroup container_concepts
 * @brief Checks if a type is a container.
 * @details A Unary concept that checks if a type is a container.
 * 
 * A type that meets this concept must provide the following
 * typedefs:
 * 
 * - `value_type`
 * - `reference`
 * - `const_reference`
 * - `iterator`
 * - `const_iterator`
 * - `difference_type`
 * - `size_type`
 * 
 * It must meet the following concepts:
 * 
 * - Destructible
 * - Regular
 * - EqualityComparable
 * - Copyable
 * 
 * The following expressions must be valid:
 * 
 * @code 
 * auto a = x.begin();    // returns iterator or const_iterator
 * auto b = x.end();     //  returns iterator or const_iterator
 * auto c = x.cbegin()  //   returns const_iterator
 * auto d = x.cend()   //    returns const_iterator
 * x.swap(y);
 * auto e = x.size()     //  returns size_type
 * auto f = x.max_size(); // returns size_type
 * bool g = x.empty(); 
 * @endcode
 * 
 * Where x and y are instances of T.
 * 
 * There is a specialisation for `std::forward_list<T>` to make it a valid container.
 * 
 * @tparam T Type to check.
 */
template<typename T>
struct Container : And<Or<TraitOf<detail::is_container, T>, 
                          TraitOf<detail::is_forward_list, T>>, 
                       Regular<T>, 
                       EqualityComparable<T>,
                       Copyable<T>,
                       Destructible<T>> {};

/**
 * @ingroup container_concepts
 * @brief Checks if a type is a container that can be reversed.
 * @details A Unary concept that checks if a type is a container that can be reversed.
 * 
 * It must meet the Container concept. In addition to that, it must have the following
 * typedefs defined:
 * 
 * - `reverse_iterator`
 * - `const_reverse_iterator`
 * 
 * and the following expressions must be valid:
 * 
 * @code 
 * auto a = x.rbegin();    // returns reverse_iterator or const_reverse_iterator
 * auto b = x.rend();      // returns reverse_iterator or const_reverse_iterator
 * auto c = x.crbegin();   // returns const_reverse_iterator
 * auto d = x.crend();     // returns const_reverse_iterator
 * @endcode
 * 
 * Where x is an instance of T.
 * 
 * @tparam T Type to check
 */
template<typename T>
struct ReversibleContainer : And<Container<T>, TraitOf<detail::is_reversible, T>> {};

/**
 * @ingroup container_concepts
 * @brief Checks if a type is a container with an allocator.
 * @details A Unary concept that checks if a type is a container that has an allocator.
 * 
 * It must meet the Container concept. In addition to that, it must have the 
 * `allocator_type` typedef defined and the following expression must be valid:
 * 
 * @code 
 * auto a = x.get_allocator(); // returns allocator_type
 * @endcode
 * 
 * Where x is an instance of T.
 * 
 * @tparam T Type to check
 */
template<typename T>
struct AllocatorAwareContainer : And<Container<T>, TraitOf<detail::is_allocator_aware, T>> {};

/**
 * @ingroup container_concepts
 * @brief Checks if a type is a sequence container.
 * @details A Unary concept that checks if a type is a sequence container.
 * 
 * It must meet the Container concept. In addition to that, the following expressions 
 * must be valid:
 * 
 * @code 
 * T x(size_type{}, value_type{});
 * T y(iterator{}, iterator{});
 * iterator a = x.emplace(iterator{}, args...);
 * iterator b = x.insert(iterator{}, value_type{});
 * iterator c = x.insert(iterator{}, size_type{}, value_type{});
 * iterator d = x.insert(iterator{}, iterator{}, iterator{});
 * iterator e = x.erase(const_iterator{});
 * iterator f = x.erase(const_iterator{}, const_iterator{});
 * x.clear();
 * x.assign(iterator{}, iterator{});
 * x.assign(size_type{}, value_type{});
 * @endcode
 * 
 * @tparam T Type to check
 */
template<typename T>
struct SequenceContainer : And<Container<T>, Or<TraitOf<detail::is_sequence_container, T>, 
                                                TraitOf<detail::is_array_sequence, T>,
                                                TraitOf<detail::is_forward_list, T>>> {};

/**
 * @ingroup container_concepts
 * @brief Checks if a type is an associative container.
 * @details A Unary concept that checks if a type is an associative container.
 * 
 * It must meet the Container concept. In addition, the following typedefs must
 * be defined:
 * 
 * - `key_type`
 * - `key_compare`
 * - `value_compare`
 * 
 * and the following expressions must be valid:
 * 
 * @code 
 * T x;
 * key_compare kc = x.key_comp();
 * value_compare vc = x.value_comp(); 
 * iterator a = x.emplace(args...);
 * iterator b = x.emplace_hint(iterator{}, args...);
 * iterator c = x.insert(iterator{});
 * iterator d = x.insert(iterator{}, value_type{});
 * iterator e = x.insert(iterator{}, iterator{});
 * iterator f = x.erase(const_iterator{});
 * iterator g = x.erase(const_iterator{}, const_iterator{});
 * size_type h = x.erase(key_type{});
 * x.clear();
 * iterator i = x.find(key_type{});
 * size_type j = x.count(key_type{});
 * iterator k = x.lower_bound(key_type{});
 * iterator l = x.upper_bound(key_type{});
 * std::pair<iterator, iterator> m = x.equal_range(key_type{}); 
 * @endcode
 * 
 * @tparam T Type to check.
 */
template<typename T>
struct AssociativeContainer : And<Container<T>, TraitOf<detail::is_associative_container, T>> {};
} // concepts
} // gears

#endif // GEARS_CONCEPTS_CONTAINER_HPP
