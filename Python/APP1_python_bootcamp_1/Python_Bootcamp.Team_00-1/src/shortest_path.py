# set WIKI_FILE=F:\PROGRAMMING\SCHOOL21-BASE\SCHOOL21_projects\Python\Python_Bootcamp.Team_00-1\src\wiki.json
# echo %WIKI_FILE%

# In power shell
# $env:WIKI_FILE = "F:\PROGRAMMING\SCHOOL21-BASE\SCHOOL21_projects\Python\Python_Bootcamp.Team_00-1\src\wiki.json"
# echo $env:WIKI_FILE

import os
import json
import logging
import argparse
from collections import deque
from typing import List, Dict

logging.basicConfig(level=logging.INFO, format="%(message)s")

def load_graph() -> Dict[str, List[str]]:
    wiki_file = os.environ.get("WIKI_FILE")
    if not wiki_file:
        print("database not found")
        exit(1)

    try:
        with open(wiki_file, "r", encoding="utf-8") as f:
            graph_data = json.load(f)
        return graph_data
    except FileNotFoundError:
        print("database not found")
        exit(1)


def build_adjacency_list(graph_data: Dict[str, List[str]], non_directed: bool) -> Dict[str, List[str]]:
    if not non_directed:
        return graph_data

    undirected_graph = {}
    for src, targets in graph_data.items():
        if src not in undirected_graph:
            undirected_graph[src] = []

        for t in targets:
            if t not in undirected_graph:
                undirected_graph[t] = []

            if t not in undirected_graph[src]:
                undirected_graph[src].append(t)
            if src not in undirected_graph[t]:
                undirected_graph[t].append(src)
    return undirected_graph


def bfs_shortest_path(graph: Dict[str, List[str]], start: str, end: str) -> List[str]:
    if start not in graph or end not in graph:
        return []

    visited = set()
    queue = deque([start])
    parents = {start: None}

    while queue:
        current = queue.popleft()

        if current == end:
            path = []
            while current is not None:
                path.append(current)
                current = parents[current]
            path.reverse()
            return path

        visited.add(current)
        for neighbor in graph.get(current, []):
            if neighbor not in visited and neighbor not in parents:
                parents[neighbor] = current
                queue.append(neighbor)

    return []


def main():
    graph_data = load_graph()
    adj_list = build_adjacency_list(graph_data, args.non_directed)

    path = bfs_shortest_path(adj_list, args.from_page, args.to_page)

    if not path:
        print("path not found")
    else:
        if args.verbose:
            path_str = " -> ".join(f"'{p}'" for p in path)
            print(path_str)
        print(len(path) - 1)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Find the shortest path in the wiki graph")
    parser.add_argument("--from", dest="from_page", required=True,
                        help="Starting page (required)")
    parser.add_argument("--to", dest="to_page", required=True,
                        help="Target page (required)")
    parser.add_argument("--non-directed", dest="non_directed", action="store_true",
                        help="Treat edges as undirected (bidirectional)")
    parser.add_argument("-v", dest='verbose', action='store_true',
                        help="Enable printing of the found path")
    args = parser.parse_args()

    graph_data = load_graph()
    adj_list = build_adjacency_list(graph_data, args.non_directed)

    path = bfs_shortest_path(adj_list, args.from_page, args.to_page)

    if not path:
        print("path not found")
    else:
        if args.verbose:
            path_str = " -> ".join(f"'{p}'" for p in path)
            print(path_str)
        print(len(path) - 1)