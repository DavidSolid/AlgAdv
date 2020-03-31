#include <iostream>
#include <vector>
#include <algorithm>
#include "data_structures/MinHeap.h"
#include "data_structures/UnionFind.h"

int main() {
    //test min-heap
    auto to_order = std::vector<int>({2,11,3,1,4,10,5,7,6,0,8,9});
    MinHeap<int> heap = MinHeap<int>(std::move(to_order));
    heap.insert(5);
    unsigned int e = heap.size();
    for(unsigned int i=0; i<e; ++i){
        std::cout << heap.extractMin() << std::endl;
    }

    //test union-find
    int* arr = new int[7]{2,1,7,3,6,4,5};

    auto un = UnionFind(arr, 7);
    un.unite(2,3);
    un.unite(3,5);
    un.unite(4,7);
    un.unite(1,7);

    std::sort(arr, arr + 7);
    for(int i=0; i<7; ++i){
        std::cout << arr[i] << ": " << un.find(arr[i]) << std::endl;
    }
    return 0;
}