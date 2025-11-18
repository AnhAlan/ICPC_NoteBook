#include <bits/stdc++.h>
#define ll long long
#define all(a) a.begin(), a.end()
#define en "\n"
#define DEBUG(x) cout << #x << " = " << x << endl;
#define MASK(x) ((1) << (x))
#define BIT(mask,i) (((mask) >> (i))&1)
using namespace std;


// Sparse Table constants
const int MAXN = 1e6 + 5;
const int LOG = 20;

int n, a[10];           // n = array size, a[] = input array
int minV[MAXN][LOG];    // Sparse Table: minV[i][j] = min in range [i, i+2^j-1]

// Build Sparse Table
void build(){
    for(int i=1;i<=n;i++) minV[i][0] = a[i]; // base case: intervals of length 1

    for(int j=1; MASK(j) <= n; j++){
        for(int i=1; i + MASK(j)-1 <= n; i++){
            // combine two intervals of length 2^(j-1)
            minV[i][j] = min(minV[i][j-1], minV[i + MASK(j-1)][j-1]);
        }
    }
}

// Query minimum in range [l, r] in O(1)
int getMin(int l,int r){
    int k = 31 - __builtin_clz(r-l+1); // floor(log2(r-l+1))
    return min(minV[l][k], minV[r - MASK(k) + 1][k]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];

    build();        // build Sparse Table

    int q;
    cin >> q;
    while(q--){
        int l,r;
        cin >> l >> r;
        cout << getMin(l,r) << en; // output minimum in [l, r]
    }
}
