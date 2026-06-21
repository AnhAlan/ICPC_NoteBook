template<typename T>
struct SegTree {
    struct Node {
        T val;
        Node(T _val) {
            val = _val;
        }
    };
    int n;
    vector<Node> seg;
    vector<T> lazy;
    SegTree() : n(0){}
    SegTree(int _n) {
        n = _n;
        seg.assign(4 * n + 5, Node(0));
        lazy.assign(4 * n + 5, 0);
    }
    Node merge(const Node &a, const Node &b) {
        return Node(a.val + b.val);
    }
    void push_down(int id, int l, int r) {
        if (lazy[id] != 0) {
            int mid = (l + r) / 2;
            seg[id * 2].val += (mid - l + 1) * lazy[id];
            seg[id * 2 + 1].val += (r - mid) * lazy[id];
            lazy[id * 2] += lazy[id];
            lazy[id * 2 + 1] += lazy[id];
            lazy[id] = 0;
        }
    }
    void build(int id, int l, int r,const vector<T> &a) {
        if (l == r) {
            seg[id].val = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(id * 2, l, mid, a);
        build(id * 2 + 1, mid + 1, r, a);
        seg[id] = merge(seg[id * 2], seg[id * 2 + 1]);
    }
    void update_range(int id, int l, int r, int u, int v,const T &val) {
        if (l > v || r < u) return;
        if (l >= u && r <= v) {
            seg[id].val += (r - l + 1) * val;
            lazy[id] += val;
            return;
        }
        push_down(id, l, r);
        int mid = (l + r) / 2;
        update_range(id * 2, l, mid, u, v, val);
        update_range(id * 2 + 1, mid + 1, r, u, v, val);
        seg[id] = merge(seg[id * 2], seg[id * 2 + 1]);
    }
    T get_range(int id, int l, int r, int u, int v) {
        if (l > v || r < u) return 0;
        if (l >= u && r <= v) return seg[id].val;
        push_down(id, l, r);
        int mid = (l + r) / 2;
        return get_range(id * 2, l, mid, u, v) + get_range(id * 2 + 1, mid + 1, r, u, v);
    }
};