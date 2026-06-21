template<int MAXS>
struct ReachSCC {
    const Scc<int> &s;
    int n;
    bitset<MAXS> reach[MAXS];
    vector<int> rev[MAXS];
    vector<int> topo;
    ReachSCC(const Scc<int> &_s) : s(_s) {
        n = s.sccCnt;
        for (int i = 1; i <= n; i++) {
            reach[i].reset();
            reach[i][i] = 1;
        }
        for (int u = 1; u <= n; u++) {
            for (int v : s.dag[u]) {
                rev[v].push_back(u);
            }
        }
        vector<int> indeg(n + 1, 0);
        for (int u = 1; u <= n; u++) {
            for (int v : s.dag[u]) {
                indeg[v]++;
            }
        }
        queue<int> q;
        for (int i = 1; i <= n; i++)
            if (!indeg[i]) q.push(i);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            topo.push_back(u);
            for (int v : s.dag[u]) {
                if (--indeg[v] == 0)
                    q.push(v);
            }
        }
        for (int i = n - 1; i >= 0; i--) {
            int u = topo[i];
            for (int v : s.dag[u]) {
                reach[u] |= reach[v];
            }
        }
    }

    void add_edge(int u, int v) {
        int a = s.comp[u];
        int b = s.comp[v];
        if (reach[a][b]) return;
        reach[a][b] = 1;
        bitset<MAXS> add = reach[b];
        add[b] = 1;
        queue<int> q;
        q.push(a);
        while (!q.empty()) {
            int x = q.front(); q.pop();
            if ((reach[x] | add) == reach[x]) continue;
            reach[x] |= add;
            for (int p : rev[x]) {
                q.push(p);
            }
        }
    }
    bool query(int u, int v) {
        return reach[s.comp[u]][s.comp[v]];
    }
};