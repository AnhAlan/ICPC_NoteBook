template<typename T>
vector<T> ford_bellman(const Digraph<T> &g, int start) {
    T INF = numeric_limits<T>::max() / 2;
    vector<T> dist(g.n + 1, INF);
    dist[start] = 0;
    for (int i = 1; i <= g.n - 1; i++) {
        bool updated = false;
        for (const auto &e : g.edges) {
            if (dist[e.from] != INF && dist[e.to] > dist[e.from] + e.cost) {
                dist[e.to] = dist[e.from] + e.cost;
                updated = true;
            }
        }
        if (!updated) break; 
    }
    for (const auto &e : g.edges) {
        if (dist[e.from] != INF && dist[e.to] > dist[e.from] + e.cost) {
            // cycle
            return {}; 
        }
    }
    return dist;
}