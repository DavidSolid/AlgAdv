#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include "data_structures/MinHeap.h"
#include "data_structures/UnionFind.h"
#include "data_structures/Parser.h"
#include "data_structures/Edge.h"
#include "data_structures/AdjacencyList.h"

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
    /*
     * Attepmp to Kruskal with union find with
     * 100 node "..\\dataset\\input_random_17_100.txt"
     * must transplant to own file
     */
    {
        auto start = std::chrono::steady_clock::now();

        //Parse file .txt into graph G
        Parser myParser = Parser();
        std::vector<std::vector<int>> G = myParser.parse("..\\dataset\\input_random_25_400.txt");
        //G[0][0] = NUMBER OF NODES
        //G[0][1] = NUMBER OF EDGES
        for(int i = 1; i <= G[0][1]; ++i){
            G[i][2] += 10000;
        }

        //save all edges in E
        std::vector<Edge<int,int>> E;
        for(int i = 1; i <= G[0][1]; ++i){
            E.emplace_back(G[i]);
        }

        //line 1 : Start A empty
        AdjacencyList<int,int> A(G[0][0]);

        //line 2 : Initialize U
        int *ar;
        ar = new int[G[0][0]];
        for(int i = 0; i < G[0][0]; ++i){
            ar[i] = i;
        }
        UnionFind<int> U(ar, G[0][0]);

        //line 3 : sort E
        /*
        std::sort(E.begin(), E.end(), [](const Edge<int,int> & a, const Edge<int,int> & b) -> bool{
            return a.get_weight() < b.get_weight();
        });
        */
        std::sort(E.begin(), E.end());

        //line 4 : for each edge in E do
        int time = 0;
        for(const auto & e : E){
            ++time;
            //line 5 : if e.node_1 and e.node_2 belong to two different connected components then
            if(U.find(e.get_node_1()) != U.find(e.get_node_2())){
                //line 6 : add e to A
                A.unite(e);
                //line 7 : unite e.node_1 and e.node_2
                U.unite(e.get_node_1(), e.get_node_2());
            }
            if(A.edges() == (A.nodes() - 1))
                break;
        }

        //line 8 : return A

        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;

        std::cout << A;
        std::cout << "Graph of 'input_random_02_10.txt'" << std::endl;
        std::cout << "Completed with " << time << " iteration vs " << G[0][1] << std::endl;
        std::cout << "Completed in " << elapsed_seconds.count() << " seconds" << std::endl;
        std::cout << A.nodes() << " " << A.edges() << std::endl;



        std::vector<std::vector<int>> matrix = A.asMatrix();

        std::ofstream ofs(R"(C:\Users\alepe\Desktop\AlgAdv\dataset\1_test.txt)", std::ifstream::out | std::ifstream::trunc);
        if(ofs.good()){
            for(const auto & row : matrix){
                for(int j = 0; j < row.size(); ++j){
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
    }

    return 0;
}