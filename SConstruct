# SCons 2.2.0
# python 2.7

import os, sys

# Meta data set up here
compiler_flags = ['-Wall', '-pedantic', '-pedantic-errors', '-Werror', '-std=c++11']
compiler_path = 'C:/mingw64/'
include_paths = ['../gears/', 'tests']
ignored_warnings = ['switch']

travis = True # Determine if we're building on travis-ci

# Utilities
def prefix(p, l):
    return map(lambda x: p + x, l)

for warning in ignored_warnings:
    compiler_flags.append('-Wno-' + warning)

if sys.platform == 'win32':
    env = Environment(tools = ['mingw'], ENV = os.environ)
    env['CXX'] = 'g++'
    env.PrependENVPath('PATH', compiler_path + 'bin/')
    env.PrependENVPath('LIB', compiler_path + 'lib/')
    env.Append(CPPFLAGS = compiler_flags)
    env.Append(CPPPATH = include_paths)
elif travis:
    env = Environment(ENV = os.environ)
    env['CXX'] = os.environ['CXX']
    env.Append(CPPFLAGS = compiler_flags)
    env.Append(CPPPATH = include_paths)
else:
    env = Environment(ENV = os.environ)

test_sources = ['tests/' + x for x in os.listdir('tests') if x.endswith('.cpp')]
test_builddir = 'obj/test/'

if sys.platform == 'win32':
    test_target = r'bin\test\runtest'
else:
    test_target = 'bin/test/runtest'

test = env.Clone()
test.VariantDir(test_builddir, '.', duplicate=0)
test_program = test.Program(test_target, prefix(test_builddir, test_sources))
test.Alias('buildtest', test_program)

test_alias = test.Alias('runtest', [test_program], test_target)
test.AlwaysBuild(test_alias)

Default('runtest')