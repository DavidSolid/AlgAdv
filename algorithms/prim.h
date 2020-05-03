//
// Created by Enrico on 07/04/2020.
//

#ifndef ALGADVGRAPHS_PRIM_H
#define ALGADVGRAPHS_PRIM_H

#include "../graph_structures/Edge.h"
#include "../graph_structures/AdjacencyList.h"
#include "../data_structures/MinHeap.h"
#include <climits>

template <typename W>
AdjacencyList<W> Prim(AdjacencyList<W>);

template <typename W>
AdjacencyList<W> Prim(AdjacencyList<W> G){
    //s == 0
    unsigned int n_vec = G.get_nodes();

    //initialize Key[]
    std::vector<std::pair<W, int>> V(n_vec);

    //initialize pi[]
    std::vector<int> pi(n_vec);

    //line 1 : for each u in  V do
    for(unsigned int i = 1; i < n_vec; ++i){

        //line 2 : Key[u] = +INF
        V[i] = std::make_pair(INT_MAX, i);

        //line 3 : pi[u] <- NULL
        pi[i] = -1;
    }

    //line 4 : Key[s] <- 0
    V[0] = std::make_pair(0, 0);
    pi[0] = -1;

    //line 5 : Q <- V
    MinHeap Q(V);

    //line 6 : while Q is not empty do
    while(Q.size()!=0){

        //line 7 : u <- extractMin(Q)
        std::pair<W, int> u = Q.extractMin();

        //line 8 : for each v adjacent to u do
        for(std::pair<int, W> v: G[u.second]){

            //line 9 : if v in Q and w(u,v) < Key[v] then
            if(Q.exists(v.first) && v.second < V[v.first].first){
                Q.decreaseUpdate(v.second, v.first);

                //line 10 : pi[v] <- u
                pi[v.first] = u.second;

                //line 11 : Key[v] <- w(u,v)
                V[v.first].first = v.second;
            }
        }
    }

    //transform the list of edge into an Adjacency List
    AdjacencyList<W> A(n_vec);
    for(unsigned int i = 0; i < n_vec; ++i){
        if(pi[i] != -1 && pi[i] != i)
            A.add(Edge(i, pi[i], V[i].first));
    }

    //line 12 : return A
    return A;
}

#endif //ALGADVGRAPHS_PRIM_H
