//
// Created by Enrico on 07/04/2020.
//

#ifndef ALGADVGRAPHS_KRUSKAL_UNION_FIND_H
#define ALGADVGRAPHS_KRUSKAL_UNION_FIND_H

#include "../data_structures/AdjacencyList.h"
#include "../data_structures/Edge.h"
#include "../data_structures/AdjacencyList.h"

template <typename T, typename W>
std::pair<int, AdjacencyList<T, W>> Kruskal_Union_Find(unsigned int, std::vector<Edge<T, W>>);

template <typename T, typename W>
std::pair<int, AdjacencyList<T, W>> Kruskal_Union_Find(unsigned int n_vec, std::vector<Edge<T, W>> E){
    //line 1 : Start A empty
    AdjacencyList<int,int> A(n_vec);

    //line 2 : Initialize U
    int *V;
    V = new int[n_vec];
    std::iota(V, V + n_vec, 0);
    /*for(int i = 0; i < G[0][0]; ++i){
        ar[i] = i;
    }*/
    UnionFind<int> U(V, n_vec);
    //todo: passare un anonimo in futuro

    //line 3 : sort E
    /*
    std::sort(E.begin(), E.end(), [](const Edge<int,int> & a, const Edge<int,int> & b) -> bool{
        return a.get_weight() < b.get_weight();
    });
    */
    std::sort(E.begin(), E.end());

    //line 4 : for each edge in E do
    int iter = 0;
    for(const auto & e : E){
        ++iter;
        //line 5 : if e.node_1 and e.node_2 belong to two different connected components then
        if(U.find(e.get_node_1()) != U.find(e.get_node_2())){
            //line 6 : add e to A
            A.unite(e); //todo: cambia nome
            //line 7 : unite e.node_1 and e.node_2
            U.unite(e.get_node_1(), e.get_node_2());
        }
        if(A.edges() == (A.nodes() - 1))
            break;
    }

    //line 8 : return A
    return std::make_pair(iter, A);
}

#endif //ALGADVGRAPHS_KRUSKAL_UNION_FIND_H
