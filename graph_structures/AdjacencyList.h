//
// Created by Alessandro on 05/04/2020.
//

#ifndef ALGADVGRAPHS_ADJACENCYLIST_H
#define ALGADVGRAPHS_ADJACENCYLIST_H

#include <vector>
#include <utility>
#include <iostream>
#include <climits>

template <typename W>
class AdjacencyList {
private:
    std::vector< std::vector< std::pair<int,W> > > array;
    bool DFS_inside(int v,int w,bool L[])const;
public:
    explicit AdjacencyList(int n);
    explicit AdjacencyList(int n, const std::vector<Edge<W>>&);
    explicit AdjacencyList(int n, std::vector<Edge<W>>&&);
    [[nodiscard]] unsigned int nodes() const;
    [[nodiscard]] unsigned int edges() const;
    [[nodiscard]] int totalCost() const;
    void add(Edge<W> ed);
    W isAdjacent(int n1, int n2) const;
    void matrixView()  const;
    std::vector<std::vector<W>> asMatrix()  const;
    [[nodiscard]] bool DFS(int v,int w)const;
    template <typename U>
    friend std::ostream& operator<<(std::ostream &os, const AdjacencyList<U>& ad);
    void order_array();
    bool operator==(const AdjacencyList<W> &ad) const;
    std::vector< std::pair<int,W> > operator[](int i) const;
};

/*private methods*/

/* Same as DSF, we just do not create the list of visited node L[n], but receive it from DFS()
 */
template <typename W>
bool AdjacencyList<W>::DFS_inside(int v, int w, bool L[]) const {
    L[v] = true; //preemptively set that the node v has been visited, to skip next call of DFS_inside(v,...)
    for(int i=0; i < array[v].size(); ++i){ //cycle all adjacent node of v
        if(L[array[v][i].first] == 0){ //if we have not check before this particular adjacent node of v then
            if(array[v][i].first == w){ // if the adjacent node is the searched node w then v and w are connected
                return true;
            }else{
                if(DFS_inside(array[v][i].first, w, L) != 0){ // search all adjacent node of this adjacent node
                    return true; // it exist at least one path from this adjacent node of v to the searched node w
                }
            }
        }
    }
    return false; // we have searched all nodes, and a path between v and w does not exist
}

/*public methods*/
template <typename W>
AdjacencyList<W>::AdjacencyList(int n): array(n, std::vector<std::pair<int,W>>()){
}

template<typename W>
AdjacencyList<W>::AdjacencyList(int n, const std::vector<Edge<W>> & vector): array(n, std::vector<std::pair<int,W>>()) {
    for(const auto & i : vector){
        /* add both sides:
         * [v1] (v2,w)
         * [v2] (v1,w)
         */
        array[i.get_node_1()].push_back(std::make_pair(i.get_node_2(), i.get_weight()));
        array[i.get_node_2()].push_back(std::make_pair(i.get_node_1(), i.get_weight()));
    }
}

template<typename W>
AdjacencyList<W>::AdjacencyList(int n, std::vector<Edge<W>> && vector): array(n, std::vector<std::pair<int,W>>()) {
    for(const auto & i : vector){
        /* add both sides:
         * [v1] (v2,w)
         * [v2] (v1,w)
         */
        array[i.get_node_1()].push_back(std::make_pair(i.get_node_2(), i.get_weight()));
        array[i.get_node_2()].push_back(std::make_pair(i.get_node_1(), i.get_weight()));
    }
}

template <typename W>
unsigned int AdjacencyList<W>::nodes() const {
    return array.size();
}

template <typename W>
unsigned int AdjacencyList<W>::edges() const {
    unsigned int cost = 0;
    for(const auto & i : array){
        cost += i.size();
    }
    return cost / 2;
}


template<typename W>
int AdjacencyList<W>::totalCost() const {
    int cost = 0;
    for(const auto & i : array){
        for(const auto & j : i){
            cost += j.second;
        }
    }
    return cost / 2;
}

