const int MAXN = 100000 + 5;
int a[MAXN], cnt[MAXN];
int n, q, BLOCK;
int distinct = 0;
struct Query{
    int l, r, id;
};

bool cmp(const Query &A, const Query &B) {
    int blockA = A.l / BLOCK;
    int blockB = B.l / BLOCK;
    if (blockA != blockB)
        return blockA < blockB;
    return A.r < B.r;
}

void add(int x) {
    cnt[x]++;
    if (cnt[x] == 1) distinct++;
}

void remove_(int x) {
    cnt[x]--;
    if (cnt[x] == 0) distinct--;
}
