.. default-domain:: cpp
.. highlight:: cpp
.. namespace:: gears::tuple
.. _gears-modules-tuple:

Tuple Module --- Facilities to work with tuples
=================================================

*Included through* ``<gears/tuple.hpp>``

This module defines utilities that help usage of :cpp:`std::tuple <utility/tuple>` to be a little
more practical. There are often times when you have a function that you want to invoke on every
member of the tuple or when you want to expand a tuple into arguments for a function. This module
takes care of this boilerplate and more.

Example Usage:

.. code-block:: cpp

    #include <gears/tuple.hpp>
    #include <tuple>
    #include <iostream>

    using namespace gears;

    struct printer {
        template<typename T>
        void operator()(const T& t) {
            std::cout << t << '\n';
        }
    };

    int main() {
        auto tup = std::make_tuple(10, "hello", 3.14f);
        tuples::for_each(tup, printer{});
    }

Output:

.. code-block:: none

    10
    hello
    3.14


Functions
------------

.. function:: constexpr void for_each(const Tuple& tuple, Function&& f)

    Calls the the function ``f`` on every member of the tuple. The function provided has
    to be generic and work with all members of the tuple. While a return type can be used
    with the function, it is silently discarded.

    :param tuple: The tuple to loop over.
    :param f: The function to invoke to every member of the tuple.
    :subinclude: algorithm.hpp

.. function:: constexpr auto invoke(Function&& f, const Tuple& tuple)

    Expands the tuple into a parameter pack that is then applied to the function provided.
    For example, given a tuple ``std::tuple<int, float, char>`` and a function that accepts
    the signature ``(int, float, char)`` then ``invoke`` expands the tuple for
    said function to work.

    :param f: The function to invoke.
    :param tuple: The tuple to expand as arguments to the function.
    :returns: The automatically deduced return type of ``f(get<Ns>(tuple)...)``
    :subinclude: algorithm.hpp
