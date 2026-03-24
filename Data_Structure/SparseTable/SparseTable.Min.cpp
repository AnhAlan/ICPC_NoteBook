//2^log >= maxn
const int maxn = 1e6 + 5;
const int LOG = 20;
int n;
int a[maxn];           
int minV[maxn][LOG];    
void build_RMQ(){
    for(int i = 1; i <= n; i++) minV[i][0] = a[i]; 

    for(int j=1; MASK(j) <= n; j++){
        for(int i=1; i + MASK(j)-1 <= n; i++){
            
            minV[i][j] = min(minV[i][j-1], minV[i + MASK(j-1)][j-1]);
        }
    }
}
int getMin(int l,int r){
    int k = 31 - __builtin_clz(r-l+1); 
    return min(minV[l][k], minV[r - MASK(k) + 1][k]);
}

