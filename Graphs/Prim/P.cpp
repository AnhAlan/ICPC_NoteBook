#include<bits/stdc++.h>
#define ll long long
#define all(a) a.begin(),a.end()
#define en "\n"
using namespace std;
const int MAXN = 1e5+5;

struct canh{
    int x,y,w;
};

int n,m;
vector<pair<int,int>> adj[MAXN];
bool used[MAXN];
int parent[MAXN];
int d[MAXN];

void load(){
    cin >> n >> m;
    for(int i=0;i<m;i++){
        int x,y,w;
        cin >> x >> y >> w;
        adj[x].push_back({y,w});
        adj[y].push_back({x,w});
    }

    memset(used,false,sizeof(used));
    for(int i=0;i<n;i++){
        d[i] = INT_MAX;
    }
}

void prim(int u){
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> Q;
    vector<canh> MST;
    int res = 0;

    Q.push({0,u});
    d[u] = 0;
    parent[u] = -1;

    while(!Q.empty()){
        pair<int,int> top = Q.top();
        Q.pop();
        int dinh = top.second;
        int trongso = top.first;

        if(used[dinh]) continue;

        used[dinh] = true;
        res += trongso;

        if(parent[dinh] != -1){
            MST.push_back({dinh, parent[dinh], trongso});
        }

        for(auto it : adj[dinh]){
            int y = it.first;
            int w = it.second;
            if(!used[y] && w < d[y]){
                d[y] = w;
                parent[y] = dinh;
                Q.push({w, y});
            }
        }
    }

    cout << res << en;
}




int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    load();
    prim(1);

    return 0;
    
}