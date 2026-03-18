long long gilbertOrder(int x, int y, int pow, int rotate) {
    if (pow == 0) return 0;
    int h = 1 << (pow - 1);
    int seg = 0;
    if (x >= h) seg |= 1;
    if (y >= h) seg |= 2;

    seg = (seg + rotate) & 3;
    static int rotateDelta[4] = {3, 0, 0, 1};
    int nx = x & (h - 1), ny = y & (h - 1);
    int nrot = (rotate + rotateDelta[seg]) & 3;

    long long subSquareSize = 1LL << (2 * pow - 2);
    long long ans = seg * subSquareSize;
    long long add = gilbertOrder(nx, ny, pow - 1, nrot);

    if (seg == 1 || seg == 2) ans += add;
    else ans += subSquareSize - add - 1;

    return ans;
}

struct Query {
    int l, r, id;
    long long ord;
    void calcOrder() { 
        ord = gilbertOrder(l, r, 3, 0); 
    }

    bool operator < (const Query& other) const {
        return ord < other.ord;
    }
};

const int MAXN = 1e5 + 5; 
int a[MAXN];              
int cnt[MAXN];            
int dist = 0;           
void add(int x) {
    cnt[x]++;
    if (cnt[x] == 1) dist++;
}

void remove_(int x) {
    cnt[x]--;
    if (cnt[x] == 0) dist--;
}
