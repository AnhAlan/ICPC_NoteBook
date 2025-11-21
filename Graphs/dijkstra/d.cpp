#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN = 1e5;
const ll INF  = 1e18;
int n,m;
vector<pair<int,int>> adj[MAXN];


void load(){

    cin >> n >> m;
    for(int i=0;i<m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }

}

void dijstraka(int s){
    vector<ll> d(n+1, INF);

    d[s] = 0;
    priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> Q;
    Q.push({0,s});
    while(!Q.empty()){
        pair<ll,int> top = Q.top();
        Q.pop();
        int u = top.second;
        ll w = top.first;
        if(w > d[u]){
            continue;
        }
        for(auto it : adj[u]){
            int v = it.first;
            ll kc_new = it.second;
            if(d[v] > d[u] + kc_new){
                d[v] = d[u] + kc_new;
                Q.push({d[v],v});
            }
        }
    }
    
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    load();
    dijstraka(1);
    return 0;
    
    
}