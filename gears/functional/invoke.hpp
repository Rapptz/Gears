// The MIT License (MIT)

// Copyright (c) 2012-2015 Danny Y., Rapptz

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

#include <gears/meta/enable_if.hpp>
#include <gears/meta/qualifiers.hpp>
#include <gears/meta/traits.hpp>

namespace gears {
namespace functional {
namespace detail {
using namespace gears::meta;
template <typename Fun, typename Obj, typename... Args,
          typename Result = decltype((std::declval<Obj>().*std::declval<Fun>())(std::declval<Args>()...)),
          bool NoExcept = noexcept((std::declval<Obj>().*std::declval<Fun>())(std::declval<Args>()...)),
          enable_if_t<std::is_member_function_pointer<unqualified_t<Fun>>,
                   std::is_base_of<class_of_t<unqualified_t<Fun>>, unqualified_t<Obj>>> = _>
constexpr Result invoke(Fun&& fun, Obj&& obj, Args&&... args) noexcept(NoExcept) {
    return (std::forward<Obj>(obj).*std::forward<Fun>(fun))(std::forward<Args>(args)...);
}

template <typename Fun, typename Obj, typename... Args,
          typename Result = decltype(((*std::declval<Obj>()).*std::declval<Fun>())(std::declval<Args>()...)),
          bool NoExcept = noexcept(((*std::declval<Obj>()).*std::declval<Fun>())(std::declval<Args>()...)),
          enable_if_t<std::is_member_function_pointer<unqualified_t<Fun>>,
                   negate<std::is_base_of<class_of_t<unqualified_t<Fun>>, unqualified_t<Obj>>>> = _>
constexpr Result invoke(Fun&& fun, Obj&& obj, Args&&... args) noexcept(NoExcept) {
    return ((*std::forward<Obj>(obj)).*std::forward<Fun>(fun))(std::forward<Args>(args)...);
}

template <typename Fun, typename Obj,
          typename Result = decltype(std::declval<Obj>().*std::declval<Fun>()),
          bool NoExcept = noexcept(std::declval<Obj>().*std::declval<Fun>()),
          enable_if_t<std::is_member_object_pointer<unqualified_t<Fun>>,
                   std::is_base_of<class_of_t<unqualified_t<Fun>>, unqualified_t<Obj>>> = _>
constexpr Result invoke(Fun&& fun, Obj&& obj) noexcept(NoExcept) {
    return std::forward<Obj>(obj).*std::forward<Fun>(fun);
}

template <typename Fun, typename Obj,
          typename Result = decltype((*std::declval<Obj>()).*std::declval<Fun>()),
          bool NoExcept = noexcept((*std::declval<Obj>()).*std::declval<Fun>()),
          enable_if_t<std::is_member_object_pointer<unqualified_t<Fun>>,
                   negate<std::is_base_of<class_of_t<unqualified_t<Fun>>, unqualified_t<Obj>>>> = _>
constexpr Result invoke(Fun&& fun, Obj&& obj) noexcept(NoExcept) {
    return (*std::forward<Obj>(obj)).*std::forward<Fun>(fun);
}

template <typename Fun, typename... Args,
          typename Result = decltype(std::declval<Fun>()(std::declval<Args>()...)),
          bool NoExcept = noexcept(std::declval<Fun>()(std::declval<Args>()...)),
          disable_if_t<std::is_member_pointer<unqualified_t<Fun>>> = _>
constexpr Result invoke(Fun&& fun, Args&&... args) noexcept(NoExcept) {
    return std::forward<Fun>(fun)(std::forward<Args>(args)...);
}
} // namespace detail

template <typename Deduced = meta::deduced, typename... Args,
          typename Expected = decltype(detail::invoke(std::declval<Args>()...)),
          typename Result = meta::iif<meta::is_deduced<Deduced>, Expected, Deduced>,
          bool NoExcept = noexcept(detail::invoke(std::declval<Args>()...)),
          meta::enable_if_t<meta::any<std::is_convertible<Expected, Result>, std::is_void<Result>>> = meta::_>
constexpr Result invoke(Args&&... args) noexcept(NoExcept) {
    return detail::invoke(std::forward<Args>(args)...);
}
} // functional
} // gears

#endif // GEARS_FUNCTIONAL_INVOKE_HPP
