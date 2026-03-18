struct Hash{
    string s;
    static const int maxn = 1e3 + 5;
    const int mod1 = (int)1e9 + 7;
    const int mod2 = (int)1e9 + 9277;
    long long pw1[maxn], pw2[maxn];
    long long hs1[maxn], hs2[maxn];
    int base = 256;
    Hash(string _s){
        s = "#" + _s;
    }

    void build(){
        int n = s.size();
        pw1[0] = pw2[0] = 1; 
        for(int i = 1; i <= maxn; i++){
            pw1[i] = 1ll * pw1[i - 1] * base % mod1;
            pw2[i] = 1ll * pw2[i - 1] * base % mod2;
        }
        for(int i = 1; i <= n; i++){
            hs1[i] = (hs1[i - 1] + 1ll * s[i] * pw1[i]) % mod1;
            hs2[i] = (hs2[i - 1] + 1ll * s[i] * pw2[i]) % mod2;
        }
    }

    pair<long long,long long> getHash(int l, int r){
        long long res1 = (hs1[r] - hs1[l - 1] + mod1) % mod1;
        long long res2 = (hs2[r] - hs2[l - 1] + mod2) % mod2;
        res1 = res1 * (pw1[maxn - r]) % mod1;
        res2 = res2 * (pw2[maxn - r]) % mod2;
        return {res1, res2};
    }
};