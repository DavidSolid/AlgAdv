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
    int* track;

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
template <typename W>
int MinHeap<W>::min_child(int pos) const{
    if(2*pos + 2 >= array.size()){
        return 2*pos + 1;
    }
    std::pair<W, int> f_child = array[2*pos + 1];
    std::pair<W, int> s_child = array[2*pos + 2];
    if(f_child < s_child){
        return 2*pos + 1;
    }
    return 2*pos + 2;
}

template <typename W>
void MinHeap<W>::push_up(int pos){
    while(std::floor((double)(pos - 1) / 2) >= 0){
        std::pair<W, int>& r_cur = array[pos];
        std::pair<W, int>& r_parent = array[std::floor((pos - 1) / 2)];
        if(r_cur < r_parent){
            std::swap(r_cur, r_parent);
            std::swap(track[r_cur.second], track[r_parent.second]);
            pos = static_cast<int>(std::floor((pos - 1) / 2));
        } else pos = 0;
    }
}

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

template <typename W>
void MinHeap<W>::min_heapify(){
    int last_p = static_cast<int>(std::floor((double)(array.size())/2 - 1));
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
    return track[v] >= 0;
}

template <typename W>
std::pair<W, int> MinHeap<W>::extractMin() {
    std::pair<W, int> val = array[0];
    std::pair<W, int> to_swap = array[array.size() - 1];
    std::swap(array[0], array[array.size() - 1]);
    std::swap(track[val.second], track[to_swap.second]);
    array.pop_back();
    track[val.second] = -1;
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
    if(track[v] >=0){
        std::pair<W, int>& o_value = array[track[v]];
        if(n_value <= o_value.first){
            o_value.first = n_value;
            push_up(track[v]);
        }
    }
}

#endif //ALGADVGRAPHS_MINHEAP_H
