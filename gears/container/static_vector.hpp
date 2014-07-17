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

#ifndef GEARS_CONTAINER_STATIC_VECTOR_HPP
#define GEARS_CONTAINER_STATIC_VECTOR_HPP

#include <type_traits>
#include <iterator>
#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <memory>

namespace gears {
namespace container {
/**
 * @ingroup container
 * @brief A vector with a static size.
 * @details Implements a vector with a static size. The semantics
 * are nearly equivalent to those of `std::vector`, except with a
 * static size similar to `std::array`. When the capacity is exceeded,
 * an exception of type `std::out_of_range` is typically thrown.
 * This container meets the requirement of Container. Its iterators
 * meet the requirement of MutableRandomAccessIterator. Unlike
 * `std::vector`, the contents of the array are not dynamically allocated.
 * Rather they are stored in automatic storage and then initialised when
 * requested. That is, the data starts out uninitialised.
 *
 * Example usage:
 *
 * @code
 * #include <gears/container/static_vector.hpp>
 * #include <iostream>
 *
 * using namespace gears::container;
 *
 * struct example {
 * private:
 *     int x;
 * public:
 *     example(int x): x(x) {}
 *
 *     void print() const {
 *         std::cout << x << ' ';
 *     }
 * };
 *
 * int main() {
 *     static_vector<example, 10> examples;
 *
 *     examples.emplace_back(10);
 *     examples.emplace_back(20);
 *
 *     for(unsigned i = examples.size(); i < examples.max_size(); ++i) {
 *         examples.emplace_back(10 + i * 10);
 *     }
 *
 *     for(auto&& ex : examples) {
 *         ex.print();
 *     }
 * }
 * @endcode
 *
 * Output:
 * <pre>
 * 10 20 30 40 50 60 70 80 90 100
 * </pre>
 *
 * @tparam T Type to hold.
 * @tparam N Maximum capacity of the vector.
 */
template<typename T, size_t N>
struct static_vector {
private:
    typename std::aligned_storage<sizeof(T), std::alignment_of<T>::value>::type arr[N];
    size_t len = 0;

    constexpr const T& ref_at(size_t pos) const {
        return *static_cast<const T*>(static_cast<const void*>(&arr[pos]));
    }

    T& ref_at(size_t pos) {
        return *static_cast<T*>(static_cast<void*>(&arr[pos]));
    }

    constexpr const T* ptr_at(size_t pos) const {
        return static_cast<const T*>(static_cast<const void*>(&arr[pos]));
    }

    T* ptr_at(size_t pos) {
        return static_cast<T*>(static_cast<void*>(&arr[pos]));
    }
public:
    using value_type             = T;
    using size_type              = size_t;
    using difference_type        = ptrdiff_t;
    using reference              = T&;
    using const_reference        = const T&;
    using pointer                = T*;
    using const_pointer          = const T*;
    using iterator               = T*;
    using const_iterator         = const T*;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    /**
     * @brief Creates a static vector of size 0.
     */
    constexpr static_vector() noexcept = default;

    /**
     * @brief Constructs a static vector from an initializer list.
     * @details Constructs a static vector from an initializer list.
     * If the length of the initializer list is too large, then `std::out_of_range` is
     * thrown.
     *
     * @throws std::out_of_range Thrown when the length of initializer list is too large.
     * @param l Initializer list to construct with.
     * @complexity Linear in `l.size()`
     */
    static_vector(std::initializer_list<T> l) {
        if(l.size() > N) {
            throw std::out_of_range("static_vector::static_vector initializer list size too large");
        }

        for(auto&& i : l) {
            push_back(i);
        }
    }

    /**
     * @brief Constructs a static vector with count of values.
     * @details Constructs a static vector with count of values.
     * If the count provided is too large for the static vector then an
     * exception is thrown.
     *
     * @throws std::out_of_range Thrown when the count is too large.
     * @param count Number of elements to initialise.
     * @param value The value to initialise with.
     * @complexity Linear in count.
     */
    static_vector(size_type count, const T& value) {
        if(count > N) {
            throw std::out_of_range("static_vector::static_vector count provided too large");
        }

        for(size_type i = 0; i < count; ++i) {
            push_back(value);
        }
    }

