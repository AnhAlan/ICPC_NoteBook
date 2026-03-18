const int N = 1e6;
int primeDiv[N + 1];
void sieve_spf(){
    for (int i = 2; 1LL * i * i <= N; i++){
        if (primeDiv[i] == 0){
            for (int j = i * i; j <= N; j += i){ 
                primeDiv[j] = i;
            }
        }
    }
    for (int i = 2; i <= N; i++){ 
        if (primeDiv[i] == 0){
            primeDiv[i] = i;
        }
    }
}

vector<pair<int,int>>factor(int x){
    vector<pair<int,int>>res;
    while(x > 1){
        int p =  primeDiv[x];
        res.push_back({p,0});
        while(x % p == 0){
            res.back().second++;
            x /= p;
        }
    }
    return res;
}

