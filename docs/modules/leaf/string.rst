.. default-domain:: gcpp
.. highlight:: cpp
.. namespace:: gears::leaf
.. _gears-modules-leaf-string:

String --- ``constexpr`` enabled string class and more
=======================================================

.. sidebar:: Tutorial

    This page just hosts the API reference.

    A tutorial for this module will be coming soon.

*Included through* ``<gears/leaf/string.hpp>``

.. |stdstr| replace:: :cpp:`std::string <string/basic_string>`
.. |str| replace:: :class:`basic_string`

This submodule provides a ``constexpr`` alternative to |stdstr|. It aims to have a similar API to
|stdstr|. Its main component is the |str| class. Due some limitations in how the data itself
is stored, some operations could not be provided out right such as substring operations.

.. class:: basic_string

    This class provides a ``constexpr`` enabled interface for
    ``std::basic_string``. Note, however, that it doesn't mimic the entire
    interface, just the parts that make sense. The only part of the interface
    that is provided are the immutable parts. The reason for this is to keep
    compatibility with C++11, where ``constexpr`` functions that modify variables
    are not allowed. The string must have a null terminator at position ``N``.
    A character trait class could be provided to customise the comparisons
    that the class implements. The only requirements for the interface is that
    it provides the following ``constexpr``, ``noexcept``, ``static`` member functions: ::

        static constexpr bool eq(char_type);
        static constexpr bool lt(char_type);
        static constexpr int_type to_int_type(char_type);
        static constexpr char_type to_char_type(int_type);

    Some member functions can be exposed through the use of a macro denoting
    C++14 support is available. This macro is ``GEARS_META_HAS_CPP14``. Currently,
    it is set to ``1`` if compiling on Clang 3.4 or higher.

    :tparam CharT: The internal character type to store.
    :tparam N: The size of the string literal with the null terminator included.
    :tparam Traits: The character traits class to do comparison with.

    .. type:: traits_type

        Equivalent to ``Traits``.
    .. type:: value_type

        Equivalent to ``typename Traits::char_type``.
    .. type:: size_type

        Equivalent to ``std::size_t``.
    .. type:: difference_type

        Equivalent to ``std::ptrdiff_t``.
    .. type:: reference

        Equivalent to ``value_type&``.
    .. type:: const_reference

        Equivalent to ``const value_type&``.
    .. type:: pointer

        Equivalent to ``value_type*``.
    .. type:: const_pointer

        Equivalent to ``const value_type*``.
    .. type:: iterator

        Equivalent to ``pointer``.
    .. type:: const_iterator

        Equivalent to ``const_pointer``.
    .. member:: static constexpr size_type npos = -1

        Represents a position not found.
    .. function:: constexpr basic_string(const CharT& arr[N])

        Constructs a basic_string from a character array.
        The character array must have a null terminator as its last
        character.

        :param arr: The character array to construct with.

    .. function:: constexpr size_type size() const noexcept
                  constexpr size_type length() const noexcept

        Returns the size of the string without the null terminator.
    .. function:: constexpr bool empty() const noexcept

        Checks if the string is empty. A string
        is considered empty if the only character it has is the
        null terminator.

        :returns: `true` if empty, `false` otherwise.

    .. function:: constexpr size_type capacity() const noexcept

        Returns the capacity of the string. i.e. ``N``.
    .. function:: constexpr size_type max_size() const noexcept

        Returns the maximum size of the string. i.e. ``N``.
    .. function:: constexpr const_reference operator[](size_type index) const noexcept

        Returns a reference to a character without
        bounds checking at the specified position. Note that
        accessing an out of bounds character is undefined behaviour.
        Use :func:`at` instead to get a compile time error when out of bounds.
        In C++14, undefined behaviour in a constant expression results
        in a compilation error.

        :param index: The specified position to get the character at.
        :returns: A reference to the character.

    .. function:: constexpr const_reference at(size_type index) const

        Returns a reference to a character with bounds
        checking at a specified position. Bounds checking is done
        by throwing an exception of type ``std::out_of_range``. When
        used in a constant expression, this turns into a compile-time
        error.

        :throws std\:\:out_of_range: Thrown when the position is out of bounds.
        :param index: The specified position to get the character at.
        :returns: A reference to the character.

    .. function:: constexpr const_reference front() const noexcept

        Accesses the first character. On an
        empty string this would return the null character.

        :returns: A reference to the first character.

    .. function:: constexpr const_reference back() const noexcept

        Accesses the last character. On an
        empty string this would result in undefined behaviour.
        In C++14 undefined behaviour in a constant expression
        ends in a compilation error.

        :returns: A reference to the last character.

    .. function:: constexpr const_pointer data() const noexcept

        Returns a pointer to the first character of the string. Available
        only if ``GEARS_META_HAS_CPP14`` is defined.
    .. function:: constexpr const_pointer c_str() const noexcept

        Returns a pointer to the first character of the string. Available
        only if ``GEARS_META_HAS_CPP14`` is defined.
    .. function:: constexpr const_iterator begin() const noexcept

        Returns an iterator pointing to the first element. Available
        only if ``GEARS_META_HAS_CPP14`` is defined.
    .. function:: constexpr const_iterator cbegin() const noexcept

        Returns an iterator pointing to the first element. Available
        only if ``GEARS_META_HAS_CPP14`` is defined.
    .. function:: constexpr const_iterator end() const noexcept

        Returns an iterator pointing to the one past the last element. Available
        only if ``GEARS_META_HAS_CPP14`` is defined.
    .. function:: constexpr const_iterator cend() const noexcept

        Returns an iterator pointing to the one past the last element. Available
        only if ``GEARS_META_HAS_CPP14`` is defined.
    .. function:: constexpr size_type find(CharT c, size_type pos = 0) const noexcept
                  constexpr size_type find_first_of(CharT c, size_type pos = 0) const noexcept

        Finds a character in the string. This
        function finds the first occurrence of the character.
        If the character is not found, :member:`npos` is returned.

        :param c: The character to look for.
        :param pos: The position to start the search at.
        :returns: The position of the character found.

    .. function:: constexpr size_type find(const basic_string<CharT, M, Traits>& s, size_type pos = 0) const noexcept

        Finds a substring in the string. This function
        finds the first occurrence of the substring. If the substring
        is not found, :member:`npos` is returned.

        :param s: The substring to look for.
        :param pos: The position to start the search at.
        :returns: The position of the substring.

    .. function:: constexpr size_type rfind(CharT c, size_type pos = npos) const noexcept
                  constexpr size_type find_last_of(CharT c, size_type pos = npos) const noexcept

        Finds the last character in the string. This
        function finds the last occurrence of the character.
        If the character is not found, :member:`npos` is returned.

        :param c: The character to look for.
        :param pos: The position to start the search at.
        :returns: The position of the character found.

    .. function:: constexpr size_type rfind(const basic_string<CharT, M, Traits>& s, size_type pos = npos) const noexcept

        Finds the last substring in the string. This function
        finds the last occurrence of the substring. If the substring
        is not found, :member:`npos` is returned.

        :param s: The substring to look for.
        :param pos: The position to start the search at.
        :returns: The position of the substring.

    .. function:: constexpr size_type find_first_of(const basic_string<CharT, M, Traits>& s, size_type pos = 0) const noexcept

        Finds the first occurrence of characters. This
        function searches through the character set provided and
        searches the first character that matches one of the
        characters in the character set, returning its position.
        If a character isn't found or the character set is empty
        then :member:`npos` is returned.

        :param s: The character set to look through.
        :param pos: The position to start the search at.
        :returns: The position of the found character.

    .. function:: constexpr size_type find_first_not_of(CharT c, size_type pos = 0) const noexcept

        Finds the first absence of a character.
        This function searches for the position of the
        first character not equal to the one provided. If the
        character is not found, then :member:`npos` is returned.

        :param c: The character to search for.
        :param pos: The position to start the search at.
        :returns: The position of the first character not equal to ``c``.

    .. function:: constexpr size_type find_first_not_of(const basic_string<CharT, M, Traits>& s, size_type pos = 0) const noexcept

        Finds the first absence of characters.
        This function searches for the position of the
        first character not equal to the ones provided. If the
        character is not found, then :member:`npos` is returned.

        :param s: The character set to search for.
        :param pos: The position to start the search at.
        :returns: The position of the first absent character.

    .. function:: constexpr size_type find_last_of(const basic_string<CharT, M, Traits>& s, size_type pos = npos) const noexcept

        Finds the last occurrence of characters. This
        function searches through the character set provided and
        finds the first character that matches one of the characters,
        returning its position. If the character isn't found then
        :member:`npos` is returned. Note that this searches backwards. It's
        the rfind analogous version of find_first_of.

        :param s: The character set to search through.
        :param pos: The position to start the search at.
        :returns: The position of the found character.

    .. function:: constexpr size_type find_last_not_of(CharT c, size_type pos = npos) const noexcept

        Finds the last absence of a character.
        This function searches for the position of the
        first character not equal to the one provided. If the
        character is not found, then :member:`npos` is returned.

        :param c: The character to search for.
        :param pos: The position to start the search at.
        :returns: The position of the first character not equal to ``c``.

    .. function:: constexpr size_type find_last_not_of(const basic_string<CharT, M, Traits>& s, size_type pos = npos) const noexcept

        Finds the last absence of characters.
        This function searches for the position of the
        first character not equal to the ones provided. If the
        character is not found, then :member:`npos` is returned.

        :param s: The character set to search for.
        :param pos: The position to start the search at.
        :returns: The position of the first absent character.

    .. function:: constexpr int compare(const basic_string<CharT, M, Traits>& s) const noexcept

        Compares two strings together. Note that
        this does not use ``Traits::compare``, but ``Traits::eq`` and
        ``Traits::lt``. The results are as follows, assuming
        ``str`` is the current string:

        +-------------+--------+
        | Expression  | Result |
        +=============+========+
        | str < s     | -1     |
        +-------------+--------+
        | str > s     | \+1    |
        +-------------+--------+
        | str == s    |  0     |
        +-------------+--------+

        :param s: The other string to compare against.
        :returns: The result of the table above.


