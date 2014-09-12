#!/usr/bin/env python

""" Breadth-first search and connected components """

from collections import deque

def bfs_visited(ugraph, start_node):
    """ Breadth-first search with queue """
    queue = deque()
    visited = set([start_node])
    queue.appendleft(start_node)
    while len(queue) != 0:
        cur = queue.pop()

        for adj in ugraph[cur]:
            if adj not in visited:
                visited.add(adj)
                queue.appendleft(adj)

    return visited

def cc_visited(graph):
    """ Connected components """
    remaining_nodes = graph.copy()
    cc_list = []
    while len(remaining_nodes) != 0:
        key = remaining_nodes.keys()[0]
        bfs = bfs_visited(graph, key)
        cc_list.append(bfs)
        for node in bfs:
            remaining_nodes.pop(node)

    return cc_list

def largest_cc_size(ugraph):
    """ Largest connected component size """
    cc_list = cc_visited(ugraph)
    lenghts = [len(component) for component in cc_list]
    if len(lenghts) == 0:
        return 0
    else:
        return max(lenghts)

def compute_resilience(ugraph, attack_order):
    """ Graph resilience on attack """
    graph = ugraph.copy()
    resilience = [largest_cc_size(graph)]
    for rnode in attack_order:
        # Remove node and all edges
        adjacents = graph.pop(rnode)
        for adjacent in adjacents:
            edges = graph[adjacent]
            edges.remove(rnode)

        # Recompute largest connected component
        resilience.append(largest_cc_size(graph))
    return resilience

if __name__ == '__main__':
    pass
