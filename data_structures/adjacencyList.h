//
// Created by Alessandro on 05/04/2020.
//

#ifndef ALGADVGRAPHS_ADJACENCYLIST_H
#define ALGADVGRAPHS_ADJACENCYLIST_H

#include <vector>
#include <utility>
//#include "data_structures/Edge.h"

template <typename T,typename W>
class AdjacencyList {
private:
    std::vector< std::vector< std::pair<T,W> > > array;
public:
    explicit AdjacencyList(int n);
    explicit AdjacencyList(int n, const std::vector<Edge<T,W>>&);
    explicit AdjacencyList(int n,std::vector<Edge<T,W>>&&);
    [[nodiscard]] unsigned int size() const;
    void unite(Edge<T,W> ed);
    bool DFS(T v,T w,bool L[])const;
};

/*public methods*/
template <typename T,typename W>
AdjacencyList<T,W>::AdjacencyList(int n): array(n, std::vector<std::pair<T,W>>()){//{std::make_pair(NULL,NULL)}
    /*for(int i= 0; i<array.size(); ++i){
        array[i].pop_back();
    }*/
}

template<typename T, typename W>
AdjacencyList<T, W>::AdjacencyList(int n, const std::vector<Edge<T, W>> & vector): array(n, std::vector<std::pair<T,W>>()) {
    for(const auto & i : vector){
        /* add both sides:
         * [v1] (v2,w)
         * [v2] (v1,w)
         */
        array[i.get_node_1()].push_back(std::make_pair(i.get_node_2(), i.get_weight()));
        array[i.get_node_2()].push_back(std::make_pair(i.get_node_1(), i.get_weight()));
    }
}

template<typename T, typename W>
AdjacencyList<T, W>::AdjacencyList(int n, std::vector<Edge<T, W>> && vector): array(n, std::vector<std::pair<T,W>>()) {
    for(const auto & i : vector){
        /* add both sides:
         * [v1] (v2,w)
         * [v2] (v1,w)
         */
        array[i.get_node_1()].push_back(std::make_pair(i.get_node_2(), i.get_weight()));
        array[i.get_node_2()].push_back(std::make_pair(i.get_node_1(), i.get_weight()));
    }
}


template <typename T,typename W>
unsigned int AdjacencyList<T,W>::size() const {
    return array.size();
}

template<typename T, typename W>
void AdjacencyList<T, W>::unite(Edge<T,W> ed){
    array[0].push_back(std::make_pair(ed.get_node_2(), ed.get_weight()));
}

/* DFS fast implementation:
 * Find if two nodes: v,w (whom we represent with their integer id) are connected.
 *
 * Return True if it exists a path between v and w, False otherwise.
 */
template<typename T, typename W>
bool AdjacencyList<T, W>::DFS(T v, T w, bool L[]) const {
    L[v] = true; //preemptively set that the node v has been visited, to skip next call of DFS(v,...)
    for(int i=0; i < array[v].size(); ++i){ //cycle all adjacent node of v
        if(L[array[v][i].first] == 0){ //if we have not check before this particular adjacent node of v then
            if(array[v][i].first == w){ // if the adjacent node is the searched node w then v and w are connected
                return true;
            }else{
                if(DFS(array[v][i].first, w, L) != 0){ // search all adjacent node of this adjacent node
                    return true; // it exist at least one path from this adjacent node of v to the searched node w
                }
            }
        }
    }
    return false; // we have searched all nodes, and a path between v and w does not exist
}


#endif //ALGADVGRAPHS_ADJACENCYLIST_H
