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

#ifndef GEARS_UTILITY_ANY_HPP
#define GEARS_UTILITY_ANY_HPP

#include <type_traits>
#include <utility>
#include <typeinfo>
#include <memory>

namespace gears {
namespace utility {
namespace detail {
struct bad_any_cast : public std::bad_cast {
    virtual const char* what() const noexcept {
        return "bad_any_cast";
    }
};
} // detail

/**
 * @ingroup utility
 * @brief A class that contains a type erased value.
 * @details `any` is a class that can contain most type of
 * variables assuming they are copy constructible. This is similar
 * to other dynamic typing languages where you could assign any
 * type to a variable. The closest C++ alternative to this behaviour
 * would be using a `void*` but `any` does this in a safer manner without
 * having `void` pointers.
 *
 * Example:
 * @code
 * #include <gears/utility/any.hpp>
 * #include <iostream>
 * #include <vector>
 *
 * namespace util = gears::utility;
 *
 * int main() {
 *      std::vector<util::any> stuff = { "hello", "world", '!', 1.0f, 200.0, 10 };
 *      for(auto&& i : stuff) {
 *          if(i.is<const char*>()) {
 *              std::cout << i.as<const char*>() << ' ';
 *          }
 *
 *          if(i.is<char>()) {
 *              std::cout << i.as<char>() << '\n';
 *          }
 *
 *          if(i.is<int>()) {
 *              std::cout << i.as<int>() * 150 << '\n';
 *          }
 *      }
 * }
 * @endcode
 *
 * Output:
 * <pre>
 * hello world !
 * 1500
 * </pre>
 */
class any {
private:
    template<typename T>
    using Decayed = typename std::decay<T>::type;

    struct base {
        virtual ~base() {}
        virtual std::unique_ptr<base> clone() const = 0;
    };

    std::unique_ptr<base> obj;

    template<typename T>
    struct object : base {
        static_assert(std::is_copy_constructible<Decayed<T>>(), "Concept violation: T is not CopyConstructible");
        template<typename U>
        object(U&& v): value(std::forward<U>(v)) {}
        T value;

        std::unique_ptr<base> clone() const {
            return std::unique_ptr<base>(new object<T>(value));
        }
    };

    std::unique_ptr<base> clone() const {
        return obj ? obj->clone() : nullptr;
    }
public:
    /**
     * @brief Constructs `any` with no value.
     * @details Constructs `any` with no value. Accessing it
     * with its empty state is undefined behaviour.
     */
    any() noexcept = default;

    /**
     * @brief Constructs `any` with a value.
     * @details Constructs `any` with a value. After construction,
     * `any` holds the value contained and can be accessed with
     * #is with the type of the variable provided. The type passed
     * must be copy constructible or else a compiler error will be
     * thrown.
     *
     * @param actual Value to construct `any` with.
     */
    template<typename T>
    any(T&& actual) noexcept: obj(new(std::nothrow) object<Decayed<T>>(std::forward<T>(actual))) {}

    /**
     * @brief Copy constructor.
     */
    any(const any& other): obj(other.clone()) {}

    /**
     * @brief Move constructor. Must not throw.
     */
    any(any&& other): obj(std::move(other.obj)) {}

    /**
     * @brief Copy assignment.
     */
    any& operator=(const any& other) {
        if(obj == other.obj)
            return *this;

        obj = other.clone();
        return *this;
    }

    /**
     * @brief Move assignment. The value of `other` is removed.
     */
    any& operator=(any&& other) {
        if(obj == other.obj)
            return *this;

        obj.swap(other.obj);
        return *this;
    }

    /**
     * @brief Checks if `any` is in a proper state.
     * @details Checks if `any` is in a proper state, i.e. it
     * contain a value.
     * @return `true` is `any` contains a value, `false` otherwise.
     */
    explicit operator bool() const {
        return static_cast<bool>(obj);
    }

    /**
     * @brief Checks if the value of `any` is a certain type.
     * @details Checks if the value of `any` is a certain type.
     * A specific gotcha with this function is thinking the value
     * of a string literal is `std::string`, it is actually
     * `const char*`. This function should be called before
     * calling #as.
     *
     * @tparam T Type to check for.
     * @return `true` if the internal value is of type `T`, `false` otherwise.
     */
    template<typename T>
    bool is() const {
        auto ptr = dynamic_cast<object<Decayed<T>>*>(obj.get());
        return ptr;
    }

    //@{
    /**
     * @brief Casts `any` to access the contained value.
     * @details Casts `any` to access the contained value. In order to
     * check if the type is valid use #is.
     *
     * @tparam T Type to cast to.
     * @throws gears::utility::bad_any_cast Thrown if the type is invalid.
     * @return The value contained if they type is valid.
     */
    template<typename T>
    const Decayed<T>& as() const {
        auto ptr = dynamic_cast<object<Decayed<T>>*>(obj.get());
        if(!ptr)
            throw detail::bad_any_cast();
        return ptr->value;
    }

   template<typename T>
    Decayed<T>& as() {
        auto ptr = dynamic_cast<object<Decayed<T>>*>(obj.get());
        if(!ptr)
            throw detail::bad_any_cast();
        return ptr->value;
    }
    //@}
};

/**
 * @relates any
 * @brief Helper function to cast `any`.
 * @details Helper function to cast `any` to another type.
 *
 * @param object The object to cast.
 * @tparam T The type to cast to.
 * @throws gears::utility::bad_any_cast Thrown if the type is invalid.
 * @return The value contained in the object if the type is valid.
 */
template<typename T>
inline auto any_cast(const any& object) -> decltype(object.as<T>()) {
    return object.as<T>();
}
} // utility
} // gears

#endif // GEARS_UTILITY_ANY_HPP
