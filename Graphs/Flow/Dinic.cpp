#include <bits/stdc++.h>
#define ll long long
using namespace std;

struct Edge {
    int to, rev;
    long long cap;
};

struct Dinic {
    int n;
    vector<vector<Edge>> adj;
    vector<int> level, ptr;

    Dinic(int _n) : n(_n) {
        adj.assign(n + 1, {});
        level.assign(n + 1, 0);
        ptr.assign(n + 1, 0);
    }

    //a - > edges from u - > v with capacity cap
    //b -> reverse edges from v -> u with capacity 0
    void add(int u, int v, ll cap) {
        Edge a = {v, (int)adj[v].size(), cap}; // to, rev, cap
        Edge b = {u, (int)adj[u].size(), 0};   // reverse edge
        adj[u].push_back(a);
        adj[v].push_back(b);
    }


    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        q.push(s);
        level[s] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto &e : adj[u]) {
                if (e.cap > 0 && level[e.to] == -1) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] != -1;
    }

    long long dfs(int u, int t, long long pushed) {
        if (!pushed) return 0;
        if (u == t) return pushed;
        for (int &i = ptr[u]; i < (int)adj[u].size(); i++) {
            Edge &e = adj[u][i];
            if (level[e.to] != level[u] + 1 || e.cap <= 0) continue;
            long long tr = dfs(e.to, t, min(pushed, e.cap));
            if (tr == 0) continue;
            e.cap -= tr;
            adj[e.to][e.rev].cap += tr;
            return tr;
        }
        return 0;
    }

    long long maxFlow(int s, int t) {
        long long flow = 0;
        while (bfs(s, t)) {
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, t, 1e18)) {
                flow += pushed;
            }
        }
        return flow;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    //Soure -> Sink
    Dinic d(7); // Sink = 7
    cout << d.maxFlow(1,7); // maxFlow From 1 -> 7
    
}