template<typename W>
void AdjacencyList<W>::add(Edge<W> ed){
    array[ed.get_node_1()].push_back(std::make_pair(ed.get_node_2(), ed.get_weight()));
    array[ed.get_node_2()].push_back(std::make_pair(ed.get_node_1(), ed.get_weight()));
}

/*
 * Return the minimum weight W of the edge between n1 and n2
 * otherwise return INT_MAX
 */
template<typename W>
W AdjacencyList<W>::isAdjacent(int n1, int n2) const {
    W min_weight = INT_MAX;
    for(const auto & pair : array[n1]){
        if(pair.first == n2 && pair.second < min_weight) {
            min_weight = pair.second;
        }
    }
    return min_weight;
}

/* Multigraph matrix contains weight of minimum edges between vertices
 */
template<typename W>
void AdjacencyList<W>::matrixView() const {
    for(int i = 0; i < array.size(); ++i){
        for(int j = 0; j < array.size(); ++j){
            W mom = isAdjacent(i,j);
            if(mom != INT_MAX){
                std::cout << mom << ", ";
            }else{
                std::cout << "0, ";
            }
        }
        std::cout << std::endl;
    }
}


//Multigraph matrix contains weight of minimum edges between vertices
template<typename W>
std::vector<std::vector<W>> AdjacencyList<W>::asMatrix() const {
    std::vector<std::vector<W>> matrix(array.size(), std::vector<W>());
    for(int i = 0; i < array.size(); ++i){
        for(int j = 0; j < array.size(); ++j){
            W mom = isAdjacent(i,j);
            if(mom != INT_MAX){
                matrix[i].push_back(mom);
            }else{
                matrix[i].push_back(0);
            }
        }
    }
    return matrix;
}

/* DFS fast implementation:
 * Find if two nodes: v,w (whom we represent with their integer id) are connected.
 *
 * Return True if it exists a path between v and w, False otherwise.
 */
template<typename W>
bool AdjacencyList<W>::DFS(int v, int w) const {
    bool L[array.size()] = {0};
    L[v] = true; //preemptively set that the node v has been visited, to skip next call of DFS_inside(v,...)
    for(int i=0; i < array[v].size(); ++i){ //cycle all adjacent node of v
        if(L[array[v][i].first] == 0){ //if we have not check before this particular adjacent node of v then
            if(array[v][i].first == w){ // if the adjacent node is the searched node w then v and w are connected
                return true;
            }else{
                if(DFS_inside(array[v][i].first, w, L) != 0){ // search all adjacent node of this adjacent node
                    return true; // it exist at least one path from this adjacent node of v to the searched node w
                }
            }
        }
    }
    return false; // we have searched all nodes, and a path between v and w does not exist
}

template<typename U>
std::ostream& operator<<(std::ostream& os, const AdjacencyList<U>& ad){
    os << "Number of nodes   : " << ad.nodes() << std::endl;
    os << "Number of edges   : " << ad.edges() << std::endl;
    os << "Cost of all edges : " << ad.totalCost() << std::endl;
    for(int i = 0; i < ad.array.size(); ++i){
        os << i+1 << " :";
        for(int j = 0; j < ad.array[i].size(); ++j){
            os << "  ( " << ad.array[i][j].first+1 << " ; " << ad.array[i][j].second << " )";
        }
        os << std::endl;
    }
    return os;
}

template<typename W>
void AdjacencyList<W>::order_array() {
    for(int i=0; i < array.size(); ++i){
        std::sort(array[i].begin(), array[i].end());
    }
}

template<typename W>
bool AdjacencyList<W>::operator==(const AdjacencyList<W>& ad) const {
    return array == ad.array;
}

template<typename W>
std::vector<std::pair<int, W>> AdjacencyList<W>::operator[](int i) const {
    return array[i];
}
#endif //ALGADVGRAPHS_ADJACENCYLIST_H
