#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 5;
int a[MAXN], cnt[MAXN], ans[MAXN];
int n, q, BLOCK;
int distinct = 0;

struct Query {
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    cin >> q;
    vector<Query> queries(q);
    BLOCK = sqrt(n);

    for (int i = 0; i < q; i++) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].id = i;
    }
    sort(queries.begin(), queries.end(), cmp);
    for(auto [l,r,id] : queries){
        cout << l << " " << r << " " << id << endl;
    }
    

    int L = 1, R = 0;
    for (auto &qr : queries) {
        int l = qr.l, r = qr.r;
        while (L > l) add(a[--L]);
        while (R < r) add(a[++R]);
        while (L < l) remove_(a[L++]);
        while (R > r) remove_(a[R--]);
        ans[qr.id] = distinct;
    }

    for (int i = 0; i < q; i++)
        cout << ans[i] << "\n";
}
