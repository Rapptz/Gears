.. default-domain:: gcpp
.. highlight:: cpp
.. namespace:: gears::leaf
.. _gears-modules-leaf:

Leaf Module --- ``constexpr`` utilities
==========================================

*Included through* ``<gears/leaf.hpp>``

This module includes ``constexpr`` programming utilities such as strings, arrays, heterogeneous lists, and
standard library components that can be made ``constexpr`` but aren't. These are all made with C++11 enabled ``constexpr``
rather than the C++14 relaxed ``constexpr``. However, as a positive consequence it should work in both C++11 and C++14.

This module is split into multiple 'submodules' which are listed below.

.. toctree::

    leaf/string
    leaf/cstdlib

