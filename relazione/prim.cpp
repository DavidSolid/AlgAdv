AdjacencyList<W> Prim(AdjacencyList<W> G){
    unsigned int n_vec = G.get_nodes();
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
        for(std::pair<int, W> v: G[u.second]){
            if(Q.exists(v.first) && v.second < V[v.first].first){
                Q.decreaseUpdate(v.second, v.first);
                V[v.first].first = v.second;
                pi[v.first] = u.second;
            }
        }
    }
    AdjacencyList<W> A(n_vec);
    for(unsigned int i = 0; i < n_vec; ++i){
        if(pi[i] != -1 && pi[i] != i)
            A.add(Edge(i, pi[i], V[i].first));
    }
    return A;
}

