//
// Created by Alessandro on 04/04/2020.
//

#ifndef ALGADVGRAPHS_EDGE_H
#define ALGADVGRAPHS_EDGE_H

#include <vector>
#include <iostream>

template <typename W>
class Edge {
private:
    int node_1, node_2;
    W weight;
public:
    explicit Edge(const std::vector<int>& cpy);
    explicit Edge(std::vector<int>&& cpy);
    explicit Edge(int n1, int n2, W w);
    Edge(const Edge &edg);
    ~Edge();
    [[nodiscard]] int get_node_1() const;
    [[nodiscard]] int get_node_2() const;
    W get_weight() const;
    bool operator<(const Edge<W> &ed);
    template <typename U>
    friend std::ostream& operator<<(std::ostream &os, const Edge<U>& ed);
    template <typename U>
    friend bool operator<(const Edge<U>& ed_1, const Edge<U>& ed_2);
};

/*public methods*/
template <typename W>
Edge<W>::Edge(const std::vector<int>& cpy): node_1(0), node_2(0), weight(0){
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

template <typename W>
Edge<W>::Edge(std::vector<int>&& cpy): node_1(0), node_2(0), weight(0){
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

template <typename W>
Edge<W>::Edge(const int n1, const int n2, const W w): node_1(n1), node_2(n2), weight(w){
}

template <typename W>
Edge<W>::Edge(const Edge &edg){
    node_1 = edg.get_node_1();
    node_2 = edg.get_node_2();
    weight = edg.get_weight();
}

template <typename W>
Edge<W>::~Edge()= default;

template<typename W>
int Edge<W>::get_node_1() const {
    return node_1;
}

template<typename W>
int Edge<W>::get_node_2() const {
    return node_2;
}

template<typename W>
W Edge<W>::get_weight() const {
    return weight;
}

template<typename U>
std::ostream& operator<<(std::ostream& os, const Edge<U>& ed){
    os << ed.get_node_1()+1 << ' ' << ed.get_node_2()+1 << ' ' << ed.get_weight();
    return os;
}

template<typename U>
bool operator<(const Edge<U> &ed_1, const Edge<U> & ed_2){
    return ed_1.get_weight() < ed_2.get_weight();
}

template<typename W>
bool Edge<W>::operator<(const Edge<W> &ed) {
    return weight < ed.weight;
}

#endif //ALGADVGRAPHS_EDGE_H
