#!/usr/bin/env python3

import sys
from struct import pack

if len(sys.argv) != 3:
    print("{} <input ASCII file> <output binary file>".format(sys.argv[0]))
    sys.exit(-1)

with open(sys.argv[1], 'r') as inf, open(sys.argv[2], 'wb') as outf:
    for line in inf.readlines():
        outf.write(pack('i', int(line)))
