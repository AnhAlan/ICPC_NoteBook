// can random base 
const long long base1 = 256 ;
const long long base2 = 652;
const long long mod1 = 1e9 + 7; 
const long long mod2 = 1e9 + 33;
template <typename T>
struct Poly_hash {
    int n;
    inline static vector<long long> pw1 = {1};
    inline static vector<long long> pw2 = {1};
    vector<long long> has1, has2;
    Poly_hash(const T &a) {
        n = (int)a.size() - 1;
        has1.assign(n + 1, 0);
        has2.assign(n + 1, 0);
        while ((int)pw1.size() <= n) {
            pw1.push_back((pw1.back() * base1) % mod1);
            pw2.push_back((pw2.back() * base2) % mod2);
        }
        for (int i = 1; i <= n; i++) {
            has1[i] = (has1[i - 1] * base1 + a[i]) % mod1;
            has2[i] = (has2[i - 1] * base2 + a[i]) % mod2;
        }
    }
    pair<long long, long long> get_hash(int l, int r) const {
        assert(l <= r);
        long long x1 = (has1[r] - has1[l - 1] * pw1[r - l + 1]) % mod1;
        long long x2 = (has2[r] - has2[l - 1] * pw2[r - l + 1]) % mod2;
        if (x1 < 0) x1 += mod1;
        if (x2 < 0) x2 += mod2;
        return {x1, x2};
    }
    /*
        Poly_hash<string / vector<int> > hs
    */
};