#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005; // number of vertices on left side (U)
const int MAXM = 1005; // number of vertices on right side (V)
const int INF = 1e9;

int n, m;                    // number of vertices in U and V
vector<int> adj[MAXN];       // adjacency list from U → V
int pairU[MAXN], pairV[MAXM]; // current matching pairs
int dist[MAXN];              // distance array for BFS

// BFS to build layers and check if there is an augmenting path
bool bfs() {
    queue<int> q;

    // Initialize distances
    for (int u = 1; u <= n; u++) {
        if (pairU[u] == 0) { // free vertex in U
            dist[u] = 0;
            q.push(u);
        } else {
            dist[u] = INF;
        }
    }
    dist[0] = INF; // "dummy node" representing free vertices on V

    while (!q.empty()) {
        int u = q.front(); q.pop();

        if (dist[u] < dist[0]) { // only expand if there is hope to find augmenting path
            for (int v : adj[u]) {
                int nxt = pairV[v]; // U vertex currently matched with v (0 if free)
                if (dist[nxt] == INF) {
                    dist[nxt] = dist[u] + 1;
                    q.push(nxt);
                }
            }
        }
    }

    // if dist[0] != INF, there is at least one augmenting path
    return dist[0] != INF;
}

// DFS to find and augment paths from free vertices in U
bool dfs(int u) {
    if (u == 0) return true; // reached dummy node = end of augmenting path

    for (int v : adj[u]) {
        int nxt = pairV[v];
        if (dist[nxt] == dist[u] + 1 && dfs(nxt)) {
            pairU[u] = v;
            pairV[v] = u;
            return true;
        }
    }

    dist[u] = INF; // mark dead-end
    return false;
}

// Hopcroft-Karp algorithm to find maximum bipartite matching
int hopcroftKarp() {
    memset(pairU, 0, sizeof(pairU));
    memset(pairV, 0, sizeof(pairV));

    int matching = 0;
    while (bfs()) { // while there exists an augmenting path
        for (int u = 1; u <= n; u++)
            if (pairU[u] == 0 && dfs(u))
                matching++;
    }
    return matching;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m; // input number of vertices in U and V
    int edges; cin >> edges;
    for (int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v; // input edge from u in U to v in V
        adj[u].push_back(v);
    }

    int ans = hopcroftKarp();
    cout << "Maximum Matching = " << ans << "\n";

    // print matching pairs
    for (int u = 1; u <= n; u++)
        if (pairU[u])
            cout << u << " - " << pairU[u] << "\n";
}
