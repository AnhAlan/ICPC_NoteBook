#include <bits/stdc++.h>
using namespace std;
using ll = long long;

mt19937_64 ran(chrono::steady_clock::now().time_since_epoch().count());
ll rand(ll l,ll r){
    uniform_int_distribution<ll> dist(l,r);
    return dist(ran);
}

vector<tuple<int, int, int>> random_tree(int n) {
    vector<tuple<int, int, int>> edges;
    if (n <= 1) return edges;
    vector<int> vertices(n);
    iota(vertices.begin(), vertices.end(), 1);
    shuffle(vertices.begin(), vertices.end(), ran);
    for (int i = 1; i < n; i++) {
        int u = vertices[i];
        int v = vertices[rand(0, i - 1)]; 
        ll w = rand(1, 10000);           
        edges.push_back({u, v, w});
    }
    shuffle(edges.begin(), edges.end(), ran);
    return edges;
}
string random_string(int n){
    string s(n, ' ');
    for(int i = 0; i < n; i++){
        s[i] = 'a' + rand(0,25);
    }
    return s;
}
vector<tuple<int,int,int> > random_graph(int n, int m){
    long long max_edges = 1LL * n * (n - 1) / 2;
    if (m > max_edges) m = max_edges; 
    vector<tuple<int,int,int> > adj;
    set<pair<int,int>> seen;
    for(int i=0; i<m; i++){
        int u = rand(1,n);
        int v = rand(1,n);
        int w = rand(1,10);
        while(u == v || seen.count({u,v}) || seen.count({v,u})){
            u = rand(1,n);
            v = rand(1,n);
        }
        seen.insert({u,v});
        seen.insert({v,u});
        adj.push_back({u, v, w});
    }
    return adj;
}
vector<int> random_vector(int n){
    vector<int> a(n);
    iota(a.begin(), a.end(), 1);
    shuffle(a.begin(), a.end(), ran);
    return a;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
}