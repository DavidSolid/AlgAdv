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
#include "algorithms/kruskal_naive2.h"
#include "algorithms/prim.h"

int main() {

    {
        //Parse file .txt into graph G
        Parser myParser = Parser();
        std::vector<std::vector<int>> G = myParser.parse("..\\dataset\\input_random_68_100000.txt");
        //G[0][0] = NUMBER OF NODES
        //G[0][1] = NUMBER OF EDGES
        //for(int i = 1; i <= G[0][1]; ++i){
          //  G[i][2] += 10000;
        //}

        //save all edges in E
        std::vector<Edge<int>> E;
        for(int i = 1; i <= G[0][1]; ++i){
            E.emplace_back(G[i]);
        }

        auto start = std::chrono::steady_clock::now();

        std::pair<int, AdjacencyList<int>> results_Kruskal_Naive = Kruskal_Naive<int>(G[0][0], E);
        auto end_naive = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_naive = end_naive-start;

        std::pair<int, AdjacencyList<int>> results_Kruskal_Naive2 = Kruskal_Naive2<int>(G[0][0], E);
        auto end_naive2 = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_naive2 = end_naive2-end_naive;

        //std::pair<int, AdjacencyList<int>> results_Kruskal_Union_Find = Kruskal_Union_Find<int>(G[0][0], E);
        auto end_union = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_union = end_union-end_naive;

        //std::pair<int, AdjacencyList<int>> results_Prim = Prim(G[0][0], AdjacencyList<int>(G[0][0],E));
        auto end_prim = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_prim = end_prim-end_union;

        //int time_Prim = results_Prim.first;
        //auto A_Prim = results_Prim.second;

        //int time_Kruskal_Union_Find = results_Kruskal_Union_Find.first;
        //auto A_Kruskal_Union_Find = results_Kruskal_Union_Find.second;

        int time_Kruskal_Naive = results_Kruskal_Naive.first;
        auto A_Kruskal_Naive = results_Kruskal_Naive.second;

        int time_Kruskal_Naive2 = results_Kruskal_Naive2.first;
        auto A_Kruskal_Naive2 = results_Kruskal_Naive2.second;



        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;

        //std::cout << A_Kruskal_Union_Find;
        //std::cout << "Prim Completed with                : " << time_Prim << " iteration vs " << G[0][1] << std::endl;
        //std::cout << "Kruskal Union Find Completed with  : " << time_Kruskal_Union_Find << " iteration vs " << G[0][1] << std::endl;
        std::cout << "Kruskal DFS Completed with : " << time_Kruskal_Naive << " iteration vs " << G[0][1] << std::endl;
        std::cout << "Kruskal BFS Completed with : " << time_Kruskal_Naive2 << " iteration vs " << G[0][1] << std::endl;

        //std::cout << "PRIM  : " << elapsed_prim.count() << " costo : " << A_Prim.total_weight() << std::endl;
        std::cout << "NAIVE DFS : " << elapsed_naive.count() << " costo : " << A_Kruskal_Naive.total_weight() << std::endl;
        std::cout << "NAIVE BFS : " << elapsed_naive2.count() << " costo : " << A_Kruskal_Naive2.total_weight() <<  std::endl;
        //std::cout << "UNION : " << elapsed_union.count() << " costo : " << A_Kruskal_Union_Find.total_weight() << std::endl;
        std::cout << "Time : " << elapsed_seconds.count() <<  std::endl;


        /*
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
         */
    }

    return 0;
}