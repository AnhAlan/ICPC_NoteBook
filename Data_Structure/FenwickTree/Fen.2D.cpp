#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define en "\n"

const int maxn = 1005;
int n, m;
ll BIT[maxn][maxn];

// Update the Fenwick Tree at position (x, y) by adding 'val'
void update(int x, int y, int val) {
    for (int i = x; i <= n; i += i & -i)
        for (int j = y; j <= m; j += j & -j)
            BIT[i][j] += val;
}

// Query prefix sum from (1,1) to (x,y)
ll query(int x, int y) {
    ll sum = 0;
    for (int i = x; i > 0; i -= i & -i)
        for (int j = y; j > 0; j -= j & -j)
            sum += BIT[i][j];
    return sum;
}

// Get the sum of the rectangle (x1, y1) to (x2, y2)
ll getSum(int x1, int y1, int x2, int y2) {
    // Inclusion–exclusion formula for 2D Fenwick Tree
    return query(x2, y2)
         - query(x1 - 1, y2)
         - query(x2, y1 - 1)
         + query(x1 - 1, y1 - 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    // Number of update queries
    int q; 
    cin >> q;
    while (q--) {
        int x, y, val;
        cin >> x >> y >> val;
        update(x, y, val);
    }

    // Number of range sum queries
    int qq;
    cin >> qq;
    while (qq--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        cout << getSum(x1, y1, x2, y2) << "\n";
    }
}
