.. default-domain:: gcpp
.. highlight:: cpp
.. namespace:: gears::functional
.. _gears-modules-functional-objects-comparison:

Comparison Operators
=======================

*Included through* ``<gears/functional/comparison_operators.hpp>``

These are a collection of function object instances that implement comparison operators.

.. var:: constexpr equal_to_type equal_to

    A function object that effectively calls ``operator==`` on two variables in a generic manner. This is an
    instance of a function object and could be called just like a regular function.

    :param t: The left hand side of the expression.
    :param u: The right hand side of the expression.
    :returns: The generic result of ``t == u``, typically a boolean.

.. var:: constexpr not_equal_to_type not_equal_to

    A function object that effectively calls ``operator!=`` on two variables in a generic manner. This is an
    instance of a function object and could be called just like a regular function.

    :param t: The left hand side of the expression.
    :param u: The right hand side of the expression.
    :returns: The generic result of ``t != u``, typically a boolean.

.. var:: constexpr greater_type greater

    A function object that effectively calls ``operator>`` on two variables in a generic manner. This is an
    instance of a function object and could be called just like a regular function.

    :param t: The left hand side of the expression.
    :param u: The right hand side of the expression.
    :returns: The generic result of ``t > u``, typically a boolean.

.. var:: constexpr less_type less

    A function object that effectively calls ``operator<`` on two variables in a generic manner. This is an
    instance of a function object and could be called just like a regular function.

    :param t: The left hand side of the expression.
    :param u: The right hand side of the expression.
    :returns: The generic result of ``t < u``, typically a boolean.

.. var:: constexpr greater_equal_type greater_equal

    A function object that effectively calls ``operator>=`` on two variables in a generic manner. This is an
    instance of a function object and could be called just like a regular function.

    :param t: The left hand side of the expression.
    :param u: The right hand side of the expression.
    :returns: The generic result of ``t >= u``, typically a boolean.

.. var:: constexpr less_equal_type less_equal

    A function object that effectively calls ``operator<=`` on two variables in a generic manner. This is an
    instance of a function object and could be called just like a regular function.

    :param t: The left hand side of the expression.
    :param u: The right hand side of the expression.
    :returns: The generic result of ``t <= u``, typically a boolean.
