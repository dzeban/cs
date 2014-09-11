#!/usr/bin/env python

from collections import deque
from degree_distribution import EX_GRAPH0, EX_GRAPH1, EX_GRAPH2
from copy import copy

EX_GRAPH0 = {
        0: set([1, 2]),
        1: set([0]),
        2: set([0])
}

EX_GRAPH1 = {
    0: set([1, 4, 5]),
    1: set([0, 4, 2, 6]),
    2: set([1, 5, 3]),
    3: set([2, 0]),
    4: set([0, 1]),
    5: set([0, 2]),
    6: set([1])
}

EX_GRAPH2 = {
    0: set([1, 4, 5]),
    1: set([0, 4, 2, 6]),
    2: set([1, 5, 3, 7]),
    3: set([2, 7]),
    4: set([0, 1]),
    5: set([0, 2]),
    6: set([1]),
    7: set([2, 3]),
    8: set([9]),
    9: set([8])
}

def bfs_visited(ugraph, start_node):
    Q = deque()
    visited = set([start_node])
    Q.appendleft(start_node)
    while len(Q) != 0:
        j = Q.pop()

        for h in ugraph[j]:
            if h not in visited:
                visited.add(h)
                Q.appendleft(h)

    return visited

def cc_visited(ugraph):
    remaining_nodes = copy(ugraph)
    CC = []
    while len(remaining_nodes) != 0:
        i = remaining_nodes.keys()[0]
        W = bfs_visited(ugraph, i)
        CC.append(W)
        for node in W:
            remaining_nodes.pop(node)

    return CC

def largest_cc_size(ugraph):
    CC = cc_visited(ugraph)
    return len(max(CC))

if __name__ == '__main__':
    print(cc_visited(EX_GRAPH0))
    print(cc_visited(EX_GRAPH1))
    cc2 = cc_visited(EX_GRAPH2)
    print(largest_cc_size(EX_GRAPH2))
