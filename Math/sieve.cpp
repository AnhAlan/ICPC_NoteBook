struct Sieve {
    int n;
    vector<bool> isPrime;
    Sieve(int _n) {
        n = _n;
        isPrime.assign(n + 1, true);
    }
    void build_sieve() {
        isPrime[0] = isPrime[1] = false;
        for (int i = 2; i * i <= n; i++) {
            if (isPrime[i]) {
                for (int j = i * i; j <= n; j += i) {
                    isPrime[j] = false;
                }
            }
        }
    }
    bool check_prime(int x) {
        return isPrime[x];
    }
};