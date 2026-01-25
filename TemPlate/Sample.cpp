#include<bits/stdc++.h>

#define ll long long
#define all(a) a.begin(),a.end()
#define en "\n"
#define bit(mask,i) (((mask)>>(i))&1)
#define MASK(x) (1 << (x))
#define debug(...) cerr << "[" << #__VA_ARGS__ << "] = ", dbg(__VA_ARGS__), cerr << "\n"
#define fi first
#define se second

using namespace std;

template<typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1,T2>& p){
    os << "{" << p.first << "," << p.second << "}";
    return os;
}


template<typename T>
ostream& operator<<(ostream& os,const vector<T>& v){
    os << "{";
    for(size_t i = 0;i<v.size();i++){
        os << v[i];
        if(i+1<v.size()){
            os << ",";
        }
    }
    os << "}";
    return os;
}

template<typename T>
ostream& operator<<(ostream& os, const vector<vector<T>>& v) {
    os << "{ ";
    for (size_t i = 0; i < v.size(); i++) {
        os << "[";
        for (size_t j = 0; j < v[i].size(); j++) {
            os << v[i][j];
            if (j + 1 < v[i].size()) os << ","; 
        }
        os << "] ";
    }
    os << " }";
    return os;
}

struct hash_pair{
    template<class T1,class T2>
    size_t operator()(const pair<T1,T2>&p)const{
        auto h1 = hash<T1>()(p.first);
        auto h2 = hash<T2>()(p.second);
        return h1 ^ (h2<<1);
    }
};

void dbg() {} 

template<typename T, typename... Args>
void dbg(const T& a, const Args&... args){
    cerr << a;
    if(sizeof...(args)) cerr << ", ";
    dbg(args...);
}



mt19937 ran(chrono::steady_clock::now().time_since_epoch().count());
int rand(int l,int r){
    return ran() % (r-l+1);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

}