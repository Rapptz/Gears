## Gears

[![Build Status](https://travis-ci.org/Rapptz/Gears.png?branch=master)](https://travis-ci.org/Rapptz/Gears)

Gears is a header-only library that offers utilities for C++11 programmers. It is a more enhanced remake of
the [original library][orig] hosted at Bitbucket. The [issue tracker][issues] will be used to keep track of things
I plan to remake until I'm satisfied initially. Documentation can be found [here][docs]

## Compiling Tests

The tests obviously require compilation. Although not required to be built, it's a good idea to compile them anyway to
see if the compiler can build gears. In order to compile gears, [ninja][ninja] is required.
Python is used to generate the ninja file so just invoke:

    ./bootstrap.py --cxx=g++ && ninja

## Compiler Support

Currently Gears targets compilers that have good support of C++11 features, at the moment these include Clang 3.4 and GCC 4.8
or higher. Visual Studio 2013 could have worked in theory but it isn't technically supported and any bugs are a side effect.

No extraneous libraries are required to use Gears, only the standard library.


[orig]: https://bitbucket.org/Rapptz/gears
[issues]: https://github.com/Rapptz/Gears/issues?milestone=1&state=open
[docs]: http://rapptz.github.io/Gears/docs/
[ninja]: https://github.com/martine/ninja
