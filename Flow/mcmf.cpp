template<typename T>
struct Mcmf : public Flow<T> {
    using Flow<T>::g; 
    using Flow<T>::edges; 
    using Flow<T>::n; 
    using Flow<T>::st; 
    using Flow<T>::fin; 
    using Flow<T>::EPS;
    vector<T> dist, pot;
    vector<int> parV, parE;
    Mcmf(int _n, int _st, int _fin) : Flow<T>(_n, _st, _fin) {
        dist.assign(n + 1, 0);
        pot.assign(n + 1, 0);
        parV.resize(n + 1);
        parE.resize(n + 1);
    }
    void reset_all() {
        this->reset(); 
        fill(pot.begin(), pot.end(), 0);
    }
    bool dijkstra() {
        fill(dist.begin(), dist.end(), numeric_limits<T>::max() / 2);
        using P = pair<T, int>;
        priority_queue<P, vector<P>, greater<P>> pq;
        dist[st] = 0; pq.push({0, st});
        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d != dist[u]) continue;
            for (int id : g[u]) {
                auto &ed = edges[id];
                if (ed.cap - ed.f > EPS) {
                    T nd = d + ed.cost + pot[u] - pot[ed.to];
                    if (nd < dist[ed.to]) {
                        dist[ed.to] = nd; parV[ed.to] = u; parE[ed.to] = id;
                        pq.push({nd, ed.to});
                    }
                }
            }
        }
        return dist[fin] < numeric_limits<T>::max() / 2;
    }

    pair<T, T> min_cost_max_flow(T need = numeric_limits<T>::max() / 2) {
        this->flow = 0;
        T total_cost = 0;
        while (this->flow < need && dijkstra()) {
            for (int i = 1; i <= n; i++) {
                if (dist[i] < numeric_limits<T>::max() / 2) pot[i] += dist[i];
            }
            T f = need - this->flow;
            for (int v = fin; v != st; v = parV[v]) {
                f = min(f, edges[parE[v]].cap - edges[parE[v]].f);
            }
            for (int v = fin; v != st; v = parV[v]) {
                edges[parE[v]].f += f; 
                edges[parE[v] ^ 1].f -= f;
            }
            this->flow += f;
            total_cost += f * pot[fin];
        }
        if (this->flow < need && need != numeric_limits<T>::max() / 2) return {-1, -1};
        return {this->flow, total_cost};
    }
};