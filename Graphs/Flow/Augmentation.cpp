#include<bits/stdc++.h>
#define ll long long
#define all(a) a.begin(),a.end()
#define en "\n"
#define bit(mask,i) (((mask)>>(i))&1)
#define MASK(x) (1 << (x))
#define DEBUG(x) cerr << #x << ": " << x << en
#define fi first
#define se second
using namespace std;

const int MAX = 1e3;
int matchL[MAX];
int matchR[MAX];
bool vis[MAX];
vector<int>adj[MAX];
int n,m,edges;

void load(){
    cin >> n >> m;
    cin >> edges;
    //INPUT edges from u = 1 -> n And v = 1 - > m
    for(int i=0;i<edges;i++){
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
}

bool dfs(int u){
    for(int v :adj[u]){
        if(!vis[v]){
            vis[v] = true;

            if(!matchR[v] || dfs(matchR[v]) ){
                matchL[u] = v;
                matchR[v] = u;
                return true;
            }
        }
    }
    return false;
}

int maxMatching(int n){
    int res = 0;

    for(int u=1;u<=n;u++){
        memset(vis,0,sizeof(vis));
        if(dfs(u)){
            res++;
        }
    }
    return res;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    load();
    memset(matchR,0,sizeof(matchR));
    memset(matchL,0,sizeof(matchL));
    cout << maxMatching(n) << en;

    for(int u=1;u<=n;u++){
        if(matchL[u]){
            cout << u << "-> " << matchL[u] << en;
        }
    }
    
}