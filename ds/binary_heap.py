#!/usr/bin/env python

from __future__ import print_function

class BinaryHeap:
	""" 
	Simple implementation of max binary heap 
	API:
		* insert(element) - insert element in heap
		* remove() - remove maximum element
	
	Note: internally heap implemented as array
	"""

	def __init__(self, heap = []):
		"""Create predefined heap"""
		self._array = [0]
		self._array.extend(heap)

		err = self._check_order()
		if err:
			self._array = [0]
			raise ValueError('Heap is out of order at index {}'.format(err))

	def insert(self, element):
		self._array.append(element)
		self._promote(len(self._array) - 1)
	
	def remove(self):
		m = self._array[1]
		self._array[1] = self._array.pop()
		self._demote(1)
		return m
	
	def _promote(self, k):
		"""Restore heap order by bubbling up element at k"""
		while k > 1:
			if self._array[k] > self._array[k//2]:
				self._array[k], self._array[k//2] = self._array[k//2], self._array[k]
			k = k//2

	def _demote(self, k):
		N = len(self._array)
		while 2*k < N:
			i = 2*k
			try:
				m = max(self._array[i], self._array[i+1])
			except IndexError:
				if i >= N:
					# Element has no children
					break
				else:
					# Element has only left children
					m = self._array[i]

			i = self._array.index(m)
			if self._array[k] >= m:
				break
			self._array[k], self._array[i] = self._array[i], self._array[k]
			k = i

	def _check_order(self):
		n = len(self._array) - 1
		while n > 1:
			if self._array[n] > self._array[n//2]:
				# Retrun index - 1 because we start with index 1
				return n - 1
			n = n - 1
		return 0

	def __str__(self):
		s = ''
		for e in self._array:
			s += str(e) + ' '
		return s
