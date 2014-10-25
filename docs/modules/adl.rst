.. default-domain:: cpp
.. highlight:: cpp
.. namespace:: gears::adl
.. _gears-modules-adl:

ADL Module --- Suite of functions that help with Argument Dependent Lookup
=============================================================================

.. sidebar:: Tutorial

    This page just hosts the API reference.

    For a tutorial and a motivation on why to use this, check the
    :ref:`tutorial <gears-tutorials-adl>`.

*Included through* ``<gears/adl.hpp>``

This module is very simple, allowing for an ADL-enabled function calls.
This is useful because it allows you to write generic code that relies on certain functions
without actually having to specify the ``using`` statement for every function in every line.
For more information about ADL (or Argument Dependent Lookup), see
`here <http://en.wikipedia.org/wiki/Argument-dependent_name_lookup>`_.

.. _gears-modules-adl-api:

Functions
---------------

.. function:: constexpr auto get<N>(T&& t)

    ADL enabled ``get`` function for tuple-like classes. Allows for argument
    dependent lookup of ``std::get`` and overloaded specialisations of ``get``.

    This is equivalent to the following code::

        using std::get;
        auto&& r = get<N>(t);

    :param t: The tuple-like class to access.
    :tparam N: The index of the element to retrieve.
    :returns: The automatically deduced return type of ``get<N>(t);``
    :subinclude: get.hpp

.. function:: constexpr auto begin(T&& t)

    ADL enabled ``begin`` that allows for retrieval of ``std::begin`` and specialisations
    of ``begin`` through argument dependent lookup.

    Equivalent to doing the following:::

        using std::begin;
        begin(t);

    :param t: Object with ``begin`` interface
    :returns: The automatically deduced return value of ``begin(t);``
    :subinclude: iterator.hpp

.. function:: constexpr auto end(T&& t)

    ADL enabled ``end`` that allows for retrieval of ``std::end`` and specialisations
    of ``end`` through argument dependent lookup.

    Equivalent to doing the following:::

        using std::end;
        end(t);

    :param t: Object with ``end`` interface
    :returns: The automatically deduced return value of ``end(t);``
    :subinclude: iterator.hpp

.. function:: constexpr auto swap(T&& t, U&& u) noexcept

    ADL-enabled ``swap`` that allows for ADL of `std::swap`.

    Equivalent to the following::

        using std::swap;
        swap(t, u);

    :param t: First element to swap.
    :param u: Second element to swap.
    :returns: The automatically deduced return value of ``swap(t, u)``.
    :noexcept: Conditional ``noexcept`` based on the expression ``swap(t, u)``.
    :subinclude: swap.hpp
