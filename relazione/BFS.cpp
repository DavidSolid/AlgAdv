bool AdjacencyList<W>::BFS(int v, int w) const {
    if(v == w)
        return true;
    bool L[array.size()] = {0};
    std::queue<int> q;
    q.push(v);
    while(!q.empty()){
        int current = q.front();
        L[current] = true;
        q.pop();
        for(int i=0; i < array[current].size(); ++i) {
            if(L[array[current][i].first] == 0){
                if(array[current][i].first == w){
                    return true;
                }else{
                    L[array[current][i].first] = true;
                    q.push(array[current][i].first);
                }
            }
        }
    }
    return false;
}

