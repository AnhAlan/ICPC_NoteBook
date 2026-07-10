template<typename T>
struct Hungarian : public Flow<T> {
    using Flow<T>::g; 
    using Flow<T>::edges; 
    using Flow<T>::n; 
    using Flow<T>::st; 
    using Flow<T>::fin; 
    using Flow<T>::EPS;

    Hungarian(int _n, int _st, int _fin) : Flow<T>(_n, _st, _fin) {}
    pair<T, T> min_cost_max_flow() {
        this->flow = 0;
        T total_cost = 0;
        vector<T> dist(n + 1); 
        vector<int> pe(n + 1); 
        while (true) {
            fill(dist.begin(), dist.end(), numeric_limits<T>::max() / 2);
            dist[st] = 0; 
            vector<bool> inq(n + 1, false); 
            queue<int> q;
            q.push(st); inq[st] = true;
            while (!q.empty()) {
                int u = q.front(); q.pop(); inq[u] = false;
                for (int id : g[u]) {
                    auto &e = edges[id];
                    if (e.cap - e.f > EPS && dist[u] + e.cost < dist[e.to]) {
                        dist[e.to] = dist[u] + e.cost;
                        pe[e.to] = id;
                        if (!inq[e.to]) { inq[e.to] = true; q.push(e.to); }
                    }
                }
            }
            if (dist[fin] >= numeric_limits<T>::max() / 4) break;
            T push = numeric_limits<T>::max();
            for (int v = fin; v != st; ) {
                int id = pe[v];
                push = min(push, edges[id].cap - edges[id].f);
                v = edges[id].from;
            } 
            for (int v = fin; v != st; ) {
                int id = pe[v];
                edges[id].f += push;
                edges[id ^ 1].f -= push; 
                v = edges[id].from;
            }
            this->flow += push; 
            total_cost += push * dist[fin];
        }
        return {this->flow, total_cost};
    }
};
