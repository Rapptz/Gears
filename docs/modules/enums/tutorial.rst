:orphan:

.. default-domain:: gcpp
.. highlight:: cpp
.. _gears-tutorials-enums:

Enums Tutorial
==================

This section describes how to use the :ref:`Enums module <gears-modules-enums>` and its motivation for its existence.

Motivation
-------------

C++ has historically allowed enums to be used as a way to make bit flags. The syntax tends to be pretty intuitive: ::

    enum flags {
        a = 0,
        b = 1 << 1,
        c = 1 << 2
    };

    void set_flag(unsigned int x) {
        // stuff
    }

    set_flag(a | b); // works

This has a couple of problems however.

1. Regular ``enum`` s are not type safe as shown here. There's an implicit conversion to the underlying type.
2. Changing the signature from ``unsigned int x`` to ``flags x`` would make the code above fail to compile.
3. The ``a``, ``b``, and ``c`` values are essentially 'global' if not put under a namespace.

C++11 solved this issue by introducing :cpp:`enum classes <language/enum>` which are type safe and have their own scope.
Converting the code above should be fairly simple in theory: ::


    enum class flags : unsigned {
        a = 0,
        b = 1 << 1,
        c = 1 << 2
    };

    void set_flag(flags x) {
        // stuff
    }

    set_flag(flags::a | flags::b); // works? Nope.

Unfortunately, just like point 2 above this would fail to compile due to the operators essentially not being overloaded.
This module aims to solve this issue by providing the operators to allow usage of both regular enums and enum classes
as bit flags.

.. _gears-tutorials-enums-usage:

Usage
---------

Adapting from the example above, using this module would make its usage fairly simple. Just a single include and a using
declaration would get the code to compile: ::

    #include <gears/enums.hpp>
    using namespace gears::enums::operators; // bring operators to scope

    enum class flags : unsigned {
        a = 0,
        b = 1 << 1,
        c = 1 << 2
    };

    void do_work(flags x) {
        // stuff
    }

    do_work(flags::a | flags::b); // work!

All bitwise operators are overloaded along with ``operator==`` and ``operator!=``.

However, some people find that syntax hard to understand and it tends to get complicated when many flags are active so this
module also defines other ways of activating, deactivating, or checking flags. For example, the code above could use this
instead to activate the flags: ::

    do_work(enums::activate_flags(flags::a, flags::b));

At this point, maybe the ``do_work`` function wants to check for the existence of a flag and print based on it. There are two
ways of doing this, using operators or the helper functions in the enums module. Both will be shown for completeness: ::

    void do_work(flags x) {
        // operator way
        if((x & flags::b) == flags::b) {
            std::cout << "flag b is active";
        }

        // helper function way
        if(enums::has_flags(x, flags::b)) {
            std::cout << "flag b is active";
        }
    }

Many more functions are provided and could be found through the :ref:`API page <gears-modules-enums>`.
