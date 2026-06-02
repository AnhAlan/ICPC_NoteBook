/*
    256MB -> maxn = 40000
    512MB -> maxn = 57000
*/
static const int MAXN = 1003;
struct Reach {
    int n;
    vector<int> adj[MAXN];
    bitset<MAXN> reach[MAXN];
    Reach(int _n): n(_n) {}
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }
    void build() {
        for(int i = 1; i <= n; i++) {
            reach[i][i] = 1;
            for(int v : adj[i]) {
                reach[i][v] = 1;
            }
        }
        for(int k = 1; k <= n; k++) {
            for(int i = 1; i <= n; i++) {
                if(reach[i][k]) {
                    reach[i] |= reach[k];
                }
            }
        }
    }
    void addEdgeOnline(int u, int v) {
        if(reach[u][v]) return;
        reach[u][v] = 1;
        bitset<MAXN> add = reach[v];
        add[v] = 1;
        for(int i = 1; i <= n; i++) {
            if(reach[i][u]) {
                reach[i] |= add;
            }
        }
    }
    bool query(int u, int v) {
        return reach[u][v];
    }
};