const int maxn = 505;
const int INF = 1e9;
int n, m;
int dist[maxn][maxn], r[maxn][maxn]; 
// u v w : dst[u][v] = w
void build_floyd(){
    for (int i = 1; i <= n; ++i){
        for (int j = 1; j <= n; ++j){
            dist[i][j] = (i == j ? 0 : INF);
        }
    }
     for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (dist[i][k] < INF && dist[k][j] < INF && dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    r[i][j] = k;   
                }
            }
        }
    }        
}
void route(int u, int v) {
    if (r[u][v] == 0) {
        cout << v << " ";
    } 
    else {
        route(u, r[u][v]);
        route(r[u][v], v);
    }
}


