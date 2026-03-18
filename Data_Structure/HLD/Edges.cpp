/*
    build segment
    node u : w -> a[pos[u]] = w;
    edges u v w -> a[parID[v]] = w; node 1 -> pos 0
*/
const int maxn = 1e6;
struct Edges{
    int u, v;
    long long w;
    Edges(){}
    Edges(int _u, int _v, long long _w){
        u = _u, v = _v, w = _w;
    }
    int other(int x){
        return u ^ v ^ x;
    }
};

Edges edges[maxn];
vector<int>adj[maxn];
int par[maxn], parID[maxn];
int high[maxn], heavy[maxn], sz[maxn];
int edges_to_node[maxn]; 

void dfs(int u, int p){
    sz[u] = 1;
    int max_sz = 0;
    for(int id : adj[u]){
        int v = edges[id].other(u);
        if(v != p){
            par[v] = u;
            high[v] = high[u] + 1;
            parID[v] = id;
            dfs(v,u);
            sz[u] += sz[v];
            if(sz[v] > max_sz){
                max_sz = sz[v];
                heavy[u] = v;
            }
            edges_to_node[id] = v;
        }
    }
}
int head[maxn], pos[maxn];
int cnt = 0;
void dfs_comp(int u, int h){
    head[u] = h;
    pos[u] = ++cnt;
    if(heavy[u]){
        dfs_comp(heavy[u], h);
    }
    for(int id : adj[u]){
        int v = edges[id].other(u);
        if(v != par[u] || v == heavy[u]) continue;
        dfs_comp(v, v);
    }
}

//get node u -> node v
long long get_hld_node(int u, int v){
    long long res = 0;
    while(head[u] != head[v]){
        if(high[head[u]] < high[head[v]]) swap(u,v);
        res += get(1, 1, n, pos[head[u]], pos[u]);
        u = par[head[u]];
    }
    if(u == v) return res; 
    if(high[u] > high[v]) swap(u,v);
    res += get(1, 1, n,pos[u], pos[v]); 
    return res;
}

//get node edges u -> edges  v
long long get_hld_edges(int u, int v){
    long long res = 0;
    while(head[u] != head[v]){
        if(high[head[u]] < high[head[v]]) swap(u,v);
        res += get(1, 1, n, pos[head[u]] + 1, pos[u]);
        u = par[head[u]];
    }
    if(u == v) return res; 
    if(high[u] > high[v]) swap(u,v);
    res += get(1, 1, n, pos[u] + 1, pos[v]); 
    return res;
}