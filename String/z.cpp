template <typename T>
vector<int> z_function(int n, const T &s) {
    vector<int> z(n + 1, 0);
    int l = 1, r = 1;
    for (int i = 2; i <= n; i++) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l + 1]); 
        }
        while (i + z[i] <= n && s[1 + z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}
// 1 index
template <typename T>
vector<int> z_function(const T &s) {
    return z_function((int)s.size() - 1, s);
}