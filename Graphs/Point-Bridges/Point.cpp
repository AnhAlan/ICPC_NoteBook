#include <bits/stdc++.h>
#define MASK(i) ((1) << i)
using namespace std;

const int MAX = 500500;
const int LOG = 19;

int numNode, numEdge;
pair<int, int> edges[MAX];
vector<int> adj[MAX];

bool used[MAX];
int low[MAX], num[MAX], cnt;
int par[MAX][LOG + 1], fin[MAX];
int high[MAX], numChild[MAX];
bool isCut[MAX];
int dsu[MAX];

int findSet(int u){
    if (dsu[u] < 0) return u;
    return dsu[u] = findSet(dsu[u]);
}

bool unionSet(int u, int v){
    int x = findSet(u);
    int y = findSet(v);
    if (x == y) return false;

    if (dsu[x] > dsu[y]) swap(x, y);

    dsu[x] += dsu[y];
    dsu[y] = x;
    return true;
}


void loadGraph() {
    cin >> numNode >> numEdge;
    for (int i = 1; i <= numEdge; i++) {
        int u, v;
        cin >> u >> v;
        edges[i] = {u, v};
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

void dfs(int u) {
    num[u] = low[u] = ++cnt;

    for (int v : adj[u]) {
        if (!num[v]) {
            par[v][0] = u;
            high[v] = high[u] + 1;
            numChild[u]++;

            dfs(v);

            low[u] = min(low[u], low[v]);

            if (par[u][0] != 0 && low[v] >= num[u]) {
                isCut[u] = true;
            }
        } 
        else if (v != par[u][0]) {
            low[u] = min(low[u], num[v]);
        }
    }

    fin[u] = cnt;
}

void prepare() {
    fill(dsu, dsu + numNode + 1, -1);

    for (int i = 1; i <= numEdge; i++) {
        unionSet(edges[i].first, edges[i].second);
    }

    for (int i = 1; i <= numNode; i++) {
        if (num[i] == 0) {
            dfs(i);
            if (numChild[i] >= 2) {
                isCut[i] = true;
            }
        }
    }

    for (int j = 1; j <= LOG; j++) {
        for (int i = 1; i <= numNode; i++) {
            int mid = par[i][j - 1];
            if (mid != 0) {
                par[i][j] = par[mid][j - 1];
            }
        }
    }
}


bool inSubtree(int u, int v) {
    return (num[u] <= num[v] && num[v] <= fin[u]);
}


int jump(int u, int k) {
    for(int j=LOG; j >= 0 ; j--){
        if(MASK(j) <= k){
            u = par[u][j];
            k -= MASK(j);
        }
    }
    return u;
}


bool checkCut(int a, int b, int u) {
    if (findSet(a) != findSet(b)) return false;
    if (!isCut[u]) return true;

    int childA = -1, childB = -1;

    if (a != u && inSubtree(u, a)) {
        childA = jump(a, high[a] - high[u] - 1);
    }
    if (b != u && inSubtree(u, b)) {
        childB = jump(b, high[b] - high[u] - 1);
    }

    if (childA > 0 && low[childA] < num[u]) childA = -1;
    if (childB > 0 && low[childB] < num[u]) childB = -1;

    return (childA == childB);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    loadGraph();
    prepare();
    for(int i=1;i<=numNode;i++){
        if(isCut[i]){
            cout << i << " ";
        }
    }
    cout << endl;
    while(1){
        int u,a,b;
        cin >> u >> a >> b;
        cout << (checkCut(a,b,u) ? "yes" : "no") << endl;
        cout.flush();
    }
}