    /**
     * @brief Constructs a static vector from two iterators.
     * @details Constructs a static vector from two iterators.
     * If the distance between the two iterators is too large, then
     * an exception is thrown. Note that this constructor expects
     * ForwardIterators, which means multiple passes are meant to be
     * allowed (i.e. no `std::istream_iterator` or anything similar).
     * The behaviour is undefined if `first` cannot reach `last`.
     *
     * @throws std::out_of_range Thrown when the distance between the iterators is too large.
     * @param first The iterator representing the beginning of the range.
     * @param last The iterator representing the end of the range.
     * @complexity Linear in `std::distance(first, last)`.
     */
    template<typename ForwardIt>
    static_vector(ForwardIt first, ForwardIt last) {
        difference_type count = std::distance(first, last);
        if(count > N) {
            throw std::out_of_range("static_vector::static_vector range provided too large");
        }

        for(; first != last; ++first) {
            push_back(*first);
        }
    }

    /**
     * @brief Copy constructor.
     */
    static_vector(const static_vector& other) {
        for(auto&& i : other) {
            push_back(i);
        }
    }

    /**
     * @brief Move constructor.
     */
    static_vector(static_vector&& other) noexcept {
        using std::swap;
        swap(arr, other.arr);
        swap(len, other.len);
    }

    /**
     * @brief Copy assignment.
     */
    static_vector& operator=(const static_vector& other) {
        clear();
        for(auto&& i : other) {
            push_back(i);
        }
    }

    /**
     * @brief Move assignment.
     */
    static_vector& operator=(static_vector&& other) noexcept {
        clear();
        using std::swap;
        swap(arr, other.arr);
        swap(len, other.len);
    }

    /**
     * @brief Assigns the value of an initializer list to the static vector.
     * @details Assigns the value of an initializer list to the static vector.
     * If the length of the initializer list is too large, then `std::out_of_range` is
     * thrown.
     *
     * @throws std::out_of_range Thrown when the initializer list is too large.
     * @param l The initializer list to construct with.
     * @complexity Linear in `l.size()`
     * @returns A reference to the the static vector.
     */
    static_vector& operator=(std::initializer_list<T> l) {
        clear();
        if(l.size() > N) {
            throw std::out_of_range("static_vector::operator= initializer list too large");
        }

        for(auto&& i : l) {
            push_back(i);
        }
    }

    /**
     * @brief Destructor.
     */
    ~static_vector() {
        clear();
    }

    //@{
    /**
     * @brief Accesses an element with bounds checking.
     * @details Accesses an element with bounds checking.
     * If the index is out of bounds, an exception is thrown.
     *
     * @throws std::out_of_range Thrown if position is out of bounds.
     * @param pos Position of the element to return.
     * @complexity Constant
     * @return Reference to the requested element.
     */
    constexpr const_reference at(size_type pos) const {
        return pos > len ? throw std::out_of_range("static_vector::at") : ref_at(pos);
    }

    reference at(size_type pos) {
        return pos > len ? throw std::out_of_range("static_vector::at") : ref_at(pos);
    }
    //@}

    //@{
    /**
     * @brief Accesses an element without bounds checking.
     * @details Accesses an element without bounds checking.
     * The behaviour is undefined if the position is out of
     * bounds.
     *
     * @param pos Position of the element to return.
     * @complexity Constant
     * @return Reference to the requested element.
     * @see at
     */
    constexpr const_reference operator[](size_type pos) const {
        return ref_at(pos);
    }

    reference operator[](size_type pos) {
        return ref_at(pos);
    }
    //@}

    //@{
    /**
     * @brief Accesses the first element.
     * @details Accesses the first element.
     * If the static vector is empty, then the behaviour
     * is undefined.
     *
     * @complexity Constant
     * @return Reference to the first element.
     */
    constexpr const_reference front() const {
        return ref_at(0);
    }

    reference front() {
        return ref_at(0);
    }
    //@}

