.. default-domain:: gcpp
.. highlight:: cpp
.. namespace:: gears::functional
.. _gears-modules-functional-objects-bitwise:

Bitwise Operators
====================

*Included through* ``<gears/functional/bitwise_operators.hpp>``

These are a collection of function object instances that implement bitwise operators.

.. var:: constexpr bit_and_type bit_and

    A function object that effectively calls ``operator&`` on two variables in a generic manner. This is an
    instance of a function object and could be called just like a regular function.

    :param t: The left hand side of the expression.
    :param u: The right hand side of the expression.
    :returns: The generic result of ``t & u``.

.. var:: constexpr bit_or_type bit_or

    A function object that effectively calls ``operator|`` on two variables in a generic manner. This is an
    instance of a function object and could be called just like a regular function.

    :param t: The left hand side of the expression.
    :param u: The right hand side of the expression.
    :returns: The generic result of ``t | u``.

.. var:: constexpr bit_xor_type bit_xor

    A function object that effectively calls ``operator^`` on two variables in a generic manner. This is an
    instance of a function object and could be called just like a regular function.

    :param t: The left hand side of the expression.
    :param u: The right hand side of the expression.
    :returns: The generic result of ``t ^ u``.

.. var:: constexpr bit_not_type bit_not

    A function object that effectively calls ``operator~`` on a single variables in a generic manner. This is an
    instance of a function object and could be called just like a regular function.

    :param t: The variable to bitwise negate.
    :returns: The generic result of ``~t``.

.. var:: constexpr lshift_type lshift

    A function object that effectively calls ``operator<<`` on two variables in a generic manner. This is an
    instance of a function object and could be called just like a regular function.

    :param t: The left hand side of the expression.
    :param u: The right hand side of the expression.
    :returns: The generic result of ``t << u``.

.. var:: constexpr rshift_type rshift

    A function object that effectively calls ``operator>>`` on two variables in a generic manner. This is an
    instance of a function object and could be called just like a regular function.

    :param t: The left hand side of the expression.
    :param u: The right hand side of the expression.
    :returns: The generic result of ``t >> u``.
