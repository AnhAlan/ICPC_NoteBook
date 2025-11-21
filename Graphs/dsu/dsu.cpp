#include<bits/stdc++.h>
#define ll long long
#define all(a) a.begin(),a.end()

using namespace std;
int parent[1001];
int Size[1001];
int n;

void make_set(int a){
    for(int i=1;i<=n;i++){
        parent[i] = i;
        Size[i] = 1;
    }
}

int find(int a){
    if(parent[a] == a){
        return a;
    }
    return parent[a] = find(parent[a]);
}

void Union(int a,int b){
    a = find(a);
    b = find(b);
    if(a != b){
        if(Size[a] < Size[b] ){
            swap(a,b);
        }
        parent[b] = a;
        Size[a] += Size[b];
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
}