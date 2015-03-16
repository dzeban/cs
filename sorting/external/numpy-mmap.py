#!/usr/bin/env python3

import numpy, sys, time

mm = numpy.memmap(sys.argv[1], dtype='uint32', mode='r+')

start = time.clock()
mm.sort()
end = time.clock()

print('{} bytes sorted in {} seconds'.format(mm.size * 4, end - start))
