#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <queue>
#include <sstream>
#include "Graph.h"
//using namespace std;

int main() {
   /* auto start = chrono::high_resolution_clock::now();
    Graph graph;

    graph.make_connections("1", { {"2",10},{"3",6},{"4",8}});
    graph.make_connection("3", "5", 3);

    graph.make_connections("2", { {"7",11},{"4",5},{"5",13} });

    graph.make_connections("4", { {"7",12},{"3",2},{"6",7},{"5",5} });

    graph.make_connections("5", { {"6",9},{"9",12} });
    graph.make_connections("7", { {"6",4},{"8",6},{"9",16} });

    graph.make_connections("6", { {"9",10}, {"8",8} });
    
    auto path = graph.dijkstra("1", "9");
    std::cout << "shortes path is:" << path.second << endl;
    for (auto node : path.first) {
        cout << node << " ";
    }
    cout << endl;
    auto end = chrono::high_resolution_clock::now();
    auto duration = duration_cast<chrono::microseconds>(end - start);

    cout << "Execution time: " << duration.count() << " mircoseconds" << endl;
    cout << "Execution time: " << duration.count() / 1000.0 << " milliseconds" << endl;
    cout << "Execution time: " << duration.count() / 1000000.0 << " seconds" << endl;
    */
    try {
        auto start = chrono::high_resolution_clock::now();

        Graph graph("1000.txt");
        //auto path = graph.find_way_DFS("15", "322");
        auto path = graph.dijkstra("0", "709");
        cout << "shortes path is:" << path.second << endl;
        for (auto node : path.first) {
            cout << node << " ";
        }
        cout << endl;
        auto end = chrono::high_resolution_clock::now();
        auto duration = duration_cast<chrono::microseconds>(end - start);

        cout << "Execution time: " << duration.count() << " mircoseconds" << endl;
        cout << "Execution time: " << duration.count() / 1000.0 << " milliseconds" << endl;
        cout << "Execution time: " << duration.count() / 1000000.0 << " seconds" << endl;
    }
    catch (const exception& e) {
        cout << e.what() << endl;
    }
    return 0;
}