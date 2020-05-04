#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <filesystem>
#include "utility/Parser.h"
#include "graph_structures/Edge.h"
#include "graph_structures/AdjacencyList.h"
#include "algorithms/kruskal_union_find.h"
#include "algorithms/kruskal_naive_bfs.h"
#include "algorithms/kruskal_naive_dfs.h"
#include "algorithms/prim.h"

int main() {
    //IF YOU WANT TO CHECK ONLY ONE GRAPH YOU CAN USE THIS COMMENTED SCRIPT
    /*
    //Parse file .txt into graph G
    Parser myParser = Parser();
    std::vector<std::vector<int>> G = myParser.parse("..\\dataset\\input_random_68_100000.txt");
    //G[0][0] = NUMBER OF NODES
    //G[0][1] = NUMBER OF EDGES

    //save all edges in E
    std::vector<Edge<int>> E;
    for(int i = 1; i <= G[0][1]; ++i){
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

    std::cout << "Prim : " << elapsed_prim.count() << "  Kruskal Union Find : "
              << elapsed_union.count() << "  Kruskal DFS : " << elapsed_naive_DFS.count()
              << "  Kruskal BFS : " << elapsed_naive_BFS.count() << std::endl;

    std::cout << "MST WEIGHT : " << std::endl;

    std::cout << "Prim : " << A_Prim.total_weight() << "  Kruskal Union Find : "
              << A_Kruskal_Union_Find.total_weight() << "  Kruskal DFS : " << A_Kruskal_Naive_DFS.total_weight()
              << "  Kruskal BFS : " << A_Kruskal_Naive_BFS.total_weight() << std::endl;

    */

    //IF YOU WANT TO CHECK ALL THE DATASET YOU CAN USE THIS SCRIPT
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

        std::cout << entry.path() << "  Prim : " << A_Prim.total_weight() << "  Kruskal Union Find : "
                  << A_Kruskal_Union_Find.total_weight() << "  Kruskal DFS : " << A_Kruskal_Naive_DFS.total_weight()
                  << "  Kruskal BFS : " << A_Kruskal_Naive_BFS.total_weight() << std::endl << std::endl;
    }

    return 0;
}