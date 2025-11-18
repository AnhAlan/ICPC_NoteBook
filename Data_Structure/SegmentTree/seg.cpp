#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    int n; 
    vector<long long> st, lazy;

    SegTree(int n) : n(n) {
        st.assign(4*n, 0);
        lazy.assign(4*n, 0);
    }

    void build(int id, int l, int r, const vector<long long>& a) {
        if (l == r) {
            st[id] = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(id*2, l, mid, a);
        build(id*2+1, mid+1, r, a);
        st[id] = st[id*2] + st[id*2+1];
    }

    // Push lazy value down to children
    void push_down(int id, int l, int r) {
        if (lazy[id] == 0) return;
        int mid = (l + r) / 2;
        st[id*2] += lazy[id] * (mid - l + 1);
        st[id*2+1] += lazy[id] * (r - mid);
        lazy[id*2] += lazy[id];
        lazy[id*2+1] += lazy[id];
        lazy[id] = 0;
    }

    // Range update: add val to [u, v]
    void update(int id, int l, int r, int u, int v, long long val) {
        if (v < l || r < u) return;
        if (u <= l && r <= v) {
            st[id] += val * (r - l + 1);
            lazy[id] += val;
            return;
        }
        push_down(id, l, r);
        int mid = (l + r) / 2;
        update(id*2, l, mid, u, v, val);
        update(id*2+1, mid+1, r, u, v, val);
        st[id] = st[id*2] + st[id*2+1];
    }

    // Range query: sum on [u, v]
    long long query(int id, int l, int r, int u, int v) {
        if (v < l || r < u) return 0;
        if (u <= l && r <= v)
            return st[id];
        push_down(id, l, r);
        int mid = (l + r) / 2;
        return query(id*2, l, mid, u, v) + query(id*2+1, mid+1, r, u, v);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<long long> a(n+1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    SegTree st(n);
    st.build(1, 1, n, a);

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int l, r;
            long long val;
            cin >> l >> r >> val;
            st.update(1, 1, n, l, r, val);
        } else {
            int l, r;
            cin >> l >> r;
            cout << st.query(1, 1, n, l, r) << "\n";
        }
    }
}
