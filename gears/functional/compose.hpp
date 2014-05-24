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

#ifndef GEARS_FUNCTIONAL_COMPOSE_HPP
#define GEARS_FUNCTIONAL_COMPOSE_HPP

#include <type_traits>
#include <utility>

namespace gears {
namespace functional {
namespace detail {
template<typename T>
using Decayed = typename std::decay<T>::type;

template<typename First, typename Second>
struct compose_type {
    First f;
    Second g;
    constexpr compose_type(First f, Second g) noexcept: f(std::move(f)), g(std::move(g)) {}

    template<typename... Args>
    constexpr auto operator()(Args&&... args) const -> decltype(f(g(std::forward<Args>(args)...))) {
        return f(g(std::forward<Args>(args)...));
    }
};

template<typename F, typename... G>
struct composer {
    using type = compose_type<Decayed<F>, typename composer<G...>::type>;
};

template<typename F>
struct composer<F> {
    using type = Decayed<F>;
};

template<typename... Args>
using Composer = typename composer<Args...>::type;
} // detail

template<typename Function>
constexpr detail::Decayed<Function> compose(Function&& f) {
    return std::forward<Function>(f);
}

/**
 * @ingroup functional
 * @brief Function composition of functions
 * @details Enables function composition of multiple functions.
 * Note that the syntax goes left to right, so for example:
 * 
 * @code 
 * compose(f, g, h);
 * @endcode
 * 
 * would be equivalent to `f(g(h()))`
 * 
 * @param f First function to compose
 * @param args Rest of the functions to compose
 * @return A function object that allows you to call the composed function.
 */
template<typename First, typename... Rest>
constexpr detail::Composer<First, Rest...> compose(First&& f, Rest&&... args) {
    return detail::Composer<First, Rest...>(std::forward<First>(f), compose(std::forward<Rest>(args)...));
}
} // functional
} // gears

#endif // GEARS_FUNCTIONAL_COMPOSE_HPP