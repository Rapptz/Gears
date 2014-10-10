.. _gears-tutorial-optparse:
.. highlight:: cpp
.. default-domain:: cpp

Optparse Tutorial
=====================

The following sections will walk you through the using the optparse
module along with things such as customisation. All code snippets are assumed
to be under the namespace alias `opt`. You can get this behaviour by
doing `namespace opt = gears::optparse`. All examples are also assumed
to be compiled into an executable called `dev`.

.. _gears-tutorial-optparse-basics:

Basics
-----------

We begin using the module with an incredibly simple example. This example
just declares a parser and parses the arguments.

.. code-block:: cpp

    #include <gears/optparse.hpp>
    namespace opt = gears::optparse;

    int main(int argc, char** argv) {
        opt::option_parser parser;
        parser.parse(argv, argv + argc);
    }

When this is executed, you'll notice that all the errors
are handled gracefully for you and the help message is automatically
provided for you.

.. code-block:: console

    $ ./dev
    $ ./dev --help
    usage: ./dev [options...]

    options:
        -h, --help         shows this message and exits
    $ ./dev --test
    usage: ./dev [options...]
    ./dev: error: unrecognised option '--test'

Command line parsing tends to involve multiple options and values. As you
may have noticed earlier, this module uses the POSIX/Unix standards for
passing command line options. The rules are simple:

- Long options start with ``--``.
- Short options start with ``-``.
- Values can be specified through a space or an equal sign for key-value pairs.
- Short options can be concatenated (this will be shown later).
- A sole ``--`` delimits positional arguments and command line options (this will be shown later).

Currently, there's a big problem: our program doesn't do anything!

.. _gears-tutorials-optparse-a-little-more-involved:

A Little More Involved
-------------------------

For this example, we'll add two command line options. One that takes in a
value, and another that doesn't.

.. code-block:: cpp

    #include <gears/optparse.hpp>
    namespace opt = gears::optparse;

    int main(int argc, char** argv) {
        opt::option_parser parser = {
            { "quiet", "print minimal info" },
            { "compression", 'c', "sets compression level", opt::value<int>() }
        };

        auto&& args = parser.parse(argv, argv + argc);

        if(args.options.is_active("compression")) {
            if(!args.options.is_active("quiet")) {
                std::cout << "The compression level is: ";
            }
            std::cout << args.options.get<int>('c') << '\n';
        }
        else {
            std::cout << "Compression is not set\n";
        }
    }

And here's running it:

.. code-block:: console

    $ ./dev
    Compression is not set
    $ ./dev -h
    usage: ./dev [options...]

    options:
        -h, --help          shows this message and exits
            --quiet         print minimal info
        -c, --compression   sets compression level
    $ ./dev -c 10
    The compression level is: 10
    $ ./dev --quiet --compression=20
    20
    $ ./dev --compression
    usage: ./dev [options...]
    ./dev: error: option '--compression' requires an argument


A couple things to note:

- The results of the parsing is sent to an ``arguments`` struct.
- You can access the options by going to its options member.
- You query if the option is currently active through the ``is_active`` member function.
- You can ask for an option through its short or  long name.
- An error is shown if an argument is not found.

.. _gears-tutorials-optparse-positional-args:

Introducing Positional Arguments
-----------------------------------

For this example, we'll introduce a positional argument and multiplies the
number by four. If a verbose flag is set, then it'll print a sentence
explaining the computation.

.. code-block:: cpp

    #include <gears/optparse.hpp>
    namespace opt = gears::optparse;

    int main(int argc, char** argv) {
        opt::option_parser parser = {
            { "verbose", "prints the computation" }
        };

        parser.usage = "[option] number";
        parser.description = "Multiplies a number by four";

        auto&& args = parser.parse(argv, argv + argc);

        if(args.positional.empty()) {
            parser.error("no number given");
        }

        int number = std::stoi(args.positional.front());

        if(args.options.is_active("verbose")) {
            std::cout << number << " * 4 = " << number * 4 << '\n';
        }
        else {
            std::cout << number * 4 << '\n';
        }
    }


And of course, running it shows this:

.. code-block:: console

    $ ./dev
    usage: ./dev [option] number
    ./dev: error: no number given
    $ ./dev -h
    usage: ./dev [option] number

    Multiplies a number by four

    options:
        -h, --help            shows this message and exits
            --verbose         prints the computation
    $ ./dev 10
    40
    $ ./dev --verbose 19
    19 * 4 = 76
    $ ./dev 19 --verbose
    76


