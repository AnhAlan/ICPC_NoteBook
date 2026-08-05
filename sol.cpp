#include <bits/stdc++.h>
using namespace std;

int main() {
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int m, n;
    cin >> m >> n;
    vector<string> grid(m);
    for (int i = 0; i < m; ++i) {
        cin >> grid[i];
    }
    vector<vector<short>> min_len(m, vector<short>(n, 0));
    for (int i = 0; i < m; ++i) {
        short cnt = 0;
        for (int j = 0; j < n; ++j) {
            cnt = (grid[i][j] == '1') ? cnt + 1 : 0;
            min_len[i][j] = cnt;
        }
        cnt = 0;
        for (int j = n - 1; j >= 0; --j) {
            cnt = (grid[i][j] == '1') ? cnt + 1 : 0;
            min_len[i][j] = min(min_len[i][j], cnt);
        }
    }
    for (int j = 0; j < n; ++j) {
        vector<short> up(m, 0);
        short cnt = 0;
        for (int i = 0; i < m; ++i) {
            cnt = (grid[i][j] == '1') ? cnt + 1 : 0;
            up[i] = cnt;
        }
        cnt = 0;
        for (int i = m - 1; i >= 0; --i) {
            cnt = (grid[i][j] == '1') ? cnt + 1 : 0;
            short current_min = min(up[i], cnt);
            min_len[i][j] = min(min_len[i][j], current_min);
        }
    }
    int max_k = -1;
    int best_i = -1, best_j = -1;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (min_len[i][j] > 0) {
                int k = min_len[i][j] - 1;
                if (k > max_k) {
                    max_k = k;
                    best_i = i + 1; 
                    best_j = j + 1; 
                }

            }
        }
    }
    if (max_k == -1) {
        cout << -1 << "\n";
    } else {
        cout << 4 * max_k + 1 << "\n";
        cout << best_i << " " << best_j << "\n";
    }

    return 0;
}