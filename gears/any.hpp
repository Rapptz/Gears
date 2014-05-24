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

#ifndef GEARS_ANY_HPP
#define GEARS_ANY_HPP

#include <type_traits>
#include <utility>
#include <typeinfo>
#include <memory>

namespace gears {
namespace any_detail {
struct bad_any_cast : public std::bad_cast {
    virtual const char* what() const noexcept {
        return "bad_any_cast";
    }
};
} // any_detail

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
    any() noexcept = default;
    template<typename T>
    any(T&& actual) noexcept: obj(new(std::nothrow) object<Decayed<T>>(std::forward<T>(actual))) {}
    any(any&)       = default;
    any(const any&) = default;
    any(any&&)      = default;

    explicit operator bool() const {
        return static_cast<bool>(obj);
    }

    template<typename T>
    bool is() const {
        auto ptr = dynamic_cast<object<Decayed<T>>*>(obj.get());
        return ptr;
    }

   template<typename T>
    Decayed<T>& as() {
        auto ptr = dynamic_cast<object<Decayed<T>>*>(obj.get());
        if(!ptr)
            throw any_detail::bad_any_cast();
        return ptr->value;
    }

    template<typename T>
    const Decayed<T>& as() const {
        auto ptr = dynamic_cast<object<Decayed<T>>*>(obj.get());
        if(!ptr)
            throw any_detail::bad_any_cast();
        return ptr->value;
    }

    any& operator=(const any& other) {
        if(obj == other.obj)
            return *this;

        obj = other.clone();
        return *this;
    }

    any& operator=(any&& other) {
        if(obj == other.obj)
            return *this;

        obj.swap(other.obj);
        return *this;
    }  
};

template<typename T>
inline auto any_cast(const any& object) -> decltype(object.as<T>()) {
    return object.as<T>();
}
} // gears

#endif // GEARS_ANY_HPP