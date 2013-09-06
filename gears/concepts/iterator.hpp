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

#ifndef GEARS_CONCEPTS_ITERATOR_HPP
#define GEARS_CONCEPTS_ITERATOR_HPP

#include "basic.hpp"

namespace gears {
namespace iter_detail {
struct is_random_access {
    template<typename It,
             typename D = typename Bare<It>::difference_type,
             typename R = typename Bare<It>::reference,
             TrueIf<std::is_same<decltype(std::declval<It&>() += 2), It&>,
                    std::is_same<decltype(std::declval<It&>() + 2), It>,
                    std::is_same<decltype(2 + std::declval<It&>()), It>,
                    std::is_same<decltype(std::declval<It&>() -= 2), It&>,
                    std::is_same<decltype(std::declval<It&>() - 2), It>,
                    std::is_same<decltype(std::declval<It&>() - (std::declval<It&>() + 2)), D>,
                    std::is_convertible<decltype(std::declval<It&>()[2]), R>>...>
    static std::true_type test(int);
    template<typename...>
    static std::false_type test(...);
};
} // iter_detail

template<typename T>
struct Iterator : And<CopyConstructible<T>, 
                      CopyAssignable<T>, 
                      Destructible<T>,
                      Dereferenceable<T>,
                      Incrementable<T>> {};

template<typename T>
struct InputIterator : And<Iterator<T>, EqualityComparable<T>> {};

template<typename T>
struct OutputIterator : And<Iterator<T>, Assignable<T>> {};

template<typename T>
struct ForwardIterator : And<InputIterator<T>, DefaultConstructible<T>> {};

template<typename T>
struct MutableForwardIterator : And<ForwardIterator<T>, Assignable<T>> {};

template<typename T>
struct BidirectionalIterator : And<ForwardIterator<T>, Decrementable<T>> {};

template<typename T>
struct MutableBidirectionalIterator : And<MutableForwardIterator<T>, Decrementable<T>> {};

template<typename T>
struct RandomAccessIterator : Or<Pointer<T>,
                                 And<BidirectionalIterator<T>, 
                                     Comparable<T>, 
                                     TraitOf<iter_detail::is_random_access, T>>> {};

template<typename T>
struct MutableRandomAccessIterator : And<RandomAccessIterator<T>, Assignable<T>> {};
} // gears

#endif // GEARS_CONCEPTS_ITERATOR_HPP