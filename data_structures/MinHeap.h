//
// Created by Enrico on 31/03/2020.
//

#ifndef ALGADVGRAPHS_MINHEAP_H
#define ALGADVGRAPHS_MINHEAP_H

#include <vector>
#include <cmath>
#include <utility>

template <typename W>
class MinHeap {
private:
    std::vector<std::pair<W, int>> array;
    //tracking list
    int* track;

    //node level operations
    [[nodiscard]] int min_child(int) const;
    void push_up(int);
    void push_down(int);
    void min_heapify();
public:
    explicit MinHeap(const std::vector<std::pair<W, int>>&);
    explicit MinHeap(std::vector<std::pair<W, int>>&&);
    MinHeap(const MinHeap&);
    ~MinHeap();
    [[nodiscard]] int* get_track() const;
    [[nodiscard]] unsigned int size() const;
    [[nodiscard]] bool exists(unsigned int) const;
    std::pair<W, int> extractMin();
    void decreaseUpdate(const W&, int);
};

/*private methods*/
//finds minimum child of a given non-leaf node
template <typename W>
int MinHeap<W>::min_child(int pos) const{
    //check if node has both children
    if(2*pos + 2 >= array.size()){
        return 2*pos + 1;
    }
    //compare key value of both nodes
    std::pair<W, int> f_child = array[2*pos + 1];
    std::pair<W, int> s_child = array[2*pos + 2];
    if(f_child < s_child){
        return 2*pos + 1;
    }
    return 2*pos + 2;
}

//up-heap operation on a given node
template <typename W>
void MinHeap<W>::push_up(int pos){
    //repeat until conditions are met or until node is root
    while(std::floor((double)(pos - 1) / 2) >= 0){
        std::pair<W, int>& r_cur = array[pos];
        std::pair<W, int>& r_parent = array[std::floor((pos - 1) / 2)];
        //if current node's key is smaller than parent's, swap them, else terminate
        if(r_cur < r_parent){
            std::swap(r_cur, r_parent);
            std::swap(track[r_cur.second], track[r_parent.second]);
            pos = static_cast<int>(std::floor((pos - 1) / 2));
        } else pos = 0;
    }
}

//down-heap operation of a given node
template <typename W>
void MinHeap<W>::push_down(int pos){
    while(2*pos + 1 <= (int)(array.size()) - 1){
        int i_min = min_child(pos);
        std::pair<W, int>& m_child = array[i_min];
        std::pair<W, int>& r_current = array[pos];
        if (m_child < r_current){
            std::swap(m_child, r_current);
            std::swap(track[m_child.second], track[r_current.second]);
            pos = i_min;
        } else pos = array.size();
    }
}

//Floyd heap construction method
template <typename W>
void MinHeap<W>::min_heapify(){
    //pick last non leaf node
    int last_p = static_cast<int>(std::floor((double)(array.size())/2 - 1));
    //repeat down-heap operation until root
    for(int i = last_p; i >= 0; --i){
        push_down(i);
    }
}

/*public methods*/
template <typename W>
MinHeap<W>::MinHeap(const std::vector<std::pair<W, int>>& cpy): array(cpy), track(new int[cpy.size()]){
    for(int i = 0; i < cpy.size(); ++i){
        track[i] = i;
    }
    min_heapify();
}

template <typename W>
MinHeap<W>::MinHeap(std::vector<std::pair<W, int>>&& cpy): array(cpy), track(new int[cpy.size()]){
    for(int i = 0; i < cpy.size(); ++i){
        track[i] = i;
    }
    min_heapify();
}

template <typename W>
MinHeap<W>::~MinHeap(){
    delete[] track;
}

template <typename W>
int *MinHeap<W>::get_track() const{
    return track;
}

template <typename W>
unsigned int MinHeap<W>::size() const {
    return array.size();
}

template <typename W>
bool MinHeap<W>::exists(unsigned int v) const {
    //check if track[v] in not -1
    return track[v] >= 0;
}

template <typename W>
std::pair<W, int> MinHeap<W>::extractMin() {
    //select root value
    std::pair<W, int> val = array[0];
    std::pair<W, int> to_swap = array[array.size() - 1];
    //swap root with last element
    std::swap(array[0], array[array.size() - 1]);
    std::swap(track[val.second], track[to_swap.second]);
    //eliminate min
    array.pop_back();
    //update track to -1
    track[val.second] = -1;
    //rebuild minheap pushing down the new root
    push_down(0);
    return val;
}

template <typename W>
MinHeap<W>::MinHeap(const MinHeap& cpy): track(new int[cpy.size()]){
    for(int i = 0; i < cpy.size(); ++i){
        track[i] = cpy.get_track()[i];
    }
}

template <typename W>
void MinHeap<W>::decreaseUpdate(const W& n_value, int v) {
    //if node to update is present
    if(track[v] >=0){
        std::pair<W, int>& o_value = array[track[v]];
        //if the new value is less than the original
        if(n_value <= o_value.first){
            //update value and up-heap the selected node
            o_value.first = n_value;
            push_up(track[v]);
        }
    }
}

#endif //ALGADVGRAPHS_MINHEAP_H
