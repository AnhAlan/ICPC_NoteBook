struct HopCroft{
    int n, INF;
    vector<vector<int> > adj;
    vector<int> level, ptr, pairU, pairV;
    HopCroft(){}
    HopCroft(int _n, int _m){
        n = _n;
        INF = (int) 1e9;
        adj.assign(_n + 1, {});
        level.assign(_n + 1, 0);
        ptr.assign(_n + 1, 0);
        pairU.assign(_n + 1, 0);
        pairV.assign(_m + 1, 0);
    }
    void add(int u, int v){
        adj[u].push_back(v);
    }
    bool bfs(){
        queue<int> q;
        for(int u = 1; u <= n; u++){
            if(!pairU[u]){
                level[u] = 0;
                q.push(u);
            }else level[u] = INF;
            ptr[u] = 0;
        }
        bool found = false;
        while(!q.empty()){
            int u = q.front(); q.pop();
            for(int v : adj[u]){
                int nxt = pairV[v];
                if(nxt == 0){
                    found = true;
                }
                else if(level[nxt] == INF){
                    level[nxt] = level[u] + 1;
                    q.push(nxt);
                }
            }
        }
        return found;
    }
    bool dfs(int u){
        for (int &i = ptr[u]; i < (int) adj[u].size(); i++){
            int v = adj[u][i];
            int nxt = pairV[v];
            if(!nxt || (level[nxt] == level[u] + 1 && dfs(nxt))){
                pairU[u] = v;
                pairV[v] = u;
                return true;
            }
        }
        return false;
    }
    int max_matching(){
        int res = 0;
        while(bfs()){
            for(int u = 1; u <= n; u++){
                if(!pairU[u] && dfs(u)){
                    res++;
                }
            }
        }
        return res;
    }
};