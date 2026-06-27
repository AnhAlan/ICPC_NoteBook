template<typename T>
struct Node {
    T sum, mn, mx;
    Node() {
        sum = 0;
        mx = numeric_limits<T>::lowest();
        mn = numeric_limits<T>::max();
    }
    Node(T v) {
        sum = v, mn = v, mx = v;
    }
};
template<typename T>
struct Merge {
    Node<T> operator()(const Node<T> &A, const Node<T> &B) const {
        Node<T> res;
        res.sum = A.sum + B.sum;
        res.mn = min(A.mn, B.mn);
        res.mx = max(A.mx, B.mx);
        return res;
    }
    Node<T> none() {
        Node<T> res;
        res.sum = 0;
        res.mn = numeric_limits<T>::max();
        res.mx = numeric_limits<T>::lowest();
        return res;
    }
};

template<typename T, typename F = Merge<T>>
struct SegTree {
    int n;
    vector<Node<T>> seg;
    vector<T> lazy;
    F merge;
    
    SegTree() : n(0){}
    SegTree(int _n) {
        n = _n;
        seg.assign(4 * n + 5, Node<T>());
        lazy.assign(4 * n + 5, 0);
    }
    void apply(int id, int l, int r, T val) {
        seg[id].sum += (r - l + 1) * val; 
        seg[id].mn += val;              
        seg[id].mx += val;              
        lazy[id] += val;
    }
    void push_down(int id, int l, int r) {
        if (lazy[id] != 0) {
            int mid = (l + r) / 2;
            apply(id * 2, l, mid, lazy[id]);      
            apply(id * 2 + 1, mid + 1, r, lazy[id]);
            lazy[id] = 0;                           
        }
    }
    
    void build(int id, int l, int r, const vector<T> &a) {
        if (l == r) {
            seg[id] = Node<T>(a[l]);
            return;
        }
        int mid = (l + r) / 2;
        build(id * 2, l, mid, a);
        build(id * 2 + 1, mid + 1, r, a);
        seg[id] = merge(seg[id * 2], seg[id * 2 + 1]);
    }
    
    void update_range(int id, int l, int r, int u, int v, const T &val) {
        if (l > v || r < u) return;
        if (l >= u && r <= v) {
            apply(id, l, r, val); 
            return;
        }
        push_down(id, l, r);
        int mid = (l + r) / 2;
        update_range(id * 2, l, mid, u, v, val);
        update_range(id * 2 + 1, mid + 1, r, u, v, val);
        seg[id] = merge(seg[id * 2], seg[id * 2 + 1]);
    }
    
    Node<T> get_range(int id, int l, int r, int u, int v) {
        if (l > v || r < u) return merge.none();
        if (l >= u && r <= v) return seg[id];
        push_down(id, l, r);
        int mid = (l + r) / 2;
        return merge(get_range(id * 2, l, mid, u, v), get_range(id * 2 + 1, mid + 1, r, u, v));
    }
    /*
        SegTree<int, Merge<int> > st(n)
    */
};