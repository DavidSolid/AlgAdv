cmake_minimum_required(VERSION 3.14)
project(AlgAdvGraphs)

set(CMAKE_CXX_STANDARD 17)

add_executable(AlgAdvGraphs main.cpp data_structures/MinHeap.h data_structures/UnionFind.h data_structures/Parser.h data_structures/Edge.h data_structures/AdjacencyList.h algorithms/kruskal_union_find.h algorithms/kruskal_naive.h algorithms/prim.h)