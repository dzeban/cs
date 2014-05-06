#!/usr/bin/env python
"""Calculates array inversions"""

import sys

def splits(list, left, right):
	i = j = k =0
	left_len = len(left)
	right_len = len(right)
	s = 0

	while (i < left_len) and (j < right_len):
		if left[i] <= right[j]:
			list[k] = left[i]
			i += 1
		else:
			list[k] = right[j]
			s += left_len - i
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
	return s

def inversions(list):
	if len(list) == 1:
		return 0

	middle = len(list) / 2

	left = list[:middle]
	right = list[middle:]

	left_inversions = 0
	right_inversions = 0
	split_inversions = 0

	left_inversions = inversions(left)
	right_inversions = inversions(right)
	split_inversions = splits(list, left, right)
	return (left_inversions + right_inversions + split_inversions)

def main():
	list = []
	try:
		f = open(sys.argv[1])
		content = f.readlines()
		list = [int(elem) for elem in content]
	except IOError:
		try:
			for elem in sys.argv[1:]:
				list.append(int(elem))
		except:
			print("Failed to read list. Either provide filename or list")
			sys.exit(1)

	invs = inversions(list)
	print(invs)

if __name__ == "__main__":
	main()
