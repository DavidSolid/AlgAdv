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
AdjacencyList<W> Prim(AdjacencyList<W> A){
    unsigned int n_vec = A.get_nodes();
    std::vector<std::pair<W, int>> V(n_vec);
    std::vector<int> pi(n_vec);
    V[0] = std::make_pair(0, 0);
    pi[0] = -1;
    for(unsigned int i = 1; i < n_vec; ++i){
        V[i] = std::make_pair(INT_MAX, i);
        pi[i] = -1;
    }
    MinHeap Q(V);
    while(Q.size()!=0){
        std::pair<W, int> u = Q.extractMin();
        for(std::pair<int, W> v: A[u.second]){
            /*v = v.first; w(u,v) = v.second*/
            if(Q.exists(v.first) && v.second < V[v.first].first /*key[v]*/){
                Q.decreaseUpdate(v.second, v.first);
                V[v.first].first = v.second;
                pi[v.first] = u.second;
                //key[v] = w(u, v); pi[v] = u
            }
        }
    }
    /*return V*/
    AdjacencyList<W> res(n_vec);
    for(unsigned int i = 0; i < n_vec; ++i){
        if(pi[i] != -1 && pi[i] != i)
            res.add(Edge(i, pi[i], V[i].first));
    }
    return res;
}

#endif //ALGADVGRAPHS_PRIM_H
