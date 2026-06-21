template<class T, class C>
struct Mcmf {
    struct Edge {
        int v;
        T cap, flow;
        C cost;
    };
    int n, st, fin;
    vector<Edge> edges;
    vector<vector<int>> g;
    vector<C> dist, pot;
    vector<int> parV, parE;
    Mcmf(int _n, int _st, int _fin) : n(_n), st(_st), fin(_fin) {
        g.assign(n + 1, {});
        dist.assign(n + 1, 0);
        pot.assign(n + 1, 0);
        parV.resize(n + 1);
        parE.resize(n + 1);
    }
    void clear_flow() {
        for(auto &e : edges){
            e.flow = 0;
        }
    }
    void add(int u, int v, T cap, C cost) {
        int id = (int) edges.size();
        g[u].push_back(id);
        edges.push_back({v, cap, 0, cost});
        g[v].push_back(id + 1);
        edges.push_back({u, 0, 0, -cost});
    }
    bool dijkstra() {
        fill(dist.begin(), dist.end(), numeric_limits<C>::max() / 2);
        using P = pair<C,int>;
        priority_queue<P, vector<P>, greater<P>> pq;
        dist[st] = 0;
        pq.push({0, st});
        while (!pq.empty()) {
            auto [d, u] = pq.top(); 
            pq.pop();
            if (d != dist[u]) continue;
            for (int id : g[u]) {
                auto &ed = edges[id];
                if (ed.flow < ed.cap) {
                    C nd = d + ed.cost + pot[u] - pot[ed.v];
                    if (nd < dist[ed.v]) {
                        dist[ed.v] = nd;
                        parV[ed.v] = u;
                        parE[ed.v] = id;
                        pq.push({nd, ed.v});
                    }
                }
            }
        }
        return dist[fin] < numeric_limits<C>::max() / 2;
    }
    pair<T, C> min_cost_max_flow(T need = numeric_limits<T>::max() / 2){
        T flow = 0;
        C cost = 0;
        while (flow < need && dijkstra()) {
            for (int i = 1; i <= n; i++)
            if (dist[i] < numeric_limits<C>::max() / 2){
                pot[i] += dist[i];
            }
            T f = need - flow;
            for (int v = fin; v != st; v = parV[v]) {
            f = min(f, edges[parE[v]].cap - edges[parE[v]].flow);
            }
            for (int v = fin; v != st; v = parV[v]) {
            edges[parE[v]].flow += f;
            edges[parE[v] ^ 1].flow -= f;
            }
            flow += f;
            cost += f * pot[fin];
        }
        if(flow < need){
            return {-1, -1}; // not find
        }
        return {flow, cost};
    }
};