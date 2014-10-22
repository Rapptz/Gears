.. default-domain:: cpp
.. highlight:: cpp
.. namespace:: gears::functional
.. _gears-modules-functional:

Functional Module --- Support for functional programming
==========================================================

*Included through* ``<gears/functional.hpp>``

This module provides multiple function objects (also called functors) and operations that make working in a
functional manner easier.

All of the function objects have a ``constexpr`` instantiation to allow working
with the other components of the module easier. It also allows the user to use the
function objects just like a regular function.

There's also basic support for partial function application and composition.
More support for other things are coming soon.

Example usage:

.. code-block:: cpp

    #include <gears/functional.hpp>
    #include <iostream>

    namespace fn = gears::functional;

    int main() {
        // equivalent to
        // fn::even(fn::plus(...))
        auto f = fn::compose(fn::even, fn::plus);
        std::cout << f(11, 15);
    }

Output:

.. code-block:: none

    1

Function Objects
--------------------

A function object is any object for which the function call operator is defined. An instance of a
function object could be called just like a regular function and could emulate functions as first class citizens. The
functional module provides ``constexpr`` instances of these function objects.

They are categorised as follows:

.. toctree::
    :maxdepth: 1

    functional/arithmetic
    functional/bitwise
    functional/comparison
    functional/logical
    functional/misc

.. _gears-modules-functional-functions:

Functions
---------------


.. function:: constexpr auto compose(First&& f, Rest&&... args)

    Enables function composition of multiple functions. Function composition is taking
    the result of one function as a parameter of another function. For example, the
    function composition of ``f`` and ``g`` is ``f(g())``.

    .. important::

        The syntax for this goes left to right, so for example ``compose(f, g, h);`` would be equivalent to ``f(g(h()))``.

    .. admonition:: compose return type

        **Member objects**

        The return type of compose stores the a pair of functions that are copied or move
        depending on the type. It defines the following public member data:

        - **f**: The first function.
        - **g**: The second function.

        **Constructibility**

        The return type is CopyConstructible and MoveConstructible.

        **Members functions**

        The return type defines a single member function, ``constexpr auto operator()(Args&&... args)``. This is called
        as if doing the following ``f(g(std::forward<Args>(args)...))``.

    :param f: The first function to compose.
    :param args: The rest of the functions to compose.
    :returns: An unspecified function object that follows the requirements above.
    :subinclude: compose.hpp

.. function:: constexpr auto partial(Function&& f, Args&&... args)

    Partially applies a function. More info on what partial function application is can be
    found `here <http://en.wikipedia.org/wiki/Partial_application>`_. The shorter form of
    explaining partial function application is essentially :cpp:`std::bind <utility/functional/bind>`
    but without the use of :cpp:`std::placeholders <utility/functional/placeholders>`.

    Example:::

        #include <gears/functional.hpp>
        #include <iostream>

        namespace fn = gears::functional;

        int main() {
            auto add_five = fn::partial(fn::plus, 5);
            std::cout << add_five(10) << ' ' << add_five(15);
        }

    Output:

    .. code-block:: none

        15 20

    .. admonition:: partial return type

        **Member objects**

        The return type of partial stores the function and a :cpp:`std::tuple <utility/tuple>` of the arguments passed
        originally. They are constructed through :cpp:`std::forward <utility/forward>` and
        :cpp:`std::make_tuple <utility/tuple/make_tuple>` respectively. There are no public member variables.

        **Constructibility**

        The return type is CopyConstructible and MoveConstructible.

        **Members functions**

        The return type defines a single member function, ``constexpr auto operator()(Args&&... args)``. Given the original
        function passed as ``f`` and the original arguments as ``t...``, then the function is called as if doing
        ``f(t.., args...)`` with decay semantics on all arguments unless the use of :cpp:`std::ref <utility/functional/ref>`
        is used to preserve references just like :cpp:`std::bind <utility/functional/bind>`.

    :param f: The function to partially apply.
    :param args: The parameters to pass to the partially applied function.
    :returns: An unspecified function object that follows the requirements above.
    :subinclude: partial.hpp

.. function:: constexpr auto invoke(Function&& f, Args&&... args) noexcept

    Implements the ``INVOKE`` facility in the C++11 standard. The ``INVOKE``
    facility in the standard is specified by §20.8.2 as follows:

    Define ``INVOKE (f, t1, t2, ..., tN)`` as follows:

    * ``(t1.*f)(t2, ..., tN)`` when ``f`` is a pointer to a member function
      of a class T and ``t1`` is an object of type T or a reference to an object
      of type T or a reference to an object of a type derived from T;
    * ``((*t1).*f)(t2, ..., tN)`` when ``f`` is a pointer to a member function
      of a class T and ``t1`` is not one of the types described in the previous item;
    * ``t1.*f`` when ``N == 1`` and ``f`` is a pointer to member data of a class T and
      ``t1`` is an object of type T or a reference to an object of type T or a reference
      to an object of a type derived from T;
    * ``(*t1).*f`` when ``N == 1`` and ``f`` is a pointer to member data of a class
      T and ``t1`` is not one of the types described in the previous item;
    * ``f(t1, t2, ..., tN)`` in all other cases.

    In other words:

    * If ``f`` is a pointer to member function of class T and the first parameter is an
      object T, then it calls the pointer to member function with ``args`` being passed with
      the first argument being used for the call. If the first parameter is a pointer to class T
      then it is dereferenced before used in the call.
    * If ``f`` is a pointer to a member variable of class T and there is only one parameter
      that is an object of class T then the member variable is returned. If the first parameter
      is a pointer to class T then it is dereferenced before used in the call.
    * Otherwise, ``f(args...)`` is done.

    :param f: The function type to pass to the ``INVOKE`` facility.
    :param args: The parameters to pass.
    :noexcept: This function conditionally does not throw.
    :returns: The result of function as specified above.
    :subinclude: invoke.hpp
