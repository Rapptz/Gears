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

#ifndef GEARS_FUNCTIONAL_INVOKE_HPP
#define GEARS_FUNCTIONAL_INVOKE_HPP

#include "../meta/alias.hpp"

namespace gears {
namespace functional {
namespace detail {
using namespace gears::meta;
template <typename Fun, typename Obj, typename... Args,
          typename Result = decltype((std::declval<Obj>().*std::declval<Fun>())(std::declval<Args>()...)),
          bool NoExcept = noexcept((std::declval<Obj>().*std::declval<Fun>())(std::declval<Args>()...)),
          EnableIf<std::is_member_function_pointer<Unqualified<Fun>>,
                   std::is_base_of<ClassOf<Unqualified<Fun>>, Unqualified<Obj>>> = _>
constexpr Result invoke(Fun&& fun, Obj&& obj, Args&&... args) noexcept(NoExcept) {
    return (std::forward<Obj>(obj).*std::forward<Fun>(fun))(std::forward<Args>(args)...);
}

template <typename Fun, typename Obj, typename... Args,
          typename Result = decltype(((*std::declval<Obj>()).*std::declval<Fun>())(std::declval<Args>()...)),
          bool NoExcept = noexcept(((*std::declval<Obj>()).*std::declval<Fun>())(std::declval<Args>()...)),
          EnableIf<std::is_member_function_pointer<Unqualified<Fun>>,
                   Not<std::is_base_of<ClassOf<Unqualified<Fun>>, Unqualified<Obj>>>> = _>
constexpr Result invoke(Fun&& fun, Obj&& obj, Args&&... args) noexcept(NoExcept) {
    return ((*std::forward<Obj>(obj)).*std::forward<Fun>(fun))(std::forward<Args>(args)...);
}

template <typename Fun, typename Obj,
          typename Result = decltype(std::declval<Obj>().*std::declval<Fun>()),
          bool NoExcept = noexcept(std::declval<Obj>().*std::declval<Fun>()),
          EnableIf<std::is_member_object_pointer<Unqualified<Fun>>,
                   std::is_base_of<ClassOf<Unqualified<Fun>>, Unqualified<Obj>>> = _>
constexpr Result invoke(Fun&& fun, Obj&& obj) noexcept(NoExcept) {
    return std::forward<Obj>(obj).*std::forward<Fun>(fun);
}

template <typename Fun, typename Obj,
          typename Result = decltype((*std::declval<Obj>()).*std::declval<Fun>()),
          bool NoExcept = noexcept((*std::declval<Obj>()).*std::declval<Fun>()),
          EnableIf<std::is_member_object_pointer<Unqualified<Fun>>,
                   Not<std::is_base_of<ClassOf<Unqualified<Fun>>, Unqualified<Obj>>>> = _>
constexpr Result invoke(Fun&& fun, Obj&& obj) noexcept(NoExcept) {
    return (*std::forward<Obj>(obj)).*std::forward<Fun>(fun);
}

template <typename Fun, typename... Args,
          typename Result = decltype(std::declval<Fun>()(std::declval<Args>()...)),
          bool NoExcept = noexcept(std::declval<Fun>()(std::declval<Args>()...)),
          DisableIf<std::is_member_pointer<Unqualified<Fun>>> = _>
constexpr Result invoke(Fun&& fun, Args&&... args) noexcept(NoExcept) {
    return std::forward<Fun>(fun)(std::forward<Args>(args)...);
}
} // namespace detail

#ifndef GEARS_FOR_DOXYGEN_ONLY
template <typename Deduced = meta::deduced, typename... Args,
          typename Expected = decltype(detail::invoke(std::declval<Args>()...)),
          typename Result = meta::If<meta::is_deduced<Deduced>, Expected, Deduced>,
          bool NoExcept = noexcept(detail::invoke(std::declval<Args>()...)),
          meta::EnableIf<meta::Any<std::is_convertible<Expected, Result>, std::is_void<Result>>> = meta::_>
#else
template<typename... Args>
#endif
constexpr Result invoke(Args&&... args) noexcept(NoExcept) {
    return detail::invoke(std::forward<Args>(args)...);
}
} // functional
} // gears

/**
 * @ingroup functional
 * @fn template<typename... Args> auto gears::functional::invoke(Args&&... t);
 * @brief Implements the `INVOKE` facility in the C++ standard.
 * @details The `INVOKE` facility in the standard is specified in
 * §20.8.2 as follows:
 *
 * <pre>
 * Define INVOKE (f, t1, t2, ..., tN) as follows:
 * — (t1.*f)(t2, ..., tN) when f is a pointer to a member function
 * of a class T and t1 is an object of type T or a reference to an object
 * of type T or a reference to an object of a type derived from T;
 * — ((*t1).*f)(t2, ..., tN) when f is a pointer to a member function
 * of a class T and t1 is not one of the types described in the previous item;
 * — t1.*f when N == 1 and f is a pointer to member data of a class T and
 * t1 is an object of type T or a reference to an object of type T or a reference
 * to an object of a type derived from T;
 * — (*t1).*f when N == 1 and f is a pointer to member data of a class
 *  T and t1 is not one of the types described in the previous item;
 * — f(t1, t2, ..., tN) in all other cases.
 * </pre>
 *
 * @param t arguments to pass to `INVOKE` facility.
 * @return generic result of the invoked call.
 */

#endif // GEARS_FUNCTIONAL_INVOKE_HPP
