template<typename T>
struct Scc {
    int n, timer = 0, sccCnt = 0;
    const digraph<T> &g; 
    vector<vector<int>> dag, scc;
    vector<int> num, low, comp;
    vector<bool> inStack;
    stack<int> st;
    vector<int> topo;
    Scc(const digraph<T> &_g) : g(_g), n(g.n) {
        num.assign(n + 1, 0);
        low.assign(n + 1, 0);
        comp.assign(n + 1, 0);
        inStack.assign(n + 1, false);
        scc.resize(n + 1);
    }
    void dfs(int u) {
        num[u] = low[u] = ++timer;
        st.push(u);
        inStack[u] = true;
        for (int id : g.adj[u]) {
            int v = g.edges[id].from ^ g.edges[id].to ^ u;
            if (!num[v]) {
                dfs(v);
                low[u] = min(low[u], low[v]);
            } else if (inStack[v]) {
                low[u] = min(low[u], num[v]);
            }
        }
        if (low[u] == num[u]) {
            ++sccCnt;
            while (true) {
                int v = st.top();
                st.pop();
                inStack[v] = false;
                comp[v] = sccCnt;
                scc[sccCnt].push_back(v);
                if (v == u) break;
            }
        }
    }
    void build_scc() {
        if (sccCnt > 0) return; 
        for (int i = 1; i <= n; i++) {
            if (!num[i]) dfs(i);
        }
    }
    void build_dag() {
        build_scc(); 
        dag.assign(sccCnt + 1, vector<int>()); 
        for (int u = 1; u <= n; u++) {
            int a = comp[u];
            for (int id : g.adj[u]) {
                int v = g.edges[id].from ^ g.edges[id].to ^ u;
                int b = comp[v];
                if (a != b) { 
                    dag[a].push_back(b);
                }
            }
        }
        for (int u = 1; u <= sccCnt; u++) {
            sort(dag[u].begin(), dag[u].end());
            dag[u].erase(unique(dag[u].begin(), dag[u].end()), dag[u].end());
        }
    }
    void build_topo() {
        build_scc(); 
        topo.clear();
        for (int i = sccCnt; i >= 1; i--) {
            topo.push_back(i);
        }
    }
};