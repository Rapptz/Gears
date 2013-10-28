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

#ifndef GEARS_FUNCTIONAL_INVOKE_HPP
#define GEARS_FUNCTIONAL_INVOKE_HPP

#include "../meta/alias.hpp"

namespace gears {
namespace functional {
namespace detail {
template<typename Func, typename Obj, typename... Args, 
         meta::EnableIf<std::is_member_function_pointer<meta::Unqualified<Func>>,
                  std::is_base_of<meta::ClassOf<meta::Unqualified<Func>>, meta::Unqualified<Obj>>>...,
         typename R = decltype((std::declval<Obj>().*std::declval<Func>())(std::declval<Args>()...))>
constexpr R invoke(Func&& f, Obj&& obj, Args&&... args) noexcept {
    return (std::forward<Obj>(obj).*std::forward<Func>(f))(std::forward<Args>(args)...);
}

template<typename Func, typename Obj, typename... Args, 
         meta::EnableIf<std::is_member_function_pointer<meta::Unqualified<Func>>,
                  meta::Not<std::is_base_of<meta::ClassOf<meta::Unqualified<Func>>, meta::Unqualified<Obj>>>>...,
         typename R = decltype((*std::declval<Obj>().*std::declval<Func>())(std::declval<Args>()...))>
constexpr R invoke(Func&& f, Obj&& obj, Args&&... args) noexcept {
    return (*std::forward<Obj>(obj).*std::forward<Func>(f))(std::forward<Args>(args)...);
}

template<typename Func, typename Obj,
         meta::EnableIf<std::is_member_function_pointer<meta::Unqualified<Func>>,
                  std::is_base_of<meta::ClassOf<meta::Unqualified<Func>>, meta::Unqualified<Obj>>>...>
constexpr auto invoke(Func&& f, Obj&& obj) noexcept -> decltype(std::forward<Obj>(obj).*std::forward<Func>(f)) {
    return std::forward<Obj>(obj).*std::forward<Func>(f);
}

template<typename Func, typename Obj,
         meta::EnableIf<std::is_member_function_pointer<meta::Unqualified<Func>>,
                  meta::Not<std::is_base_of<meta::ClassOf<meta::Unqualified<Func>>, meta::Unqualified<Obj>>>>...>
constexpr auto invoke(Func&& f, Obj&& obj) noexcept -> decltype(*(std::forward<Obj>(obj)).*std::forward<Func>(f)) {
    return (*std::forward<Obj>(obj)).*std::forward<Func>(f);
}

template<typename Func, typename... Args, meta::DisableIf<std::is_member_function_pointer<meta::Unqualified<Func>>>...>
constexpr auto invoke(Func&& f, Args&&... args) noexcept -> decltype(std::forward<Func>(f)(std::forward<Args>(args)...)) {
    return std::forward<Func>(f)(std::forward<Args>(args)...);
}
} // detail

template<typename Deduced = meta::deduced, typename... T, typename Actual = decltype(detail::invoke(std::declval<T>()...)),
         typename Result = meta::If<meta::is_deduced<Deduced>, Actual, Deduced>,
         meta::EnableIf<meta::Any<std::is_convertible<Actual, Result>, std::is_void<Result>>>...>
constexpr Result invoke(T&&... t) noexcept {
    return Result(detail::invoke(std::forward<T>(t)...));
}
} // functional
} // gears

#endif // GEARS_FUNCTIONAL_INVOKE_HPP