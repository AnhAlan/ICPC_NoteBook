template<typename T>
struct Lca{
    const forest<T> &f;
    int n, cnt, LOG;
    vector<int> high, in, out, node;
    vector<vector<int> > minH;
    Lca(const forest<T> &_f) : f(_f), n(f.n){
        assert(n > 0);
        LOG = 31 - __builtin_clz(2 * n + 5) + 1;
        cnt = 0;
        high.resize(n + 1);
        node.resize(2 * n + 5);
        in.resize(n + 1);
        out.resize(n + 1);
        minH.assign(2 * n + 5, vector<int> (LOG + 1));
    }
    void dfs(int u, int p){
        node[++cnt] = u;
        in[u] = cnt;
        for(int id : f.adj[u]){
            int v = f.edges[id].from ^ f.edges[id].to ^ u;
            if(v == p) continue;
            high[v] = high[u] + 1;
            dfs(v, u);
            node[++cnt] = u;
        }
        out[u] = cnt;
    }
    int minHigh(int u, int v){
        return high[u] < high[v] ? u : v;
    }
    void build_lca(int root = 1){
        high[0] = -1;
        high[root] = 0; 
        dfs(root, -1);
        for(int i = 1; i <= cnt; i++) minH[i][0] = node[i];
        for(int j = 1; j <= LOG; j++){
            for(int i = 1; i <= cnt - (1 << j) + 1; i++){
                minH[i][j] = minHigh(minH[i][j - 1], minH[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    int lca(int u, int v){
        int pu = in[u]; 
        int pv = in[v];
        if(pu > pv) swap(pu, pv);
        int k = 31 - __builtin_clz(pv - pu + 1);
        return minHigh(minH[pu][k], minH[pv - (1 << k) + 1][k]);
    }
};