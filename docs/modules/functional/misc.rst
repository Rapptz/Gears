.. default-domain:: gcpp
.. highlight:: cpp
.. namespace:: gears::functional
.. _gears-modules-functional-objects-misc:

Miscellaneous Operations
===========================

These are a collection of function object instances that implement miscellaneous things such as numerical
properties.

.. var:: constexpr even_type even

    Function object checking if a numeric type is even. Checks if a numeric instance is even by
    effectively checking if ``t % 2 == 0``.

    :param t: The numeric instance to check.
    :returns: The generic result of ``t % 2 == 0``, typically a bool.
    :subinclude: numeric_properties.hpp

.. var:: constexpr odd_type odd

    Function object checking if a numeric type is odd. Checks if a numeric instance is even by
    effectively checking if ``t % 2 != 0``.

    :param t: The numeric instance to check.
    :returns: The generic result of ``t % 2 != 0``, typically a bool.
    :subinclude: numeric_properties.hpp
