.. default-domain:: gcpp
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

.. _gears-modules-math-functions:

Functions
--------------

.. function:: void primes(Integral limit, Container& cont)


    Generates primes using a modified Sieve of Eratosthenes. The function will generate primes up to the limit provided.
    e.g. if limit is 100, then the last prime generated would be 97. The container must have an integral ``value_type``
    for best results. Currently this function only works on containers that provide the ``push_back`` function.
    This might be changed in the future. The first two primes (2 and 3) are always provided regardless of the limit given.

    :param limit: The upper limit of primes to generate.
    :param cont: The container to insert the primes to.
    :subinclude: generator.hpp

.. function:: void pythagorean_triples(Integral limit, Container& cont)

    Generates Pythagorean triples and puts the results into a container provided. The results are added to the container
    as if calling: ::

        cont.emplace_back(x, y, z)

    :param limit: The upper limit of Pythagorean triples to generate.
    :param cont: The container to emplace the Pythagorean triples.
    :complexity: :math:`O(n^2)` with respect to ``limit``.
    :subinclude: generator.hpp

.. _gears-modules-math-uintx:

Unbound Unsigned Integer
-----------------------------

*Included through* ``<gears/math/uintx.hpp>``

.. |buintx| replace:: :class:`basic_uintx`

There are often times when an unbound unsigned integer is required. Many other programming languages come with this
facility built-in into the standard library, including `C# <http://msdn.microsoft.com/en-us/library/system.numerics.biginteger%28v=vs.110%29.aspx>`_, `Java <http://docs.oracle.com/javase/7/docs/api/java/math/BigInteger.html>`_ and Python who has built-in support
in the language using ``int`` or ``long`` in Python 2.x. C++ has historically not had support for unbound integers, although from the C side of things there is `GMP <https://gmplib.org/>`_ and C++ has a large amount of `numeric libraries <https://github.com/search?l=C%2B%2B&q=biginteger&ref=opensearch&type=Repositories>`_. On the standard side of things there is `Boost.Multiprecision <http://www.boost.org/doc/libs/release/libs/multiprecision/doc/html/index.html>`_ but that is typically a wrapper around GMP.

The implementation in Gears is decently fast and provides a nice API but doesn't have the fastest speeds expected from GMP.
This unbound unsigned integer overloads all mathematical operators except the bitwise operators. The streaming
operators ``operator<<`` and ``operator>>`` are provided as well. In order to disable the streaming operators,
define ``GEARS_NO_IOSTREAM`` before including the file. There are two user-defined literals
provided under ``gears::math::literals`` to help with the construction of a |buintx|. An example is provided below.::

    using namespace gears::math::literals; // required

    auto one = 1902748734897198347123_x; // recommended way
    auto two = "89374128732819928123"_x; // also provided

.. class:: basic_uintx<Digit, Digits>

    Multi-precision unsigned integer. Basic usage does not need to modify the Digit or Digits template parameters, those are there for memory optimisations on rare cases when necessary. Both types should be unsigned if provided. A typedef is provided for
    common case called :type:`uintx`.

    :tparam Digit: The underlying type to store bits.
    :tparam Digits: The underlying type to store numbers.

    .. var:: static constexpr size_t digits10

        Equivalent to ``std::numeric_limits<Digit>::digits10``.
    .. var:: static constexpr size_t base

        Equivalent to :math:`10^x` where :math:`x` is :data:`digits10`.
    .. function:: basic_uintx()

        Default constructor. The default value is 0.
    .. function:: basic_uintx(Integral value)

        Constructs |buintx| from an integer type. |buintx| is then set to the value provided. If the value is negative, then
        it is made positive before hand.

        :param value: The value to set |buintx| to.
    .. function:: basic_uintx(const std::string& str)

        Constructs from a string. |buintx| is then set to the value provided from the string. If the string contains letters or
        special characters, the behaviour is undefined. The string must not represent a negative integer.

        :param str: The string to set the value of.
        :complexity: :math:`O(n^2)` with respect to ``str.size()``.

    .. function:: basic_uintx& operator+=(const basic_uintx& other)
                  basic_uintx operator+(const basic_uintx& other) const

        Adds two |buintx| together.

        :param other: The right hand side to add with.
        :complexity: :math:`O(3 \times n)` with respect to other's size.

    .. function:: basic_uintx& operator-=(const basic_uintx& other)
                  basic_uintx operator-(const basic_uintx& other) const

        Subtracts two |buintx|. If the value ends up negative, then the behaviour is
        undefined.

        :param other: The right hand side to subtract with.
        :complexity: :math:`O(3 \times n)` with respect to other's size.

    .. function:: basic_uintx& operator*=(const basic_uintx& other)
                  basic_uintx operator*(const basic_uintx& other) const

        Multiplies two |buintx|.

        .. todo::

            Improve complexity to be sub-quadratic.

        :param other: The right hand side to multiply with.
        :complexity: :math:`O(n^2)` with respect to other's size.

    .. function:: basic_uintx& operator/=(const basic_uintx& other)
                  basic_uintx operator/(const basic_uintx& other) const

        Divides two |buintx|. If ``other`` is zero, then an exception is thrown.

        .. todo::

            Improve complexity.

        :param other: The right hand side to divide with.
        :throws runtime_error: If division by zero occurs.
        :complexity: :math:`O(n^2)` with respect to other's size.

    .. function:: basic_uintx& operator%=(const basic_uintx& other)
                  basic_uintx operator%(const basic_uintx& other) const

        Implements modulo arithmetic with |buintx|. If ``other`` is zero, then an exception is thrown.

        .. todo::

            Improve complexity.

        :param other: The right hand side to modulo with.
        :throws runtime_error: If division by zero occurs.
        :complexity: :math:`O(n^2)` with respect to other's size.

    .. function:: bool operator==(const basic_uintx& other) const
                  bool operator!=(const basic_uintx& other) const
                  bool operator<(const basic_uintx& other) const
                  bool operator>(const basic_uintx& other) const
                  bool operator>=(const basic_uintx& other) const
                  bool operator<=(const basic_uintx& other) const

        Implements the logical operators for |buintx|.

        :param other: The right hand side of the comparison.
        :complexity: :math:`O(n)` with respect to the size.

    .. function:: const uintx& operator++()
                  uintx operator++(int)
                  const uintx& operator--()
                  uintx operator--(int)

        Increments or decrements a |buintx| by one. If the result ends up being negative then the behaviour is undefined.
        This is syntactic sugar for ``+= 1`` or ``-=1``.

    .. function:: explicit operator bool() const noexcept

        Checks if |buintx| is greater than 0.

        :complexity: :math:`O(1)`.
        :returns: A boolean indicating if the represented digits are greater than 0.

.. function:: To uintx_cast(const basic_uintx<U, V>& obj)

    @details Casts a uintx to another type. This type can be an integer type or a string type. To cast to a string,
    ``std::string`` must be the ``To`` type. If the underlying value of |buintx| does not fit in the type casted, then
    the behaviour is undefined.

    :tparam To: The type to cast to.
    :param obj: The |buintx| object to cast.
    :returns: The casted value.

.. type:: uintx

    A convenience typedef for ``basic_uintx<unsigned int, unsigned long long>``.
