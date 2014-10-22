.. default-domain:: cpp
.. highlight:: cpp
.. namespace:: gears::io
.. _gears-modules-io:

I/O Module --- Suite of functions to aid usage of iostreams
=============================================================

*Included through* ``<gears/io.hpp>``

.. |pair| replace:: :cpp:`std::pair <utility/pair>`
.. |tuple| replace:: :cpp:`std::tuple <utility/tuple>`
.. |format| replace:: :ref:`gears-modules-io-format`

This module provides tools to help with iostreams, including prettyprinting, typesafe printf and more.

One of the first things the I/O module is useful for is for prettyprinting containers, tuples, and pairs. It is available in
the subinclude, ``prettyprint.hpp``. In order to enable the use of the prettyprinting functions, the usage
of ``using namespace gears::io::operators`` is required. The prettyprinting is done through the use of ``operator<<``.

The list it outputs is as follows:


============  ===================
 Type           Output
============  ===================
 |pair|         (a, b)
 Containers     [a, b, ..., n]
 |tuple|        (a, b, ..., n)
============  ===================

Example usage:

.. code-block:: cpp

    #include <gears/io.hpp>
    #include <vector>

    namespace io = gears::io;

    // needed for operator<< of standard library types
    using namespace gears::io::operators;

    int main() {
        std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        io::print("|0| + |0| = |1|\n", v.front(), v[1]);
        io::print("|0|", v);
    }


Output:

.. code-block:: none

    1 + 1 = 2
    [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]


.. _gears-modules-io-functions:

Functions
--------------

.. function:: void fprint(std::basic_ostream<Char, Trait>& out, const std::basic_string<Char, Trait>& str, const Args&... arguments)
              void fprint(std::basic_ostream<Char, Trait>& out, const Char* str, const Args&... args)

    This function is a type-safe alternative to :cpp:`std::fprintf <io/c/fprintf>` that uses a different format string and
    uses iostreams instead of regular C streams. It accepts any stream that is derived from
    :cpp:`std::ostream <io/basic_ostream>`. This function does **not** write a newline to the ending result or flush
    the stream.

    More information about the format string can be found in |format|.

    :param out: The output string to write to.
    :param str: The format string that mandates how formatting should be done. See |format|.
    :param arguments: The corresponding arguments used for the format string.
    :throws runtime_error: Thrown during error when parsing the format string.
    :throws out_of_range: Thrown when the index in a format string is out of bounds.
    :subinclude: fprint.hpp

.. function:: void print(const std::string& str, const Args&... arguments)
              void print(const char* str, const Args&... arguments)
              void print(const std::wstring& str, const Args&... arguments)
              void print(const wchar_t* str, const Args&... arguments)

    This function is a type-safe alternative to :cpp:`std::printf <io/c/printf>` and :cpp:`std::wprintf <io/c/wfprintf>`
    that uses a different format string using iostreams instead of regular C streams. Based on the string type provided
    it forwards the arguments to :func:`fprint` using either :cpp:`std::cout <io/cout>` or :cpp:`std::wcout <io/cout>`
    as the stream used to write to. This function does **not** write a newline to the ending result or flush the stream.

    More information about the format string can be found in |format|.

    :param str: The format string that mandates how formatting should be done. See |format|.
    :param arguments: The corresponding arguments used for the format string.
    :throws runtime_error: Thrown during error when parsing the format string.
    :throws out_of_range: Thrown when the index in a format string is out of bounds.
    :subinclude: print.hpp

.. function:: auto getline_until(std::basic_istream<Char, Trait>& in, std::basic_string<Char, Trait, Alloc>& str, Predicate p)

    Reads a string until a predicate is met. This function behaves similarly to :cpp:`std::getline <string/basic_string/getline>`
    except that rather than reading until a newline, it reads until a predicate given. The predicate given must have a
    signature of ``bool(const Char&)`` or ``bool(char)``. While this isn't strictly enforced, it's a good idea to not
    modify the characters as this might lead to unexpected behaviour.

    :param in: The input stream to read from.
    :param str: The string to write to.
    :param p: The predicate to use. Must return something convertible to bool.
    :returns: A reference to the input stream.
    :subinclude: getline.hpp

.. function:: auto lines(std::basic_istream<CharT, Traits>& in)

    Returns a range object to iterate through input lines. Best used with the range-based for loop.

    Example: ::

        #include <gears/io/lines.hpp>
        #include <iostream>
        #include <fstream>

        namespace io = gears::io;

        int main() {
            std::ifstream in("test.txt"); // could be any file
            for(auto&& line : io::lines(in)) {
                std::cout << line << '\n';
            }
        }

    .. admonition:: lines return type

        **Member functions**

        The return type of lines is a range object that defines a ``begin`` and an ``end`` member function
        for compatibility with the C++11 range-based for loop.

        **Iterator Information**

        The iterator returned by the member functions are input iterators that are copyable and movable. These
        iterators are expensive to copy so they should not be copied or moved too much.

        **Constructibility**

        The return type is CopyConstructible and MoveConstructible. It is not advised to do so however.

    :param in: The input stream to iterate lines with.
    :returns: An unspecified return type that meets the requirements set above.
    :subinclude: lines.hpp

