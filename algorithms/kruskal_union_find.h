//
// Created by Alessandro on 06/04/2020.
//

#ifndef ALGADVGRAPHS_KRUSKAL_UNION_FIND_H
#define ALGADVGRAPHS_KRUSKAL_UNION_FIND_H

#include "../graph_structures/Edge.h"
#include "../graph_structures/AdjacencyList.h"
#include "../data_structures/UnionFind.h"

template <typename W>
AdjacencyList<W> Kruskal_Union_Find(int, std::vector<Edge<W>>);

template <typename W>
AdjacencyList<W> Kruskal_Union_Find(int n, std::vector<Edge<W>> E){
    //line 1 : Initialize A empty
    AdjacencyList<W> A(n);

    //line 2 : Initialize U with V
    int *V;
    V = new int[n];
    std::iota(V, V + n, 0);
    UnionFind U(V, n);
    //todo: passare un anonimo in futuro

    //line 3 : sort E
    std::sort(E.begin(), E.end());

    //line 4 : for each edge in E do
    for(const auto & e : E){
        //line 5 : if e.node_1 and e.node_2 belong to two different connected components then
        if(U.find(e.get_node_1()) != U.find(e.get_node_2())){
            //line 6 : add e to A
            A.add(e);
            //line 7 : unite e.node_1 and e.node_2
            U.unite(e.get_node_1(), e.get_node_2());
        }
        //if A contains n-1 edges then it must be a MST
        if(A.get_edges() == (A.get_nodes() - 1))
            break;
    }

    //line 8 : return A
    return A;
}

#endif //ALGADVGRAPHS_KRUSKAL_UNION_FIND_H
