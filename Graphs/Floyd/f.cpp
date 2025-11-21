#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int N = 505;

int n, m, q;
int d[N][N], r[N][N]; 
// d[u][v] = shortest distance from u to v
// r[u][v] = intermediate vertex used in the shortest path (0 means direct edge)

// Recursively print path from u to v
void route(int u, int v) {
    // If no intermediate vertex, directly print destination
    if (r[u][v] == 0) {
        cout << v << " ";
    } 
    // Otherwise, split path: u → r[u][v] → v
    else {
        route(u, r[u][v]);
        route(r[u][v], v);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    // Initialize distance matrix:
    // 0 for diagonal, INF for others
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            d[i][j] = (i == j ? 0 : INF);

    // Input edges (undirected graph)
    for (int i = 0; i < m; ++i) {
        int x, y, t;
        cin >> x >> y >> t;
        d[x][y] = t;
        d[y][x] = t;
    }

    // Floyd–Warshall algorithm (O(n^3))
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {

                // If path i → k → j is shorter, update distance
                if (d[i][k] < INF && d[k][j] < INF && 
                    d[i][j] > d[i][k] + d[k][j]) {

                    d[i][j] = d[i][k] + d[k][j];
                    r[i][j] = k;   // store intermediate vertex
                }
            }
        }
    }

    cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;

        if (d[x][y] == INF) {
            cout << "-1\n";   // no path exists
        } else {
            cout << "Shortest distance: " << d[x][y] << "\n";
            cout << "Path: " << x << " ";
            route(x, y);
            cout << "\n";
        }
    }

    return 0;
}
