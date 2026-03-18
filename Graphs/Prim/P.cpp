
struct Edges {
    int u, v, w;
    Edges() {}
    Edges(int _x, int _y, int _w) : u(_x), v(_y), w(_w) {}
};

int n, m;
const int maxn = 100005;
vector<pair<int,int>> adj[maxn];
bool used[maxn];
int parent[maxn];
int d[maxn];

void prim(int from){
    for(int i = 1; i <= n; i++){
        d[i] = INT_MAX;
        used[i] = false;
    }

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> Q;
    vector<Edges> MST;
    long long res = 0;

    d[from] = 0;
    parent[from] = -1;
    Q.push({0, from});

    while(!Q.empty()){
        auto top = Q.top(); Q.pop();
        int u = top.second;
        int w = top.first;

        if(used[u]) continue;

        used[u] = true;
        res += w;

        if(parent[u] != -1){
            MST.push_back(Edges(u, parent[u], w));
        }
        for(auto it : adj[u]){
            int v = it.first;
            int new_w = it.second;
            if(!used[v] && new_w < d[v]){
                d[v] = new_w;
                parent[v] = u;
                Q.push({new_w, v});
            }
        }
    }

    cout << res << endl;
}