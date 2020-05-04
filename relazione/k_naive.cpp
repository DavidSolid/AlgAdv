AdjacencyList<W> Kruskal_Naive_DFS(int n, std::vector<Edge<W>> E) {
    AdjacencyList <W> A(n);
    std::sort(E.begin(), E.end());
    for (int i = 0; i < E.size(); ++i) {
        if (!A.DFS(E[i].get_node_1(), E[i].get_node_2())) {
            A.add(E[i]);
            if (A.get_edges() == (A.get_nodes() - 1))
                break;
        }
    }
    return A;
}