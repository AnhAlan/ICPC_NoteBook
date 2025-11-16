#include<bits/stdc++.h>
#define ll long long
#define all(a) a.begin(),a.end()
#define en "\n"
#define bit(mask,i) (((mask)>>(i))&1)
#define MASK(x) (1 << (x))
#define DEBUG(x) cerr << #x << ": " << x << en
#define fi first
#define se second
using namespace std;

const int maxn = 1e3;
int n,m;
vector<int> adj[maxn]; // adjacency list for tree

// Load tree input
void load(){
    cin >> n >> m; // n = #nodes, m = #edges
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

// Euler tour arrays
int nodes[2*maxn];   // store nodes during Euler tour
int pos[maxn];       // first occurrence of node in Euler tour
int fin[maxn];       // last occurrence of node in Euler tour
int cnt = 0;
int high[maxn];      // depth of nodes

// DFS to perform Euler tour and record depth
void dfs(int u,int par){
    nodes[++cnt] = u;
    pos[u] = cnt;     // first occurrence
    for(int v : adj[u]){
        if(v != par){
            high[v] = high[u] + 1;
            dfs(v,u);
            nodes[++cnt] = u; // add parent again after visiting child
        }
    }
    fin[u] = cnt;      // last occurrence
}

// Compare two nodes by depth, return the shallower one
int MinHigh(int u,int v){
    return high[u] < high[v] ? u : v;
}

#define LOG 10
int minH[2*maxn][maxn]; // Sparse table for RMQ (range min query on depth)

// Build Sparse Table for RMQ over Euler tour
void build(){
    for(int i=1;i<=cnt;i++){
        minH[i][0] = nodes[i];
    }

    for(int j=1;j<LOG;j++){
        for(int i=1;i<= cnt - MASK(j)+1;i++){
            minH[i][j] = MinHigh(minH[i][j-1],minH[i + MASK(j-1)][j-1]);
        }
    }
}

// Query LCA using RMQ over Euler tour
int lca(int u,int v){
    int pu = pos[u];
    int pv = pos[v];
    if(pu > pv){
        swap(pu,pv);
    }
    int k = 31 - __builtin_clz(pv-pu+1); // floor(log2(length))
    return MinHigh(minH[pu][k],minH[pv-MASK(k)+1][k]);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    load();           // read tree input
    high[1] = 0;      // root depth = 0
    dfs(1,-1);        // perform Euler tour
    build();          // build Sparse Table for RMQ

    // interactive queries for LCA
    while(true){
        int l,r;
        cin >> l >> r;
        cout << lca(l,r) << en;
        cout.flush();
    }
}
