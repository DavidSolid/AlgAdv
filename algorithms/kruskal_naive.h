//
// Created by Alessandro on 07/04/2020.
//

#ifndef ALGADVGRAPHS_KRUSKAL_NAIVE_H
#define ALGADVGRAPHS_KRUSKAL_NAIVE_H

#include "../graph_structures/AdjacencyList.h"
#include "../graph_structures/Edge.h"
#include "../graph_structures/AdjacencyList.h"

template <typename T, typename W>
std::pair<int, AdjacencyList<T, W>> Kruskal_Naive(unsigned int, std::vector<Edge<T, W>>);

template <typename T, typename W>
std::pair<int, AdjacencyList<T, W>> Kruskal_Naive(unsigned int n_vec, std::vector<Edge<T, W>> E){
    //
}

#endif //ALGADVGRAPHS_KRUSKAL_NAIVE_H