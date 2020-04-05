#include <iostream>
#include <vector>
#include <algorithm>
#include "data_structures/MinHeap.h"
#include "data_structures/UnionFind.h"
#include "data_structures/Parser.h"
#include "data_structures/Edge.h"
#include "data_structures/AdjacencyList.h"

int main() {
    //test min-heap
    auto to_order = std::vector<int>({2,11,3,0,1,4,5,9,7,8,6,0,23});
    Parser textParser = Parser();
    auto real_to_order = std::vector<std::pair<int, int>>();
    for(unsigned int i = 0; i<to_order.size(); ++i){
        real_to_order.push_back(std::make_pair(to_order[i], i));
    }
    MinHeap<int> heap = MinHeap<int>(std::move(real_to_order));
    heap.decreaseUpdate(-1, 12);
    unsigned int e = heap.size();
    for(unsigned int i=0; i<e; ++i){
        for(unsigned int j=0; j<e; ++j){
            std::cout << heap.exists(j) << "-";
        }
        std::cout <<std::endl;
        auto f = heap.extractMin();
        std::cout << "(" << f.first << "," << f.second << ")" << std::endl;
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
    std::cout << "List of edges" << std::endl;
    std::vector<Edge<int,int>> list_of_edge;
    for(int i = 1; i <= textMatrix[0][1]; ++i){
        list_of_edge.emplace_back(textMatrix[i][0], textMatrix[i][1], textMatrix[i][2]);
    }
    for(const auto & i : list_of_edge){
        std::cout << i << std::endl;
    }

    std::cout << "Adjacency List" << std::endl;
    AdjacencyList<int,int> ad(textMatrix[0][0], list_of_edge);
    std::cout << ad.size() << std::endl;

    //devo cercare come chiamare DFS() passandogli un vettore L[n] con tutti Bool = false

    bool L[textMatrix[0][0]] = {false};
    std::cout << ad.DFS(8,4,L)<< std::endl; // esiste un path tra 8 e 4

    return 0;
}