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
} // container_detail

template<typename T>
struct Container : And<TraitOf<container_detail::is_container, T>, Regular<T>, Destructible<T>> {};
} // gears

#endif // GEARS_CONCEPTS_CONTAINER_HPP