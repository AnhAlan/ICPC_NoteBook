#include<bits/stdc++.h>
#define ll long long
using namespace std;

#define log 10          
const int maxn = 1000;
vector<int> adj[maxn];  
int par[maxn][log+1];   
int high[maxn];         
int n;                  


void load() {
    cin >> n;
    for(int i = 1; i <= n-1; i++) {
        int u, v;
        cin >> u >> v;      
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}


void dfs(int u) {
    for(int v : adj[u]) {
        if(v != par[u][0]) { 
            par[v][0] = u;
            high[v] = high[u] + 1;
            dfs(v);
        }
    }
}


void build_lca() {
    for(int j = 1; j <= log; j++) {
        for(int i = 1; i <= n; i++) {
            if(par[i][j-1])
                par[i][j] = par[par[i][j-1]][j-1]; 
        }
    }
}


int lca(int u, int v) {
    if(high[v] > high[u]) {
        return lca(v, u); 
    }
    for(int i = log; i >= 0; i--) {
        if(high[par[u][i]] >= high[v]) {
            u = par[u][i];
        }
    }
    if(u == v) return u;
    for(int i = log; i >= 0; i--) {
        if(par[u][i] != par[v][i]) {
            u = par[u][i];
            v = par[v][i];
        }
    }
    return par[u][0]; 
}

