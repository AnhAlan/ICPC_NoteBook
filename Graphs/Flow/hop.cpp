struct Hopcrof{
    int n, m; 
    vector<vector<int>> adj; 
    vector<int> pairU, pairV, dist;

    Hopcrof(int _n, int _m) : n(_n), m(_m) {
        adj.assign(n + 1, {});
        pairU.assign(n + 1, 0);
        pairV.assign(m + 1, 0);
        dist.assign(n + 1, 0);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v); 
    }

    bool bfs() {
        queue<int> q;

        for (int u = 1; u <= n; u++) {
            if (pairU[u] == 0) {
                dist[u] = 0;
                q.push(u);
            } else {
                dist[u] = INT_MAX;
            }
        }
        dist[0] = INT_MAX;

        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (dist[u] < dist[0]) {
                for (int v : adj[u]) {
                    int nxt = pairV[v];
                    if (dist[nxt] == INT_MAX) {
                        dist[nxt] = dist[u] + 1;
                        q.push(nxt);
                    }
                }
            }
        }
        return dist[0] != INT_MAX;
    }

    bool dfs(int u) {
        if (u == 0) return true;
        for (int v : adj[u]) {
            int nxt = pairV[v];
            if (dist[nxt] == dist[u] + 1 && dfs(nxt)) {
                pairU[u] = v;
                pairV[v] = u;
                return true;
            }
        }
        dist[u] = INT_MAX;
        return false;
    }
    int maxMatching() {
        fill(pairU.begin(), pairU.end(), 0);
        fill(pairV.begin(), pairV.end(), 0);
        int matching = 0;
        while (bfs()) {
            for (int u = 1; u <= n; u++) {
                if (pairU[u] == 0 && dfs(u))
                    matching++;
            }
        }
        return matching;
    }
};