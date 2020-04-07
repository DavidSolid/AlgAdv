//
// Created by Alessandro on 07/04/2020.
//

#ifndef ALGADVGRAPHS_KRUSKAL_NAIVE_H
#define ALGADVGRAPHS_KRUSKAL_NAIVE_H

#include "../graph_structures/Edge.h"
#include "../graph_structures/AdjacencyList.h"

template <typename T, typename W>
std::pair<int, AdjacencyList<T, W>> Kruskal_Naive(unsigned int, std::vector<Edge<T, W>>);

template <typename T, typename W>
std::pair<int, AdjacencyList<T, W>> Kruskal_Naive(unsigned int n_vec, std::vector<Edge<T, W>> E){
    //number of iteration of the outer for
    int iter = 0;

    //line 1 : Initialize A empty
    AdjacencyList<int,int> A(n_vec);

    //line 2 : sort E
    std::sort(E.begin(), E.end());

    //line 3 : for each edge in E do
    for(const auto & e : E){
        ++iter;
        //line 4 : if in A it does not exist a cycle between e.node_1 and e.node_2 then
        if(!A.DFS(e.get_node_1(), e.get_node_2())){
            //line 5 : add e to A
            A.add(e);
        }
        //if A contains n-1 edges then it must be a MST
        if(A.edges() == (A.nodes() - 1))
            break;
    }

    //line 6 : return A and the number of iteration
    return std::make_pair(iter, A);
}

#endif //ALGADVGRAPHS_KRUSKAL_NAIVE_H
