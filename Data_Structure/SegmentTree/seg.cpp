
const int maxn = 1e6 + 6;
int a[maxn];
struct Node {
   long long val;
    Node(long long _val = 0) : val(_val) {}
};

struct SegTree {
    int n;
    vector<Node> seg;
    //vector<long long> lazy; 

    SegTree(int _n) : n(_n) {
        seg.assign(4*n, Node(0));
        //lazy.assign(4*n, 0);
    }

    void apply(int id, int l, int r,long long w) {
        seg[id].val = w;       
        //lazy[id] = w;          
    }

    // void push(int id, int l, int r) {
    //     if(lazy[id] != 0) {
    //         int mid = (l + r) / 2;
    //         apply(id*2, l, mid, lazy[id]);
    //         apply(id*2+1, mid+1, r, lazy[id]);
    //         lazy[id] = 0;
    //     }
    // }

    void pull(int id) {
        seg[id].val = max(seg[id*2].val, seg[id*2+1].val);
    }

    void build(int id, int l, int r) {
        //lazy[id] = 0;
        if(l == r){
            seg[id] = Node(a[l]);
            return;
        }
        int mid = (l + r) / 2;
        build(id*2, l, mid);
        build(id*2+1, mid+1, r);
        pull(id);
    }

    // void update_range(int id, int l, int r, int u, int v, long long w) {
    //     if(r < u || v < l) return;
    //     if(u <= l && r <= v){
    //         apply(id, l, r, w);
    //         return;
    //     }
    //     push(id, l, r);
    //     int mid = (l + r) / 2;
    //     update_range(id*2, l, mid, u, v, w);
    //     update_range(id*2+1, mid+1, r, u, v, w);
    //     pull(id);
    // }

    void update_pos(int id, int l, int r, int pos,long long w) {
        if(l == r){
            seg[id] = Node(w);
            //lazy[id] = 0;
            return;
        }
        //push(id, l, r);
        int mid = (l + r) / 2;
        if(pos <= mid) update_pos(id*2, l, mid, pos, w);
        else update_pos(id*2+1, mid+1, r, pos, w);
        pull(id);
    }

   long long get(int id, int l, int r, int u, int v){
        if(r < u || v < l) return LLONG_MIN;
        if(u <= l && r <= v) return seg[id].val;
        //push(id, l, r);
        int mid = (l + r) / 2;
        return max(get(id*2, l, mid, u, v), get(id*2+1, mid+1, r, u, v));
    }
};

