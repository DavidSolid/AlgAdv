W AdjacencyList<W>::total_weight() const {
    int cost = 0;
    for(const auto & i : array){
        for(const auto & j : i){
            cost += j.second;
        }
    }
    return cost / 2;
}

