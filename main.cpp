#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <numeric>
#include <filesystem>
#include "data_structures/MinHeap.h"
#include "data_structures/UnionFind.h"
#include "utility/Parser.h"
#include "graph_structures/Edge.h"
#include "graph_structures/AdjacencyList.h"
#include "algorithms/kruskal_union_find.h"
#include "algorithms/kruskal_naive.h"
#include "algorithms/prim.h"

int main() {
    /*
     //test min-heap
    auto to_order = std::vector<int>({2,11,3,0,1,4,5,9,7,8,6,0,23});
    Parser textParser = Parser();
    auto real_to_order = std::vector<std::pair<int, int>>();
    for(unsigned int i = 0; i<to_order.size(); ++i){
        real_to_order.push_back(std::make_pair(to_order[i], i));
    }
    MinHeap<int> heap = MinHeap<int>(std::move(real_to_order));
    heap.decreaseUpdate(-1, 12);
    unsigned int e1 = heap.size();
    for(unsigned int i=0; i<e1; ++i){
        for(unsigned int j=0; j<e1; ++j){
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

    std::cout << ad.DFS(8,4)<< std::endl; // esiste un path tra 8 e 4

    //test Adjacency List with custom file:
    std::vector<std::vector<int>> test_parse = textParser.parse("..\\dataset\\1_test.txt");
    std::vector<Edge<int,int>> list_test;
    for(int i = 1; i < test_parse[0][1]; ++i){
        list_test.emplace_back(test_parse[i]);
    }
    AdjacencyList<int,int> ad_test(test_parse[0][0], list_test);
    std::cout << "Number of nodes : " << ad_test.size() << std::endl;
    std::cout << "Total weight : " << ad_test.totalCost() << std::endl;

    //missing 1 2 4993 -> 0 1 4993
    std::cout << "Does 1-2 exist? : " <<ad_test.DFS(0,1)<< std::endl;

    std::cout << ad_test << std::endl;

    std::cout << "Add edge 1 2 4993" << std::endl;

    ad_test.unite(Edge<int,int>(0,1,4993));

    std::cout << "Does 1-2 exist? : " <<ad_test.DFS(0,1)<< std::endl;

    std::cout << ad_test << std::endl;
*/
    {
        /*
        auto start = std::chrono::steady_clock::now();

        //Parse file .txt into graph G
        Parser myParser = Parser();
        std::vector<std::vector<int>> G = myParser.parse("..\\dataset\\input_random_01_10.txt");
        //G[0][0] = NUMBER OF NODES
        //G[0][1] = NUMBER OF EDGES
        for(int i = 1; i <= G[0][1]; ++i){
            G[i][2] += 10000;
        }

        //save all edges in E
        std::vector<Edge<int>> E;
        for(int i = 1; i <= G[0][1]; ++i){
            E.emplace_back(G[i]);
        }

        std::pair<int, AdjacencyList<int>> results_Prim = Prim(G[0][0], AdjacencyList<int>(G[0][0],E));
        std::pair<int, AdjacencyList<int>> results_Kruskal_Union_Find = Kruskal_Union_Find<int>(G[0][0], E);
        std::pair<int, AdjacencyList<int>> results_Kruskal_Naive = Kruskal_Naive<int>(G[0][0], E);

        int time_Prim = results_Prim.first;
        auto A_Prim = results_Prim.second;

        int time_Kruskal_Union_Find = results_Kruskal_Union_Find.first;
        auto A_Kruskal_Union_Find = results_Kruskal_Union_Find.second;

        int time_Kruskal_Naive = results_Kruskal_Naive.first;
        auto A_Kruskal_Naive = results_Kruskal_Naive.second;



        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;

        //std::cout << A_Kruskal_Union_Find;
        std::cout << "Prim Completed with                : " << time_Prim << " iteration vs " << G[0][1] << std::endl;
        std::cout << "Kruskal Union Find Completed with  : " << time_Kruskal_Union_Find << " iteration vs " << G[0][1] << std::endl;
        std::cout << "Kruskal Union Naive Completed with : " << time_Kruskal_Naive << " iteration vs " << G[0][1] << std::endl;

        //given that AdjacencyList is a vector of vector we try ==
        A_Prim.order_array();
        A_Kruskal_Naive.order_array();
        A_Kruskal_Union_Find.order_array();
        bool naive_union = A_Kruskal_Naive == A_Kruskal_Union_Find;
        bool naive_prim = A_Kruskal_Naive == A_Prim;
        bool prim_union = A_Prim == A_Kruskal_Union_Find;

        std::cout << "Naive == Prim      : " << naive_prim << std::endl;
        std::cout << "UnionFind == Naive : " << naive_union << std::endl;
        std::cout << "UnionFind == Prim  : " << prim_union << std::endl;
*/
        std::string path = "..\\dataset";
        Parser myParser = Parser();
        for (const auto & entry : std::filesystem::directory_iterator(path)){std::vector<std::vector<int>> G = myParser.parse(entry.path());
            //save all edges in E
            std::vector<Edge<int>> E;
            for (int i = 1; i <= G[0][1]; ++i) {
                E.emplace_back(G[i]);
            }

            AdjacencyList<int> A = AdjacencyList(G[0][0], E);
            std::pair<int, AdjacencyList<int>> results_Prim = Prim(G[0][0], A);
            std::pair<int, AdjacencyList<int>> results_Kruskal_Union_Find = Kruskal_Union_Find<int>(G[0][0], E);
            std::pair<int, AdjacencyList<int>> results_Kruskal_Naive = Kruskal_Naive<int>(G[0][0], E);

            auto A_Prim = results_Prim.second;

            auto A_Kruskal_Union_Find = results_Kruskal_Union_Find.second;

            auto A_Kruskal_Naive = results_Kruskal_Naive.second;

            //given that AdjacencyList is a vector of vector we try ==
            A_Prim.order_array();
            A_Kruskal_Naive.order_array();
            A_Kruskal_Union_Find.order_array();
            bool naive_union = (A_Kruskal_Naive.totalCost() == A_Kruskal_Union_Find.totalCost()) || (A_Kruskal_Naive == A_Kruskal_Union_Find);
            bool naive_prim = (A_Kruskal_Naive.totalCost() == A_Prim.totalCost()) || (A_Kruskal_Naive == A_Prim);
            bool prim_union = (A_Prim.totalCost() == A_Kruskal_Union_Find.totalCost()) || (A_Prim == A_Kruskal_Union_Find);

            if (!((naive_union && naive_prim) && prim_union)) {
                std::cout << entry.path() << " ";
                std::cout << " - NAIVE : " << A_Kruskal_Naive.totalCost() << " - UNION : " << A_Kruskal_Union_Find.totalCost() << " PRIM : " << A_Prim.totalCost();
                std::cout << " naive_prim : " << naive_prim << " - naive_union : " << naive_union << " - prim_union : " << prim_union << std::endl;
            }
        }

        /*
        std::vector<std::vector<int>> matrix = A_Kruskal_Naive.asMatrix();

        std::ofstream ofs(R"(C:\Users\alepe\Desktop\AlgAdv\dataset\1_test.txt)", std::ifstream::out | std::ifstream::trunc);
        if(ofs.good()){
            for(const auto & row : matrix){
                for(unsigned int j = 0; j < row.size(); ++j){
                    ofs << row[j];
                    if(j != (row.size() - 1)){
                        ofs << ", ";
                    }
                }
                ofs << std::endl;
            }
            std::cout << "Adjacency Matrix saved on file" << std::endl;
        }else{
            std::cout << "Failed to save Adjacency Matrix on file" << std::endl;
        }

        ofs.close();
         */
    }

    return 0;
}