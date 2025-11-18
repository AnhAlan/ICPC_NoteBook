#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 1e5 + 6;
int BIT[MAXN];
int a[MAXN];
int n;

struct FenwickTree {
    int n;
    vector<int> BIT;

    // Constructor
    FenwickTree(int n) : n(n) {
        BIT.assign(n + 1, 0);  // initialize BIT from 0
    }

    // Update BIT: add val to idx position
    void update(int idx, int val) {
        for(;idx<=n;idx+=(idx&-idx)){
            BIT[idx] += val;
        }
    }

    // Get the sum of prefix 1..idx
    int query(int idx) {
        int res = 0;
        for(;idx>0; idx-=(idx&-idx)){
            res += BIT[idx];
        }
        return res;
    }

    // Get the sum from l..r
    int rangeQuery(int l, int r) {
        return query(r) - query(l - 1);
    }
};

int main() {
    FenwickTree ft(10);
    // FenwickTree ft[10] // each array is frenwick 
    ft.update(3, 5);
    cout << ft.query(3) << "\n"; 
}



