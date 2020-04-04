//
// Created by Alessandro on 04/04/2020.
//

#ifndef ALGADVGRAPHS_EDGE_H
#define ALGADVGRAPHS_EDGE_H

#include <vector>
#include <iostream>

template <typename T>
class Edge {
private:
    std::vector<T> array_of_3; //contains node_1, node_2, weight
public:
    explicit Edge(const std::vector<T>&);
    explicit Edge(std::vector<T>&&);
    Edge(const Edge &edg);
    ~Edge();
    T get_node_1() const;
    T get_node_2() const;
    T get_weight() const;
    template <typename U>
    friend std::ostream& operator<<(std::ostream &os, const Edge<U>& ed);
};

/*public methods*/
template <typename T>
Edge<T>::Edge(const std::vector<T>& cpy): array_of_3(std::vector<T>(cpy)){
    if(array_of_3.size() != 3) {
        array_of_3.resize(3, 0);
    }
}

template <typename T>
Edge<T>::Edge(std::vector<T>&& cpy): array_of_3(std::vector<T>(cpy)){
    if(array_of_3.size() != 3) {
        array_of_3.resize(3, 0);
    }
}

template<typename T>
Edge<T>::Edge(const Edge &edg): array_of_3(std::vector<T>(3)){
    array_of_3[0] = edg.get_node_1();
    array_of_3[1] = edg.get_node_2();
    array_of_3[2] = edg.get_weight();
}

template <typename T>
Edge<T>::~Edge(){
}

template<typename T>
T Edge<T>::get_node_1() const {
    return array_of_3[0];
}

template<typename T>
T Edge<T>::get_node_2() const {
    return array_of_3[1];
}

template<typename T>
T Edge<T>::get_weight() const {
    return array_of_3[2];
}

template<typename U>
std::ostream& operator<<(std::ostream& os, const Edge<U>& ed){
    os << ed.get_node_1() << ' ' << ed.get_node_2() << ' ' << ed.get_weight();
    return os;
}

#endif //ALGADVGRAPHS_EDGE_H
