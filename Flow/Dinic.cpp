template<typename T>
struct Dinic : public Flow<T> {
    using Flow<T>::g; 
    using Flow<T>::edges; 
    using Flow<T>::n; 
    using Flow<T>::st; 
    using Flow<T>::fin; 
    using Flow<T>::EPS;
    vector<int> level, ptr;
    Dinic(int _n, int _st, int _fin) : Flow<T>(_n, _st, _fin) {
        level.resize(_n + 1);
        ptr.resize(_n + 1);
    }
    bool bfs() {
        fill(level.begin(), level.end(), -1);
        queue<int> q; q.push(st); level[st] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int id : g[u]) {
                auto &e = edges[id];
                if (level[e.to] == -1 && e.cap - e.f > EPS) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[fin] != -1;
    }

    T dfs(int u, T pushed) {
        if (pushed <= EPS) return 0;
        if (u == fin) return pushed;
        for (int &i = ptr[u]; i < (int)g[u].size(); i++) {
            int id = g[u][i]; auto &e = edges[id];
            if (level[e.to] != level[u] + 1) continue;
            T rem = e.cap - e.f;
            if (rem <= EPS) continue;
            T tr = dfs(e.to, min(pushed, rem));
            if (tr <= EPS) continue;
            e.f += tr; edges[id ^ 1].f -= tr;
            return tr;
        }
        return 0;
    }
    T max_flow() {
        this->flow = 0;
        while (bfs()) {
            fill(ptr.begin(), ptr.end(), 0);
            while (true) {
                T pushed = dfs(st, numeric_limits<T>::max() / 2);
                if (pushed <= EPS) break;
                this->flow += pushed;
            }
        }
        return this->flow;
    }
    vector<int> min_cut_side() {
        vector<int> vis(n + 1, false);
        queue<int> q;
        q.push(st);
        vis[st] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int id : g[u]) {
                auto &e = edges[id];
                if (!vis[e.to] && e.cap - e.f > EPS) {
                    vis[e.to] = true;
                    q.push(e.to);
                }
            }
        }
        return vis;
    }
    vector<pair<int,int>> get_min_cut_edges() {
        vector<int> vis = min_cut_side();
        vector<pair<int,int>> cut;
        for (int i = 0; i < (int)edges.size(); i += 2) {
            auto &e = edges[i];
            if (vis[e.from] && !vis[e.to] && e.cap > EPS)
                cut.push_back({e.from, e.to});
        }
        return cut;
    }
};
