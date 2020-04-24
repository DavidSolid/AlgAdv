//
// Created by Alessandro on 07/04/2020.
//

#ifndef ALGADVGRAPHS_KRUSKAL_NAIVE2_H
#define ALGADVGRAPHS_KRUSKAL_NAIVE2_H

#include "../graph_structures/Edge.h"
#include "../graph_structures/AdjacencyList.h"

template <typename W>
std::pair<int, AdjacencyList<W>> Kruskal_Naive2(int, std::vector<Edge<W>>);

template <typename W>
std::pair<int, AdjacencyList<W>> Kruskal_Naive2(int n, std::vector<Edge<W>> E){
    //number of iteration of the outer for
    int iter = 0;

    //line 1 : Initialize A empty
    AdjacencyList<W> A(n);

    //line 2 : sort E
    std::sort(E.begin(), E.end());

    //line 3 : for each edge in E do
    for(int i = 0; i< E.size(); ++i){
        ++iter;
        //line 4 : if in A it does not exist a cycle between e.node_1 and e.node_2 then
        if(!A.BFS(E[i].get_node_1(), E[i].get_node_2())){

            //line 5 : add e to A
            A.add(E[i]);

            //if A contains n-1 edges then it must be a MST
            if(A.get_edges() == (A.get_nodes() - 1))
                break;
        }
    }

    //line 6 : return A and the number of iteration
    return std::make_pair(iter, A);
}

#endif //ALGADVGRAPHS_KRUSKAL_NAIVE2_H
