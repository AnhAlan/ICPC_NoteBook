using u128 = __uint128_t;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
long long mod_mul(long long a, long long b, long long mod) {
    return (u128)a * b % mod;
}
long long mod_pow(long long a, long long d, long long mod) {
    long long r = 1;
    while (d) {
        if (d & 1) r = mod_mul(r, a, mod);
        a = mod_mul(a, a, mod);
        d >>= 1;
    }
    return r;
}
bool is_prime(long long n) {
    if (n < 2) return false;
    for (long long p : {2,3,5,7,11,13,17,19,23,29,31,37}){
        if (n % p == 0) return n == p;
    }
    long long d = n - 1, s = 0;
    while ((d & 1) == 0) d >>= 1, s++;
    auto check = [&](long long a) {
        long long x = mod_pow(a, d, n);
        if (x == 1 || x == n - 1) return true;
        for (long long i = 1; i < s; i++) {
            x = mod_mul(x, x, n);
            if (x == n - 1) return true;
        }
        return false;
    };
    for (long long a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}){
        if (a % n && !check(a)) return false;
    }
    return true;
}
long long f(long long x, long long c, long long mod) {
    return (mod_mul(x, x, mod) + c) % mod;
}
long long pollard_rho(long long n) {
    if (n % 2 == 0) return 2;
    if (n % 3 == 0) return 3;
    uniform_int_distribution<long long> dist(2, n - 2);
    long long x = dist(rng);
    long long y = x;
    long long c = dist(rng);
    long long d = 1;
    while (d == 1) {
        x = f(x, c, n);
        y = f(f(y, c, n), c, n);
        d = gcd(llabs(x - y), n);
        if (d == n) return pollard_rho(n);
    }
    return d;
}
vector<long long> tmp;
void factor(long long n) {
    if (n == 1) return;
    if (is_prime(n)) {
        tmp.push_back(n);
        return;
    }
    long long d = pollard_rho(n);
    factor(d);
    factor(n / d);
}
vector<pair<long long,long long>> get_factors(long long n) {
    tmp.clear();
    factor(n);
    sort(tmp.begin(), tmp.end());
    vector<pair<long long,long long>> res;
    for (long long x : tmp) {
        if (res.empty() || res.back().first != x){
            res.push_back({x, 1});
        }
        else res.back().second++;
    }
    return res;
}
/*
    is_prime(n) -> check prime (64-bit)
    auto fac = get_factors(n) -> factorization
    format: {{prime, exponent}}
*/
