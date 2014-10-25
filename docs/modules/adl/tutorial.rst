:orphan:

.. default-domain:: cpp
.. highlight:: cpp
.. _gears-tutorials-adl:

ADL Tutorial
===============

This section describes how to use the :ref:`ADL module <gears-modules-adl>` and its motivation for its existence.

.. _gears-tutorials-adl-motivation:

Motivation
-------------

.. |swap| replace:: :cpp:`std::swap <utility/swap>`

When writing generic code, it's typically appropriate at some point to start calling functions such as |swap|
but that comes with a strange gotcha. By explicitly invoking |swap| you're only accepting the generic greedy templated
version that doesn't have a possible optimisation of a user defined type. Consider the following: ::

    #include <iostream>

    namespace ns {
    struct test {
        int* data = nullptr; // "expensive" data

        void swap(test& t) noexcept {
            std::cout << "swapping\n"; // for exposition only
            auto temp = data;
            data = t.data;
            t.data = temp;
        }
    };

    void swap(test& a, test& b) noexcept {
        a.swap(b);
    }
    } // ns

    int main() {
        ns::test a, b;
        std::swap(a, b); // bad
    }

To the surprise of some people, this would not print "swapping". In order to do that, the following idiom has to be used: ::

    using std::swap;
    swap(a, b);

The purpose of this module is to make this easier. It's easy to forget ``using std::swap`` and this library aims to aid that.

.. _gears-tutorials-adl-usage:

Usage
------------

The usage of this module is very simple. Just replace ``std::`` with ``adl::`` for the most part. So for the example above
you'd have to do ``adl::swap(a, b);`` and it'd work as expected.

A full example is provided below: ::

    #include <gears/adl/get.hpp>
    #include <tuple>
    #include <iostream>

    namespace adl = gears::adl;

    namespace my {
    struct get_example {
        int x;
        int y;
    };

    template<size_t N>
    constexpr int get(const get_example& g) {
        return N == 0 ? g.x : g.y;
    }
    } // my

    int main() {
        auto tup = std::make_tuple("hello", 3.14);
        my::get_example f = {10, 11};
        std::cout << adl::get<0>(tup) << ' ' << adl::get<0>(f);
    }

Output:

.. code-block:: none

    hello 10

A list of functions that have ``adl::`` version can be found in the :ref:`API page <gears-modules-adl-api>`.
