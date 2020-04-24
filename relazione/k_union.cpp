AdjacencyList<W> Kruskal_Union_Find(int n, std::vector<Edge<W>> E){
    AdjacencyList<W> A(n);
    int *V;
    V = new int[n_vec];
    std::iota(V, V + n, 0);
    UnionFind U(V, n_vec);
    std::sort(E.begin(), E.end());
    for (const auto &e : E) {
        if (U.find(e.get_node_1()) != U.find(e.get_node_2())) {
            A.add(e);
            U.unite(e.get_node_1(), e.get_node_2());
        }
        if (A.get_edges() == (A.get_nodes() - 1))
            break;
    }
    return A;
}