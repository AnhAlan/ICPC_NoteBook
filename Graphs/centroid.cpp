
int sz[maxn];
bool used[maxn];
void dfs_sz(int u, int p){
    sz[u] = 1;
    for(int v : adj[u]){
        if(v != p && !used[v]){
            dfs_sz(v, u);
            sz[u] += sz[v];
        }
    }
}

int dfs_centroid(int u, int p, int total){
    for(int v : adj[u]){
        if(v != p && !used[v]){
            if(sz[v] > total / 2){
                return dfs_centroid(v, u, total);
            }
        }
    }
    return u;
}

void dfs_path(int u, int p, int c, int d){
    path[u].push_back({c, d});
    for(int v : adj[u]){
        if(v != p && !used[v]){
            dfs_path(v, u, c, d + 1);
        }
    }
}

void build(int u, int p){
    dfs_sz(u, -1);
    int c = dfs_centroid(u, -1, sz[u]);
    used[c] = true;
    dfs_path(c, -1, c, 0);
    for(int v : adj[c]){
        if(!used[v]){
            build(v, c);
        }
    }
}
void update(int u){
    for(auto &[c, d] : path[u]){
        bestPath[c] = min(bestPath[c], d);
    }
}
int get(int u){
    int res = (int)1e9;
    for(auto &[c, d] : path[u]){
        res = min(res, bestPath[c] + d);
    }
    return res;
}
