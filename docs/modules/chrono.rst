.. default-domain:: gcpp
.. highlight:: cpp
.. namespace:: gears::chrono
.. _gears-modules-chrono:

Chrono Module --- Time Utilities
===================================

.. sidebar:: Tutorial

    This page just hosts the API reference.

    A tutorial for this module will be coming soon.

*Included through* ``<gears/chrono.hpp>``

This module defines utilities that make working with the ``<chrono>`` header
easier and adds new tools for it as well.

One of the first things the chrono module is useful for is the creation of ``std::chrono::duration``
using the new C++11 user defined literal feature. The table below specifies the literals and their return value.

==========  ================
 Literal      Result
==========  ================
 \_h          hours
 \_min        minutes
 \_s          seconds
 \_ms         milliseconds
 \_us         microseconds
 \_ns         nanoseconds
==========  ================

All of these have ``unsigned long long`` and ``long double`` overloads. It's available through the subinclude
``literals.hpp``.

Example usage can be found below.

.. code-block:: cpp

    #include <gears/chrono/literals.hpp>
    #include <thread>
    #include <iostream>

    // this line is required
    using namespace gears::chrono::literals;

    void f() {
        std::this_thread::sleep_for(1.4_s); // 1.4 seconds
    }

    int main() {
        std::cout << "Going to sleep for 1.4 seconds...";
        f();
        std::cout << "\nDone!";
    }

.. _gears-modules-chrono-classes:

Classes
----------

.. class:: basic_stopwatch<Clock>

    This class is used as a basic way of measuring time. It defines
    the most basic stopwatch representation that could have its internal
    clock configured to give you the flexibility you desire.

    :tparam Clock: The internal clock used to calculate time.

    .. type:: time_point
    .. type:: duration
    .. type:: rep
    .. type:: period

        Redirects to the internal clock's respective typedef.
    .. function:: basic_stopwatch()

        The default constructor. Does not start the stopwatch.
    .. function:: void start()

        Starts the stopwatch.
    .. function:: void stop()

        Stops the stopwatch.
    .. function:: void reset()

        Resets the stopwatch and pauses it. Meaning that it sets the elapsed time to zero.

        :post-condition: :func:`is_running` is ``false``.
    .. function:: void restart()

        Restarts the stopwatch. Meaning that it sets the elapsed time to zero and starts the stopwatch again.

        This is equivalent to doing:::

            my_stopwatch.reset();
            my_stopwatch.start();

    .. function:: rep elapsed<Duration>()

        Returns the elapsed time. The elapsed time is considered the time since the stopwatch was started via the
        :func:`start` member function. Consecutive calls to this function would not stop
        the watch and would simply return the elapsed time since the starting point.

        .. note::

            This function does not stop the watch. Use :func:`stop` before hand to do so.

        :tparam Duration: The duration to cast the elapsed time to. Defaults to ``std::chrono::milliseconds``.

    .. function:: is_running() const

        Checks if the stopwatch is running.

.. type:: stopwatch

    A convenient typedef for a :class:`basic_stopwatch\<Clock>` with ``std::chrono::high_resolution_clock`` as the internal clock.

Example usage of the :class:`stopwatch <basic_stopwatch\<Clock>>` class is given below:::

    #include <gears/chrono.hpp>
    #include <thread>
    #include <iostream>

    namespace ch = gears::chrono;

    void f() {
        using namespace ch::literals;
        std::this_thread::sleep_for(1.16_s);
    }

    int main() {
        ch::stopwatch w;
        w.start();
        f();
        w.stop();
        std::cout << w.elapsed() << ' ' << w.elapsed<std::chrono::seconds>();
    }

Possible Output:

.. code-block:: none

    1159 1
