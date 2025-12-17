const int N = 1e6;
int spf[N+1];

void sieve_spf(){
    for(int i = 1; i <= N; i++) spf[i] = i;
    for(int i = 2; i * i <= N; i++){
        if(spf[i] == i){
            for(int j = i*i; j <= N; j += i){
                if(spf[j] == j)
                    spf[j] = i;
            }
        }
    }
}

map<int,int> factor(int n){
    map<int,int> mp;
    while(n > 1){
        mp[spf[n]]++;
        n /= spf[n];
    }
    return mp;
}
