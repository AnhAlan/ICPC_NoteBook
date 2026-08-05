template<typename T>
struct Hld {
    const Forest<T> &f;
    const SegTree &st;
    int n;
    vector<int> par, high;
    vector<int> heavy, head, pos;
    vector<int> sz;
    vector<int> edge_to_node;
    vector<int> par_id;
    int curPos;
    Hld(const Forest<T> &_f) : f(_f), n(_f.n) {
        st = SegTree(n);
        par.assign(n + 1, 0);
        high.assign(n + 1, 0);
        heavy.assign(n + 1, 0);
        head.assign(n + 1, 0);
        pos.assign(n + 1, 0);
        sz.assign(n + 1, 0);
        par_id.assign(n + 1, 0);
        edge_to_node.assign(n + 5, 0);
        curPos = 0;
    }
    void dfs(int u, int p) {
        sz[u] = 1;
        par[u] = p;
        heavy[u] = 0;
        int maxSz = 0;
        for (int id : f.adj[u]) {
            int v = f.edges[id].from ^ f.edges[id].to ^ u;
            if (v == p) continue;
            high[v] = high[u] + 1;
            par_id[v] = id;
            dfs(v, u);
            sz[u] += sz[v];
            if (sz[v] > maxSz) {
                maxSz = sz[v];
                heavy[u] = v;
            }
            edge_to_node[id] = v;
        }
    }
    void dfs_hld(int u, int h) {
        head[u] = h;
        pos[u] = ++curPos;
        if (heavy[u]) {
            dfs_hld(heavy[u], h);
        }
        for (int id : f.adj[u]) {
            int v = f.edges[id].from ^ f.edges[id].to ^ u;
            if (v == par[u] || v == heavy[u]) continue;
            dfs_hld(v, v);
        }
    }
    void build(int root = 1) {
        high[root] = 0;
        dfs(root, 0);
        dfs_hld(root, root);
    }
    void build_node(const vector<T> &a) {
        vector<int> v(n + 1);
        assert((int) a.size() - 1 == n);
        for (int i = 1; i <= n; i++) {
            v[pos[i]] = a[i];
        }
        st.build(1, 1, n, v);
    }
    void build_edges() {
        vector<T> v(n + 1);
        for (int i = 2; i <= n; i++) {
            int id = par_id[i];
            T w = f.edges[id].cost;
            v[pos[i]] = w;
        }
        st.build(1, 1, n, v);
    }
    T get_node(int u, int v) {
        T res = 0;
        while (head[u] != head[v]) {
            if (high[head[u]] < high[head[v]]) swap(u, v);
            res += st.get_range(1, 1, n, pos[head[u]], pos[u]);
            u = par[head[u]];
        }
        if (high[u] > high[v]) swap(u, v);
        res += st.get_range(1, 1, n, pos[u], pos[v]);
        return res;
    }
    T get_edges(int u, int v) {
        T res = 0;
        while (head[u] != head[v]) {
            if (high[head[u]] < high[head[v]]) swap(u, v);
            res += st.get_range(1, 1, n, pos[head[u]], pos[u]);
            u = par[head[u]];
        }
        if (u == v) return res;
        if (high[u] > high[v]) swap(u, v);
        res += st.get_range(1, 1, n, pos[u] + 1, pos[v]);
        return res;
    }
    void update_node_range(int u, int v, T w) {
        while (head[u] != head[v]) {
            if (high[head[u]] < high[head[v]]) swap(u, v);
            st.update_range(1, 1, n, pos[head[u]], pos[u], w);
            u = par[head[u]];
        }
        if (high[u] > high[v]) swap(u, v);
        st.update_range(1, 1, n, pos[u], pos[v], w);
    }
    void update_edges_range(int u, int v, T w) {
        while (head[u] != head[v]) {
            if (high[head[u]] < high[head[v]]) swap(u, v);
            st.update_range(1, 1, n, pos[head[u]], pos[u], w);
            u = par[head[u]];
        }
        if (u == v) return;
        if (high[u] > high[v]) swap(u, v);
        st.update_range(1, 1, n, pos[u] + 1, pos[v], w);
    }
};