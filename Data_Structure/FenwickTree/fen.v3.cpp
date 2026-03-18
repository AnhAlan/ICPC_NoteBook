template<typename T>
struct Fenwick{
    int n;
    vector<T> bitMul, bitAdd;

    Fenwick(int _n){
        n = _n;
        bitMul.assign(n + 1, 0);
        bitAdd.assign(n + 1, 0);
    }

    void update(vector<T> &bit, int i, T v){
        for(; i <= n; i += (i & -i)) bit[i] += v;
    }

    T get(vector<T> &bit, int i){
        T res = 0;
        for(; i > 0; i -= (i & -i)) res += bit[i];
        return res;
    }

    void updateRange(int l, int r, T v){
        update(bitMul, l, v);
        update(bitMul, r + 1, -v);
        update(bitAdd, l, -v * (l - 1));
        update(bitAdd, r + 1, v * r);
    }

    T getPrefix(int x){
        return get(bitMul, x) * x + get(bitAdd, x);
    }

    T get(int l, int r){
        return getPrefix(r) - getPrefix(l - 1);
    }
};