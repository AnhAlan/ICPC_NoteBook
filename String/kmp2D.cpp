struct KMP2D {
    string s;
    vector<vector<int>> kmp;
    void build(const string &str, int maxn) {
        kmp.assign(maxn + 5, vector<int>(maxn + 5));
        s = " " + str;
        int n = (int)s.size() - 1;
        for (int i = 1; i <= n; i++) {
            int k = 0;
            for (int j = 1; j <= n - i; j++) {
                while (k && s[j + i] != s[k + i]) {
                    k = kmp[i][k - 1];
                }
                if (s[j + i] == s[k + i]) {
                    ++k;
                }
                kmp[i][j] = k;
            }
        }
    }
    int get(int l, int r) {
        return kmp[l][r];
    }
};