A couple notes:

- The order of positional and optional arguments matter
- Positional arguments are stored under the positional member as strings.

As you can see, you can modify the output of the ``--help`` message through the
usage and description members. Another way to modify the ``--help`` message
is through the ``epilogue`` member which would be the message printed at the end of
the ``--help`` message.

Working with positional arguments that expect a specific type other than
string can be a little annoying. In the next section, we'll talk about the different
kinds of values we can store in an option.

.. _gears-tutorials-optparse-types-value:

Different Types of Values
----------------------------

This example builds on the other example by automatically handling the conversion
of the positional arguments by using an optional argument instead.

.. code-block:: cpp

    #include <gears/optparse.hpp>
    namespace opt = gears::optparse;

    int main(int argc, char** argv) {
        opt::option_parser parser = {
            { "verbose", "prints the computation" },
            { "numbers", "the numbers to compute", opt::list<std::vector<int>>(2), opt::trait::required },
        };

        parser.description = "Multiplies two numbers together";
        auto&& args = parser.parse(argv, argv + argc);
        auto&& numbers = args.options.get<std::vector<int>>("numbers");

        if(args.options.is_active("verbose")) {
            std::cout << numbers[0] << " * " << numbers[1] << " = " << numbers[0] * numbers[1] << '\n';
        }
        else {
            std::cout << numbers[0] * numbers[1] << '\n';
        }
    }


Introduced in this example is the trait enum which is used as a bit flag that is
used to modify the behaviour of the option. In this case, the trait given is that
the option is required to continue.

Running the the program gives the following output:

.. code-block:: console

    $ ./dev
    usage: ./dev [options...]
    ./dev: error: missing required option '--numbers'
    $ ./dev --numbers 19 20
    380
    $ ./dev --verbose --numbers 19 20
    19 * 20 = 380
    $ ./dev --verbose --numbers
    usage: ./dev [options...]
    ./dev: error: option '--numbers' requires 2 arguments


Other types of values can be seen in this demonstrative example:

.. code-block:: cpp

    #include <gears/optparse.hpp>
    namespace opt = gears::optparse;

    int main(int argc, char** argv) {
        int stuff = 0;
        opt::option_parser parser = {
            { "modify", 'm', "modifies a variable in C++", opt::bind_to(stuff) },
            { "const", 'c', "always returns 42", opt::constant(42) },
            { 'I', "include directories", opt::compose<std::vector<std::string>>() }
        };

        auto&& args = parser.parse(argv, argv + argc);

        if(args.options.is_active('I')) {
            std::cout << "include directories:\n";
            for(auto&& i : args.options.get<std::vector<std::string>>('I')) {
                std::cout << i << '\n';
            }
        }

        std::cout << "stuff variable: " << stuff << '\n';
        if(args.options.is_active('c')) {
            std::cout << "constant: " << args.options.get<int>('c') << '\n';
        }
    }

And the output is as follows:

.. code-block:: console

    $ ./dev
    stuff variable: 0
    $ ./dev -m 10 -c
    stuff variable: 10
    constant: 42
    $ ./dev -cm 10
    stuff variable: 10
    constant: 42
    $ ./dev -I "/usr/include" -cm 42 -I "."
    include directories:
    /usr/include
    .
    stuff variable: 42
    constant: 42

.. _gears-tutorials-optparse-advanced-usage:

Advanced Usage
-----------------

This section details more advanced usage including subcommands, custom
error handling, and using custom parsers to further customise optparse
to your liking.

.. _gears-tutorials-optparse-using-subcommands:

Using Subcommands
~~~~~~~~~~~~~~~~~~~

The optparse module provides support for subcommands that allow the
usage of command line interfaces similar to those found in ``git``, ``svn``,
and ``hg``. Examples of subcommands include things such as ``git add``, ``git commit``,
and ``git checkout``, you get the message. Subcommands are very easy to register,
just look at the following example which implements a basic two command calculator
to do some arithmetic:

