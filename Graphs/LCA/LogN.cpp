#include<bits/stdc++.h>
#define ll long long
using namespace std;

#define log 10          // maximum power of 2 for binary lifting (log2(n) upper bound)
const int maxn = 1000;
vector<int> adj[maxn];  // adjacency list for the tree
int par[maxn][log+1];   // par[u][i] = 2^i-th ancestor of node u
int high[maxn];         // depth (height) of node u from root
int n;                  // number of nodes in tree

// Input tree
void load() {
    cin >> n;
    for(int i = 1; i <= n-1; i++) {
        int u, v;
        cin >> u >> v;      // edge between u and v
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

// DFS to compute depth and immediate parent (par[u][0])
void dfs(int u) {
    for(int v : adj[u]) {
        if(v != par[u][0]) { // avoid going back to parent
            par[v][0] = u;
            high[v] = high[u] + 1;
            dfs(v);
        }
    }
}

// Build sparse table for binary lifting
void build() {
    for(int j = 1; j <= log; j++) {
        for(int i = 1; i <= n; i++) {
            if(par[i][j-1])
                par[i][j] = par[par[i][j-1]][j-1]; // 2^j-th ancestor
        }
    }
}

// Query LCA of nodes u and v
int lca(int u, int v) {
    if(high[v] > high[u]) {
        return lca(v, u); // ensure u is deeper
    }
    // lift u to the same level as v
    for(int i = log; i >= 0; i--) {
        if(high[par[u][i]] >= high[v]) {
            u = par[u][i];
        }
    }
    if(u == v) return u;

    // lift u and v together until their parents match
    for(int i = log; i >= 0; i--) {
        if(par[u][i] != par[v][i]) {
            u = par[u][i];
            v = par[v][i];
        }
    }
    return par[u][0]; // parent of u (or v) is LCA
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    load();          // input tree
    par[1][0] = 0;   // root's parent = 0
    high[0] = -1;    // dummy node depth
    high[1] = 0;     // root depth = 0
    dfs(1);          // compute depth & par[u][0]
    build();         // build binary lifting table

    cout << lca(5, 3); // example query
}
