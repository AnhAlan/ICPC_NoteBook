template<typename T>
struct GraphCut{
    const undigraph<T> &g;
    int n, m, LOG, cnt;
    vector<int> low, num, in, out, high, numChild, dsu;
    vector<bool> isBridge, isArticu;
    vector<vector<int> > par;
    vector<pair<pair<int,int> , int>> sored_edges;
    int cnt_bridge, cut_articu;
    GraphCut(const undigraph<T> &_g) : g(_g), n(g.n), m((int) g.edges.size()){
        assert(n > 0);
        LOG = 31 - __builtin_clz(n) + 1;
        cnt = 0;
        cnt_bridge = cut_articu = 0;
        low.resize(n + 1);
        num.resize(n + 1);
        in.resize(n + 1);
        out.resize(n + 1);
        high.resize(n + 1);
        numChild.resize(n + 1);
        dsu.assign(n + 1, -1);
        isBridge.assign(m + 1, false);
        isArticu.assign(n +1, false);
        par.assign(n + 1, vector<int>(LOG + 1));
        for(int id = 0; id < (int) g.edges.size(); id++){
            int u = g.edges[id].from, v = g.edges[id].to;
            if(u > v) swap(u, v);
            sored_edges.push_back({{u, v}, id});
        }
    }
    int find(int u){
        return dsu[u] < 0 ? u : dsu[u] = find(dsu[u]);
    }
    bool unite(int u, int v){
        u = find(u);
        v = find(v);
        if(u == v) return false;
        if(dsu[u] > dsu[v]) swap(u, v);
        dsu[u] += dsu[v];
        dsu[v] = u;
        return true;
    }
    void dfs(int u, int par_id = -1){
        low[u] = num[u] = ++cnt;
        in[u] = cnt;
        for(int id : g.adj[u]){
            if(id == par_id) continue;
            int v = g.edges[id].from ^ g.edges[id].to ^ u;
            if(!num[v]){
                par[v][0] = u;
                high[v] = high[u] + 1;
                numChild[u]++;
                dfs(v, id);
                low[u] = min(low[u], low[v]);
                if(par[u][0] != 0 && low[v] >= num[u] && !isArticu[u]){
                    cut_articu++;
                    isArticu[u] = true; 
                }
                if(low[v] > num[u]){
                    cnt_bridge++;
                    isBridge[id] = true;
                }
            }else{
                low[u] = min(low[u], num[v]);
            }
        }
        out[u] = cnt;
    }
    void build(){
        int sz = (int) g.edges.size();
        sort(sored_edges.begin(), sored_edges.end());     
        for(int id = 0; id < sz; id++){
            unite(g.edges[id].from, g.edges[id].to);
        }
        for(int u = 1; u <= n; u++){
            if(!num[u]){
                dfs(u);
                if(numChild[u] >= 2){
                    cut_articu++;
                    isArticu[u] = true;
                }
            }
        }
        for(int j = 1; j <= LOG; j++){
            for(int i = 1; i <= n; i++){
                if(par[i][j - 1] != 0) par[i][j] = par[par[i][j - 1]][j - 1];
                else par[i][j] = 0;
            }
        }
    }
    bool in_subTree(int u, int v){
        return (num[u] <= num[v] && num[v] <= out[u]);
    }
    int jump(int u, int k){
        for(int i = LOG; i >= 0; i--){
            if((1 << i) <= k){
                u = par[u][i];
                k -= (1 << i);
            }
        }
        return u;
    }
    bool check_Articu(int u, int v, int cut){
        if(find(u) != find(v)) return false;
        if(!isArticu[cut]) return false;
        if(u == cut || v == cut) return false;
        int childA = -1, childB = -1;
        if(u != cut && in_subTree(u, cut)){
            childA = jump(u, high[u] - high[cut] - 1);
        }
        if(v != cut && in_subTree(v, cut)){
            childB = jump(v, high[v] - high[cut] - 1);
        }
        if (childA > 0 && low[childA] < num[cut]) childA = -1;
        if (childB > 0 && low[childB] < num[cut]) childB = -1;
        return childA != childB;
    }
    bool check_bridge(int u, int v, int cut_u, int cut_v){
        if(find(u) != find(v)) return false;
        int a = cut_u, b = cut_v;
        if(a > b) swap(a, b);
        int idx = lower_bound(sored_edges.begin(), sored_edges.end(), 
                    make_pair(make_pair(a, b), INT_MIN)) - sored_edges.begin();
        if(idx >= (int)sored_edges.size() || sored_edges[idx].first != make_pair(a, b)) return false;  
        int id = sored_edges[idx].second; 
        if(!isBridge[id]) return false;
        int child = (high[cut_u] > high[cut_v] ? cut_u : cut_v);
        bool uIn = in_subTree(child, u);
        bool vIn = in_subTree(child, v);
        return uIn != vIn;  
    }
};  