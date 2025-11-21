#include<bits/stdc++.h>

#define ll long long
#define all(a) a.begin(),a.end()
#define en "\n"
#define bit(mask,i) (((mask)>>(i))&1)
#define MASK(x) (1 << (x))
#define DEBUG(x) cerr << #x << " " << x << en
#define fi first
#define se second

using namespace std;

#define LOG 19
const int maxn = 50000;
int n,m;
vector<int> adj[maxn];
pair<int,int> edges[maxn];
int high[maxn];
int low[maxn];
int num[maxn];
int fin[maxn];
bool visited[maxn];
bool isBridge[maxn];
int par[maxn][LOG];
int numChild[maxn];
int dsu[maxn];

//dsu
int find(int u){
    if(dsu[u] < 0){
        return u;
    }
    return dsu[u] = find(dsu[u]);
}

bool uniset(int u,int v){
    int x = find(u);
    int y = find(v);
    if( x == y){
        return false;
    }
    if(dsu[x] > dsu[y]){
        swap(x,y);
    }
    dsu[x] += dsu[y];
    dsu[y] = x;
    return true;
}

//input
void load(){
    cin >> n >> m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin >> u >> v;
        edges[i] = {u,v};
        adj[u].push_back(i);
        adj[v].push_back(i);
    }
}

//dsf
int cnt = 0;
void dfs(int u){
    low[u] = num[u] = ++cnt;

    for(int id : adj[u]){
        if(!visited[id]){
            visited[id] = true;
            int v = edges[id].first + edges[id].second - u;
            if(num[v] == 0){
                dfs(v);
                low[u] = min(low[u],low[v]);
                if(low[v] > num[u]){
                    isBridge[id] = true;
                }
            }
            else{
                low[u] = min(low[u],num[v]);
            }
        }
    }
    fin[u] = cnt;
}

//set up
void prepare(){
    fill(dsu,dsu+maxn,-1);
    for(int i=1;i<=m;i++){
        uniset(edges[i].fi,edges[i].se);
    }
    
    for(int i=1;i<=n;i++){
        dfs(i);
    }
    for(int j=LOG;j>=0;j--){
        for(int i=1;i<=n;i++){
            if(par[i][j-1]){
                par[i][j] = par[par[i][j-1]][j-1];
            }
            else{
                par[i][j] = 0;
            }
        }
    }

}

//cay con
bool isSub(int u,int a){
    return(num[u] <= num[a]) && (num[a] <= fin[u]);
}

//jump
int jump(int u,int k){
    for(int j=LOG;j>=0;j--){
        if(MASK(j) <= k){
            u = par[u][j];
            k -= MASK(j);
        }
    }
    return u;
}

bool solve(int u,int v,int a,int b){
    if(find(a) != find(b)){
        return false;
    }
    int id = lower_bound(edges+1,edges+m+1,make_pair(u,v)) - edges;
    cout << "id: " << id << endl;
    if(isBridge[id]){
        return false;
    }
    int child = (par[v][0] == u ? v : u);
    bool inA = isSub(child,a);
    bool inB = isSub(child,b);
    return inA == inB;

}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    load();
    prepare();
    cout << "hihi" << endl;
    for(int i=1;i<=m;i++){
        if(isBridge[i]){
            cout << "id " << i << ": ";
            cout << edges[i].fi << " " << edges[i].se << endl;
        }
    }
    while(1){
        int u,v,a,b;
        cin >> u >> v >> a >> b;
        if(solve(u,v,a,b)){
            cout <<  "yes" << en; 
        }
        else{
            cout << "no" << en;
        }
        cout.flush();
    }

}