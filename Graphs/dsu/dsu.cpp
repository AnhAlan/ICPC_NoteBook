struct DSU {
    vector<int> par, Size;
    int n;
    DSU(int _n) : n(_n) {
        par.resize(n+1);
        Size.resize(n+1);
        for(int i = 1; i <= n; i++) {
            par[i] = i;
            Size[i] = 1;
        }
    }

    int find(int a) {
        if(par[a] == a) return a;
        return par[a] = find(par[a]);
    }
    
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if(a == b) return;
        if(Size[a] < Size[b]) swap(a, b);
        par[b] = a;
        Size[a] += Size[b];
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }
};


