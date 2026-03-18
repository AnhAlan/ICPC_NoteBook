const long long INF = 1e18; 
struct Edge {
    int v;
    long long cap;
    int rev;
};

struct Edmon {
    int n, s, t;
    std::vector<std::vector<Edge>> adj;

    Edmon(int _n, int _s, int _t) : n(_n), s(_s), t(_t) {
        adj.assign(n+1, {});
    }

    void add(int u, int v, long long cap) {
        Edge a = {v, cap, (int)adj[v].size()};
        Edge b = {u, 0, (int)adj[u].size()};
        adj[u].push_back(a);
        adj[v].push_back(b);
    }

    bool bfs(std::vector<int>& par, std::vector<int>& reved) {
        fill(par.begin(), par.end(), -1);
        std::queue<int> q;
        q.push(s);
        par[s] = s;

        while(!q.empty()) {
            int u = q.front(); q.pop();
            for(int i = 0; i < (int)adj[u].size(); i++) {
                Edge &e = adj[u][i];
                if(e.cap > 0 && par[e.v] == -1) {
                    par[e.v] = u;
                    reved[e.v] = i;
                    if(e.v == t) return true;
                    q.push(e.v);
                }
            }
        }
        return false;
    }

    long long maxFlow() {
        long long max_flow = 0;
        std::vector<int> par(n+1), reved(n+1);
        while(bfs(par, reved)) {
            long long min_flow = INF;
            for(int v = t; v != s; v = par[v]) {
                int u = par[v];
                Edge &e = adj[u][reved[v]];
                min_flow = std::min(min_flow, e.cap);
            }
            for(int v = t; v != s; v = par[v]) {
                int u = par[v];
                Edge &e = adj[u][reved[v]];
                e.cap -= min_flow;
                adj[e.v][e.rev].cap += min_flow;
            }
            max_flow += min_flow;
        }
        return max_flow;
    }
};