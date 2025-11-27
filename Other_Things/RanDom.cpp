#include<bits/stdc++.h>

#define ll long long

using namespace std;

mt19937_64 ran(chrono::steady_clock::now().time_since_epoch().count());
ll rand(int l,int r){
    uniform_int_distribution<ll> dist(l,r);
    return dist(ran);
}

void rd_tree(){
    int n = rand(2,6); //2 to random number
    int m = rand(1,n-1);
    cout << n << " " << m << "\n";
    vector<int>par(n);

    for(int i = 2; i <= n ;i++){
        par[i] = rand(1,i-1);
        cout << par[i] << " " << i << "\n";
    }
}

void rd_string(){
    int n = rand(2,100);
    string s(n, ' ');
    for(int i = 0; i < n; i++){
        s[i] = 'a' + rand(0,25); // 0 - 25 first char
        /*
            if want string upper s[i] = 'A' + rand(0,25)
            if want string a number s[i] = '0' + rand(0,9)
        */
    }
    cout << s << "\n";
}

//scalar
void rd_graph(){
    int n = rand(2,10);
    int m = rand(2,10);
    set<pair<int,int>>seen;
    cout << n << " " << m << "\n";
    for(int i=0;i<m;i++){
        int u = rand(1,n);
        int v = rand(1,n);
        int w = rand(1,10); // value
        while(u == v || seen.count({u,v})){
            u = rand(1,n);
            v = rand(1,n);
        }
        seen.insert({u,v});
        seen.insert({v,u});
        cout << u << " " << v << " " << w << "\n";
    }
    
}

void rd_vector(){
    int n = 10;
    vector<int>a(n);

    iota(a.begin(),a.end(),1);
    shuffle(a.begin(),a.end(),ran); //use ran 

    for(auto x : a){
        cout << x << " ";
    }
    cout << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    rd_graph();

}