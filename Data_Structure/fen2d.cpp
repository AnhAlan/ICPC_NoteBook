template<typename T>
struct Fenwick2D{
    int n, m;
    vector<vector<T> > bit;
    Fenwick2D(int _n, int _m) : n(_n), m(_m), bit(_n + 1, vector<T>(_m + 1, 0)) {}
    void update(int x, int y, T v) { 
        for(int i = x; i <= n; i += (i & -i)){
            for(int j = y; j <= m; j += (j & -j)){
                bit[i][j] += v;
            }
        }
    }
    T query(int x, int y) { 
        T res = 0;
        for(int i = x; i > 0; i -= (i & -i)){
            for(int j = y; j > 0; j -= (j & -j)){
                res += bit[i][j];
            }
        }
        return res;
    }
    T get(int x1, int y1, int x2, int y2) { 
        return query(x2,y2) - query(x1-1,y2) - query(x2,y1-1) + query(x1-1,y1-1);
    }
};