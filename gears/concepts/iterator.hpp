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
namespace concepts {
namespace detail {
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
} // detail

/**
 * @defgroup iterator_concepts Iterator concepts submodule
 * @ingroup concepts
 * 
 * @brief Concepts involving iterators.
 * 
 * @details A collection of concepts dealing with iterators
 * used in the standard.
 * 
 * Concepts prefixed with Mutable in this collection mean that they are 
 * OutputIterators simultaneously.
 */

/**
 * @ingroup iterator_concepts
 * @brief Checks if a type is an iterator.
 * @details A Unary concept to check if a type is an iterator.
 * Note that this doesn't mean that it inherits from `std::iterator`.
 * 
 * In order to meet this concept, the type must meet these concepts:
 * 
 * - CopyConstructible
 * - CopyAssignable
 * - Destructible
 * - Dereferenceable
 * - Incrementable
 * 
 * @tparam T Type to check.
 */
template<typename T>
struct Iterator : And<CopyConstructible<T>, 
                      CopyAssignable<T>, 
                      Destructible<T>,
                      Dereferenceable<T>,
                      Incrementable<T>> {};

/**
 * @ingroup iterator_concepts
 * @brief Checks if a type is an input iterator.
 * @details A Unary concept that checks if a type is an input iterator.
 * Note that this doesn't mean it inherits from `std::iterator`.
 * 
 * In order to meet this concept, the type must be:
 * 
 * - Iterator
 * - EqualityComparable
 * 
 * @tparam T Type to check.
 */
template<typename T>
struct InputIterator : And<Iterator<T>, EqualityComparable<T>> {};

/**
 * @ingroup iterator_concepts
 * @brief Checks if a type is an output iterator.
 * @details A Unary concept that checks if a type is an output iterator.
 * Note that this doesn't mean it inherits from `std::iterator`.
 * 
 * In order to meet this concept, the type must be:
 * 
 * - Iterator
 * - Assignable
 * 
 * @tparam T Type to check.
 */
template<typename T>
struct OutputIterator : And<Iterator<T>, Assignable<T>> {};

/**
 * @ingroup iterator_concepts
 * @brief Checks if a type is a forward iterator.
 * @details A Unary concept that checks if a type is a forward iterator.
 * Note that this doesn't mean it inherits from `std::iterator`.
 * 
 * In order to meet this concept, the type must be:
 * 
 * - InputIterator
 * - DefaultConstructible
 * 
 * @tparam T Type to check.
 */
template<typename T>
struct ForwardIterator : And<InputIterator<T>, DefaultConstructible<T>> {};

/**
 * @ingroup iterator_concepts
 * @brief Checks if a type is a mutable forward iterator.
 * @details A Unary concept that checks if a type is a mutable forward iterator.
 * Note that this doesn't mean it inherits from `std::iterator`.
 * 
 * In order to meet this concept, the type must be:
 * 
 * - ForwardIterator
 * - Assignable
 * 
 * @tparam T Type to check.
 */
template<typename T>
struct MutableForwardIterator : And<ForwardIterator<T>, Assignable<T>> {};

/**
 * @ingroup iterator_concepts
 * @brief Checks if a type is a bidirectional iterator.
 * @details A Unary concept that checks if a type is a bidirectional iterator.
 * Note that this doesn't mean it inherits from `std::iterator`.
 * 
 * In order to meet this concept, the type must be:
 * 
 * - ForwardIterator
 * - Decrementable
 * 
 * @tparam T Type to check.
 */
template<typename T>
struct BidirectionalIterator : And<ForwardIterator<T>, Decrementable<T>> {};

/**
 * @ingroup iterator_concepts
 * @brief Checks if a type is a mutable bidirectional iterator.
 * @details A Unary concept that checks if a type is a mutable bidirectional iterator.
 * Note that this doesn't mean it inherits from `std::iterator`.
 * 
 * In order to meet this concept, the type must be:
 * 
 * - BidirectionalIterator
 * - Assignable
 * 
 * @tparam T Type to check.
 */
template<typename T>
struct MutableBidirectionalIterator : And<MutableForwardIterator<T>, Decrementable<T>> {};

/**
 * @ingroup iterator_concepts
 * @brief Checks if a type is a random access iterator.
 * @details A Unary concept that checks if a type is a random access iterator.
 * Note that this doesn't mean it inherits from `std::iterator`.
 * 
 * In order to meet this concept, the type must be:
 * 
 * - BidirectionalIterator
 * - Comparable
 * 
 * In addition, the following expressions must be valid:
 * 
 * @code 
 * auto& a = (x += n);
 * auto b = x + n;
 * auto c = n + x;
 * auto& d = (x -= n);
 * auto e = x - n;
 * auto f = n - x;
 * auto g = x - y;
 * auto& h = x[n];
 * @endcode
 * 
 * Where x and y are instances of T. 
 * 
 * @tparam T Type to check.
 */
template<typename T>
struct RandomAccessIterator : Or<Pointer<T>,
                                 And<BidirectionalIterator<T>, 
                                     Comparable<T>, 
                                     TraitOf<detail::is_random_access, T>>> {};

/**
 * @ingroup iterator_concepts
 * @brief Checks if a type is a mutable random access iterator.
 * @details A Unary concept that checks if a type is a mutable random access iterator.
 * Note that this doesn't mean it inherits from `std::iterator`.
 * 
 * In order to meet this concept, the type must be:
 * 
 * - RandomAccessIterator
 * - Assignable
 * 
 * @tparam T Type to check.
 */
template<typename T>
struct MutableRandomAccessIterator : And<RandomAccessIterator<T>, Assignable<T>> {};
} // concepts
} // gears

#endif // GEARS_CONCEPTS_ITERATOR_HPP