#include <bits/stdc++.h>
using namespace std;

class Graph {
public:
    unordered_map<int, list<pair<int, int>>> adjList;

    void addEdge(int u, int v, int wt, bool direction) {
        adjList[u].push_back({v, wt});
        if (!direction) {
            adjList[v].push_back({u, wt});
        }
    }

    void printGraph() {
        for (auto& i : adjList) {
            cout << i.first << " -> ";
            for (auto& nbr : i.second) {
                cout << "(" << nbr.first << ", " << nbr.second << ") ";
            }
            cout << endl;
        }
    }

    // Dijkstra’s Algorithm
    void dijkstra(int src) {
        unordered_map<int, int> dist;
        for (auto& i : adjList) {
            dist[i.first] = INT_MAX;
        }

        set<pair<int, int>> s;
        dist[src] = 0;
        s.insert({0, src});

        while (!s.empty()) {
            auto top = *(s.begin());
            int nodeDist = top.first;
            int topNode = top.second;
            s.erase(s.begin());

            for (auto& nbr : adjList[topNode]) {
                if (nodeDist + nbr.second < dist[nbr.first]) {
                    auto record = s.find({dist[nbr.first], nbr.first});
                    if (record != s.end()) {
                        s.erase(record);
                    }

                    dist[nbr.first] = nodeDist + nbr.second;
                    s.insert({dist[nbr.first], nbr.first});
                }
            }
        }

        cout << "Shortest distances from node " << src << ":" << endl;
        for (auto& d : dist) {
            cout << "Node " << d.first << " -> Distance: " << d.second << endl;
        }
    }

    // Prim’s Algorithm
    void primMST() {
        unordered_map<int, int> key;
        unordered_map<int, bool> mstSet;
        unordered_map<int, int> parent;

        for (auto& i : adjList) {
            key[i.first] = INT_MAX;
            mstSet[i.first] = false;
            parent[i.first] = -1;
        }

        key.begin()->second = 0;
        set<pair<int, int>> s;
        s.insert({0, key.begin()->first});

        while (!s.empty()) {
            auto top = *(s.begin());
            int u = top.second;
            s.erase(s.begin());
            mstSet[u] = true;

            for (auto& nbr : adjList[u]) {
                int v = nbr.first;
                int weight = nbr.second;
                if (!mstSet[v] && weight < key[v]) {
                    s.erase({key[v], v});
                    key[v] = weight;
                    s.insert({key[v], v});
                    parent[v] = u;
                }
            }
        }

        cout << "Minimum Spanning Tree (Prim's Algorithm):" << endl;
        int totalSum = 0;
        for (auto& i : parent) {
            if (i.second != -1){
                cout << "Edge: " << i.second << " - " << i.first << " | Weight: " << key[i.first] << endl;
                totalSum += key[i.first];
            }

        }
        cout<<"Total Sum of weight of edges included in Prims Algo : "<<totalSum<<endl;
    }
};
 
int main() {
    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Dijkstra's Algorithm (Shortest Path)\n";
        cout << "2. Prim's Algorithm (Minimum Spanning Tree)\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            Graph g;
            int nodes, edges, u, v, wt, src;
            cout << "Enter number of nodes and edges: ";
            cin >> nodes >> edges;

            cout << "Enter edges (u v weight):\n";
            for (int i = 0; i < edges; i++) {
                cin >> u >> v >> wt;
                g.addEdge(u, v, wt, false);
            }

            cout << "Graph Representation:\n";
            g.printGraph();
            cout << "Enter source node for Dijkstra's Algorithm: ";
            cin >> src;
            g.dijkstra(src);

        } 
        else if (choice == 2) {
            Graph g;
            int nodes, edges, u, v, wt;
            cout << "Enter number of nodes and edges: ";
            cin >> nodes >> edges;
 
            cout << "Enter edges (u v weight):\n";
            for (int i = 0; i < edges; i++) {
                cin >> u >> v >> wt;
                g.addEdge(u, v, wt, false);
            }

            cout << "Graph Representation:\n";
            g.printGraph();
            g.primMST();

        } 
        else if (choice == 3) {
            cout << "Exiting...\n";
        }
        else {
            cout << "Invalid choice! Please enter a valid option.\n";
        }

    } while (choice != 3);

    return 0;
}


// Graph g ; 
//     g.addNode( "Katraj" , "PICT" ) ;
//     g.addNode( "Bharti" , "Katraj" ) ; 
//     g.addNode( "Bharti" , "PICT" ) ;
//     g.addNode( "Katraj" , "SKNCOE" ) ; 
//     g.addNode( "PICT" , "SKNCOE" ) ;
//     g.addNode( "SKNCOE" , "Temple" ) ; 
//     g.addNode( "Temple" , "Katraj" ) ; 
//     g.addNode( "Temple" , "Kondhwa" ) ; 

// 3 1
// 5 2
// 4 3
// 6 4
// 2 0

// 0 1 2
// 0 3 6
// 1 3 8
// 1 4 5
// 1 2 3
// 2 4 7



// 1 2 28
// 1 6 10
// 6 5 25
// 5 4 22
// 4 7 18
// 7 5 24
// 3 4 12
// 2 3 16
// 2 7 14


