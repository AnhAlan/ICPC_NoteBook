template<typename T>
struct Merge{
    T operator()(const T &A, const T &B) const {
        return min(A, B);
    }
    T none() const {
        return numeric_limits<T>::max();
        //return numeric_limits<T>::lowest();
    }
};


template<typename T, typename F = Merge<T>>
struct Rmq{
    int n;
    int LOG;
    F merge;
    vector<vector<T> > min_v;
    Rmq(){}
    Rmq(const vector<T> &a){
        n = (int) a.size() - 1;
        assert(n >= 1);
        LOG = 31 - __builtin_clz(n) + 1;
        min_v.assign(n + 1, vector<T>(LOG));
        for(int i = 1; i <= n; i++){
            min_v[i][0] = a[i];
        }
    }
    void build(){
        for(int j = 1; j <= LOG; j++){
            for(int i = 1; i + (1 << j) - 1 <= n; i++){
                min_v[i][j] = merge(min_v[i][j - 1], min_v[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    T get(int l, int r){
        assert(l <= r && l >= 1 && r <= n);
        int k = 31 - __builtin_clz(r - l + 1);
        return merge(min_v[l][k], min_v[r - (1 << k) + 1][k]);
    }
};