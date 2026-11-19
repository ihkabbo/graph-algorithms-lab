# Graph Algorithms for Shortest Path and Minimum Spanning Tree Analysis

A C-based project that implements different graph algorithms to find shortest paths, construct Minimum Spanning Trees, and analyze graph connectivity.

## Project Overview

This project demonstrates how graph algorithms can be used to solve network connection problems. It uses an adjacency matrix to represent the graph and calculates paths based on edge weights.

The program also checks how removing a specific edge affects the shortest path and graph connectivity.

## Algorithms Implemented

- **Dijkstra's Algorithm:** Finds the shortest path between a source and destination.
- **Kruskal's Algorithm:** Constructs a Minimum Spanning Tree with minimum total weight.
- **Prim's Algorithm:** Builds a Minimum Spanning Tree using a different approach.
- **Breadth-First Search (BFS):** Finds a path between two vertices in the generated Minimum Spanning Trees.

## Features

- Graph representation using an adjacency matrix.
- Shortest path calculation using Dijkstra's Algorithm.
- Minimum Spanning Tree construction using Kruskal's and Prim's Algorithms.
- Pathfinding using BFS.
- Edge removal and connectivity checking.
- Updated shortest path and MST calculation after removing an edge.
- Input validation and handling of disconnected graphs.

## Input Format

The program reads graph information from `input.txt`.

The input contains:

1. Number of vertices and edges.
2. Edge connections with their weights.
3. Source and destination vertices.
4. The edge to be removed.

All vertices are numbered starting from 0.

## Time and Space Complexity

The time complexity of each algorithm is given below:

- **Dijkstra's Algorithm:** O(V²)
- **Kruskal's Algorithm:** O(E² + E α(V))
- **Prim's Algorithm:** O(V²)
- **Breadth-First Search (BFS):** O(V²)

Here, V represents the number of vertices, E represents the number of edges, and α(V) is the inverse Ackermann function.

The overall space complexity is **O(V² + E)**.

## How to Run

1. Download or clone this repository.
2. Keep the C source file and `input.txt` in the same folder.
3. Compile the program using GCC:

```bash
gcc "Graph Algorithms for Shortest Path and Minimum Spanning Tree Analysis code.c" -o graph
```

4. Run the program:

```bash
./graph
```

On Windows, use:

```bash
graph.exe
```

## Project Files

- [Graph Algorithms for Shortest Path and Minimum Spanning Tree Analysis code.c](./Graph%20Algorithms%20for%20Shortest%20Path%20and%20Minimum%20Spanning%20Tree%20Analysis%20code.c) – Main C source code.
- [input.txt](./input.txt) – Input data for the graph.
- [README.md](./README.md) – Project documentation.

## Programming Language

- C Programming Language

## Author

**Md. Imran Hossen**

GitHub: [ihkabbo](https://github.com/ihkabbo)