.. code-block:: cpp

    #include <gears/optparse.hpp>
    namespace opt = gears::optparse;

    int main(int argc, char** argv) {
        opt::option_parser parser;
        int lhs = 0;
        int rhs = 0;
        parser.usage = "<calculation> [options...]";
        parser.description = "Calculates a binary expression through subcommands.";


        opt::option_set common_options = {
            { "left", 'l', "the left hand side of the expression (default: 0)", opt::bind_to(lhs) },
            { "right", 'r', "the right hand side of the expression (default: 0)", opt::bind_to(rhs) },
            { "verbose", "shows verbose calculation" }
        };

        parser.add_subcommand({ "add", "adds two numbers", common_options });
        parser.add_subcommand({ "subtract", "multiplies two numbers", common_options });
        parser.add_subcommand({ "multiply", "subtracts two numbers", common_options });

        auto&& args = parser.parse(argv, argv + argc);
        bool is_verbose = args.options.is_active("verbose");

        if(args.subcommand.empty()) {
            parser.error("no calculation given");
        }

        if(args.subcommand == "add") {
            if(is_verbose) {
                std::cout << lhs << " + " << rhs << " = ";
            }
            std::cout << lhs + rhs << '\n';
        }
        else if(args.subcommand == "subtract") {
            if(is_verbose) {
                std::cout << lhs << " - " << rhs << " = ";
            }
            std::cout << lhs - rhs << '\n';
        }
        else if(args.subcommand == "multiply") {
            if(is_verbose) {
                std::cout << lhs << " * " << rhs << " = ";
            }
            std::cout << lhs * rhs << '\n';
        }
    }

Running the executable gives us the following:

.. code-block:: console

    $ ./dev
    usage: ./dev <calculation> [options...]
    ./dev: error: no calculation given
    $ ./dev -h
    usage: ./dev <calculation> [options...]

    subcommands
        add                     adds two numbers
        subtract                multiplies two numbers
        multiply                subtracts two numbers

    options:
        -h, --help         shows this message and exits
    $ ./dev multiply -h
    usage: ./dev multiply [options..]

    options:
        -h, --help            shows this message and exits
        -l, --left            the left hand side of the expression (default: 0)
        -r, --right           the right hand side of the expression (default: 0)
            --verbose         shows verbose calculation
    $ ./dev multiply -l 10 -r 20
    200
    $ ./dev add -l 30 -r 40 --verbose
    30 + 40 = 70
    $ ./dev subtract -l 50 -r 45
    5

There are a lot of new things shown here. Some important things to notice:

- Every subcommand has its own usage message that can be customised.
- Every subcommand has its own list of options.
- Every subcommand is printed through the main program's ``--help`` message.
- The active subcommand name can be retrieved through the ``subcommand`` member.
- The options member automatically updates to the active subcommand.
- Options can be stored in an option_set class and shared.

The API for subcommands is simple enough to not complicate the main querying code.

@subsection custom_parser Custom Parsers and Actions

The optparse module parses things based on something called an action. An
action takes in a key and a value and then returns the result of parsing. The
actions are typically abstracted away when using the factory functions such as
``opt::bind_to``, ``opt::value``, and ``opt::list``, etc. However, in order to create
something similar, it doesn't take much effort. A factory function was made to
ease into the creation of custom actions named ``opt::custom``. Note, however, that
almost all the factory functions take in an action as a parameter. An action can be
any type of callable as long as it meets the signature of
``T(const std::string&, const std::string&)``. The type of ``T`` is the one provided when
creating a value. So in ``opt::value<int>()``, the type of ``T`` is ``int``.

The following example shows how to parse a complex number:

.. code-block:: cpp

    #include <gears/optparse.hpp>
    #include <complex>
    namespace opt = gears::optparse;

    struct complex_action {
        std::complex<double> operator()(const std::string&, const std::string& value) const {
            std::complex<double> result;
            auto&& pos = value.find(',');
            if(pos == std::string::npos) {
                throw std::runtime_error("invalid complex format given");
            }
            result.real(std::stod(value.substr(0, pos)));
            result.imag(std::stod(value.substr(pos + 1)));
            return result;
        }
    };

    int main(int argc, char** argv) {
        opt::option_parser parser = {
            { "complex", 'c', "sets the complex value",
              opt::custom<std::complex<double>>(complex_action{}) }
        };

        auto&& args = parser.parse(argv, argv + argc);

        if(args.options.is_active('c')) {
            std::cout << args.options.get<std::complex<double>>('c') << '\n';
        }
    }


When run, it produces the following output:

.. code-block:: console

    $ ./dev -c 1,2
    (1,2)
    $ ./dev --complex=4,4
    (4,4)
    $ ./dev --complex=44
    usage: ./dev [options...]
    ./dev: error: invalid complex format given


