#include <bits/stdc++.h>
#define ll long long
#define en "\n"
using namespace std;

const int BASE = 256;
const ll MOD = 1e9 + 2277;
const int MAX = 200005;

ll pw[MAX], hs[MAX];


/*
    Returns the hash of the substring [l, r].
    tmp = hs[r] - hs[l-1]  → sum of weighted characters in the range l..r
    Multiply by pw[MAX - r] to normalize the substring,
    so that hashes of substrings at different positions can be compared directly.
*/
ll gethash(int l, int r) {
    ll tmp = (hs[r] - hs[l-1] + MOD) % MOD;
    return tmp * pw[MAX - r] % MOD;  
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    s = "#" + s;
    int n = s.size() - 1;

    //pw[i] = 256^i-1 
    pw[0] = 1;
    for (int i = 1; i < MAX; i++) 
        pw[i] = 1ll *  pw[i-1] * BASE % MOD;

    //hs[i] = hs[i-1] + char * 256^i-1
    for (int i = 1; i <= n; i++)
        hs[i] = (1ll * hs[i-1] + s[i] * pw[i]) % MOD;

    while (true) {
        int l, r;
        cin >> l >> r;
        cout << gethash(l, r) << en;
        cout.flush();
    }
}
