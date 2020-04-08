//
// Created by Enrico on 07/04/2020.
//

#ifndef ALGADVGRAPHS_PRIM_H
#define ALGADVGRAPHS_PRIM_H

#include "../graph_structures/AdjacencyList.h"
#include "../graph_structures/Edge.h"
#include "../graph_structures/AdjacencyList.h"
#include "../data_structures/MinHeap.h"

template <typename T, typename W>
std::pair<int, AdjacencyList<T, W>> Prim(unsigned int, AdjacencyList<T, W>);

template <typename T, typename W>
std::pair<int, AdjacencyList<T, W>> Prim(unsigned int n_vec, AdjacencyList<T, W> A){
    std::vector<std::pair<W, T>> V(n_vec);
    std::vector<T> pi(n_vec);
    V[0] = std::make_pair(0, 0);
    pi[0] = -1;
    for(unsigned int i = 1; i < n_vec; ++i){
        V[i] = std::make_pair(INT_MAX, i);
        pi[i] = -1;
    }
    MinHeap<W> Q(V);
    while(Q.size()!=0){
        std::pair<W, T> u = Q.extractMin();
        for(std::pair<T, W> v: A[u.second]){
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
    AdjacencyList<T, W> res(n_vec);
    for(unsigned int i = 0; i < n_vec; ++i){
        if(p[i] != -1 && p[i] != i)
            res.add(Edge(i, pi[i], V[i].first));
    }
    return std::make_pair(n_vec, res);
}

#endif //ALGADVGRAPHS_PRIM_H
