//
// Created by Enrico on 31/03/2020.
//

#ifndef ALGADVGRAPHS_UNIONFIND_H
#define ALGADVGRAPHS_UNIONFIND_H

#include <map>
#include <utility>

template <typename T>
class UnionFind {
private:
    std::map<T, std::pair<T, int>> data;
public:
    explicit UnionFind(T*, int);
    [[nodiscard]] int size() const;
    T find(const T&) const;
    void unite(const T&, const T&);
};

template<typename T>
UnionFind<T>::UnionFind(T* raw, int sz){
    for(int i=0; i<sz; ++i){
        data[raw[i]] = std::make_pair(raw[i], 1);
    }
}

template<typename T>
int UnionFind<T>::size() const {
    return data.size();
}

template<typename T>
void UnionFind<T>::unite(const T& fst, const T& snd) {
    T f_tree = find(fst);
    T s_tree = find(snd);
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

template<typename T>
T UnionFind<T>::find(const T& elem) const {
    T current = elem;
    T parent = (data.at(elem)).first;
    while(parent != current){
        current = parent;
        parent = (data.at(parent)).first;
    }
    return parent;
}


#endif //ALGADVGRAPHS_UNIONFIND_H
