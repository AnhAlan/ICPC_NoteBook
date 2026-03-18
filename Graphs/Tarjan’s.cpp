#include <bits/stdc++.h>
#define ll long long
#define all(a) a.begin(), a.end()
#define en "\n"
#define DEBUG(x) cerr << #x << ": " << x << en
using namespace std;

const int maxn = 1005;
vector<int> adj[maxn];       // adjacency list of original graph
int n, m;
vector<vector<int>> SCC;     // stores all strongly connected components

int low[maxn], num[maxn], onst[maxn], comp[maxn];
int cnt = 0;
stack<int> st;

// Load graph input
void load() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);  // directed graph
    }
}

// Tarjan's DFS for finding SCCs
void dfs(int u) {
    low[u] = num[u] = ++cnt;
    st.push(u);
    onst[u] = 1;

    for (int v : adj[u]) {
        if (!num[v]) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        } else if (onst[v]) {
            low[u] = min(low[u], num[v]);
        }
    }

    if (low[u] == num[u]) {
        vector<int> tmp;
        while (true) {
            int v = st.top(); st.pop();
            onst[v] = 0;
            tmp.push_back(v);
            if (v == u) break;
        }
        SCC.push_back(tmp);
    }
}

vector<vector<int>> dag;     // DAG of SCCs
vector<int> topo;            // topological order
vector<int> idx;             // indegree for Kahn's algorithm

// Build DAG of SCCs
void build_DAG() {
    int k = SCC.size();

    // Assign component index to each vertex
    for (int i = 0; i < k; i++) {
        for (int u : SCC[i]) {
            comp[u] = i;
        }
    }

    // Resize DAG
    dag.assign(k, {});
    for (int u = 1; u <= n; u++) {
        for (int v : adj[u]) {
            if (comp[u] != comp[v]) {
                dag[comp[u]].push_back(comp[v]);
            }
        }
    }

    // Remove duplicate edges
    for (int i = 0; i < k; i++) {
        sort(all(dag[i]));
        dag[i].erase(unique(all(dag[i])), dag[i].end());
    }

    // Print DAG
    cout << "DAG (between SCCs):\n";
    for (int i = 0; i < k; i++) {
        cout << "SCC " << i << " -> ";
        for (int v : dag[i]) cout << v << " ";
        cout << en;
    }
}

// Kahn's algorithm for topological sorting
void kahn(const vector<vector<int>>& g) {
    int k = g.size();
    topo.clear();
    idx.assign(k, 0);

    // Compute indegree
    for (int u = 0; u < k; u++) {
        for (int v : g[u]) {
            idx[v]++;
        }
    }

    queue<int> q;
    for (int i = 0; i < k; i++) {
        if (idx[i] == 0) q.push(i);
    }

    while (!q.empty()) {
        int u = q.front(); q.pop();
        topo.push_back(u);
        for (int v : g[u]) {
            if (--idx[v] == 0) q.push(v);
        }
    }

    // Check DAG validity
    if ((int)topo.size() != k) {
        cerr << "Warning: topo size != k, something wrong\n";
    }

    cout << "Topological order of SCCs:\n";
    for (int v : topo) cout << v << " ";
    cout << en;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    load();

    // Run Tarjan's algorithm
    for (int i = 1; i <= n; i++) {
        if (!num[i]) dfs(i);
    }

    // Build DAG of SCCs and perform topological sort
    build_DAG();
    kahn(dag);

    return 0;
}
