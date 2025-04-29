#include<bits/stdc++.h>
using namespace std;

template < typename T >
class Graph {
public:
    unordered_map<T, list<pair<T, int>>> adjList;

    void addEdge(T u, T v, int wt, bool direction) {
        if (direction) {
            adjList[u].push_back(make_pair(v, wt));
        } else {
            adjList[u].push_back(make_pair(v, wt));
            adjList[v].push_back(make_pair(u, wt));
        }
    }

    void printAll() {
        for (auto& i : adjList) {
            cout << i.first << " : { ";
            for (auto& nbr : adjList[i.first]) {
                cout << "(" << nbr.first << "," << nbr.second << ") , ";
            }
            cout << " }" << endl;
        }
    }

    void dfsIterative(map<T, bool>& vis) {
        for (auto& node : adjList) {
            if (!vis[node.first]) {
                dfs(node.first, vis);
            }
        }
    }

    void dfs(T src, map<T, bool>& vis) {
        vis[src] = true;
        cout << src << " ";
        for (auto& nbr : adjList[src]) {
            if (!vis[nbr.first]) {
                dfs(nbr.first, vis);
            }
        }
    }

    void dfsLevelPrint(T src, map<T, bool>& vis, map<T, int>& levels, int curr) {
        vis[src] = true;
        levels[src] = curr;
        cout << src << " level : " << curr << endl;

        for (auto& nbr : adjList[src]) {
            if (!vis[nbr.first]) {
                dfsLevelPrint(nbr.first, vis, levels, curr + 1);
            }
        }
        curr--;
    }

    void bfs(T src, map<T, bool>& vis) {
        queue<T> q;
        q.push(src);
        vis[src] = true;

        while (!q.empty()) {
            T front = q.front();
            q.pop();
            cout << front << " ";

            for (auto& nbr : adjList[front]) {
                if (!vis[nbr.first]) {
                    q.push(nbr.first);
                    vis[nbr.first] = true;
                }
            }
        }
    }
   
    void bfsRecursive(map < T, bool > & vis) {
        for (int i = 1; i < adjList.size(); ++i) {
            if (!vis[i]) {
                bfs(i, vis);
            }
        }
        cout<<endl;
    }

    void bfsLevelPrint(T src, map<T, bool>& vis) {
        queue<T> q;
        q.push(src);
        vis[src] = true;

        int level = 0;
        cout << "Level " << level << ": ";
        q.push(T());

        while (!q.empty()) {
            T front = q.front();
            q.pop();

            if (front == T()) {  
                if (!q.empty()) {
                    level++;
                    cout << "\nLevel " << level << ": ";
                    q.push(T());
                }
            } else {
                cout << front << " ";
                for (auto& nbr : adjList[front]) {
                    if (!vis[nbr.first]) {
                        q.push(nbr.first);
                        vis[nbr.first] = true;
                    }
                }
            }
        }
    }

    bool depthLimitedSearch(T src, T target, int limit) {
        if (src == target) {
            cout << src << " ";
            return true;
        }

        if (limit <= 0) {
            return false;
        }

        cout << src << " ";
        for (auto& nbr : adjList[src]) {
            if (depthLimitedSearch(nbr.first, target, limit - 1)) {
                return true;
            }
        }

        return false;
    }

    void performDepthLimitedSearch(T src, T target, int limit) {
        cout << "Depth-Limited Search (Limit = " << limit << "):" << endl;
        if (!depthLimitedSearch(src, target, limit)) {
            cout << "\nTarget not reachable within depth " << limit << endl;
        }
    }

    bool depthLimitedSearch(T src, T target, int limit, vector<T>& path) {
        if (src == target) {
            path.push_back(src);
            return true;
        }

        if (limit <= 0) {
            return false;
        }

        path.push_back(src);
        for (auto& nbr : adjList[src]) {
            if (find(path.begin(), path.end(), nbr.first) == path.end()) {
                if (depthLimitedSearch(nbr.first, target, limit - 1, path)) {
                    return true;
                }
            }
        }

        path.pop_back();
        return false;
    }

    void iterativeDeepeningDFS(T src, T target) {
        int depth = 0;
        while (true) {
            vector<T> path;
            cout << "For depth: " << depth << endl;
            if (depthLimitedSearch(src, target, depth, path)) {
                cout << "Path found: ";
                for (const auto& node : path) {
                    cout << node << " ";
                }
                cout << endl;
                return;
            }
            depth++;
            if (depth > adjList.size()) {
                cout << "Target is not reachable" << endl;
                return;
            }
        }
    }

