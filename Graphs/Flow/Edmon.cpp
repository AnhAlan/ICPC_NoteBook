#include <bits/stdc++.h>
#define en "\n"
#define DEBUG(x) cerr << #x << " " << x << en
#define all(a) ((a).begin(),(a).end())
using namespace std;

const int INF = (int)1e9; // infinity

// Edge structure
struct edges {
    int v;    // destination vertex
    int cap;  // residual capacity
    int rev;  // index of reverse edge in adj[v]
};

// Edmonds-Karp implementation for Maximum Flow
struct edmondskarp {
    int n, s, t;                     // number of vertices, source, sink
    vector<vector<edges>> adj;       // adjacency list storing edges

    // constructor
    edmondskarp(int _n,int _s,int _t) : n(_n), s(_s), t(_t) {
        adj.assign(n+1,{});          // 1-based indexing
    }

    // add directed edge u → v with capacity cap
    void add(int u,int v,int cap) {
        edges a = {v, cap, (int)adj[v].size()}; // forward edge
        edges b = {u, 0, (int)adj[u].size()};   // reverse edge (capacity 0)
        adj[u].push_back(a);
        adj[v].push_back(b);
    }

    // BFS to find augmenting path
    bool bfs(vector<int>& par, vector<int>& reved) {
        fill(par.begin(), par.end(), -1);
        queue<int> q;
        q.push(s);
        par[s] = s; // source's parent = itself

        while(!q.empty()) {
            int u = q.front(); q.pop();
            for(int i = 0; i < (int)adj[u].size(); i++) {
                edges &e = adj[u][i];
                if(e.cap > 0 && par[e.v] == -1) { // only follow edges with capacity
                    par[e.v] = u;        // store parent
                    reved[e.v] = i;      // store index of edge in adjacency list
                    if(e.v == t) return true; // reached sink
                    q.push(e.v);
                }
            }
        }
        return false; // no augmenting path found
    }

    // main Edmonds-Karp algorithm to calculate max flow
    int maxek() {
        int max_flow = 0;
        vector<int> par(n+1), reved(n+1);

        // while there exists an augmenting path
        while(bfs(par, reved)) {
            int min_flow = INF;

            // find bottleneck (minimum residual capacity) along the path
            for(int v = t; v != s; v = par[v]) {
                int u = par[v];
                edges &e = adj[u][reved[v]];
                min_flow = min(min_flow, e.cap);
            }

            // update residual capacities along the path
            for(int v = t; v != s; v = par[v]) {
                int u = par[v];
                edges &e = adj[u][reved[v]];
                e.cap -= min_flow;                   // reduce forward capacity
                adj[e.v][e.rev].cap += min_flow;     // increase backward capacity
            }

            max_flow += min_flow; // add flow of this augmentation
        }
        return max_flow;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, s, t;
    cin >> n >> m >> s >> t;           // input: vertices, edges, source, sink
    edmondskarp ek(n, s, t);

    for(int i = 0; i < m; i++) {
        int u, v, cap;
        cin >> u >> v >> cap;           // input edges and capacities
        ek.add(u, v, cap);
    }

    cout << ek.maxek() << en;          // output max flow
}
