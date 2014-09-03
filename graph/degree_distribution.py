#!/usr/bin/env python

""" Simple graph properties """

EX_GRAPH0 = {
        0: set([1, 2]),
        1: set([]),
        2: set([])
}

EX_GRAPH1 = {
    0: set([1, 4, 5]),
    1: set([2, 6]),
    2: set([3]),
    3: set([0]),
    4: set([1]),
    5: set([2]),
    6: set([])
}

EX_GRAPH2 = {
    0: set([1, 4, 5]),
    1: set([2, 6]),
    2: set([3, 7]),
    3: set([7]),
    4: set([1]),
    5: set([2]),
    6: set([]),
    7: set([3]),
    8: set([1, 2]),
    9: set([0, 3, 4, 5, 6, 7])
}


def make_complete_graph(num_nodes):
    """ Creates complete directed graph (without cycles) """
    graph = {}
    for index in xrange(num_nodes):
        graph[index] = set([])
        for jey in xrange(index):
            graph[index].add(jey)
    return graph

def compute_in_degrees(digraph):
    """ For given graph computes in-degrees of each node """
    graph = {}
    for node in digraph:
        graph[node] = 0
        for key, val in digraph.iteritems():
            if key != node:
                if node in val:
                    graph[node] = graph[node]+1

    return graph

def in_degree_distribution(digraph):
    """ For given graph computes in-degree distribution """
    computed = compute_in_degrees(digraph)
    distribution = {}
    for degree in computed.itervalues():
        if degree not in distribution.keys():
            distribution[degree] = 0

        distribution[degree] = distribution[degree] + 1

    #if 0 in distribution.keys():
    #    distribution.pop(0)
    return distribution

if __name__ == '__main__':
    print in_degree_distribution(EX_GRAPH2)

