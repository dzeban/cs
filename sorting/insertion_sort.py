#!/usr/bin/env python
from __future__ import print_function

def insertion_sort(A):
    n = len(A)
    for i in range(n):
        j = i
        while (j > 0) and (A[j] < A[j-1]):
            tmp = A[j]
            A[j] = A[j-1]
            A[j-1] = tmp
            j = j - 1

def main():
    A = [13, 37, 61, 73, 97, 44, 72, 56, 85, 29]
    insertion_sort(A)
    print(A)

if __name__ == '__main__':
    main()
