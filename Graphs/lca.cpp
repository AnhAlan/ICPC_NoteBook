template<typename T>
struct Lca{
    const forest<T> &f;
    int n, LOG;
    vector<vector<int> > par;
    vector<int> high;
    Lca(const forest<T> &_f) : f(_f), n(f.n){
        assert(n > 0);
        LOG = 31 - __builtin_clz(n) + 1;
        par.assign(n + 1, vector<int>(LOG + 1));
        high.assign(n + 1, 0);
    }
    void dfs(int u){
        for(int id : f.adj[u]){
            int v = f.edges[id].from ^ f.edges[id].to ^ u;
            if(v == par[u][0]) continue;
            par[v][0] = u;
            high[v] = high[u] + 1;
            dfs(v);
        }
    }
    void build_lca(int root = 1){
        high[0] = -1;
        high[root] = 0;
        par[root][0] = 0;
        dfs(root    );
        for(int j = 1; j <= LOG; j++){
            for(int i = 1; i <= n; i++){
                if(par[i][j - 1] != 0) par[i][j] = par[par[i][j - 1]][j - 1];
                else par[i][j] = 0;
            }
        }
    }
    int lca(int u, int v){
        if(high[u] < high[v]) swap(u, v);
        for(int i = LOG; i >= 0; i--){
            if(par[u][i] != 0 && high[par[u][i]] >= high[v]){
                u = par[u][i];
            }
        }
        if(u == v) return u;
        for(int i = LOG; i >= 0; i--){
            if(par[u][i] != par[v][i]){
                u = par[u][i];
                v = par[v][i];
            }
        }
        return par[u][0];
    }
};