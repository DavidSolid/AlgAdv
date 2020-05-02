cmake_minimum_required(VERSION 3.14)
project(AlgAdvGraphs)

set(CMAKE_CXX_STANDARD 17)

add_executable(AlgAdvGraphs main.cpp data_structures/MinHeap.h data_structures/UnionFind.h utility/Parser.h graph_structures/Edge.h graph_structures/AdjacencyList.h algorithms/kruskal_union_find.h algorithms/kruskal_naive_dfs.h algorithms/kruskal_naive_bfs.h algorithms/prim.h)