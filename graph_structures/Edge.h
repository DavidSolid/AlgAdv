//
// Created by Alessandro on 04/04/2020.
//

#ifndef ALGADVGRAPHS_EDGE_H
#define ALGADVGRAPHS_EDGE_H

#include <vector>
#include <iostream>

template <typename T,typename W>
class Edge {
private:
    T node_1, node_2;
    W weight;
public:
    explicit Edge(const std::vector<T>& cpy);
    explicit Edge(std::vector<T>&& cpy);
    explicit Edge(T n1, T n2, W w);
    Edge(const Edge &edg);
    ~Edge();
    T get_node_1() const;
    T get_node_2() const;
    W get_weight() const;
    template <typename U>
    friend std::ostream& operator<<(std::ostream &os, const Edge<U,U>& ed);
    bool operator<(const Edge<T,W> &ed);
    template <typename U>
    friend bool operator<(const Edge<U,U>& ed_1, const Edge<U,U>& ed_2);
};

/*public methods*/
template <typename T,typename W>
Edge<T,W>::Edge(const std::vector<T>& cpy): node_1(0), node_2(0), weight(0){
    if(cpy.size() < 3) {
        node_1 = 0;
        node_2 = 0;
        weight = 0;
    }else {
        node_1 = cpy[0];
        node_2 = cpy[1];
        weight = cpy[2];
    }
}

template <typename T,typename W>
Edge<T,W>::Edge(std::vector<T>&& cpy): node_1(0), node_2(0), weight(0){
    if(cpy.size() < 3) {
        node_1 = 0;
        node_2 = 0;
        weight = 0;
    }else {
        node_1 = cpy[0];
        node_2 = cpy[1];
        weight = cpy[2];
    }
}

template <typename T,typename W>
Edge<T,W>::Edge(const T n1, const T n2, const W w): node_1(n1), node_2(n2), weight(w){
}

template <typename T,typename W>
Edge<T,W>::Edge(const Edge &edg){
    node_1 = edg.get_node_1();
    node_2 = edg.get_node_2();
    weight = edg.get_weight();
}

template <typename T,typename W>
Edge<T,W>::~Edge(){
}

template<typename T, typename W>
T Edge<T,W>::get_node_1() const {
    return node_1;
}

template<typename T, typename W>
T Edge<T,W>::get_node_2() const {
    return node_2;
}

template<typename T, typename W>
W Edge<T,W>::get_weight() const {
    return weight;
}

template<typename U>
std::ostream& operator<<(std::ostream& os, const Edge<U,U>& ed){
    os << ed.get_node_1()+1 << ' ' << ed.get_node_2()+1 << ' ' << ed.get_weight()+1;
    return os;
}

template<typename U>
bool operator<(const Edge<U,U> &ed_1, const Edge<U,U> & ed_2){
    return ed_1.get_weight() < ed_2.get_weight();
}

template<typename T, typename W>
bool Edge<T, W>::operator<(const Edge<T,W> &ed) {
    return weight < ed.weight;
}

#endif //ALGADVGRAPHS_EDGE_H
