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
    std::vector<T>* array;

    [[nodiscard]] int min_child(int) const;
    void push_up(int);
    void push_down(int);
    void min_heapify();
public:
    explicit MinHeap(const std::vector<T>&);
    explicit MinHeap(std::vector<T>&&);
    ~MinHeap();
    [[nodiscard]] unsigned int size() const;
    void insert(const T&);
    T extractMin();
};

/*private methods*/
template<typename T>
int MinHeap<T>::min_child(int pos) const{
    if(2*pos + 2 >= array->size()){
        return 2*pos + 1;
    }
    T f_child = (*array)[2*pos + 1];
    T s_child = (*array)[2*pos + 2];
    if(f_child < s_child){
        return 2*pos + 1;
    }
    return 2*pos + 2;
}

template <typename T>
void MinHeap<T>::push_up(int pos){
    while(std::floor((double)(pos - 1) / 2) >= 0){
        T& r_cur = (*array)[pos];
        T& r_parent = (*array)[std::floor((pos - 1) / 2)];
        if(r_cur < r_parent){
            std::swap(r_cur, r_parent);
            pos = static_cast<int>(std::floor((pos - 1) / 2));
        } else pos = 0;
    }
}

template <typename T>
void MinHeap<T>::push_down(int pos){
    while(2*pos + 1 <= (int)(array->size()) - 1){
        int i_min = min_child(pos);
        T& m_child = (*array)[i_min];
        T& r_current = (*array)[pos];
        if (m_child < r_current){
            std::swap(m_child,r_current);
            pos = i_min;
        } else pos = array->size();
    }
}

template <typename T>
void MinHeap<T>::min_heapify(){
    int last_p = static_cast<int>(std::floor((double)(array->size())/2 - 1));
    for(int i = last_p; i >= 0; --i){
        push_down(i);
    }
}

/*public methods*/
template <typename T>
MinHeap<T>::MinHeap(const std::vector<T>& cpy): array(new std::vector<T>(cpy)){
    min_heapify();
}

template <typename T>
MinHeap<T>::MinHeap(std::vector<T>&& cpy): array(new std::vector<T>(cpy)){
    min_heapify();
}

template <typename T>
MinHeap<T>::~MinHeap(){
    delete array;
}

template<typename T>
unsigned int MinHeap<T>::size() const {
    return array->size();
}

template<typename T>
void MinHeap<T>::insert(const T &elem) {
    array->push_back(elem);
    push_up(array->size()-1);
}

template<typename T>
T MinHeap<T>::extractMin() {
    T val = (*array)[0];
    std::swap((*array)[0], (*array)[array->size() - 1]);
    array->pop_back();
    push_down(0);
    return val;
}

#endif //ALGADVGRAPHS_MINHEAP_H
