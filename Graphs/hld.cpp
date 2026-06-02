struct Hld {
    struct Edges {
        int u, v;
        long long w;
        Edges() {}
        Edges(int _u, int _v, long long _w) : u(_u), v(_v), w(_w) {}
        int other(int x) {
            return u ^ v ^ x;
        }
    };
    int n;
    SegTree st;
    vector<Edges> edges;
    vector<vector<int>> adj;
    vector<int> par, high;
    vector<int> heavy, head, pos;
    vector<int> sz;
    vector<int> edge_to_node;
    vector<int> parId;
    int curPos;
    Hld(int n) : n(n) {
        st = SegTree(n);
        adj.assign(n + 1, {});
        edges.reserve(n + 5);
        par.assign(n + 1, 0);
        high.assign(n + 1, 0);
        heavy.assign(n + 1, 0);
        head.assign(n + 1, 0);
        pos.assign(n + 1, 0);
        sz.assign(n + 1, 0);
        parId.assign(n + 1, 0);
        edge_to_node.assign(n + 5, 0); // not use
        curPos = 0;
    }
    void add_edges(int u, int v, long long w) {
        edges.emplace_back(u, v, w);
        int id = (int)edges.size() - 1;
        adj[u].push_back(id);
        adj[v].push_back(id);
    }
    void dfs(int u, int p) {
        sz[u] = 1;
        par[u] = p;
        heavy[u] = 0;
        int maxSz = 0;
        for (int id : adj[u]) {
            auto &e = edges[id];
            int v = e.other(u);
            if (v == p) continue;
            high[v] = high[u] + 1;
            parId[v] = id;
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
        for (int id : adj[u]) {
            int v = edges[id].other(u);
            if (v == par[u] || v == heavy[u]) continue;
            dfs_hld(v, v);
        }
    }
    void build_hld(int root) {
        high[root] = 0;
        dfs(root, 0);
        dfs_hld(root, root);
    }
    void build_node(vector<int> &a) {
        vector<int> v(n + 1);
        assert(a.size() - 1 == n);
        for (int i = 1; i <= n; i++) {
            v[pos[i]] = a[i];
        }
        st.build(1, 1, n, v);
    }
    void build_edges() {
        vector<int> v(n + 1);
        for (int i = 2; i <= n; i++) {
            int id = parId[i];
            long long w = edges[id].w;
            v[pos[i]] = w;
        }
        st.build(1, 1, n, v);
    }
    long long get_node(int u, int v) {
        long long res = 0;
        while (head[u] != head[v]) {
            if (high[head[u]] < high[head[v]]) swap(u, v);
            res += st.get_range(1, 1, n, pos[head[u]], pos[u]);
            u = par[head[u]];
        }
        if (u == v) return res;
        if (high[u] > high[v]) swap(u, v);
        res += st.get_range(1, 1, n, pos[u], pos[v]);
        return res;
    }
    long long get_edges(int u, int v) {
        long long res = 0;
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
    void update_node_range(int u, int v, long long w) {
        while (head[u] != head[v]) {
            if (high[head[u]] < high[head[v]]) swap(u, v);
            st.update_range(1, 1, n, pos[head[u]], pos[u], w);
            u = par[head[u]];
        }
        if (high[u] > high[v]) swap(u, v);
        st.update_range(1, 1, n, pos[u], pos[v], w);
    }
    void update_edges_range(int u, int v, long long w) {
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