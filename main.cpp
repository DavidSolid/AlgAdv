#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <numeric>
#include <filesystem>
#include "utility/Parser.h"
#include "graph_structures/Edge.h"
#include "graph_structures/AdjacencyList.h"
#include "algorithms/kruskal_union_find.h"
#include "algorithms/kruskal_naive_bfs.h"
#include "algorithms/kruskal_naive_dfs.h"
#include "algorithms/prim.h"

int main() {

    {
        /*
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

        //auto start = std::chrono::steady_clock::now();

        std::pair<int, AdjacencyList<int>> results_Kruskal_Naive_DFS = Kruskal_Naive_DFS<int>(G[0][0], E);
        //auto end_naive = std::chrono::steady_clock::now();
        //std::chrono::duration<double> elapsed_naive = end_naive-start;

        std::pair<int, AdjacencyList<int>> results_Kruskal_Naive_BFS = Kruskal_Naive_BFS<int>(G[0][0], E);
        //auto end_naive2 = std::chrono::steady_clock::now();
        //std::chrono::duration<double> elapsed_naive2 = end_naive2-end_naive;

        std::pair<int, AdjacencyList<int>> results_Kruskal_Union_Find = Kruskal_Union_Find<int>(G[0][0], E);
        //auto end_union = std::chrono::steady_clock::now();
        //std::chrono::duration<double> elapsed_union = end_union-end_naive;

        std::pair<int, AdjacencyList<int>> results_Prim = Prim(AdjacencyList<int>(G[0][0],E));
        //auto end_prim = std::chrono::steady_clock::now();
        //std::chrono::duration<double> elapsed_prim = end_prim-end_union;

        int time_Prim = results_Prim.first;
        //auto A_Prim = results_Prim.second;

        int time_Kruskal_Union_Find = results_Kruskal_Union_Find.first;
        //auto A_Kruskal_Union_Find = results_Kruskal_Union_Find.second;

        int time_Kruskal_Naive_BFS = results_Kruskal_Naive_BFS.first;
        //auto A_Kruskal_Naive = results_Kruskal_Naive.second;

        int time_Kruskal_Naive_DFS = results_Kruskal_Naive_DFS.first;
        //auto A_Kruskal_Naive2 = results_Kruskal_Naive2.second;



        //auto end = std::chrono::steady_clock::now();
        //std::chrono::duration<double> elapsed_seconds = end-start;

        std::cout << "Prim : " << time_Prim << "  ";
        std::cout << "Kruskal Union Find : " << time_Kruskal_Union_Find << "  ";
        std::cout << "Kruskal DFS : " << time_Kruskal_Naive_DFS << "  ";
        std::cout << "Kruskal BFS Completed with : " << time_Kruskal_Naive_BFS << std::endl;

        //std::cout << "PRIM  : " << elapsed_prim.count() << " costo : " << A_Prim.total_weight() << std::endl;
        //std::cout << "NAIVE DFS : " << elapsed_naive.count() << " costo : " << A_Kruskal_Naive.total_weight() << std::endl;
        //std::cout << "NAIVE BFS : " << elapsed_naive2.count() << " costo : " << A_Kruskal_Naive2.total_weight() <<  std::endl;
        //std::cout << "UNION : " << elapsed_union.count() << " costo : " << A_Kruskal_Union_Find.total_weight() << std::endl;
        //std::cout << "Time : " << elapsed_seconds.count() <<  std::endl;

        */

        int iter = 0;

        std::string path = "..\\dataset";
        Parser myParser = Parser();
        for (const auto &entry : std::filesystem::directory_iterator(path)) {
            std::vector<std::vector<int>> G = myParser.parse(entry.path());

            //save all edges in E
            std::vector<Edge<int>> E;
            for (int i = 1; i <= G[0][1]; ++i) {
                E.emplace_back(G[i]);
            }

            auto start = std::chrono::steady_clock::now();

            auto A_Kruskal_Naive_DFS = Kruskal_Naive_DFS<int>(G[0][0], E);
            auto end_naive_DFS = std::chrono::steady_clock::now();


            auto A_Kruskal_Naive_BFS = Kruskal_Naive_BFS<int>(G[0][0], E);
            auto end_naive_BFS = std::chrono::steady_clock::now();

            auto A_Kruskal_Union_Find = Kruskal_Union_Find<int>(G[0][0], E);
            auto end_union = std::chrono::steady_clock::now();

            auto A_Prim = Prim(AdjacencyList<int>(G[0][0], E));
            auto end_prim = std::chrono::steady_clock::now();

            std::chrono::duration<double> elapsed_naive_DFS = end_naive_DFS - start;
            std::chrono::duration<double> elapsed_naive_BFS = end_naive_BFS - end_naive_DFS;
            std::chrono::duration<double> elapsed_union = end_union - end_naive_BFS;
            std::chrono::duration<double> elapsed_prim = end_prim - end_union;


            std::cout << entry.path() << "  Prim : " << elapsed_prim.count() << "  Kruskal Union Find : "
                      << elapsed_union.count() << "  Kruskal DFS : " << elapsed_naive_DFS.count()
                      << "  Kruskal BFS : " << elapsed_naive_BFS.count() << std::endl;
            std::cout << "MST WEIGHT : " << std::endl;
            std::cout << "Prim : " << A_Prim.total_weight() << "  Kruskal Union Find : "
                      << A_Kruskal_Union_Find.total_weight() << "  Kruskal DFS : " << A_Kruskal_Naive_DFS.total_weight()
                      << "  Kruskal BFS : " << A_Kruskal_Naive_BFS.total_weight() << std::endl;
        }
    }

    return 0;
}