#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Node {
    ll val; 
    Node(ll _val){
        val = _val;
    }
};

struct SegTree {
    int n;
    vector<Node> seg;
    vector<ll> lazy; 

    SegTree(int _n) : n(_n) {
        seg.assign(4*n, Node(0));
        lazy.assign(4*n, 0);
    }

    void apply(int id, int l, int r, ll w) {
        seg[id].val = w;       
        lazy[id] = w;          
    }

    void push(int id, int l, int r) {
        if(lazy[id] != 0) {
            int mid = (l + r) / 2;
            apply(id*2, l, mid, lazy[id]);
            apply(id*2+1, mid+1, r, lazy[id]);
            lazy[id] = 0;
        }
    }

    void pull(int id) {
        seg[id].val = max(seg[id*2].val, seg[id*2+1].val);
    }

    void build(int id, int l, int r, const vector<ll>& a) {
        lazy[id] = 0;
        if(l == r){
            seg[id] = Node(a[l]);
            return;
        }
        int mid = (l + r) / 2;
        build(id*2, l, mid, a);
        build(id*2+1, mid+1, r, a);
        pull(id);
    }

    void update(int id, int l, int r, int u, int v, ll w) {
        if(r < u || v < l) return;
        if(u <= l && r <= v){
            apply(id, l, r, w);
            return;
        }
        push(id, l, r);
        int mid = (l + r) / 2;
        update(id*2, l, mid, u, v, w);
        update(id*2+1, mid+1, r, u, v, w);
        pull(id);
    }

    void update_point(int id, int l, int r, int pos, ll w) {
        if(l == r){
            seg[id] = Node(w);
            lazy[id] = 0;
            return;
        }
        push(id, l, r);
        int mid = (l + r) / 2;
        if(pos <= mid) update_point(id*2, l, mid, pos, w);
        else update_point(id*2+1, mid+1, r, pos, w);
        pull(id);
    }

    ll query(int id, int l, int r, int u, int v){
        if(r < u || v < l) return LLONG_MIN;
        if(u <= l && r <= v) return seg[id].val;
        push(id, l, r);
        int mid = (l + r) / 2;
        return max(query(id*2, l, mid, u, v),
                   query(id*2+1, mid+1, r, u, v));
    }


};

