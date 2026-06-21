struct Hash {
    string s;
    int n;
    const long long MOD1 = 1e9 + 7;
    const long long MOD2 = 1e9 + 8277;
    const long long BASE = 256;
    vector<long long> pw1, pw2;
    vector<long long> has1, has2;
    Hash(string _s) {
        s = "*" + _s;
        n = _s.size();
        pw1.resize(n + 1);
        pw2.resize(n + 1);
        has1.resize(n + 1);
        has2.resize(n + 1);
    }
    void build_hash() {
        pw1[0] = pw2[0] = 1;
        has1[0] = has2[0] = 0;
        for (int i = 1; i <= n; i++) {
            pw1[i] = pw1[i - 1] * BASE % MOD1;
            pw2[i] = pw2[i - 1] * BASE % MOD2;
            has1[i] = (has1[i - 1] * BASE + s[i]) % MOD1;
            has2[i] = (has2[i - 1] * BASE + s[i]) % MOD2;
        }
    }
    pair<long long, long long> get_hash(int l, int r) {
        long long x1 = (has1[r] - has1[l - 1] * pw1[r - l + 1]) % MOD1;
        long long x2 = (has2[r] - has2[l - 1] * pw2[r - l + 1]) % MOD2;
        if (x1 < 0) x1 += MOD1;
        if (x2 < 0) x2 += MOD2;
        return {x1, x2};
    }
};