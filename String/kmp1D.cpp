#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string s,t;
    cin >> s >> t;
    s = "#" + s;
    t = "%" + t;

    int m = s.size() - 1;
    int n = t.size() - 1;

    vector<int>kmp(100,0);
    int k = kmp[1] = 0;

    for(int i=2;i<=m;i++){
        while(k > 0 && s[i] != s[k+1]){
            k = kmp[k];
        }
        if(s[i] == s[k+1]){
            ++k;
        }
        kmp[i] = k; 
    }

    vector<int> match(100,0);
    k = match[1] = 0;
    for(int i=1;i<=n;i++){
        while(k > 0 && t[i] != s[k+1]){
            k = kmp[k];
        }
        if(t[i] == s[k+1]){
            match[i] = ++k;
        }
        if(k == m){
            cout << "pos: " << i-m+1 << "\n";
            k = kmp[k];
        }
    }

}