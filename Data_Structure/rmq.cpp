template<typename T, typename F = Merge<T>>
struct Rmq{
    int n;
    int LOG;
    F merge;
    vector<vector<T> > minV;
    Rmq(){}
    Rmq(const vector<T> &a){
        n = (int) a.size() - 1;
        assert(n >= 1);
        LOG = 31 - __builtin_clz(n) + 1;
        minV.assign(n + 1, vector<T>(LOG));
        for(int i = 1; i <= n; i++){
            minV[i][0] = a[i];
        }
    }
    void build(){
        for(int j = 1; j <= LOG; j++){
            for(int i = 1; i + (1 << j) - 1 <= n; i++){
                minV[i][j] = merge(minV[i][j - 1], minV[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    T get(int l, int r){
        assert(l <= r && l >= 1 && r <= n);
        int k = 31 - __builtin_clz(r - l + 1);
        return merge(minV[l][k], minV[r - (1 << k) + 1][k]);
    }
};