.. _gears-modules-io-format:

Format String Syntax
-----------------------

The :func:`fprint` family of functions share the same format string syntax that allows it to communicate how
formatting should be done and how the arguments passed should be used.

At its core, format strings contain a parameter and a format specification wrapped around in 'pipes', i.e. ``|``
characters. In order to escape the ``|`` character, you should just add another one, i.e. ``||`` would produce ``|``.
Everything not enclosed in 'pipes' is considered literal text and untouched in the resulting text.

The grammar of the format string is as follows:

    .. productionlist:: sf
        format_string: "|" <`parameter`> [":" `format_spec`] "|"
        parameter: <integer>
        format_spec: [`fill`][`align`][`width`]["." `precision`][`verb`]*
        fill: "'" <any character>
        align: "<" | ">" | "^"
        width: <integer> | "*" <integer>
        precision: <integer> | "*" <integer>
        verb: "f" | "e" | "g" | "x" | "b" | "o" | "d" | "u" | "p" | "t"

In plain English, this means that format strings have two components, the parameter and the format specification. The
parameter tells the formatting function what parameter to obtain. The index starts at zero.

Examples: ::

    io::print("|0|", 1, 2); // 1
    io::print("|0| |1|", 1, 2); // 1 2
    io::print("|2|", 1, 2); // throws std::out_of_range
    io::print("|2|", 1, 2, 3); // 3

There is no 'automatic' indexing provided, so the user must provide the positional argument that it is located.

.. danger::

    Providing an incomplete format string such as ``|0`` or ``|0:.2`` can result in undefined behaviour
    or throw an exception. When in doubt, don't do it. No consistent attempts are made to check the format
    string for the sake of performance.


The format string also allows you to set the 'width' of an entry which would be equivalent to
:cpp:`std::setw <io/manip/setw>`. The syntax for this just requires having digits to denote the width. If the width
is given as a parameter then prefixing the index with an asterisk would set the width to that specific integral.

Examples: ::

    io::print("[|0:10|]", "hello"); // [     hello]
    io::print("[|0:*1|]", "hello", 10); // [     hello]

Of course, having a width that automatically fills with spaces isn't as useful as having to specify the alignment
and the fill character yourself. The format string allows for specifying the fill character by prefixing the
character with an apostrophe, ``'``, which is equivalent to :cpp:`std::setfill <io/manip/setfill>`. In terms of syntax,
having the fill character is the first thing in the format string after the colon. Of course, it is optional.

There are also three ways to set the alignment, which comes after the optional fill character specification. They are
as follows:

.. |left| replace:: :cpp:`std::left <io/manip/left>`
.. |right| replace:: :cpp:`std::right <io/manip/left>`
.. |internal| replace:: :cpp:`std::internal <io/manip/left>`

===========  ==========================
 Character     Equivalent Manipulator
===========  ==========================
 <             |left|
 >             |right|
 ^             |internal|
===========  ==========================

Examples are given below: ::

    io::print("[|0:'#10|]", "hello");  // [#####hello]
    io::print("[|0:'#<10|]", "hello"); // [hello#####]
    io::print("[|0:'#>10|]", "hello"); // [#####hello]
    io::print("[|0:<10|]", "hello");   // [hello     ]

Specifying the precision works the same way as specifying width, except it is prefixed with a period. It is equivalent to
:cpp:`std::setprecision <io/manip/setprecision>`. It comes after the width just like ``printf``.

Due to this format string being built for the standard C++ streams there are other ways of getting the formatting such as
:cpp:`std::hex <io/manip/hex>` and friends. These are called 'verbs' and look similarly to the type specifiers in ``printf``.
The major difference is that you could apply as many as you want and that all they handle are miscellaneous formatting. They
come right before the terminating pipe.

The table below gives the entire list of verbs and their effects on the stream. Note that they only apply to the
argument they are formatting on.

==========  =========================
 Verb        Equivalent Manipulator
==========  =========================
f           :cpp:`std::fixed <io/manip/fixed>`
e           :cpp:`std::scientific <io/manip/fixed>`
g           :cpp:`std::defaultfloat <io/manip/fixed>`
x           :cpp:`std::hex <io/manip/hex>`
o           :cpp:`std::oct <io/manip/hex>`
d           :cpp:`std::dec <io/manip/hex>`
p           :cpp:`std::showpos <io/manip/showpos>`
u           :cpp:`std::uppercase <io/manip/uppercase>`
b           :cpp:`std::showbase <io/manip/showbase>`
t           :cpp:`std::boolalpha <io/manip/boolalpha>`
==========  =========================

Various examples of the format string is given below: ::

    io::print("|0:.2f|\n", 1.23456); // 1.23
    io::print("|0:t| |1:t|\n", true, false); // true false
    io::print("|0:.3eu|\n", 7e+10); // 7.000E+010
    io::print("|0| |0:x| |0:xb| |0:xu| |0:xub|\n", 0xDEAD); // 57005 dead 0xdead DEAD 0XDEAD

