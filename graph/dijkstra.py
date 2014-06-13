#!/usr/bin/env python3

import sys
from pprint import pprint

def load(filename):
    """ 
    Load graph from file.

    Graph is represented as adjacent vertices:
    <vertex> <list of adjacent vertices with weights>

    For example:
    2 1,3

    means that vertex 2 is connected with vertex 1 and edge's weight is 3

    NOTE: vertex labels must be separated by tab
    """

    with open(filename) as f:
        G = dict()
        lines = f.readlines()
        for line in lines:
            line = line.strip()
            splits = line.split('\t')
            key = int(splits[0])
            nodes = []
            for s in splits[1:]:
                pair = s.split(',')
                t = tuple([int(pair[0]), int(pair[1])])
                nodes.append(t)
            G[key] = nodes
    return G

def dijkstra(G):

    # Initialize distances
    D = dict()
    for k in G.keys():
        D[k] = float("inf")

    # Start with first vertex
    v = list(G.keys())[0]
    D[v] = 0

    for v in G.items():
        d = D[v[0]]

        for u, w in v[1]:
            if w + d < D[u]:
                D[u] = w + d
    return D

if __name__ == '__main__':
    G = load(sys.argv[1])
    pprint(G)
    D = dijkstra(G)
    pprint(D)
