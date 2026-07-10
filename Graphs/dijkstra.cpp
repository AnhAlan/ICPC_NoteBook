template<typename T>
vector<T> dijkstra(const Undigraph<T> &g, int start){
    vector<T> dist(g.n + 1, numeric_limits<T>::max() / 2);
    using P = pair<T,int>;
    priority_queue<P, vector<P>,greater<P> > pq;
    dist[start] = 0; 
    pq.push({0, start});
    while(!pq.empty()){
        auto [d, u] = pq.top();
        pq.pop();
        if(d != dist[u]) continue;
        for(int id : g.adj[u]){
            int v = g.edges[id].from ^ g.edges[id].to ^ u;
            if(dist[v] > dist[u] + g.edges[id].cost){
                dist[v] = dist[u] + g.edges[id].cost;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}