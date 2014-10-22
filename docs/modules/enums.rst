.. default-domain:: cpp
.. highlight:: cpp
.. namespace:: gears::enums
.. _gears-modules-enums:

Enums Module --- Support for enum classes as bitmasks
=======================================================

*Included through* ``<gears/enums.hpp>``

This module is meant to help with the usage of enums as bitmasks. C++11 has added support for strongly typed enums through
the usage of ``enum class`` or ``enum struct``. A big problem with using the strongly typed enums is that the usual
operators are unavailable for usage. For example, the following code is not well formed:::

    enum class test {
        one = 1 << 0,
        two = 1 << 1
    };

    int main() {
        auto x = test::one & test::two;
    }

The purpose of this module is to aid in the usage of enums by making it a little bit easier than having to define
the entire set of operators yourself. To fix the error above, all you have to do is the following:::

    #include <gears/enums.hpp>
    using namespace gears::enums::operators;

    enum class test {
        one = 1 << 0,
        two = 1 << 1
    };

    int main() {
        auto x = test::one & test::two;
    }


Functions
-----------

.. function:: constexpr Enum operator~(const Enum& x) noexcept
              constexpr Enum operator|(const Enum& lhs, const Enum& rhs) noexcept
              constexpr Enum operator&(const Enum& lhs, const Enum& rhs) noexcept
              constexpr Enum operator^(const Enum& lhs, const Enum& rhs) noexcept
              Enum& operator|=(Enum& lhs, const Enum& rhs) noexcept
              Enum& operator&=(Enum& lhs, const Enum& rhs) noexcept
              Enum& operator^=(Enum& lhs, const Enum& rhs) noexcept
              constexpr bool operator!=(const Enum& lhs, const Enum& rhs) noexcept
              constexpr bool operator!=(const Enum& lhs, const UnderlyingType& rhs) noexcept
              constexpr bool operator!=(const UnderlyingType& lhs, const Enum& rhs) noexcept
              constexpr bool operator==(const Enum& lhs, const Enum& rhs) noexcept
              constexpr bool operator==(const Enum& lhs, const UnderlyingType& rhs) noexcept
              constexpr bool operator==(const UnderlyingType& lhs, const Enum& rhs) noexcept

    Implements bitwise and comparison operators on enums and enum classes. The purpose of these
    overloads is to allow enum classes to be used as bit flags easier. These are all located under
    the subnamespace ``gears::enums::operators`` so a ``using`` statement is required to bring
    them under scope. If ``Enum`` is not an enumerator type, then these operators do not
    participate in overload resolution. ``Underlying`` is the underlying type of the
    enumerator, received through :cpp:`std::underlying_type <types/underlying_type>`.

    :subinclude: operators.hpp

.. function:: constexpr Underlying to_underlying(Enum x) noexcept

    Casts an enumerator to its underlying type. This is equivalent to calling:::

        static_cast<typename std::underlying_type<Enum>::type>(x);

    :param x: The enumerator to cast.
    :returns: The value of the enum in its underlying type.
    :subinclude: helpers.hpp

.. function:: constexpr Enum activate_flags(const Enum& first, const Enum& second, Enums&&... rest) noexcept

    Activates the flags specified. This function returns an enum type containing all the argument flags activated.
    The flags are activated as if invoking ``operator|`` on the values.

    :param first: The first bit flag to activate.
    :param second: The second bit flag to activate.
    :param rest: The rest of the flags to activate.
    :returns: An enumerator with the flags activated.
    :subinclude: helpers.hpp

.. function:: Enum& set_flags(Enum& flag, Enums&&... flags) noexcept

    Activates the flags specified by ``flags`` and then sets the result to the ``flag`` enumerator. Essentially,
    this is the same as doing:::

        enum class stuff {
            a = 1 << 0,
            b = 1 << 1,
            c = 1 << 2
        };

        stuff x = activate_flags(stuff::a, stuff::b);

    :param flag: The enumerator to set the flags to.
    :param flags: The flags to activate.
    :returns: A reference to the enumerator being set.
    :subinclude: helpers.hpp

.. function:: Enum& remove_flags(Enum& flag, Enums&&... flags) noexcept

    Deactivates the flags specified by ``flags`` and then sets the result to the ``flag`` enumerator.
    This is the opposite of :func:`set_flags`.

    :param flag: The enumerator to set the flags to.
    :param flags: The flags to deactivate.
    :returns: A reference to the enumerator being set.
    :subinclude: helpers.hpp

.. function:: constexpr bool has_flags(const Enum& flag, Enums&&... flags) noexcept

    Checks if the flags specified by ``flags`` are all set in the enumerator ``flag``.

    :param flag: The enumerator to check.
    :param flags: The flags to see if they're set.
    :returns: ``true`` if all the flags are set, ``false`` otherwise.
    :subinclude: helpers.hpp
