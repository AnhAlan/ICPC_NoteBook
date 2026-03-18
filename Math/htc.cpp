const int MOD = 1e9 + 7;
const int maxn = 101; 
long long fac[maxn], inv[maxn];
long long powMod(long long a, long long b) {
    long long res = 1;
    a %= MOD;
    while(b) {
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}
void build() {
    fac[0] = 1;
    for(int i = 1; i < maxn; i++){
        fac[i] = fac[i-1] * i % MOD;
    }
    inv[maxn-1] = powMod(fac[maxn-1], MOD-2);
    for(int i = maxn-1; i > 0; i--){
        inv[i-1] = inv[i] * i % MOD;
    }
}

long long A(int n, int k) {
    if(k > n) return 0;
    return fac[n] * inv[n-k] % MOD;
}

long long C(int n, int k) {
    if(k > n) return 0;
    return fac[n] * inv[k] % MOD * inv[n-k] % MOD;
}

