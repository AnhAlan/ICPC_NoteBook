template<typename T, typename F = Merge<T> >
struct Lca {
    const Forest<T> &f;
    int n, LOG;
    F merge;
    vector<vector<int> > par;
    vector<vector<T> > lca_edges;
    vector<int> high;
    vector<bool> vis;

    Lca(const Forest<T> &_f) : f(_f), n(f.n) {
        assert(n > 0);
        LOG = 31 - __builtin_clz(n);
        par.assign(n + 1, vector<int>(LOG + 1, 0));
        lca_edges.assign(n + 1, vector<T>(LOG + 1, merge.none()));
        high.assign(n + 1, 0);
        vis.assign(n + 1, false);
    }

    void dfs(int u) {
        vis[u] = true;
        for(int id : f.adj[u]) {
            int v = f.edges[id].from ^ f.edges[id].to ^ u;
            if(v == par[u][0]) continue;
            lca_edges[v][0] = f.edges[id].cost; 
            par[v][0] = u;
            high[v] = high[u] + 1;
            dfs(v);
        }
    }

    void build() {
        high[0] = -1;
        for (int i = 1; i <= n; i++) {
            if(!vis[i]) {
                high[i] = 0;
                par[i][0] = 0;
                lca_edges[i][0] = merge.none();
                dfs(i);
            }
        }
        for(int j = 1; j <= LOG; j++) {
            for(int i = 1; i <= n; i++) {
                if(par[i][j - 1] != 0) {
                    int p = par[i][j - 1];
                    par[i][j] = par[p][j - 1];
                    lca_edges[i][j] = merge(lca_edges[i][j - 1], lca_edges[p][j - 1]);
                } else {
                    par[i][j] = 0;
                    lca_edges[i][j] = merge.none();
                }
            }
        }
    }

    int lca(int u, int v) {
        if(high[u] < high[v]) swap(u, v);
        for(int i = LOG; i >= 0; i--) {
            if(par[u][i] != 0 && high[par[u][i]] >= high[v]) {
                u = par[u][i];
            }
        }
        if(u == v) return u;
        for(int i = LOG; i >= 0; i--) {
            if(par[u][i] != par[v][i]) {
                u = par[u][i];
                v = par[v][i];
            }
        }
        return par[u][0];
    }
    T get_path(int u, int v) {
        T res = merge.none();
        if(high[u] < high[v]) swap(u, v);
        for(int i = LOG; i >= 0; i--) {
            if(par[u][i] != 0 && high[par[u][i]] >= high[v]) {
                res = merge(res, lca_edges[u][i]);
                u = par[u][i];
            }
        }
        if(u == v) return res;
        for(int i = LOG; i >= 0; i--) {
            if(par[u][i] != par[v][i]) {
                res = merge(res, lca_edges[u][i]);
                res = merge(res, lca_edges[v][i]);
                u = par[u][i];
                v = par[v][i];
            }
        }
        res = merge(res, lca_edges[u][0]);
        res = merge(res, lca_edges[v][0]);
        return res;
    }
};