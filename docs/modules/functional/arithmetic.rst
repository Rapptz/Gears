.. default-domain:: gcpp
.. highlight:: cpp
.. namespace:: gears::functional
.. _gears-modules-functional-objects-arithmetic:

Arithmetic Operators
=======================

*Included through* ``<gears/functional/arithmetic_operators.hpp>``

These are a collection of function object instances that implement arithmetic operators.

.. var:: constexpr plus_type plus

    A function object that effectively calls ``operator+`` on two variables in a generic manner. This is an
    instance of a function object and could be called just like a regular function.

    :param t: The left hand side of the expression.
    :param u: The right hand side of the expression.
    :returns: The generic result of ``t + u``.

.. var:: constexpr minus_type minus

    A function object that effectively calls ``operator-`` on two variables in a generic manner. This is an
    instance of a function object and could be called just like a regular function.

    :param t: The left hand side of the expression.
    :param u: The right hand side of the expression.
    :returns: The generic result of ``t - u``.

.. var:: constexpr multiplies_type multiplies

    A function object that effectively calls ``operator*`` on two variables in a generic manner. This is an
    instance of a function object and could be called just like a regular function.

    :param t: The left hand side of the expression.
    :param u: The right hand side of the expression.
    :returns: The generic result of ``t * u``.

.. var:: constexpr divides_type divides

    A function object that effectively calls ``operator/`` on two variables in a generic manner. This is an
    instance of a function object and could be called just like a regular function.

    :param t: The left hand side of the expression.
    :param u: The right hand side of the expression.
    :returns: The generic result of ``t / u``.

.. var:: constexpr modulus_type modulus

    A function object that effectively calls ``operator%`` on two variables in a generic manner. This is an
    instance of a function object and could be called just like a regular function.

    :param t: The left hand side of the expression.
    :param u: The right hand side of the expression.
    :returns: The generic result of ``t % u``.
