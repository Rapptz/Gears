Welcome to gears' documentation!
=================================

Welcome to the official documentation for Gears. You can find all the documentation for
classes and functions in the :ref:`genindex` or you can use the :ref:`search` instead.

The complete contents are:

.. toctree::
    :maxdepth: 2

    tutorials
    modules

What is Gears?
----------------

Gears is a collection of utilities (henceforth now called "modules") that are helpful to C++11 programmers.
These include a large collection of modules ranging from the string module to the functional module. You can
consider Gears to be similar to Boost -- that is, a bunch of things that are there to help the typical programmer
with the repetitive things in C++.

Using Gears
--------------

Gears is a header-only library so there's no intermediate install step. Everything resides in the ``gears`` namespace.
For every submodule, they tend to have the subnamespace based on the submodule name. For example, if you were using the
ADL submodule, it'd be in the ``gears::adl`` subnamespace. The only submodule that does not follow this is the Utility
submodule, which only has a single namespace -- ``gears``.

Compiler Support
---------------------

Since Gears makes heavy use of C++11 features, only the compilers with the most support for C++11 are supported. At the
time of this writing, this only includes GCC 4.8.1 or higher and Clang 3.4 or higher. Visual Studio 2012 or lower are
not supported at all, and you might get lucky with some modules on Visual Studio 2013 although not explicitly supported.
