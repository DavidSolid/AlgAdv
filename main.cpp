#include <iostream>
#include <vector>
#include <algorithm>
#include "data_structures/MinHeap.h"
#include "data_structures/UnionFind.h"
#include "data_structures/Parser.h"
#include "data_structures/Edge.h"

int main() {
    //test min-heap
    auto to_order = std::vector<int>({2,11,3,1,4,10,5,7,6,0,8,9});
    Parser textParser = Parser();
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

    std::vector<std::vector<int>> wrongMatrix = textParser.parse("..\\dataset\\input_random_02_10txt");

    std::vector<std::vector<int>> textMatrix;
    textParser.parse("..\\dataset\\input_random_02_10.txt",textMatrix);
    std::cout << "wrong parsing : " << wrongMatrix[0][0] << std::endl;
    std::cout << "right parsing : " << textMatrix[0][0] << " " << textMatrix[0][1] << std::endl;

    //Using the value from the first line parsed we build as many edges as described

    /*
    std::vector<Edge<int>> list_of_edge;
    for(int i = 0; i < textMatrix[0][1]; ++i){
        Edge<int> temp(std::move(textMatrix[i+1]));
        list_of_edge.push_back(temp);
    }
    std::cout << list_of_edge.size() << std::endl;

    */

    /*

    MinHeap<int> heap1 = MinHeap<int>(std::move(to_order));

    std::vector<int> to_order_2 = std::vector<int>({2,11});
    MinHeap<int> heap2 = MinHeap<int>(std::move(to_order_2));

    MinHeap<int> heap_errato = MinHeap<int>(std::move(textMatrix[0])); // lo costruisce senza problemi in debug

    std::vector<MinHeap<int>> container;

    container.push_back(heap); //ok
    container.push_back(heap1); //ok
    container.push_back(heap2); //ok
    container.push_back(heap_errato); //si rompe

    */


    return 0;
}