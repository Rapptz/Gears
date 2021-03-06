#!/usr/bin/env python

import argparse
import os, sys
import re
import datetime as dt

# python 3 compatibility
try:
    import cStringIO as sstream
except ImportError:
    import io.StringIO as sstream

description = "Converts a gears module to a single file for convenience."
epilogue = """To get a list of modules, run ".{sep}single.py list". To receive a
sub-module you could use a period to delimit the sub-module. For example, to get maybe
from the utility module you would run ".{sep}single.py utility.maybe"
""".format(sep=os.sep)

# command line parser
parser = argparse.ArgumentParser(usage='%(prog)s [options...] module', description=description, epilog=epilogue)
parser.add_argument('module', help='module to convert to single file', metavar='module')
parser.add_argument('--output', '-o', help='output directory to place file in', metavar='dir')
parser.add_argument('--quiet', help='suppress all output', action='store_true')
parser.add_argument('--strip', '-s', help='strip all doc comments from output', action='store_true')
parser.add_argument('--lf-only', help='writes LF instead of CRLF on Windows', action='store_true')
args = parser.parse_args()

script_path = os.path.dirname(os.path.realpath(__file__))
working_dir = os.getcwd()
os.chdir(script_path)

valid_modules = []
for i in os.listdir('gears'):
    (f, ext) = os.path.splitext(i)
    if ext == '.hpp':
        valid_modules.append(f)

if args.module == 'list':
    print('\n'.join(valid_modules))
    parser.exit(0)

if args.module.split('.')[0] not in valid_modules:
    parser.error('invalid module given')

intro = """// The MIT License (MIT)

// Copyright (c) 2012-2014 Danny Y., Rapptz

// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

// This file was generated with a script.
// Generated {time} UTC
// This header is part of gears {version} (revision {revision})
// https://github.com/Rapptz/Gears

#ifndef {guard}
#define {guard}

"""


module_path = os.path.join('gears', args.module)

includes = set([])
include = re.compile(r'#include <gears/(.*?)>')
ifndef_cpp = re.compile(r'#ifndef GEARS_.*?_HPP')
define_cpp = re.compile(r'#define GEARS_.*?_HPP')
endif_cpp = re.compile(r'#endif // GEARS_.*?_HPP')

def get_include(line):
    match = include.match(line)
    if match:
        # local include found
        full_path = os.path.join('gears', match.group(1))
        return full_path

    return None


def is_include_guard(line):
    return ifndef_cpp.match(line) or define_cpp.match(line) or endif_cpp.match(line)

def get_revision():
    return os.popen('git rev-parse --short HEAD').read().strip()

def get_version():
    return os.popen('git describe --tags --abbrev=0').read().strip()

def process_file(filename, out):
    global includes

    if filename in includes:
        return

    includes.add(filename)

    if not args.quiet:
        print('processing {}'.format(filename))

    out.write('// beginning of {}\n\n'.format(filename))
    empty_line_state = True

    with open(filename, 'r') as f:
        for line in f:
            # skip comments
            if line.startswith('//'):
                continue

            # skip include guard non-sense
            if is_include_guard(line):
                continue

            # see if it's an include file
            name = get_include(line)

            if name:
                process_file(name, out)
                continue

            empty_line = len(line.strip()) == 0

            if empty_line and empty_line_state:
                continue

            empty_line_state = empty_line

            # line is fine
            out.write(line)

    out.write('// end of {}\n\n'.format(filename))


version = get_version()
revision = get_revision()
include_guard = 'GEARS_SINGLE_INCLUDE_{module}_HPP'.format(module = args.module.upper().replace('.', '_'))

if not args.quiet:
    print('Creating single header for module {}.'.format(args.module))
    print('Current version: {version} (revision {revision})\n'.format(version = version, revision = revision))


module_file = '{}.hpp'.format(args.module.replace('.', os.sep))

output_path = '.'

if args.output:
    output_path = os.path.normpath(os.path.join(working_dir, args.output))
    if not os.path.exists(output_path):
        os.makedirs(output_path)

output_file = os.path.join(output_path, module_file)

if '.' in args.module:
    submodule = args.module.split('.')[1]
    output_file = os.path.join(output_path, '{}.hpp'.format(submodule))

result = ''

ss = sstream.StringIO()
ss.write(intro.format(time=dt.datetime.utcnow(), revision=revision, version=version, guard=include_guard))
process_file(os.path.join('gears', module_file), ss)
ss.write('#endif // {}\n'.format(include_guard))
result = ss.getvalue()
ss.close()

if args.strip:
    result = re.sub(r'\/\*\*.*?\*\/', '', result, flags=re.DOTALL)

write_mode = 'w' if not args.lf_only else 'wb'

with open(output_file, write_mode) as f:
    f.write(result)

