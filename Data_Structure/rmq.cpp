struct Rmq{
    int n;
    int LOG;
    vector<vector<int> > minV;
    Rmq(){}
    Rmq(const vector<int> &a){
        n = a.size() - 1;
        assert(n >= 1);
        LOG = 31 - __builtin_clz(n) + 1;
        minV.assign(n + 1, vector<int>(LOG));
        for(int i = 1; i <= n; i++){
            minV[i][0] = a[i];
        }
    }
    void build_rmq(){
        for(int j = 1; j <= LOG; j++){
            for(int i = 1; i + (1 << j) - 1 <= n; i++){
                minV[i][j] = min(minV[i][j - 1], minV[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    int get_min(int l, int r){
        if(l > r) return (int)1e9;
        int k = 31 - __builtin_clz(r - l + 1);
        return min(minV[l][k], minV[r - (1 << k) + 1][k]);
    }
};