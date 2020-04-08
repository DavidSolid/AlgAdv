//
// Created by Enrico on 31/03/2020.
//

#ifndef ALGADVGRAPHS_MINHEAP_H
#define ALGADVGRAPHS_MINHEAP_H

#include <vector>
#include <cmath>
#include <utility>

class MinHeap {
private:
    std::vector<std::pair<int, int>> array;
    int* track;

    [[nodiscard]] int min_child(int) const;
    void push_up(int);
    void push_down(int);
    void min_heapify();
public:
    explicit MinHeap(const std::vector<std::pair<int, int>>&);
    explicit MinHeap(std::vector<std::pair<int, int>>&&);
    MinHeap(const MinHeap&);
    ~MinHeap();
    [[nodiscard]] int* get_track() const;
    [[nodiscard]] unsigned int size() const;
    [[nodiscard]] bool exists(unsigned int) const;
    //void insert(const std::pair<int, int>&);
    std::pair<int, int> extractMin();
    void decreaseUpdate(const int&, int);
};

/*private methods*/
int MinHeap::min_child(int pos) const{
    if(2*pos + 2 >= array.size()){
        return 2*pos + 1;
    }
    std::pair<int, int> f_child = array[2*pos + 1];
    std::pair<int, int> s_child = array[2*pos + 2];
    if(f_child < s_child){
        return 2*pos + 1;
    }
    return 2*pos + 2;
}

void MinHeap::push_up(int pos){
    while(std::floor((double)(pos - 1) / 2) >= 0){
        std::pair<int, int>& r_cur = array[pos];
        std::pair<int, int>& r_parent = array[std::floor((pos - 1) / 2)];
        if(r_cur < r_parent){
            std::swap(r_cur, r_parent);
            std::swap(track[r_cur.second], track[r_parent.second]);
            pos = static_cast<int>(std::floor((pos - 1) / 2));
        } else pos = 0;
    }
}

void MinHeap::push_down(int pos){
    while(2*pos + 1 <= (int)(array.size()) - 1){
        int i_min = min_child(pos);
        std::pair<int, int>& m_child = array[i_min];
        std::pair<int, int>& r_current = array[pos];
        if (m_child < r_current){
            std::swap(m_child, r_current);
            std::swap(track[m_child.second], track[r_current.second]);
            pos = i_min;
        } else pos = array.size();
    }
}

void MinHeap::min_heapify(){
    int last_p = static_cast<int>(std::floor((double)(array.size())/2 - 1));
    for(int i = last_p; i >= 0; --i){
        push_down(i);
    }
}

/*public methods*/
MinHeap::MinHeap(const std::vector<std::pair<int, int>>& cpy): array(cpy), track(new int[cpy.size()]){
    for(int i = 0; i < cpy.size(); ++i){
        track[i] = i;
    }
    min_heapify();
}

MinHeap::MinHeap(std::vector<std::pair<int, int>>&& cpy): array(cpy), track(new int[cpy.size()]){
    for(int i = 0; i < cpy.size(); ++i){
        track[i] = i;
    }
    min_heapify();
}

MinHeap::~MinHeap(){
    delete[] track;
}

int *MinHeap::get_track() const{
    return track;
}

unsigned int MinHeap::size() const {
    return array.size();
}

bool MinHeap::exists(unsigned int v) const {
    return track[v] >= 0;
}

//void MinHeap::insert(const std::pair<int, int>& elem) {
    //array.push_back(elem);
    //push_up(array.size()-1);
//}

std::pair<int, int> MinHeap::extractMin() {
    std::pair<int, int> val = array[0];
    std::pair<int, int> to_swap = array[array.size() - 1];
    std::swap(array[0], array[array.size() - 1]);
    std::swap(track[val.second], track[to_swap.second]);
    array.pop_back();
    track[val.second] = -1;
    push_down(0);
    return val;
}

MinHeap::MinHeap(const MinHeap& cpy): track(new int[cpy.size()]){
    for(int i = 0; i < cpy.size(); ++i){
        track[i] = cpy.get_track()[i];
    }
}

void MinHeap::decreaseUpdate(const int& n_value, int v) {
    if(track[v] >=0){
        std::pair<int, int>& o_value = array[track[v]];
        if(n_value <= o_value.first){
            o_value.first = n_value;
            push_up(track[v]);
        }
    }
}

#endif //ALGADVGRAPHS_MINHEAP_H
