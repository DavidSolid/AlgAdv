//
// Created by Enrico on 31/03/2020.
//

#ifndef ALGADVGRAPHS_UNIONFIND_H
#define ALGADVGRAPHS_UNIONFIND_H

#include <vector>
#include <utility>

class UnionFind {
private:
    std::vector<std::pair<int, int>> data;
public:
    explicit UnionFind(int*, int);
    [[nodiscard]] int size() const;
    [[nodiscard]] int find(const int&) const;
    void unite(const int&, const int&);
};

UnionFind::UnionFind(int* raw, int sz): data(sz){
    for(int i=0; i<sz; ++i){
        data[raw[i]] = std::make_pair(raw[i], 1);
    }
}

int UnionFind::size() const {
    return data.size();
}

void UnionFind::unite(const int& fst, const int& snd) {
    int f_tree = find(fst);
    int s_tree = find(snd);
    if(f_tree != s_tree){
        if(data[f_tree].second >= data[s_tree].second){
            data[s_tree].first = f_tree;
            data[f_tree].second += data[s_tree].second;
        } else{
            data[f_tree].first = s_tree;
            data[s_tree].second += data[f_tree].second;
        }
    }
}

int UnionFind::find(const int& elem) const {
    int current = elem;
    int parent = data[elem].first;
    while(parent != current){
        current = parent;
        parent = data[parent].first;
    }
    return parent;
}


#endif //ALGADVGRAPHS_UNIONFIND_H
