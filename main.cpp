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
        for (const auto &entry : std::filesystem::directory_iterator(path)) {
            std::vector<std::vector<int>> G = myParser.parse(entry.path());

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
            bool naive_union = (A_Kruskal_Naive.totalCost() == A_Kruskal_Union_Find.totalCost()) ||
                               (A_Kruskal_Naive == A_Kruskal_Union_Find);
            bool naive_prim = (A_Kruskal_Naive.totalCost() == A_Prim.totalCost()) || (A_Kruskal_Naive == A_Prim);
            bool prim_union =
                    (A_Prim.totalCost() == A_Kruskal_Union_Find.totalCost()) || (A_Prim == A_Kruskal_Union_Find);

            if (!naive_union || !naive_prim || !prim_union) {
                std::cout << entry.path() << " ";
                std::cout << " - NAIVE : " << A_Kruskal_Naive.totalCost() << " - UNION : "
                          << A_Kruskal_Union_Find.totalCost() << " PRIM : " << A_Prim.totalCost();
                std::cout << "                  naive_prim : " << naive_prim << " - naive_union : " << naive_union
                          << " - prim_union : " << prim_union << std::endl;
            }
        }
    }

    return 0;
}