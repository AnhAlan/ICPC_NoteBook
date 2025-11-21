#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
bitset<MAXN> reach[MAXN];
vector<int> adj[MAXN];
int n, m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
    }
    for(int i=1;i<=n;i++){
        reach[i][i] = 1;
        for(int v : adj[i]){
            reach[i][v] = 1;
        }
    }

    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            if(reach[i][k]){
                reach[i] |= reach[k];
            }
        }
    }

    int q;
    cin >> q;
    int cnt_u = n;
    while(q-->0){
        int ask,u,v;
        cin >> ask >>u >> v;
        if(ask == 1){
            ++cnt_u;
            reach[u][v] = 1;
            reach[u] |= reach[v];
            for(int x=1;x<=n;x++){
                if(reach[x][u]){
                    reach[x] |= reach[u];
                }
            }
        }
        else{
            cout << (reach[u][v] ? "yes" : "no") << "\n";
        }
    }
}
