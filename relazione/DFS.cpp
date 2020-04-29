bool AdjacencyList<W>::DFS(int v, int w) const {
    if(v == w)
        return true;
    bool L[array.size()] = {0};
    L[v] = true;
    for(int i=0; i < array[v].size(); ++i){
        if(L[array[v][i].first] == 0){
            if(array[v][i].first == w){
                return true;
            }else{
                if(DFS_inside(array[v][i].first, w, L) != 0){
                    return true;
                }
            }
        }
    }
    return false;
}