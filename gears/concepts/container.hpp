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
namespace container_detail {
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
} // container_detail

template<typename T>
struct Container : And<Or<TraitOf<container_detail::is_container, T>, 
                          TraitOf<container_detail::is_forward_list, T>>, 
                       Regular<T>, 
                       Destructible<T>> {};

template<typename T>
struct ReversibleContainer : And<Container<T>, TraitOf<container_detail::is_reversible, T>> {};

template<typename T>
struct AllocatorAwareContainer : And<Container<T>, TraitOf<container_detail::is_allocator_aware, T>> {};

template<typename T>
struct SequenceContainer : And<Container<T>, Or<TraitOf<container_detail::is_sequence_container, T>, 
                                                TraitOf<container_detail::is_array_sequence, T>,
                                                TraitOf<container_detail::is_forward_list, T>>> {};
} // gears

#endif // GEARS_CONCEPTS_CONTAINER_HPP