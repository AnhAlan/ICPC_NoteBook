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

template<typename T>
ostream& operator<<(ostream& os,const vector<T>& v){
    os << "[";
    for(size_t i = 0;i<v.size();i++){
        os << v[i];
        if(i+1<v.size()){
            os << ",";
        }
    }
    os << "]";
    return os;
}

template<typename T>
ostream& operator<<(ostream& os, const vector<vector<T>>& v) {
    for (size_t i = 0; i < v.size(); i++) {
        os << "[";
        for (size_t j = 0; j < v[i].size(); j++) {
            os << v[i][j];
            if (j + 1 < v[i].size()) os << ","; 
        }
        os << "] ";
    }
    return os;
}

//un_map<pair<int,int>,int,hash_pair>mp
struct hash_pair{
    template<class T1,class T2>
    size_t operator()(const pair<T1,T2>&p)const{
        auto h1 = hash<T1>()(p.first);
        auto h2 = hash<T2>()(p.second);
        return h1 ^ (h2<<1);
    }
};

//random
mt19937 ran(chrono::steady_clock::now().time_since_epoch().count());
int rand(int l,int r){
    return ran() % (r-l+1);
}
/*solve*/

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);


}