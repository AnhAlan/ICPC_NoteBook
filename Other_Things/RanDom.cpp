#include <bits/stdc++.h>

#define ll long long
using namespace std;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

ll ran(ll l, ll r){
    return uniform_int_distribution<ll>(l,r)(rng);
}

void rd_tree(){
    int n = ran(2,6);
    int m = ran(1,n-1);
    cout << n << " " << m << "\n";
    vector<int> par(n+1);
    for(int i = 2; i <= n; i++){
        par[i] = ran(1,i-1);
        cout << par[i] << " " << i << "\n";
    }
}

void rd_string(){
    int n = ran(2,100);
    string s(n,' ');
    for(int i = 0; i < n; i++){
        s[i] = 'a' + ran(0,25);
        /*
        uppercase: 'A' + ran(0,25)
        digit:     '0' + ran(0,9)
        */
    }
    cout << s << "\n";
}

void rd_graph(){
    int n = ran(2,10);
    int maxEdge = n*(n-1)/2;
    int m = ran(1,maxEdge);
    set<pair<int,int>> seen;
    cout << n << " " << m << "\n";
    while(seen.size()/2 < m){
        int u = ran(1,n);
        int v = ran(1,n);
        int w = ran(1,10);
        if(u == v) continue;
        if(seen.count({u,v})) continue;
        seen.insert({u,v});
        seen.insert({v,u});
        cout << u << " " << v << " " << w << "\n";
    }
}

void rd_vector(){
    int n = 10;
    vector<int> a(n);
    iota(a.begin(),a.end(),1);
    shuffle(a.begin(),a.end(),rng);
    for(auto x : a){
        cout << x << " ";
    }
    cout << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


}