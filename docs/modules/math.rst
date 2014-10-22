.. default-domain:: cpp
.. highlight:: cpp
.. namespace:: gears::math
.. _gears-modules-math:

Mathematics Module --- Algorithms, unbound integers, and constants
====================================================================

This module provides an implementation of common mathematical algorithms and an infinite precision integer.

Example usage: ::

    #include <gears/math.hpp>
    #include <iostream>

    namespace math = gears::math;

    // needed to use _x user defined literal
    using namespace gears::math::literals;

    int main() {
        auto lhs = 9384721983748274812387232191827321_x;
        auto rhs = 2937189237182973865769137697362736_x;
        std::cout << (lhs * rhs) << '\n';
        std::cout << math::factorial(10) << '\n';
    }

Output:

.. code-block:: none

    27564704404619880556797005156529364384954680388538087951954412110256
    3628800


.. _gears-modules-math-algorithm:

Algorithms
------------

*Included through* ``<gears/math/algorithm.hpp>``

.. function:: Integral fibonacci(Integral n)

    Calculates the nth :wiki:`fibonacci number`.

    :param n: The nth fibonacci number to calculate.
    :complexity: :math:`O(n)`
    :returns: The nth fibonacci number.

.. function:: constexpr Integral factorial(const Integral& n)

    Calculates the nth :wiki:`factorial`. This uses the naive
    recursive algorithm in order to maintain ``constexpr``
    compatibility with C++11.

    :param n: The nth factorial number to calculate.
    :complexity: :math:`O(n)`
    :returns: The nth factorial number.

.. function:: constexpr Integral gcd(const Integral& x, const Integral& y)

    Calculates the greatest common divisor between two numbers. The algorithm
    used is Euclid's algorithm.

    :param x: The left hand side.
    :param y: The right hand side.
    :complexity: See :wiki:`here <Euclidean_algorithm#Algorithmic_efficiency>`
    :returns: The greatest common divisor between the two numbers.

.. function:: Integral mod_pow(Integral base, Integral exp, const Integral& m)

    Calculates the modular exponentiation which is defined with the following equation:

    .. math::

        \rm\ base^{exp}\ mod\ m

    All numbers provided must be positive.

    :param base: The base number of the formula.
    :param exp: The exponent number of the formula.
    :param m: The modulo number of the formula.
    :complexity: :math:`O(\log n)` with respect to ``exp``.
    :returns: The result of the formula above.

.. function:: Integral sum_of_divisors(const Integral& number)

    Calculates the sum of divisors of a given integer. For example, the divisors for the number 12 are 1, 2, 3, 4,
    6, and 12. The sum of these numbers is 28. So ``sum_of_divisors(12)`` would return 28.

    :param number: The number to take the sum of divisors for.
    :complexity: :math:`O(\log n)`
    :returns: The sum of the number's divisors.

.. function:: bool is_prime(const Integral& number)

    Checks if a number is prime using the AKS primality test. This function is pretty slow for numbers that are
    relatively large.

    :param number: The number to test for primality.
    :complexity: See :wiki:`here <AKS_primality_test#History_and_running_time>`.
    :returns: A boolean indicating if the number is a prime.

.. function:: constexpr T abs(const T& n)

    Calculates the absolute value of a number. This uses the incredibly naive implementation and should only be used for its
    ``constexpr`` status, which the function in ``<cmath>`` lacks.

    :param t: The number to make positive.
    :complexity: :math:`O(1)`
    :returns: The absolute value of a number.

.. function:: constexpr auto min(Args&&... args)

    Calculates the minimum value of a list of numbers. It is recommended to not mix different types when using this
    function as it will promote types and make it unsafe. The types must meet the concept of LessThanComparable.

    :param args: The list of numbers to pass.
    :complexity: :math:`O(n)` with respect to ``sizeof...(args)``.
    :returns: The minimum number. If several values are the minimum number then the leftmost one is returned.

.. function:: constexpr auto max(Args&&... args)

    Calculates the maximum value of a list of numbers. It is recommended to not mix different types when using this
    function as it will promote types and make it unsafe. The types must meet the concept of LessThanComparable.

    :param args: The list of numbers to pass.
    :complexity: :math:`O(n)` with respect to ``sizeof...(args)``.
    :returns: The maximum number. If several values are the maximum number then the leftmost one is returned.

.. _gears-modules-math-constants:

Constants
-------------

*Included through* ``<gears/math/constants.hpp>``

These functions compute their respective named constants up to the precision of the type given. The maximum valid
precision that is guaranteed to be valid is ``std::numeric_limits<T>::digits10 + 2``. This is to allow proper roundtrip
calculations. For integer types the computed constant is floored. So ``pi<int>()`` would return 3. All constants provided
are ``constexpr``.

Example usage: ::

    #include <gears/math/constants.hpp>
    using namespace gears;

    template<typename T>
    constexpr T area(T radius) {
        return math::pi<T>() * radius * radius;
    }

    int main() {
        static_assert(area<double>(4) == 50.26548245743669, "...");
    }

.. function:: constexpr T pi() noexcept
              constexpr T half() noexcept
              constexpr T third() noexcept
              constexpr T root_two() noexcept
              constexpr T ln_two() noexcept
              constexpr T half_pi() noexcept
              constexpr T third_pi() noexcept
              constexpr T two_thirds_pi() noexcept
              constexpr T sixth_pi() noexcept
              constexpr T three_fourths_pi() noexcept
              constexpr T four_thirds_pi() noexcept
              constexpr T two_pi() noexcept

    Computes the above constants with the precision wanted. The constants are
    mapped as follows:

    ===================  ================
     Function              Constant
    ===================  ================
     pi                   :math:`\pi`
     half                 :math:`{}^{1}\!/_{2}`
     third                :math:`{}^{1}\!/_{3}`
     root_two             :math:`\sqrt{2}`
     ln_two               :math:`\ln(2)`
     half_pi              :math:`{}^{\pi}\!/_{2}`
     third_pi             :math:`{}^{\pi}\!/_{3}`
     two_thirds_pi        :math:`{}^{2\pi}\!/_{3}`
     sixth_pi             :math:`{}^{\pi}\!/_{6}`
     three_fourths_pi     :math:`{}^{3\pi}\!/_{4}`
     four_thirds_pi       :math:`{}^{4\pi}\!/_{3}`
     two_pi               :math:`2\pi`
    ===================  ================

    :tparam T: The type of precision needed.
    :complexity: :math:`O(1)`
    :returns: The constant with the precision wanted. See the table above.
