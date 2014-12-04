#!/usr/bin/env python

from __future__ import print_function

import gf

ns = 2

def printD(D):
	print([hex(d) for d in D])

def calc_s0(D):
	""" Calculate S0 = D0 + D1 + ... + Dn-1 """

	# Number of data disks
	nd = len(D) - ns

	s0 = 0
	for i in range(0, nd):
		s0 ^= D[i]

	return s0

def calc_s1(D):
	"""
	Calculate S1 = D0x^(n-1) + D1x^(n-2) + ... + D{n-1} =
	 = ((D0x + D1)x + D2)x + ... + D{n-1}
	"""

	# Number of data disks
	nd = len(D) - ns

	s1 = 0
	#for i in range(0, nd - 1):
		#s1 ^= D[i]
		#s1 = gf.mulx(s1)
	#s1 ^= D[nd]
	for i in range(0, nd):
		s1 = gf.mulx(s1)
		s1 ^= D[i]

	return s1

def calculate_s0s1(D):
	D[-2] = calc_s0(D)
	D[-1] = calc_s1(D)

def recover1d_s0(D, failed):
	new_s0 = calc_s0(D)
	old_s0 = D[-2]
	return new_s0 ^ old_s0

def recover1d_s1(D, failed):
	n = len(D) - ns

	new_s1 = calc_s1(D)
	old_s1 = D[-1]

	x = gf.pow(n - failed - 1)
	x1 = gf.inv(x)

	return gf.mul(new_s1 ^ old_s1, x1)

def recover2d_s0s1(D, failed):
	n = len(D) - ns
	j = failed[0]
	k = failed[1]

	old_s0 = D[-2]
	old_s1 = D[-1]

	new_s0 = calc_s0(D)
	new_s1 = calc_s1(D)

	x1 = gf.inv(gf.pow(n - k - 1))
	x2 = gf.inv(gf.pow(k - j) ^ 1)

	Dj = gf.mul((gf.mul(old_s1 ^ new_s1, x1) ^ old_s0 ^ new_s0), x2)
	Dk = old_s0 ^ new_s0 ^ Dj

	return Dj, Dk

def sdc_detect(D):
	n = len(D) - ns

	old_s0 = D[-2]
	old_s1 = D[-1]

	new_s0 = calc_s0(D)
	new_s1 = calc_s1(D)

	if new_s0 == old_s0 and new_s1 == old_s1:
		return -1

	j = n - 1 - gf.log( gf.mul((old_s1 ^ new_s1), gf.inv(old_s0 ^ new_s0)) )
	D[j] = old_s0 ^ new_s0 ^ D[j]

	return j

def main():
	print('Syndromes calculation')
	D = [ 0x11, 0x22, 0x33, 0x44,
	      0x55, 0x66, 0x77, 0x88,
	      0x99, 0xaa, 0xbb, 0xcc,
	      0xdd, 0xee, 0x00, 0x00 ]

	printD(D)
	calculate_s0s1(D)
	printD(D)

	print('#------------------------#')
	print('Recovering disk #2 from S0')

	D = [ 0x11, 0x22, 0x00, 0x44, 
	      0x55, 0x66, 0x77, 0x88, 
	      0x99, 0xaa, 0xbb, 0xcc, 
	      0xdd,	0xee, 0xd9 ,0x8e ] 
	D[2] = 0
	printD(D)
	D[2] = recover1d_s0(D, 2)
	printD(D)

	print('#------------------------#')
	print('Recovering disk #2 from S1')

	D = [ 0x11, 0x22, 0x00, 0x44, 
	      0x55, 0x66, 0x77, 0x88, 
	      0x99, 0xaa, 0xbb, 0xcc,
	      0xdd,	0xee, 0x00, 0x91 ]
	D[2] = 0
	printD(D)
	print('Recovering from S1:')
	D[2] = recover1d_s1(D, 2)
	printD(D)

	print('#------------------------#')

	print('Recovering disks #3 and #7 from S0 and S1')
	D = [ 0x11, 0x22, 0x33, 0x00, 
	      0x55, 0x66, 0x77, 0x00,
	      0x99, 0xaa, 0xbb, 0xcc, 
	      0xdd,	0xee, 0x11, 0xe7 ]
	D[3] = 0
	D[7] = 0
	printD(D)
	print('Recovering 2 failed disks:')
	D[3], D[7] = recover2d_s0s1(D, (3,7))
	printD(D)

	print('###########################')
	print('       SDC detection       ')

	print('Original array:')
	D = [ 0x1e, 0x45, 0x6f, 0x2a,
	      0x88, 0xef, 0x7b, 0x0,
	      0xbb, 0x67, 0x17, 0x8,
	      0x0f, 0x86, 0xb8, 0xc0 ]
	printD(D)

	failed = sdc_detect(D)
	if failed != -1:
		print('SDC detected in {}'.format(failed))
		print('Corrected value {}'.format(hex(D[failed])))
		print('Corrected array')
		printD(D)

if __name__ == '__main__':
	main()

# vim: set noexpandtab:
