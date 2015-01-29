#!/usr/bin/env python3
"""Convert ASCII file with integers to raw binary format and back"""

import sys
from struct import pack, unpack

# FIXME: get to know this at runtime
intsize = 4
def binary2text(input_filename, output_filename):
    with  open(sys.argv[1], 'rb') as inf, open(sys.argv[2], 'w') as outf:
        b = inf.read(intsize)
        while b:
            a = unpack('i', b)[0]
            outf.write(str(a) + '\n')
            b = inf.read(intsize)

def text2binary(input_filename, output_filename):
    with open(sys.argv[1], 'r') as inf, open(sys.argv[2], 'wb') as outf:
        for line in inf.readlines():
            outf.write(pack('i', int(line)))


# Text characters are special ASCII symbols and printable range
textchars = bytearray([7,8,9,10,12,13,27]) + bytearray(range(0x20, 0x100))
def is_binary(b):
    """ Accepts bytes and guesses if it's a binary or not by looking for non
    text characters. """
    return bool(b.translate(None, textchars))

if len(sys.argv) != 3:
    print("{} <input file> <output file>".format(sys.argv[0]))
    print("If input file is text then it's converted to binary")
    print("if input file is binary then it's converted to text")
    sys.exit(-1)

binary = is_binary(open(sys.argv[1], 'rb').read(100))

if binary:
    binary2text(sys.argv[1], sys.argv[2])
else:
    text2binary(sys.argv[1], sys.argv[2])

