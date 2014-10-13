.. default-domain:: cpp
.. highlight:: cpp
.. namespace:: gears::functional
.. _gears-modules-functional-objects-logical:

Logical Operators
====================

*Included through* ``<gears/functional/logical_operators.hpp>``

These are a collection of function object instances that implement comparison operators. They typically
return a ``bool`` but they are parametrised for automatic return type deduction in case the type is
not a bool.

.. warning::

    These functions don't short circuit properly. For example, if you feed it something like this:
    ``logical_and(f(), g())`` then both ``f()`` and ``g()`` will be evaluated. This is a consequence
    of these being parameters. The actual computation inside might be short circuited.
    Note that only the boolean operators short circuit. Overloaded operators don't.

.. var:: constexpr logical_and_type logical_and

    Effectively calls `operator&&` on two variables in a generic manner. This is an instance of a function object
    and could be called just like a regular function.

    :param t: The left hand side of the expression.
    :param u: The right hand side of the expression.
    :returns: The generic result of ``t && u``, typically a boolean.

.. var:: constexpr logical_or_type logical_or

    Effectively calls `operator||` on two variables in a generic manner. This is an instance of a function object
    and could be called just like a regular function.

    :param t: The left hand side of the expression.
    :param u: The right hand side of the expression.
    :returns: The generic result of ``t || u``, typically a boolean.

.. var:: constexpr logical_not_type logical_not

    Effectively calls `operator!` on a single variables in a generic manner. This is an instance of a function object
    and could be called just like a regular function.

    :param t: The variable to logically negate.
    :returns: The generic result of ``!t``, typically a boolean.