    //@{
    /**
     * @brief Accesses the last element.
     * @details Accesses the last element.
     * If the static vector is empty, then the behaviour
     * is undefined.
     *
     * @return Reference to the last element.
     */
    constexpr const_reference back() const {
        return ref_at(len - 1);
    }

    reference back() {
        return ref_at(len - 1);
    }
    //@}

    //@{
    /**
     * @brief Retrieve the pointer to the underlying storage.
     * @details Retrieve the pointer to the underlying storage.
     * If the container is empty, the pointer is still valid. The
     * pointer returned is in the range of [data(), data() + size()].
     *
     * @complexity Constant
     * @return A pointer to the underlying storage.
     */
    const_pointer data() const {
        return ptr_at(0);
    }

    pointer data() {
        return ptr_at(0);
    }
    //@}

    //@{
    /**
     * @brief Returns an iterator pointing to the first element.
     * @details Returns an iterator pointing to the first element.
     * If the container is empty, the iterator is equal to #end().
     *
     * @complexity Constant
     * @return An iterator pointing to the first element.
     */
    iterator begin() {
        return data();
    }

    const_iterator begin() const {
        return data();
    }

    const_iterator cbegin() const {
        return data();
    }
    //@}

    //@{
    /**
     * @brief Returns an iterator pointing to the one past the end element.
     * @details Returns an iterator pointing to the one past the end element.
     * If the container is empty, the iterator is equal to #begin(). It is
     * undefined behaviour to dereference this iterator.
     *
     * @complexity Constant
     * @return An iterator pointing to the one past the end element.
     */
    iterator end() {
        return data() + len;
    }

    const_iterator end() const {
        return data() + len;
    }

    const_iterator cend() const {
        return data() + len;
    }
    //@}

    //@{
    /**
     * @brief Returns an iterator pointing to the first element of the container reversed.
     * @details Returns an iterator pointing to the first element of the container reversed.
     * Essentially, this returns an iterator pointing to the last element of the container.
     *
     * @complexity Constant
     * @return An iterator pointing to the first element of the reversed container.
     */
    reverse_iterator rbegin() {
        return reverse_iterator{ data() + len };
    }

    const_reverse_iterator rbegin() const {
        return const_reverse_iterator{ data() + len };
    }

    const_reverse_iterator crbegin() const {
        return const_reverse_iterator{ data() + len };
    }
    //@}

    //@{
    /**
     * @brief Returns an iterator pointing to following the last element of the container reversed.
     * @details Returns an iterator pointing to following the last element of the container reversed.
     * This iterator acts as a sentinel value, attempting to dereference it results in undefined
     * behaviour.
     *
     * @complexity Constant
     * @return An iterator pointing to following the last element of the reversed container.
     */
    reverse_iterator rend() {
        return reverse_iterator{ data() };
    }

    const_reverse_iterator rend() const {
        return const_reverse_iterator{ data() };
    }

    const_reverse_iterator crend() const {
        return const_reverse_iterator{ data() };
    }
    //@}

    /**
     * @brief Checks if the container is empty.
     * @details Checks if the container is empty. That is,
     * #begin == #end and #size == 0.
     *
     * @complexity Constant
     * @return `true` if empty, `false` otherwise.
     */
    constexpr bool empty() const noexcept {
        return len == 0;
    }

    /**
     * @brief Returns the number of elements in the container.
     * @details Returns the number of elements in the container.
     * This is the equivalent of calling `std::distance(begin(), end())`.
     *
     * @complexity Constant
     * @return The number of elements in the container.
     */
    constexpr size_type size() const noexcept {
        return len;
    }

    /**
     * @brief Returns the maximum number of elements allowed.
     * @details Returns the maximum number of elements allowed.
     * This just delegates the return to the static capacity provided.
     *
     * @complexity Constant
     * @return The maximum number of elements allowed.
     */
    constexpr size_type max_size() const noexcept {
        return N;
    }

    /**
     * @brief Returns the number of elements that can be held in storage.
     * @details Returns the number of elements that can be held in storage.
     * This just delegates the return to the static capacity provided.
     *
     * @complexity Constant
     * @return Number of elements that can be held in storage.
     */
    constexpr size_type capacity() const noexcept {
        return N;
    }