    void webCrawlBFS(T startUrl) {
        queue<T> q;
        unordered_set<T> visited;
        unordered_map<T, int> levels;

        q.push(startUrl);
        visited.insert(startUrl);
        levels[startUrl] = 0;

        cout << "Crawling order (BFS) with levels:" << endl;

        while (!q.empty()) {
            T currentUrl = q.front();
            q.pop();

            cout << currentUrl << " at level " << levels[currentUrl] << endl;

            for (auto& nbr : adjList[currentUrl]) {
                if (visited.find(nbr.first) == visited.end()) {
                    q.push(nbr.first);
                    visited.insert(nbr.first);
                    levels[nbr.first] = levels[currentUrl] + 1;
                }
            }
        }
    }
};

int main() {
    Graph<int> g;
    int choice;

    int n;
    cout << "How many edges do you want to enter: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        int from, towards;
        bool direc;
        cout << "Enter source (from): ";
        cin >> from;
        cout << "Enter destination (towards): ";
        cin >> towards;
        cout << "Is it directed (1 for Yes, 0 for No): ";
        cin >> direc;

        g.addEdge(from, towards, 0, direc);
    }

    while (true) {
        cout << "\nMenu:" << endl;
        cout << "1. Add Edge" << endl;
        cout << "2. Print Graph" << endl;
        cout << "3. Perform DFS" << endl;
        cout << "4. Level print DFS" << endl;
        cout << "5. Perform BFS" << endl;
        cout << "6. BFS Recursive "<<endl;
        cout << "7. Level print BFS" << endl;
        cout << "8. Perform Depth-Limited Search" << endl;
        cout << "9. Perform Iterative Deepening DFS" << endl;
        cout << "10. Web Crawl (BFS)" << endl;
        cout << "11. DFS Recursive"<<endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int u, v, wt, dir;
                cout << "Enter source, destination, weight, and direction (1 for directed, 0 for undirected): ";
                cin >> u >> v >> wt >> dir;
                g.addEdge(u, v, wt, dir);
                break;
            }
            case 2: {
                g.printAll();
                break;
            }
            case 3: {
                int src;
                cout << "Enter source for DFS: ";
                cin >> src;
                map<int, bool> vis;
                g.dfs(src, vis);
                cout << endl;
                break;
            }
            case 4: {
                int src;
                cout << "Enter source for Level print DFS: ";
                cin >> src;
                map<int, bool> vis;
                map<int, int> levels;
                g.dfsLevelPrint(src, vis, levels, 0);
                break;
            }
            case 5: {
                int src;
                cout << "Enter source for BFS: ";
                cin >> src;
                map<int, bool> visited;
                g.bfs(src, visited);
                break;
            }
            case 6:{
                map<int, bool> visited;
                cout<<"BFS Recursive : "<<endl;
                g.bfsRecursive(visited);
            }
            case 7: {
                int src;
                cout << "Enter source for BFS Level Print: ";
                cin >> src;
                map<int, bool> vis;
                g.bfsLevelPrint(src, vis);
                break;
            }
            case 8: {
                int src, target, limit;
                cout << "Enter source, target, and depth limit for Depth-Limited Search: ";
                cin >> src >> target >> limit;
                g.performDepthLimitedSearch(src, target, limit);
                break;
            }
            case 9: {
                int src, target;
                cout << "Enter source and target for Iterative Deepening DFS: ";
                cin >> src >> target;
                g.iterativeDeepeningDFS(src, target);
                break;
            }
            case 10: {
                string startUrl;
                cout << "Enter starting URL for Web Crawl: ";
                cin >> startUrl;
                Graph<string> web;
                web.addEdge("example.com", "example.com/about", 1, true);
                web.addEdge("example.com", "example.com/contact", 1, true);
                web.addEdge("example.com/about", "example.com/team", 1, true);
                web.addEdge("example.com/contact", "example.com/form", 1, true);
                web.addEdge("example.com/team", "example.com/mission", 1, true);
                web.addEdge("example.com/form", "example.com/submit", 1, true);
                web.addEdge("example.com/mission", "example.com/history", 1, true);
                web.addEdge("example.com/submit", "example.com/success", 1, true);
                web.webCrawlBFS(startUrl);
                break;
            }
            case 11:{
                map<int, bool> visited;
                cout<<"DFS Iterative: "<<endl;
                g.dfsIterative(visited);
            }
            case 0: {
                cout << "Exiting..." << endl;
                return 0;
            }
            default: {
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        }
    }

    return 0;
}