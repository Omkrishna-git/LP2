#include <bits/stdc++.h>
using namespace std;

class Graph
{
public:
    unordered_map<int, list<pair<int, int>>> adjList;

    void addEdge(int u, int v, int wt, bool dir)
    {
        if (dir)
        {
            adjList[u].push_back({u, wt});
        }
        else
        {
            adjList[u].push_back({v, wt});
            adjList[v].push_back({u, wt});
        }
    }

    void printEdges()
    {
        for (auto &i : adjList)
        {
            cout << i.first << " -> ";
            for (auto &p : i.second)
            {
                cout << " { " << p.first << "," << " }";
            }
            cout << endl;
        }
    }


    
};

int main()
{

    return 0;
}