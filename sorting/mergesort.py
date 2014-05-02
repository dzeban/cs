#!/usr/bin/env python

import sys

def merge(list, left, right, middle):
	i = j = k =0
	left_len = len(left)
	right_len = len(right)

	while (i < left_len) and (j < right_len):
		if left[i] <= right[j]:
			list[k] = left[i]
			i += 1
		else:
			list[k] = right[j]
			j += 1
		k += 1
	
	while i < left_len:
		list[k] = left[i]
		i += 1
		k += 1
	
	while j < right_len:
		list[k] = right[j]
		j += 1
		k += 1

def mergesort(list):
	if len(list) == 1:
		return

	middle = len(list) / 2

	left = list[middle:]
	right = list[:middle]

	mergesort(left)
	mergesort(right)
	merge(list, left, right, middle)

def main():
	list = []
	for arg in sys.argv[1:]:
		list.append(int(arg))
	
	mergesort(list)
	print(list)

if __name__ == "__main__":
	main()
