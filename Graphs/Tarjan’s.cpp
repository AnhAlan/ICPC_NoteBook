const int maxn = 1005;
vector<vector<int>> SCC;  
int low[maxn], num[maxn], onst[maxn], comp[maxn];
int cnt = 0;
stack<int> st;
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
