#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent, Size;
    int n;
    DSU(int _n) : n(_n) {
        parent.resize(n+1);
        Size.resize(n+1);
        for(int i = 1; i <= n; i++) {
            parent[i] = i;
            Size[i] = 1;
        }
    }

    int find(int a) {
        if(parent[a] == a) return a;
        return parent[a] = find(parent[a]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if(a == b) return;
        if(Size[a] < Size[b]) swap(a, b);
        parent[b] = a;
        Size[a] += Size[b];
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }
};


