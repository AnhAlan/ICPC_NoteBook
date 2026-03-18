//maxn <= 1000
const int maxn = 1003;
struct Reach {
    /*
        query u -> v = bitset
    */
    int n;
    vector<int> adj[MAXN];
    bitset<MAXN> reach[MAXN];

    Reach(int _n) : n(_n) {}
    void addEdges(int u, int v) {
        adj[u].push_back(v);
        reach[u][v] = 1;
    }

    void buildReach() {
        for (int i = 1; i <= n; i++) {
            reach[i][i] = 1;
            for (int v : adj[i]) reach[i][v] = 1;
        } 
        for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= n; i++) {
                if (reach[i][k]) reach[i] |= reach[k];
            }
        }
    }
    void addEdges(int u, int v) {
        if (reach[u][v]) return;
        bitset<MAXN> add = reach[v];
        add[v] = 1;
        for (int i = 1; i <= n; i++) {
            if (reach[i][u]) reach[i] |= add;
        }
    }

    bool query(int u, int v) {
        return reach[u][v];
    }
};