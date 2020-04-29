//
// Created by Alessandro on 05/04/2020.
//

#ifndef ALGADVGRAPHS_ADJACENCYLIST_H
#define ALGADVGRAPHS_ADJACENCYLIST_H

#include <vector>
#include <utility>
#include <queue>

template <typename W>
class AdjacencyList {
private:
    std::vector< std::vector< std::pair<int,W> > > array;
    unsigned int edges;
    bool DFS_inside(int v,int w,bool L[])const;
public:
    explicit AdjacencyList(int n);
    explicit AdjacencyList(int n, const std::vector<Edge<W>>&);
    explicit AdjacencyList(int n, std::vector<Edge<W>>&&);
    [[nodiscard]] unsigned int get_nodes() const;
    [[nodiscard]] unsigned int get_edges() const;
    [[nodiscard]] W total_weight() const;
    void add(Edge<W> ed);
    [[nodiscard]] bool DFS(int v,int w)const;
    [[nodiscard]] bool BFS(int v,int w)const;
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
AdjacencyList<W>::AdjacencyList(int n): array(n, std::vector<std::pair<int,W>>()), edges(0){
}

template<typename W>
AdjacencyList<W>::AdjacencyList(int n, const std::vector<Edge<W>> & vector): array(n, std::vector<std::pair<int,W>>()), edges(vector.size()) {
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
AdjacencyList<W>::AdjacencyList(int n, std::vector<Edge<W>> && vector): array(n, std::vector<std::pair<int,W>>()), edges(vector.size()) {
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
unsigned int AdjacencyList<W>::get_nodes() const {
    return array.size();
}

template <typename W>
unsigned int AdjacencyList<W>::get_edges() const {
    return edges;
}

template<typename W>
W AdjacencyList<W>::total_weight() const {
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
    edges++;
}

/* DFS fast implementation:
 * Find if two nodes: v,w (whom we represent with their integer id) are connected.
 *
 * Return True if it exists a path between v and w, False otherwise.
 */
template<typename W>
bool AdjacencyList<W>::DFS(int v, int w) const {
    if(v == w){
        return true;
    }
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

/* BFS iterative implementation:
 * Find if two nodes: v,w (whom we represent with their integer id) are connected.
 *
 * Return True if it exists a path between v and w, False otherwise.
 */
template<typename W>
bool AdjacencyList<W>::BFS(int v, int w) const {
    if(v == w){
        return true;
    }
    bool L[array.size()] = {0};
    std::queue<int> q;
    q.push(v);
    while(!q.empty()){
        int current = q.front();
        L[current] = true;
        q.pop();
        for(int i=0; i < array[current].size(); ++i) { //cycle all adjacent node of current
            if(L[array[current][i].first] == 0){ //if we have not already checked this particular adjacent node
                if(array[current][i].first == w){ //if the adjacent node is the searched node w then v and w are connected
                    return true;
                }else{
                    L[array[current][i].first] = true; //mark the adjacent node as checked
                    q.push(array[current][i].first);  //add the adjacent node to the queue for further checks
                }
            }
        }
    }
    return false; // we have searched all nodes, and a path between v and w does not exist
}

template<typename W>
std::vector<std::pair<int, W>> AdjacencyList<W>::operator[](int i) const {
    return array[i];
}

#endif //ALGADVGRAPHS_ADJACENCYLIST_H
