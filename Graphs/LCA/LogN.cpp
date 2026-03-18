
//2^log >= maxn
const int LOG = 20;          
const int maxn = 1e6 + 5;
int par[maxn][LOG   +1];   
int high[maxn];         
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
    for(int j = 1; j <= LOG; j++) {
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

