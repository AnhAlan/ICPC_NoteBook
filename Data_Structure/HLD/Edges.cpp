#include <bits/stdc++.h>
using namespace std;
#define ll long long


int n, Q;
vector<pair<int,int>> g[MAXN]; 
const int MAXN = 200005;
int par[MAXN], high[MAXN], heavy[MAXN], head[MAXN], pos[MAXN], sz[MAXN];
int cnt = 1; 
int edge_to_node[MAXN]; 


void dfs(int u, int p){
    par[u] = p;
    sz[u] = 1;
    int max_sz = 0;
    for(auto [v, idx] : g[u]){
        if(v == p) continue;
        high[v] = high[u] + 1;
        dfs(v, u);
        sz[u] += sz[v];
        if(sz[v] > max_sz){
            max_sz = sz[v];
            heavy[u] = v;
        }
        edge_to_node[idx] = v; 
    }
}


void decompose(int u, int h){
    head[u] = h;
    pos[u] = cnt++;
    if(heavy[u]) decompose(heavy[u], h);
    for(auto [v, idx] : g[u]){
        if(v == par[u] || v == heavy[u]) continue;
        decompose(v,v);
    }
}

ll seg[MAXN*4+5], edge_weight[MAXN]; 

void build(int id, int l, int r){
    if(l == r){
        seg[id] = edge_weight[l];
        return;
    }
    int mid = (l+r)/2;
    build(id*2, l, mid);
    build(id*2+1, mid+1, r);
    seg[id] = seg[id*2] + seg[id*2+1];
}

void update(int id, int l, int r, int idx, ll val){
    if(l == r){
        seg[id] = val;
        return;
    }
    int mid = (l+r)/2;
    if(idx <= mid) update(id*2,l,mid,idx,val);
    else update(id*2+1,mid+1,r,idx,val);
    seg[id] = seg[id*2] + seg[id*2+1];
}

ll query(int id,int l,int r,int ql,int qr){
    if(ql>r || qr<l) return 0;
    if(ql<=l && r<=qr) return seg[id];
    int mid=(l+r)/2;
    return query(id*2,l,mid,ql,qr)+query(id*2+1,mid+1,r,ql,qr);
}


ll query_path(int u, int v){
    ll res = 0;
    while(head[u] != head[v]){
        if(high[head[u]] < high[head[v]]) swap(u,v);
        res += query(1,1,n,pos[head[u]],pos[u]);
        u = par[head[u]];
    }
    if(u==v) return res; 
    if(high[u] > high[v]) swap(u,v);
    res += query(1,1,n,pos[u]+1,pos[v]); 
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for(int i=1;i<n;i++){
        int a,b; ll w;
        cin >> a >> b >> w;
        g[a].push_back({b,i});
        g[b].push_back({a,i});
        edge_weight[i] = w; 
    }

    high[1] = 0;
    dfs(1,0);
    decompose(1,1);
 
    ll temp[MAXN];
    for(int i=1;i<n;i++){
        int node = edge_to_node[i]; 
        temp[pos[node]] = edge_weight[i];
    }
    for(int i=1;i<=n;i++) edge_weight[i] = temp[i];

    /*
        if node is value
        int tmp[n+1];
        for(int i=1;i<=n;i++){
            tmp[pos[i]] = a[i];
        }
        for(int i=1;i<=n;i++){
        a[i] = tmp[i];
        }
    */

    build(1,1,n);

    cin >> Q;
    while(Q--){
        int type;
        cin >> type;
        if(type == 1){
            int i; ll w;
            cin >> i >> w;
            int node = edge_to_node[i];
            update(1,1,n,pos[node],w);
        } else {
            int a,b;
            cin >> a >> b;
            cout << query_path(a,b) << "\n";
        }
    }
}
