struct Topo {
    const vector<vector<int>> &dag;
    int n;
    vector<bool> vis;
    vector<int> topo;
    Topo(const vector<vector<int>> &_dag) : dag(_dag), n((int)_dag.size() - 1) {
        vis.assign(n + 1, false);
    }
    void dfs_topo(int u) {
        vis[u] = true;
        for(int v : dag[u]) {
            if(!vis[v]) {
                dfs_topo(v);
            }
        }
        topo.push_back(u);
    }
    vector<int> build_topo() {
        topo.clear();
        fill(vis.begin(), vis.end(), false);
        for(int i = 1; i <= n; i++) {
            if(!vis[i]) {
                dfs_topo(i);
            }
        }
        reverse(topo.begin(), topo.end());
        return topo;
    }
};