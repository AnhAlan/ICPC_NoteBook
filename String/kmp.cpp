template<typename T>
vector<int> kmp(int n, const T &s) {
    vector<int> res(n + 1, 0);
    int k = 0;
    for (int i = 2; i <= n; i++) {
        while (k > 0 && s[i] != s[k + 1]) {
            k = res[k];
        }
        if (s[i] == s[k + 1]) {
            k++;
        }
        res[i] = k;
    }
    return res;
}
// index 1
template<typename T>
vector<int> kmp(const T &s) {
    return kmp((int)s.size() - 1, s); 
}
// find t in s
template<typename T>
vector<int> match(const T &s, const T &t, const vector<int> &kmp_t) {
    vector<int> match_id; 
    int n = (int)s.size() - 1;
    int m = (int)t.size() - 1;
    int k = 0;
    for (int i = 1; i <= n; i++) {
        while (k > 0 && s[i] != t[k + 1]) {
            k = kmp_t[k];
        }
        if (s[i] == t[k + 1]) {
            k++;
        }
        if (k == m) {
            match_id.push_back(i - m + 1); 
            k = kmp_t[k];
        }
    }
    return match_id;
}