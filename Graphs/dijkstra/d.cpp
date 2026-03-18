const int MAXN = 1e5;
const long long INF  = 1e18;;
void dijstraka(int s){
    vector<long long> d(n+1, INF);
    d[s] = 0;
    priority_queue<pair<long long,int>,vector<pair<long long,int>>,greater<pair<long long,int>>> Q;
    Q.push({0,s});
    while(!Q.empty()){
        pair<long long,int> top = Q.top();
        Q.pop();
        int u = top.second;
        long long w = top.first;
        if(w > d[u]){
            continue;
        }
        for(auto it : adj[u]){
            int v = it.first;
            long long new_dist = it.second;
            if(d[v] > d[u] + new_dist){
                d[v] = d[u] + new_dist;
                Q.push({d[v],v});
            }
        }
    }
}
