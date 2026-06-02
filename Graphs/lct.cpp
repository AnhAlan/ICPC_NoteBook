#include <bits/stdc++.h>
using namespace std;

struct Node {
    int ch[2], p;
    int val, sum;
    bool rev;
    //can ues more data struct
    Node() {
        ch[0] = ch[1] = p = 0;
        val = sum = 0;
        rev = false;
    }
};

const int N = 200005;
Node t[N];

/*
    if x is root
    -> no parent of x 
    -> check if left parent x != x and right parent x != x
    -> x is root
*/
bool isRoot(int x) {
    int p = t[x].p;
    return (t[p].ch[0] != x && t[p].ch[1] != x);
}

// push lazy down child
void push(int x) {
    if (!x || !t[x].rev) return;
    swap(t[x].ch[0], t[x].ch[1]);
    if (t[x].ch[0]) t[t[x].ch[0]].rev ^= 1;
    if (t[x].ch[1]) t[t[x].ch[1]].rev ^= 1;
    t[x].rev = false;
}

/*
    each pull -> reset sum
    sum += left sum + right sum 
*/
void pull(int x) {
    t[x].sum = t[x].val;
    if (t[x].ch[0]) t[x].sum += t[t[x].ch[0]].sum;
    if (t[x].ch[1]) t[x].sum += t[t[x].ch[1]].sum;
}

/*
    p : par x
    g : par p
    x - p - g
    make sure p and x are rev done
    then roate x 
        p - x - g
        if x left -> right child x is left child p
        if x right -> 

    
*/

void rotate(int x) {
    int p = t[x].p, g = t[p].p;
    push(p); push(x);
    int d = (t[p].ch[1] == x);

    if (!isRoot(p)) t[g].ch[t[g].ch[1] == p] = x;
    t[x].p = g;

    t[p].ch[d] = t[x].ch[d ^ 1];
    if (t[x].ch[d ^ 1]) t[t[x].ch[d ^ 1]].p = p;

    t[x].ch[d ^ 1] = p;
    t[p].p = x;

    pull(p); pull(x);
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
    access(x); splay(x);
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

    if (t[v].ch[0] == u) {
        t[v].ch[0] = 0;
        t[u].p = 0;
        pull(v);
    }
}

int query(int u, int v) {
    makeRoot(u);
    access(v); splay(v);
    return t[v].sum;
}

int lca(int u, int v) {
    //make sure u - v is link
    if (findRoot(u) != findRoot(v)) return -1;
    access(u);
    return access(v);
}