.. function:: constexpr basic_string<CharT, N> make_string(const CharT& arr[N])

    A factory function to create a ``constexpr`` enabled
    string. This is meant to be used with string literals and
    is the preferred way to create the string instances.

    :param arr: The string literal to construct the string with.
    :returns: A |str| instance containing the literal.


.. function:: constexpr bool operator==(const basic_string<CharT, N, Traits>& lhs, const basic_string<CharT, M, Traits>& rhs) noexcept
              constexpr bool operator!=(const basic_string<CharT, N, Traits>& lhs, const basic_string<CharT, M, Traits>& rhs) noexcept

    Compares two strings if they're equal or
    not equal. This uses ``Traits::eq`` to do the equality
    comparison.

    :param lhs: The left hand side of the expression.
    :param rhs: The right hand side of the expression.

.. function:: constexpr bool operator<(const basic_string<CharT, N, Traits>& lhs, const basic_string<CharT, M, Traits>& rhs) noexcept
              constexpr bool operator<=(const basic_string<CharT, N, Traits>& lhs, const basic_string<CharT, M, Traits>& rhs) noexcept
              constexpr bool operator>(const basic_string<CharT, N, Traits>& lhs, const basic_string<CharT, M, Traits>& rhs) noexcept
              constexpr bool operator>=(const basic_string<CharT, N, Traits>& lhs, const basic_string<CharT, M, Traits>& rhs) noexcept

    Lexicographically compares two strings. Compares two strings as if using
    :cpp:`std::lexicographical_compare <algorithm/lexicographical_compare>`.
    The comparison is done with ``Traits::lt``.

    :param lhs: The left hand side of the expression.
    :param rhs: The right hand side of the expression.

.. function:: constexpr auto operator+(const basic_string<CharT, N, Traits>& lhs, const basic_string<CharT, M, Traits>& rhs) noexcept
              constexpr auto operator+(const basic_string<CharT, N, Traits>& lhs, CharT rhs) noexcept
              constexpr auto operator+(CharT lhs, const basic_string<CharT, N, Traits>& rhs) noexcept

    Appends two strings together or a string with a character. The resulting
    string ends in a null terminator as if calling
    ``Traits::to_char_type(0)``.

    :param lhs: The left hand side of the expression.
    :param rhs: The right hand side of the expression.
    :returns: The concatenated string.

