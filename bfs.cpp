#include <bits/stdc++.h>
using namespace std;

class Graph {
    int n;
    vector<vector<int>> adj;
public:
    Graph(int n) : n(n), adj(n) {}
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    // BFS from source s
    vector<int> bfs(int s) {
        vector<int> order;
        vector<bool> vis(n, false);
        queue<int> q;
        vis[s] = true;
        q.push(s);
        while(!q.empty()) {
            int u = q.front(); q.pop();
            order.push_back(u);
            for(int w : adj[u]) {
                if(!vis[w]) {
                    vis[w] = true;
                    q.push(w);
                }
            }
        }
        return order;
    }
};
