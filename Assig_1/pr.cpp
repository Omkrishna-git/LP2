
#include <bits/stdc++.h>
using namespace std;

class Graph{
    public:
        unordered_map<int,list<pair<int,int>>>adjList;
    
        void addEdge(int u,int v,int wt, bool dir){
            if(dir){
                adjList[u].push_back({v,wt});
            }
            else{
                adjList[u].push_back({v,wt});
                adjList[v].push_back({u,wt});
            }
        }

        void print(){
            for(auto &i : adjList){
                cout<<i.first<<" -> ";
                for(auto &j : i.second){
                    cout<<"{ "<<j.first<<" , "<<j.second<<" }";
                }
                cout<<endl;
            }
        }

        void dfsIterative(map<int,bool>&vis){
            for(auto&i : adjList){
                if(!vis[i.first]){
                    vis[i.first] = true;
                    dfs(i.first,vis);
                }
            }
        }

        void dfs(int src,map<int,bool>&vis){
            vis[src] = true;
            cout<<src<<", ";

            for(auto &i : adjList[src]){
                if(!vis[i.first]){
                    vis[i.first] = true;
                    dfs(i.first,vis);
                }
            }
        }
};

int main() {

    Graph g;
    g.addEdge(1,2,0,0);
    g.addEdge(1,3,0,0);
    g.addEdge(2,4,0,0);
    g.addEdge(3,5,0,0);
    g.addEdge(5,6,0,0);
    g.addEdge(4,6,0,0);

    g.print();



    return 0;
}