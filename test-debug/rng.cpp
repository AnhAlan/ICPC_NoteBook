mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
long long rand(long long l,long long r){
    uniform_int_distribution<long long> dist(l,r);
    return dist(rng);
}