#!/usr/bin/env python3

def pivot_start(L, start, end):
    return start

def pivot_end(L, start, end):
    return end

def pivot_median(L, start, end):
    middle = start + (end - start)//2
    idxs = [start, middle, end]
    vals = [L[start], L[middle], L[end]]
    return sorted(zip(vals, idxs))[1][1]

def partition(L, start, end, pi):
    L[start], L[pi] = L[pi], L[start]
    pivot = L[start]

    i = start + 1
    j = start + 1
    while i <= end:
        if L[i] <= pivot:
            L[i], L[j] = L[j], L[i]
            j += 1
        i += 1
    
    L[start], L[j - 1] = L[j - 1], L[start]
    return j - 1 

def quicksort(L, start = 0, end = None):
    if end is None:
        end = len(L) - 1

    if end - start < 1:
        return
    
    #pi = pivot(L, start, end)
    pi = pivot_median(L, start, end)
    pi = partition(L, start, end, pi)
    quicksort(L, start, pi - 1)
    quicksort(L, pi + 1, end)

if __name__ == "__main__":
    L = [1,5,2,5,8,51,2,685,342,34,65]
    print("Origin list: {}".format(L))
    quicksort(L)
    print("Sorted list: {}".format(L))
