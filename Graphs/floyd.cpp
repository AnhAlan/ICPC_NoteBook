template<typename T>
struct Floyd{
    int n;
    T INF;
    vector<vector<T>> dist;
    vector<vector<int>> nxt;
    Floyd(const digraph<T> &g){
        n = g.n;
        INF = numeric_limits<T>::max() / 4;
        dist.assign(n + 1, vector<T>(n + 1, INF));
        nxt.assign(n + 1, vector<int>(n + 1, 0));
        for(int i = 1; i <= n; i++) dist[i][i] = 0;
        for(auto &e : g.edges){
            if(e.cost < dist[e.from][e.to]){
                dist[e.from][e.to] = e.cost;
                nxt[e.from][e.to] = e.to;
            }
        }
    }
    void build(){
        for(int k = 1; k <= n; k++){
            for(int i = 1; i <= n; i++){
                if(dist[i][k] == INF) continue;
                for(int j = 1; j <= n; j++){
                    if(dist[k][j] == INF) continue;
                    if(dist[i][j] > dist[i][k] + dist[k][j]){
                        dist[i][j] = dist[i][k] + dist[k][j];
                        nxt[i][j] = nxt[i][k];
                    }
                }
            }
        }
    }
    T get_dist(int u, int v){
        return dist[u][v];
    }
    vector<int> get_path(int u, int v){
        if(dist[u][v] == INF) return {};
        vector<int> path;
        while(u != v){
            path.push_back(u);
            u = nxt[u][v];
        }
        path.push_back(v);
        return path;
    }
};