    /**
     * @brief Removes the last element.
     * @details Removes the last element of the container. No iterators or
     * references are invalidated except for #end and #back. The behaviour is
     * undefined if the container is empty.
     *
     * @complexity Constant
     */
    void pop_back() noexcept {
        static_cast<const T*>(static_cast<const void*>(&arr[len - 1]))->~T();
        --len;
    }

    /**
     * @brief Removes all elements.
     * @details Removes all elements of the container. All iterators
     * and references are invalidated.
     *
     * @complexity Linear in #size
     */
    void clear() noexcept {
        while(!empty()) {
            pop_back();
        }
        len = 0;
    }

    //@{
    /**
     * @brief Inserts an element at the end.
     * @details Inserts an element at the end of the container.
     * If #size == #max_size then an exception is thrown. The move
     * constructor is only called if it is declared `noexcept`. The only
     * iterator that is invalidated is #end.
     *
     * @throws std::out_of_range Thrown if no more elements can be inserted.
     * @complexity Constant
     * @param v Value to insert.
     */
    void push_back(const_reference value) {
        // can't push back anymore
        if(size() == N) {
            throw std::out_of_range("static_vector::push_back");
        }

        ::new(arr + len) T(value);
        ++len;
    }

    void push_back(value_type&& value) {
        // can't push back anymore
        if(size() == N) {
            throw std::out_of_range("static_vector::push_back");
        }

        ::new(arr + len) T(std::move_if_noexcept(value));
        ++len;
    }
    //@}

    /**
     * @brief Creates an element in place at the end.
     * @details Creates an element in place at the end.
     * Just like #push_back, an exception is thrown if the
     * insertion would be out of bounds. The element is created
     * in place as if calling `std::forward<Args>(args)...`
     * to the constructor of `value_type`. The only iterator
     * that is invalidated is #end.
     *
     * @throws std::out_of_range Thrown if no more elements can be inserted.
     * @complexity Constant
     * @param args Arguments to pass to the element's constructor.
     */
    template<typename... Args>
    void emplace_back(Args&&... args) {
        // reached maximum
        if(size() == N) {
            throw std::out_of_range("static_vector::emplace_back");
        }

        ::new(arr + len) T(std::forward<Args>(args)...);
        ++len;
    }

    /**
     * @brief Creates an element in place at a specified position.
     * @details Creates an element in place at a specified position.
     * The inserted position is the one before the one given. If the
     * #size is equal to #max_size then an exception is thrown. The
     * element is created in place as if calling `std::forward<Args>(args)...`
     * to the constructor of `value_type`. The elements are shifted to the right
     * and are only moved if the move constructor is declared `noexcept`.
     *
     * @throws std::out_of_range Thrown if no more elements can be inserted.
     * @complexity Linear in `std::distance(pos, cend())`.
     * @param pos Position to insert to.
     * @param args Arguments to pass to the element's constructor.
     * @return Iterator to the inserted element.
     */
    template<typename... Args>
    iterator emplace(const_iterator pos, Args&&... args) {
        if(size() == N) {
            throw std::out_of_range("static_vector::emplace");
        }

        // pos == cend()
        if(pos == cend()) {
            ::new(arr + len) T(std::forward<Args>(args)...);
            ++len;
            return ptr_at(len - 1);
        }

        difference_type diff = std::distance(cbegin(), pos);

        // elements don't fit in [pos, end)
        std::uninitialized_copy(pos, cend(), ptr_at(diff + 1));
        ptr_at(diff)->~T();
        ::new(arr + diff) T(std::forward<Args>(args)...);
        ++len;
        return ptr_at(diff);
    }

    template<typename InputIt>
    iterator insert(const_iterator pos, InputIt first, InputIt last) {
        if(size() == N) {
            throw std::out_of_range("static_vector::insert");
        }
    }
};
} // container
} // gears

#endif // GEARS_CONTAINER_STATIC_VECTOR_HPP
