//
// Created by Alessandro on 06/04/2020.
//

#ifndef ALGADVGRAPHS_KRUSKAL_UNION_FIND_H
#define ALGADVGRAPHS_KRUSKAL_UNION_FIND_H

#include "../graph_structures/Edge.h"
#include "../graph_structures/AdjacencyList.h"

template <typename T, typename W>
std::pair<int, AdjacencyList<T, W>> Kruskal_Union_Find(unsigned int, std::vector<Edge<T, W>>);

template <typename T, typename W>
std::pair<int, AdjacencyList<T, W>> Kruskal_Union_Find(unsigned int n_vec, std::vector<Edge<T, W>> E){
    //number of iteration of the outer for
    int iter = 0;

    //line 1 : Initialize A empty
    AdjacencyList<int,int> A(n_vec);

    //line 2 : Initialize U with V
    int *V;
    V = new int[n_vec];
    std::iota(V, V + n_vec, 0);
    UnionFind<int> U(V, n_vec);
    //todo: passare un anonimo in futuro

    //line 3 : sort E
    std::sort(E.begin(), E.end());

    //line 4 : for each edge in E do
    for(const auto & e : E){
        ++iter;
        //line 5 : if e.node_1 and e.node_2 belong to two different connected components then
        if(U.find(e.get_node_1()) != U.find(e.get_node_2())){
            //line 6 : add e to A
            A.add(e);
            //line 7 : unite e.node_1 and e.node_2
            U.unite(e.get_node_1(), e.get_node_2());
        }
        //if A contains n-1 edges then it must be a MST
        if(A.edges() == (A.nodes() - 1))
            break;
    }

    //line 8 : return A and the number of iteration
    return std::make_pair(iter, A);
}

#endif //ALGADVGRAPHS_KRUSKAL_UNION_FIND_H
