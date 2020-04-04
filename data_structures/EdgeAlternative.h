//
// Created by Alessandro on 04/04/2020.
//

#ifndef ALGADVGRAPHS_EDGEALTERNATIVE_H
#define ALGADVGRAPHS_EDGEALTERNATIVE_H

#include <vector>
#include <iostream>

template <typename T,typename W>
class EdgeAlternative {
private:
    T node_1, node_2;
    W weight;
public:
    explicit EdgeAlternative(const std::vector<T>&);
    explicit EdgeAlternative(std::vector<T>&&);
    explicit EdgeAlternative(T n1, T n2, W w);
    EdgeAlternative(const EdgeAlternative &edg);
    ~EdgeAlternative();
    T get_node_1() const;
    T get_node_2() const;
    W get_weight() const;
    template <typename U>
    friend std::ostream& operator<<(std::ostream &os, const EdgeAlternative<U,U>& ed);
};

/*public methods*/
template <typename T,typename W>
EdgeAlternative<T,W>::EdgeAlternative(const std::vector<T>& cpy){
    if(cpy.size() < 3) {
        node_1 = NULL;
        node_2 = NULL;
        weight = NULL;
    }else {
        node_1 = cpy[0];
        node_2 = cpy[1];
        weight = cpy[2];
    }
}

template <typename T,typename W>
EdgeAlternative<T,W>::EdgeAlternative(std::vector<T>&& cpy){
    if(cpy.size() < 3) {
        node_1 = NULL;
        node_2 = NULL;
        weight = NULL;
    }else {
        node_1 = cpy[0];
        node_2 = cpy[1];
        weight = cpy[2];
    }
}

template <typename T,typename W>
EdgeAlternative<T,W>::EdgeAlternative(const T n1, const T n2, const W w): node_1(n1), node_2(n2), weight(w){
}

template <typename T,typename W>
EdgeAlternative<T,W>::EdgeAlternative(const EdgeAlternative &edg){
    node_1 = edg.get_node_1();
    node_2 = edg.get_node_2();
    weight = edg.get_weight();
}

template <typename T,typename W>
EdgeAlternative<T,W>::~EdgeAlternative(){
}

template<typename T, typename W>
T EdgeAlternative<T,W>::get_node_1() const {
    return node_1;
}

template<typename T, typename W>
T EdgeAlternative<T,W>::get_node_2() const {
    return node_2;
}

template<typename T, typename W>
W EdgeAlternative<T,W>::get_weight() const {
    return weight;
}

template<typename U>
std::ostream& operator<<(std::ostream& os, const EdgeAlternative<U,U>& ed){
    os << ed.get_node_1() << ' ' << ed.get_node_2() << ' ' << ed.get_weight();
    return os;
}

#endif //ALGADVGRAPHS_EDGEALTERNATIVE_H
