#include <bits/stdc++.h>
using namespace std;
 
class Graph
{
public:
    unordered_map<int, list<pair<int, int>>> adjList;

    void addEdge(int u, int v, int wt, bool direction)
    {
        adjList[u].push_back({v, wt});
        if (!direction)
        {
            adjList[v].push_back({u, wt});
        }
    }

    void printGraph()
    {
        for (auto &i : adjList)
        {
            cout << i.first << " -> ";
            for (auto &nbr : i.second)
            {
                cout << "(" << nbr.first << ", " << nbr.second << ") ";
            }
            cout << endl;
        }
    }

    // Dijkstra’s Algorithm
    void dijkstra(int src)
    {
        unordered_map<int, int> dist;
        for (auto &i : adjList)
        {
            dist[i.first] = INT_MAX;
        }

        set<pair<int, int>> s;
        dist[src] = 0;
        s.insert({0, src});

        while (!s.empty())
        {
            auto top = *(s.begin());
            int nodeDist = top.first;
            int topNode = top.second;
            s.erase(s.begin());

            for (auto &nbr : adjList[topNode])
            {
                if (nodeDist + nbr.second < dist[nbr.first])
                {
                    auto record = s.find({dist[nbr.first], nbr.first});
                    if (record != s.end())
                    {
                        s.erase(record);
                    }

                    dist[nbr.first] = nodeDist + nbr.second;
                    s.insert({dist[nbr.first], nbr.first});
                }
            }
        }

        cout << "Shortest distances from node " << src << ":" << endl;
        for (auto &d : dist)
        {
            cout << "Node " << d.first << " -> Distance: " << d.second << endl;
        }
    }

    // Prim’s Algorithm
    void primMST()
    {
        unordered_map<int, int> key;
        unordered_map<int, bool> mst;
        unordered_map<int, int> parent;

        for (auto &i : adjList)
        {
            key[i.first] = INT_MAX;
            mst[i.first] = false;
            parent[i.first] = -1;
        }

        // Start from any node (first in the map)
        int startNode = adjList.begin()->first;
        key[startNode] = 0;

        int n = adjList.size();

        for (int count = 0; count < n - 1; count++)
        {
            int mini = INT_MAX, u = -1;

            // Find the minimum key node not yet included in MST
            for (auto &i : adjList)
            {
                int node = i.first;
                if (!mst[node] && key[node] < mini)
                {
                    mini = key[node];
                    u = node;
                }
            }

            if (u == -1)
                break; // all nodes connected

            mst[u] = true;

            for (auto &nbr : adjList[u])
            {
                int v = nbr.first;
                int wt = nbr.second;
                if (!mst[v] && wt < key[v])
                {
                    key[v] = wt;
                    parent[v] = u;
                }
            }
        }

        cout << "Minimum Spanning Tree (Prim's Algorithm):\n";
        int totalWeight = 0;
        for (auto &i : parent)
        {
            if (i.second != -1)
            {
                cout << "Edge: " << i.second << " - " << i.first << " | Weight: " << key[i.first] << endl;
                totalWeight += key[i.first];
            }
        }
        cout << "Total Sum of weight of edges included in Prims Algo: " << totalWeight << endl;
    }

    void primMST(int n)
    {
        vector<int> key(n + 1, INT_MAX);
        vector<bool> mst(n + 1, false);
        vector<int> parent(n + 1, -1);

        key[1] = 0;

        for (int count = 1; count <= n - 1; count++)
        {
            int mini = INT_MAX, u = -1;

            // Pick the minimum key vertex not yet in MST
            for (int v = 1; v <= n; v++)
            {
                if (!mst[v] && key[v] < mini)
                {
                    mini = key[v];
                    u = v;
                }
            }

            if (u == -1)
                break; // All remaining nodes are disconnected

            mst[u] = true;

            for (auto &nbr : adjList[u])
            {
                int v = nbr.first;
                int weight = nbr.second;
                if (!mst[v] && weight < key[v])
                {
                    key[v] = weight;
                    parent[v] = u;
                }
            }
        }

        cout << "Minimum Spanning Tree (Prim's Algorithm):\n";
        int totalWeight = 0;
        for (int i = 2; i <= n; i++)
        {
            if (parent[i] != -1)
            {
                cout << "Edge: " << parent[i] << " - " << i << " | Weight: " << key[i] << endl;
                totalWeight += key[i];
            }
        }
        cout << "Total Sum of weight of edges included in Prims Algo: " << totalWeight << endl;
    }
};

void selectionSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        // Find the index of the minimum element in the unsorted part
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_idx])
            {
                min_idx = j;
            }
        }
        // Swap the minimum element with the first element of the unsorted part
        if (min_idx != i)
        {
            swap(arr[i], arr[min_idx]);
        }
    }
}

int main()
{
    int choice;
    do
    {
        cout << "\nMenu:\n";
        cout << "1. Dijkstra's Algorithm (Shortest Path)\n";
        cout << "2. Prim's Algorithm (Minimum Spanning Tree)\n";
        cout << "3. Selection Sort\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            Graph g;
            int nodes, edges, u, v, wt, src;
            cout << "Enter number of nodes and edges: ";
            cin >> nodes >> edges;

            cout << "Enter edges (u v weight):\n";
            for (int i = 0; i < edges; i++)
            {
                cin >> u >> v >> wt;
                g.addEdge(u, v, wt, false);
            }

            cout << "Graph Representation:\n";
            g.printGraph();
            cout << "Enter source node for Dijkstra's Algorithm: ";
            cin >> src;
            g.dijkstra(src);
        }
        else if (choice == 2)
        {
            Graph g;
            int nodes, edges, u, v, wt;
            cout << "Enter number of nodes and edges: ";
            cin >> nodes >> edges;

            cout << "Enter edges (u v weight):\n";
            for (int i = 0; i < edges; i++)
            {
                cin >> u >> v >> wt;
                g.addEdge(u, v, wt, false);
            }

            cout << "Graph Representation:\n";
            g.printGraph();
            g.primMST();
        }
        else if (choice == 3)
        {
            int arr[] = {64, 25, 12, 22, 11};
            int n = sizeof(arr) / sizeof(arr[0]);

            selectionSort(arr, n);

            cout << "Sorted array: ";
            for (int i = 0; i < n; i++)
            {
                cout << arr[i] << " ";
            }
            cout << endl;
        }
        else if (choice == 4)
        {
            cout << "Exiting...\n";
        }
        else
        {
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
