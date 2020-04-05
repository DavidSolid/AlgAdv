//
// Created by Enrico on 31/03/2020.
//

#ifndef ALGADVGRAPHS_MINHEAP_H
#define ALGADVGRAPHS_MINHEAP_H

#include <vector>
#include <cmath>
#include <utility>

template <typename T>
class MinHeap {
private:
    std::vector<std::pair<T, int>> array;
    int* track;

    [[nodiscard]] int min_child(int) const;
    void push_up(int);
    void push_down(int);
    void min_heapify();
public:
    explicit MinHeap(const std::vector<std::pair<T, int>>&);
    explicit MinHeap(std::vector<std::pair<T, int>>&&);
    MinHeap(const MinHeap&);
    ~MinHeap();
    [[nodiscard]] int* get_track() const;
    [[nodiscard]] unsigned int size() const;
    [[nodiscard]] bool exists(unsigned int) const;
    //void insert(const std::pair<T, int>&);
    std::pair<T, int> extractMin();
    void decreaseUpdate(const T&, int);
};

/*private methods*/
template<typename T>
int MinHeap<T>::min_child(int pos) const{
    if(2*pos + 2 >= array.size()){
        return 2*pos + 1;
    }
    std::pair<T, int> f_child = array[2*pos + 1];
    std::pair<T, int> s_child = array[2*pos + 2];
    if(f_child < s_child){
        return 2*pos + 1;
    }
    return 2*pos + 2;
}

template <typename T>
void MinHeap<T>::push_up(int pos){
    while(std::floor((double)(pos - 1) / 2) >= 0){
        std::pair<T, int>& r_cur = array[pos];
        std::pair<T, int>& r_parent = array[std::floor((pos - 1) / 2)];
        if(r_cur < r_parent){
            std::swap(r_cur, r_parent);
            std::swap(track[r_cur.second], track[r_parent.second]);
            pos = static_cast<int>(std::floor((pos - 1) / 2));
        } else pos = 0;
    }
}

template <typename T>
void MinHeap<T>::push_down(int pos){
    while(2*pos + 1 <= (int)(array.size()) - 1){
        int i_min = min_child(pos);
        std::pair<T, int>& m_child = array[i_min];
        std::pair<T, int>& r_current = array[pos];
        if (m_child < r_current){
            std::swap(m_child, r_current);
            std::swap(track[m_child.second], track[r_current.second]);
            pos = i_min;
        } else pos = array.size();
    }
}

template <typename T>
void MinHeap<T>::min_heapify(){
    int last_p = static_cast<int>(std::floor((double)(array.size())/2 - 1));
    for(int i = last_p; i >= 0; --i){
        push_down(i);
    }
}

/*public methods*/
template <typename T>
MinHeap<T>::MinHeap(const std::vector<std::pair<T, int>>& cpy): array(cpy), track(new unsigned int[cpy.size()]){
    for(int i = 0; i < cpy.size(); ++i){
        track[i] = i;
    }
    min_heapify();
}

template <typename T>
MinHeap<T>::MinHeap(std::vector<std::pair<T, int>>&& cpy): array(cpy), track(new int[cpy.size()]){
    for(int i = 0; i < cpy.size(); ++i){
        track[i] = i;
    }
    min_heapify();
}

template <typename T>
MinHeap<T>::~MinHeap(){
    delete[] track;
}

template<typename T>
int *MinHeap<T>::get_track() const{
    return track;
}

template<typename T>
unsigned int MinHeap<T>::size() const {
    return array.size();
}

template<typename T>
bool MinHeap<T>::exists(unsigned int v) const {
    return track[v] >= 0;
}

//template<typename T>
//void MinHeap<T>::insert(const std::pair<T, int>& elem) {
    //array.push_back(elem);
    //push_up(array.size()-1);
//}

template<typename T>
std::pair<T, int> MinHeap<T>::extractMin() {
    std::pair<T, int> val = array[0];
    std::pair<T, int> to_swap = array[array.size() - 1];
    std::swap(array[0], array[array.size() - 1]);
    std::swap(track[val.second], track[to_swap.second]);
    array.pop_back();
    track[val.second] = -1;
    push_down(0);
    return val;
}

template<typename T>
MinHeap<T>::MinHeap(const MinHeap& cpy): track(new int[cpy.size()]){
    for(int i = 0; i < cpy.size(); ++i){
        track[i] = cpy.get_track()[i];
    }
}

template<typename T>
void MinHeap<T>::decreaseUpdate(const T& n_value, int v) {
    if(track[v] >=0){
        std::pair<T, int>& o_value = array[track[v]];
        if(n_value <= o_value.first){
            o_value.first = n_value;
            push_up(track[v]);
        }
    }
}

#endif //ALGADVGRAPHS_MINHEAP_H
