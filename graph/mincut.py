#!/usr/bin/env python3

import sys
import copy
import random
from pprint import pprint

def load(filename):
    """ 
    Load graph from file.

    Graph is represented as adjacent vertices:
    <vertex> <list of adjacent vertices>

    For example:
    2 1 3

    means that vertex 2 is connected with vertex 1 and 3

    NOTE: vertex labels must be separated by tav
    """

    with open(filename) as f:
        G = dict()
        lines = f.readlines()
        for line in lines:
            line = line.strip()
            nodes = line.split('\t')
            nodes = [int(n) for n in nodes]
            G[nodes[0]] = nodes[1:]
    return G

def merge_keys(k1, k2):
    """ This stupid function is needed because python tuples are stupid """

    if   type(k1) == tuple and type(k2) == tuple:
        return k1 + k2
    elif type(k1) == tuple and type(k2) == int:
        return k1 + (k2,)
    elif type(k1) == int   and type(k2) == tuple:
        return (k1,) + k2
    elif type(k1) == int   and type(k2) == int:
        return (k1,k2)
    else:
        message = "Incorrect types to merge: k1 is {}, k2 is {}".format(type(k1), type(k2))
        raise TypeError(message)

def mincut(G):
    while len(G.items()) != 2:
        # Choose 2 connected vertices
        k1 = random.choice(list(G.keys()))
        k2 = random.choice(G[k1])

        # Merge them to new one
        newkey = merge_keys(k1,k2)
        newvals = G[k1] + G[k2]
        edges = []
        for v in newvals:
            if v != k1 and v != k2:
                edges.append(v)

        # Replace them with new one
        G.pop(k1)
        G.pop(k2)
        G[newkey] = edges

        # Update other edges
        for item in G.items():
            for index, node in enumerate(item[1]):
                if node == k1 or node == k2:
                    G[item[0]][index] = newkey

    return len(list(G.values())[0])

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("./mincut <graph file> <attempts>")
        sys.exit(1)

    # See graph file format description in load() comments
    G = load(sys.argv[1])

    cuts = []
    for i in range(int(sys.argv[2])):
        g = copy.deepcopy(G)
        m = mincut(g)
        cuts.append(m)
    print(min(cuts))
