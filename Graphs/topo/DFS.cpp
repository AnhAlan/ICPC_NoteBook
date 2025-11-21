#include<bits/stdc++.h>
#define ll long long
using namespace std;

int n, m;
vector<int> luu[1001];
bool check[1001];
vector<int> poto;

void nhap(){
    cin >> b >> n;
    for(int i = 1; i <= m; i++){
        int x, y;
        cin >> x >> y;
        luu[x].push_back(y); // directed graph: x -> y
    }
    memset(check, false, sizeof(check));
}

void dfs(int u){
    check[u] = true; // mark node as visited

    // explore all outgoing edges from u
    for(int v : luu[u]){
        if(!check[v]){ // if not visited
            dfs(v);
        }
    }

    // after visiting all neighbors, push u into result
    // (post-order) — this is the key step for topological sort
    poto.push_back(u);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    nhap();

    // run DFS from all unvisited nodes
    for(int i = 1; i <= dinh; i++){
        if(!check[i]){
            dfs(i);
        }
    }

    // reverse the post-order list to obtain topological order
    reverse(poto.begin(), poto.end());

    for(int x : poto){
        cout << x << " ";
    }

    return 0;
}
