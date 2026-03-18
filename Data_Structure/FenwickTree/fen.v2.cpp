template<typename T>
struct FenWick{
    //update [l, r] & get(i)
    T n;
    vector<T>bit;
    FenWick(T _n){
        n = _n;
        bit.assign(n + 1,0);
    }

    void update(int i, T v){
        for(; i <= n; i += (i & -i)){
            bit[i] += v;
        }
    }

    T get(int i){
        T res = 0;
        for(; i > 0; i -= (i & -i)){
            res += bit[i];
        }
        return res;
    }

    void updateRange(T l, T r, T v){
        update(l, v);
        update(r + 1, -v);
    }
};