This example shows how to parse an enum:

.. code-block:: cpp

    #include <gears/optparse.hpp>
    namespace opt = gears::optparse;

    enum class game {
        rock, paper, scissors
    };

    struct game_action {
        game operator()(const std::string&, const std::string& value) const {
            if(value == "rock") {
                return game::rock;
            }
            else if(value == "paper") {
                return game::paper;
            }
            else if(value == "scissors") {
                return game::scissors;
            }
            else {
                throw std::runtime_error("invalid enum value");
            }
        }
    };

    int main(int argc, char** argv) {
        opt::option_parser parser = {
            { "game", 'g', "sets an enum value", opt::custom<game>(game_action{}) }
        };

        auto&& args = parser.parse(argv, argv + argc);

        if(args.options.is_active('g')) {
            switch(args.options.get<game>('g')) {
            case game::rock:
                std::cout << "rock\n";
                break;
            case game::scissors:
                std::cout << "scissors\n";
                break;
            case game::paper:
                std::cout << "paper\n";
                break;
            }
        }
    }


And of course, the output when running:

.. code-block:: console

    $ ./dev --game=rock
    rock
    $ ./dev --game scissors
    scissors
    $ ./dev -g paper
    paper
    $ ./dev -g=test
    usage: ./dev [options...]
    ./dev: error: invalid enum value

.. _gears-tutorial-optparse-custom-eh-and-format:

Custom Error Handling and Formatting
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The optparse module provides a sensible default for handling errors
and to format the help message. The default was carefully picked to be
consistent with a lot of the tools currently available on Linux. Sometimes
however, a little more flexibility and control is needed to print things
just the way you want them.

.. _gears-tutorial-optparse-custom-eh:

Custom Error Handling
^^^^^^^^^^^^^^^^^^^^^^^^

The ``parse`` member function of ``option_parser`` has some reasonable default error
handling mechanisms in place to make the code easier to read. However, if for
some reason you want to handle the errors yourself, another member function
is provided that does absolutely no error handling named ``raw_parse``. The ``parse``
member function also checks for required arguments not being present, which has
to be checked through a different member function called ``notify``.

The following example shows how to handle errors using ``raw_parse`` and a try-catch
block. Note that all errors are derived from ``optparse::error``.

.. code-block:: cpp

    #include <gears/optparse.hpp>
    namespace opt = gears::optparse;

    int main(int argc, char** argv) {
        opt::option_parser parser = {
            { "required", 'r', "a required option", opt::constant(true), opt::trait::required }
        };

        try {
            parser.raw_parse(argv, argv + argc);
            parser.notify();
        }
        catch(const opt::missing_required_option& e) {
            std::cerr << "You missed the option " << e.option_name << '\n';
        }
        catch(const opt::error& e) {
            std::cerr << e.program_name << ": unexpected error: " << e.error_string << '\n';
        }
    }


Running it leads to the following output:

.. code-block:: console

    $ ./dev
    You missed the option --required
    $ ./dev --required
    $ ./dev --required=true
    ./dev: unexpected error: option '--required' does not take a value

.. _gears-tutorials-optparse-custom-format:

Custom Formatting
^^^^^^^^^^^^^^^^^^^

The default behaviour of the ``--help`` message relies on the default
implementation of the class ``optparse::formatter``. The formatter
class takes care of the formatting of the usage, epilogue, and description
messages. Along with that, it also handles the subcommand list and the
pretty printing of the currently active ``option_set``. The following
example changes the the option formatting.

.. code-block:: cpp

    #include <gears/optparse.hpp>
    namespace opt = gears::optparse;

    struct my_formatter : public opt::formatter {
        std::string options(const opt::option_set& opts) override {
            std::string result = "options:\n";
            for(auto&& opt : opts) {
                result.append(4, ' ').append(1, '-').append(1, opt.alias);
                result.push_back('\t');
            }
            result.push_back('\n');
            return result;
        }
    };

    int main(int argc, char** argv) {
        opt::option_parser parser = {
            { 'a', "The first option" },
            { 'b', "The second option" },
            { 'c', "The third option" }
        };

        parser.help_formatter(my_formatter{});
        parser.parse(argv, argv + argc);
    }

Running the code leads to the following help output:

.. code-block:: console

    $ ./dev --help
    usage: ./dev [options...]

    options:
        -h      -a      -b      -c
