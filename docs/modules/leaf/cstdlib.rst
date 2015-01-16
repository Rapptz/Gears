.. default-domain:: gcpp
.. highlight:: cpp
.. namespace:: gears::leaf
.. _gears-modules-leaf-cstdlib:

Stdlib --- ``constexpr`` enabled conversions and more
=============================================================

.. sidebar:: Tutorial

    This page just hosts the API reference.

    A tutorial for this module will be coming soon.

*Included through* ``<gears/leaf/cstdlib.hpp>``

Provides ``constexpr`` functions found in ``<cstdlib>``. This submodule's purpose is to
provide some of the old C functions found in ``<cstdlib>`` with a ``constexpr`` interface.
As a result of this, all the functions are generalised.
That is, there will be no type suffixes for ad-hoc function overloading. Note, not all functions are provided either.

.. class:: div_t

    A structure that represents the result of :func:`div <gears::leaf::div>`.

    :tparam Integer: The internal integral type.

    .. member:: Integer rem

        Represents the remainder, i.e. ``rem = x / y``.
    .. member:: Integer quot

        Represents the quotient, i.e. ``quot = x % y``.

.. function:: constexpr auto div(Integer x, Integer y)

    Computes the quotient and remainder of two integers.
    The integral type must have ``operator/`` and ``operator%`` defined
    for this function to work. The return value is the :class:`div_t` struct
    containing the remainder and quotient.

    :param x: The left hand side of the expression.
    :param y: The right hand side of the expression.
    :returns: :class:`div_t` containing the remainder and quotient.

.. function:: constexpr Number abs(Number number)

    Computes the absolute value of a number.
    This just uses the naive implementation of
    ``number < 0 ? -number : number;`` which is a valid
    ``constexpr`` expression. The behaviour is undefined if
    the number cannot be represented in which case on a
    conforming compiler would be undefined behaviour.

    :param number: The number to turn to an absolute value.
    :returns: The absolute value of the number.

.. function:: constexpr Integral atoi(const char* str)

    Converts a null terminated string to an integer type.
    The string must be all digits (i.e. in the range of '0' and '9'). If
    the string isn't full of digits, then an exception is thrown which
    is a compile time error if used in a constant expression. If the number
    starts with +, then the string is processed as a positive number. If the
    number string starts with - however, then the result of the conversion will
    be multiplied with ``static_cast<Integral>(-1)``.

    :tparam Integral: The integral type to convert to. Must not be a floating point.
    :param str: The numeric string to convert to a digit.
    :returns: The string converted into an integral type.
