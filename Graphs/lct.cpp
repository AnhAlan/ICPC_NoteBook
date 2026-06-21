template<typename T>
struct Lct {
    struct Node {
        int ch[2], p;
        T val, sum;
        bool rev;
        Node() {
            ch[0] = ch[1] = p = 0;
            val = sum = 0;
            rev = false;
        }
    };
    static const int N = 200005;
    Node t[N];
    bool isRoot(int x) {
        int p = t[x].p;
        return (t[p].ch[0] != x && t[p].ch[1] != x);
    }
    void push(int x) {
        if (!x || !t[x].rev) return;
        swap(t[x].ch[0], t[x].ch[1]);
        if (t[x].ch[0]) t[t[x].ch[0]].rev ^= 1;
        if (t[x].ch[1]) t[t[x].ch[1]].rev ^= 1;
        t[x].rev = false;
    }
    void pull(int x) {
        if (!x) return;
        t[x].sum = t[x].val;
        if (t[x].ch[0]) t[x].sum += t[t[x].ch[0]].sum;
        if (t[x].ch[1]) t[x].sum += t[t[x].ch[1]].sum;
    }
    void rotate(int x) {
        int p = t[x].p, g = t[p].p;
        int d = (t[p].ch[1] == x);
        if (!isRoot(p))
            t[g].ch[t[g].ch[1] == p] = x;
        t[x].p = g;
        t[p].ch[d] = t[x].ch[d ^ 1];
        if (t[x].ch[d ^ 1])
            t[t[x].ch[d ^ 1]].p = p;
        t[x].ch[d ^ 1] = p;
        t[p].p = x;
        pull(p);
        pull(x);
    }

    void splay(int x) {
        static int st[N];
        int top = 0, y = x;
        st[++top] = y;
        while (!isRoot(y)) {
            y = t[y].p;
            st[++top] = y;
        }
        while (top) push(st[top--]);
        while (!isRoot(x)) {
            int p = t[x].p, g = t[p].p;
            if (!isRoot(p)) {
                if ((t[p].ch[0] == x) ^ (t[g].ch[0] == p))
                    rotate(x);
                else
                    rotate(p);
            }
            rotate(x);
        }
    }

    int access(int x) {
        int last = 0;
        for (; x; x = t[x].p) {
            splay(x);
            t[x].ch[1] = last;
            pull(x);
            last = x;
        }
        return last;
    }

    void makeRoot(int x) {
        access(x);
        splay(x);
        t[x].rev ^= 1;
    }

    int findRoot(int x) {
        access(x);
        splay(x);
        while (t[x].ch[0]) {
            push(x);
            x = t[x].ch[0];
        }
        splay(x);
        return x;
    }
    void link(int u, int v) {
        makeRoot(u);
        if (findRoot(v) != u) {
            t[u].p = v;
        }
    }
    void cut(int u, int v) {
        makeRoot(u);
        access(v);
        splay(v);
        if (t[v].ch[0] == u && !t[u].ch[1]) {
            t[v].ch[0] = 0;
            t[u].p = 0;
            pull(v);
        }
    }

    T query(int u, int v) {
        makeRoot(u);
        access(v);
        splay(v);
        return t[v].sum;
    }

    int lca(int u, int v) {
        if (findRoot(u) != findRoot(v)) return -1;
        access(u);
        return access(v);
    }
};