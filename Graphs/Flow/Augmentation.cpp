struct Augmentation {
    int n;                     
    vector<vector<int>> adj;
    vector<int> matchL, matchR;
    vector<bool> vis;

    Augmentation(int n_){
        int n = _n;
        adj.assign(n + 1, {});
        matchL.assign(n + 1, 0);
        matchR.assign(n + 1, 0);
        vis.assign(n + 1, false);
    }
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }
    bool dfs(int u) {
        for (int v : adj[u]) {
            if (!vis[v]) {
                vis[v] = true;
                if (!matchR[v] || dfs(matchR[v])) {
                    matchL[u] = v;
                    matchR[v] = u;
                    return true;
                }
            }
        }
        return false;
    }

    int Matching() {
        fill(matchL.begin(), matchL.end(), 0);
        fill(matchR.begin(), matchR.end(), 0);
        int res = 0;
        for (int u = 1; u <= n; u++) {
            fill(vis.begin(), vis.end(), false);
            if (dfs(u)) res++;
        }
        return res;
    }
};