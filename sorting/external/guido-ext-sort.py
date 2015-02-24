#!/usr/bin/env python3

# As seen on 
# http://neopythonic.blogspot.ru/2008/10/sorting-million-32-bit-integers-in-2mb.html

import sys, os, array, tempfile, heapq, time
assert array.array('i').itemsize == 4

def intsfromfile(f):
	while True:
		 a = array.array('i')
		 a.fromstring(f.read(4000))
		 if not a:
			 break
		 for x in a:
			 yield x

if len(sys.argv) != 3:
	print("{} <filename> <buffer size>".format(sys.argv[0]), file=sys.stderr)
	sys.exit(1)

bufsize = int(sys.argv[2])
inf = open(sys.argv[1], "rb")
iters = []
start = time.clock()
while True:
	a = array.array('i')
	a.frombytes(inf.read(bufsize))

	if not a:
		break

	f = tempfile.TemporaryFile()
	array.array('i', sorted(a)).tofile(f)
	f.seek(0)
	iters.append(intsfromfile(f))

inf.close()

a = array.array('i')
for x in heapq.merge(*iters):
	a.append(x)
	if len(a) >= 1000:
			a.tofile(sys.stdout.buffer)
			del a[:]
end = time.clock()
if a:
	a.tofile(sys.stdout.buffer)
	pass

print("{} bytes sorted in {} seconds".format(os.stat(sys.argv[1]).st_size, end - start), file=sys.stderr)
